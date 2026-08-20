//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: crash_dump.cpp
//
// 내용: 크래시 내용을 기록한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "player.h"
#include "crash_dump.h"
#include <dbghelp.h>
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <atomic>
#include <deque>
#include <iomanip>
#include <mutex>
#include <sstream>

extern const char* version_string;
extern std::wstring morgue_path_w;

static std::atomic<long> writing_crash_dump(0);
static std::mutex crash_history_mutex;
static std::deque<std::string> crash_messages;
static std::deque<std::string> crash_inputs;
static std::string crash_message_line;

void AddCrashMessage(const std::string& message, bool enter) noexcept
{
	try
	{
		std::lock_guard<std::mutex> lock(crash_history_mutex);
		crash_message_line += message;
		if(crash_message_line.size() > 1024)
			crash_message_line.resize(1024);
		if(enter)
		{
			crash_messages.push_back(crash_message_line);
			crash_message_line.clear();
			while(crash_messages.size() > 20)
				crash_messages.pop_front();
		}
	}
	catch(...)
	{
	}
}

void AddCrashInput(const std::string& input) noexcept
{
	try
	{
		std::lock_guard<std::mutex> lock(crash_history_mutex);
		std::ostringstream ss;
		ss << GetTickCount64() << "ms " << input;
		crash_inputs.push_back(ss.str());
		while(crash_inputs.size() > 30)
			crash_inputs.pop_front();
	}
	catch(...)
	{
	}
}

static void AppendHistory(std::ostringstream& ss)
{
	if(!crash_history_mutex.try_lock())
	{
		ss << "recent history could not be read\n";
		return;
	}

	ss << "recent messages\n";
	for(const std::string& message : crash_messages)
		ss << message << "\n";
	if(!crash_message_line.empty())
		ss << crash_message_line << "\n";
	ss << "\nrecent inputs\n";
	for(const std::string& input : crash_inputs)
		ss << input << "\n";
	crash_history_mutex.unlock();
}

static const char* ExceptionName(DWORD code)
{
	switch(code)
	{
	case EXCEPTION_ACCESS_VIOLATION: return "access violation";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "array bounds exceeded";
	case EXCEPTION_BREAKPOINT: return "breakpoint";
	case EXCEPTION_DATATYPE_MISALIGNMENT: return "datatype misalignment";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "floating point divide by zero";
	case EXCEPTION_ILLEGAL_INSTRUCTION: return "illegal instruction";
	case EXCEPTION_IN_PAGE_ERROR: return "in page error";
	case EXCEPTION_INT_DIVIDE_BY_ZERO: return "integer divide by zero";
	case EXCEPTION_STACK_OVERFLOW: return "stack overflow";
	case 0xE06D7363: return "C++ exception";
	default: return "unknown exception";
	}
}

static void AppendStack(std::ostringstream& ss, CONTEXT* context_)
{
	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();
	CONTEXT context;

	if(context_)
		context = *context_;
	else
		RtlCaptureContext(&context);

	SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_FAIL_CRITICAL_ERRORS);
	SymInitialize(process, NULL, TRUE);

	STACKFRAME64 frame = {};
	DWORD machine;
#ifdef _M_X64
	machine = IMAGE_FILE_MACHINE_AMD64;
	frame.AddrPC.Offset = context.Rip;
	frame.AddrFrame.Offset = context.Rbp;
	frame.AddrStack.Offset = context.Rsp;
#else
	machine = IMAGE_FILE_MACHINE_I386;
	frame.AddrPC.Offset = context.Eip;
	frame.AddrFrame.Offset = context.Ebp;
	frame.AddrStack.Offset = context.Esp;
