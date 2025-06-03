//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sprint.cpp
//
// 내용: 스프린트
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "map.h"
#include "skill_use.h"
#include "mon_infor.h"
#include "book.h"
#include "rand_shuffle.h"
#include "tribe.h"
#include "event.h"
#include "note.h"
#include "evoke.h"
#include "armour.h"
#include "shooting_sprint.h"
#include "soundmanager.h"




void set_sprint_map(map_dummy* map_dummy_);

bool PixedMap(map_dummy* map, const char *temp);
void scrollup(bool down, int need_y);

deque<int> shooting_god_dq;
SHOOTING_STAGE_LEVEL current_base_level;


const shootingPathInfo left_straight(coord_def(DG_MAX_X/2-3, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo middle_straight(coord_def(DG_MAX_X/2, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo right_straight(coord_def(DG_MAX_X/2+3, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo one_straight(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo two_straight(coord_def(DG_MAX_X/2-2, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo three_straight(coord_def(DG_MAX_X/2+2, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});
const shootingPathInfo four_straight(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4});

const shootingPathInfo left_straight_back(coord_def(DG_MAX_X/2-3, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo middle_straight_back(coord_def(DG_MAX_X/2, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo right_straight_back(coord_def(DG_MAX_X/2+3, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo one_straight_back(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo two_straight_back(coord_def(DG_MAX_X/2-2, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo three_straight_back(coord_def(DG_MAX_X/2+2, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo four_straight_back(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2+7), {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});

const shootingPathInfo left_straight_stopandgo(coord_def(DG_MAX_X/2-3, DG_MAX_Y/2-7),  {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo middle_straight_stopandgo(coord_def(DG_MAX_X/2, DG_MAX_Y/2-7) , {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo right_straight_stopandgo(coord_def(DG_MAX_X/2+3, DG_MAX_Y/2-7), {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo one_straight_stopandgo(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2-7),   {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo two_straight_stopandgo(coord_def(DG_MAX_X/2-2, DG_MAX_Y/2-7),   {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo three_straight_stopandgo(coord_def(DG_MAX_X/2+2, DG_MAX_Y/2-7), {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});
const shootingPathInfo four_straight_stopandgo(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2-7),  {4,4,4,4,4,8,8,8,8,8,8,8,8,8,8,8,8,8});


const shootingPathInfo left_immediately(coord_def(DG_MAX_X/2-3, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo middle_immediately(coord_def(DG_MAX_X/2, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo right_immediately(coord_def(DG_MAX_X/2+3, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo one_immediately(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo two_immediately(coord_def(DG_MAX_X/2-2, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo three_immediately(coord_def(DG_MAX_X/2+2, DG_MAX_Y/2-7), {4,4,4,4,4});
const shootingPathInfo four_immediately(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2-7), {4,4,4,4,4});




const shootingPathInfo left_U_turn(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,3,3,3,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0});
const shootingPathInfo right_U_turn(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2-7), {4,4,4,4,4,4,4,4,4,5,5,5,6,6,7,7,7,0,0,0,0,0,0,0,0,0,0});

const shootingPathInfo left_X_turn(coord_def(DG_MAX_X/2-4, DG_MAX_Y/2-7),  {3,3,3,3,3,3,3,3,4,4,5,5,6,6,6,6,7,0,0,0,1,1,1,1,1,1,1,1,1});
const shootingPathInfo right_X_turn(coord_def(DG_MAX_X/2+4, DG_MAX_Y/2-7), {5,5,5,5,5,5,5,5,4,4,4,3,2,2,2,2,1,1,7,0,0,7,7,7,7,7,7,7,7,7});

const vector<shootingLineTemplate> shootinglines = {
shootingLineTemplate(30, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_straight),
	stUnit(3, SHT_MON_WEAK, &left_straight),
	stUnit(6, SHT_MON_WEAK, &left_straight),
	stUnit(9, SHT_MON_WEAK, &left_straight),
	stUnit(12, SHT_MON_WEAK, &left_straight),
	stUnit(15, SHT_MON_WEAK, &left_straight),
	stUnit(18, SHT_MON_WEAK, &left_straight),
	stUnit(21, SHT_MON_STRONG, &left_straight, true)
})
,shootingLineTemplate(30, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_straight),
	stUnit(3, SHT_MON_WEAK, &right_straight),
	stUnit(6, SHT_MON_WEAK, &right_straight),
	stUnit(9, SHT_MON_WEAK, &right_straight),
	stUnit(12, SHT_MON_WEAK, &right_straight),
	stUnit(15, SHT_MON_WEAK, &right_straight),
	stUnit(18, SHT_MON_WEAK, &right_straight),
	stUnit(21, SHT_MON_STRONG, &right_straight, true)
})
,shootingLineTemplate(30, 0, SHT_STAGE_2, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_straight_back),
	stUnit(3, SHT_MON_WEAK, &left_straight_back),
	stUnit(6, SHT_MON_WEAK, &left_straight_back),
	stUnit(9, SHT_MON_WEAK, &left_straight_back),
	stUnit(12, SHT_MON_WEAK, &left_straight_back),
	stUnit(15, SHT_MON_WEAK, &left_straight_back),
	stUnit(18, SHT_MON_WEAK, &left_straight_back),
	stUnit(21, SHT_MON_STRONG, &left_straight_back, true)
})
,shootingLineTemplate(30, 0, SHT_STAGE_2, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_straight_back),
	stUnit(3, SHT_MON_WEAK, &right_straight_back),
	stUnit(6, SHT_MON_WEAK, &right_straight_back),
	stUnit(9, SHT_MON_WEAK, &right_straight_back),
	stUnit(12, SHT_MON_WEAK, &right_straight_back),
	stUnit(15, SHT_MON_WEAK, &right_straight_back),
	stUnit(18, SHT_MON_WEAK, &right_straight_back),
	stUnit(21, SHT_MON_STRONG, &right_straight_back, true)
})
,shootingLineTemplate(25, 100, SHT_STAGE_2, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK_RANGE, &left_straight),
	stUnit(0, SHT_MON_WEAK_RANGE, &right_straight),
	stUnit(0, SHT_MON_WEAK, &middle_straight_back),
	stUnit(3, SHT_MON_WEAK_RANGE, &left_straight),
	stUnit(3, SHT_MON_WEAK_RANGE, &right_straight),
	stUnit(3, SHT_MON_WEAK, &middle_straight_back),
	stUnit(6, SHT_MON_WEAK_RANGE, &left_straight),
	stUnit(6, SHT_MON_WEAK_RANGE, &right_straight),
	stUnit(6, SHT_MON_WEAK, &middle_straight_back),
	stUnit(9, SHT_MON_WEAK_RANGE, &left_straight),
	stUnit(9, SHT_MON_WEAK_RANGE, &right_straight),
	stUnit(9, SHT_MON_STRONG, &middle_straight_back, true)
})
,shootingLineTemplate(20, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK_RANGE, &two_straight),
	stUnit(4, SHT_MON_WEAK_RANGE, &two_straight),
	stUnit(8, SHT_MON_WEAK_RANGE, &two_straight),
	stUnit(12, SHT_MON_WEAK_RANGE, &two_straight, true)
})
,shootingLineTemplate(20, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK_RANGE, &three_straight),
	stUnit(4, SHT_MON_WEAK_RANGE, &three_straight),
	stUnit(8, SHT_MON_WEAK_RANGE, &three_straight),
	stUnit(12, SHT_MON_WEAK_RANGE, &three_straight, true)
})
,shootingLineTemplate(25, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK_RANGE, &one_straight_stopandgo),
	stUnit(0, SHT_MON_WEAK_RANGE, &two_straight_stopandgo),
	stUnit(0, SHT_MON_WEAK_RANGE, &middle_straight_stopandgo),
	stUnit(0, SHT_MON_WEAK_RANGE, &three_straight_stopandgo),
	stUnit(0, SHT_MON_WEAK_RANGE, &four_straight_stopandgo)
})
,shootingLineTemplate(25, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK_RANGE, &middle_straight_stopandgo),
	stUnit(5, SHT_MON_WEAK_RANGE, &three_straight_stopandgo),
	stUnit(5, SHT_MON_WEAK_RANGE, &two_straight_stopandgo),
	stUnit(10, SHT_MON_WEAK_RANGE, &one_straight_stopandgo),
	stUnit(10, SHT_MON_WEAK_RANGE, &four_straight_stopandgo)
})
,shootingLineTemplate(40,100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_STRONG_RANGE, &one_straight_stopandgo, true),
	stUnit(20, SHT_MON_STRONG_RANGE, &four_straight_stopandgo, true)
})
,shootingLineTemplate(40, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_STRONG_RANGE, &one_straight_stopandgo, true),
	stUnit(6, SHT_MON_WEAK, &right_U_turn),
	stUnit(9, SHT_MON_WEAK, &right_U_turn),
	stUnit(12, SHT_MON_WEAK, &right_U_turn),
	stUnit(15, SHT_MON_WEAK, &right_U_turn),
	stUnit(18, SHT_MON_WEAK, &right_U_turn)
})
,shootingLineTemplate(35, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_X_turn),
	stUnit(3, SHT_MON_WEAK, &left_X_turn),
	stUnit(6, SHT_MON_WEAK, &left_X_turn),
	stUnit(7, SHT_MON_STRONG_RANGE, &middle_straight_stopandgo, true),
	stUnit(9, SHT_MON_WEAK, &left_X_turn),
	stUnit(12, SHT_MON_WEAK, &left_X_turn),
	stUnit(15, SHT_MON_WEAK, &left_X_turn)
})
,shootingLineTemplate(40, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_STRONG_RANGE, &four_straight_stopandgo, true),
	stUnit(6, SHT_MON_WEAK, &left_U_turn),
	stUnit(9, SHT_MON_WEAK, &left_U_turn),
	stUnit(12, SHT_MON_WEAK, &left_U_turn),
	stUnit(15, SHT_MON_WEAK, &left_U_turn),
	stUnit(18, SHT_MON_WEAK, &left_U_turn)
})
,shootingLineTemplate(30, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_straight),
	stUnit(3, SHT_MON_WEAK, &right_straight),
	stUnit(6, SHT_MON_WEAK, &right_straight),
	stUnit(9, SHT_MON_WEAK, &right_straight),
	stUnit(12, SHT_MON_WEAK, &right_straight),
	stUnit(15, SHT_MON_WEAK, &right_straight),
	stUnit(18, SHT_MON_WEAK, &right_straight),
	stUnit(21, SHT_MON_STRONG, &right_straight, true)
})
,shootingLineTemplate(40, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &one_straight),
	stUnit(3, SHT_MON_WEAK, &one_straight),
	stUnit(6, SHT_MON_WEAK, &one_straight),
	stUnit(6, SHT_MON_WEAK, &two_straight),
	stUnit(9, SHT_MON_WEAK, &two_straight),
	stUnit(12, SHT_MON_WEAK, &two_straight),
	stUnit(12, SHT_MON_WEAK, &middle_straight),
	stUnit(15, SHT_MON_WEAK, &middle_straight),
	stUnit(18, SHT_MON_WEAK, &middle_straight),
	stUnit(18, SHT_MON_WEAK, &three_straight),
	stUnit(21, SHT_MON_WEAK, &three_straight),
	stUnit(24, SHT_MON_WEAK, &three_straight),
	stUnit(24, SHT_MON_WEAK, &four_straight),
	stUnit(27, SHT_MON_WEAK, &four_straight),
	stUnit(30, SHT_MON_WEAK, &four_straight)
})
,shootingLineTemplate(50, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_U_turn),
	stUnit(3, SHT_MON_WEAK, &left_U_turn),
	stUnit(6, SHT_MON_WEAK, &left_U_turn),
	stUnit(9, SHT_MON_WEAK, &left_U_turn),
	stUnit(12, SHT_MON_WEAK, &left_U_turn),
	stUnit(15, SHT_MON_WEAK, &left_U_turn),
	stUnit(18, SHT_MON_WEAK, &left_U_turn),
	stUnit(21, SHT_MON_WEAK, &left_U_turn),
	stUnit(24, SHT_MON_WEAK, &left_U_turn),
	stUnit(27, SHT_MON_WEAK, &left_U_turn),
	stUnit(30, SHT_MON_STRONG, &left_U_turn, true)
})
,shootingLineTemplate(50, 0, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_U_turn),
	stUnit(3, SHT_MON_WEAK, &right_U_turn),
	stUnit(6, SHT_MON_WEAK, &right_U_turn),
	stUnit(9, SHT_MON_WEAK, &right_U_turn),
	stUnit(12, SHT_MON_WEAK, &right_U_turn),
	stUnit(15, SHT_MON_WEAK, &right_U_turn),
	stUnit(18, SHT_MON_WEAK, &right_U_turn),
	stUnit(21, SHT_MON_WEAK, &right_U_turn),
	stUnit(24, SHT_MON_WEAK, &right_U_turn),
	stUnit(27, SHT_MON_WEAK, &right_U_turn),
	stUnit(30, SHT_MON_STRONG, &right_U_turn, true)
})
,shootingLineTemplate(50, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_X_turn),
	stUnit(3, SHT_MON_WEAK, &right_X_turn),
	stUnit(6, SHT_MON_WEAK, &left_X_turn),
	stUnit(9, SHT_MON_WEAK, &right_X_turn),
	stUnit(12, SHT_MON_WEAK, &left_X_turn),
	stUnit(15, SHT_MON_WEAK, &right_X_turn),
	stUnit(18, SHT_MON_WEAK, &left_X_turn),
	stUnit(21, SHT_MON_WEAK, &right_X_turn),
	stUnit(24, SHT_MON_WEAK, &left_X_turn),
	stUnit(27, SHT_MON_WEAK, &right_X_turn),
	stUnit(30, SHT_MON_STRONG, &left_X_turn, true),
	stUnit(33, SHT_MON_STRONG, &right_X_turn, true)
})
,shootingLineTemplate(25, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_straight),
	stUnit(0, SHT_MON_WEAK, &left_straight),
	stUnit(3, SHT_MON_WEAK, &right_straight),
	stUnit(3, SHT_MON_WEAK, &left_straight),
	stUnit(6, SHT_MON_WEAK, &right_straight),
	stUnit(6, SHT_MON_WEAK, &left_straight),
	stUnit(9, SHT_MON_WEAK, &right_straight),
	stUnit(9, SHT_MON_WEAK, &left_straight),
	stUnit(12, SHT_MON_WEAK, &right_straight),
	stUnit(12, SHT_MON_WEAK, &left_straight),
	stUnit(15, SHT_MON_STRONG, &left_straight, true),
	stUnit(15, SHT_MON_STRONG, &right_straight, true)
})
,shootingLineTemplate(30, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &right_straight),
	stUnit(0, SHT_MON_WEAK_RANGE, &left_U_turn),
	stUnit(3, SHT_MON_WEAK, &right_straight),
	stUnit(3, SHT_MON_WEAK_RANGE, &left_U_turn),
	stUnit(6, SHT_MON_WEAK, &right_straight),
	stUnit(6, SHT_MON_WEAK_RANGE, &left_U_turn),
	stUnit(9, SHT_MON_WEAK, &right_straight),
	stUnit(9, SHT_MON_WEAK_RANGE, &left_U_turn),
	stUnit(12, SHT_MON_STRONG, &right_straight, true)
})
,shootingLineTemplate(30, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &left_straight),
	stUnit(0, SHT_MON_WEAK_RANGE, &right_U_turn),
	stUnit(3, SHT_MON_WEAK, &left_straight),
	stUnit(3, SHT_MON_WEAK_RANGE, &right_U_turn),
	stUnit(6, SHT_MON_WEAK, &left_straight),
	stUnit(6, SHT_MON_WEAK_RANGE, &right_U_turn),
	stUnit(9, SHT_MON_WEAK, &left_straight),
	stUnit(9, SHT_MON_WEAK_RANGE, &right_U_turn),
	stUnit(12, SHT_MON_STRONG, &left_straight, true)
})
,shootingLineTemplate(25, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_NORMAL, &left_immediately),
	stUnit(15, SHT_MON_NORMAL, &right_immediately, true)
})
,shootingLineTemplate(25, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(15, SHT_MON_NORMAL, &right_immediately),
	stUnit(0, SHT_MON_NORMAL, &left_immediately, true)
})
,shootingLineTemplate(25, 100, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &one_immediately),
	stUnit(0, SHT_MON_WEAK, &two_immediately),
	stUnit(0, SHT_MON_NORMAL, &middle_immediately, true),
	stUnit(0, SHT_MON_WEAK, &three_immediately),
	stUnit(0, SHT_MON_WEAK, &four_immediately)
})
,shootingLineTemplate(20, 250, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_NORMAL_STRONG, &middle_immediately, true)
})
,shootingLineTemplate(20, 250, SHT_STAGE_1, SHT_STAGE_END,
{
	stUnit(0, SHT_MON_WEAK, &two_immediately),
	stUnit(0, SHT_MON_WEAK, &middle_immediately),
	stUnit(0, SHT_MON_WEAK, &three_immediately),
	stUnit(3, SHT_MON_WEAK, &two_immediately),
	stUnit(3, SHT_MON_NORMAL_STRONG, &middle_immediately, true),
	stUnit(3, SHT_MON_WEAK, &three_immediately),
	stUnit(6, SHT_MON_WEAK, &two_immediately),
	stUnit(6, SHT_MON_WEAK, &middle_immediately),
	stUnit(6, SHT_MON_WEAK, &three_immediately)
})
};





