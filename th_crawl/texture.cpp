//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: texture.cpp
//
// 내용: texture클래스 정의 및 텍스쳐객체
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "textureUtility.h"
#include "monster_texture.h"
#include "texture.h"
#include "Fliename.h"

#include "option_manager.h"
#include "enum.h"


const char *imgfile_title[MAX_TITLE] = 
{
	"./data/title.png",
	"./data/title2.png",
	//"./data/title_0.png",
	//"./data/title_1.png",
	"./data/title_3.png",
	"./data/title_4.png",
	"./data/title_5.png",
};


TextureFile texture_dungeon01(imgfile_dungeon01);
TextureFile texture_monster01(imgfile_monster01);
TextureFile texture_players01(imgfile_players01);
TextureFile texture_item01(imgfile_item01);
TextureFile texture_item02(imgfile_item02);
TextureFile texture_laser(imgfile_laser);
TextureFile texture_test(imgfile_test);
TextureFile texture_dot_floor(imgfile_dot_floor);
TextureFile texture_dot_wall(imgfile_dot_wall);
TextureFile texture_dot_monster(imgfile_dot_monster);
TextureFile texture_dot_player(imgfile_dot_player);
TextureFile texture_dot_up(imgfile_dot_up);
TextureFile texture_dot_down(imgfile_dot_down);
TextureFile texture_dot_item(imgfile_dot_item);
TextureFile texture_dot_door(imgfile_dot_door);
TextureFile texture_dot_temple(imgfile_dot_temple);
TextureFile texture_dot_sea(imgfile_dot_sea);
TextureFile texture_dot_mapping_floor(imgfile_dot_mapping_floor);
TextureFile texture_dot_mapping_wall(imgfile_dot_mapping_wall);

TextureFile texture_sight_rect(imgfile_sight_rect);


TextureFile texture_title(imgfile_title[0]);



textures img_title(&texture_title, 0, 0, 512, 512, 255);

textures img_dungeon01[] = {textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //땅1
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 256, 0, 288, 32, 255),
					textures(&texture_dungeon01, 384, 0, 416, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //문열림 15
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단-신전
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단-안개
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단-요괴산
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단-홍마					
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단홍마도서관
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단홍마지하
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단죽림
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단영원정
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //계단지저

					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),//플로어 더미끝

					
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),

					textures(&texture_dungeon01, 64, 0, 96, 32, 255),//벽60
					textures(&texture_dungeon01, 32, 0, 64, 32, 255),//돌벽
					textures(&texture_dungeon01, 128, 0, 160, 32, 255),//붉은벽
					textures(&texture_dungeon01, 160, 0, 192, 32, 255),//책장
					textures(&texture_dungeon01, 224, 0, 256, 32, 255),//대나무
					textures(&texture_dungeon01, 192, 0, 224, 32, 255),//철벽
					textures(&texture_dungeon01, 448, 0, 480, 32, 255),//벽2
					textures(&texture_dungeon01, 480, 0, 512, 32, 255),//벽3
					textures(&texture_item01, 3, 255), //닫힌문
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),//유리
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),//석상
					textures(&texture_dungeon01, 96, 0, 128, 32, 255),//바다
					textures(&texture_item01, 167, 255)
};

textures img_dungeon_object[][3] = {{textures(&texture_item01, 4, 255),textures(&texture_item01, 4, 255),textures(&texture_item01, 4, 255)},
				{textures(&texture_item01, 5, 255),textures(&texture_item01, 5, 255),textures(&texture_item01, 5, 255)},//계단내
				{textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255)},//계단올
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단신전
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단안개
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단요괴
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단홍마
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단홍마도서관
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단홍마지하
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단죽림
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단영원정
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단지저
				
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단윳쿠리
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단짐승길
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단꿈
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단달
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단마계
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단히쿠레이

				{textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255)},//계단
				{textures(&texture_item01, 120, 255),textures(&texture_item01, 120, 255),textures(&texture_item01, 120, 255)}, //시키
				{textures(&texture_item01, 121, 255),textures(&texture_item01, 121, 255),textures(&texture_item01, 121, 255)}, //뱌쿠렌
				{textures(&texture_item01, 122, 255),textures(&texture_item01, 122, 255),textures(&texture_item01, 122, 255)}, //카나코
				{textures(&texture_item01, 123, 255),textures(&texture_item01, 123, 255),textures(&texture_item01, 123, 255)}, //스와코
				{textures(&texture_item01, 124, 255),textures(&texture_item01, 124, 255),textures(&texture_item01, 124, 255)}, //미노리코
				{textures(&texture_item01, 125, 255),textures(&texture_item01, 125, 255),textures(&texture_item01, 125, 255)}, //미마
				{textures(&texture_item01, 126, 255),textures(&texture_item01, 126, 255),textures(&texture_item01, 126, 255)}, //신키
				{textures(&texture_item01, 127, 255),textures(&texture_item01, 127, 255),textures(&texture_item01, 127, 255)},  //유우기
				{textures(&texture_item01, 128, 255),textures(&texture_item01, 220, 255),textures(&texture_item01, 221, 255)}, //시즈하
			    {textures(&texture_item01, 129, 255),textures(&texture_item01, 129, 255),textures(&texture_item01, 129, 255)}, //히나
			    {textures(&texture_item01, 130, 255),textures(&texture_item01, 130, 255),textures(&texture_item01, 130, 255)}, //유카리
			    {textures(&texture_item01, 131, 255),textures(&texture_item01, 131, 255),textures(&texture_item01, 131, 255)}, //에이린
				{textures(&texture_item01, 132, 255),textures(&texture_item01, 132, 255),textures(&texture_item01, 132, 255)}, //유유코
			    {textures(&texture_item01, 133, 255),textures(&texture_item01, 133, 255),textures(&texture_item01, 133, 255)}, //사토리
			    {textures(&texture_item01, 134, 255),textures(&texture_item01, 134, 255),textures(&texture_item01, 134, 255)}, //텐시
				{textures(&texture_item01, 236, 255),textures(&texture_item01, 236, 255),textures(&texture_item01, 236, 255)}, //세이자				
				{textures(&texture_item01, 175, 255),textures(&texture_item01, 175, 255),textures(&texture_item01, 175, 255)}, //릴리
				{ textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255) }, //미코
				{ textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255) }, //오키나
				{ textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255), textures(&texture_item01, 222, 255) }, //순호

				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},



								
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}, //벽
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 168, 255),textures(&texture_item01, 168, 255),textures(&texture_item01, 168, 255)},
				{textures(&texture_item01, 222, 255),textures(&texture_item01, 222, 255),textures(&texture_item01, 222, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}
};


textures img_mons_default(&texture_monster01, 47, 255);

textures img_mons_reimu_yukkuri(&texture_monster01, 0, 255);
textures img_mons_rat(&texture_monster01, 1, 255);
textures img_mons_fairy_green(&texture_monster01, 2, 255);
textures img_mons_fairy_blue(&texture_monster01, 3, 255);
textures img_mons_fairy_red(&texture_monster01, 4, 255);
textures img_mons_mook(&texture_monster01, 5, 255);
textures img_mons_crow(&texture_monster01, 6, 255);
textures img_mons_crane(&texture_monster01, 7, 255);
textures img_mons_spider(&texture_monster01, 8, 255);
textures img_mons_snake(&texture_monster01, 9, 255);
textures img_mons_katpa(&texture_monster01, 59, 255);
textures img_mons_katpa_gun(&texture_monster01, 59, 255);
textures img_mons_fairy_green_warroir(&texture_monster01, 10, 255);
textures img_mons_fairy_blue_magician(&texture_monster01, 11, 255);
textures img_mons_fairy_red_commander(&texture_monster01, 12, 255);
textures img_mons_human_woman(&texture_monster01,19, 255);
textures img_mons_human_man(&texture_monster01, 20, 255);
textures img_mons_human_yinyang(&texture_monster01, 21, 255);
textures img_mons_human_priest(&texture_monster01, 22, 255);
textures img_mons_human_samuri(&texture_monster01, 23, 255);
textures img_mons_firefly(&texture_monster01, 24, 255);
textures img_mons_butterfly(&texture_monster01, 25, 255);
textures img_mons_ghost[] = {textures(&texture_monster01, 26, 255),
				textures(&texture_monster01, 27, 255),
				textures(&texture_monster01, 28	, 255)};
textures img_mons_bakekasa(&texture_monster01, 29, 255);
textures img_mons_green_mook(&texture_monster01, 30, 255);
textures img_mons_orange_mook(&texture_monster01, 31, 255);
textures img_mons_gray_mook(&texture_monster01, 32, 255);
textures img_mons_frog(&texture_monster01, 33, 255);
textures img_mons_black_cat(&texture_monster01, 34, 255);
textures img_mons_orange_cat(&texture_monster01, 35, 255);
textures img_mons_white_cat(&texture_monster01, 36, 255);
textures img_mons_crow_tengu(&texture_monster01, 38, 255);
textures img_mons_oni(&texture_monster01, 37, 255);
textures img_mons_marisa_yukkuri(&texture_monster01, 45, 255);
textures img_mons_aya_yukkuri(&texture_monster01, 46, 255);
textures img_mons_remila_yukkuri(&texture_monster01, 49, 255);
textures img_mons_alice_yukkuri(&texture_monster01, 50, 255);
textures img_mons_yamabiko(&texture_monster01, 51, 255);
textures img_mons_katpa_spear(&texture_monster01, 60, 255);
textures img_mons_katpa_water_wizard(&texture_monster01, 61, 255);
textures img_mons_yamabush_tengu(&texture_monster01, 52, 255);
textures img_mons_hanataca_tengu(&texture_monster01, 53, 255);
textures img_mons_blue_oni(&texture_monster01, 54, 255);
textures img_mons_mushroom(&texture_monster01, 55, 255);
textures img_mons_new_kappa(&texture_monster01, 59, 255);
textures img_mons_new_kappa_spear(&texture_monster01, 60, 255);
textures img_mons_new_kappa_wizard(&texture_monster01, 61, 255);

textures img_mons_magic_book[] = 
{
	textures(&texture_monster01, 85, 255),
	textures(&texture_monster01, 86, 255),
	textures(&texture_monster01, 87, 255),
	textures(&texture_monster01, 88, 255)
};
textures img_mons_hobgobrin(&texture_monster01, 89, 255);
textures img_mons_hobgobrin_maid(&texture_monster01, 90, 255);
textures img_mons_hobgobrin_librarian(&texture_monster01, 91, 255);
textures img_mons_hobgobrin_temp(&texture_monster01, 92, 255);
textures img_mons_maid_fairy(&texture_monster01, 93, 255);
textures img_mons_chuparcabra(&texture_monster01, 94, 255);
textures img_mons_eagle(&texture_monster01, 99, 255);
textures img_mons_tiger(&texture_monster01, 100, 255);
textures img_mons_raijuu(&texture_monster01, 101, 255);
textures img_mons_dragon_baby(&texture_monster01, 102, 255);

