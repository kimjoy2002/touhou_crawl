//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: zigurrat.cpp
//
// 내용: 지구랏
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "zigurrat.h"
#include "map.h"
#include "mon_infor.h"
#include "event.h"
#include "note.h"
#include "evoke.h"
#include "rect.h"



enum ziggrrat_type
{
	ZIGURRAT_FAIRY,
	ZIGURRAT_KAPPA_TENGU,
	ZIGURRAT_SCARLET,
	ZIGURRAT_BEAST,
	ZIGURRAT_DREAM,
	ZIGURRAT_HELL,
	ZIGURRAT_PANDEMONIUM,
	ZIGURRAT_HAKUREI,
	ZIGURRAT_MECANIC,
	ZIGURRAT_SOUL,
	ZIGURRAT_NAMED,
	ZIGURRAT_MAX
};





int getZigurratMonster(int ziggurat_level, int named_percent, int type) {
	random_extraction<int> monster_list;
	if (randA(99) < named_percent || type == ZIGURRAT_NAMED) {
		monster_list.push(MON_KYOUKO, 1);
		monster_list.push(MON_MISTIA, 1);
		monster_list.push(MON_KEGERO, 1);
		monster_list.push(MON_CLOWNPIECE, 1);
		monster_list.push(MON_LETTY, 1);
		monster_list.push(MON_CIRNO, 1);
		monster_list.push(MON_IKU, 1);
		monster_list.push(MON_ALICE, 1);
		monster_list.push(MON_YAMAME, 1);
		monster_list.push(MON_SUNNY, 1);
		monster_list.push(MON_LUNAR, 1);
		monster_list.push(MON_STAR, 1);
		monster_list.push(MON_KOMACHI, 1);
		return monster_list.pop();
	}


 	switch (type) {
	case ZIGURRAT_FAIRY:
		monster_list.push(MON_FAIRY_GREEN_WARRIOR, 5);
		monster_list.push(MON_FAIRY_BLUE_MAGICIAN, 5);
		monster_list.push(MON_FAIRY_HERO, 5);
		monster_list.push(MON_FAIRY_SOCERER, 5);
		monster_list.push(MON_FAIRY_SUN_FLOWER, 3);
		break;
	case ZIGURRAT_KAPPA_TENGU:
		monster_list.push(MON_KATPA_SPEAR, 5);
		monster_list.push(MON_KATPA_WATER_WIZARD, 5);
		monster_list.push(MON_YAMABUSH_TENGU, 8);
		monster_list.push(MON_HANATACA_TENGU, 8);
		monster_list.push(MON_SANPEI_FIGHTER, 3);
		break;
	case ZIGURRAT_SCARLET:
		monster_list.push(MON_HOBGOBRIN_LIBRARIAN, 8);
		monster_list.push(MON_HOBGOBRIN_TEMP, 8);
		monster_list.push(MON_HOBGOBRIN_MAID, 8);
		monster_list.push(MON_CHUPARCABRA, 5);
		monster_list.push(MON_VAMPIER_BAT, 5);
		break;
	case ZIGURRAT_BEAST:
		monster_list.push(MON_NAMAZ, 5);
		monster_list.push(MON_TIGER, 8);
		monster_list.push(MON_RAIJUU, 8);
		monster_list.push(MON_DRAGON_BABY, 3);
		monster_list.push(MON_EAGLE, 5);
		monster_list.push(MON_DEAGAMA, 5);
		break;
	case ZIGURRAT_DREAM:
		monster_list.push(MON_SHEEP, 7);
		monster_list.push(MON_MAC, 3);
		monster_list.push(MON_NIGHTMARE, 3);
		monster_list.push(MON_LUNATIC, 3);
		monster_list.push(MON_BLUE_UFO, 3);
		monster_list.push(MON_RED_UFO, 3);
		monster_list.push(MON_GREEN_UFO, 3);
		monster_list.push(MON_MOON_RABIT_ATTACK, 5);
		monster_list.push(MON_MOON_RABIT_SUPPORT, 3);
		monster_list.push(MON_MOON_RABIT_ELITE, 2);
		break;
	case ZIGURRAT_HELL:
		monster_list.push(MON_HELL_CROW, 5);
		monster_list.push(MON_VAMPIER_BAT, 5);
		monster_list.push(MON_HAUNT, 5);
		monster_list.push(MON_HELL_SPIDER, 5);
		monster_list.push(MON_HELL_HOUND, 5);
		monster_list.push(MON_LANTERN_YOUKAI, 3);
		monster_list.push(MON_BLOOD_HAUNT, 2);
		monster_list.push(MON_ONI, 3);
		monster_list.push(MON_FIRE_CAR, 3);
		break;
	case ZIGURRAT_PANDEMONIUM:
		monster_list.push(MON_SARA, 5);
		monster_list.push(MON_LUIZE, 5);
		monster_list.push(MON_ELIS, 5);
		monster_list.push(MON_NIGHTMARE, 2);
		monster_list.push(MON_YUKI, 3);
		monster_list.push(MON_MAI, 3);
		monster_list.push(MON_SARIEL, 3);
		monster_list.push(MON_YUUGENMAGAN, 3);
		monster_list.push(MON_FIRE_CAR, 3);
		break;
	case ZIGURRAT_HAKUREI:
		monster_list.push(MON_DRAGON_BABY, 8);
		monster_list.push(MON_FLOWER_TANK, 8);
		monster_list.push(MON_ONI, 5);
		monster_list.push(MON_BLUE_ONI, 5);
		monster_list.push(MON_SNOW_GIRL, 5);
		monster_list.push(MON_FIRE_CAR, 3);
		monster_list.push(MON_EVIL_EYE_TANK, 2);
		break;
	case ZIGURRAT_MECANIC:
		monster_list.push(MON_SANPEI_FIGHTER, 5);
		monster_list.push(MON_FLOWER_TANK, 10);
		monster_list.push(MON_EVIL_EYE_TANK, 2);
		monster_list.push(MON_BLUE_UFO, 4);
		monster_list.push(MON_RED_UFO, 4);
		monster_list.push(MON_GREEN_UFO, 4);
		monster_list.push(MON_CURIOSITY, 10);
		break;
	case ZIGURRAT_SOUL:
		monster_list.push(MON_DESIRE, 10);
		monster_list.push(MON_HAUNT, 10);
		monster_list.push(MON_LUNATIC, 4);
		monster_list.push(MON_NIGHTMARE, 4);
		monster_list.push(MON_BLOOD_HAUNT, 2); 
		break;
		
	}
	if (monster_list.GetSize() == 0)
		return MON_MOOK;
	else
		return monster_list.pop();
}

