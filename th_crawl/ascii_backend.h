//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ascii_backend.h
//
// 콘솔 모드
//   th_crawl_console.exe   : 그 터미널에서
//   th_crawl.exe --console : 새 콘솔 창
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ASCII_BACKEND_H__
#define __ASCII_BACKEND_H__

namespace ascii {

bool requested(const char* cmdLine);
void init(const char* cmdLine);
bool enabled();

void beginFrame();
void recText(const wchar_t* text, float x, float y, unsigned int argb);
void recSelect(long left, long top, long right, long bottom);
void endFrame();

} // namespace ascii

#endif // __ASCII_BACKEND_H__
