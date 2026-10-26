//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ascii_backend.cpp
//
// 콘솔 출력(VT 시퀀스) + 콘솔 키 입력 주입 + 게임 화면 아스키 레이아웃.
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "ascii_backend.h"

#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "d3dUtility.h"
#include "display.h"
#include "environment.h"
#include "player.h"
#include "monster.h"
#include "mon_infor.h"
#include "smoke.h"
#include "option_manager.h"
#include "const.h"
#include "localization.h"
#include "throw.h"
#include <imm.h>
#pragma comment(lib, "imm32.lib")
#ifndef IMC_SETCONVERSIONMODE
#define IMC_SETCONVERSIONMODE 0x0002
#endif

using namespace std;

extern std::unique_ptr<KeyInputQueue> g_keyQueue;
extern std::atomic<bool> g_saveandexit;
extern bool widesearch;
bool IsCJKWideChar(wchar_t ch);
int PrintCharWidth(const wstring& wtext);

namespace {

int COLS = 120;
int ROWS = 30;

const int PANEL_W = 65;
int MAP_RX = 26, MAP_RY = 9;
int MAP_W = 53, MAP_H = 19;
int PANEL_COL = 55;
int MSG_ROW = 19;

void updateLayout(int cols, int rows, int min_map_h = 0)
{
	COLS = min(300, max(80, cols));
	ROWS = min(120, max(10, rows));
	MAP_W = max(21, COLS - PANEL_W - 2);
	if (MAP_W % 2 == 0)
		MAP_W--;
	MAP_H = max(9, ROWS - max(6, ROWS / 3));
	MAP_H = min(ROWS - 1, max(MAP_H, min_map_h));
	if (MAP_H % 2 == 0 && MAP_H > min_map_h)
		MAP_H--; 
	MAP_RX = (MAP_W - 1) / 2;
	MAP_RY = (MAP_H - 1) / 2;
	PANEL_COL = MAP_W + 2;
	MSG_ROW = MAP_H;
}

const unsigned int COLOR_DEFAULT = 0xffc8c8c8;

const wchar_t CLOUD_GLYPH = 0x0282; //ʂ

std::atomic<bool> g_enabled{ false };
HANDLE g_out = INVALID_HANDLE_VALUE;
HANDLE g_in = INVALID_HANDLE_VALUE;
bool g_ownConsole = false; 
struct TextOp
{
	wstring str;
	float x, y;
	unsigned int color;
};
vector<TextOp> g_texts;
vector<RECT> g_selects;
bool g_recording = false;
const unsigned int COLOR_SELECT_BG = 0xffffd040;

struct Cell
{
	wchar_t ch = L' ';
	unsigned int fg = COLOR_DEFAULT;
	unsigned int bg = 0;
	bool cont = false; //넓은 글자의 뒷칸
	bool operator==(const Cell& o) const { return ch == o.ch && fg == o.fg && bg == o.bg && cont == o.cont; }
	bool operator!=(const Cell& o) const { return !(*this == o); }
};

//2칸 문자를 ASCII 로 바꿔 쓴다
wchar_t narrowChar(wchar_t ch)
{
	if (ch < 0x80)
		return ch;
	switch (ch)
	{
	case 0x2190: return L'<';
	case 0x2191: return L'^';
	case 0x2192: return L'>';
	case 0x2193: return L'v';
	case 0x2194: return L'-';
	case 0x2195: return L'|';
	case 0x2196: case 0x2198: return L'\\';
	case 0x2197: case 0x2199: return L'/';
	case 0x00A7: return CLOUD_GLYPH; //§
	case 0x00B7: case 0x2026: return L'.'; //· …
	case 0x00D7: return L'x'; //×
	case 0x203B: case 0x2605: case 0x2606: case 0x25CF: case 0x2022: return L'*'; //※ ★ ☆ ● •
	case 0x25CB: return L'o'; //○
	case 0x25A0: case 0x25A1: return L'#'; //■ □
	case 0x2500: case 0x2501: return L'-'; //─ ━
	case 0x2502: case 0x2503: case 0x2551: return L'|'; //│ ┃ ║
	case 0x2550: return L'='; //═
	default:
		break;
	}
	if (ch >= 0x2500 && ch <= 0x257F)
		return L'+'; //그 밖의 표 테두리(├ ┼ ┌ 등)
	return ch;
}

class Grid
{
public:
	int w_, h_; //만들 때의 크기 (화면 크기가 바뀌어도 이 격자는 그대로)
	vector<Cell> cells;
	Grid() : w_(COLS), h_(ROWS), cells(COLS * ROWS) {}
	Cell& at(int x, int y) { return cells[y * w_ + x]; }
	int put(int x, int y, const wstring& s, unsigned int fg, unsigned int bg = 0, int max_x = -1)
	{
		if (max_x < 0 || max_x > w_)
			max_x = w_;
		if (y < 0 || y >= h_)
			return 0;
		int start_ = x;
		for (wchar_t ch : s)
		{
			if (ch == L'\n')
			{
				x = start_;
				if (++y >= h_)
					break;
				continue;
			}
			if (ch == L'\0' || ch == L'\r')
				continue;
			ch = narrowChar(ch);
			int w = IsCJKWideChar(ch) ? 2 : 1;
			if (x < 0) { x += w; continue; }
			if (x + w > max_x)
				break;
			clearWide(x, y);
			if (w == 2)
				clearWide(x + 1, y);
			Cell& c = at(x, y);
			c.ch = ch; c.fg = fg; c.bg = bg; c.cont = false;
			if (w == 2)
			{
				Cell& c2 = at(x + 1, y);
				c2.ch = L' '; c2.fg = fg; c2.bg = bg; c2.cont = true;
			}
			x += w;
		}
		return x - start_;
	}
private:
	//넓은 글자의 반쪽을 덮어쓰면 나머지 반쪽을 지운다.
	void clearWide(int x, int y)
	{
		Cell& c = at(x, y);
		if (c.cont && x > 0)
			at(x - 1, y) = Cell();
		else if (!c.cont && x + 1 < w_ && at(x + 1, y).cont)
			at(x + 1, y) = Cell();
	}
};

Grid g_prev;
bool g_full_redraw = true;

unsigned int dimColor(unsigned int c)
{
	unsigned int r = (c >> 16) & 0xff, g = (c >> 8) & 0xff, b = c & 0xff;
	return 0xff000000 | ((r / 2) << 16) | ((g / 2) << 8) | (b / 2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 출력
//////////////////////////////////////////////////////////////////////////////////////////////////

void writeOut(const wstring& s)
{
	if (g_out == INVALID_HANDLE_VALUE || s.empty())
		return;
	DWORD written = 0;
	WriteConsoleW(g_out, s.c_str(), (DWORD)s.size(), &written, nullptr);
}

void appendColor(wstring& out, unsigned int fg, unsigned int bg)
{
	wchar_t buf[64];
	swprintf_s(buf, L"\x1b[38;2;%u;%u;%um", (fg >> 16) & 0xff, (fg >> 8) & 0xff, fg & 0xff);
	out += buf;
	if (bg & 0xff000000)
	{
		swprintf_s(buf, L"\x1b[48;2;%u;%u;%um", (bg >> 16) & 0xff, (bg >> 8) & 0xff, bg & 0xff);
		out += buf;
	}
	else
		out += L"\x1b[49m";
}

void visibleSize(int& cols, int& rows)
{
	cols = COLS;
	rows = ROWS;
	CONSOLE_SCREEN_BUFFER_INFO info_;
	if (GetConsoleScreenBufferInfo(g_out, &info_))
	{
		cols = info_.srWindow.Right - info_.srWindow.Left + 1;
		rows = info_.srWindow.Bottom - info_.srWindow.Top + 1;
		if (g_ownConsole)
		{
			cols = info_.dwSize.X;
			rows = info_.dwSize.Y;
		}
	}
}

void present(Grid& grid)
{
	wstring out;
	static int last_cols_ = 0, last_rows_ = 0;
	int vis_cols_, vis_rows_;
	visibleSize(vis_cols_, vis_rows_);
	if (vis_cols_ != last_cols_ || vis_rows_ != last_rows_ || g_prev.w_ != grid.w_ || g_prev.h_ != grid.h_)
	{
		last_cols_ = vis_cols_;
		last_rows_ = vis_rows_;
		g_full_redraw = true;
		out += L"\x1b[0m\x1b[2J";
	}
	int draw_rows_ = max(1, min(grid.h_, vis_rows_));
	for (int y = 0; y < draw_rows_; y++)
	{
		bool changed_ = g_full_redraw;
		for (int x = 0; x < grid.w_ && !changed_; x++)
			if (grid.at(x, y) != g_prev.at(x, y))
				changed_ = true;
		if (!changed_)
			continue;
		wchar_t buf[32];
		swprintf_s(buf, L"\x1b[%d;1H", y + 1);
		out += buf;
		unsigned int fg = 0, bg = 1;
		for (int x = 0; x < min(grid.w_, vis_cols_); x++)
		{
			const Cell& c = grid.at(x, y);
			if (c.cont)
				continue;
			if (IsCJKWideChar(c.ch) && x + 1 >= vis_cols_)
				break; //넓은 글자가 창 끝에 걸리면 줄바꿈되므로 쓰지 않는다
			if (c.fg != fg || c.bg != bg)
			{
				appendColor(out, c.fg, c.bg);
				fg = c.fg; bg = c.bg;
			}
			out += c.ch;
		}
		out += L"\x1b[0m";
	}
	writeOut(out);
	g_prev = grid;
	g_full_redraw = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 텍스트 화면 (메뉴, 인벤토리 등)
//////////////////////////////////////////////////////////////////////////////////////////////////

int toCol(float x) { return (int)floor(x / DisplayManager.fontDesc.Width + 0.5f); }
int toRow(float y) { return (int)floor((y + DisplayManager.fontDesc.Height * 0.25f) / DisplayManager.fontDesc.Height); }

map<int, int> g_textRows;

void buildTextRows()
{
	g_textRows.clear();
	vector<int> ys_;
	float h_ = DisplayManager.fontDesc.Height;
	float bottom_ = (float)option_mg.getHeight() - h_ * 0.5f;
	for (const TextOp& t : g_texts)
		if (t.x >= -1000 && t.y >= -h_ * 0.5f && t.y < bottom_)
			ys_.push_back((int)lround(t.y));
	sort(ys_.begin(), ys_.end());
	ys_.erase(unique(ys_.begin(), ys_.end()), ys_.end());
	int row_ = 0, prev_ = 0;
	for (size_t i = 0; i < ys_.size(); i++)
	{
		if (i == 0)
			row_ = toRow((float)ys_[i]);
		else
		{
			float dy_ = (float)(ys_[i] - prev_);
			if (dy_ >= h_ * 0.5f)
				row_ += max(1, (int)floor(dy_ / h_ + 0.25f));
		}
		g_textRows[ys_[i]] = row_;
		prev_ = ys_[i];
	}
}

int g_textScroll = 0;
int g_textScrollState = -1;
int g_visRows = 30;

bool textInRect(const TextOp& t, const RECT& rc)
{
	float w_ = (float)PrintCharWidth(t.str) * DisplayManager.fontDesc.Width;
	return !(t.y < rc.top - 2 || t.y >= rc.bottom || t.x + w_ <= rc.left || t.x >= rc.right);
}

void updateTextScroll()
{
	if (DisplayManager.state != g_textScrollState)
	{
		g_textScroll = 0;
		g_textScrollState = DisplayManager.state;
	}
	int sel_min_ = INT_MAX, sel_max_ = -1;
	for (const RECT& rc : g_selects)
	{
		for (const TextOp& t : g_texts)
		{
			auto it_ = g_textRows.find((int)lround(t.y));
			if (it_ == g_textRows.end() || !textInRect(t, rc))
				continue;
			sel_min_ = min(sel_min_, it_->second);
			sel_max_ = max(sel_max_, it_->second);
		}
	}
	if (sel_max_ < 0)
		return;
	int view_ = max(1, min(ROWS, g_visRows));
	if (sel_max_ - g_textScroll >= view_)
		g_textScroll = sel_max_ - view_ + 1;
	if (sel_min_ < g_textScroll)
		g_textScroll = sel_min_;
	g_textScroll = max(0, g_textScroll);
}

bool textCell(float x, float y, int& col, int& row)
{
	auto it_ = g_textRows.find((int)lround(y));
	if (it_ == g_textRows.end())
		return false;
	col = toCol(x);
	row = it_->second - g_textScroll;
	return row >= 0;
}

void drawTexts(Grid& grid)
{
	buildTextRows();
	updateTextScroll();
	for (const TextOp& t : g_texts)
	{
		int col_, row_;
		if (t.x < -1000 || !textCell(t.x, t.y, col_, row_))
			continue;
		grid.put(col_, row_, t.str, t.color | 0xff000000);
	}
}

template <typename F>
void drawSelects(Grid& grid, F to_cell)
{
	for (const RECT& rc : g_selects)
	{
		map<int, pair<int, int>> rows_; //줄 -> (시작 칸, 끝 칸)
		for (const TextOp& t : g_texts)
		{
			if (!textInRect(t, rc))
				continue;
			int col_, row_;
			if (!to_cell(t.x, t.y, col_, row_) || row_ < 0 || row_ >= ROWS)
				continue;
			int end_ = col_ + PrintCharWidth(t.str);
			auto it_ = rows_.find(row_);
			if (it_ == rows_.end())
				rows_[row_] = make_pair(col_, end_);
			else
				it_->second = make_pair(min(it_->second.first, col_), max(it_->second.second, end_));
		}
		for (auto& r_ : rows_)
		{
			for (int x = max(0, r_.second.first); x < min(COLS, r_.second.second); x++)
			{
				Cell& c = grid.at(x, r_.first);
				c.bg = COLOR_SELECT_BG;
				c.fg = 0xff000000;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 게임 화면
//////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int readableColor(unsigned int fg_, unsigned int bg_)
{
	if (!(bg_ & 0xff000000))
		return fg_;
	int dr_ = (int)((fg_ >> 16) & 0xff) - (int)((bg_ >> 16) & 0xff);
	int dg_ = (int)((fg_ >> 8) & 0xff) - (int)((bg_ >> 8) & 0xff);
	int db_ = (int)(fg_ & 0xff) - (int)(bg_ & 0xff);
	return dr_ * dr_ + dg_ * dg_ + db_ * db_ < 120 * 120 ? 0xff000000 : fg_;
}

bool isShownMonster(monster& mon_)
{
	return mon_.isLive() && env[current_level].isInSight(mon_.position) && mon_.isView();
}

void drawMap(Grid& grid)
{
	environment& env_ = env[current_level];
	coord_def center_ = you.position;
	if (widesearch || (you.search && (abs(you.search_pos.x - center_.x) > MAP_RX || abs(you.search_pos.y - center_.y) > MAP_RY)))
		center_ = you.search_pos;

	map<pair<int, int>, item*> items_;
	for (item& item_ : env_.item_list)
	{
		auto key_ = make_pair(item_.position.x, item_.position.y);
		if (!items_.count(key_))
			items_[key_] = &item_;
	}
	map<pair<int, int>, smoke*> smokes_;
	for (smoke& smoke_ : env_.smoke_list)
		smokes_[make_pair(smoke_.position.x, smoke_.position.y)] = &smoke_;
	map<pair<int, int>, effect*> effects_;
	for (effect& effect_ : env_.effect_list)
		if (effect_.over_sight || env_.isInSight(effect_.position))
			effects_[make_pair(effect_.position.x, effect_.position.y)] = &effect_;

	for (int dy = -MAP_RY; dy <= MAP_RY; dy++)
	{
		for (int dx = -MAP_RX; dx <= MAP_RX; dx++)
		{
			int x = center_.x + dx, y = center_.y + dy;
			int gx = dx + MAP_RX, gy = dy + MAP_RY;
			if (x < 0 || y < 0 || x >= DG_MAX_X || y >= DG_MAX_Y)
				continue;
			bool sight_ = env_.isInSight(coord_def(x, y));
			if (!sight_ && !env_.isExplore(x, y) && !env_.isMapping(x, y))
				continue;
			char tile_ch_ = env_.getAsciiDot(x, y);
			wchar_t ch = (wchar_t)tile_ch_;
			unsigned int fg = env_.getAsciiColor(x, y);
			if (sight_)
			{
				auto smoke_it_ = smokes_.find(make_pair(x, y));
				auto item_it_ = items_.find(make_pair(x, y));
				if (item_it_ != items_.end())
				{
					ch = (wchar_t)item_it_->second->getAsciiDot();
					fg = item_it_->second->getAsciiColor();
				}
				if (smoke_it_ != smokes_.end())
				{
					ch = CLOUD_GLYPH;
					fg = smoke_it_->second->getAsciiColor();
				}
			}
			else
				fg = dimColor(fg);
			unsigned int bg = 0;
			if (sight_)
			{
				if (unit* unit_ = env_.isMonsterPos(x, y))
				{
					if (unit_->isplayer())
					{
						ch = L'@';
						fg = 0xffffffff;
					}
					else if (((monster*)unit_)->isView())
					{
						ch = (wchar_t)unit_->getAsciiDot();
						bg = ((monster*)unit_)->getAsciiBackColor();
						fg = readableColor(((monster*)unit_)->getAsciiColor(), bg);
					}
				}
			}
			//날아가는 탄막/마법, 레이저, 폭발 등 효과
			auto effect_it_ = effects_.find(make_pair(x, y));
			if (effect_it_ != effects_.end())
			{
				D3DCOLOR effect_color_ = 0;
				ch = (wchar_t)GetEffectAsciiDot(effect_it_->second->image, effect_color_);
				fg = effect_color_;
				bg = 0;
			}
			if (you.search && you.search_pos == coord_def(x, y))
			{
				bg = 0xffc0c0c0;
				fg = 0xff000000;
			}
			grid.put(gx, gy, wstring(1, ch), fg, bg);
		}
	}
}

void drawMonsterList(Grid& grid, int row_, int max_row_)
{
	struct Entry
	{
		wchar_t ch;
		unsigned int color;
		unsigned int back;
		wstring name;
		vector<pair<wstring, unsigned int>> states;
		int count;
		int dist;
	};
	vector<Entry> list_;
	for (monster& mon_ : env[current_level].mon_vector)
	{
		if (!isShownMonster(mon_) || (mon_.flag & M_FLAG_UNHARM))
			continue;
		Entry e;
		e.ch = (wchar_t)mon_.getAsciiDot();
		e.back = mon_.getAsciiBackColor();
		e.color = readableColor(mon_.getAsciiColor(), e.back);
		e.name = ConvertUTF8ToUTF16(mon_.GetName()->getName());
		if (!(mon_.flag & M_FLAG_NO_STATE))
		{
			for (monster_state_simple mss = MSS_SLEEP; mss < MSS_MAX; mss = (monster_state_simple)(mss + 1))
			{
				ostringstream ss;
				D3DCOLOR color_ = mon_.GetStateString(mss, ss);
				if (color_ != CL_none)
					e.states.push_back(make_pair(ConvertUTF8ToUTF16(ss.str()), (unsigned int)color_ | 0xff000000));
			}
		}
		e.count = 1;
		e.dist = max(abs(mon_.position.x - you.position.x), abs(mon_.position.y - you.position.y));
		bool merged_ = false;
		for (Entry& other_ : list_)
		{
			if (other_.ch == e.ch && other_.name == e.name && other_.states == e.states && other_.color == e.color && other_.back == e.back)
			{
				other_.count++;
				other_.dist = min(other_.dist, e.dist);
				merged_ = true;
				break;
			}
		}
		if (!merged_)
			list_.push_back(e);
	}
	sort(list_.begin(), list_.end(), [](const Entry& a, const Entry& b) { return a.dist < b.dist; });
	for (size_t n_ = 0; n_ < list_.size(); n_++)
	{
		const Entry& e = list_[n_];
		if (row_ >= max_row_)
			break;
		//다 못 보여주면 마지막으로 보이는 몬스터 뒤에 ... 을 붙인다
		bool cut_ = row_ == max_row_ - 1 && n_ + 1 < list_.size();
		int x = PANEL_COL;
		x += grid.put(x, row_, wstring(1, e.ch), e.color, e.back);
		x += grid.put(x, row_, L" ", COLOR_DEFAULT);
		wstring name_ = e.name;
		if (e.count > 1)
			name_ += L" x" + to_wstring(e.count);
		x += grid.put(x, row_, name_, COLOR_DEFAULT);
		for (size_t i = 0; i < e.states.size(); i++)
		{
			x += grid.put(x, row_, i ? L", " : L" (", COLOR_DEFAULT);
			x += grid.put(x, row_, e.states[i].first, e.states[i].second);
		}
		if (!e.states.empty())
			x += grid.put(x, row_, L")", COLOR_DEFAULT);
		if (cut_)
			grid.put(x, row_, L" ...", COLOR_DEFAULT);
		row_++;
	}
}

//@ 가 가리는 발밑의 지형과 아이템
void drawUnderPlayer(Grid& grid, int row_)
{
	environment& env_ = env[current_level];
	int x = PANEL_COL;
	x += grid.put(x, row_, L"@:", COLOR_DEFAULT);
	vector<item*> items_;
	for (item& it_ : env_.item_list)
		if (it_.position.x == you.position.x && it_.position.y == you.position.y)
			items_.push_back(&it_);
	char tile_ch_ = env_.getAsciiDot(you.position.x, you.position.y);
	if (items_.empty() && tile_ch_ != '.' && tile_ch_ != ' ')
	{
		dungeon_tile_type tile_ = env_.dgtile[you.position.x][you.position.y].tile;
		x += grid.put(x, row_, L" " + wstring(1, (wchar_t)tile_ch_), env_.getAsciiColor(you.position.x, you.position.y));
		wstring name_ = ConvertUTF8ToUTF16(LocalzationManager::locString(dungeon_tile_tribe_type_string[tile_]));
		if (!name_.empty())
			x += grid.put(x, row_, L" (" + name_ + L")", COLOR_DEFAULT);
	}
	//아이템이 2개 이상이고 이름까지 쓰면 줄을 넘으면 기호만 보여준다
	int need_ = x;
	for (item* it_ : items_)
		need_ += 3 + PrintCharWidth(ConvertUTF8ToUTF16(it_->GetName()));
	bool glyph_only_ = items_.size() >= 2 && need_ > COLS;
	if (glyph_only_)
		x += grid.put(x, row_, L" ", COLOR_DEFAULT);
	for (item* it_ : items_)
	{
		unsigned int color_ = it_->getAsciiColor();
		wchar_t ch_ = (wchar_t)it_->getAsciiDot();
		if (glyph_only_)
		{
			x += grid.put(x, row_, wstring(1, ch_), color_);
			continue;
		}
		x += grid.put(x, row_, L" " + wstring(1, ch_), color_);
		x += grid.put(x, row_, L" " + ConvertUTF8ToUTF16(it_->GetName()), COLOR_DEFAULT);
		if (x >= COLS)
			break;
	}
}

void drawGame(Grid& grid)
{
	drawMap(grid);

	//게임이 그린 텍스트 중 오른쪽은 상태창, 위쪽은 메시지
	int info_min_x_ = 32 * (option_mg.getTileMaxX() * 2) + 50;
	int log_rows_ = DisplayManager.text_log.short_len + 1;
	int panel_last_row_ = 0;
	for (const TextOp& t : g_texts)
	{
		if (t.x < -1000 || t.y < -1000)
			continue;
		int row_ = toRow(t.y);
		if (t.x >= info_min_x_)
		{
			if (row_ >= MAP_H)
				continue;
			grid.put(PANEL_COL + toCol(t.x - info_min_x_), row_, t.str, t.color | 0xff000000);
			panel_last_row_ = max(panel_last_row_, row_);
		}
		else if (row_ < log_rows_)
			grid.put(toCol(t.x), MSG_ROW + row_, t.str, t.color | 0xff000000);
	}
	drawUnderPlayer(grid, panel_last_row_ + 1);
	drawMonsterList(grid, panel_last_row_ + 2, MAP_H);
	drawSelects(grid, [&](float x, float y, int& col, int& row) {
		int r_ = toRow(y);
		if (x >= info_min_x_)
		{
			col = PANEL_COL + toCol(x - info_min_x_);
			row = r_;
			return r_ < MAP_H;
		}
		col = toCol(x);
		row = MSG_ROW + r_;
		return r_ < log_rows_;
	});
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 입력
//////////////////////////////////////////////////////////////////////////////////////////////////

void pushMsg(UINT message_, WPARAM wparam_)
{
	MSG m{};
	m.message = message_;
	m.wParam = wparam_;
	if (g_keyQueue)
		g_keyQueue->push(m);
}

void inputLoop()
{
	INPUT_RECORD records_[32];
	while (true)
	{
		DWORD n = 0;
		if (!ReadConsoleInputW(g_in, records_, 32, &n))
			break;
		for (DWORD i = 0; i < n; i++)
		{
			const INPUT_RECORD& r = records_[i];
			if (r.EventType == WINDOW_BUFFER_SIZE_EVENT)
			{
				g_full_redraw = true;
				continue;
			}
			if (r.EventType != KEY_EVENT)
				continue;
			const KEY_EVENT_RECORD& k = r.Event.KeyEvent;
			WORD vk = k.wVirtualKeyCode;
			if (!k.bKeyDown)
			{
				if (vk == VK_SHIFT || vk == VK_CONTROL)
					pushMsg(WM_KEYUP, vk);
				continue;
			}
			if (k.dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
				continue;
			wchar_t ch_ = k.uChar.UnicodeChar;
			//한글 입력 상태로 눌린 자모(ㅁ 등)는 같은 자리의 영문 키로 바꾼다 (게임 명령은 영문 키)
			if (vk == VK_PROCESSKEY)
				vk = (WORD)MapVirtualKeyW(k.wVirtualScanCode, MAPVK_VSC_TO_VK);
			if ((ch_ >= 0x3131 && ch_ <= 0x318E) || (k.wVirtualKeyCode == VK_PROCESSKEY && ch_ == 0))
			{
				if (vk >= 'A' && vk <= 'Z')
					ch_ = (k.dwControlKeyState & SHIFT_PRESSED) ? (wchar_t)vk : (wchar_t)(vk - 'A' + 'a');
				else if (ch_ >= 0x3131)
					continue;
			}
			for (WORD rep = 0; rep < max<WORD>(1, k.wRepeatCount); rep++)
			{
				pushMsg(WM_KEYDOWN, vk);
				if (ch_)
					pushMsg(WM_CHAR, ch_);
			}
		}
	}
}

BOOL WINAPI ctrlHandler(DWORD type_)
{
	if (type_ == CTRL_CLOSE_EVENT || type_ == CTRL_LOGOFF_EVENT || type_ == CTRL_SHUTDOWN_EVENT)
	{
		g_saveandexit = true; //창을 닫을 때와 같이 저장하고 끝낸다.
		Sleep(4000);
		return TRUE;
	}
	return TRUE; //Ctrl+C 등은 무시
}

//터미널에서 실행했을 때 끝나고 원래대로 돌려놓을 상태
DWORD g_origOutMode = 0, g_origInMode = 0;
UINT g_origCP = 0;
CONSOLE_SCREEN_BUFFER_INFO g_origInfo{};
wchar_t g_origTitle[256] = {};

void restoreConsole()
{
	writeOut(L"\x1b[0m\x1b[?25h\x1b[?1049l");
	if (g_ownConsole)
		return;
	SetConsoleMode(g_out, g_origOutMode);
	SetConsoleMode(g_in, g_origInMode);
	SetConsoleOutputCP(g_origCP);
	SetConsoleScreenBufferSize(g_out, g_origInfo.dwSize);
	SetConsoleWindowInfo(g_out, TRUE, &g_origInfo.srWindow);
	SetConsoleTitleW(g_origTitle);
}

void setupConsole()
{
	g_ownConsole = !GetConsoleWindow();
	if (g_ownConsole)
		AllocConsole();
	g_out = CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	g_in = CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	GetConsoleMode(g_out, &g_origOutMode);
	GetConsoleMode(g_in, &g_origInMode);
	g_origCP = GetConsoleOutputCP();
	GetConsoleScreenBufferInfo(g_out, &g_origInfo);
	GetConsoleTitleW(g_origTitle, 255);
	atexit(restoreConsole);
	//입력기를 영문 모드로 시작한다 (한/영 키로 다시 바꿀 수 있다).
	//실행한 터미널을 쓰는 경우엔 지금 앞에 있는 창(그 터미널)도 바꾼다. 새 콘솔이면 다른 프로그램 창은 건드리지 않는다.
	for (HWND w_ : { GetConsoleWindow(), g_ownConsole ? (HWND)nullptr : GetForegroundWindow() })
		if (HWND ime_ = w_ ? ImmGetDefaultIMEWnd(w_) : nullptr)
			SendMessageW(ime_, WM_IME_CONTROL, IMC_SETCONVERSIONMODE, IME_CMODE_ALPHANUMERIC);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitleW(L"Touhou Crawl");
	SetConsoleMode(g_out, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
	SetConsoleMode(g_in, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT);
	SetConsoleCtrlHandler(ctrlHandler, TRUE);

	if (g_ownConsole)
	{
		SMALL_RECT tiny_ = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(g_out, TRUE, &tiny_);
		SetConsoleScreenBufferSize(g_out, { (SHORT)COLS, (SHORT)ROWS });
		SMALL_RECT full_ = { 0, 0, (SHORT)(COLS - 1), (SHORT)(ROWS - 1) };
		SetConsoleWindowInfo(g_out, TRUE, &full_);
	}

	writeOut(L"\x1b[?1049h\x1b[?25l\x1b[2J");
}

} // namespace

namespace ascii {

bool requested(const char* cmdLine)
{
	string cl = cmdLine ? cmdLine : "";
	if (cl.find("--console") != string::npos)
		return true;
	//콘솔판(th_crawl_console.exe)은 시작할 때 이미 콘솔이 있으므로 플래그 없이도 콘솔 모드
	return GetConsoleWindow() != nullptr && cl.find("--webtiles") == string::npos && cl.find("--headless") == string::npos;
}

void init(const char* cmdLine)
{
	if (!requested(cmdLine))
		return;
	setupConsole();
	g_enabled.store(true);
	std::thread(inputLoop).detach();
}

bool enabled() { return g_enabled.load(); }

void beginFrame()
{
	if (!g_enabled.load())
		return;
	g_recording = true;
	g_texts.clear();
	g_selects.clear();
}

void recText(const wchar_t* text, float x, float y, unsigned int argb)
{
	if (!g_recording || !text || !*text)
		return;
	g_texts.push_back({ wstring(text), x, y, argb });
}

void recSelect(long left, long top, long right, long bottom)
{
	if (!g_recording)
		return;
	g_selects.push_back({ left, top, right, bottom });
}

void endFrame()
{
	if (!g_recording)
		return;
	g_recording = false;
	int vis_cols_, vis_rows_;
	visibleSize(vis_cols_, vis_rows_);
	int panel_rows_ = 0;
	if (DisplayManager.state == DT_GAME)
	{
		int info_min_x_ = 32 * (option_mg.getTileMaxX() * 2) + 50;
		for (const TextOp& t : g_texts)
			if (t.x >= info_min_x_ && t.y >= 0 && t.y < option_mg.getHeight())
				panel_rows_ = max(panel_rows_, toRow(t.y) + 1);
		panel_rows_ += 2;
	}
	updateLayout(vis_cols_, vis_rows_, panel_rows_);
	g_visRows = vis_rows_;
	DisplayManager.text_log.short_len = max(1, ROWS - MSG_ROW);
	Grid grid;
	if (DisplayManager.state == DT_GAME)
		drawGame(grid);
	else
	{
		drawTexts(grid);
		drawSelects(grid, textCell);
	}
	present(grid);
}

} // namespace ascii