random_extraction<pair<item_type,int>> rand_stage[6];

void addToRandomStage(int min, int max, int num, item_type type, int value, int percent = 1) {
	//스테이지에 골고루 분산시키기
	
	random_extraction<int> able_stage;
	for(int i = 0; i<6; i++) {
		if(i >= min && i <= max) {
			able_stage.push(i);
		}
	}

	for(int i = 0;i < num; i++) {
		rand_stage[able_stage.choice()].push(make_pair(type, value), percent);
	}
}


void shooting_reward_random_init()
{
	for(int i = 0; i< 6; i++)
		rand_stage[i].clear();

	//필수 소모품들
	addToRandomStage(0, 3, rand_int(6,8), ITM_POTION, PT_HEAL,2);
	addToRandomStage(0, 3, rand_int(6,8), ITM_POTION, PT_HEAL_WOUND,2);
	addToRandomStage(4, 5, rand_int(1,2), ITM_POTION, PT_HEAL_WOUND);
	addToRandomStage(0, 4, rand_int(3,5), ITM_POTION, PT_MIGHT,2);
	addToRandomStage(0, 4, rand_int(3,5), ITM_POTION, PT_CLEVER);
	addToRandomStage(0, 4, rand_int(3,5), ITM_POTION, PT_AGILITY);
	addToRandomStage(0, 4, rand_int(3,5), ITM_POTION, PT_HASTE);
	addToRandomStage(0, 4, rand_int(3,5), ITM_POTION, PT_RECOVER_STAT);
	addToRandomStage(0, 4, rand_int(1,3), ITM_POTION, PT_MAGIC);

	addToRandomStage(1, 5, rand_int(3,5), ITM_SCROLL, SCT_BLINK);
	addToRandomStage(1, 5, rand_int(1,2), ITM_SCROLL, SCT_SILENCE);
	addToRandomStage(1, 5, rand_int(1,2), ITM_SCROLL, SCT_FOG);
	addToRandomStage(1, 5, 1, ITM_SCROLL, SCT_SANTUARY);
	addToRandomStage(0, 4, rand_int(6,9), ITM_SCROLL, SCT_ENCHANT_ARMOUR);
	addToRandomStage(0, 4, rand_int(6,9), ITM_SCROLL, SCT_ENCHANT_WEAPON_1);
	addToRandomStage(1, 5, rand_int(1,2), ITM_SCROLL, SCT_SOUL_SHOT);
	addToRandomStage(2, 5, 2, ITM_SCROLL, SCT_BRAND_WEAPON);

	//초반에 필요한 저항들
	addToRandomStage(0, 2, 1, ITM_RING, RGT_ELEC_RESIS,3);
	addToRandomStage(0, 2, 1, ITM_RING, RGT_FIRE_RESIS,3);
	addToRandomStage(0, 2, 1, ITM_RING, RGT_ICE_RESIS,3);
	addToRandomStage(0, 2, 1, ITM_RING, RGT_POISON_RESIS,3);
	addToRandomStage(0, 2, 1, ITM_RING, RGT_SEE_INVISIBLE,3);

	//아마 방어구
	addToRandomStage(0, 4, 1, ITM_ARMOR_HEAD, -1, 3);
	addToRandomStage(0, 4, 1, ITM_ARMOR_CLOAK, -1, 3);
	addToRandomStage(0, 4, 1, ITM_ARMOR_GLOVE, -1, 3);
	addToRandomStage(0, 4, 1, ITM_ARMOR_BOOT, -1, 3);

	//발동템(하나씩)
	addToRandomStage(1, 5, 1, ITM_MISCELLANEOUS, EVK_PAGODA);
	addToRandomStage(2, 5, 1, ITM_MISCELLANEOUS, EVK_AIR_SCROLL);
	addToRandomStage(1, 5, 1, ITM_MISCELLANEOUS, EVK_BOMB);
	addToRandomStage(3, 5, 1, ITM_MISCELLANEOUS, EVK_GHOST_BALL);

	//탄막
	addToRandomStage(0, 2, 3, ITM_THROW_TANMAC, TMT_AMULET);
	addToRandomStage(0, 1, 3, ITM_THROW_TANMAC, TMT_POISON_NEEDLE);
	addToRandomStage(0, 3, 2, ITM_THROW_TANMAC, TMT_KIKU_COMPRESSER);
	addToRandomStage(1, 3, 2, ITM_THROW_TANMAC, TMT_DOGGOJEO);


	for(int i = ITM_WEAPON_FIRST; i<= ITM_WEAPON_CLOSE; i++) {
		//무기별 3개씩만, 좋은 효과 줘서
		for(int j = 0; j < 3; j++) {
			addToRandomStage(0, 5, 3, (item_type )i, -1);
		}
	}

	for(int i = ITM_ARMOR_BODY_FIRST; i<= ITM_ARMOR_BODY_LAST; i++) {
		//방어구도 3개씩만, 좋은 효과 줘서
		for(int j = 0; j < 3; j++) {
			addToRandomStage(0, 5, 3, (item_type )i, -1);
		}
	}

	addToRandomStage(2, 2, 2, (item_type )rand_int(ITM_WEAPON_FIRST, ITM_WEAPON_CLOSE), -2); //초반용 무기 아티팩트
	addToRandomStage(2, 2, 1, ITM_RING, -2); //초반용 반지 아티팩트
	addToRandomStage(2, 2, 1,  (item_type )rand_int(ITM_ARMOR_BODY_FIRST, ITM_ARMOR_BODY_LAST-1), -2); //초반용 갑옷 아티팩트

	addToRandomStage(3, 5, 2, (item_type )rand_int(ITM_WEAPON_FIRST, ITM_WEAPON_CLOSE), -2); //후반 무기 아티팩트
	addToRandomStage(3, 5, 3, ITM_RING, -2); //후반용 반지 아티팩트
	addToRandomStage(3, 5, 3,  (item_type )rand_int(ITM_ARMOR_BODY_FIRST, ITM_ARMOR_BODY_LAST-1), -2); //후반 갑옷 아티팩트
	addToRandomStage(3, 5, 3,  (item_type )rand_int(ITM_ARMOR_HEAD, ITM_ARMOR_BOOT), -2); //후반 갑옷 아티팩트


	
	//나오면 좋은 반지들
	random_extraction<int> able_ring;
	able_ring.push(RGT_STR);
	able_ring.push(RGT_DEX);
	able_ring.push(RGT_INT);
	able_ring.push(RGT_INVISIBLE);
	able_ring.push(RGT_MANA);
	able_ring.push(RGT_MAGACIAN);
	able_ring.push(RGT_AC);
	able_ring.push(RGT_AC);
	able_ring.push(RGT_EV);
	able_ring.push(RGT_EV);
	able_ring.push(RGT_CONFUSE_RESIS);
	able_ring.push(RGT_MAGACIAN);
	able_ring.push(RGT_FULL);
	able_ring.push(RGT_MAGIC_RESIS);
	for(int i = 0; i < 8; i++) {		
		addToRandomStage(0, 5, 1, ITM_RING, able_ring.pop());
	}

	
	//나오면 좋은 스펠카드
	random_extraction<int> able_spellcard;
	
	addToRandomStage(0, 4, 1, ITM_RING, ITM_ARMOR_HEAD,3);

	able_spellcard.push(SPC_V_FIRE);
	able_spellcard.push(SPC_V_ICE);
	able_spellcard.push(SPC_V_AIR);
	able_spellcard.push(SPC_V_METAL);
	able_spellcard.push(SPC_V_SUN);

	for(int i = 0; i < 3; i++) {		
		addToRandomStage(0, 5, 1, ITM_SPELL, able_spellcard.pop());
	}

	//나오면 좋은 아뮬렛
	random_extraction<int> able_amulet;

	able_amulet.push(AMT_PERFECT);
	able_amulet.push(AMT_BLOSSOM);
	able_amulet.push(AMT_TIMES);
	able_amulet.push(AMT_FAITH);
	able_amulet.push(AMT_SPIRIT);
	able_amulet.push(AMT_GRAZE);
	able_amulet.push(AMT_WEATHER);
	able_amulet.push(AMT_OCCULT);

	for(int i = 0; i < 4; i++) {
		addToRandomStage(1, 4, 1, ITM_AMULET, able_amulet.pop(), 2);
	}

	//나오면 좋은 책
	random_extraction<int> able_book;
	random_extraction<int> able_end_book;


	for (int i = 0; i < BOOK_LAST; i++) {
		if(i != BOOK_TRANSITION) {
			if(!isRareBook((book_list)i))
				able_book.push(i);
			else 
				able_end_book.push(i);
		}
	}
	for(int i = 0; i < 2; i++) {		
		//초반용 부스트
		addToRandomStage(0, 1, 1, ITM_BOOK, able_book.pop());
	}
	for(int i = 0; i < 8; i++) {		
		//중반 부스트
		addToRandomStage(2, 4, 1, ITM_BOOK, able_book.pop());
	}
	while(able_end_book.GetSize() > 0) {		
		//후반용 책
		addToRandomStage(3, 5, 1, ITM_BOOK, able_end_book.pop());
	}
}


