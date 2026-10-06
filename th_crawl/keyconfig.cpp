#include "keyconfig.h"

#include "const.h"
#include "display.h"
#include "d3dUtility.h"
#include "joypad.h"
#include "key.h"
#include "localization.h"
#include "option_manager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <set>
#include <shellapi.h>
#include <sstream>
#include <windows.h>

extern HANDLE mutx;
extern display_manager DisplayManager;

key_binding_manager keybind_mg;

namespace
{
	constexpr int KEY_UNBOUND_COMMAND = 0xE100;
	constexpr int KEYCONFIG_SCROLL_UP = 0xE210;
	constexpr int KEYCONFIG_SCROLL_DOWN = 0xE211;
	constexpr int KEYCONFIG_CLEAR = 0xE212;
	constexpr int KEYCONFIG_RESET = 0xE213;
	constexpr int KEYCONFIG_OPEN_FILE = 0xE214;
	constexpr int KEYCONFIG_BACK = 0xE215;
	constexpr int KEYCONFIG_RESET_YES = 0xE216;
	constexpr int KEYCONFIG_RESET_NO = 0xE217;
	constexpr int KEYCONFIG_ADD = 0xE218;
	constexpr int KEYCONFIG_RESET_ALL = 0xE219;
	constexpr int KEYCONFIG_ENTRY_BASE = 0xE300;

	std::string trim_copy(const std::string& value)
	{
		size_t first = value.find_first_not_of(" \t\r\n");
		if(first == std::string::npos)
			return "";
		size_t last = value.find_last_not_of(" \t\r\n");
		return value.substr(first, last - first + 1);
	}

	std::string upper_copy(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
		return value;
	}

	bool is_gamepad_key(int key)
	{
		return key >= GVK_BUTTON_A && key <= GVK_START;
	}

	bool is_step_movement_command(int key)
	{
		switch(key)
		{
		case 'k': case 'j': case 'h': case 'l':
		case 'b': case 'n': case 'y': case 'u':
			return true;
		default:
			return false;
		}
	}

	bool is_long_movement_command(int key)
	{
		switch(key)
		{
		case 'K': case 'J': case 'H': case 'L':
		case 'B': case 'N': case 'Y': case 'U':
			return true;
		default:
			return false;
		}
	}

	bool is_step_movement_submenu_key(int key)
	{
		switch(key)
		{
		case '*': case 'v': case 'e': case 'E': case '.': case 'x':
		case '<': case '>': case '+': case '=': case '-':
		case '(': case ')': case 'i':
			return true;
		default:
			return false;
		}
	}

	bool is_long_movement_submenu_key(int key)
	{
		// Long movement is accepted only by the local/wide search screens.
		switch(key)
		{
		case 'v': case 'e': case 'E': case '.': case 'x': case '<': case '>':
			return true;
		default:
			return false;
		}
	}

	bool is_fixed_binding_key(int key)
	{
		if(key == '1' || key == '2' || key == '3' || key == '4' ||
			key == '6' || key == '7' || key == '8' || key == '9')
			return true;
		if(!is_virtual_key_code(key))
			return false;
		switch(get_virtual_key(key))
		{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_NUMPAD1:
		case VK_NUMPAD3:
		case VK_NUMPAD7:
		case VK_NUMPAD9:
			return true;
		default:
			return false;
		}
	}

	bool is_fixed_direction_input(int key, const InputedKey& inputed)
	{
		if(key == '1' || key == '2' || key == '3' || key == '4' ||
			key == '6' || key == '7' || key == '8' || key == '9')
			return true;
		if(inputed.mouse != MKIND_NONE)
			return false;
		if(inputed.key.message == GAMEPAD_DIRECTION_MESSAGE || inputed.key.message == GAMEPAD_DPAD_MESSAGE)
			return true;
		if(inputed.key.message != WM_KEYDOWN)
			return false;
		switch(inputed.key.wParam)
		{
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_NUMPAD1:
		case VK_NUMPAD2:
		case VK_NUMPAD3:
		case VK_NUMPAD4:
		case VK_NUMPAD6:
		case VK_NUMPAD7:
		case VK_NUMPAD8:
		case VK_NUMPAD9:
		case VK_HOME:
		case VK_END:
		case VK_PRIOR:
		case VK_NEXT:
		case '1':
		case '2':
		case '3':
		case '4':
		case '6':
		case '7':
		case '8':
		case '9':
			return true;
		default:
			return false;
		}
	}

	int macro_capture_key(int key, const InputedKey& inputed)
	{
		if(inputed.mouse != MKIND_NONE)
			return key;
		if(inputed.key.message == GAMEPAD_DPAD_MESSAGE)
			return make_virtual_key_code(static_cast<int>(inputed.key.wParam));
		if(inputed.key.message == WM_KEYDOWN)
		{
			switch(inputed.key.wParam)
			{
			case VK_UP:
			case VK_NUMPAD8:
			case VK_DOWN:
			case VK_NUMPAD2:
			case VK_LEFT:
			case VK_NUMPAD4:
			case VK_RIGHT:
			case VK_NUMPAD6:
				return make_virtual_key_code(key);
			case VK_NUMPAD1:
			case VK_END:
				return make_virtual_key_code(VK_NUMPAD1);
			case VK_NUMPAD3:
			case VK_NEXT:
				return make_virtual_key_code(VK_NUMPAD3);
			case VK_NUMPAD7:
			case VK_HOME:
				return make_virtual_key_code(VK_NUMPAD7);
			case VK_NUMPAD9:
			case VK_PRIOR:
				return make_virtual_key_code(VK_NUMPAD9);
			default:
				break;
			}
		}
		return key;
	}

	void add_keyboard(std::vector<key_binding_entry>& entries, const char* id, LOCALIZATION_ENUM_KEY label, int command, int key)
	{
		entries.push_back({id, label, command, {key}, {key}});
	}

	void add_keyboard(std::vector<key_binding_entry>& entries, const char* id, LOCALIZATION_ENUM_KEY label, int command, std::initializer_list<int> keys)
	{
		entries.push_back({id, label, command, keys, keys});
	}

	void add_gamepad(std::vector<key_binding_entry>& entries, const char* id, LOCALIZATION_ENUM_KEY label, int command, int key)
	{
		entries.push_back({id, label, command, {key}, {key}});
	}

	void add_gamepad(std::vector<key_binding_entry>& entries, const char* id, LOCALIZATION_ENUM_KEY label,
		int command, std::initializer_list<int> keys, int input_context)
	{
		entries.push_back({id, label, command, keys, keys, input_context});
	}

	std::string key_config_pad_button(int command);

