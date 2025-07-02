//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Fliename.h
//
// 내용: 사용 파일의 이름 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef  __FILENAME_H__
#define  __FILENAME_H__

#define MAX_TITLE 7

const char imgfile_dungeon01[] = "./data/floor";
const char imgfile_dungeon02[] = "./data/floor2";

const char imgfile_monster01[] = "./data/monster";
const char imgfile_monster02[] = "./data/monster2";

const char imgfile_players01[] = "./data/players";

const char imgfile_item01[] = "./data/item";
const char imgfile_item02[] = "./data/item2";
const char imgfile_item03[] = "./data/item3";
const char imgfile_item04[] = "./data/item4";

const char imgfile_laser[] = "./data/laser";



extern const char *imgfile_title[MAX_TITLE];
extern const char *imgfile_god[];


const char imgfile_dot_floor[] = "./data/dot/fl";
const char imgfile_dot_wall[] = "./data/dot/wa";
const char imgfile_dot_monster[] = "./data/dot/mo";
const char imgfile_dot_player[] = "./data/dot/pl";
const char imgfile_dot_up[] = "./data/dot/up";
const char imgfile_dot_down[] = "./data/dot/do";
const char imgfile_dot_item[] = "./data/dot/it";
const char imgfile_dot_door[] = "./data/dot/dr";
const char imgfile_dot_temple[] = "./data/dot/te";
const char imgfile_dot_sea[] = "./data/dot/se";
const char imgfile_dot_mapping_floor[] = "./data/dot/mf";
const char imgfile_dot_mapping_wall[] = "./data/dot/mw";
const char imgfile_sight_rect[] = "./data/dot/sight";

//여기에 추가하면 monster_texture.h, texture.h, texture.cpp


#endif // __FILENAME_H__