textures img_mons_yamawaro_ninja(&texture_monster01, 104, 255);
textures img_mons_yamawaro_warrior(&texture_monster01, 105, 255);
textures img_mons_yamawaro_flag(&texture_monster01, 106, 255);
textures img_mons_option(&texture_monster01, 107, 255);
textures img_mons_golem(&texture_monster01, 108, 255);
textures img_mons_onbasira(&texture_monster01, 109, 255);
textures img_mons_red_ufo(&texture_monster01, 110, 255);
textures img_mons_blue_ufo(&texture_monster01, 111, 255);
textures img_mons_green_ufo(&texture_monster01, 112, 255);
textures img_mons_sanpei_fighter(&texture_monster01, 115, 255);
textures img_mons_vamp_bat(&texture_monster01, 116, 255);
textures img_mons_dagama(&texture_monster01, 117, 255);

textures img_mons_rabit(&texture_monster01, 118, 255);
textures img_mons_youkai_rabit(&texture_monster01, 119, 255);
textures img_mons_namaz(&texture_monster01, 120, 255);
textures img_mons_hell_crow(&texture_monster01, 121, 255);
textures img_mons_raccoon(&texture_monster01, 122, 255);
textures img_mons_lantern_youkai(&texture_monster01, 123, 255);
textures img_mons_yinyan(&texture_monster01, 124, 255);
textures img_mons_yugenmagan(&texture_monster01, 125, 255);
textures img_mons_elise(&texture_monster01, 126, 255);
textures img_mons_sariel(&texture_monster01, 127, 255);
textures img_mons_sara(&texture_monster01, 128, 255);
textures img_mons_louise(&texture_monster01, 129, 255);
textures img_mons_yuki(&texture_monster01, 130, 255);
textures img_mons_mai(&texture_monster01, 131, 255);
textures img_mons_yumeko(&texture_monster01, 132, 255);
textures img_mons_evil_eye(&texture_monster01, 133, 255);
textures img_mons_little_imp(&texture_monster01, 134, 255);
textures img_mons_schema_eye(&texture_monster01, 138, 255);
textures img_mons_bomb_rabbit(&texture_monster01, 139, 255);
textures img_mons_spear_rabbit(&texture_monster01, 140, 255);
textures img_mons_support_rabbit(&texture_monster01, 141, 255);
textures img_mons_magic_rabbit(&texture_monster01, 142, 255);


textures img_named_seiran(&texture_monster01, 147, 255);
textures img_named_ringo(&texture_monster01, 148, 255);
textures img_mons_fairy_green_hero(&texture_monster01, 149, 255);
textures img_mons_fairy_green_socerer(&texture_monster01, 150, 255);
textures img_mons_fairy_green_himawari(&texture_monster01, 151, 255);
textures img_mons_moon_rabbit_attack(&texture_monster01, 152, 255);
textures img_mons_moon_rabbit_supporter(&texture_monster01, 153, 255);
textures img_mons_moon_rabbit_elite(&texture_monster01, 154, 255);
textures img_mons_mac(&texture_monster01, 155, 255);
textures img_mons_nightmare(&texture_monster01, 156, 255);
textures img_mons_lunatic(&texture_monster01, 157, 255);
textures img_mons_haunt[] = 
{
	textures(&texture_monster01, 158, 255),
	textures(&texture_monster01, 159, 255),
	textures(&texture_monster01, 160, 255)
};
textures img_mons_fire_car(&texture_monster01, 161, 255);
textures img_mons_hell_spider(&texture_monster01, 162, 255);
textures img_mons_blood_haunt(&texture_monster01, 163, 255);
textures img_mons_hell_dog(&texture_monster01, 164, 255);
textures img_mons_flower_tank[] = 
{
	textures(&texture_monster01, 165, 255),
	textures(&texture_monster01, 166, 255)
};
textures img_mons_evil_eye_tank(&texture_monster01, 167, 255);
textures img_mons_snow_girl(&texture_monster01, 168, 255);
textures img_named_letty(&texture_monster01, 169, 255);
textures img_named_yorihime(&texture_monster01, 170, 255);
textures img_named_toyohime(&texture_monster01, 171, 255);
textures img_named_utsuho(&texture_monster01, 172, 255);
textures img_named_suika(&texture_monster01, 173, 255);
textures img_named_reimu(&texture_monster01, 174, 255);
textures img_named_alice(&texture_monster01, 175, 255);
textures img_named_udonge(&texture_monster01, 176, 255);
textures img_named_kaguya(&texture_monster01, 177, 255);
textures img_mons_nesi(&texture_monster01, 178, 255);
textures img_mons_sanghai[] = 
{
	textures(&texture_monster01, 179, 255),
	textures(&texture_monster01, 181, 255)
};
textures img_mons_hourai[] = 
{
	textures(&texture_monster01, 180, 255),
	textures(&texture_monster01, 182, 255)
};

textures img_mons_youmu_yukkuri(&texture_monster01, 183, 255);
textures img_mons_tokiko(&texture_monster01, 184, 255);
textures img_mons_toziko(&texture_monster01, 185, 255);
textures img_mons_futo(&texture_monster01, 186, 255);
textures img_mons_mamizo(&texture_monster01, 187, 255);
textures img_mons_seiga(&texture_monster01, 188, 255);
textures img_mons_close_door(&texture_item01, 3, 255);

textures img_mons_anchor(&texture_monster01, 190, 255);
textures img_mons_mask_angry(&texture_monster01, 212, 255);
textures img_mons_mask_sad(&texture_monster01, 213, 255);
textures img_mons_mask_happy(&texture_monster01, 214, 255);
textures img_mons_trash[] =
{
	textures(&texture_monster01, 216, 255),
	textures(&texture_monster01, 217, 255),
	textures(&texture_monster01, 218, 255),
	textures(&texture_monster01, 219, 255)
};

textures img_mons_occult_long(&texture_monster01, 220, 255);
textures img_mons_occult_disk(&texture_monster01, 221, 255);
textures img_mons_occult_small(&texture_monster01, 222, 255);
textures img_mons_occult_kunekune(&texture_monster01, 223, 255);





textures img_named_rumia(&texture_monster01, 13, 255);
textures img_named_mistia(&texture_monster01, 14, 255);
textures img_named_wriggle(&texture_monster01, 15, 255);
textures img_named_cirno(&texture_monster01, 16, 255);
textures img_named_medicine(&texture_monster01, 17, 255);
textures img_named_diefairy(&texture_monster01, 18, 255);
textures img_named_kisume(&texture_monster01, 39, 255);
textures img_named_chen(&texture_monster01,40, 255);
textures img_named_kogasa(&texture_monster01, 41, 255);
textures img_named_sunny(&texture_monster01, 42, 255);
textures img_named_lunar(&texture_monster01, 43, 255);
textures img_named_star(&texture_monster01, 44, 255);
textures img_named_sigmund(&texture_monster01, 48, 255);
textures img_named_kyouko(&texture_monster01, 56, 255);
textures img_named_momizi(&texture_monster01, 57, 255);
textures img_named_aya(&texture_monster01, 58, 255);
textures img_named_wakasagi(&texture_monster01, 62, 255);
textures img_named_yamame(&texture_monster01, 63, 255);
textures img_named_nazrin(&texture_monster01, 64, 255);
textures img_mons_dauzing(&texture_monster01, 65, 255);
textures img_named_yosika(&texture_monster01, 66, 255);
textures img_named_sekibanki(&texture_monster01, 67, 255);
textures img_named_sekibanki_body(&texture_monster01, 68, 255);
textures img_named_sekibanki_head(&texture_monster01, 69, 255);
textures img_named_nitori(&texture_monster01, 70, 255);
textures img_named_kagero(&texture_monster01, 71, 255);
textures img_named_parsi(&texture_monster01, 72, 255);
textures img_named_benben(&texture_monster01, 73, 255);
textures img_named_yathasi(&texture_monster01, 74, 255);
textures img_named_orin(&texture_monster01, 75, 255);
textures img_named_orin_cat(&texture_monster01, 76, 255);
textures img_mons_zombiefairy(&texture_monster01, 77, 255);
textures img_named_ichirin(&texture_monster01, 78, 255);
textures img_named_unzan(&texture_monster01, 79, 255);
textures img_named_unzan_punch[] = 
{
	textures(&texture_monster01, 80, 255),
	textures(&texture_monster01, 81, 255),
	textures(&texture_monster01, 82, 255),
	textures(&texture_monster01, 83, 255)
};
textures img_named_pachu(&texture_monster01, 84, 255);
textures img_named_koakuma(&texture_monster01, 95, 255);
textures img_named_meirin(&texture_monster01, 96, 255);
textures img_named_sakuya(&texture_monster01, 97, 255);
textures img_named_remilia(&texture_monster01, 98, 255);
textures img_named_kasen(&texture_monster01, 103, 255);
textures img_named_koishi(&texture_monster01, 113, 255);
textures img_named_nue(&texture_monster01, 114, 255);
textures img_named_flandre(&texture_monster01, 143, 255);
textures img_named_tewi(&texture_monster01, 144, 255);
textures img_named_clownpiece(&texture_monster01, 145, 255);
textures img_named_doremi(&texture_monster01, 146, 255);
textures img_named_murasa(&texture_monster01, 189, 255);
textures img_named_keine(&texture_monster01, 191, 255);
textures img_named_keine2(&texture_monster01, 192, 255);
textures img_named_youmu(&texture_monster01, 193, 255);
textures img_named_lyrica(&texture_monster01, 194, 255);
textures img_named_merlin(&texture_monster01, 195, 255);
textures img_named_lunasa(&texture_monster01, 196, 255);
textures img_named_komachi(&texture_monster01, 197, 255);
textures img_named_iku(&texture_monster01, 200, 255);
textures img_named_larva(&texture_monster01, 201, 255);
textures img_named_nemuno(&texture_monster01, 202, 255);
textures img_named_aunn(&texture_monster01, 203, 255);
textures img_named_narumi(&texture_monster01, 204, 255);
textures img_named_mai(&texture_monster01, 205, 255);
textures img_named_satono(&texture_monster01, 206, 255);
textures img_named_kokoro[] =
{
	textures(&texture_monster01, 208, 255),
	textures(&texture_monster01, 209, 255),
	textures(&texture_monster01, 210, 255),
	textures(&texture_monster01, 211, 255)
};
textures img_named_sumireko(&texture_monster01, 215, 255);








textures img_play_reimu(&texture_players01, 0, 255);
textures img_play_marisa(&texture_players01, 1, 255);
textures img_play_sanae(&texture_players01, 2, 255);
textures img_play_momizi(&texture_players01, 3, 255);
textures img_play_normal(&texture_players01, 4, 255);
textures img_play_yamame(&texture_players01, 5, 255);
textures img_play_mokou[] = {
		textures(&texture_players01, 6, 255),
		textures(&texture_players01, 7, 255),
		textures(&texture_players01, 8, 255)
};


textures img_item_armor_robe(&texture_item01, 7, 255);
textures img_item_armor_cloak(&texture_item01, 8, 255);
textures img_item_armor_robe_sanae(&texture_item01, 9, 255);
textures img_item_armor_glove(&texture_item01, 10, 255);
textures img_item_armor_boot(&texture_item01, 11, 255);
textures img_item_armor_helmet(&texture_item01, 12, 255);
textures img_item_armor_armour_0(&texture_item01, 136, 255);
textures img_item_armor_armour_1(&texture_item01, 137, 255);
textures img_item_armor_armour_2(&texture_item01, 138, 255);
textures img_item_armor_armour_3(&texture_item01, 139, 255);