list<std::shared_ptr<shootingLineInfo>> current_lines_info;
int line_delay = 0;

int getMonsterForSprint(SHOOTING_STAGE_LEVEL base_level, int count, SHOOTING_MONSTER_TYPE type) ;


bool isOutskirt(coord_def c) {
	if(c.x < DG_MAX_X/2-5 || c.x > DG_MAX_X/2+5 || c.y < DG_MAX_Y/2-7 || c.y > DG_MAX_Y/2+7) {
		return true;
	}
	return false;
}


std::shared_ptr<shootingLineInfo> getMonsterLine(SHOOTING_STAGE_LEVEL base_level, int count) 
{
	random_extraction<const shootingLineTemplate*> lines;
	for(const shootingLineTemplate& shootingline : shootinglines) {
		if(shootingline.min_count <= count && shootingline.minStage <= base_level && shootingline.maxStage >= base_level) {
			lines.push(&shootingline);
		}
	}
	std::shared_ptr<shootingLineInfo> created_line = std::make_shared<shootingLineInfo>(lines.choice());
	for(int i =0;i<SHT_MAX;i++) {
		created_line->mon[i] = getMonsterForSprint(base_level, count, (SHOOTING_MONSTER_TYPE)i);
	}
	return created_line;
}



int getStageLevel(SHOOTING_STAGE_LEVEL base_level) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		return 0;
	case SHT_STAGE_MISTY:
		return 1;
	case SHT_STAGE_YOUKAI:
	case SHT_STAGE_SCARLET:
		return 2;
	case SHT_STAGE_DEPTH:
		return 3;
	case SHT_STAGE_PANDE:
	case SHT_STAGE_MOON:
	case SHT_STAGE_HELL:
		return 4;
	case SHT_STAGE_HAKUREI:
		return 5;
	default:
		break;
	}
	return 0;
};

