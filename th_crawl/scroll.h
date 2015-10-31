//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: scroll.h
//
// 내용: scroll관련 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SCROLL_H__
#define  __SCROLL_H__


#include "player.h"
#include "item.h"

scroll_type goodbadscroll(int good_bad);

extern char *scroll_uniden_string[SCT_MAX]; //스크롤 스트링
extern const char *scroll_iden_string[SCT_MAX];

int isGoodScroll(scroll_type kind);
void readscroll(scroll_type kind);

#endif // __SCROLL_H__