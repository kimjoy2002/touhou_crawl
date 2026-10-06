#pragma once

#include <deque>
#include <filesystem>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include "enumMapBuilder.h"

struct key_binding_entry
{
	std::string id;
	LOCALIZATION_ENUM_KEY label;
	int command_key;
	std::vector<int> default_keys;
	std::vector<int> keys;
	int input_context = 0;
};

constexpr int KEYCODE_VIRTUAL_BASE = 0x10000;
constexpr int make_virtual_key_code(int virtual_key) { return KEYCODE_VIRTUAL_BASE + virtual_key; }
constexpr bool is_virtual_key_code(int key) { return key >= KEYCODE_VIRTUAL_BASE && key < KEYCODE_VIRTUAL_BASE + 0x100; }
constexpr int get_virtual_key(int key) { return key - KEYCODE_VIRTUAL_BASE; }

class key_binding_manager
{
	std::filesystem::path file_path;
	std::vector<key_binding_entry> keyboard_bindings;
	std::vector<key_binding_entry> gamepad_bindings;
	std::unordered_map<int, int> keyboard_lookup;
	std::unordered_map<int, int> gamepad_lookup;
	std::map<int, std::vector<int>> macros;
	std::deque<int> macro_buffer;

	void init_defaults();
	void rebuild_lookup();
	bool is_reserved_keyboard_key(int key) const;
	bool is_reserved_gamepad_key(int key) const;

public:
	void init(const std::filesystem::path& directory);
	bool load();
	bool save() const;
	void reset(bool gamepad);

	int process_input(int key, bool command_context, bool fixed_direction, bool raw_input, int movement_context = 0);
	bool pop_macro_input(int& key, bool direction_context);
	void clear_macro_buffer();

	const std::vector<key_binding_entry>& bindings(bool gamepad) const;
	bool set_binding(bool gamepad, size_t index, int key, bool append = false);
	bool reset_binding(bool gamepad, size_t index);
	bool has_conflict(bool gamepad, size_t index) const;
	bool has_submenu_conflict(bool gamepad, size_t index) const;

	const std::map<int, std::vector<int>>& get_macros() const;
	bool set_macro(int trigger, const std::vector<int>& sequence);
	bool remove_macro(int trigger);
	bool is_macro_editor_key(int key) const;

	std::string key_name(int key) const;
	int parse_key_name(const std::string& text) const;
	std::vector<int> parse_sequence(const std::string& text) const;
	std::string sequence_name(const std::vector<int>& sequence) const;
	std::string entry_name(const key_binding_entry& entry) const;
	std::string binding_name(const key_binding_entry& entry, const std::string& separator = ", ") const;
	std::string expand_help_tokens(const std::string& text, bool gamepad) const;
	int physical_gamepad_key(int command_key) const;
	int gamepad_command_for_physical(int physical_key) const;
	bool is_gamepad_dash_key(int physical_key) const;
	const std::filesystem::path& get_file_path() const { return file_path; }
	bool open_file() const;
};

extern key_binding_manager keybind_mg;

bool key_config_menu(int value);
std::string key_config_menu_name();
void print_key_binding_help(bool gamepad);
void macro_add_query();