SHOOTING_STAGE_LEVEL getNextlevel(SHOOTING_STAGE_LEVEL base_level) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		return SHT_STAGE_MISTY;
	case SHT_STAGE_MISTY:
		return randA(1)?SHT_STAGE_YOUKAI:SHT_STAGE_SCARLET;
	case SHT_STAGE_YOUKAI:
		return SHT_STAGE_DEPTH;
	case SHT_STAGE_SCARLET:
		return SHT_STAGE_DEPTH;
	case SHT_STAGE_DEPTH:
		return (randA(2)==0?SHT_STAGE_PANDE:(randA(1)?SHT_STAGE_MOON:SHT_STAGE_HELL));
	case SHT_STAGE_PANDE:
		return SHT_STAGE_HAKUREI;
	case SHT_STAGE_MOON:
		return SHT_STAGE_HAKUREI;
	case SHT_STAGE_HELL:
		return SHT_STAGE_HAKUREI;
	case SHT_STAGE_HAKUREI:
		return SHT_STAGE_END;
	default:
		break;
	}
	return SHT_STAGE_END;
};


void initBaselevel(SHOOTING_STAGE_LEVEL base_level) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		break;
	case SHT_STAGE_MISTY:
		StopCurrentBGM("mistlake");
		PlayBGM("mistlake");
		break;
	case SHT_STAGE_YOUKAI:
		StopCurrentBGM("youkaimountain");
		PlayBGM("youkaimountain");
		break;
	case SHT_STAGE_SCARLET:
		StopCurrentBGM("scarlet");
		PlayBGM("scarlet");
		break;
	case SHT_STAGE_DEPTH:
		StopCurrentBGM("depth");
		PlayBGM("depth");
		break;
	case SHT_STAGE_PANDE:
		StopCurrentBGM("pandemonium");
		PlayBGM("pandemonium");
		break;
	case SHT_STAGE_MOON:
		StopCurrentBGM("dream");
		PlayBGM("dream");
		break;
	case SHT_STAGE_HELL:
		StopCurrentBGM("subterranean");
		PlayBGM("subterranean");
		break;
	case SHT_STAGE_HAKUREI:
		StopCurrentBGM("hakurei");
		PlayBGM("hakurei");
		break;
	default:
		break;
	}
};



