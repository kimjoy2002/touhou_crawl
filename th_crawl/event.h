//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: event.h
//
// 내용: 이벤트 클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EVENT_H__
#define  __EVENT_H__

#include "common.h"
#include "enum.h"

enum event_list
{
	EVL_KISME=100,
	EVL_SIGHT_P, //시야에 들어와야 생기는 P
	EVL_FLOOR, //땅이 된다
	EVL_DREAM_FLOOR, //땅이 된다2
	EVL_BAMBOO, //미궁의죽림
	EVL_LUNATICTIME, //루나틱 타임!
	EVL_KOGASA, //키스메를 따라하는 코가사
	EVL_NOISE,//소음
	EVL_VIOLET,//필드 바이올렛
	EVL_DREAM_MONSTER,//드림방 몬스터 생성
	EVL_DREAM_MESSAGE, //꿈의 세계가 펼쳐진다.
	EVL_AGRO, //모든 몹이 플레이어에게 어그로가 끌린다.
	EVL_REGEN, //몹의 리젠 (꿈의 세계).
	EVL_REGEN2, //몹의 리젠 (지저).
	EVL_ARENA, //아레나
	EVL_NAMAZ, //나마즈 떨구기
	EVL_KOISHI,
	EVL_KYOKO, //공포의 쿄코
	EVL_AUTUMN, //단풍
	EVL_SUKIMA, //스키마
	EVL_RUN_FAIRY, //도망치는 삼월정
	EVL_SCALET_TRAP, //홍마관 트랩
	EVL_KOGASATIME, //코가사 타임!
	EVL_SANTUARY, //성역
	EVL_HOJOK, //호족난무
	EVL_KOGASA3, //코가사안개
	EVL_MEDI, //메디슨
	EVL_LOCK_DOOR, //바로 문을 잠근다.
	EVL_SMOKE, //연기발생
	EVL_CHEN,
	EVL_BROKEN_NESI, //수리가 끝나지않은 네시
	EVL_FIRE_SMOKE,
	EVL_COLD_SMOKE,
	EVL_SILENCE,
	EVL_SION_DELETE,
	EVL_WATER, //임시로 물이 된다.
	EVL_RUMIA_DANCER1,
	EVL_RUMIA_DANCER2,
	EVL_DIEFAIRY,
	EVL_CHANGE_TILE,
	EVL_MIMA_SPARK_BOOK,
	EVL_TENSI_EARTHQUAKE,
	EVL_TWIST, //트위스트
	EVL_KISUME_UP,
	EVL_CREATE_KOGASA_STONE,
	EVL_SHOOTING_SPRINT
};

class events
{
public:
	int id;
	coord_def position;
	event_type type;
	int count;
	bool prev_sight;
	int value;

	events();
	events(int id_, coord_def position_, event_type type_, int count_ = -1, int value = 0);
	void SaveDatas(FILE *fp);
	void LoadDatas(FILE *fp);
	int start();
	int action(int delay_);
};
#endif // __EVENT_H__