textures img_item_autumn_armour[] =
{	
	textures(&texture_item01, 176, 255),
	textures(&texture_item01, 177, 255),
	textures(&texture_item01, 178, 255),
	textures(&texture_item01, 179, 255),
	textures(&texture_item01, 180, 255)
};


textures img_item_armor_relec(&texture_item01, 223, 255);
textures img_item_armor_rcold(&texture_item01, 224, 255);
textures img_item_armor_rfire(&texture_item01, 225, 255);
textures img_item_armor_rmagic(&texture_item01, 226, 255);
textures img_item_armor_rpois(&texture_item01, 227, 255);


textures img_item_evo_pagoda(&texture_item01, 228, 255);
textures img_item_evo_air_scroll(&texture_item01, 229, 255);
textures img_item_evo_dream_soul(&texture_item01, 230, 255);
textures img_item_evo_hammer(&texture_item01, 231, 255);



textures img_item_weapon_gohey(&texture_item01, 33, 255);
textures img_item_weapon_dagger(&texture_item01, 34, 255);
textures img_item_weapon_katana(&texture_item01, 35, 255);
textures img_item_weapon_scimitar(&texture_item01, 36, 255);
textures img_item_weapon_greatsword(&texture_item01, 37, 255);
textures img_item_weapon_broomstick(&texture_item01, 38, 255);
textures img_item_weapon_handaxe(&texture_item01, 39, 255);
textures img_item_weapon_battleaxe(&texture_item01, 40, 255);
textures img_item_weapon_anchor(&texture_item01, 41, 255);
textures img_item_weapon_spear(&texture_item01, 42, 255);
textures img_item_weapon_scythe(&texture_item01, 43, 255);
textures img_item_weapon_trident(&texture_item01, 44, 255);
textures img_item_weapon_smalllance(&texture_item01, 45, 255);
textures img_item_weapon_umbrella(&texture_item01, 46, 255);
textures img_item_weapon_knife(&texture_item01, 47, 255);
textures img_item_weapon_shortsword(&texture_item01, 48, 255);
textures img_item_weapon_gohey2(&texture_item01, 49, 255);
textures img_item_weapon_hammer(&texture_item01, 50, 255);
textures img_item_weapon_onbasira(&texture_item01, 51, 255);
textures img_item_weapon_roundshield(&texture_item01, 52, 255);
textures img_item_weapon_shield(&texture_item01, 53, 255);
textures img_item_weapon_momizishield(&texture_item01, 54, 255);
textures img_item_weapon_kiteshield(&texture_item01, 55, 255);




textures img_item_food_bread(&texture_item01, 0, 255);
textures img_item_food_p_item(&texture_item01, 63, 255);

textures img_item_potion[] = {textures(&texture_item02, 0, 255),
	textures(&texture_item02, 1, 255),
	textures(&texture_item02, 2, 255),
	textures(&texture_item02, 3, 255),
	textures(&texture_item02, 4, 255),
	textures(&texture_item02, 5, 255),
	textures(&texture_item02, 6, 255),
	textures(&texture_item02, 7, 255),
	textures(&texture_item02, 8, 255),
	textures(&texture_item02, 9, 255),
	textures(&texture_item02, 10, 255),
	textures(&texture_item02, 11, 255),
	textures(&texture_item02, 12, 255),
	textures(&texture_item02, 13, 255),
	textures(&texture_item02, 14, 255),
	textures(&texture_item02, 15, 255),
	textures(&texture_item02, 16, 255),
	textures(&texture_item02, 17, 255),
	textures(&texture_item02, 18, 255),
	textures(&texture_item02, 19, 255)
};


textures img_item_scroll(&texture_item01, 14, 255);

textures img_item_book[] = {textures(&texture_item02, 32, 255),
	textures(&texture_item02, 33, 255),
	textures(&texture_item02, 34, 255),
	textures(&texture_item02, 35, 255),
	textures(&texture_item02, 36, 255),
	textures(&texture_item02, 37, 255),
	textures(&texture_item02, 38, 255)
};


textures img_item_potion_kind[] = { textures(&texture_item02, 48, 255),
textures(&texture_item02, 49, 255),
textures(&texture_item02, 50, 255),
textures(&texture_item02, 51, 255),
textures(&texture_item02, 52, 255),
textures(&texture_item02, 53, 255),
textures(&texture_item02, 54, 255),
textures(&texture_item02, 55, 255),
textures(&texture_item02, 56, 255),
textures(&texture_item02, 57, 255),
textures(&texture_item02, 58, 255),
textures(&texture_item02, 59, 255),
textures(&texture_item02, 60, 255),
textures(&texture_item02, 61, 255),
textures(&texture_item02, 62, 255),
textures(&texture_item02, 63, 255),
textures(&texture_item02, 64, 255) };

textures img_item_scroll_kind[] = { textures(&texture_item02, 80, 255),
textures(&texture_item02, 81, 255),
textures(&texture_item02, 82, 255),
textures(&texture_item02, 83, 255),
textures(&texture_item02, 84, 255),
textures(&texture_item02, 85, 255),
textures(&texture_item02, 86, 255),
textures(&texture_item02, 87, 255),
textures(&texture_item02, 88, 255),
textures(&texture_item02, 89, 255),
textures(&texture_item02, 90, 255),
textures(&texture_item02, 91, 255),
textures(&texture_item02, 92, 255),
textures(&texture_item02, 93, 255),
textures(&texture_item02, 94, 255),
textures(&texture_item02, 95, 255),
textures(&texture_item02, 96, 255),
textures(&texture_item02, 97, 255),
textures(&texture_item02, 98, 255) };


textures img_item_amulet_kind[] = { textures(&texture_item02, 112, 255),
textures(&texture_item02, 113, 255),
textures(&texture_item02, 114, 255),
textures(&texture_item02, 115, 255),
textures(&texture_item02, 116, 255),
textures(&texture_item02, 117, 255),
textures(&texture_item02, 118, 255),
textures(&texture_item02, 119, 255),
textures(&texture_item02, 120, 255),
textures(&texture_item02, 121, 255)
};

textures img_item_goal(&texture_item01, 135, 255);
textures img_item_rune(&texture_item01, 214, 255);

textures img_item_ring(&texture_item01, 15, 255);

textures img_item_amulet(&texture_item01, 16, 255);

textures img_item_needle(&texture_item01, 141, 255);
textures img_item_kikuichi(&texture_item01, 142, 255);

textures img_item_spellcard(&texture_item01, 181, 255);
textures img_item_sweet_potato(&texture_item01, 182, 255);


textures img_effect_select(&texture_item01, 1, 255);
textures img_effect_slience(&texture_item01, 111, 255);
textures img_effect_auto_pick(&texture_item01, 143, 255);
textures img_effect_lunatic(&texture_dungeon01, 288, 0, 320, 32, 255);
textures img_effect_freeze(&texture_dungeon01, 320, 0, 352, 32, 255);
textures img_effect_gold(&texture_dungeon01, 352, 0, 384, 32, 255);
textures img_mons_test(&texture_test, 0, 0, 32, 32, 255);



textures img_effect_tanmac_middle[] = 
{
	textures(&texture_item01, 57, 255),
	textures(&texture_item01, 58, 255),
	textures(&texture_item01, 59, 255),
	textures(&texture_item01, 60, 255),
	textures(&texture_item01, 61, 255),
	textures(&texture_item01, 62, 255)
};

textures img_hp_graphic[5] = 
{
	textures(&texture_item01, 256, 125, 288, 127, 255),
	textures(&texture_item01, 256, 119, 288, 121, 255),
	textures(&texture_item01, 256, 113, 288, 115, 255),
	textures(&texture_item01, 256, 107, 288, 109, 255),
	textures(&texture_item01, 256, 101, 288, 103, 255)
};

textures img_tanmac_bill[] = {textures(&texture_item01, 17, 255),
							  textures(&texture_item01, 18, 255),
							  textures(&texture_item01, 19, 255),
							  textures(&texture_item01, 20, 255),
							  textures(&texture_item01, 21, 255),
							  textures(&texture_item01, 22, 255),
							  textures(&texture_item01, 23, 255),
							  textures(&texture_item01, 24, 255)
};

textures img_tanmac_amulet[] = {textures(&texture_item01, 25, 255),
							    textures(&texture_item01, 26, 255)
};



textures img_fog_normal[] = {textures(&texture_item01, 64, 255),
							    textures(&texture_item01, 65, 255),
							    textures(&texture_item01, 66, 255),
							    textures(&texture_item01, 67, 255)
};
textures img_fog_fire[] = {textures(&texture_item01, 68, 255),
							    textures(&texture_item01, 69, 255),
							    textures(&texture_item01, 70, 255),
							    textures(&texture_item01, 71, 255)
};
textures img_fog_cold[] = {textures(&texture_item01, 72, 255),
								textures(&texture_item01, 73, 255),
							    textures(&texture_item01, 74, 255),
							    textures(&texture_item01, 75, 255),
};
textures img_fog_dark[] = {textures(&texture_item01, 76, 255),
								textures(&texture_item01, 77, 255),
							    textures(&texture_item01, 78, 255),
							    textures(&texture_item01, 79, 255)
};
textures img_fog_poison[] = {textures(&texture_item01, 80, 255),
							    textures(&texture_item01, 81, 255),
							    textures(&texture_item01, 82, 255),
							    textures(&texture_item01, 83, 255)
};
textures img_fog_slow[] = {textures(&texture_item01, 84, 255),
							    textures(&texture_item01, 85, 255),
							    textures(&texture_item01, 86, 255),
							    textures(&texture_item01, 87, 255)
};


textures img_tanmac_fire_big[] = {textures(&texture_item01, 88, 255),
								textures(&texture_item01, 89, 255),
							    textures(&texture_item01, 90, 255),
							    textures(&texture_item01, 91, 255),
								textures(&texture_item01, 92, 255),
								textures(&texture_item01, 93, 255),
							    textures(&texture_item01, 94, 255),
							    textures(&texture_item01, 95, 255)
};
textures img_tanmac_fire_small[] = {textures(&texture_item01, 96, 255),
							    textures(&texture_item01, 97, 255),
							    textures(&texture_item01, 98, 255),
							    textures(&texture_item01, 99, 255),
								textures(&texture_item01, 100, 255),
							    textures(&texture_item01, 101, 255),
							    textures(&texture_item01, 102, 255),
							    textures(&texture_item01, 103, 255)
};
textures img_tanmac_ice[] = {textures(&texture_item01, 104, 255),
								textures(&texture_item01, 105, 255),
							    textures(&texture_item01, 106, 255),
							    textures(&texture_item01, 107, 255)
};
textures img_tanmac_ice_big[] = {textures(&texture_item01, 160, 255),
							    textures(&texture_item01, 161, 255),
							    textures(&texture_item01, 162, 255),
							    textures(&texture_item01, 163, 255),
								textures(&texture_item01, 164, 255),
							    textures(&texture_item01, 165, 255),
							    textures(&texture_item01, 166, 255),
							    textures(&texture_item01, 167, 255)
};
textures img_tanmac_ice_small[] = {textures(&texture_item01, 112, 255),
							    textures(&texture_item01, 113, 255),
							    textures(&texture_item01, 114, 255),
							    textures(&texture_item01, 115, 255),
								textures(&texture_item01, 116, 255),
							    textures(&texture_item01, 117, 255),
							    textures(&texture_item01, 118, 255),
							    textures(&texture_item01, 119, 255)
};
textures img_tanmac_poison_big[] = {textures(&texture_item01, 152, 255),
								textures(&texture_item01, 153, 255),
							    textures(&texture_item01, 154, 255),
							    textures(&texture_item01, 155, 255),
								textures(&texture_item01, 156, 255),
								textures(&texture_item01, 157, 255),
							    textures(&texture_item01, 158, 255),
							    textures(&texture_item01, 159, 255)
};
textures img_tanmac_poison_small[] = {textures(&texture_item01, 144, 255),
							    textures(&texture_item01, 145, 255),
							    textures(&texture_item01, 146, 255),
							    textures(&texture_item01, 147, 255),
								textures(&texture_item01, 148, 255),
							    textures(&texture_item01, 149, 255),
							    textures(&texture_item01, 150, 255),
							    textures(&texture_item01, 151, 255)
};