int getFloorOfBaselevel(SHOOTING_STAGE_LEVEL base_level, int count) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		return 0 + count/70;
	case SHT_STAGE_MISTY:
		return MISTY_LAKE_LEVEL;
	case SHT_STAGE_YOUKAI:
		return YOUKAI_MOUNTAIN_LEVEL;
	case SHT_STAGE_SCARLET:
		return SCARLET_LEVEL;
	case SHT_STAGE_DEPTH:
		return DEPTH_LEVEL;
	case SHT_STAGE_PANDE:
		return PANDEMONIUM_LEVEL;
	case SHT_STAGE_MOON:
		return MOON_LEVEL;
	case SHT_STAGE_HELL:
		return SUBTERRANEAN_LEVEL;
	case SHT_STAGE_HAKUREI:
		return HAKUREI_LEVEL;
	default:
		break;
	}
	return 0;
};

dungeon_tile_type getTileOfBaselevel(SHOOTING_STAGE_LEVEL base_level, int count) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		return DG_FLOOR;
	case SHT_STAGE_MISTY:
		return DG_GRASS;
	case SHT_STAGE_YOUKAI:
		return DG_GRASS;
	case SHT_STAGE_SCARLET:
		return DG_FLOOR;
	case SHT_STAGE_DEPTH:
		return DG_FLOOR;
	case SHT_STAGE_PANDE:
		return (dungeon_tile_type)(DG_PANDE_FLOOR1 + (count/20)%7);
	case SHT_STAGE_MOON:
		return DG_DREAM_FLOOR;
	case SHT_STAGE_HELL:
		return DG_HELL_FLOOR;
	case SHT_STAGE_HAKUREI:
		return DG_FLOOR;
	default:
		break;
	}
	return DG_FLOOR;
};