void addZigguratNamed(int num, int mon_id_, int x_, int y_, int level_)
{
	monster* mon_ = env[num].AddMonster(mon_id_, 0, coord_def(x_, y_));
	mon_->flag &= ~M_FLAG_UNIQUE;
	mon_->flag |= M_FLAG_NONE_STAIR;
	mon_->dream = true;
	int level_up_ = min(9, randA(max(0,level_ - mon_->level/2)));
	ostringstream oss;
	if (level_up_ > 0) {
		oss << "꿈의 주민 " << mon_->name.name.c_str() << "+" << level_up_;
	}
	else {
		oss << "꿈의 주민 " << mon_->name.name.c_str();
	}
	mon_->name = name_infor(oss.str(), mon_->name.name_type);
	while (level_up_ > 0) {
		mon_->LevelUpdown(2,6.0f,1.0f);
		level_up_--;
	}
}


void addZigguratMonsterInner(int num, int mon_id_, int x_, int y_)
{
	monster* mon_ = env[num].AddMonster(mon_id_, 0, coord_def(x_, y_));
}
int getZigguratType(int level)
{

	random_extraction<int> type_list;

	type_list.push(ZIGURRAT_FAIRY, 100);
	type_list.push(ZIGURRAT_KAPPA_TENGU, 100);
	type_list.push(ZIGURRAT_SCARLET, 100);
	type_list.push(ZIGURRAT_BEAST, 100);
	type_list.push(ZIGURRAT_DREAM, 50);
	type_list.push(ZIGURRAT_HELL, 50);
	type_list.push(ZIGURRAT_PANDEMONIUM, 50);
	type_list.push(ZIGURRAT_HAKUREI, 30);
	type_list.push(ZIGURRAT_MECANIC, 30);
	type_list.push(ZIGURRAT_SOUL, 30);
	type_list.push(ZIGURRAT_NAMED, 10);

	return type_list.pop();
}