	void render_device_select(int selected)
	{
		char blank[32];
		sprintf_s(blank,32,"            ");

		WaitForSingleObject(mutx, INFINITE);
		deletesub(false);

		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("======",false,CL_help);
		printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_TITLE), false, CL_help);
		printsub("======",false,CL_help);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("a - " + LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_KEYBOARD),true,CL_normal,'a');
		printsub(blank,false,CL_warning);
		printsub("b - " + LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GAMEPAD),true,CL_normal,'b');
		printsub("",true,CL_normal);
		printsub(blank,false,CL_warning);
		printsub("esc - " + LocalzationManager::locString(LOC_SYSTEM_OPTION_MENU_BACK),true,CL_normal,VK_ESCAPE);
		DisplayManager.current_position = selected;
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
	}

	int key_config_page_rows()
	{
		return std::max(1, DisplayManager.log_length - 5);
	}

	int key_config_column_width()
	{
		int font_width = std::max(1, static_cast<int>(DisplayManager.fontDesc.Width));
		int screen_width = static_cast<int>(option_mg.getWidth() / font_width);
		return std::max(20, std::min(44, screen_width - 30));
	}

	std::string key_config_pad_button(int command)
	{
		return joypadUtil::getRawGamepad(static_cast<wchar_t>(command));
	}

	enum class key_config_category
	{
		MOVEMENT,
		DUNGEON,
		ITEM,
		MAGIC,
		CHARACTER,
		COMMAND,
		CONVENIENCE,
		ABILITY,
		GAMEPAD,
		MAP_SEARCH,
		PROJECTILE
	};

	struct key_config_row
	{
		int left = -1;
		int right = -1;
		LOCALIZATION_ENUM_KEY heading = LOC_NONE;
	};

	key_config_category get_key_config_category(const key_binding_entry& entry, bool gamepad)
	{
		if(gamepad)
		{
			if(entry.input_context == KEY_INPUT_MAP_SEARCH)
				return key_config_category::MAP_SEARCH;
			if(entry.input_context == KEY_INPUT_PROJECTILE)
				return key_config_category::PROJECTILE;
			return key_config_category::GAMEPAD;
		}
		const std::string& id = entry.id;
		if(id.rfind("MOVE_", 0) == 0 || id.rfind("RUN_", 0) == 0 || id == "AUTO_TRAVEL")
			return key_config_category::MOVEMENT;
		if(id == "SEARCH" || id == "WAIT" || id == "LONG_REST" ||
			id == "WIDE_SEARCH" || id == "STAIRS_DOWN" || id == "STAIRS_UP" || id == "CLOSE_DOOR" ||
			id == "OPEN_DOOR" || id == "FLOOR_TRAVEL" || id == "AUTO_ATTACK")
			return key_config_category::DUNGEON;
		if(id == "INVENTORY" || id == "PICKUP" || id == "DROP" || id == "DROP_LAST" || id == "WIELD" ||
			id == "WEAR_ARMOUR" || id == "REMOVE_ARMOUR" || id == "EAT" || id == "DRINK" || id == "READ" ||
			id == "WEAR_JEWELRY" || id == "REMOVE_JEWELRY" || id == "FIND_ITEM" || id == "QUICK_THROW" ||
			id == "SELECT_THROW" || id == "EVOKE" || id == "EVOKE_SPELLCARD" || id == "SWAP_WEAPON" ||
			id == "AUTO_PICKUP")
			return key_config_category::ITEM;
		if(id == "QUICK_CAST" || id == "CAST" || id == "SPELL_INFO" || id == "MEMORIZED_SPELLS")
			return key_config_category::MAGIC;
		if(id == "CHARACTER_STATS" || id == "IDENTIFIED_ITEMS" || id == "SKILL_INFO" || id == "GOD_INFO" ||
			id == "PROPERTY" || id == "WEAPON_LIST" || id == "ARMOUR_LIST" || id == "RUNE_LIST" ||
			id == "AMULET_INFO" || id == "STATE_INFO" || id == "EXPERIENCE_INFO" || id == "DUNGEON_MAP")
			return key_config_category::CHARACTER;
		if(id == "PRAY" || id == "ABILITY" || id == "SHOUT")
			return key_config_category::ABILITY;
		if(id == "REPEAT" || id == "MACRO")
			return key_config_category::CONVENIENCE;
		return key_config_category::COMMAND;
	}

	LOCALIZATION_ENUM_KEY get_key_config_category_label(key_config_category category)
	{
		switch(category)
		{
		case key_config_category::MOVEMENT: return LOC_SYSTEM_KEYCONFIG_CATEGORY_MOVEMENT;
		case key_config_category::DUNGEON: return LOC_SYSTEM_KEYCONFIG_CATEGORY_DUNGEON;
		case key_config_category::ITEM: return LOC_SYSTEM_KEYCONFIG_CATEGORY_ITEM;
		case key_config_category::MAGIC: return LOC_SYSTEM_KEYCONFIG_CATEGORY_MAGIC;
		case key_config_category::CHARACTER: return LOC_SYSTEM_KEYCONFIG_CATEGORY_CHARACTER;
		case key_config_category::COMMAND: return LOC_SYSTEM_KEYCONFIG_CATEGORY_COMMAND;
		case key_config_category::CONVENIENCE: return LOC_SYSTEM_KEYCONFIG_CATEGORY_CONVENIENCE;
		case key_config_category::ABILITY: return LOC_SYSTEM_KEYCONFIG_CATEGORY_ABILITY;
		case key_config_category::GAMEPAD: return LOC_SYSTEM_KEYCONFIG_CATEGORY_GAMEPAD;
		case key_config_category::MAP_SEARCH: return LOC_SYSTEM_KEYCONFIG_CATEGORY_MAP_SEARCH;
		case key_config_category::PROJECTILE: return LOC_SYSTEM_KEYCONFIG_CATEGORY_PROJECTILE;
		}
		return LOC_NONE;
	}

	std::vector<key_config_row> build_key_config_rows(const std::vector<key_binding_entry>& entries, bool gamepad)
	{
		std::vector<key_config_row> rows;
		const key_config_category categories[] = {
			key_config_category::MOVEMENT, key_config_category::DUNGEON, key_config_category::ITEM,
			key_config_category::ABILITY, key_config_category::MAGIC, key_config_category::CHARACTER,
			key_config_category::COMMAND, key_config_category::CONVENIENCE, key_config_category::GAMEPAD,
			key_config_category::MAP_SEARCH, key_config_category::PROJECTILE
		};
		bool first_category = true;
		for(key_config_category category : categories)
		{
			std::vector<int> indices;
			for(size_t i = 0; i < entries.size(); ++i)
				if(get_key_config_category(entries[i], gamepad) == category)
					indices.push_back(static_cast<int>(i));
			if(indices.empty())
				continue;
			if(!first_category)
				rows.push_back({});
			rows.push_back({-1, -1, get_key_config_category_label(category)});
			rows.push_back({});
			first_category = false;
			for(size_t i = 0; i < indices.size(); i += 2)
				rows.push_back({indices[i], i + 1 < indices.size() ? indices[i + 1] : -1, LOC_NONE});
		}
		return rows;
	}

	int find_key_config_row(const std::vector<key_config_row>& rows, size_t selected, int* column = nullptr)
	{
		for(size_t i = 0; i < rows.size(); ++i)
		{
			if(rows[i].left == static_cast<int>(selected))
			{
				if(column) *column = 0;
				return static_cast<int>(i);
			}
			if(rows[i].right == static_cast<int>(selected))
			{
				if(column) *column = 1;
				return static_cast<int>(i);
			}
		}
		if(column) *column = 0;
		return 0;
	}

	bool move_key_config_selection(const std::vector<key_config_row>& rows, size_t& selected, int row_delta)
	{
		if(rows.empty() || row_delta == 0)
			return false;
		int column = 0;
		int row = find_key_config_row(rows, selected, &column);
		int direction = row_delta > 0 ? 1 : -1;
		int target = std::max(0, std::min(static_cast<int>(rows.size()) - 1, row + row_delta));
		for(int i = target; i >= 0 && i < static_cast<int>(rows.size()); i += direction)
		{
			int entry = column == 0 ? rows[i].left : rows[i].right;
			if(entry < 0)
				entry = column == 0 ? rows[i].right : rows[i].left;
			if(entry >= 0)
			{
				selected = static_cast<size_t>(entry);
				return true;
			}
		}
		return false;
	}

	void print_key_config_guide(bool gamepad, bool editing, bool reset_confirm, bool reset_all)
	{
		const bool prompt_gamepad = joypadUtil::isUsingPad();
		if(editing)
		{
			if(gamepad)
				printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_CAPTURE_GAMEPAD,
					PlaceHolderHelper(key_config_pad_button(GVK_START))), true, CL_green);
			else
				printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_CAPTURE_KEYBOARD), true, CL_green);
			printsub("", true, CL_normal);
			return;
		}
		if(reset_confirm)
		{
			printsub(LocalzationManager::locString(reset_all ? LOC_SYSTEM_KEYCONFIG_RESET_ALL_CONFIRM : LOC_SYSTEM_KEYCONFIG_RESET_CONFIRM), false, CL_danger);
			printsub(" (", false, CL_danger);
			if(prompt_gamepad)
			{
				printsub(key_config_pad_button(GVK_BUTTON_A), false, CL_danger, KEYCONFIG_RESET_YES);
				printsub("/", false, CL_danger);
				printsub(key_config_pad_button(GVK_BUTTON_B), false, CL_danger, KEYCONFIG_RESET_NO);
			}
			else
			{
				printsub("Y", false, CL_danger, KEYCONFIG_RESET_YES);
				printsub("/", false, CL_danger);
				printsub("N", false, CL_danger, KEYCONFIG_RESET_NO);
			}
			printsub(")", true, CL_danger);
			printsub("", true, CL_normal);
			return;
		}

		if(prompt_gamepad)
		{
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_MOVE,
				PlaceHolderHelper(key_config_pad_button(GVK_BUTTON_A))), false, CL_normal);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_ADD,
				PlaceHolderHelper(key_config_pad_button(GVK_LEFT_BUMPER))), false, CL_normal, KEYCONFIG_ADD);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_CLEAR,
				PlaceHolderHelper(key_config_pad_button(GVK_BUTTON_X))), true, CL_normal, KEYCONFIG_CLEAR);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_RESET,
				PlaceHolderHelper(key_config_pad_button(GVK_BUTTON_Y))), false, CL_normal, KEYCONFIG_RESET);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_RESET_ALL,
				PlaceHolderHelper(key_config_pad_button(GVK_RIGHT_BUMPER))), false, CL_normal, KEYCONFIG_RESET_ALL);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_FILE,
				PlaceHolderHelper(key_config_pad_button(GVK_BACK))), false, CL_normal, KEYCONFIG_OPEN_FILE);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_GUIDE_PAD_BACK,
				PlaceHolderHelper(key_config_pad_button(GVK_BUTTON_B))), true, CL_normal, KEYCONFIG_BACK);
		}
		else
		{
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_MOVE), false, CL_normal);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_ADD), false, CL_normal, KEYCONFIG_ADD);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_CLEAR), true, CL_normal, KEYCONFIG_CLEAR);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_RESET), false, CL_normal, KEYCONFIG_RESET);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_RESET_ALL), false, CL_normal, KEYCONFIG_RESET_ALL);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_FILE), false, CL_normal, KEYCONFIG_OPEN_FILE);
			printsub("  ", false, CL_normal);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_GUIDE_KEYBOARD_BACK), true, CL_normal, KEYCONFIG_BACK);
		}
	}

	void print_key_config_cell(const key_binding_entry& entry, size_t index, bool selected, bool editing,
		bool conflict, bool submenu_conflict, int label_width, int column_width, bool enter)
	{
		int clickable = KEYCONFIG_ENTRY_BASE + static_cast<int>(index);
		std::string label = keybind_mg.entry_name(entry);
		std::string prefix = (selected ? "> " : "  ") + label;
		prefix += std::string(std::max(0, label_width - PrintCharWidth(label)), ' ') + " : ";
		printsub(prefix, false, editing ? CL_green : CL_normal, clickable);
		int width = PrintCharWidth(prefix);
		if(!editing)
		{
			if(entry.keys.empty())
			{
				printsub("NONE", false, conflict ? CL_danger : (submenu_conflict ? CL_small_danger : D3DCOLOR_RGBA(240, 200, 100, 255)), clickable);
				width += PrintCharWidth("NONE");
			}
			else
			{
				for(size_t i = 0; i < entry.keys.size(); ++i)
				{
					if(i > 0)
					{
						printsub(" / ", false, CL_normal, clickable);
						width += PrintCharWidth(" / ");
					}
					std::string name = keybind_mg.key_name(entry.keys[i]);
					printsub(name, false, conflict ? CL_danger : (submenu_conflict ? CL_small_danger : D3DCOLOR_RGBA(240, 200, 100, 255)), clickable);
					width += PrintCharWidth(name);
				}
			}
		}
		if(enter)
			printsub("", true, CL_normal);
		else
			printsub(std::string(std::max(1, column_width - width), ' '), false, CL_normal);
	}

	void print_key_config_scroll(bool up, bool visible)
	{
		if(!visible)
		{
			printsub("", true, CL_normal);
			return;
		}
		int font_width = std::max(1, static_cast<int>(DisplayManager.fontDesc.Width));
		int center = std::max(0, static_cast<int>(option_mg.getWidth() / font_width / 2 - 1));
		printsub(std::string(center, ' '), false, CL_normal);
		printsub(up ? "↑" : "↓", true, CL_normal, up ? KEYCONFIG_SCROLL_UP : KEYCONFIG_SCROLL_DOWN);
	}

	void render_key_config(bool gamepad, size_t selected, bool editing = false, bool reset_confirm = false, bool reset_all = false)
	{
		const auto& entries = keybind_mg.bindings(gamepad);
		std::vector<key_config_row> rows = build_key_config_rows(entries, gamepad);
		int selected_row = find_key_config_row(rows, selected);
		WaitForSingleObject(mutx, INFINITE);
		deletesub(false);
		printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_TITLE), true, CL_normal);
		print_key_config_guide(gamepad, editing, reset_confirm, reset_all);

		int page_rows = key_config_page_rows();
		int page_start = rows.empty() ? 0 : (selected_row / page_rows) * page_rows;
		int page_end = std::min(static_cast<int>(rows.size()), page_start + page_rows);
		bool conflict = !editing && !reset_confirm && selected < entries.size() && keybind_mg.has_conflict(gamepad, selected);
		bool submenu_conflict = !conflict && !editing && !reset_confirm && selected < entries.size() &&
			keybind_mg.has_submenu_conflict(gamepad, selected);
		if(conflict)
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_CONFLICT_WARNING), true, CL_danger);
		else if(submenu_conflict)
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_SUBMENU_CONFLICT_WARNING), true, CL_small_danger);
		else
			print_key_config_scroll(true, page_start > 0);

		int label_width = 0;
		for(const auto& entry : entries)
			label_width = std::max(label_width, PrintCharWidth(keybind_mg.entry_name(entry)));
		int column_width = key_config_column_width();
		int clickable_before_selected = editing ? 0 : 6;
		if(page_start > 0 && !conflict && !submenu_conflict)
			++clickable_before_selected;
		for(int row = 0; row < page_rows; ++row)
		{
			int layout_index = page_start + row;
			if(layout_index >= page_end)
			{
				printsub("", true, CL_normal);
				continue;
			}
			const key_config_row& layout_row = rows[layout_index];
			if(layout_row.heading != LOC_NONE)
			{
				// Match the §b category headings used by help.txt.
				printsub(LocalzationManager::locString(layout_row.heading), true,
					D3DCOLOR_RGBA(80, 80, 240, 255));
				continue;
			}
			if(layout_row.left < 0 && layout_row.right < 0)
			{
				printsub("", true, CL_normal);
				continue;
			}
			for(int column = 0; column < 2; ++column)
			{
				int entry_index = column == 0 ? layout_row.left : layout_row.right;
				if(entry_index < 0)
				{
					printsub("", true, CL_normal);
					break;
				}
				if(static_cast<size_t>(entry_index) == selected)
					clickable_before_selected += column;
				else if(layout_index < selected_row)
					++clickable_before_selected;
				print_key_config_cell(entries[entry_index], static_cast<size_t>(entry_index),
					static_cast<size_t>(entry_index) == selected, editing && static_cast<size_t>(entry_index) == selected,
					keybind_mg.has_conflict(gamepad, static_cast<size_t>(entry_index)),
					keybind_mg.has_submenu_conflict(gamepad, static_cast<size_t>(entry_index)),
					label_width, column_width, column == 1);
			}
		}
		print_key_config_scroll(false, page_end < static_cast<int>(rows.size()));
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
		DisplayManager.current_position = reset_confirm ? 0 : clickable_before_selected;
	}

	bool confirm_key_config_reset(bool gamepad, size_t selected, bool reset_all)
	{
		int choice = 0;
		while(true)
		{
			render_key_config(gamepad, selected, false, true, reset_all);
			DisplayManager.current_position = choice;
			InputedKey inputed;
			int key = waitkeyinput(inputed, true, false, false, false, true);
			if(key == KEYCONFIG_RESET_YES || key == 'Y' || key == 'y')
				return true;
			if(key == KEYCONFIG_RESET_NO || key == 'N' || key == 'n' || key == VK_ESCAPE ||
				key == GVK_BUTTON_B || key == GVK_BUTTON_B_LONG || (key == -1 && inputed.isRightClick()))
				return false;
			if(key == VK_LEFT || key == VK_UP)
				choice = 0;
			else if(key == VK_RIGHT || key == VK_DOWN || key == VK_TAB)
				choice = 1;
			else if(key == VK_RETURN || key == GVK_BUTTON_A)
				return choice == 0;
		}
	}

	void render_macro_capture(LOCALIZATION_ENUM_KEY message, bool show_list = false)
	{
		WaitForSingleObject(mutx, INFINITE);
		deletesub(false);
		printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MACRO_TITLE), true, CL_normal);
		printsub(LocalzationManager::locString(message), true, CL_normal);
		if(show_list)
		{
			printsub("", true, CL_normal);
			const auto& macros = keybind_mg.get_macros();
			if(macros.empty())
				printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MACRO_NONE), true, CL_normal);
			else
				for(const auto& macro : macros)
					printsub(keybind_mg.key_name(macro.first) + " => " + keybind_mg.sequence_name(macro.second), true, CL_STAT);
		}
		ReleaseMutex(mutx);
		changedisplay(DT_SUB_TEXT);
	}

	bool capture_macro_sequence(std::vector<int>& sequence)
	{
		sequence.clear();
		while(true)
		{
			render_macro_capture(LOC_SYSTEM_KEYCONFIG_MACRO_SEQUENCE);
			WaitForSingleObject(mutx, INFINITE);
			printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MACRO_SEQUENCE_GUIDE), true, CL_normal);
			printsub(keybind_mg.sequence_name(sequence), true, CL_STAT);
			ReleaseMutex(mutx);

			InputedKey inputed;
			int key = waitkeyinput(inputed, true, false, false, false, true);
			key = macro_capture_key(key, inputed);
			if(key == VK_ESCAPE || key == GVK_BUTTON_B || key == GVK_BUTTON_B_LONG)
				return false;
			if(key == VK_RETURN || key == GVK_BUTTON_A)
				return !sequence.empty();
			if(key == VK_BACK)
			{
				if(!sequence.empty())
					sequence.pop_back();
				continue;
			}
			if(key != -1 && sequence.size() < 128)
				sequence.push_back(key);
		}
	}

	void render_existing_macro(int trigger, const std::vector<int>& sequence)
	{
		render_macro_capture(LOC_SYSTEM_KEYCONFIG_MACRO_CURRENT);
		WaitForSingleObject(mutx, INFINITE);
		printsub(keybind_mg.key_name(trigger) + " => " + keybind_mg.sequence_name(sequence), true, CL_STAT);
		printsub(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MACRO_EXISTING_GUIDE), true, CL_normal);
		ReleaseMutex(mutx);
	}
}