dungeon_tile_type getWallTileOfBaselevel(SHOOTING_STAGE_LEVEL base_level, int count) 
{
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		return DG_WALL;
	case SHT_STAGE_MISTY:
		return DG_WALL;
	case SHT_STAGE_YOUKAI:
		return DG_STONE_WALL;
	case SHT_STAGE_SCARLET:
		return DG_RED_WALL;
	case SHT_STAGE_DEPTH:
		return DG_WALL;
	case SHT_STAGE_PANDE:
		return (dungeon_tile_type)(DG_PANDE_WALL1 + (count/20+1)%7);
	case SHT_STAGE_MOON:
		return DG_WALL2;
	case SHT_STAGE_HELL:
		return DG_HELL_WALL;
	case SHT_STAGE_HAKUREI:
		return DG_WALL;
	default:
		break;
	}
	return DG_FLOOR;
};


bool shootingLineInfo::process(int stage_count) {
	bool last_ = true;
	for(const stUnit& unit_ : lineTemplate->units) {
		if(unit_.count == count) {
			coord_def start_pos = unit_.path->start;
			monster* mon_ = (monster*)env[current_level].AddMonster(mon[unit_.type], 0, start_pos);
			
			for(int step : unit_.path->path_steps) {
				if(step != 8) {
					start_pos += GetDirecToPos(step);
				}
				mon_->will_move.push_front(start_pos);
			}
			mon_->item_lists.clear();
			if(unit_.item) {
				if(rand_stage[getStageLevel(current_base_level)].GetSize() > 0) {
					std::pair<item_type, int> item_ = rand_stage[getStageLevel(current_base_level)].pop();
					item_infor t;
					if(item_.second != -2) {
						makeitem(item_.first, 1, &t, item_.second);
					} else {
						//아티팩트
						makeitem(item_.first, 1, &t, -1);
						t.artifact = true;
					}
					mon_->item_lists.push_back(t);
				}
			}
			mon_->target = &you;
			mon_->target_pos = you.position;
			mon_->state.SetState(MS_DECIDE);
		}
		if(unit_.count > count) {
			last_ = false;
		}
	}
	
	count++;
	
	return last_;
}



int getBossForSprint(SHOOTING_STAGE_LEVEL base_level) 
{
	random_extraction<int> boss;
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
		boss.push(MON_RUMIA);
		boss.push(MON_WRIGGLE);
		boss.push(MON_KYOUKO);
		break;
	case SHT_STAGE_MISTY:
		boss.push(MON_CIRNO);
		boss.push(MON_MEDICINE);
		boss.push(MON_MISTIA);
		break;
	case SHT_STAGE_YOUKAI:
		boss.push(MON_AYA);
		boss.push(MON_NITORI);
		boss.push(MON_SANNYO);
		break;
	case SHT_STAGE_SCARLET:
		boss.push(MON_SAKUYA);
		boss.push(MON_MEIRIN);
		boss.push(MON_PACHU);
		break;
	case SHT_STAGE_DEPTH:
		boss.push(MON_SEIGA);
		boss.push(MON_ALICE);
		boss.push(MON_MURASA);
		break;
	case SHT_STAGE_PANDE:
		boss.push(MON_YUMEKO);
		//쇼 추가
		break;
	case SHT_STAGE_MOON:
		boss.push(MON_YORIHIME);
		boss.push(MON_TOYOHIME);
		boss.push(MON_DOREMI);
		break;
	case SHT_STAGE_HELL:
		boss.push(MON_SAKI);
		boss.push(MON_YUMA);
		boss.push(MON_ORIN);
		break;
	case SHT_STAGE_HAKUREI:
		boss.push(MON_FLAN);
		boss.push(MON_REIMU);
		boss.push(MON_UTSUHO);
		break;
	default:
		break;
	}
	return boss.choice();
}