void addZigguratMonster(int num, int x_, int y_, int monster_num)
{
	bool first_ = true;
	int type_ = getZigguratType(you.ziggurat_level);
	dif_rect_iterator rect_(coord_def(x_, y_), 7);

	while (!rect_.end() && monster_num > 0)
	{
		if (env[num].isMove((*rect_)))
		{

			int named_percent = randA(10+you.ziggurat_level);
			int mon_id_ = getZigurratMonster(you.ziggurat_level, named_percent, type_);
			if (first_ == true && you.ziggurat_level == 26) {
				//마지막 층에서는 도레킹이 고정
				mon_id_ = MON_DOREKING;
			}

			if (mon_id_ != MON_DOREKING && mondata[mon_id_].flag & M_FLAG_UNIQUE)
			{
				addZigguratNamed(num, mon_id_, rect_->x, rect_->y, 5+ you.ziggurat_level);
			}
			else {
				addZigguratMonsterInner(num, mon_id_, rect_->x, rect_->y);
			}
			monster_num--;
			first_ = false;
		}
		rect_++;
	}
}

void addZigguratItem(int num, int x_, int y_, int item_num)
{
	dif_rect_iterator rect_(coord_def(x_, y_), 7);

	while (!rect_.end() && item_num > 0)
	{
		if (env[num].isMove((*rect_)) &&
			env[num].dgtile[rect_->x][rect_->y].tile != DG_RETURN_STAIR &&
			env[num].dgtile[rect_->x][rect_->y].tile != DG_ZIGURRAT_STAIR &&
			env[num].GetPositiontoitem((*rect_)) == env[num].item_list.end()
			)
		{
			//아이템이 이 자리에 없을때~ 라는 조건이 필요함
			item_infor t;
			item* it = env[num].MakeItem((*rect_), CreateFloorItem(DEPTH_LEVEL, &t));
			item_num--;
		}
		rect_++;
	}

}
void map_algorithms_zigurrat(int num)
{
	int size_x = 4+ (you.ziggurat_level+1)/2, size_y = 3+ (you.ziggurat_level+1)/3;


	for (int x = 0; x < DG_MAX_X; x++)
	{
		for (int y = 0; y < DG_MAX_Y; y++)
		{
			float x_ = x - DG_MAX_X / 2;
			float y_ = y - DG_MAX_Y / 2;
			if ((x_*x_) / (size_x*size_x) + (y_*y_) / (size_y*size_y) < 1) {
				env[num].dgtile[x][y].tile = DG_DREAM_FLOOR;
			}
			else {
				env[num].dgtile[x][y].tile = DG_WALL2;
			}
		}
	}
	int x_ = DG_MAX_X / 2 - size_x + 2;
	int y_ = DG_MAX_Y / 2;

	int x2_ = DG_MAX_X / 2 + size_x - 2;
	int y2_ = DG_MAX_Y / 2;

	env[num].stair_up[0].x = x_ ;
	env[num].stair_up[0].y = y_;

	env[num].dgtile[x2_][y2_+1].tile = DG_RETURN_STAIR;
	env[num].dgtile[x2_][y2_-1].tile = DG_RETURN_STAIR;
	if (you.ziggurat_level < 26) {
		env[num].dgtile[x2_][y2_].tile = DG_ZIGURRAT_STAIR;
	}
	addZigguratMonster(num, x2_, y2_, 1+ (you.ziggurat_level)*(you.ziggurat_level/10+1) + randA(2+ you.ziggurat_level));
	addZigguratItem(num, x2_, y2_, 1 + (you.ziggurat_level * 2));
	you.ziggurat_level++;
}