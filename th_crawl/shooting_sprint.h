#pragma once

class map_dummy;

void set_shooting_sprint_map(map_dummy* map_dummy_);
bool shooting_event(int num);
bool isOutskirt(coord_def c);

enum SHOOTING_STAGE_LEVEL {
	SHT_STAGE_1,
	SHT_STAGE_DUNGEON = SHT_STAGE_1,
	SHT_STAGE_2,
	SHT_STAGE_MISTY = SHT_STAGE_2,
	SHT_STAGE_3,
	SHT_STAGE_YOUKAI = SHT_STAGE_3,
	SHT_STAGE_SCARLET,
	SHT_STAGE_4,
	SHT_STAGE_DEPTH = SHT_STAGE_4,
	SHT_STAGE_5,
	SHT_STAGE_PANDE = SHT_STAGE_5,
	SHT_STAGE_MOON,
	SHT_STAGE_HELL,
	SHT_STAGE_6,
	SHT_STAGE_HAKUREI = SHT_STAGE_6,
	SHT_STAGE_END
};

enum SHOOTING_MONSTER_TYPE {
	SHT_MON_WEAK, //줄지어 나오는 잡몹들
	SHT_MON_WEAK_RANGE, //줄지어 나오는 잡몹인데 원거리 공격이 가능
	SHT_MON_STRONG, //꽤 강한 몬스터(보통 한 웨이브에 하나씩 포함)
	SHT_MON_STRONG_RANGE, //강하면서 원거리 공격이 가능함(보통 나와서 상단에서 유지중)
	SHT_MON_NORMAL, //보통 라인없이 돌격하는 몬스터
	SHT_MON_NORMAL_STRONG, //강력하면서 라인없이 돌격하는 몬스터	
	SHT_MAX
};


class shootingPathInfo { //미리 정의해둔 길
public:
	coord_def start; //시작점
	vector<int> path_steps; //이동길
	
	shootingPathInfo(coord_def start, const vector<int>& path_steps):start(start), path_steps(path_steps){}
};


class stUnit { //길 정의를 쉽게 하기위한 클래스
public:
	int count; //발생시간
	SHOOTING_MONSTER_TYPE type; //몬스터 타입
	const shootingPathInfo* path;
	bool item;
	stUnit(int count,SHOOTING_MONSTER_TYPE type,const shootingPathInfo* path, bool item = false):count(count), type(type),path(path), item(item){}
};


class shootingLineTemplate {
public:
	int delay; //라인이 생기고 다음 라인까지 딜레이
	int min_count; //등장하는 최소 카운트
	SHOOTING_STAGE_LEVEL minStage; //등장하는 최소 스테이지
	SHOOTING_STAGE_LEVEL maxStage; //등장하는 최대 스테이지
	
	vector<stUnit> units; //유닛 라인 정보
	
	shootingLineTemplate(int delay, int min_count, SHOOTING_STAGE_LEVEL minStage, SHOOTING_STAGE_LEVEL maxStage,const vector<stUnit>& units):delay(delay), min_count(min_count), minStage(minStage),maxStage(maxStage), units(units){}
};


class shootingLineInfo {
public:
	const shootingLineTemplate* lineTemplate;
	
	int count;
	int mon[SHT_MAX];
	
	shootingLineInfo(const shootingLineTemplate* lineTemplate):lineTemplate(lineTemplate), count(0){
		for(int i = 0; i < SHT_MAX;i++) {
			mon[i] = -1;
		}
	};
	
	bool process(int stage_count);
};