int getMonsterForSprint(SHOOTING_STAGE_LEVEL base_level, int count, SHOOTING_MONSTER_TYPE type) 
{
	random_extraction<int> monsters;
	switch (base_level) {
	case SHT_STAGE_DUNGEON:
	default:
		if(count < 100) {//극초반
			switch (type) {
			case SHT_MON_WEAK:
				monsters.push(MON_MOOK);
				monsters.push(MON_FAIRY_GREEN);
				break;
			case SHT_MON_WEAK_RANGE:
				monsters.push(MON_FAIRY_BLUE);
				break;
			case SHT_MON_STRONG:
				monsters.push(MON_FAIRY_RED);
				monsters.push(MON_GREEN_MOOK);
				break;
			case SHT_MON_STRONG_RANGE:
				monsters.push(MON_FAIRY_BLUE);
				break;
			case SHT_MON_NORMAL:
				monsters.push(MON_CROW);
				monsters.push(MON_MOOK);
				monsters.push(MON_FAIRY_GREEN);
				break;
			case SHT_MON_NORMAL_STRONG:
				monsters.push(MON_SNAKE);
				monsters.push(MON_ORANGE_MOOK);
				break;
			default:
				break;
			}
		} else {
			switch (type) {
			case SHT_MON_WEAK:
				monsters.push(MON_MOOK);
				monsters.push(MON_FAIRY_GREEN);
				break;
			case SHT_MON_WEAK_RANGE:
				monsters.push(MON_FAIRY_BLUE);
				break;
			case SHT_MON_STRONG:
				monsters.push(MON_FAIRY_RED);
				monsters.push(MON_GREEN_MOOK);
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				break;
			case SHT_MON_STRONG_RANGE:
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				break;
			case SHT_MON_NORMAL:
				monsters.push(MON_BAKEKASA);
				monsters.push(MON_FIREFLY);
				monsters.push(MON_FAIRY_GREEN);
				break;
			case SHT_MON_NORMAL_STRONG:
				monsters.push(MON_CRANE);
				monsters.push(MON_FROG);
				monsters.push(MON_MARISAYUKKURI);
				break;
			default:
				break;
			}
		}
		break;
	case SHT_STAGE_MISTY:
		if(count < 100) {//극초반
			switch (type) {
			case SHT_MON_WEAK:
				monsters.push(MON_FAIRY_GREEN);
				monsters.push(MON_FAIRY_RED);
				break;
			case SHT_MON_WEAK_RANGE:
				monsters.push(MON_FAIRY_BLUE);
				break;
			case SHT_MON_STRONG:
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				monsters.push(MON_FAIRY_RED_COMMANDER);
				break;
			case SHT_MON_STRONG_RANGE:
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				break;
			case SHT_MON_NORMAL:
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				monsters.push(MON_FAIRY_RED_COMMANDER);
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				monsters.push(MON_FROG);
				break;
			case SHT_MON_NORMAL_STRONG:
				monsters.push(MON_TSUCHINOKO);
				monsters.push(MON_DEAGAMA);
				break;
			default:
				break;
			}
		} else {
			switch (type) {
			case SHT_MON_WEAK:
				monsters.push(MON_FAIRY_RED);
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				break;
			case SHT_MON_WEAK_RANGE:
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				break;
			case SHT_MON_STRONG:
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				monsters.push(MON_FAIRY_RED_COMMANDER);
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				monsters.push(MON_FAIRY_HERO);
				break;
			case SHT_MON_STRONG_RANGE:
				monsters.push(MON_FAIRY_SOCERER);
				monsters.push(MON_FAIRY_SUN_FLOWER);
				break;
			case SHT_MON_NORMAL:
				monsters.push(MON_FAIRY_GREEN_WARRIOR);
				monsters.push(MON_FAIRY_RED_COMMANDER);
				monsters.push(MON_FAIRY_BLUE_MAGICIAN);
				monsters.push(MON_FROG);
				break;
			case SHT_MON_NORMAL_STRONG:
				monsters.push(MON_TSUCHINOKO);
				monsters.push(MON_DEAGAMA);
				monsters.push(MON_FAIRY_HERO);
				monsters.push(MON_FAIRY_SOCERER);
				monsters.push(MON_FAIRY_SUN_FLOWER);
				break;
			default:
				break;
			}
		}
		break;
	case SHT_STAGE_YOUKAI:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_KATPA);
			monsters.push(MON_CROW);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_KATPA_GUN);
			monsters.push(MON_YAMAWARO_NINJA);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_KATPA_SPEAR);
			monsters.push(MON_KATPA_WATER_WIZARD);
			monsters.push(MON_CROW_TENGU);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_KATPA_WATER_WIZARD);
			monsters.push(MON_YAMABUSH_TENGU);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_KATPA_SPEAR);
			monsters.push(MON_KATPA_WATER_WIZARD);
			monsters.push(MON_YAMAWARO_WAWRRIOR);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_HANATACA_TENGU);
			if(count > 100)
				monsters.push(MON_SANPEI_FIGHTER);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_SCARLET:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_HOBGOBRIN);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_MAID_FAIRY_WEAK);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_HOBGOBRIN_MAID);
			monsters.push(MON_HOBGOBRIN_LIBRARIAN);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_MAGIC_BOOK);
			monsters.push(MON_HOBGOBRIN_LIBRARIAN);
			monsters.push(MON_HOBGOBRIN_TEMP);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_HOBGOBRIN_MAID);
			monsters.push(MON_MAGIC_BOOK);
			monsters.push(MON_HOBGOBRIN_LIBRARIAN);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_CHUPARCABRA);
			monsters.push(MON_VAMPIER_BAT);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_DEPTH:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_EAGLE);
			monsters.push(MON_DESIRE);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_RAIJUU);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_TIGER);
			monsters.push(MON_RED_UFO);
			monsters.push(MON_SNOW_GIRL);
			monsters.push(MON_LANTERN_YOUKAI);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_DRAGON_BABY);
			monsters.push(MON_NAMAZ);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_RED_UFO);
			monsters.push(MON_TIGER);
			monsters.push(MON_RACCON);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_ONI);
			monsters.push(MON_BLUE_ONI);
			monsters.push(MON_DRAGON_BABY);
			monsters.push(MON_NAMAZ);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_PANDE:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_LITTLE_IMP, 3);
			monsters.push(MON_SARA);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_EVIL_EYE, 3);
			monsters.push(MON_LUIZE);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_YUUGENMAGAN);
			monsters.push(MON_MAI);
			monsters.push(MON_YUKI);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_YUUGENMAGAN);
			monsters.push(MON_MAI);
			monsters.push(MON_YUKI);
			monsters.push(MON_SARIEL);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_SARA);
			monsters.push(MON_LUIZE);
			monsters.push(MON_ELIS);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_YUUGENMAGAN);
			monsters.push(MON_MAI);
			monsters.push(MON_YUKI);
			monsters.push(MON_SARIEL);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_MOON:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_MOON_RABIT_ATTACK);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_MOON_RABIT_ATTACK); //TODO
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_MOON_RABIT_ELITE);
			monsters.push(MON_MOON_RABIT_SUPPORT);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_MAC);
			monsters.push(MON_NIGHTMARE);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_MOON_RABIT_ELITE);
			monsters.push(MON_LUNATIC);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_NIGHTMARE);
			monsters.push(MON_MAC);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_HELL:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_HAUNT);
			monsters.push(MON_HELL_CROW);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_HAUNT); //TODO
			monsters.push(MON_HELL_CROW);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_HELL_SPIDER);
			monsters.push(MON_BLOOD_HAUNT);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_BLOOD_HAUNT);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_HELL_HOUND);
			monsters.push(MON_HELL_SPIDER);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_FIRE_CAR);
			break;
		default:
			break;
		}
		break;
	case SHT_STAGE_HAKUREI:
		switch (type) {
		case SHT_MON_WEAK:
			monsters.push(MON_FAIRY_GREEN_WARRIOR);
			monsters.push(MON_HELL_CROW);
			monsters.push(MON_DESIRE);
			monsters.push(MON_RED_UFO);
			break;
		case SHT_MON_WEAK_RANGE:
			monsters.push(MON_FLOWER_TANK);
			monsters.push(MON_MAGIC_BOOK);
			monsters.push(MON_FAIRY_SOCERER);
			break;
		case SHT_MON_STRONG:
			monsters.push(MON_ONI);
			monsters.push(MON_BLUE_ONI);
			break;
		case SHT_MON_STRONG_RANGE:
			monsters.push(MON_EVIL_EYE_TANK);
			break;
		case SHT_MON_NORMAL:
			monsters.push(MON_FLOWER_TANK);
			monsters.push(MON_ONI);
			monsters.push(MON_BLUE_ONI);
			break;
		case SHT_MON_NORMAL_STRONG:
			monsters.push(MON_EVIL_EYE_TANK);
			break;
		default:
			break;
		}
		break;
	}
	return monsters.choice();
}





