//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: crash_dump.h
//
// 내용: 크래시 내용을 기록한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CRASH_DUMP_H__
#define __CRASH_DUMP_H__

struct _EXCEPTION_POINTERS;
typedef struct _EXCEPTION_POINTERS EXCEPTION_POINTERS;

#include <string>

void InitCrashDump();
long __stdcall CrashDumpExceptionFilter(EXCEPTION_POINTERS* exception_info);
void CrashDumpMessage(const char* message);
void AddCrashMessage(const std::string& message, bool enter) noexcept;
void AddCrashInput(const std::string& input) noexcept;

#endif