textures img_tanmac_air[] ={textures(&texture_item01, 184, 255),
								textures(&texture_item01, 185, 255),
							    textures(&texture_item01, 186, 255),
							    textures(&texture_item01, 187, 255),
								textures(&texture_item01, 188, 255),
								textures(&texture_item01, 189, 255),
							    textures(&texture_item01, 190, 255),
							    textures(&texture_item01, 191, 255)

};
textures img_tanmac_rock_small[] = {textures(&texture_item01, 192, 255),
								textures(&texture_item01, 193, 255),
							    textures(&texture_item01, 194, 255),
							    textures(&texture_item01, 195, 255),
								textures(&texture_item01, 196, 255),
								textures(&texture_item01, 197, 255),
							    textures(&texture_item01, 198, 255),
							    textures(&texture_item01, 199, 255)
};
textures img_tanmac_rock_big[] = {textures(&texture_item01, 200, 255),
								textures(&texture_item01, 201, 255),
							    textures(&texture_item01, 202, 255),
							    textures(&texture_item01, 203, 255),
								textures(&texture_item01, 204, 255),
								textures(&texture_item01, 205, 255),
							    textures(&texture_item01, 206, 255),
							    textures(&texture_item01, 207, 255)
};
textures img_tanmac_small[6][4] =
{
	{textures(&texture_laser, 36, 255),textures(&texture_laser, 37, 255),textures(&texture_laser, 38, 255), textures(&texture_laser, 39, 255)},
	{textures(&texture_laser, 40, 255),textures(&texture_laser, 41, 255),textures(&texture_laser, 42, 255), textures(&texture_laser, 43, 255)},
	{textures(&texture_laser, 44, 255),textures(&texture_laser, 45, 255),textures(&texture_laser, 46, 255), textures(&texture_laser, 47, 255)},
	{textures(&texture_laser, 48, 255),textures(&texture_laser, 49, 255),textures(&texture_laser, 50, 255), textures(&texture_laser, 51, 255)},
	{textures(&texture_laser, 52, 255),textures(&texture_laser, 53, 255),textures(&texture_laser, 54, 255), textures(&texture_laser, 55, 255)},
	{textures(&texture_laser, 56, 255),textures(&texture_laser, 57, 255),textures(&texture_laser, 58, 255), textures(&texture_laser, 59, 255)}
};
textures img_blizzard[] = {textures(&texture_item01, 215, 255),
							    textures(&texture_item01, 216, 255),
								textures(&texture_item01, 217, 255),
								textures(&texture_item01, 218, 255)};


textures img_fog_tonado[] = {textures(&texture_laser, 96, 255),
							    textures(&texture_laser, 97, 255),
								textures(&texture_laser, 98, 255),
								textures(&texture_laser, 99, 255)};
textures img_blast[] = {textures(&texture_laser, 100, 255),
							    textures(&texture_laser, 101, 255),
								textures(&texture_laser, 102, 255),
								textures(&texture_laser, 103, 255),
								textures(&texture_laser, 104, 255),
								textures(&texture_laser, 105, 255)};

textures img_fog_thunder[] = {textures(&texture_item01, 232, 255),
							    textures(&texture_item01, 233, 255),
								textures(&texture_item01, 234, 255),
								textures(&texture_item01, 235, 255)};


textures img_laser[] = {textures(&texture_laser, 0, 255),
							    textures(&texture_laser, 1, 255),
							    textures(&texture_laser, 2, 255),
							    textures(&texture_laser, 3, 255),
								textures(&texture_laser, 4, 255),
							    textures(&texture_laser, 5, 255),
							    textures(&texture_laser, 6, 255),
							    textures(&texture_laser, 7, 255),
								textures(&texture_laser, 8, 255),
								textures(&texture_laser, 9, 255),
							    textures(&texture_laser, 10, 255),
							    textures(&texture_laser, 11, 255),
								textures(&texture_laser, 12, 255),
								textures(&texture_laser, 13, 255),
							    textures(&texture_laser, 14, 255),
							    textures(&texture_laser, 15, 255),
								textures(&texture_laser, 16, 255),
							    textures(&texture_laser, 17, 255),
							    textures(&texture_laser, 18, 255),
							    textures(&texture_laser, 19, 255),
								textures(&texture_laser, 20, 255),
							    textures(&texture_laser, 21, 255),
							    textures(&texture_laser, 22, 255),
							    textures(&texture_laser, 23, 255),
								textures(&texture_laser, 24, 255),
								textures(&texture_laser, 25, 255),
							    textures(&texture_laser, 26, 255),
							    textures(&texture_laser, 27, 255),
								textures(&texture_laser, 28, 255),
								textures(&texture_laser, 29, 255),
							    textures(&texture_laser, 30, 255),
							    textures(&texture_laser, 31, 255)
};





textures img_thunder[] = {textures(&texture_laser, 64, 255),
							    textures(&texture_laser, 65, 255),
							    textures(&texture_laser, 66, 255),
							    textures(&texture_laser, 67, 255),
								textures(&texture_laser, 68, 255),
							    textures(&texture_laser, 69, 255),
							    textures(&texture_laser, 70, 255),
							    textures(&texture_laser, 71, 255),
								textures(&texture_laser, 72, 255),
								textures(&texture_laser, 73, 255),
							    textures(&texture_laser, 74, 255),
							    textures(&texture_laser, 75, 255),
								textures(&texture_laser, 76, 255),
								textures(&texture_laser, 77, 255),
							    textures(&texture_laser, 78, 255),
							    textures(&texture_laser, 79, 255),
								textures(&texture_laser, 80, 255),
							    textures(&texture_laser, 81, 255),
							    textures(&texture_laser, 82, 255),
							    textures(&texture_laser, 83, 255),
								textures(&texture_laser, 84, 255),
							    textures(&texture_laser, 85, 255),
							    textures(&texture_laser, 86, 255),
							    textures(&texture_laser, 87, 255),
								textures(&texture_laser, 88, 255),
								textures(&texture_laser, 89, 255),
							    textures(&texture_laser, 90, 255),
							    textures(&texture_laser, 91, 255),
								textures(&texture_laser, 92, 255),
								textures(&texture_laser, 93, 255),
							    textures(&texture_laser, 94, 255),
							    textures(&texture_laser, 95, 255)

};
textures img_laser_small[] = {
	textures(&texture_laser, 32, 255),
	textures(&texture_laser, 33, 255),
	textures(&texture_laser, 34, 255),
	textures(&texture_laser, 35, 255)
};

textures img_effect_autumn_leave[] = {
	textures(&texture_item01, 169, 255),
	textures(&texture_item01, 170, 255),
	textures(&texture_item01, 171, 255),
	textures(&texture_item01, 172, 255)
};




textures img_effect_rock_trap(&texture_item01, 183, 255);

textures img_effect_rock_uplift[] = {
	textures(&texture_item01, 208, 255),
	textures(&texture_item01, 209, 255),
	textures(&texture_item01, 210, 255),
	textures(&texture_item01, 211, 255),
	textures(&texture_item01, 212, 255)	
};

textures img_effect_emerald_uplift[] = {
	textures(&texture_item01, 237, 255),
	textures(&texture_item01, 238, 255)
};



textures img_effect_schema[] = {
	textures(&texture_monster01, 135, 255),
	textures(&texture_monster01, 136, 255),
	textures(&texture_monster01, 137, 255)
	
};


textures img_state_sleep(&texture_item01, 27, 255);
textures img_state_wardering(&texture_item01, 28, 255);
textures img_state_confuse(&texture_item01, 29, 255);
textures img_state_poison(&texture_item01, 30, 255);
textures img_state_paralysis(&texture_item01, 31, 255);
textures img_state_scary(&texture_item01, 32, 255);
textures img_state_ally(&texture_item01, 108, 255);
textures img_state_summon(&texture_item01, 109, 255);
textures img_state_haste(&texture_item01, 110, 255);
textures img_state_lunatic(&texture_item01, 219, 255);
textures img_state_slow(&texture_item01, 239, 255);

textures dot_floor(&texture_dot_floor, 0, 0, 3, 3, 255);
textures dot_wall(&texture_dot_wall, 0, 0, 3, 3, 255);
textures dot_monster(&texture_dot_monster, 0, 0, 3, 3, 255);
textures dot_player(&texture_dot_player, 0, 0, 3, 3, 255);
textures dot_up(&texture_dot_up, 0, 0, 3, 3, 255);
textures dot_down(&texture_dot_down, 0, 0, 3, 3, 255);
textures dot_item(&texture_dot_item, 0, 0, 3, 3, 255);
textures dot_door(&texture_dot_door, 0, 0, 3, 3, 255);
textures dot_temple(&texture_dot_temple, 0, 0, 3, 3, 255);
textures dot_sea(&texture_dot_sea, 0, 0, 3, 3, 255);
textures dot_mapping_floor(&texture_dot_mapping_floor, 0, 0, 3, 3, 255);
textures dot_mapping_wall(&texture_dot_mapping_wall, 0, 0, 3, 3, 255);
textures sight_rect(&texture_sight_rect, 0, 0, 64, 64, 255);



//-----------------------------------------------------------
//TextureFile 클래스
//-----------------------------------------------------------

//TextureFile 클래스의 생성자
TextureFile::TextureFile(LPCSTR _name)
{
	name = _name;
	pTexture = NULL;
}

//TextureFile 클래스의 소멸자
TextureFile::~TextureFile()
{
	d3d::Release(pTexture);  
}

//로딩
bool TextureFile::loading(IDirect3DDevice9* Device)
{
	if(FAILED(D3DXCreateTextureFromFile(Device,name,&pTexture)))
		return false;
	return true;
}

//로딩
bool TextureFile::loadingEX(IDirect3DDevice9* Device)
{
	if(FAILED(D3DXCreateTextureFromFileExA(Device,
		name,
		0,
		0,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, //2승수아니어도 제대로(이거 안쓰면 지포스가 아닌 컴에선 찌그러짐 조심)
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&pTexture
		)))
		return false;
	return true;
}