void key_binding_manager::init_defaults()
{
	keyboard_bindings.clear();
	gamepad_bindings.clear();

	add_keyboard(keyboard_bindings, "MOVE_N", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_N, 'k', 'k');
	add_keyboard(keyboard_bindings, "MOVE_S", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_S, 'j', 'j');
	add_keyboard(keyboard_bindings, "MOVE_W", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_W, 'h', 'h');
	add_keyboard(keyboard_bindings, "MOVE_E", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_E, 'l', 'l');
	add_keyboard(keyboard_bindings, "MOVE_SW", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_SW, 'b', 'b');
	add_keyboard(keyboard_bindings, "MOVE_SE", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_SE, 'n', 'n');
	add_keyboard(keyboard_bindings, "MOVE_NW", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_NW, 'y', 'y');
	add_keyboard(keyboard_bindings, "MOVE_NE", LOC_SYSTEM_KEYCONFIG_ACTION_MOVE_NE, 'u', 'u');
	add_keyboard(keyboard_bindings, "RUN_N", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_N, 'K', 'K');
	add_keyboard(keyboard_bindings, "RUN_S", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_S, 'J', 'J');
	add_keyboard(keyboard_bindings, "RUN_W", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_W, 'H', 'H');
	add_keyboard(keyboard_bindings, "RUN_E", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_E, 'L', 'L');
	add_keyboard(keyboard_bindings, "RUN_SW", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_SW, 'B', 'B');
	add_keyboard(keyboard_bindings, "RUN_SE", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_SE, 'N', 'N');
	add_keyboard(keyboard_bindings, "RUN_NW", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_NW, 'Y', 'Y');
	add_keyboard(keyboard_bindings, "RUN_NE", LOC_SYSTEM_KEYCONFIG_ACTION_RUN_NE, 'U', 'U');
	add_keyboard(keyboard_bindings, "AUTO_TRAVEL", LOC_SYSTEM_KEYCONFIG_ACTION_AUTO_TRAVEL, 'o', 'o');

	add_keyboard(keyboard_bindings, "LONG_REST", LOC_SYSTEM_KEYCONFIG_ACTION_LONG_REST, '5', '5');
	add_keyboard(keyboard_bindings, "SEARCH", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH, 'x', 'x');
	add_keyboard(keyboard_bindings, "WAIT", LOC_SYSTEM_KEYCONFIG_ACTION_WAIT, '.', {'.', 's'});
	add_keyboard(keyboard_bindings, "WIDE_SEARCH", LOC_SYSTEM_KEYCONFIG_ACTION_WIDE_SEARCH, 'X', 'X');
	add_keyboard(keyboard_bindings, "STAIRS_UP", LOC_SYSTEM_KEYCONFIG_ACTION_STAIRS_UP, '<', '<');
	add_keyboard(keyboard_bindings, "STAIRS_DOWN", LOC_SYSTEM_KEYCONFIG_ACTION_STAIRS_DOWN, '>', '>');
	add_keyboard(keyboard_bindings, "OPEN_DOOR", LOC_SYSTEM_KEYCONFIG_ACTION_OPEN_DOOR, 'O', 'O');
	add_keyboard(keyboard_bindings, "CLOSE_DOOR", LOC_SYSTEM_KEYCONFIG_ACTION_CLOSE_DOOR, 'C', 'C');
	add_keyboard(keyboard_bindings, "FLOOR_TRAVEL", LOC_SYSTEM_KEYCONFIG_ACTION_FLOOR_TRAVEL, 'G', {'G', 0x07});
	add_keyboard(keyboard_bindings, "AUTO_ATTACK", LOC_SYSTEM_KEYCONFIG_ACTION_AUTO_ATTACK, VK_TAB, VK_TAB);

	add_keyboard(keyboard_bindings, "INVENTORY", LOC_SYSTEM_KEYCONFIG_ACTION_INVENTORY, 'i', 'i');
	add_keyboard(keyboard_bindings, "PICKUP", LOC_SYSTEM_KEYCONFIG_ACTION_PICKUP, ',', {',', 'g'});
	add_keyboard(keyboard_bindings, "DROP", LOC_SYSTEM_KEYCONFIG_ACTION_DROP, 'd', 'd');
	add_keyboard(keyboard_bindings, "DROP_LAST", LOC_SYSTEM_KEYCONFIG_ACTION_DROP_LAST, 'D', 'D');
	add_keyboard(keyboard_bindings, "EAT", LOC_SYSTEM_KEYCONFIG_ACTION_EAT, 'e', 'e');
	add_keyboard(keyboard_bindings, "READ", LOC_SYSTEM_KEYCONFIG_ACTION_READ, 'r', 'r');
	add_keyboard(keyboard_bindings, "DRINK", LOC_SYSTEM_KEYCONFIG_ACTION_DRINK, 'q', 'q');
	add_keyboard(keyboard_bindings, "QUICK_THROW", LOC_SYSTEM_KEYCONFIG_ACTION_QUICK_THROW, 'f', 'f');
	add_keyboard(keyboard_bindings, "SELECT_THROW", LOC_SYSTEM_KEYCONFIG_ACTION_SELECT_THROW, 'F', 'F');
	add_keyboard(keyboard_bindings, "EVOKE", LOC_SYSTEM_KEYCONFIG_ACTION_EVOKE, 'v', 'v');
	add_keyboard(keyboard_bindings, "EVOKE_SPELLCARD", LOC_SYSTEM_KEYCONFIG_ACTION_EVOKE_MENU, 'V', 'V');
	add_keyboard(keyboard_bindings, "WIELD", LOC_SYSTEM_KEYCONFIG_ACTION_WIELD, 'w', 'w');
	add_keyboard(keyboard_bindings, "WEAR_ARMOUR", LOC_SYSTEM_KEYCONFIG_ACTION_WEAR_ARMOUR, 'W', 'W');
	add_keyboard(keyboard_bindings, "REMOVE_ARMOUR", LOC_SYSTEM_KEYCONFIG_ACTION_REMOVE_ARMOUR, 'T', 'T');
	add_keyboard(keyboard_bindings, "WEAR_JEWELRY", LOC_SYSTEM_KEYCONFIG_ACTION_WEAR_JEWELRY, 'P', 'P');
	add_keyboard(keyboard_bindings, "REMOVE_JEWELRY", LOC_SYSTEM_KEYCONFIG_ACTION_REMOVE_JEWELRY, 'R', 'R');
	add_keyboard(keyboard_bindings, "SWAP_WEAPON", LOC_SYSTEM_KEYCONFIG_ACTION_SWAP_WEAPON, '\'', '\'');
	add_keyboard(keyboard_bindings, "AUTO_PICKUP", LOC_SYSTEM_KEYCONFIG_ACTION_AUTO_PICKUP, 0x8B, 0x8B);
	add_keyboard(keyboard_bindings, "FIND_ITEM", LOC_SYSTEM_KEYCONFIG_ACTION_FIND_ITEM, 0x06, 0x06);

	add_keyboard(keyboard_bindings, "PRAY", LOC_SYSTEM_KEYCONFIG_ACTION_PRAY, 'p', 'p');
	add_keyboard(keyboard_bindings, "ABILITY", LOC_SYSTEM_KEYCONFIG_ACTION_ABILITY, 'a', 'a');
	add_keyboard(keyboard_bindings, "SHOUT", LOC_SYSTEM_KEYCONFIG_ACTION_SHOUT, 't', 't');

	add_keyboard(keyboard_bindings, "MEMORIZED_SPELLS", LOC_SYSTEM_KEYCONFIG_ACTION_MEMORIZE_SPELLS, 'M', 'M');
	add_keyboard(keyboard_bindings, "QUICK_CAST", LOC_SYSTEM_KEYCONFIG_ACTION_QUICK_CAST, 'z', 'z');
	add_keyboard(keyboard_bindings, "CAST", LOC_SYSTEM_KEYCONFIG_ACTION_CAST, 'Z', 'Z');
	add_keyboard(keyboard_bindings, "SPELL_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_SPELL_INFO, 'I', 'I');

	add_keyboard(keyboard_bindings, "STATE_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_STATE_INFO, '@', '@');
	add_keyboard(keyboard_bindings, "CHARACTER_STATS", LOC_SYSTEM_KEYCONFIG_ACTION_CHARACTER_STATS, '%', '%');
	add_keyboard(keyboard_bindings, "GOD_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_GOD_INFO, '^', '^');
	add_keyboard(keyboard_bindings, "IDENTIFIED_ITEMS", LOC_SYSTEM_KEYCONFIG_ACTION_IDENTIFIED_ITEMS, '\\', '\\');
	add_keyboard(keyboard_bindings, "PROPERTY", LOC_SYSTEM_KEYCONFIG_ACTION_PROPERTY, 'A', 'A');
	add_keyboard(keyboard_bindings, "ARMOUR_LIST", LOC_SYSTEM_KEYCONFIG_ACTION_ARMOUR_LIST, '[', '[');
	add_keyboard(keyboard_bindings, "WEAPON_LIST", LOC_SYSTEM_KEYCONFIG_ACTION_WEAPON_LIST, '}', '}');
	add_keyboard(keyboard_bindings, "AMULET_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_AMULET_INFO, '"', '"');
	add_keyboard(keyboard_bindings, "EXPERIENCE_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_EXPERIENCE_INFO, 'E', 'E');
	add_keyboard(keyboard_bindings, "SKILL_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_SKILL_INFO, 'm', 'm');
	add_keyboard(keyboard_bindings, "RUNE_LIST", LOC_SYSTEM_KEYCONFIG_ACTION_RUNE_LIST, ']', ']');
	add_keyboard(keyboard_bindings, "DUNGEON_MAP", LOC_SYSTEM_KEYCONFIG_ACTION_DUNGEON_PROGRESS, 15, 15);

	add_keyboard(keyboard_bindings, "MESSAGE_LOG", LOC_SYSTEM_KEYCONFIG_ACTION_MESSAGE_LOG, 0x88, 0x88);
	add_keyboard(keyboard_bindings, "SAVE_CHECK", LOC_SYSTEM_KEYCONFIG_ACTION_SAVE_CHECK, 'S', 'S');
	add_keyboard(keyboard_bindings, "SAVE_QUIT", LOC_SYSTEM_KEYCONFIG_ACTION_SAVE_QUIT, 0x8A, 0x8A);
	add_keyboard(keyboard_bindings, "QUIT_NOSAVE", LOC_SYSTEM_KEYCONFIG_ACTION_QUIT_NOSAVE, 0x89, 0x89);
	add_keyboard(keyboard_bindings, "DUMP", LOC_SYSTEM_KEYCONFIG_ACTION_DUMP, '#', '#');
	add_keyboard(keyboard_bindings, "ZOOM_IN", LOC_SYSTEM_KEYCONFIG_ACTION_ZOOM_IN, '+', '+');
	add_keyboard(keyboard_bindings, "ZOOM_OUT", LOC_SYSTEM_KEYCONFIG_ACTION_ZOOM_OUT, '-', '-');
	add_keyboard(keyboard_bindings, "WIZARD", LOC_SYSTEM_KEYCONFIG_ACTION_WIZARD, '&', '&');
	add_keyboard(keyboard_bindings, "HELP", LOC_SYSTEM_KEYCONFIG_ACTION_HELP, '?', '?');
	add_keyboard(keyboard_bindings, "ESCAPE", LOC_SYSTEM_KEYCONFIG_ACTION_OPEN_MENU, VK_ESCAPE, VK_ESCAPE);

	add_keyboard(keyboard_bindings, "REPEAT", LOC_SYSTEM_KEYCONFIG_ACTION_REPEAT, '`', '`');
	add_keyboard(keyboard_bindings, "MACRO", LOC_SYSTEM_KEYCONFIG_ACTION_MACRO, '~', '~');

	add_gamepad(gamepad_bindings, "PAD_CONFIRM", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_CONFIRM, GVK_BUTTON_A, GVK_BUTTON_A);
	add_gamepad(gamepad_bindings, "PAD_LONG_REST", LOC_SYSTEM_KEYCONFIG_ACTION_LONG_REST, GVK_BUTTON_A_LONG, GVK_BUTTON_A_LONG);
	add_gamepad(gamepad_bindings, "PAD_CANCEL", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_CANCEL, GVK_BUTTON_B, GVK_BUTTON_B);
	add_gamepad(gamepad_bindings, "PAD_WIDE_SEARCH", LOC_SYSTEM_KEYCONFIG_ACTION_WIDE_SEARCH, GVK_BUTTON_B_LONG, GVK_BUTTON_B_LONG);
	add_gamepad(gamepad_bindings, "PAD_QUICK_1", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_QUICK_1, GVK_BUTTON_X, GVK_BUTTON_X);
	add_gamepad(gamepad_bindings, "PAD_QUICK_2", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_QUICK_2, GVK_BUTTON_X_LONG, GVK_BUTTON_X_LONG);
	add_gamepad(gamepad_bindings, "PAD_RIGHT_MENU", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_RIGHT_MENU, GVK_BUTTON_Y, GVK_BUTTON_Y);
	add_gamepad(gamepad_bindings, "PAD_INVENTORY", LOC_SYSTEM_KEYCONFIG_ACTION_INVENTORY, GVK_BUTTON_Y_LONG, GVK_BUTTON_Y_LONG);
	add_gamepad(gamepad_bindings, "PAD_AUTO_ATTACK", LOC_SYSTEM_KEYCONFIG_ACTION_AUTO_ATTACK, GVK_LEFT_BUMPER, GVK_LEFT_BUMPER);
	add_gamepad(gamepad_bindings, "PAD_AUTO_TRAVEL", LOC_SYSTEM_KEYCONFIG_ACTION_AUTO_TRAVEL, GVK_RIGHT_BUMPER, GVK_RIGHT_BUMPER);
	add_gamepad(gamepad_bindings, "PAD_ZOOM_OUT", LOC_SYSTEM_KEYCONFIG_ACTION_ZOOM_OUT, GVK_LT, GVK_LT);
	add_gamepad(gamepad_bindings, "PAD_ZOOM_IN", LOC_SYSTEM_KEYCONFIG_ACTION_ZOOM_IN, GVK_RT, GVK_RT);
	add_gamepad(gamepad_bindings, "PAD_DASH_MODIFIER", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_DASH,
		GVK_BUTTON_B, {GVK_BUTTON_B}, KEY_INPUT_DASH_MODIFIER);

	add_gamepad(gamepad_bindings, "PAD_SEARCH_CONFIRM", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH_CONFIRM,
		GVK_BUTTON_A, {GVK_BUTTON_A}, KEY_INPUT_MAP_SEARCH);
	add_gamepad(gamepad_bindings, "PAD_SEARCH_INSPECT", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH_INSPECT,
		GVK_BUTTON_A_LONG, {GVK_BUTTON_A_LONG}, KEY_INPUT_MAP_SEARCH);
	add_gamepad(gamepad_bindings, "PAD_SEARCH_FORBID", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH_FORBID,
		GVK_BUTTON_X, {GVK_BUTTON_X}, KEY_INPUT_MAP_SEARCH);
	add_gamepad(gamepad_bindings, "PAD_SEARCH_PREV_STAIR", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH_PREV_STAIR,
		GVK_LEFT_BUMPER, {GVK_LEFT_BUMPER}, KEY_INPUT_MAP_SEARCH);
	add_gamepad(gamepad_bindings, "PAD_SEARCH_NEXT_STAIR", LOC_SYSTEM_KEYCONFIG_ACTION_SEARCH_NEXT_STAIR,
		GVK_RIGHT_BUMPER, {GVK_RIGHT_BUMPER}, KEY_INPUT_MAP_SEARCH);
	add_gamepad(gamepad_bindings, "PAD_SEARCH_CANCEL", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_CANCEL,
		GVK_BUTTON_B, {GVK_BUTTON_B, GVK_BUTTON_B_LONG}, KEY_INPUT_MAP_SEARCH);

	add_gamepad(gamepad_bindings, "PAD_TARGET_CONFIRM", LOC_SYSTEM_KEYCONFIG_ACTION_TARGET_CONFIRM,
		GVK_BUTTON_A, {GVK_BUTTON_A}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_TARGET_CURSOR", LOC_SYSTEM_KEYCONFIG_ACTION_TARGET_CURSOR,
		GVK_BUTTON_X, {GVK_BUTTON_X}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_TARGET_INSPECT", LOC_SYSTEM_KEYCONFIG_ACTION_TARGET_INSPECT,
		GVK_BUTTON_A_LONG, {GVK_BUTTON_A_LONG}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_TARGET_PREV", LOC_SYSTEM_KEYCONFIG_ACTION_TARGET_PREV,
		GVK_LT, {GVK_LT}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_TARGET_NEXT", LOC_SYSTEM_KEYCONFIG_ACTION_TARGET_NEXT,
		GVK_RT, {GVK_RT}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_THROW_PREV", LOC_SYSTEM_KEYCONFIG_ACTION_THROW_PREV,
		GVK_LEFT_BUMPER, {GVK_LEFT_BUMPER}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_THROW_NEXT", LOC_SYSTEM_KEYCONFIG_ACTION_THROW_NEXT,
		GVK_RIGHT_BUMPER, {GVK_RIGHT_BUMPER}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_THROW_INFO", LOC_SYSTEM_KEYCONFIG_ACTION_THROW_INFO,
		GVK_BUTTON_Y, {GVK_BUTTON_Y}, KEY_INPUT_PROJECTILE);
	add_gamepad(gamepad_bindings, "PAD_TARGET_CANCEL", LOC_SYSTEM_KEYCONFIG_ACTION_PAD_CANCEL,
		GVK_BUTTON_B, {GVK_BUTTON_B, GVK_BUTTON_B_LONG}, KEY_INPUT_PROJECTILE);
}

void key_binding_manager::init(const std::filesystem::path& directory)
{
	file_path = directory.empty() ? std::filesystem::path(L"keybindings.txt") : directory / L"keybindings.txt";
	init_defaults();
	load();
}

bool key_binding_manager::load()
{
	init_defaults();
	macros.clear();
	macro_buffer.clear();
	std::ifstream input(file_path);
	if(!input)
	{
		rebuild_lookup();
		return save();
	}

	enum class section_type { NONE, KEYBOARD, GAMEPAD, MACROS } section = section_type::NONE;
	std::string line;
	while(std::getline(input, line))
	{
		line = trim_copy(line);
		if(line.empty() || ((line[0] == '#' || line[0] == ';') && line.find('=') == std::string::npos))
			continue;
		if(line.front() == '[' && line.back() == ']')
		{
			std::string name = upper_copy(trim_copy(line.substr(1, line.size() - 2)));
			section = name == "KEYBOARD" ? section_type::KEYBOARD : name == "GAMEPAD" ? section_type::GAMEPAD : name == "MACROS" ? section_type::MACROS : section_type::NONE;
			continue;
		}

		size_t equal = line.find('=');
		if(equal == std::string::npos)
			continue;
		std::string id = trim_copy(line.substr(0, equal));
		std::string value = trim_copy(line.substr(equal + 1));
		if(section == section_type::KEYBOARD || section == section_type::GAMEPAD)
		{
			auto& entries = section == section_type::GAMEPAD ? gamepad_bindings : keyboard_bindings;
			std::string binding_id = upper_copy(id);
			bool legacy_secondary = false;
			if(section == section_type::KEYBOARD)
			{
				if(binding_id == "WAIT_ALT") { binding_id = "WAIT"; legacy_secondary = true; }
				else if(binding_id == "PICKUP_ALT") { binding_id = "PICKUP"; legacy_secondary = true; }
				else if(binding_id == "FLOOR_TRAVEL_ALT") { binding_id = "FLOOR_TRAVEL"; legacy_secondary = true; }
			}
			for(auto& entry : entries)
			{
				if(entry.id == binding_id)
				{
					std::vector<int> parsed_keys;
					std::istringstream values(value);
					std::string key_text;
					while(values >> key_text)
					{
						int parsed = parse_key_name(key_text);
						bool valid_device_key = section == section_type::GAMEPAD ? is_gamepad_key(parsed) : !is_gamepad_key(parsed);
						if(parsed > 0 && valid_device_key && !is_fixed_binding_key(parsed) &&
							std::find(parsed_keys.begin(), parsed_keys.end(), parsed) == parsed_keys.end())
							parsed_keys.push_back(parsed);
					}
					if(upper_copy(value) == "NONE")
						parsed_keys.clear();
					if(legacy_secondary)
					{
						for(int parsed : parsed_keys)
							if(std::find(entry.keys.begin(), entry.keys.end(), parsed) == entry.keys.end())
								entry.keys.push_back(parsed);
					}
					else if(!parsed_keys.empty() || upper_copy(value) == "NONE")
						entry.keys = parsed_keys;
					break;
				}
			}
		}
		else if(section == section_type::MACROS)
		{
			int trigger = parse_key_name(id);
			std::vector<int> sequence = parse_sequence(value);
			if(trigger > 0 && !sequence.empty() && !is_fixed_binding_key(trigger))
				macros[trigger] = sequence;
		}
	}
	rebuild_lookup();
	return true;
}

bool key_binding_manager::save() const
{
	enum class section_type { NONE, KEYBOARD, GAMEPAD, MACROS };
	std::vector<std::string> source_lines;
	std::ifstream input(file_path);
	if(input)
	{
		std::string line;
		while(std::getline(input, line))
			source_lines.push_back(line);
	}
	else if(std::filesystem::exists(file_path))
		return false;
	else
	{
		source_lines.push_back(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_FILE_HEADER));
		source_lines.push_back(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_FILE_BINDING_HELP));
		source_lines.push_back(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_FILE_MACRO_HELP));
		source_lines.push_back("");
		source_lines.push_back(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_FILE_MACRO_COMMAND_HELP));
	}

	std::map<std::string, std::string> keyboard_values;
	std::map<std::string, std::string> gamepad_values;
	for(const auto& entry : keyboard_bindings)
		keyboard_values[entry.id] = binding_name(entry, " ");
	for(const auto& entry : gamepad_bindings)
		gamepad_values[entry.id] = binding_name(entry, " ");
	std::map<int, std::string> macro_values;
	for(const auto& macro : macros)
		macro_values[macro.first] = sequence_name(macro.second);

	std::set<std::string> found_keyboard;
	std::set<std::string> found_gamepad;
	std::set<int> found_macros;
	std::vector<std::string> output_lines;
	section_type section = section_type::NONE;
	auto get_section = [](const std::string& line)
	{
		std::string trimmed_line = trim_copy(line);
		if(trimmed_line.empty() || trimmed_line.front() != '[' || trimmed_line.back() != ']')
			return section_type::NONE;
		std::string name = upper_copy(trim_copy(trimmed_line.substr(1, trimmed_line.size() - 2)));
		return name == "KEYBOARD" ? section_type::KEYBOARD :
			name == "GAMEPAD" ? section_type::GAMEPAD :
			name == "MACROS" ? section_type::MACROS : section_type::NONE;
	};
	for(const std::string& original_line : source_lines)
	{
		std::string trimmed = trim_copy(original_line);
		if(!trimmed.empty() && trimmed.front() == '[' && trimmed.back() == ']')
		{
			section_type new_section = get_section(original_line);
			// Repeating the same section changes no parsing state and only bloats the file.
			if(new_section != section_type::NONE && new_section == section)
				continue;
			section = new_section;
			output_lines.push_back(original_line);
			continue;
		}
		if(trimmed.empty() || ((trimmed[0] == '#' || trimmed[0] == ';') && trimmed.find('=') == std::string::npos))
		{
			output_lines.push_back(original_line);
			continue;
		}

		size_t equal = original_line.find('=');
		if(equal == std::string::npos)
		{
			output_lines.push_back(original_line);
			continue;
		}
		std::string id = upper_copy(trim_copy(original_line.substr(0, equal)));
		std::string desired;
		bool update_line = false;
		bool remove_line = false;
		if(section == section_type::KEYBOARD)
		{
			auto found = keyboard_values.find(id);
			if(found != keyboard_values.end())
			{
				desired = found->second;
				found_keyboard.insert(id);
				update_line = true;
			}
		}
		else if(section == section_type::GAMEPAD)
		{
			auto found = gamepad_values.find(id);
			if(found != gamepad_values.end())
			{
				desired = found->second;
				found_gamepad.insert(id);
				update_line = true;
			}
		}
		else if(section == section_type::MACROS)
		{
			int trigger = parse_key_name(trim_copy(original_line.substr(0, equal)));
			if(trigger > 0)
			{
				auto found = macro_values.find(trigger);
				if(found == macro_values.end())
					remove_line = true;
				else
				{
					desired = found->second;
					found_macros.insert(trigger);
					update_line = true;
				}
			}
		}
		if(remove_line)
			continue;
		if(update_line && trim_copy(original_line.substr(equal + 1)) != desired)
		{
			size_t value_start = equal + 1;
			while(value_start < original_line.size() &&
				(original_line[value_start] == ' ' || original_line[value_start] == '\t'))
				++value_start;
			output_lines.push_back(original_line.substr(0, value_start) + desired);
		}
		else
			output_lines.push_back(original_line);
	}

	auto insert_section_lines = [&output_lines, &get_section](section_type target,
		const std::string& name, const std::vector<std::string>& lines)
	{
		if(lines.empty())
			return;
		section_type current = section_type::NONE;
		size_t insert_at = std::string::npos;
		for(size_t i = 0; i < output_lines.size(); ++i)
		{
			std::string trimmed_line = trim_copy(output_lines[i]);
			bool is_section_header = !trimmed_line.empty() &&
				trimmed_line.front() == '[' && trimmed_line.back() == ']';
			if(is_section_header)
			{
				if(current == target)
					insert_at = i;
				current = get_section(output_lines[i]);
				if(current == target)
					insert_at = i + 1;
			}
			else if(current == target)
				insert_at = i + 1;
		}
		if(insert_at == std::string::npos)
		{
			if(!output_lines.empty() && !output_lines.back().empty())
				output_lines.push_back("");
			output_lines.push_back(name);
			output_lines.insert(output_lines.end(), lines.begin(), lines.end());
		}
		else
			output_lines.insert(output_lines.begin() + insert_at, lines.begin(), lines.end());
	};
	std::vector<std::string> missing_keyboard_lines;
	for(const auto& entry : keyboard_bindings)
		if(found_keyboard.find(entry.id) == found_keyboard.end())
			missing_keyboard_lines.push_back(entry.id + '=' + binding_name(entry, " "));
	insert_section_lines(section_type::KEYBOARD, "[Keyboard]", missing_keyboard_lines);

	std::vector<std::string> missing_gamepad_lines;
	for(const auto& entry : gamepad_bindings)
		if(found_gamepad.find(entry.id) == found_gamepad.end())
			missing_gamepad_lines.push_back(entry.id + '=' + binding_name(entry, " "));
	insert_section_lines(section_type::GAMEPAD, "[Gamepad]", missing_gamepad_lines);

	std::vector<std::string> missing_macro_lines;
	for(const auto& value : macro_values)
		if(found_macros.find(value.first) == found_macros.end())
		{
			std::string trigger_name = key_name(value.first);
			if(trigger_name == "=")
				trigger_name = "KEY_61";
			missing_macro_lines.push_back(trigger_name + '=' + value.second);
		}
	insert_section_lines(section_type::MACROS, "[Macros]", missing_macro_lines);

	std::ofstream output(file_path, std::ios::trunc);
	if(!output)
		return false;
	for(const std::string& line : output_lines)
		output << line << '\n';
	return output.good();
}

void key_binding_manager::rebuild_lookup()
{
	keyboard_lookup.clear();
	gamepad_lookup.clear();
	for(const auto& entry : keyboard_bindings)
		for(int key : entry.keys)
			if(key > 0 && keyboard_lookup.find(key) == keyboard_lookup.end())
				keyboard_lookup[key] = entry.command_key;
	for(const auto& entry : gamepad_bindings)
	{
		if(entry.input_context != KEY_INPUT_DEFAULT)
			continue;
		for(int key : entry.keys)
			if(key > 0 && gamepad_lookup.find(key) == gamepad_lookup.end())
				gamepad_lookup[key] = entry.command_key;
	}
}

bool key_binding_manager::is_reserved_keyboard_key(int key) const
{
	for(const auto& entry : keyboard_bindings)
	{
		if(entry.command_key == key)
			return true;
		if(std::find(entry.default_keys.begin(), entry.default_keys.end(), key) != entry.default_keys.end())
			return true;
	}
	return false;
}

bool key_binding_manager::is_reserved_gamepad_key(int key) const
{
	for(const auto& entry : gamepad_bindings)
	{
		if(entry.input_context != KEY_INPUT_DEFAULT)
			continue;
		if(entry.command_key == key)
			return true;
		if(std::find(entry.default_keys.begin(), entry.default_keys.end(), key) != entry.default_keys.end())
			return true;
	}
	return false;
}

int key_binding_manager::process_input(int key, bool command_context, bool fixed_direction, bool raw_input, int movement_context)
{
	if(raw_input || key <= 0)
		return key;
	if(fixed_direction)
		return key;

	if(movement_context > KEY_INPUT_DEFAULT && !is_gamepad_key(key))
	{
		auto found = keyboard_lookup.find(key);
		if(found != keyboard_lookup.end())
		{
			if(is_step_movement_command(found->second))
				return found->second;
			if((movement_context == KEY_INPUT_LONG_MOVEMENT || movement_context == KEY_INPUT_MAP_SEARCH) &&
				is_long_movement_command(found->second))
				return found->second;
		}
		for(const auto& entry : keyboard_bindings)
		{
			if(!is_step_movement_command(entry.command_key) && !is_long_movement_command(entry.command_key))
				continue;
			if(entry.command_key == key || std::find(entry.default_keys.begin(), entry.default_keys.end(), key) != entry.default_keys.end())
				return KEY_UNBOUND_COMMAND;
		}
	}
	else if(is_gamepad_key(key) &&
		(movement_context == KEY_INPUT_MAP_SEARCH || movement_context == KEY_INPUT_PROJECTILE))
	{
		for(const auto& entry : gamepad_bindings)
			if(entry.input_context == movement_context &&
				std::find(entry.keys.begin(), entry.keys.end(), key) != entry.keys.end())
				return entry.command_key;
		for(const auto& entry : gamepad_bindings)
			if(entry.input_context == movement_context &&
				(entry.command_key == key || std::find(entry.default_keys.begin(), entry.default_keys.end(), key) != entry.default_keys.end()))
				return KEY_UNBOUND_COMMAND;
		return key;
	}

	if(command_context)
	{
		if(!is_gamepad_key(key))
		{
			auto binding = keyboard_lookup.find(key);
			if(binding != keyboard_lookup.end() && binding->second == '~')
				return '~';
		}
		auto macro = macros.find(key);
		if(macro != macros.end() && !macro->second.empty())
		{
			for(int macro_key : macro->second)
				macro_buffer.push_back(macro_key);
			int result = 0;
			pop_macro_input(result, false);
			return result;
		}
	}

	if(is_gamepad_key(key))
	{
		auto found = gamepad_lookup.find(key);
		if(found != gamepad_lookup.end())
			return found->second;
		return is_reserved_gamepad_key(key) ? KEY_UNBOUND_COMMAND : key;
	}
	if(!command_context)
		return key;
	auto found = keyboard_lookup.find(key);
	if(found != keyboard_lookup.end())
		return found->second;
	return is_reserved_keyboard_key(key) ? KEY_UNBOUND_COMMAND : key;
}

bool key_binding_manager::pop_macro_input(int& key, bool direction_context)
{
	if(macro_buffer.empty())
		return false;
	key = macro_buffer.front();
	macro_buffer.pop_front();
	if(is_virtual_key_code(key))
	{
		switch(get_virtual_key(key))
		{
		case VK_UP: key = direction_context ? VK_UP : 'k'; break;
		case VK_DOWN: key = direction_context ? VK_DOWN : 'j'; break;
		case VK_LEFT: key = direction_context ? VK_LEFT : 'h'; break;
		case VK_RIGHT: key = direction_context ? VK_RIGHT : 'l'; break;
		case VK_NUMPAD1: key = 'b'; break;
		case VK_NUMPAD3: key = 'n'; break;
		case VK_NUMPAD7: key = 'y'; break;
		case VK_NUMPAD9: key = 'u'; break;
		default: break;
		}
	}
	return true;
}

void key_binding_manager::clear_macro_buffer()
{
	macro_buffer.clear();
}

const std::vector<key_binding_entry>& key_binding_manager::bindings(bool gamepad) const
{
	return gamepad ? gamepad_bindings : keyboard_bindings;
}

bool key_binding_manager::set_binding(bool gamepad, size_t index, int key, bool append)
{
	auto& entries = gamepad ? gamepad_bindings : keyboard_bindings;
	if(index >= entries.size())
		return false;
	if(key != 0 && ((gamepad && !is_gamepad_key(key)) || (!gamepad && (is_gamepad_key(key) || is_fixed_binding_key(key)))))
		return false;
	if(key == 0)
		entries[index].keys.clear();
	else if(append)
	{
		if(std::find(entries[index].keys.begin(), entries[index].keys.end(), key) == entries[index].keys.end())
			entries[index].keys.push_back(key);
	}
	else
		entries[index].keys = {key};
	rebuild_lookup();
	return save();
}

bool key_binding_manager::reset_binding(bool gamepad, size_t index)
{
	auto& entries = gamepad ? gamepad_bindings : keyboard_bindings;
	if(index >= entries.size())
		return false;
	entries[index].keys = entries[index].default_keys;
	rebuild_lookup();
	return save();
}

bool key_binding_manager::has_conflict(bool gamepad, size_t index) const
{
	const auto& entries = gamepad ? gamepad_bindings : keyboard_bindings;
	if(index >= entries.size() || entries[index].keys.empty())
		return false;
	for(int key : entries[index].keys)
		for(size_t other = 0; other < entries.size(); ++other)
			if(other != index && entries[other].input_context == entries[index].input_context &&
				std::find(entries[other].keys.begin(), entries[other].keys.end(), key) != entries[other].keys.end())
				return true;
	return false;
}

bool key_binding_manager::has_submenu_conflict(bool gamepad, size_t index) const
{
	if(gamepad || index >= keyboard_bindings.size())
		return false;
	const key_binding_entry& entry = keyboard_bindings[index];
	const bool step_movement = entry.id.compare(0, 5, "MOVE_") == 0;
	const bool long_movement = entry.id.compare(0, 4, "RUN_") == 0;
	if(!step_movement && !long_movement)
		return false;
	for(int key : entry.keys)
		if((step_movement && is_step_movement_submenu_key(key)) ||
			(long_movement && is_long_movement_submenu_key(key)))
			return true;
	return false;
}

void key_binding_manager::reset(bool gamepad)
{
	auto& entries = gamepad ? gamepad_bindings : keyboard_bindings;
	for(auto& entry : entries)
		entry.keys = entry.default_keys;
	rebuild_lookup();
	save();
}

const std::map<int, std::vector<int>>& key_binding_manager::get_macros() const
{
	return macros;
}

bool key_binding_manager::set_macro(int trigger, const std::vector<int>& sequence)
{
	if(trigger <= 0 || sequence.empty() || is_fixed_binding_key(trigger) || is_macro_editor_key(trigger))
		return false;
	macros[trigger] = sequence;
	return save();
}

bool key_binding_manager::remove_macro(int trigger)
{
	if(macros.erase(trigger) == 0)
		return false;
	return save();
}

bool key_binding_manager::is_macro_editor_key(int key) const
{
	for(const auto& entry : keyboard_bindings)
		if(entry.command_key == '~' && std::find(entry.keys.begin(), entry.keys.end(), key) != entry.keys.end())
			return true;
	return false;
}

std::string key_binding_manager::key_name(int key) const
{
	if(key == 0) return "NONE";
	if(is_virtual_key_code(key))
	{
		int virtual_key = get_virtual_key(key);
		if(virtual_key >= VK_F1 && virtual_key <= VK_F12)
			return "F" + std::to_string(virtual_key - VK_F1 + 1);
		if(virtual_key == VK_INSERT) return "INSERT";
		if(virtual_key == VK_DELETE) return "DELETE";
		if(virtual_key == VK_UP) return "UP";
		if(virtual_key == VK_DOWN) return "DOWN";
		if(virtual_key == VK_LEFT) return "LEFT";
		if(virtual_key == VK_RIGHT) return "RIGHT";
		if(virtual_key == VK_NUMPAD1) return "NUM1";
		if(virtual_key == VK_NUMPAD3) return "NUM3";
		if(virtual_key == VK_NUMPAD7) return "NUM7";
		if(virtual_key == VK_NUMPAD9) return "NUM9";
		return "VK_" + std::to_string(virtual_key);
	}
	if(key == VK_ESCAPE) return "ESC";
	if(key == VK_RETURN) return "ENTER";
	if(key == VK_TAB) return "TAB";
	if(key == VK_BACK) return "BACKSPACE";
	if(key == ' ') return "SPACE";
	if(key == 0x8B) return "CTRL_A";
	if(key == 0x88) return "CTRL_P";
	if(key == 0x89) return "CTRL_Q";
	if(key == 0x8A) return "CTRL_S";
	if(key == 6) return "CTRL_F";
	if(key == 7) return "CTRL_G";
	if(key == 15) return "CTRL_O";
	if(key == GVK_BUTTON_A) return "PAD_A";
	if(key == GVK_BUTTON_A_LONG) return "PAD_A_HOLD";
	if(key == GVK_BUTTON_B) return "PAD_B";
	if(key == GVK_BUTTON_B_LONG) return "PAD_B_HOLD";
	if(key == GVK_BUTTON_X) return "PAD_X";
	if(key == GVK_BUTTON_X_LONG) return "PAD_X_HOLD";
	if(key == GVK_BUTTON_Y) return "PAD_Y";
	if(key == GVK_BUTTON_Y_LONG) return "PAD_Y_HOLD";
	if(key == GVK_LEFT_BUMPER) return "PAD_LB";
	if(key == GVK_RIGHT_BUMPER) return "PAD_RB";
	if(key == GVK_LT) return "PAD_LT";
	if(key == GVK_RT) return "PAD_RT";
	if(key == GVK_BACK) return "PAD_BACK";
	if(key == GVK_START) return "PAD_START";
	if(key >= 33 && key <= 126)
		return std::string(1, static_cast<char>(key));
	return "KEY_" + std::to_string(key);
}

int key_binding_manager::parse_key_name(const std::string& text) const
{
	std::string value = trim_copy(text);
	if(value.empty()) return -1;
	if(value.size() == 1) return static_cast<unsigned char>(value[0]);
	std::string upper = upper_copy(value);
	if(upper == "NONE") return 0;
	if(upper == "ESC" || upper == "ESCAPE") return VK_ESCAPE;
	if(upper == "ENTER" || upper == "RETURN") return VK_RETURN;
	if(upper == "TAB") return VK_TAB;
	if(upper == "BACKSPACE") return VK_BACK;
	if(upper == "DELETE" || upper == "DEL") return make_virtual_key_code(VK_DELETE);
	if(upper == "INSERT" || upper == "INS") return make_virtual_key_code(VK_INSERT);
	if(upper == "UP") return make_virtual_key_code(VK_UP);
	if(upper == "DOWN") return make_virtual_key_code(VK_DOWN);
	if(upper == "LEFT") return make_virtual_key_code(VK_LEFT);
	if(upper == "RIGHT") return make_virtual_key_code(VK_RIGHT);
	if(upper == "NUM1") return make_virtual_key_code(VK_NUMPAD1);
	if(upper == "NUM3") return make_virtual_key_code(VK_NUMPAD3);
	if(upper == "NUM7") return make_virtual_key_code(VK_NUMPAD7);
	if(upper == "NUM9") return make_virtual_key_code(VK_NUMPAD9);
	if(upper.size() >= 2 && upper[0] == 'F')
	{
		try
		{
			int function_number = std::stoi(upper.substr(1));
			if(function_number >= 1 && function_number <= 12)
				return make_virtual_key_code(VK_F1 + function_number - 1);
		}
		catch(...) {}
	}
	if(upper == "SPACE") return ' ';
	if(upper == "CTRL_A") return 0x8B;
	if(upper == "CTRL_P") return 0x88;
	if(upper == "CTRL_Q") return 0x89;
	if(upper == "CTRL_S") return 0x8A;
	if(upper == "CTRL_F") return 6;
	if(upper == "CTRL_G") return 7;
	if(upper == "CTRL_O") return 15;
	if(upper == "PAD_A") return GVK_BUTTON_A;
	if(upper == "PAD_A_HOLD") return GVK_BUTTON_A_LONG;
	if(upper == "PAD_B") return GVK_BUTTON_B;
	if(upper == "PAD_B_HOLD") return GVK_BUTTON_B_LONG;
	if(upper == "PAD_X") return GVK_BUTTON_X;
	if(upper == "PAD_X_HOLD") return GVK_BUTTON_X_LONG;
	if(upper == "PAD_Y") return GVK_BUTTON_Y;
	if(upper == "PAD_Y_HOLD") return GVK_BUTTON_Y_LONG;
	if(upper == "PAD_LB") return GVK_LEFT_BUMPER;
	if(upper == "PAD_RB") return GVK_RIGHT_BUMPER;
	if(upper == "PAD_LT") return GVK_LT;
	if(upper == "PAD_RT") return GVK_RT;
	if(upper == "PAD_BACK") return GVK_BACK;
	if(upper == "PAD_START") return GVK_START;
	if(upper.rfind("KEY_", 0) == 0)
	{
		try { return std::stoi(upper.substr(4)); }
		catch(...) { return -1; }
	}
	if(upper.rfind("VK_", 0) == 0)
	{
		try { return make_virtual_key_code(std::stoi(upper.substr(3))); }
		catch(...) { return -1; }
	}
	return -1;
}

std::vector<int> key_binding_manager::parse_sequence(const std::string& text) const
{
	std::vector<int> result;
	for(size_t i = 0; i < text.size();)
	{
		if(text[i] == '<')
		{
			size_t close = text.find('>', i + 1);
			if(close != std::string::npos)
			{
				int key = parse_key_name(text.substr(i + 1, close - i - 1));
				if(key > 0) result.push_back(key);
				i = close + 1;
				continue;
			}
		}
		result.push_back(static_cast<unsigned char>(text[i]));
		++i;
	}
	return result;
}

std::string key_binding_manager::sequence_name(const std::vector<int>& sequence) const
{
	std::string result;
	for(int key : sequence)
	{
		std::string name = key_name(key);
		if(key == '<')
			result += "<KEY_60>";
		else if(key >= 33 && key <= 126)
			result += static_cast<char>(key);
		else if(key == ' ')
			result += "<SPACE>";
		else
			result += '<' + name + '>';
	}
	return result;
}

std::string key_binding_manager::entry_name(const key_binding_entry& entry) const
{
	return LocalzationManager::locString(entry.label);
}

std::string key_binding_manager::binding_name(const key_binding_entry& entry, const std::string& separator) const
{
	if(entry.keys.empty())
		return "NONE";
	std::string result;
	for(int key : entry.keys)
	{
		if(!result.empty())
			result += separator;
		std::string name = key_name(key);
		result += name == "=" ? "KEY_61" : name;
	}
	return result;
}

std::string key_binding_manager::expand_help_tokens(const std::string& text, bool gamepad) const
{
	std::string result = text;
	auto expand = [&](const std::string& prefix, bool primary_only)
	{
		size_t begin = 0;
		while((begin = result.find(prefix, begin)) != std::string::npos)
		{
			size_t end = result.find('}', begin + prefix.size());
			if(end == std::string::npos)
				break;
			std::string id = upper_copy(result.substr(begin + prefix.size(), end - begin - prefix.size()));
			const auto& entries = gamepad ? gamepad_bindings : keyboard_bindings;
			std::string replacement = "NONE";
			for(const auto& entry : entries)
			{
				if(entry.id != id)
					continue;
				replacement.clear();
				for(int key : entry.keys)
				{
					if(!replacement.empty())
						replacement += '/';
					std::string name = gamepad ? joypadUtil::getRawGamepad(static_cast<wchar_t>(key)) : key_name(key);
					if(name.empty())
						name = key_name(key);
					if(gamepad)
					{
						name.erase(std::remove(name.begin(), name.end(), '['), name.end());
						name.erase(std::remove(name.begin(), name.end(), ']'), name.end());
					}
					else if(name.rfind("CTRL_", 0) == 0)
						name = "ctrl-" + name.substr(5);
					replacement += name;
					if(primary_only)
						break;
				}
				if(replacement.empty())
					replacement = "NONE";
				break;
			}
			result.replace(begin, end - begin + 1, replacement);
			begin += replacement.size();
		}
	};
	expand("{KEY1:", true);
	expand("{KEY:", false);
	return result;
}

int key_binding_manager::physical_gamepad_key(int command_key) const
{
	for(const auto& entry : gamepad_bindings)
		if(entry.command_key == command_key && !entry.keys.empty())
			return entry.keys.front();
	return command_key;
}

int key_binding_manager::gamepad_command_for_physical(int physical_key) const
{
	auto found = gamepad_lookup.find(physical_key);
	return found == gamepad_lookup.end() ? physical_key : found->second;
}

bool key_binding_manager::is_gamepad_dash_key(int physical_key) const
{
	for(const auto& entry : gamepad_bindings)
		if(entry.input_context == KEY_INPUT_DASH_MODIFIER &&
			std::find(entry.keys.begin(), entry.keys.end(), physical_key) != entry.keys.end())
			return true;
	return false;
}

bool key_binding_manager::open_file() const
{
	if(file_path.empty()) return false;
	if(!std::filesystem::exists(file_path)) save();
	HINSTANCE result = ShellExecuteW(nullptr, L"open", file_path.c_str(), nullptr, file_path.parent_path().c_str(), SW_SHOWNORMAL);
	return reinterpret_cast<INT_PTR>(result) > 32;
}

std::string key_config_menu_name()
{
	return LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MENU_NAME);
}

void print_key_binding_help(bool gamepad)
{
	printsub("                                   --- " + LocalzationManager::locString(gamepad ? LOC_SYSTEM_PAD_COMMAND_LIST : LOC_SYSTEM_COMMAND_LIST) + " ---", true, CL_normal);
	printsub("", true, CL_normal);
	const auto& help = gamepad ? LocalzationManager::getHelpPadCommand() : LocalzationManager::getHelpCommand();
	constexpr char help_tab_marker = '\x1D';
	constexpr int help_tab_column = 72;
	auto align_help_separator = [](std::string text, int current_width)
	{
		size_t separator = text.find("- ");
		if(separator == std::string::npos || separator == 0 ||
			text.find_first_not_of(' ', 0) != separator)
			return text;

		constexpr int help_description_column = 7;
		int local_width = current_width >= help_tab_column ?
			current_width - help_tab_column : current_width;
		int padding = local_width <= help_description_column ?
			help_description_column - local_width : 1;
		return std::string(std::max(1, padding), ' ') + text.substr(separator);
	};
	int line_width = 0;
	for(const TextHelper& text : help)
	{
		std::string expanded = keybind_mg.expand_help_tokens(text.text, gamepad);
		size_t start = 0;
		size_t tab = std::string::npos;
		while((tab = expanded.find(help_tab_marker, start)) != std::string::npos)
		{
			std::string before = align_help_separator(expanded.substr(start, tab - start), line_width);
			if(!before.empty())
			{
				printsub(before, false, text.color);
				line_width += PrintCharWidth(before);
			}
			int padding = std::max(1, help_tab_column - line_width);
			printsub(std::string(padding, ' '), false, CL_normal);
			line_width += padding;
			start = tab + 1;
		}
		std::string rest = align_help_separator(expanded.substr(start), line_width);
		printsub(rest, text.enter, text.color);
		if(text.enter)
			line_width = 0;
		else
			line_width += PrintCharWidth(rest);
	}
}

bool key_config_menu(int)
{
	bool gamepad = false;
	DisplayManager.current_position = 0;
	size_t selected[2] = {0, 0};
	while(true)
	{
		bool device_selected = false;
		while(!device_selected)
		{
			render_device_select(DisplayManager.current_position);
			InputedKey inputedKey;
			int input_;
			while(1) {
				input_ = waitkeyinput(inputedKey,true);
				
				if(input_ == -1) {
					if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
						if((inputedKey.val1 >= 'a' && inputedKey.val1 <= 'b') 
							|| inputedKey.val1 == VK_ESCAPE) {
							input_ = inputedKey.val1;
						}
						break;
					}
				}
				else if(input_ == VK_UP || input_ == VK_LEFT)
					DisplayManager.addPosition(-1);
				else if(input_ == VK_DOWN || input_ == VK_RIGHT)
					DisplayManager.addPosition(1);
				else if(input_ == VK_RETURN || input_ == GVK_BUTTON_A || input_ == GVK_BUTTON_A_LONG) {
					input_ = DisplayManager.positionToChar();
					break;
				} else {
					break;
				}
			}

			if(input_ >= 'a' && input_ <= 'b')
			{
				gamepad = (input_ == 'b');
				device_selected = true;
			}
			else if(input_ == VK_ESCAPE ||
			input_ == GVK_BUTTON_B ||
			input_ == GVK_BUTTON_B_LONG  || (input_ == -1 && inputedKey.isRightClick())) {
				return false;
			}
		}

		bool return_to_device = false;
		while(!return_to_device)
		{
			auto& current_selected = selected[gamepad ? 1 : 0];
			const auto& entries = keybind_mg.bindings(gamepad);
			std::vector<key_config_row> rows = build_key_config_rows(entries, gamepad);
			if(!entries.empty() && current_selected >= entries.size()) current_selected = entries.size() - 1;
			render_key_config(gamepad, current_selected);
			const bool prompt_gamepad = joypadUtil::isUsingPad();

			InputedKey inputed;
			int key = waitkeyinput(inputed, true, false, false, false, true);
			if(key == -1)
			{
				if(inputed.mouse == MKIND_SCROLL_UP)
					key = VK_UP;
				else if(inputed.mouse == MKIND_SCROLL_DOWN)
					key = VK_DOWN;
				else if(inputed.isRightClick())
					key = VK_ESCAPE;
			}
			if(key == VK_ESCAPE || key == KEYCONFIG_BACK || key == GVK_BUTTON_B || key == GVK_BUTTON_B_LONG)
			{
				DisplayManager.current_position = gamepad ? 1 : 0;
				return_to_device = true;
				continue;
			}
			if(key == VK_UP)
				move_key_config_selection(rows, current_selected, -1);
			else if(key == VK_DOWN)
				move_key_config_selection(rows, current_selected, 1);
			else if(key == VK_LEFT || key == VK_RIGHT)
			{
				int column = 0;
				int row = find_key_config_row(rows, current_selected, &column);
				if(row >= 0 && row < static_cast<int>(rows.size()))
				{
					int other = column == 0 ? rows[row].right : rows[row].left;
					if(other >= 0 && ((key == VK_LEFT && column == 1) || (key == VK_RIGHT && column == 0)))
						current_selected = static_cast<size_t>(other);
				}
			}
			else if(key == VK_PRIOR || key == KEYCONFIG_SCROLL_UP)
				move_key_config_selection(rows, current_selected, -key_config_page_rows());
			else if(key == VK_NEXT || key == KEYCONFIG_SCROLL_DOWN)
				move_key_config_selection(rows, current_selected, key_config_page_rows());
			else if(key == 'r' || key == KEYCONFIG_RESET || (prompt_gamepad && key == GVK_BUTTON_Y))
				keybind_mg.reset_binding(gamepad, current_selected);
			else if(key == 'R' || key == KEYCONFIG_RESET_ALL || (prompt_gamepad && key == GVK_RIGHT_BUMPER))
			{
				if(confirm_key_config_reset(gamepad, current_selected, true))
				{
					keybind_mg.reset(false);
					keybind_mg.reset(true);
				}
			}
			else if(key == 'O' || key == 'o' || key == KEYCONFIG_OPEN_FILE || (prompt_gamepad && key == GVK_BACK))
				keybind_mg.open_file();
			else if((key == VK_BACK || key == make_virtual_key_code(VK_DELETE) || key == KEYCONFIG_CLEAR ||
				(prompt_gamepad && key == GVK_BUTTON_X)) && !entries.empty())
				keybind_mg.set_binding(gamepad, current_selected, 0);
			else
			{
				size_t edit_index = current_selected;
				bool edit = key == VK_RETURN || key == GVK_BUTTON_A;
				bool append = key == 'A' || key == 'a' || key == KEYCONFIG_ADD || (prompt_gamepad && key == GVK_LEFT_BUMPER);
				if(key >= KEYCONFIG_ENTRY_BASE && key < KEYCONFIG_ENTRY_BASE + static_cast<int>(entries.size()))
				{
					edit_index = static_cast<size_t>(key - KEYCONFIG_ENTRY_BASE);
					current_selected = edit_index;
					edit = true;
				}
				if((!edit && !append) || entries.empty())
					continue;

				while(true)
				{
					render_key_config(gamepad, edit_index, true);
					InputedKey captured_input;
					int captured = waitkeyinput(captured_input, true, false, false, false, true);
					if(captured == VK_ESCAPE || captured == GVK_START || captured == -1)
						break;
					if(gamepad)
					{
						if(is_gamepad_key(captured))
						{
							keybind_mg.set_binding(true, current_selected, captured, append);
							break;
						}
					}
					else if(!is_gamepad_key(captured) && !is_fixed_direction_input(captured, captured_input))
					{
						keybind_mg.set_binding(false, current_selected, captured, append);
						break;
					}
				}
			}
		}
	}
}