#endif
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrStack.Mode = AddrModeFlat;

	ss << "call stack\n";
	for(int i = 0; i < 40; i++)
	{
		if(!StackWalk64(machine, process, thread, &frame, &context, NULL,
			SymFunctionTableAccess64, SymGetModuleBase64, NULL) || !frame.AddrPC.Offset)
			break;

		DWORD64 address = frame.AddrPC.Offset;
		char symbol_buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = {};
		SYMBOL_INFO* symbol = (SYMBOL_INFO*)symbol_buffer;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;
		DWORD64 displacement = 0;

		ss << std::setw(2) << i << "  0x" << std::hex << address << std::dec;
		DWORD64 module_base = SymGetModuleBase64(process, address);
		if(module_base)
		{
			char module_path[MAX_PATH] = {};
			if(GetModuleFileNameA((HMODULE)module_base, module_path, MAX_PATH))
			{
				const char* module_name = strrchr(module_path, '\\');
				module_name = module_name ? module_name + 1 : module_path;
				ss << "  " << module_name << "+0x" << std::hex << address - module_base << std::dec;
			}
		}
		if(SymFromAddr(process, address, &displacement, symbol))
			ss << "  " << symbol->Name << "+0x" << std::hex << displacement << std::dec;

		IMAGEHLP_LINE64 line = {};
		line.SizeOfStruct = sizeof(line);
		DWORD line_displacement = 0;
		if(SymGetLineFromAddr64(process, address, &line_displacement, &line))
			ss << "  " << line.FileName << ":" << line.LineNumber;
		ss << "\n";
	}
	SymCleanup(process);
}

static char MapChar(environment& e, int x, int y)
{
	if(you.position.x == x && you.position.y == y)
		return '@';
	for(const monster& mon : e.mon_vector)
		if(mon.hp > 0 && mon.position.x == x && mon.position.y == y)
			return 'M';

	return e.getAsciiDot(x, y);
}

static void AppendGameState(std::ostringstream& ss)
{
	ss << "game state\n";
	ss << "floor=" << current_level;
	if(current_level >= 0 && current_level < MAXLEVEL)
		ss << " map_floor=" << env[current_level].floor;
	ss << " position=(" << you.position.x << "," << you.position.y << ")";
	ss << " turn=" << you.turn << " real_turn=" << you.real_turn << "\n";
	ss << "player level=" << you.level << " tribe=" << (int)you.tribe << " job=" << (int)you.job;
	ss << " hp=" << you.hp << "/" << you.max_hp << " mp=" << you.mp << "/" << you.max_mp << "\n";
	ss << "status poison=" << you.s_poison << " confuse=" << you.s_confuse;
	ss << " slow=" << you.s_slow << " frozen=" << you.s_frozen;
	ss << " paralyse=" << you.s_paralyse << " invisible=" << you.s_invisible;
	ss << " swift=" << you.s_swift << "\n";

	if(current_level < 0 || current_level >= MAXLEVEL)
		return;

	environment& e = env[current_level];
	int live_monster = 0;
	for(const monster& mon : e.mon_vector)
		if(mon.hp > 0)
			live_monster++;
	ss << "map monsters=" << live_monster << "/" << e.mon_vector.size();
	ss << " items=" << e.item_list.size() << " smoke=" << e.smoke_list.size();
	ss << " events=" << e.event_list.size() << "\n";

	ss << "visible monsters\n";
	int shown_monster = 0;
	for(monster& mon : e.mon_vector)
	{
		if(mon.hp <= 0 || mon.position.x < 0 || mon.position.x >= DG_MAX_X ||
			mon.position.y < 0 || mon.position.y >= DG_MAX_Y ||
			!(e.dgtile[mon.position.x][mon.position.y].flag & FLAG_INSIGHT))
			continue;
		ss << "id=" << mon.id;
		ss << " map_id=" << mon.map_id << " pos=(" << mon.position.x << "," << mon.position.y << ")";
		ss << " hp=" << mon.hp << "/" << mon.max_hp;
		ss << " target_ptr=" << mon.target << " target_map_id=" << mon.temp_target_map_id;
		ss << " delay=" << mon.time_delay << "\n";
		if(++shown_monster >= 20)
		{
			ss << "...\n";
			break;
		}
	}

	ss << "inventory\n";
	int shown_item = 0;
	for(item& it : you.item_list)
	{
		int equipped = -1;
		for(int slot = 0; slot < ET_LAST; slot++)
			if(you.equipment[slot] == &it)
				equipped = slot;
		ss << "id=" << (int)it.id << " type=" << (int)it.type << " num=" << it.num;
		ss << " identify=" << it.identify;
		ss << " curse=" << it.curse << " equipped=" << equipped;
		ss << " value=" << it.value << " values=" << it.value0 << "," << it.value1 << "," << it.value2;
		ss << "," << it.value3 << "," << it.value4 << "," << it.value5 << "\n";
		if(++shown_item >= 30)
		{
			ss << "... " << you.item_list.size() - shown_item << " more\n";
			break;
		}
	}

	int min_x = (you.position.x - 7 < 0) ? 0 : you.position.x - 7;
	int max_x = (you.position.x + 7 >= DG_MAX_X) ? DG_MAX_X - 1 : you.position.x + 7;
	int min_y = (you.position.y - 7 < 0) ? 0 : you.position.y - 7;
	int max_y = (you.position.y + 7 >= DG_MAX_Y) ? DG_MAX_Y - 1 : you.position.y + 7;
	ss << "map around player (x " << min_x << "-" << max_x << ", y " << min_y << "-" << max_y << ")\n";
	for(int y = min_y; y <= max_y; y++)
	{
		ss << std::setw(2) << y << " ";
		for(int x = min_x; x <= max_x; x++)
			ss << MapChar(e, x, y);
		ss << "\n";
	}
}