//-----------------------------------------------------------
//textures 클래스
//-----------------------------------------------------------

//textures 클래스의 생성자
textures::textures(TextureFile* _texture, int left, int top, int right, int bottom, int alphas)
{
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	alpha = alphas;
	texture = _texture;
}
textures::textures(TextureFile* _texture, int mon_num, int alphas)
{
	rect.left = (mon_num%16)*32;
	rect.top = (mon_num/16)*33;
	rect.right = (mon_num%16)*32+32;
	rect.bottom = (mon_num/16)*33+32;
	alpha = alphas;
	texture = _texture;
}

//textures 클래스의 소멸자
textures::~textures()
{
}

//드로우(배경)
bool textures::draw(LPD3DXSPRITE pSprite, int alphas)
{
	if(!texture)
		return true;
	D3DXVECTOR3 Pos(option_mg.getWidth()/2, option_mg.getHeight()/2, 0);
	D3DXVECTOR3 center((float)(rect.right-rect.left)/2, (float)(rect.bottom-rect.top)/2, 0);

	if(FAILED(pSprite->Draw(texture->pTexture, &rect, &center, &Pos, D3DCOLOR_RGBA(255,255,255,alphas))))
		return false;

	return true;
}

//드로우(위치)
bool textures::draw(LPD3DXSPRITE pSprite, float x, float y, int alphas)
{	
	if(!texture)
		return true;
	D3DXVECTOR3 Pos(x, y, 0);
	D3DXVECTOR3 center((float)(rect.right-rect.left)/2, (float)(rect.bottom-rect.top)/2, 0);

	if(FAILED(pSprite->Draw(texture->pTexture, &rect, &center, &Pos, D3DCOLOR_RGBA(255,255,255,alphas))))
		return false;

	return true;
}
//드로우(위치,색깔)
bool textures::draw(LPD3DXSPRITE pSprite, float x, float y, D3DCOLOR color)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, 1.0f, 1.0f, 0.0f, x, y, texture->pTexture,color);
	
	return true;
}

//드로우(위치, 회전)
bool textures::draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, int alphas)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, 1.0f, 1.0f, rotation, x, y, texture->pTexture,D3DCOLOR_RGBA(255,255,255,alphas));
	
	return true;
}


//드로우(위치, 회전, 크기)
bool textures::draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, float scale_x, float scale_y, int alphas)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, scale_x, scale_y, rotation, x, y, texture->pTexture,D3DCOLOR_RGBA(255,255,255,alphas));
	
	return true;
}

//드로우(위치, 회전, 크기,색깔)
bool textures::draw(LPD3DXSPRITE pSprite, float x, float y, float rotation, float scale_x, float scale_y, D3DCOLOR color)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, scale_x, scale_y, rotation, x, y, texture->pTexture,color);
	
	return true;
}


//드로우(배경, 특정 잘라쓰기)
bool textures::draw(LPD3DXSPRITE pSprite, RECT rc, int alphas)
{
	if(!texture)
		return true;
	D3DXVECTOR3 Pos(option_mg.getWidth()/2, option_mg.getHeight()/2, 0);
	D3DXVECTOR3 center((float)(rc.right-rc.left)/2, (float)(rc.bottom-rc.top)/2, 0);

	if(FAILED(pSprite->Draw(texture->pTexture, &rc, &center, &Pos, D3DCOLOR_RGBA(255,255,255,alphas))))
		return false;

	return true;
}


