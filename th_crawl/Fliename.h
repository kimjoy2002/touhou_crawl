//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Fliename.h
//
// 내용: 사용 파일의 이름 모음
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef  __FILENAME_H__
#define  __FILENAME_H__

#define MAX_TITLE 6

const char imgfile_dungeon01[] = "./data/floor.png";

const char imgfile_monster01[] = "./data/monster.png";

const char imgfile_players01[] = "./data/players.png";

const char imgfile_item01[] = "./data/item.png";
const char imgfile_item02[] = "./data/item2.png";
const char imgfile_item03[] = "./data/item3.png";

const char imgfile_laser[] = "./data/laser.png";
const char imgfile_test[] = "./data/test.png";



extern const char *imgfile_title[MAX_TITLE];
extern const char *imgfile_god[];


const char imgfile_dot_floor[] = "./data/dot/fl.png";
const char imgfile_dot_wall[] = "./data/dot/wa.png";
const char imgfile_dot_monster[] = "./data/dot/mo.png";
const char imgfile_dot_player[] = "./data/dot/pl.png";
const char imgfile_dot_up[] = "./data/dot/up.png";
const char imgfile_dot_down[] = "./data/dot/do.png";
const char imgfile_dot_item[] = "./data/dot/it.png";
const char imgfile_dot_door[] = "./data/dot/dr.png";
const char imgfile_dot_temple[] = "./data/dot/te.png";
const char imgfile_dot_sea[] = "./data/dot/se.png";
const char imgfile_dot_mapping_floor[] = "./data/dot/mf.png";
const char imgfile_dot_mapping_wall[] = "./data/dot/mw.png";
const char imgfile_sight_rect[] = "./data/dot/sight.tga";

//여기에 추가하면 monster_texture.h, texture.h, texture.cpp


#endif // __FILENAME_H__