void macro_add_query()
{
	auto finish = []() { changedisplay(DT_GAME); };
	render_macro_capture(LOC_SYSTEM_KEYCONFIG_MACRO_TRIGGER, true);
	InputedKey trigger_input;
	int trigger = waitkeyinput(trigger_input, true, false, false, false, true);
	trigger = macro_capture_key(trigger, trigger_input);
	if(trigger == VK_ESCAPE || trigger == GVK_BUTTON_B || trigger == GVK_BUTTON_B_LONG || trigger == -1 || is_fixed_direction_input(trigger, trigger_input))
	{
		finish();
		return;
	}
	if(keybind_mg.is_macro_editor_key(trigger))
	{
		finish();
		printlog(LocalzationManager::locString(LOC_SYSTEM_KEYCONFIG_MACRO_RESERVED), true, false, false, CL_warning);
		return;
	}

	auto found = keybind_mg.get_macros().find(trigger);
	if(found != keybind_mg.get_macros().end())
	{
		render_existing_macro(trigger, found->second);
		InputedKey choice_input;
		int choice = waitkeyinput(choice_input, true, false, false, false, true);
		choice = std::tolower(static_cast<unsigned char>(choice));
		if(choice == 'c')
		{
			keybind_mg.remove_macro(trigger);
			finish();
			printlog(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_MACRO_CLEARED,
				PlaceHolderHelper(keybind_mg.key_name(trigger))), true, false, false, CL_normal);
			return;
		}
		if(choice != 'r')
		{
			finish();
			return;
		}
	}

	std::vector<int> sequence;
	if(!capture_macro_sequence(sequence))
	{
		finish();
		return;
	}
	if(keybind_mg.set_macro(trigger, sequence))
	{
		std::string trigger_name = keybind_mg.key_name(trigger);
		std::string sequence_name = keybind_mg.sequence_name(sequence);
		finish();
		printlog(LocalzationManager::formatString(LOC_SYSTEM_KEYCONFIG_MACRO_CREATED,
			PlaceHolderHelper(trigger_name), PlaceHolderHelper(sequence_name)), true, false, false, CL_normal);
		return;
	}
	finish();
}