int texturetoint(textures* input)
{

	if(input == &img_mons_default)
		return 0;
	else if(input == &img_mons_reimu_yukkuri)
		return 1;
	else if(input == &img_play_reimu)
		return 2;
	else if(input == &img_item_armor_robe)
		return 3;
	else if(input == &img_item_armor_cloak)
		return 4;
	else if(input == &img_item_armor_robe_sanae)
		return 5;
	else if(input == &img_item_armor_glove)
		return 6;
	else if(input == &img_item_armor_boot)
		return 7;
	else if(input == &img_item_armor_helmet)
		return 8;
	else if(input == &img_item_weapon_dagger)
		return 9;
	else if(input == &img_item_food_bread)
		return 10;
	else if(input == &img_item_potion[0])
		return 11;
	else if(input == &img_item_scroll)
		return 12;
	else if(input == &img_item_ring)
		return 13;
	else if(input == &img_item_amulet)
		return 14;
	else if(input == &img_effect_select)
		return 15;
	else if(input == &img_tanmac_bill[1])
		return 16;
	else if(input == &img_tanmac_amulet[0])
		return 17;
	else if(input == &img_item_weapon_gohey)
		return 18;
	else if(input == &img_item_weapon_katana)
		return 19;
	else if(input == &img_item_weapon_scimitar)
		return 20;
	else if(input == &img_item_weapon_greatsword)
		return 21;
	else if(input == &img_item_weapon_broomstick)
		return 22;
	else if(input == &img_item_weapon_handaxe)
		return 23;
	else if(input == &img_item_weapon_battleaxe)
		return 24;
	else if(input == &img_item_weapon_anchor)
		return 25;
	else if(input == &img_item_weapon_spear)
		return 26;
	else if(input == &img_item_weapon_scythe)
		return 27;
	else if(input == &img_item_weapon_trident)
		return 28;
	else if(input == &img_item_weapon_smalllance)
		return 29;
	else if(input == &img_item_weapon_umbrella)
		return 30;
	else if(input == &img_item_weapon_knife)
		return 31;
	else if(input == &img_item_weapon_shortsword)
		return 32;
	else if(input == &img_item_weapon_gohey2)
		return 33;
	else if(input == &img_item_weapon_hammer)
		return 34;
	else if(input == &img_item_weapon_onbasira)
		return 35;
	else if(input == &img_item_weapon_roundshield)
		return 36;
	if(input == &img_item_weapon_shield)
		return 37;
	else if(input == &img_item_weapon_momizishield)
		return 38;
	else if(input == &img_item_weapon_kiteshield)
		return 39;
	else if(input == &img_mons_rat)
		return 40;
	else if(input == &img_mons_fairy_green)
		return 41;
	else if(input == &img_mons_fairy_blue)
		return 42;
	else if(input == &img_mons_fairy_red)
		return 43;
	else if(input == &img_mons_mook)
		return 44;
	else if(input == &img_mons_crow)
		return 45;
	else if(input == &img_mons_crane)
		return 46;
	else if(input == &img_mons_spider)
		return 47;
	else if(input == &img_mons_snake)
		return 48;
	else if(input == &img_mons_katpa)
		return 49;
	else if(input == &img_mons_katpa_gun)
		return 50;
	else if(input == &img_mons_fairy_green_warroir)
		return 51;
	else if(input == &img_mons_fairy_blue_magician)
		return 52;
	else if(input == &img_mons_fairy_red_commander)
		return 53;
	else if(input == &img_named_rumia)
		return 54;
	else if(input == &img_named_mistia)
		return 55;
	else if(input == &img_named_wriggle)
		return 56;
	else if(input == &img_named_cirno)
		return 57;
	else if(input == &img_item_food_p_item)
		return 58;
	else if(input == &img_fog_normal[0])
		return 59;
	else if(input == &img_fog_fire[0])
		return 60;
	else if(input == &img_fog_cold[0])
		return 61;
	else if(input == &img_fog_dark[0])
		return 62;
	else if(input == &img_fog_poison[0])
		return 63;
	else if(input == &img_fog_slow[0])
		return 64;
	else if(input == &img_mons_human_woman)
		return 65;
	else if(input == &img_mons_human_man)
		return 66;
	else if(input == &img_mons_human_yinyang)
		return 67;
	else if(input == &img_mons_human_priest)
		return 68;
	else if(input == &img_mons_human_samuri)
		return 69;
	else if(input == &img_mons_firefly)
		return 70;
	else if(input == &img_mons_butterfly)
		return 71;
	else if(input == &img_named_medicine)
		return 72;
	else if(input == &img_named_diefairy)
		return 73;
	else if(input == &img_tanmac_fire_big[1])
		return 74;
	else if(input == &img_tanmac_fire_small[1])
		return 75;
	else if(input == &img_tanmac_ice[0])
		return 76;
	else if(input == &img_tanmac_ice_small[0])
		return 77;
	else if(input == &img_item_goal)
		return 78;
	else if(input == &img_play_marisa)
		return 79;
	else if(input == &img_play_sanae)
		return 80;
	else if(input == &img_item_armor_armour_0)
		return 81;
	else if(input == &img_item_armor_armour_1)
		return 82;
	else if(input == &img_item_armor_armour_2)
		return 83;
	else if(input == &img_item_armor_armour_3)
		return 84;	
	else if(input == &img_item_book[0])
		return 85;
	else if(input == &img_tanmac_ice_small[0])
		return 86;
	else if(input == &img_mons_ghost[0])
		return 87;
	else if(input == &img_mons_ghost[1])
		return 88;
	else if(input == &img_mons_ghost[2])
		return 89;
	else if(input == &img_mons_bakekasa)
		return 90;
	else if(input == &img_mons_green_mook)
		return 91;
	else if(input == &img_mons_orange_mook)
		return 92;
	else if(input == &img_mons_gray_mook)
		return 93;
	else if(input == &img_mons_frog)
		return 94;
	else if(input == &img_mons_black_cat)
		return 95;
	else if(input == &img_mons_orange_cat)
		return 96;
	else if(input == &img_mons_white_cat)
		return 97;
	else if(input == &img_mons_crow_tengu)
		return 98;
	else if(input == &img_mons_oni)
		return 99;
	else if(input == &img_mons_marisa_yukkuri)
		return 100;
	else if(input == &img_mons_aya_yukkuri)
		return 101;
	else if(input == &img_named_kisume)
		return 102;
	else if(input == &img_named_chen)
		return 103;
	else if(input == &img_named_kogasa)
		return 104;
	else if(input == &img_named_sunny)
		return 105;
	else if(input == &img_named_lunar)
		return 106;
	else if(input == &img_named_star)
		return 107;
	else if(input == &img_tanmac_ice_big[0])
		return 108;
	else if(input == &img_tanmac_poison_big[0])
		return 109;
	else if(input == &img_mons_remila_yukkuri)
		return 110;
	else if(input == &img_mons_alice_yukkuri)
		return 111;
	else if(input == &img_mons_yamabiko)
		return 112;
	else if(input == &img_mons_katpa_spear)
		return 113;
	else if(input == &img_mons_katpa_water_wizard)
		return 114;
	else if(input == &img_mons_yamabush_tengu)
		return 115;
	else if(input == &img_mons_hanataca_tengu)
		return 116;
	else if(input == &img_mons_blue_oni)
		return 117;
	else if(input == &img_mons_mushroom)
		return 118;
	else if(input == &img_named_kyouko)
		return 119;
	else if(input == &img_named_momizi)
		return 120;
	else if(input == &img_named_aya)
		return 121;
	else if(input == &img_mons_new_kappa)
		return 122;
	else if(input == &img_mons_new_kappa_spear)
		return 123;
	else if(input == &img_mons_new_kappa_wizard)
		return 124;
	else if(input == &img_mons_test)
		return 125;
	else if(input == &img_mons_magic_book[0])
		return 126;
	else if(input == &img_mons_magic_book[1])
		return 127;
	else if(input == &img_mons_magic_book[2])
		return 128;
	else if(input == &img_mons_magic_book[3])
		return 129;
	else if(input == &img_mons_hobgobrin)
		return 130;
	else if(input == &img_mons_hobgobrin_maid)
		return 131;
	else if(input == &img_mons_hobgobrin_librarian)
		return 132;
	else if(input == &img_mons_hobgobrin_temp)
		return 133;
	else if(input == &img_mons_maid_fairy)
		return 134;
	else if(input == &img_mons_chuparcabra)
		return 135;
	else if(input == &img_mons_eagle)
		return 136;
	else if(input == &img_mons_tiger)
		return 137;
	else if(input == &img_mons_raijuu)
		return 138;
	else if(input == &img_mons_dragon_baby)
		return 139;
	else if(input == &img_mons_yamawaro_ninja)
		return 140;
	else if(input == &img_mons_yamawaro_warrior)
		return 141;
	else if(input == &img_mons_yamawaro_flag)
		return 142;
	else if(input == &img_named_wakasagi)
		return 143;
	else if(input == &img_named_yamame)
		return 144;
	else if(input == &img_named_nazrin)
		return 145;
	else if(input == &img_mons_dauzing)
		return 146;
	else if(input == &img_named_yosika)
		return 147;
	else if(input == &img_named_sekibanki)
		return 148;
	else if(input == &img_named_sekibanki_body)
		return 149;
	else if(input == &img_named_sekibanki_head)
		return 150;
	else if(input == &img_named_nitori)
		return 151;
	else if(input == &img_named_kagero)
		return 152;
	else if(input == &img_named_parsi)
		return 153;
	else if(input == &img_named_benben)
		return 154;
	else if(input == &img_named_yathasi)
		return 155;
	else if(input == &img_named_orin)
		return 156;
	else if(input == &img_named_orin_cat)
		return 157;
	else if(input == &img_mons_zombiefairy)
		return 158;
	else if(input == &img_named_ichirin)
		return 159;
	if(input == &img_named_unzan)
		return 160;
	else if(input == &img_named_unzan_punch[0])
		return 161;
	else if(input == &img_named_unzan_punch[1])
		return 162;
	else if(input == &img_named_unzan_punch[2])
		return 163;
	else if(input == &img_named_unzan_punch[3])
		return 164;
	else if(input == &img_named_pachu)
		return 165;
	else if(input == &img_named_koakuma)
		return 166;
	else if(input == &img_named_meirin)
		return 167;
	else if(input == &img_named_sakuya)
		return 168;
	else if(input == &img_named_remilia)
		return 169;
	else if(input == &img_named_kasen)
		return 170;
	else if(input == &img_effect_autumn_leave[0])
		return 171;
	else if(input == &img_effect_autumn_leave[1])
		return 172;
	else if(input == &img_effect_autumn_leave[2])
		return 173;
	else if(input == &img_effect_autumn_leave[3])
		return 174;
	else if(input == &img_item_autumn_armour[0])
		return 175;
	else if(input == &img_item_autumn_armour[1])
		return 176;
	else if(input == &img_item_autumn_armour[2])
		return 177;
	else if(input == &img_item_autumn_armour[3])
		return 178;
	else if(input == &img_item_autumn_armour[4])
		return 179;
	else if(input == &img_tanmac_air[0])
		return 180;
	else if(input == &img_tanmac_rock_small[0])
		return 181;
	else if(input == &img_mons_option)
		return 182;
	else if(input == &img_mons_golem)
		return 183;
	else if(input == &img_mons_onbasira)
		return 184;
	else if(input == &img_item_needle)
		return 185;
	else if(input == &img_item_kikuichi)
		return 186;
	else if(input == &img_item_spellcard)
		return 187;
	else if(input == &img_item_sweet_potato)
		return 188;	
	else if(input == &img_mons_red_ufo)
		return 189;
	else if(input == &img_mons_blue_ufo)
		return 190;
	else if(input == &img_mons_green_ufo)
		return 191;
	else if(input == &img_named_koishi)
		return 192;
	else if(input == &img_named_nue)
		return 193;
	else if(input == &img_mons_sanpei_fighter)
		return 194;
	else if(input == &img_mons_vamp_bat)
		return 195;
	else if(input == &img_mons_dagama)
		return 196;
	else if(input == &img_play_momizi)
		return 197;
	else if(input == &img_play_normal)
		return 198;
	else if(input == &img_tanmac_rock_big[0])
		return 199;
	else if(input == &img_effect_rock_trap)
		return 200;
	else if(input == &img_effect_rock_uplift[0])
		return 201;
	else if(input == &img_effect_rock_uplift[1])
		return 202;
	else if(input == &img_effect_rock_uplift[2])
		return 203;
	else if(input == &img_effect_rock_uplift[3])
		return 204;
	else if(input == &img_effect_rock_uplift[4])
		return 205;
	else if(input == &img_mons_rabit)
		return 206;
	else if(input == &img_mons_youkai_rabit)
		return 207;
	else if(input == &img_mons_namaz)
		return 208;
	else if(input == &img_mons_hell_crow)
		return 209;
	else if(input == &img_mons_raccoon)
		return 210;
	else if(input == &img_mons_lantern_youkai)
		return 211;
	else if(input == &img_mons_yinyan)
		return 212;
	else if(input == &img_mons_yugenmagan)
		return 213;
	else if(input == &img_mons_elise)
		return 214;
	else if(input == &img_mons_sariel)
		return 215;
	else if(input == &img_mons_sara)
		return 216;
	else if(input == &img_mons_louise)
		return 217;
	else if(input == &img_mons_yuki)
		return 218;
	else if(input == &img_mons_mai)
		return 219;
	else if(input == &img_mons_yumeko)
		return 220;
	else if(input == &img_mons_evil_eye)
		return 221;
	else if(input == &img_mons_little_imp)
		return 222;
	else if(input == &img_mons_schema_eye)
		return 223;
	else if(input == &img_effect_schema[0])
		return 224;
	else if(input == &img_effect_schema[1])
		return 225;
	else if(input == &img_effect_schema[2])
		return 226;	
	else if(input == &img_mons_bomb_rabbit)
		return 227;
	else if(input == &img_mons_spear_rabbit)
		return 228;
	else if(input == &img_mons_support_rabbit)
		return 229;
	else if(input == &img_mons_magic_rabbit)
		return 230;
	else if(input == &img_named_flandre)
		return 231;
	else if(input == &img_named_tewi)
		return 232;
	else if(input == &img_named_clownpiece)
		return 233;
	else if(input == &img_named_doremi)
		return 234;
	else if(input == &img_item_rune)
		return 235;
	else if(input == &img_blizzard[0])
		return 236;
	else if(input == &img_named_seiran)
		return 237;
	else if(input == &img_named_ringo)
		return 238;
	else if(input == &img_mons_fairy_green_hero)
		return 239;
	else if(input == &img_mons_fairy_green_socerer)
		return 240;
	else if(input == &img_mons_fairy_green_himawari)
		return 241;
	else if(input == &img_mons_moon_rabbit_attack)
		return 242;
	else if(input == &img_mons_moon_rabbit_supporter)
		return 243;
	else if(input == &img_mons_moon_rabbit_elite)
		return 244;
	else if(input == &img_mons_mac)
		return 245;
	else if(input == &img_mons_nightmare)
		return 246;
	else if(input == &img_mons_lunatic)
		return 247;
	else if(input == &img_mons_haunt[0])
		return 248;
	else if(input == &img_mons_haunt[1])
		return 249;
	else if(input == &img_mons_haunt[2])
		return 250;
	else if(input == &img_mons_fire_car)
		return 251;
	else if(input == &img_mons_hell_spider)
		return 252;
	else if(input == &img_mons_blood_haunt)
		return 253;
	else if(input == &img_mons_hell_dog)
		return 254;
	else if(input == &img_mons_flower_tank[0])
		return 255;
	else if(input == &img_mons_flower_tank[1])
		return 256;
	else if(input == &img_mons_evil_eye_tank)
		return 257;
	else if(input == &img_mons_snow_girl)
		return 258;
	else if(input == &img_named_letty)
		return 259;
	else if(input == &img_named_yorihime)
		return 260;
	else if(input == &img_named_toyohime)
		return 261;
	else if(input == &img_named_utsuho)
		return 262;
	else if(input == &img_named_suika)
		return 263;
	else if(input == &img_named_reimu)
		return 264;
	else if(input == &img_named_alice)
		return 265;
	else if(input == &img_named_udonge)
		return 266;
	else if(input == &img_named_kaguya)
		return 267;
	else if(input == &img_mons_nesi)
		return 268;
	else if(input == &img_mons_sanghai[0])
		return 269;
	else if(input == &img_mons_sanghai[1])
		return 270;
	else if(input == &img_mons_hourai[0])
		return 271;
	else if(input == &img_mons_hourai[1])
		return 272;
	else if(input == &img_play_yamame)
		return 273;
	else if(input == &img_play_mokou[0])
		return 274;
	else if(input == &img_play_mokou[1])
		return 275;
	else if(input == &img_play_mokou[2])
		return 276;	
	else if(input == &img_item_armor_relec)
		return 277;
	else if(input == &img_item_armor_rcold)
		return 278;
	else if(input == &img_item_armor_rfire)
		return 279;
	else if(input == &img_item_armor_rmagic)
		return 280;
	else if(input == &img_item_armor_rpois)
		return 281;
	if(input == &img_item_evo_pagoda)
		return 282;
	else if(input == &img_item_evo_air_scroll)
		return 283;
	else if(input == &img_item_evo_dream_soul)
		return 284;
	else if(input == &img_item_evo_hammer)
		return 285;	
	else if(input == &img_mons_youmu_yukkuri)
		return 286;		
	else if(input == &img_laser_small[0])
		return 287;	
	else if(input == &img_tanmac_small[0][0])
		return 288;
	else if(input == &img_tanmac_small[1][0])
		return 289;
	else if(input == &img_tanmac_small[2][0])
		return 290;
	else if(input == &img_tanmac_small[3][0])
		return 291;
	else if(input == &img_tanmac_small[4][0])
		return 292;
	else if(input == &img_tanmac_small[5][0])
		return 293;
	else if(input == &img_fog_tonado[0])
		return 294;
	else if(input == &img_blast[0])
		return 295;
	else if(input == &img_thunder[0])
		return 296;
	else if(input == &img_mons_tokiko)
		return 297;
	else if(input == &img_fog_thunder[0])
		return 298;
	else if(input == &img_item_potion[1])
		return 299;
	else if(input == &img_item_potion[2])
		return 300;
	else if(input == &img_item_potion[3])
		return 301;
	else if(input == &img_item_potion[4])
		return 302;
	else if(input == &img_item_potion[5])
		return 303;
	else if(input == &img_item_potion[6])
		return 304;
	else if(input == &img_item_potion[7])
		return 305;
	else if(input == &img_item_potion[8])
		return 306;
	else if(input == &img_item_potion[9])
		return 307;
	else if(input == &img_item_potion[10])
		return 308;
	else if(input == &img_item_potion[11])
		return 309;
	else if(input == &img_item_potion[12])
		return 310;
	else if(input == &img_item_potion[13])
		return 311;
	else if(input == &img_item_potion[14])
		return 312;
	else if(input == &img_item_potion[15])
		return 313;
	else if(input == &img_item_potion[16])
		return 314;
	else if(input == &img_item_potion[17])
		return 315;
	else if(input == &img_item_potion[18])
		return 316;
	else if(input == &img_item_potion[19])
		return 317;
	else if(input == &img_item_book[1])
		return 318;
	else if(input == &img_item_book[2])
		return 319;
	else if(input == &img_item_book[3])
		return 320;
	else if(input == &img_item_book[4])
		return 321;
	else if(input == &img_item_book[5])
		return 322;
	else if(input == &img_item_book[6])
		return 323;	
	else if(input == &img_mons_toziko)
		return 324;
	else if(input == &img_mons_futo)
		return 325;
	else if(input == &img_mons_mamizo)
		return 326;
	else if(input == &img_mons_seiga)
		return 327;
	else if(input == &img_effect_emerald_uplift[0])
		return 328;
	else if(input == &img_effect_emerald_uplift[1])
		return 329;
	else if (input == &img_named_murasa)
		return 330;
	else if (input == &img_named_keine)
		return 331;
	else if (input == &img_named_keine2)
		return 332;
	else if (input == &img_named_youmu)
		return 333;
	else if (input == &img_named_lyrica)
		return 334;
	else if (input == &img_named_merlin)
		return 335;
	else if (input == &img_named_lunasa)
		return 336;
	else if (input == &img_named_komachi)
		return 337;
	else if (input == &img_named_iku)
		return 338;
	else if (input == &img_named_larva)
		return 339;
	else if (input == &img_named_nemuno)
		return 340;
	else if (input == &img_named_aunn)
		return 341;
	else if (input == &img_named_narumi)
		return 342;
	else if (input == &img_named_mai)
		return 343;
	else if (input == &img_named_satono)
		return 344;
	else if (input == &img_named_kokoro[0])
		return 345;
	else if (input == &img_named_kokoro[1])
		return 346;
	else if (input == &img_named_kokoro[2])
		return 347;
	else if (input == &img_named_kokoro[3])
		return 348;
	else if (input == &img_named_sumireko)
		return 349;
	else if (input == &img_mons_anchor)
		return 350;
	else if (input == &img_mons_mask_angry)
		return 351;
	else if (input == &img_mons_mask_sad)
		return 352;
	else if (input == &img_mons_mask_happy)
		return 353;
	else if (input == &img_mons_trash[0])
		return 354;
	else if (input == &img_mons_trash[1])
		return 355;
	else if (input == &img_mons_trash[2])
		return 356;
	else if (input == &img_mons_trash[3])
		return 357;
	else if (input == &img_mons_occult_long)
		return 358;
	else if (input == &img_mons_occult_disk)
		return 359;
	else if (input == &img_mons_occult_small)
		return 360;
	else if (input == &img_mons_occult_kunekune)
		return 361;
	else if (input == &img_mons_close_door)
		return 362;	else
		return 0;
}