static bool TryAppendGameState(std::ostringstream* ss)
{
	__try
	{
		AppendGameState(*ss);
		return true;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}

static bool WriteCrashDump(EXCEPTION_POINTERS* exception_info, const char* message)
{
	if(writing_crash_dump.exchange(1) != 0)
		return false;

	_wmkdir(morgue_path_w.c_str());
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);

	wchar_t filename[512];
	swprintf_s(filename, 512, L"%s\\crash-%04d%02d%02d-%02d%02d%02d.txt",
		morgue_path_w.c_str(), 1900 + t.tm_year, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);

	std::ostringstream ss;
	DWORD code = exception_info && exception_info->ExceptionRecord ?
		exception_info->ExceptionRecord->ExceptionCode : 0;
	void* address = exception_info && exception_info->ExceptionRecord ?
		exception_info->ExceptionRecord->ExceptionAddress : NULL;

	ss << "Touhou Crawl crash report " << version_string << "\n\n";
	ss << "CRASH: " << (message ? message : ExceptionName(code));
	if(code)
		ss << " (0x" << std::hex << code << std::dec << ")";
	ss << "\n\n";
	ss << "time=" << 1900 + t.tm_year << "-" << std::setfill('0') << std::setw(2) << t.tm_mon + 1;
	ss << "-" << std::setw(2) << t.tm_mday << " " << std::setw(2) << t.tm_hour;
	ss << ":" << std::setw(2) << t.tm_min << ":" << std::setw(2) << t.tm_sec << std::setfill(' ') << "\n";
	ss << "thread=" << GetCurrentThreadId() << " address=" << address << "\n";

	if(exception_info && exception_info->ContextRecord)
	{
#ifdef _M_X64
		CONTEXT* c = exception_info->ContextRecord;
		ss << "rax=" << (void*)c->Rax << " rbx=" << (void*)c->Rbx << " rcx=" << (void*)c->Rcx << " rdx=" << (void*)c->Rdx << "\n";
		ss << "rsi=" << (void*)c->Rsi << " rdi=" << (void*)c->Rdi << " rbp=" << (void*)c->Rbp << " rsp=" << (void*)c->Rsp << "\n";
		ss << "rip=" << (void*)c->Rip << "\n";
#endif
	}
	ss << "\n";
	AppendStack(ss, exception_info ? exception_info->ContextRecord : NULL);
	ss << "\n";
	AppendHistory(ss);
	ss << "\n";
	if(!TryAppendGameState(&ss))
		ss << "game state could not be read\n";

	FILE* fp = NULL;
	bool result = false;
	if(_wfopen_s(&fp, filename, L"wb") == 0 && fp)
	{
		unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
		fwrite(bom, 1, 3, fp);
		std::string text = ss.str();
		fwrite(text.data(), 1, text.size(), fp);
		fclose(fp);
		result = true;
	}
	writing_crash_dump.store(0);
	return result;
}

LONG WINAPI CrashDumpExceptionFilter(EXCEPTION_POINTERS* exception_info)
{
	if(exception_info && exception_info->ExceptionRecord &&
		exception_info->ExceptionRecord->ExceptionCode == 0xE06D7363)
		return EXCEPTION_EXECUTE_HANDLER;

	try
	{
		WriteCrashDump(exception_info, NULL);
	}
	catch(...)
	{
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void CrashDumpMessage(const char* message)
{
	try
	{
		WriteCrashDump(NULL, message);
	}
	catch(...)
	{
	}
}

void InitCrashDump()
{
	SetUnhandledExceptionFilter(CrashDumpExceptionFilter);
}