void map_algorithms_shooting_sprint(int num)
{
	current_base_level = SHT_STAGE_DUNGEON;
	shooting_reward_random_init();
	shooting_god_dq.clear();
	current_lines_info.clear();
	you.SetProperty(TPT_STG_DEFAULT_ABIL, 1);
	line_delay = 10;
	for(int i=0;i<GT_LAST;i++)
	{
		shooting_god_dq.push_back(i);
	}
	rand_shuffle(shooting_god_dq.begin(),shooting_god_dq.end());
	for (int x = 0; x < DG_MAX_X; x++)
	{
		for (int y = 0; y < DG_MAX_Y; y++)
		{
			env[num].dgtile[x][y].tile = DG_FLOOR;
		}
	}
	map_dummy sprint_map(num, coord_def(DG_MAX_X/2, DG_MAX_Y/2), true, 1, 1, 0, DG_FLOOR, DG_WALL);
	set_shooting_sprint_map(&sprint_map);
	sprint_map.make_map(env[num],true, true);

	
	env[num].stair_up[0].x = DG_MAX_X/2;
	env[num].stair_up[0].y = DG_MAX_Y/2+6;
	map_list.god_num=0;
	env[num].MakeEvent(EVL_SHOOTING_SPRINT,coord_def(0,0),EVT_ALWAYS);
	scrollup(false, 7);
}

bool pickup_move();

bool shooting_event(int num)
{
	static int maximum_turn = 400;
	static int boss_trun = 420;

	if(map_list.bamboo_count%3 == 0)
	{
		for(list<item>::iterator it = env[current_level].item_list.begin();it != env[current_level].item_list.end();)
		{
			list<item>::iterator temp = it++;
			temp->position.y++;
			if(temp->position == you.position) {
				pickup_move();
			}
		}

		for(int x = -6 + DG_MAX_X/2; x <= 6 + DG_MAX_X/2; x++) {
			for(int y = 7 + DG_MAX_Y/2; y >= -7 + DG_MAX_Y/2; y--) {
				if(y != 7 + DG_MAX_Y/2) {
					env[current_level].changeTile(coord_def(x, y+1), env[current_level].dgtile[x][y].tile);
				}
				env[current_level].changeTile(coord_def(x, y),
				(std::abs(x -DG_MAX_X/2) == 6) ?
				getWallTileOfBaselevel(current_base_level, map_list.bamboo_count)
				:getTileOfBaselevel(current_base_level, map_list.bamboo_count));
			}
		}

	}

	if(!line_delay && map_list.bamboo_count < maximum_turn)
	{
		std::shared_ptr<shootingLineInfo> new_line = getMonsterLine(current_base_level, map_list.bamboo_count);
		line_delay += new_line->lineTemplate->delay;
		current_lines_info.push_back(new_line);
		
	} else if(line_delay > 0) {
		
		line_delay--;
	}
	
	for(list<std::shared_ptr<shootingLineInfo>>::iterator it = current_lines_info.begin(); it != current_lines_info.end();) {
		list<std::shared_ptr<shootingLineInfo>>::iterator temp = it++;
		if((*temp)->process(map_list.bamboo_count)) {
			current_lines_info.erase(temp);
		}
	}
	
	
	if(map_list.bamboo_count == 200)
	{
		random_extraction<int> rand_x;
		for(int i = -5; i <=5; i++) {
			rand_x.push(i);
		}
		for(int i = 0; i < GT_LAST/5;i++) {
			if(shooting_god_dq.size() > 0) {
				int temple_ = shooting_god_dq.back();
				env[current_level].changeTile(coord_def(rand_x.pop()+DG_MAX_X/2, DG_MAX_Y/2-7), (dungeon_tile_type)(DG_TEMPLE_FIRST+temple_));
				shooting_god_dq.pop_back();
			}
		}
		if(shooting_god_dq.size() <= 2) {
			while(  shooting_god_dq.size() > 0) {
				int temple_ = shooting_god_dq.back();
				env[current_level].changeTile(coord_def(rand_x.pop()+DG_MAX_X/2, DG_MAX_Y/2-7), (dungeon_tile_type)(DG_TEMPLE_FIRST+temple_));
				shooting_god_dq.pop_back();
			}
		}
	}

	if(map_list.bamboo_count == boss_trun) {
		//보스!
		int boss = getBossForSprint(current_base_level);
		coord_def create_pos(DG_MAX_X/2, DG_MAX_Y/2-7);
		env[current_level].AddMonster(boss, M_FLAG_EVENT, create_pos);
	}

	if(map_list.bamboo_count > boss_trun) {
		bool exist = false;
		vector<monster>::iterator it;
		it = env[current_level].mon_vector.begin();
		for (int i = 0; i < MON_MAX_IN_FLOOR && it != env[current_level].mon_vector.end(); i++, it++)
		{
			if ((*it).isLive() && (*it).isUnique() && (*it).s_ally != -1)
			{
				exist = true;
				break;
			}
		}
		if(!exist) {
			SHOOTING_STAGE_LEVEL next_base_level = getNextlevel(current_base_level);
			if(next_base_level == SHT_STAGE_END) {
				item_infor t;
				makeitem(ITM_ORB, -1, &t);
				env[num].MakeItem(coord_def(DG_MAX_X/2, DG_MAX_Y/2-7), t);
				env[current_level].changeTile(coord_def(DG_MAX_X/2, DG_MAX_Y/2-7), DG_UP_STAIR);
				return true;
			} else {
				random_extraction<int> rand_reward;
				for(int i = TPT_STG_START; i < TPT_STG_DEFAULT_ABIL; i++) {
					if( i == TPT_STG_OPTION && you.GetProperty((tribe_proper_type)i)<3) {
						rand_reward.push(100+i-TPT_STG_START);
					}
					else if(!you.GetProperty((tribe_proper_type)i)) {
						rand_reward.push(100+i-TPT_STG_START);
					}
				}

				for(int i = 0; i < 3;i++) {
					item_infor t;
					int value1 = rand_reward.pop();
					makeitem(ITM_GOAL, 0, &t, value1);
					t.name = name_infor(getTribePropertyKey((tribe_proper_type)(value1-100+TPT_STG_START), 1));
					env[num].MakeItem(coord_def(DG_MAX_X/2-4+i*4, DG_MAX_Y/2-7), t);
				}

				current_base_level = next_base_level;
				map_list.bamboo_count = 0;
				line_delay = 30;
				initBaselevel(current_base_level);
			}
		}
	}

	map_list.bamboo_count++;

	return false;
}


const char* create_shooting_sprint_map()
{
	return "\
#############\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#...........#\
#############";

}
void set_shooting_sprint_map(map_dummy* map_dummy_) {
	map_dummy_->size_x = 6;
	map_dummy_->size_y = 8;

	for(int x = 0; x<DG_MAX_X; x++)
	{	
		for(int y=0; y<DG_MAX_Y; y++)
		{
			env[current_level].dgtile[x][y].tile = DG_WALL;
		}
	}
	PixedMap(map_dummy_, create_shooting_sprint_map());
}