textures* inttotexture(int input)
{
	switch(input)
	{
	case 1:
		return &img_mons_reimu_yukkuri;
	case 2:
		return &img_play_reimu;
	case 3:
		return &img_item_armor_robe;
	case 4:
		return &img_item_armor_cloak;
	case 5:
		return &img_item_armor_robe_sanae;
	case 6:
		return &img_item_armor_glove;
	case 7:
		return &img_item_armor_boot;
	case 8:
		return &img_item_armor_helmet;
	case 9:
		return &img_item_weapon_dagger;
	case 10:
		return &img_item_food_bread;
	case 11:
		return &img_item_potion[0];
	case 12:
		return &img_item_scroll;
	case 13:
		return &img_item_ring;
	case 14:
		return &img_item_amulet;
	case 15:
		return &img_effect_select;
	case 16:
		return &img_tanmac_bill[1];
	case 17:
		return &img_tanmac_amulet[0];
	case 18:
		return &img_item_weapon_gohey;
	case 19:
		return &img_item_weapon_katana;
	case 20:
		return &img_item_weapon_scimitar;
	case 21:
		return &img_item_weapon_greatsword;
	case 22:
		return &img_item_weapon_broomstick;
	case 23:
		return &img_item_weapon_handaxe;
	case 24:
		return &img_item_weapon_battleaxe;
	case 25:
		return &img_item_weapon_anchor;
	case 26:
		return &img_item_weapon_spear;
	case 27:
		return &img_item_weapon_scythe;
	case 28:
		return &img_item_weapon_trident;
	case 29:
		return &img_item_weapon_smalllance;
	case 30:
		return &img_item_weapon_umbrella;
	case 31:
		return &img_item_weapon_knife;
	case 32:
		return &img_item_weapon_shortsword;
	case 33:
		return &img_item_weapon_gohey2;
	case 34:
		return &img_item_weapon_hammer;
	case 35:
		return &img_item_weapon_onbasira;
	case 36:
		return &img_item_weapon_roundshield;
	case 37:
		return &img_item_weapon_shield;
	case 38:
		return &img_item_weapon_momizishield;
	case 39:
		return &img_item_weapon_kiteshield;		
	case 40:
		return &img_mons_rat;
	case 41:
		return &img_mons_fairy_green;
	case 42:
		return &img_mons_fairy_blue;
	case 43:
		return &img_mons_fairy_red;
	case 44:
		return &img_mons_mook;
	case 45:
		return &img_mons_crow;
	case 46:
		return &img_mons_crane;
	case 47:
		return &img_mons_spider;
	case 48:
		return &img_mons_snake;
	case 49:
		return &img_mons_katpa;
	case 50:
		return &img_mons_katpa_gun;
	case 51:
		return &img_mons_fairy_green_warroir;
	case 52:
		return &img_mons_fairy_blue_magician;
	case 53:
		return &img_mons_fairy_red_commander;
	case 54:
		return &img_named_rumia;
	case 55:
		return &img_named_mistia;
	case 56:
		return &img_named_wriggle;
	case 57:
		return &img_named_cirno;
	case 58:
		return &img_item_food_p_item;
	case 59:
		return &img_fog_normal[0];
	case 60:
		return &img_fog_fire[0];
	case 61:
		return &img_fog_cold[0];
	case 62:
		return &img_fog_dark[0];
	case 63:
		return &img_fog_poison[0];
	case 64:
		return &img_fog_slow[0];
	case 65:
		return &img_mons_human_woman;
	case 66:
		return &img_mons_human_man;
	case 67:
		return &img_mons_human_yinyang;
	case 68:
		return &img_mons_human_priest;
	case 69:
		return &img_mons_human_samuri;
	case 70:
		return &img_mons_firefly;
	case 71:
		return &img_mons_butterfly;
	case 72:
		return &img_named_medicine;
	case 73:
		return &img_named_diefairy;
	case 74:
		return &img_tanmac_fire_big[0];
	case 75:
		return &img_tanmac_fire_small[0];
	case 76:
		return &img_tanmac_ice[0];
	case 77:
		return &img_tanmac_ice_small[0];
	case 78:
		return &img_item_goal;
	case 79:
		return &img_play_marisa;
	case 80:
		return &img_play_sanae;
	case 81:
		return &img_item_armor_armour_0;
	case 82:
		return &img_item_armor_armour_1;
	case 83:
		return &img_item_armor_armour_2;
	case 84:
		return &img_item_armor_armour_3;
	case 85:
		return &img_item_book[0];
	case 86:
		return &img_tanmac_ice_small[0];
	case 87:
		return &img_mons_ghost[0];
	case 88:
		return &img_mons_ghost[1];
	case 89:
		return &img_mons_ghost[2];
	case 90:
		return &img_mons_bakekasa;
	case 91:
		return &img_mons_green_mook;
	case 92:
		return &img_mons_orange_mook;
	case 93:
		return &img_mons_gray_mook;
	case 94:
		return &img_mons_frog;
	case 95:
		return &img_mons_black_cat;
	case 96:
		return &img_mons_orange_cat;
	case 97:
		return &img_mons_white_cat;
	case 98:
		return &img_mons_crow_tengu;
	case 99:
		return &img_mons_oni;
	case 100:
		return &img_mons_marisa_yukkuri;
	case 101:
		return &img_mons_aya_yukkuri;
	case 102:
		return &img_named_kisume;
	case 103:
		return &img_named_chen;
	case 104:
		return &img_named_kogasa;
	case 105:
		return &img_named_sunny;
	case 106:
		return &img_named_lunar;
	case 107:
		return &img_named_star;
	case 108:
		return &img_tanmac_ice_big[0];
	case 109:
		return &img_tanmac_poison_big[0];
	case 110:
		return &img_mons_remila_yukkuri;
	case 111:
		return &img_mons_alice_yukkuri;
	case 112:
		return &img_mons_yamabiko;
	case 113:
		return &img_mons_katpa_spear;
	case 114:
		return &img_mons_katpa_water_wizard;
	case 115:
		return &img_mons_yamabush_tengu;
	case 116:
		return &img_mons_hanataca_tengu;
	case 117:
		return &img_mons_blue_oni;
	case 118:
		return &img_mons_mushroom;
	case 119:
		return &img_named_kyouko;
	case 120:
		return &img_named_momizi;
	case 121:
		return &img_named_aya;
	case 122:
		return &img_mons_new_kappa;
	case 123:
		return &img_mons_new_kappa_spear;
	case 124:
		return &img_mons_new_kappa_wizard;
	case 125:
		return &img_mons_test;
	case 126:
		return &img_mons_magic_book[0];
	case 127:
		return &img_mons_magic_book[1];
	case 128:
		return &img_mons_magic_book[2];
	case 129:
		return &img_mons_magic_book[3];
	case 130:
		return &img_mons_hobgobrin;
	case 131:
		return &img_mons_hobgobrin_maid;
	case 132:
		return &img_mons_hobgobrin_librarian;
	case 133:
		return &img_mons_hobgobrin_temp;
	case 134:
		return &img_mons_maid_fairy;
	case 135:
		return &img_mons_chuparcabra;
	case 136:
		return &img_mons_eagle;
	case 137:
		return &img_mons_tiger;
	case 138:
		return &img_mons_raijuu;
	case 139:
		return &img_mons_dragon_baby;
	case 140:
		return &img_mons_yamawaro_ninja;
	case 141:
		return &img_mons_yamawaro_warrior;
	case 142:
		return &img_mons_yamawaro_flag;
	case 143:
		return &img_named_wakasagi;
	case 144:
		return &img_named_yamame;
	case 145:
		return &img_named_nazrin;
	case 146:
		return &img_mons_dauzing;
	case 147:
		return &img_named_yosika;
	case 148:
		return &img_named_sekibanki;
	case 149:
		return &img_named_sekibanki_body;
	case 150:
		return &img_named_sekibanki_head;
	case 151:
		return &img_named_nitori;
	case 152:
		return &img_named_kagero;
	case 153:
		return &img_named_parsi;
	case 154:
		return &img_named_benben;
	case 155:
		return &img_named_yathasi;
	case 156:
		return &img_named_orin;
	case 157:
		return &img_named_orin_cat;
	case 158:
		return &img_mons_zombiefairy;
	case 159:
		return &img_named_ichirin;
	case 160:
		return &img_named_unzan;
	case 161:
		return &img_named_unzan_punch[0];
	case 162:
		return &img_named_unzan_punch[1];
	case 163:
		return &img_named_unzan_punch[2];
	case 164:
		return &img_named_unzan_punch[3];
	case 165:
		return &img_named_pachu;
	case 166:
		return &img_named_koakuma;
	case 167:
		return &img_named_meirin;
	case 168:
		return &img_named_sakuya;
	case 169:
		return &img_named_remilia;
	case 170:
		return &img_named_kasen;
	case 171:
		return &img_effect_autumn_leave[0];
	case 172:
		return &img_effect_autumn_leave[1];
	case 173:
		return &img_effect_autumn_leave[2];
	case 174:
		return &img_effect_autumn_leave[3];
	case 175:
		return &img_item_autumn_armour[0];
	case 176:
		return &img_item_autumn_armour[1];
	case 177:
		return &img_item_autumn_armour[2];
	case 178:
		return &img_item_autumn_armour[3];
	case 179:
		return &img_item_autumn_armour[4];
	case 180:
		return &img_tanmac_air[0];
	case 181:
		return &img_tanmac_rock_small[0];
	case 182:
		return &img_mons_option;
	case 183:
		return &img_mons_golem;		
	case 184:
		return &img_mons_onbasira;
	case 185:
		return &img_item_needle;
	case 186:
		return &img_item_kikuichi;
	case  187:
		return &img_item_spellcard;
	case 188:
		return &img_item_sweet_potato;
	case 189:
		return &img_mons_red_ufo;
	case 190:
		return &img_mons_blue_ufo;
	case 191:
		return &img_mons_green_ufo;
	case 192:
		return &img_named_koishi;
	case 193:
		return &img_named_nue;
	case 194:
		return &img_mons_sanpei_fighter;
	case 195:
		return &img_mons_vamp_bat;
	case 196:
		return &img_mons_dagama;
	case 197:
		return &img_play_momizi;
	case 198:
		return &img_play_normal;		
	case 199:
		return &img_tanmac_rock_big[0];
	case 200:
		return &img_effect_rock_trap;
	case 201:
		return &img_effect_rock_uplift[0];
	case 202:
		return &img_effect_rock_uplift[1];
	case 203:
		return &img_effect_rock_uplift[2];
	case 204:
		return &img_effect_rock_uplift[3];
	case 205:
		return &img_effect_rock_uplift[4];
	case 206:
		return &img_mons_rabit;
	case 207:
		return &img_mons_youkai_rabit;
	case 208:
		return &img_mons_namaz;
	case 209:
		return &img_mons_hell_crow;
	case 210:
		return &img_mons_raccoon;
	case 211:
		return &img_mons_lantern_youkai;
	case 212:
		return &img_mons_yinyan;
	case 213:
		return &img_mons_yugenmagan;
	case 214:
		return &img_mons_elise;
	case 215:
		return &img_mons_sariel;
	case 216:
		return &img_mons_sara;
	case 217:
		return &img_mons_louise;
	case 218:
		return &img_mons_yuki;
	case 219:
		return &img_mons_mai;
	case 220:
		return &img_mons_yumeko;
	case 221:
		return &img_mons_evil_eye;
	case 222:
		return &img_mons_little_imp;
	case 223:
		return &img_mons_schema_eye;
	case 224:
		return &img_effect_schema[0];
	case 225:
		return &img_effect_schema[1];
	case 226:
		return &img_effect_schema[2];
	case 227:
		return &img_mons_bomb_rabbit;
	case 228:
		return &img_mons_spear_rabbit;
	case 229:
		return &img_mons_support_rabbit;
	case 230:
		return &img_mons_magic_rabbit;
	case 231:
		return &img_named_flandre;
	case 232:
		return &img_named_tewi;
	case 233:
		return &img_named_clownpiece;
	case 234:
		return &img_named_doremi;
	case 235:
		return &img_item_rune;
	case 236:
		return &img_blizzard[0];
	case 237:
		return &img_named_seiran;
	case 238:
		return &img_named_ringo;
	case 239:
		return &img_mons_fairy_green_hero;
	case 240:
		return &img_mons_fairy_green_socerer;
	case 241:
		return &img_mons_fairy_green_himawari;
	case 242:
		return &img_mons_moon_rabbit_attack;
	case 243:
		return &img_mons_moon_rabbit_supporter;
	case 244:
		return &img_mons_moon_rabbit_elite;
	case 245:
		return &img_mons_mac;
	case 246:
		return &img_mons_nightmare;
	case 247:
		return &img_mons_lunatic;
	case 248:
		return &img_mons_haunt[0];
	case 249:
		return &img_mons_haunt[1];
	case 250:
		return &img_mons_haunt[2];
	case 251:
		return &img_mons_fire_car;
	case 252:
		return &img_mons_hell_spider;
	case 253:
		return &img_mons_blood_haunt;
	case 254:
		return &img_mons_hell_dog;
	case 255:
		return &img_mons_flower_tank[0];
	case 256:
		return &img_mons_flower_tank[1];
	case 257:
		return &img_mons_evil_eye_tank;
	case 258:
		return &img_mons_snow_girl;
	case 259:
		return &img_named_letty;
	case 260:
		return &img_named_yorihime;
	case 261:
		return &img_named_toyohime;
	case 262:
		return &img_named_utsuho;
	case 263:
		return &img_named_suika;
	case 264:
		return &img_named_reimu;
	case 265:
		return &img_named_alice;
	case 266:
		return &img_named_udonge;
	case 267:
		return &img_named_kaguya;
	case 268:
		return &img_mons_nesi;
	case 269:
		return &img_mons_sanghai[0];
	case 270:
		return &img_mons_sanghai[1];
	case 271:
		return &img_mons_hourai[0];
	case 272:
		return &img_mons_hourai[1];
	case 273:
		return &img_play_yamame;
	case 274:
		return &img_play_mokou[0];
	case 275:
		return &img_play_mokou[1];
	case 276:
		return &img_play_mokou[2];		
	case 277:
		return &img_item_armor_relec;
	case 278:
		return &img_item_armor_rcold;
	case 279:
		return &img_item_armor_rfire;
	case 280:
		return &img_item_armor_rmagic;
	case 281:
		return &img_item_armor_rpois;
	case 282:
		return &img_item_evo_pagoda;
	case 283:
		return &img_item_evo_air_scroll;
	case 284:
		return &img_item_evo_dream_soul;
	case 285:	
		return &img_item_evo_hammer;
	case 286:	
		return &img_mons_youmu_yukkuri;
	case 287:
		return &img_laser_small[0];
	case 288:
		return &img_tanmac_small[0][0];
	case 289:
		return &img_tanmac_small[1][0];
	case 290:
		return &img_tanmac_small[2][0];
	case 291:
		return &img_tanmac_small[3][0];
	case 292:
		return &img_tanmac_small[4][0];
	case 293:
		return &img_tanmac_small[5][0];
	case 294:
		return &img_fog_tonado[0];
	case 295:
		return &img_blast[0];
	case 296:
		return &img_thunder[0];
	case 297:
		return &img_mons_tokiko;
	case 298:
		return &img_fog_thunder[0];		
	case 299:
		return &img_item_potion[1];
	case 300:
		return &img_item_potion[2];
	case 301:
		return &img_item_potion[3];
	case 302:
		return &img_item_potion[4];
	case 303:
		return &img_item_potion[5];
	case 304:
		return &img_item_potion[6];
	case 305:
		return &img_item_potion[7];
	case 306:
		return &img_item_potion[8];
	case 307:
		return &img_item_potion[9];
	case 308:
		return &img_item_potion[10];
	case 309:
		return &img_item_potion[11];
	case 310:
		return &img_item_potion[12];
	case 311:
		return &img_item_potion[13];
	case 312:
		return &img_item_potion[14];
	case 313:
		return &img_item_potion[15];
	case 314:
		return &img_item_potion[16];
	case 315:
		return &img_item_potion[17];
	case 316:
		return &img_item_potion[18];
	case 317:
		return &img_item_potion[19];		
	case 318:
		return &img_item_book[1];
	case 319:
		return &img_item_book[2];
	case 320:
		return &img_item_book[3];
	case 321:
		return &img_item_book[4];
	case 322:
		return &img_item_book[5];
	case 323:
		return &img_item_book[6];
	case 324:
		return &img_mons_toziko;
	case 325:
		return &img_mons_futo;
	case 326:
		return &img_mons_mamizo;
	case 327:
		return &img_mons_seiga;
	case 328:
		return &img_effect_emerald_uplift[0];
	case 329:
		return &img_effect_emerald_uplift[1];
	case 330:
		return &img_named_murasa;
	case 331:
		return &img_named_keine;
	case 332:
		return &img_named_keine2;
	case 333:
		return &img_named_youmu;
	case 334:
		return &img_named_lyrica;
	case 335:
		return &img_named_merlin;
	case 336:
		return &img_named_lunasa;
	case 337:
		return &img_named_komachi;
	case 338:
		return &img_named_iku;
	case 339:
		return &img_named_larva;
	case 340:
		return &img_named_nemuno;
	case 341:
		return &img_named_aunn;
	case 342:
		return &img_named_narumi;
	case 343:
		return &img_named_mai;
	case 344:
		return &img_named_satono;
	case 345:
		return &img_named_kokoro[0];
	case 346:
		return &img_named_kokoro[1];
	case 347:
		return &img_named_kokoro[2];
	case 348:
		return &img_named_kokoro[3];
	case 349:
		return &img_named_sumireko;
	case 350:
		return &img_mons_anchor;
	case 351:
		return &img_mons_mask_angry;
	case 352:
		return &img_mons_mask_sad;
	case 353:
		return &img_mons_mask_happy;
	case 354:
		return &img_mons_trash[0];
	case 355:
		return &img_mons_trash[1];
	case 356:
		return &img_mons_trash[2];
	case 357:
		return &img_mons_trash[3];
	case 358:
		return &img_mons_occult_long;
	case 359:
		return &img_mons_occult_disk;
	case 360:
		return &img_mons_occult_small;
	case 361:
		return &img_mons_occult_kunekune;
	case 362:
		return &img_mons_close_door;	default:
		return &img_mons_default;
	}
}


textures* statetotexture(monster_state_simple state_)
{
	switch(state_)
	{
	case MSS_SLEEP:
		return &img_state_sleep;
	case MSS_WANDERING:
		return &img_state_wardering;
	case MSS_CONFUSE:
		return &img_state_confuse;
	case MSS_POISON:
		return &img_state_poison;
	case MSS_SLOW:
		return &img_state_slow;
	case MSS_PARALYSE:
		return &img_state_paralysis;
	case MSS_SCARY:
		return &img_state_scary;
	case MSS_ALLY:
		return &img_state_ally;
	case MSS_SUMMON:
		return &img_state_summon;
	case MSS_HASTE:
		return &img_state_haste;
	case MSS_FEAR:
		return &img_state_scary;
	case MSS_LUNATIC:
		return &img_state_lunatic;
	default:
		return &img_state_sleep;
	}
}