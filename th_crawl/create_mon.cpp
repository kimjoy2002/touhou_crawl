//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: create_mon.cpp
//
// 내용: 맵에 맞는 몬스터그룹을 생성한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_infor.h"
#include "environment.h"
#include "event.h"


void create_id_to_mon(int id, int level);
int get_unique_to_id(int m_id);
void create_id_to_unique(int id, int level);
vector<unique_infor> unique_list;

struct mon_group
{
	int id; //고유번호 <- 고유번호
	int min_level; //최소레벨 <- 나오는 던전 층
	int max_level; //최대레벨 <- 나오는 던전 층
	int percent; //확률  <- 나올 빈도를 결정한다.
	int strong; //집단의 난이도  (10이 기본) <- 약한 몹이나 강한 몹이 너무 많이 생성됨을 방지

};
mon_group normal_group[] = //일반몹 그룹
{
	{  0,  0,  4,  30,  1}, //모옥 1
	{  1,  0,  4,  30,  1}, //쥐 1
	{  2,  0,  3,  8,  2}, //레이무윳쿠리 1
	{  3,  0,  2,  30,  1}, //초록요정 1
	//{  4,  0,  4,  20,  3}, //까마귀 3
	{  6,  0,  1,  10,  3}, //파랑요정 1
	{  7,  0,  2,  10,  2}, //초록요정 2~3
	
	{  5,  1,  2,  2,  3}, //빨간요정 1
	{ 23,  1,  5,  5,  3}, //반딧불이
	{  8,  1,  4,  10,  3}, //거미 1
	{  9,  1,  5,  10,  5}, //뱀 1
	{ 11,  1,  4,  12,  3}, //초록요정1 파랑요정1
	{ 12,  1,  5,  12,  3}, //초록요정1 빨강요정1
	//{ 13,  1,  5,  40,  3}, //모옥2 까마귀4
	//{ 14,  1,  3,  8,  5}, //캇파2~3 (갓파 너무 쎄서 제거)
	{ 24,  1,  4,  5,  5}, //인간부대(약함)
	{ 27,  1,  14,  8,  5}, //우산요괴
	{ 28,  1,  5,  5,  5}, //초록모옥
	
	{ 15,  2,  9,  20,  5}, //초록요정2 파랑요정1 빨강요정1
	{ 14,  2,  3,  8,  5}, //캇파2~3
	{ 18,  2,  6,  25,  6}, //캇파4~5
	{ 20,  2,  9,  10,  7}, //거미1 뱀1
	{ 10,  2,  11,  10,  6}, //두루미 1
	{ 24,  2,  4,  5,  5}, //인간부대(약함)
	{ 29,  2,  7,  5,  5}, //주황모옥
	{ 28,  2,  5,  10,  5}, //초록모옥

	
	{ 10,  3,  14,  3,  6}, //두루미 1
	{ 4,   3,  7,  10 , 3}, //까마귀3
	{ 16,  3,  9,  10,  6}, //파랑요정2 빨강요정2
	{ 25,  3,  6,  7, 10}, //인간부대(중간)
	{ 30,  3,  9,  5,  5}, //회색모옥

	
	{ 25,  4,  6,  20, 10}, //인간부대(중간)
	{ 29,  4,  7,  10,  5}, //주황모옥

	
	{ 21,  5,  11,  10,  8}, //요정 전사사격 호위부대
	{ 35,  5,  14,  5, 10}, //마리사윳쿠리
	{ 30,  5,  9,  10,  5}, //회색모옥

	
	{ 22,  6,  12,  10, 13}, //깃발 요정 호위부대
	{ 32,  6,  14,  15, 10}, //고양이
	
	{ 31,  7,  14,  20, 10}, //개구리
	{ 26,  7,  14,  30, 20}, //인간부대(강함)
	{ 33,  7,  14,  15, 15}, //까마귀텐구
	{ 38,  7,  14,  8, 10}, //야마비코


	{ 34,  9,  14,  5, 30}, //오니
	{ 39,  9,  14,  5, 15}, //캇파창병부대
	{ 36,  9,  14,  5, 10}, //키메이마루

	{ 37,  10,  14,  5, 30}, //레밀리아 윳쿠리
	{ 53,  10,  14,  5, 30}, //매	
	{ 54,  10,  14,  5, 30}, //호랑이

	
	{ 58,  11,  14,  5, 30}, //벤토라 1기
	{ 34,  11,  14,  5, 30}, //오니
	{ 42,  11,  14,  10, 30}, //텐구부대


	{ 43,  12,  14,  5, 30}, //아오오니
	{ 55,  12,  14,  5, 30}, //뇌수
	
	{ 56,  13,  14,  5, 30}, //용

	
	//YOUKAI_MOUNTAIN_LEVEL

	
	
	{ 15,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  8,  5}, //초록요정2 파랑요정1 빨강요정1
	{ 21,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10,  8}, //요정 전사사격 호위부대
	{ 22,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+4,  10, 13}, //깃발 요정 호위부대
	{  3,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  1}, //초록요정 1
	{  5,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+1,  1,  3}, //빨간요정 1
	{  6,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  3}, //파랑요정 1
	{  7,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  2}, //초록요정 2~3
	{  0,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  1,  1}, //모옥 1
	{ 29,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  2,  5}, //주황모옥
	{ 28,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  2,  5}, //초록모옥
	{ 30,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  2,  5}, //회색모옥
	
	{ 21,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  5,  8}, //요정 전사사격 호위부대
	{ 22,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  8, 13}, //깃발 요정 호위부대
	{ 14,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  2,  5}, //캇파2~3
	{ 17,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4, 2,  5}, //캇파창병
	{ 31,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  7, 10}, //개구리
	{ 94,  MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  7, 15}, //버섯요괴
		
	{ 22,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4, 5, 13}, //깃발 요정 호위부대
	{ 65,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4, 2, 20}, //요정영웅부대
	
	{ 63,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 5, 13}, //큰두꺼비

	{ 66,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 2, 20}, //요정소서러
	{ 67,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4, 2, 25}, //요정해바라기

	//YOUKAI_MOUNTAIN_LEVEL

	{ 18,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2, 15,  6}, //캇파4~5
	{ 31,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2,  7, 10}, //개구리
	{ 17,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1, 10,  5}, //캇파창병
	{ 19,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+1,  7, 10}, //캇파1~3 캇파수술사
	{ 33,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //까마귀텐구
	{ 39,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+2,  2, 15}, //캇파창병부대
	{ 36,  YOUKAI_MOUNTAIN_LEVEL,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 10}, //키메이마루

	{ 17,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+2,  5, 10}, //캇파창병 
	{ 33,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 15}, //까마귀텐구
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //캇파창병부대
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //캇파 창 수술 엘리트부대
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+1,  YOUKAI_MOUNTAIN_LEVEL+3,  1, 25}, //야마와로 부대


	{ 33,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //까마귀텐구
	{ 39,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //캇파창병부대
	{ 44,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //캇파 창 수술 엘리트부대
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //야마부시텐구
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //하나타카텐구
	{ 36,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  3, 10}, //키메이마루
	{ 42,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3,  10, 30}, //텐구부대
	//{ 45,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+4,  10, 30}, //백랑텐구
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+2,  YOUKAI_MOUNTAIN_LEVEL+3, 2, 25}, //야마와로 부대

	 
	{ 40,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 15}, //야마부시텐구
	{ 41,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 20}, //하나타카텐구
	{ 61,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  2, 30}, //산페이파이터
	{ 57,  YOUKAI_MOUNTAIN_LEVEL+3,  YOUKAI_MOUNTAIN_LEVEL+3,  5, 25}, //야마와로 부대


	
	//SCARLET_LEVEL
	{ 51,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 15,  6}, //메이드요정3~4
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+2, 15,  16}, //홉고블린 소부대 
	{ 49,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //홉고블린 메이드2기
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 1,  16}, //홉고블린 서기
	
	{ 48,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 5,  16}, //홉고블린 소부대 
	{ 50,  SCARLET_LEVEL,  SCARLET_LEVEL+3, 3,  16}, //홉고블린 서기
	{ 47,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 3,  20}, //마법책
	{ 52,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  30}, //추파카브라
	{ 62,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3, 1,  20}, //흡혈박쥐
	
	{ 48,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //홉고블린 소부대 
	{ 49,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //홉고블린 메이드2기
	{ 50,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  16}, //홉고블린 서기
	{ 47,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 5,  20}, //마법책
	{ 37,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 3,  30}, //레밀리아 윳쿠리
	{ 60,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3, 3,  30}, //홉고블린 악마술사
	
	{ 52,  SCARLET_LEVEL+3,  SCARLET_LEVEL+3, 5,  30}, //추파카브라
	
	{ 47,  SCARLET_LIBRARY_LEVEL,  SCARLET_LIBRARY_LEVEL, 5,  20}, //도서관용 마법책
	

	//영원정
	{ 95,  EIENTEI_LEVEL,  EIENTEI_LEVEL, 10,  30}, //토끼들



	//윳쿠리굴
	{ 2,  YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1, 2,  1}, //레이무윳쿠리
	{ 35, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1, 2, 2}, //마리사윳쿠리
	{ 36, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //키메이마루
	{ 37, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //레밀리아윳쿠리
	{ 97, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //윳쿠리앨리스
	{ 98, YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL, 10, 2}, //윳쿠리요우무



	//짐승길
	{ 68,  DEPTH_LEVEL,  DEPTH_LEVEL+2, 10,  28}, //요정대부대
	{ 64,  DEPTH_LEVEL,  DEPTH_LEVEL+3, 10,  25}, //동물3형제
	{ 86,  DEPTH_LEVEL,  DEPTH_LEVEL+3, 10,  20}, //너구리
	{ 83,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //설녀
	{ 84,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //나마즈
	{ 87,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  25}, //제등요괴
	{ 34,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  30}, //오니
	{ 43,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  30}, //아오오니
	{ 56,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  35}, //용
	{ 59,  DEPTH_LEVEL,  DEPTH_LEVEL+4, 10,  35}, //벤토라

	
	//꿈의 세계
	{ 73,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //맥
	{ 74,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //악몽
	{ 75,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //광기
	{ 59,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //벤토라
	{ 69,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //달토끼 지원병
	{ 70,  DREAM_LEVEL,  DREAM_LEVEL, 10,  35}, //달토끼 척후병
	//아래는 희귀한 확률로 나오는
	{ 89,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //마족들
	{ 68,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //요정들
	{ 83,  DREAM_LEVEL,  DREAM_LEVEL, 2,  35}, //설녀
	{ 95,  DREAM_LEVEL,  DREAM_LEVEL, 2,  30}, //토끼들
	{ 42,  DREAM_LEVEL,  DREAM_LEVEL, 2, 30}, //텐구부대




	//달의 세계
	{ 75,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //광기
	{ 69,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //달토끼 지원병
	{ 70,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //달토끼 척후병
	{ 72,  MOON_LEVEL,  MOON_LEVEL, 10,  35}, //달토끼 엘리트
	
	//지저
	{ 87,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+2, 10,  30}, //제등요괴
	{ 68,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+3, 10,  28}, //요정대부대
	{ 62,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+3, 10,  20}, //흡혈박쥐
	{ 60,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL+4, 2,  30}, //홉고블린 악마술사
	{ 76,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //원령때
	{ 78,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //츠치구모
	{ 34,  SUBTERRANEAN_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //오니

	{ 79,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //핏빛원령
	{ 43,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL_LAST_LEVEL-1, 10,  30}, //아오오니
	{ 32,  SUBTERRANEAN_LEVEL+1,  SUBTERRANEAN_LEVEL+4, 7,  30}, //고양이

	{ 80,  SUBTERRANEAN_LEVEL+2,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //지옥개

	{ 77,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 3,  30}, //화차
	{ 34,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //오니
	{ 43,  SUBTERRANEAN_LEVEL+3,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //아오오니

	{ 85,  SUBTERRANEAN_LEVEL+4,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //지옥까마귀	
	
	{ 76,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 5,  30}, //원령때
	{ 85,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //지옥까마귀
	{ 77,  SUBTERRANEAN_LEVEL_LAST_LEVEL,  SUBTERRANEAN_LEVEL_LAST_LEVEL, 10,  30}, //화차
	
	//판데모니엄
	{ 89,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 50,  35}, //3티어마족+자코
	{ 90,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 6,  35}, //유겐마간
	{ 91,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 7,  35}, //유키
	{ 92,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 7,  35}, //마이
	{ 93,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 6,  35}, //사리엘
	{ 74,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 4,  35}, //악몽
	{ 79,  PANDEMONIUM_LEVEL,  PANDEMONIUM_LEVEL, 4,  35}, //피빛원령
	

	//법계 (법계는 무슨 차이가 있지?
	{ 89,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 60,  35}, //3티어마족+자코
	{ 93,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 10,  35}, //사리엘
	{ 59,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 10,  35}, //벤토라
	{ 74,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 5,  35}, //악몽
	{ 79,  PANDEMONIUM_LEVEL+1,  PANDEMONIUM_LEVEL+1, 5,  35}, //피빛원령

	//빙설세계	
	{ 99,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 70,  35}, //루이즈의 비중이 높아지는
	{ 92,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 15,  35}, //마이
	{ 83,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 6,  35}, //설녀
	{ 74,  PANDEMONIUM_LEVEL+2,  PANDEMONIUM_LEVEL+2, 3,  35}, //악몽

	//판데모니엄
	{ 89,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 60,  35}, //3티어마족+자코
	{ 91,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 5,  35}, //유키
	{ 92,  PANDEMONIUM_LEVEL+3,  PANDEMONIUM_LEVEL+3, 15,  35}, //마이

	//하쿠레이 신사
	{ 56,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //용
	{ 81,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //플라워 전차
	{ 96,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 10,  30}, //오니패거리
	{ 86,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL, 5,  20}, //너구리
	//{ 90,  HAKUREI_LEVEL+1,  HAKUREI_LAST_LEVEL, 3,  35}, //유겐마간
	{ 83,  HAKUREI_LEVEL+1,  HAKUREI_LAST_LEVEL, 5,  35}, //설녀
	{ 77,  HAKUREI_LEVEL+2,  HAKUREI_LAST_LEVEL, 10,  35}, //화차
	{ 82,  HAKUREI_LEVEL+3,  HAKUREI_LAST_LEVEL, 10,  35}, //이블 전차
	//{ 88, HAKUREI_LAST_LEVEL,  HAKUREI_LAST_LEVEL, 10,  35}, //음양옥

	{ -1,  0,  0,  0,  0} //배열의 끝
};


mon_group unigue_group[] = //네임드몹 그룹 확률은 100이 최고
{
	{  0,  1,  3,  35,  1}, //루미아
	{  6,  1,  3,  35,  1}, //키스메
	{  11,  1,  6,  5,  2}, //지그문트
	{  1,  2,  4,  35,  1}, //리글
	{  9,  2,  4,  35,  2}, //삼월정
	{  10, 2,  4,  30,  2}, //쿄코
	{  8,  3,  5,  35,  2}, //코가사
	{  2,  4,  6,  35,  2}, //미스티아
	{  7,  6,  9,  35,  3}, //첸
	{  44,  6,  9,  30,  3}, //세이란
	{  5,  7,  8,  35,  2}, //대요정
	{  16,  7,  11,  15,  3}, //나즈린
	{  3,  8,  10,  35,  3}, //치르노
	{  4,  8,  12,  20,  3}, //메디슨
	
	{  15,  9,  14,  15,  3}, //야마메
	{  17,  9,  14,  15,  3}, //요시카
	{  18,  9,  14,  15,  3}, //세키반키
	{  20,  9,  14,  15,  3}, //카게로
	{  21,  9,  14,  10,  3}, //파르시
	{  22,  9,  14,  20,  3}, //츠쿠모
	{  31,  9,  14,  25,  3}, //코이시
	{  49,  9,  14,  15,  3}, //책읽는요괴(토키코)
	{  35,  11,  14,  15,  3}, //클라운피스
	{  37,  11,  14,  15,  3}, //레티

	//안개호수
	{  9, MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+2,  40,  2}, //삼월정
	{  14,  MISTY_LAKE_LEVEL,  MISTY_LAKE_LEVEL+3,  40,  2}, //빙어
	{  5, MISTY_LAKE_LEVEL+1,  MISTY_LAKE_LEVEL+4,  40,  2}, //대요정
	{  3, MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  40,  3}, //치르노
	{  21,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  10,  3}, //파르시
	{  18,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  15,  2}, //세키반키
	{  49,  MISTY_LAKE_LEVEL+2,  MISTY_LAKE_LEVEL+4,  15,  2}, //책읽는요괴(토키코)
	{  18,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  15,  2}, //세키반키
	
	{  12,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  60,  4}, //모미지
	{  22,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3, 20,  3}, //츠쿠모
	{  16,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  20,  3}, //나즈린
	//{  13,  YOUKAI_MOUNTAIN_LEVEL+4,  YOUKAI_MOUNTAIN_LEVEL+4,  100,  5}, //아야(현재버젼에선 벌트로 등장)
	{  21,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+3,  10,  3}, //파르시
	//{  19,  YOUKAI_MOUNTAIN_LEVEL+1, YOUKAI_MOUNTAIN_LEVEL+2,  30,  3}, //니토리(현재버젼에선 벌트로 등장)

	
	{  21,  SCARLET_LEVEL+1,  SCARLET_LEVEL+3,  10,  3}, //파르시
	//{  25,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  40,  4}, //파츄리(아마 벌트고정)
	{  26,  SCARLET_LEVEL+2,  SCARLET_LEVEL+3,  50,  3}, //소악마
	//{  27,  MISTY_LAKE_LEVEL+3,  MISTY_LAKE_LEVEL+4,  60,  4}, //메이린(아마 벌트고정)
	{  28,  SCARLET_LEVEL+3,  SCARLET_LEVEL+4,  50,  4}, //사쿠야
	//{  29,  SCARLET_LEVEL+4,  SCARLET_LEVEL+4,  60,  5}, //레밀리아 아마 벌트 고정
	
	

	{ 18,  YUKKURI_LEVEL, YUKKURI_LAST_LEVEL-1, 20,  28}, //세키반키
	{  21,  YUKKURI_LEVEL,  YUKKURI_LAST_LEVEL-1,  5,  3}, //파르시

	
	{ 23,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  3}, //오린
	{ 32,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  28}, //누에
	{ 35,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL, 30,  28}, //클라운피스
	{ 21,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  10,  3}, //파르시
	{ 24,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  30,  3}, //이치린
	{ 37,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  15,  3}, //레티
	{ 43,  DEPTH_LEVEL,  DEPTH_LAST_LEVEL,  30,  3}, //앨리스
	
	{ 6,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+1, 20,  28}, //키스메 
	{ 15,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+2, 20,  28}, //야마메 
	{ 21,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+3, 20,  28}, //파르시 
	{ 23,  SUBTERRANEAN_LEVEL, SUBTERRANEAN_LEVEL+5, 30,  28}, //오린

	{ 37,  HAKUREI_LEVEL,  HAKUREI_LAST_LEVEL-1,  30,  3}, //스이카

	{ -1,  0,  0,  0,  0} //배열의 끝
};


void init_monster()
{
	int i=0;
	while(unigue_group[i].id != -1)
	{
		if(randA_1(100)<=unigue_group[i].percent)
		{
			int f_id_ = unigue_group[i].id;
			auto it = find_if(unique_list.begin(),unique_list.end(),
				[f_id_](unique_infor &v)->bool{
					return v.id == f_id_;
				}
				);

			if(it != unique_list.end())
			{
				if(randA(1))
				{
					unique_list.erase(it);
					unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));
				}
			}
			else	
				unique_list.push_back(unique_infor(unigue_group[i].id,rand_int(unigue_group[i].min_level,unigue_group[i].max_level)));

		}
		i++;
	}

}



bool is_exist_named(monster_index m_id_) //해당 네임드가 출현확정되어있는지
{		
	int id_ = get_unique_to_id(m_id_);

	auto it = find_if(unique_list.begin(),unique_list.end(),
		[id_](unique_infor &v)->bool{
			return v.id == id_;
		}
	);
	return it != unique_list.end();
}
void set_exist_named(monster_index m_id_) //네임드를 출현확정(벌트등으로)
{
	for(auto it = unique_list.begin();  it !=  unique_list.end(); it++)
	{ //기존에 있으면 지워버린다.
		if(it->id == get_unique_to_id(m_id_))
		{
			unique_list.erase(it);
			break;
		}
	}
	int id_ = get_unique_to_id(m_id_);
	unique_list.push_back(unique_infor(id_,-1));
}
void unset_exist_named(monster_index m_id_) //네임드를 다시 출현할 수 있는 상태로
{
	for(auto it = unique_list.begin();  it !=  unique_list.end(); it++)
	{ //기존에 있으면 지워버린다.
		if(it->id == get_unique_to_id(m_id_))
		{
			unique_list.erase(it);
			break;
		}
	}
}





void create_mon(int floor, int num_)
{
	if(num_ == 0)
		return;

	int i = 0, total=0, num = num_?num_:10;
	vector<mon_group*> group;
	group.reserve(128);
	while(normal_group[i].id != -1)
	{
		if(normal_group[i].min_level<=floor && normal_group[i].max_level>=floor)
		{
			group.push_back(&normal_group[i]);
			total+=normal_group[i].percent;
		}
		else if(normal_group[i].min_level > floor)
			break;
		i++;
	}

	for(int i = 0; i<num; i++)
	{
		int rand_ = randA_1(total);
		vector<mon_group*>::iterator it;
		for(it = group.begin(); it != group.end(); it++)
		{
			if(rand_<=(*it)->percent)
			{
				create_id_to_mon((*it)->id, floor);
				break;
			}
			else
				rand_ -= (*it)->percent;	
	
		}
	}

	for(vector<unique_infor>::iterator it = unique_list.begin();it!=unique_list.end();it++)
	{
		if(it->level == floor)
		{
			create_id_to_unique(it->id, floor);

		}
	}
}


void Set_X_Y(int &x_, int x, int rand_x, int &y_, int y, int rand_y)
{
	x_= x+rand_x;
	y_= y+rand_y;
	if(x_<0)
		x_=0;
	else if(x_>=DG_MAX_X)
		x = DG_MAX_X-1;
	if(y_<0)
		y_=0;
	else if(y_>=DG_MAX_Y)
		y_ = DG_MAX_Y-1;
}




void create_id_to_mon(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_MOOK);
		break;
	case 1:
		index.push_back(MON_RAT);
		break;
	case 2:
		index.push_back(MON_REIMUYUKKURI);
		break;
	case 3:
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 4:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		break;
	case 5:
		index.push_back(MON_FAIRY_RED);
		break;
	case 6:
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 7:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_FAIRY_GREEN);
		break;
	case 8:
		index.push_back(MON_SPIDER);
		break;
	case 9:
		index.push_back(MON_SNAKE);
		break;
	case 10:
		index.push_back(MON_CRANE);
		break;
	case 11:
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 12:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 13:
		//index.push_back(MON_MOOK);
		//index.push_back(MON_MOOK);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		//index.push_back(MON_CROW);
		break;
	case 14:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 15:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_GREEN);
		index.push_back(MON_FAIRY_GREEN);
		break;
	case 16:
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_RED);
		index.push_back(MON_FAIRY_BLUE);
		index.push_back(MON_FAIRY_BLUE);
		break;
	case 17:
		//비어있어
		/*index.push_back(MON_KATPA);
		index.push_back(MON_KATPA);*/
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 18:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		break;
	case 19:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		/*for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back((monster_index)rand_int(MON_FAIRY_GREEN_WARRIOR,MON_FAIRY_RED_COMMANDER));*/
		
		break;
	case 20:
		index.push_back(MON_SPIDER);
		index.push_back(MON_SNAKE);
		break;
	case 21:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ = randA(3)?1:2, i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		break;
	case 22:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(randA(2)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		index.push_back(MON_FAIRY_RED_COMMANDER);
		break;
	case 23:
		index.push_back(MON_FIREFLY);
		break;
	case 24:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		break;
	case 25:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		if(randA(4)<1)
			index.push_back(MON_HUMAM_SAMURI);
		break;
	case 26:
		for(int rand_ = rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_HUMAM_MAN);
		index.push_back(MON_HUMAM_PRIEST);
		index.push_back(MON_HUMAM_YINYANG);
		index.push_back(randA(1)?MON_HUMAM_PRIEST:MON_HUMAM_YINYANG);
		index.push_back(MON_HUMAM_SAMURI);
		break;
	case 27:
		index.push_back(MON_BAKEKASA);
		break;
	case 28:
		index.push_back(MON_GREEN_MOOK);
		break;
	case 29:
		index.push_back(MON_ORANGE_MOOK);
		break;
	case 30:
		index.push_back(MON_GRAY_MOOK);
		break;
	case 31:
		index.push_back(MON_FROG);
		break;
	case 32:
		index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 33:
		index.push_back(MON_CROW_TENGU);
		break;
	case 34:
		index.push_back(MON_ONI);
		break;
	case 35:
		index.push_back(MON_MARISAYUKKURI);
		break;
	case 36:
		index.push_back(MON_AYAYUKKURI);
		break;
	case 37:
		index.push_back(MON_REMILIAYUKKURI);
		break;
	case 38:
		index.push_back(MON_YAMABIKO);
		break;
	case 39:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_KATPA);
		index.push_back(MON_KATPA_WATER_WIZARD);
		index.push_back(MON_KATPA_SPEAR);
		break;
	case 40:
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 41:
		index.push_back(MON_HANATACA_TENGU);
		break;
	case 42:
		for(int rand_ =rand_int(0,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_CROW_TENGU);
		index.push_back(MON_YAMABUSH_TENGU);
		break;
	case 43:
		index.push_back(MON_BLUE_ONI);
		break;
	case 44:
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_SPEAR);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_KATPA_WATER_WIZARD);
		break;
	case 45:
		index.push_back(MON_WOLF_TENGU);
		break;
		
	case 46:	
		for(int rand_ =rand_int(1,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;			
	case 47:
		//마법책은 마법을 배우고있어야하므로 조심
		index.push_back(MON_MAGIC_BOOK);
		break;		
	case 48:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_HOBGOBRIN);
		if(randA(2)<1)
			index.push_back(MON_HOBGOBRIN_MAID);
		if(randA(4)<1)
			index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;		
	case 49:
		index.push_back(MON_HOBGOBRIN_MAID);
		index.push_back(MON_HOBGOBRIN_MAID);
		break;	
	case 50:
		index.push_back(MON_HOBGOBRIN_LIBRARIAN);
		break;
	case 51:	
		for(int rand_ =rand_int(3,5), i=0;i<rand_;i++)
			index.push_back(MON_MAID_FAIRY);
		break;
	case 52:
		index.push_back(MON_CHUPARCABRA);
		break;
	case 53:
		index.push_back(MON_EAGLE);
		break;
	case 54:
		index.push_back(MON_TIGER);
		break;
	case 55:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_RAIJUU);
		break;
	case 56:
		index.push_back(MON_DRAGON_BABY);
		break;
	case 57:
		for(int rand_ =rand_int(1,5), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_YAMAWARO_NINJA:MON_YAMAWARO_WAWRRIOR);
		if(randA(3)<1)
			index.push_back(MON_YAMAWARO_FLAG);
		break;
	case 58:
		index.push_back(MON_RED_UFO);
		break;
	case 59:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
		index.push_back(randA(2)?(randA(1)?MON_RED_UFO:MON_BLUE_UFO):MON_GREEN_UFO);
		break;
	case 60:
		index.push_back(MON_HOBGOBRIN_TEMP);
		break;
	case 61:
		index.push_back(MON_SANPEI_FIGHTER);
		break;
	case 62:
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_VAMPIER_BAT);
		break;
	case 63:
		index.push_back(MON_DEAGAMA);
		break;	
	case 64:
		index.push_back(MON_EAGLE);
		for(int rand_ =rand_int(0,1), i=0;i<rand_;i++)
			index.push_back(MON_TIGER);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_RAIJUU);
		break;
	case 65:		
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_FAIRY_GREEN_WARRIOR:(randA(1)?MON_FAIRY_BLUE_MAGICIAN:MON_FAIRY_RED_COMMANDER));
		index.push_back(MON_FAIRY_HERO);
		break;
	case 66:
		index.push_back(MON_FAIRY_SOCERER);
		break;	
	case 67:		
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN_WARRIOR:MON_FAIRY_BLUE_MAGICIAN);
		index.push_back(MON_FAIRY_SUN_FLOWER);
		break;
	case 68:
		index.push_back(MON_FAIRY_HERO);
		index.push_back(MON_FAIRY_SOCERER);
		index.push_back(MON_FAIRY_SUN_FLOWER);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_FAIRY_GREEN:randA(1)?MON_FAIRY_BLUE:MON_FAIRY_RED);
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_FAIRY_GREEN_WARRIOR:(randA(1)?MON_FAIRY_BLUE_MAGICIAN:MON_FAIRY_RED_COMMANDER));
		break;	
	case 69:
		index.push_back(MON_MOON_RABIT_SUPPORT);
		break;
	case 70:
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ATTACK);
		break;
	case 71:
		index.push_back(MON_MOON_RABIT_ELITE);
		break;		
	case 72:
		if(randA(3)==0)
			index.push_back(MON_MOON_RABIT_SUPPORT);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ATTACK);
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(MON_MOON_RABIT_ELITE);
		break;	
	case 73:
		index.push_back(MON_MAC);
		break;	
	case 74:
		index.push_back(MON_NIGHTMARE);
		break;	
	case 75:
		index.push_back(MON_LUNATIC);
		break;	
	case 76:
		for(int rand_ =rand_int(3,6), i=0;i<rand_;i++)
			index.push_back(MON_HAUNT);
		break;
	case 77:
		index.push_back(MON_FIRE_CAR);
		break;	
	case 78:
		index.push_back(MON_HELL_SPIDER);
		break;	
	case 79:
		index.push_back(MON_BLOOD_HAUNT);
		break;	
	case 80:
		index.push_back(MON_HELL_HOUND);
		if(randA(4)==0)
		{
			for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
				index.push_back(MON_HELL_HOUND);
		}
		break;	
	case 81:
		index.push_back(MON_FLOWER_TANK);
		break;	
	case 82:
		index.push_back(MON_EVIL_EYE_TANK);
		break;	
	case 83:
		index.push_back(MON_SNOW_GIRL);
		break;	
	case 84:
		index.push_back(MON_NAMAZ);
		break;	
	case 85:
		for(int rand_ =rand_int(3,6), i=0;i<rand_;i++)
			index.push_back(MON_HELL_CROW);
		break;	
	case 86:
		index.push_back(MON_RACCON);
		break;	
	case 87:
		index.push_back(MON_LANTERN_YOUKAI);
		break;
	case 88:
		index.push_back(MON_YINYAN);
		break;
	case 89:
		if(randA(2)==0)
		{
			for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
				index.push_back(MON_LITTLE_IMP);
		}
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_SARA:randA(1)?MON_LUIZE:MON_ELIS);
		break;
	case 90:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(MON_EVIL_EYE);
		index.push_back(MON_YUUGENMAGAN);
		break;
	case 91:
		index.push_back(MON_YUKI);
		break;
	case 92:
		index.push_back(MON_MAI);
		break;
	case 93:
		index.push_back(MON_SARIEL);
		for(int rand_ =rand_int(1,3), i=0;i<rand_;i++)
			index.push_back(randA(2)==0?MON_SARA:randA(1)?MON_LUIZE:MON_ELIS);
		break;
	case 94:
		index.push_back(MON_MUSHROOM);
		break;
	case 95:
		for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
			index.push_back(randA(4)?MON_RABIT_SPEAR:randA(1)?MON_RABIT_MAGIC:MON_RABIT_BOMB);
		if(randA(3)==0)
		{
			index.push_back(MON_RABIT_SUPPORT);
		}
		break;
	case 96:
		for(int rand_ =rand_int(2,3), i=0;i<rand_;i++)
			index.push_back(randA(1)?MON_ONI:MON_BLUE_ONI);
		break;
	case 97:
		index.push_back(MON_ALICEYUKKURI);
		break;
	case 98:
		index.push_back(MON_YOUMUYUKKURI);
		break;
	case 99:
		if(randA(2)==0)
		{
			for(int rand_ =rand_int(2,4), i=0;i<rand_;i++)
				index.push_back(MON_LITTLE_IMP);
		}
		for(int rand_ =rand_int(1,2), i=0;i<rand_;i++)
			index.push_back(randA(4)?MON_LUIZE:randA(1)?MON_SARA:MON_ELIS);
		break;
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
		{
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}	


int get_unique_to_id(int m_id)
{
	switch(m_id)
	{
	default: return -1;
	case MON_RUMIA:return 0;
	case MON_WRIGGLE: return 1;
	case MON_MISTIA: return 2;
	case MON_CIRNO: return 3;
	case MON_MEDICINE: return 4;
	case MON_DIEFAIRY: return 5;
	case MON_KISUME: return 6;
	case MON_CHEN: return 7;
	case MON_KOGASA: return 8;
	case MON_SUNNY:case MON_LUNAR:case MON_STAR: return 9;
	case MON_KYOUKO: return 10;
	case MON_FORTUNE_TELLER: return 11;
	case MON_MOMIZI: return 12;
	case MON_AYA: return 13;
	case MON_WAKASAGI: return 14;
	case MON_YAMAME: return 15;
	case MON_NAZRIN:case MON_DAUZING: return 16;
	case MON_YOSIKA: return 17;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
	case MON_SEKIBANKI_HEAD: return 18;
	case MON_NITORI: return 19;
	case MON_KEGERO: return 20;
	case MON_PARSI: return 21;
	case MON_BENBEN:
	case MON_YATHASI: return 22;
	case MON_ORIN:
	case MON_ORIN_CAT: return 23;
	case MON_ICHIRIN:
	case MON_UNZAN:
	case MON_UNZAN_PUNCH: return 24;
	case MON_PACHU: return 25;
	case MON_KOAKUMA: return 26;
	case MON_MEIRIN: return 27;
	case MON_SAKUYA: return 28;
	case MON_REMILIA: return 29;
	case MON_KASEN: return 30;
	case MON_KOISHI: return 31;
	case MON_NUE: return 32;
	case MON_FLAN: 
	case MON_FLAN_BUNSIN: return 33;
	case MON_TEWI:  return 34;
	case MON_CLOWNPIECE:  return 35;
	case MON_DOREMI:  return 36;
	case MON_LETTY:  return 37;
	case MON_YORIHIME:  return 38;
	case MON_TOYOHIME:  return 39;
	case MON_UTSUHO:  return 40;
	case MON_SUIKA:  return 41;
	case MON_REIMU:  return 42;
	case MON_ALICE:  return 43;
	case MON_SEIRAN:  return 44;
	case MON_RINGO:  return 45;
	case MON_UDONGE:  return 46;
	case MON_KAGUYA:  return 47;
	case MON_MOKOU:  return 48;
	case MON_TOKIKO: return 49;
	case MON_TOZIKO: return 50;
	case MON_FUTO: return 51;
	case MON_MAMIZO: return 52;
	}
}




void create_id_to_unique(int id, int level)
{
	vector<monster_index> index;

	switch(id)
	{
	case 0:
		index.push_back(MON_RUMIA);
		break;
	case 1:
		index.push_back(MON_WRIGGLE);
		break;
	case 2:
		index.push_back(MON_MISTIA);
		break;
	case 3:
		index.push_back(MON_CIRNO);
		break;
	case 4:
		index.push_back(MON_MEDICINE);
		break;
	case 5:
		index.push_back(MON_DIEFAIRY);
		break;
	case 6:
		{
			int x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
			{
				x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			}			
			env[level].MakeEvent(EVL_KISME,coord_def(x_,y_),EVT_APPROACH_SMALL);
		}
		break;
	case 7:
		index.push_back(MON_CHEN);
		for(int i=0;i<4;i++)
			index.push_back(randA(2)?(randA(1)?MON_ORANGE_CAT:MON_WHITE_CAT):MON_BLACK_CAT);
		break;
	case 8:
		index.push_back(MON_KOGASA);
		break;
	case 9:
		index.push_back(MON_SUNNY);
		index.push_back(MON_LUNAR);
		index.push_back(MON_STAR);
		break;
	case 10:
		index.push_back(MON_KYOUKO);
		break;
	case 11:
		index.push_back(MON_FORTUNE_TELLER);
		break;
	case 12:
		index.push_back(MON_MOMIZI);
		break;
	case 13:
		index.push_back(MON_AYA);
		break;
			
	case 14:	
		index.push_back(MON_WAKASAGI);
		break;
	case 15:
		index.push_back(MON_YAMAME);
		break;
	case 16:
		index.push_back(MON_NAZRIN);
		if(randA(2)<1)
		{			
			for(int rand_ =rand_int(2,5), i=0;i<rand_;i++)
				index.push_back(MON_RAT);
		}
		break;
	case 17:
		index.push_back(MON_YOSIKA);
		break;
	case 18:
		index.push_back(MON_SEKIBANKI);
		break;
	case 19:
		index.push_back(MON_NITORI);
		if(randA(2)<1)
		{			
			index.push_back(MON_KATPA);
			index.push_back(MON_KATPA_SPEAR);
			index.push_back(MON_KATPA_WATER_WIZARD);
		}
		break;
	case 20:
		index.push_back(MON_KEGERO);
		break;		
	case 21:
		index.push_back(MON_PARSI);
		break;	
	case 22:
		index.push_back(MON_BENBEN);
		index.push_back(MON_YATHASI);
		break;
	case 23:
		index.push_back(MON_ORIN);
		for(int rand_ =rand_int(3,4), i=0;i<rand_;i++)
			index.push_back(MON_ZOMBIE_FAIRY);
		break;
	case 24:
		index.push_back(MON_ICHIRIN);
		break;	
	case 25:
		//홍마관 도서관 고정 출현
		index.push_back(MON_PACHU);
		break;	
	case 26:
		index.push_back(MON_KOAKUMA);
		break;	
	case 27:
		//아마 이 번호는 안쓰려나? 메이린은 홍마관 입구 고정 출현
		index.push_back(MON_MEIRIN);
		break;	
	case 28:
		index.push_back(MON_SAKUYA);
		break;	
	case 29:
		//역시 홍마관 최심층 고정출현(랜덤등장없음)
		index.push_back(MON_REMILIA);
		break;		
	case 30:
		index.push_back(MON_KASEN);
		index.push_back(MON_EAGLE);
		index.push_back(MON_TIGER);
		index.push_back(MON_RAIJUU);
		index.push_back(MON_DRAGON_BABY);
		break;	
	case 31:
		if(randA(5)==0)
		{
			int x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y_))
			{
				x_=randA(DG_MAX_X-1),y_=randA(DG_MAX_Y-1);
			}			
			env[level].MakeEvent(EVL_KOISHI,coord_def(x_,y_),EVT_APPROACH_SMALL);
		}
		else
			index.push_back(MON_KOISHI);
		break;
	case 32:
		index.push_back(MON_NUE);
		break;
	case 33:
		index.push_back(MON_FLAN);
		break;
	case 34:
		index.push_back(MON_TEWI);
		break;
	case 35:
		index.push_back(MON_CLOWNPIECE);
		break;
	case 36:
		index.push_back(MON_DOREMI);
		break;
	case 37:
		index.push_back(MON_LETTY);
		break;
	case 38: //달의도시 고정네임드
		index.push_back(MON_YORIHIME);
		break;
	case 39: //달의도시 고정네임드
		index.push_back(MON_TOYOHIME);
		break;
	case 40: //지령전 고정네임드
		index.push_back(MON_UTSUHO);
		break;
	case 41:
		index.push_back(MON_SUIKA);
		break;
	case 42: //최종보스
		index.push_back(MON_REIMU);
		break;
	case 43:
		index.push_back(MON_ALICE);
		break;
	case 44:
		index.push_back(MON_SEIRAN);
		break;
	case 45:
		index.push_back(MON_RINGO);
		break;
	case 46: //영원정 고정
		index.push_back(MON_UDONGE);
		break;
	case 47: //영원정 고정
		index.push_back(MON_KAGUYA);
		break;
	case 48:
		index.push_back(MON_MOKOU);
		break;
	case 49:
		index.push_back(MON_TOKIKO);
		break;
	case 50:
		index.push_back(MON_TOZIKO);
		break;
	case 51:
		index.push_back(MON_FUTO);
		break;
	case 52:
		index.push_back(MON_MAMIZO);
		break;
	}

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<monster_index>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0, limit_ = 10000;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		bool only_water = (mondata[(*it)].flag & M_FLAG_CANT_GROUND) && (mondata[(*it)].flag & M_FLAG_SWIM);
		while(!env[level].isMove(x_,y_,false, only_water, only_water) || 
			(env[level].dgtile[x_][y_].flag & FLAG_NO_MONSTER) || 
			env[level].isMonsterPos(x_,y_) || env[level].isStair(x_,y))
		{
			if(limit_--<0)
				break;
			if(it==index.begin())
			{
				x = randA(DG_MAX_X-1),y = randA(DG_MAX_Y-1);
			}
			else
			{
				rand_x=rand_int(-r,r);
				rand_y=rand_int(-r,r);
				if(++k%5 == 0)
				{
					r++;
				}
			}
			Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		}
		if(limit_<=0)
			continue;

			
		if(env[level].AddMonster((*it),0,coord_def(x_,y_)))
		{
			continue;
		}
		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}
}


void SetResistMonster(monster* mon)
{
	mon->ice_resist = 0;
	mon->fire_resist = 0;
	mon->poison_resist=0;
	mon->elec_resist=0;
	switch(mon->id)
	{
	case MON_CIRNO:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		break;
	case MON_MISTIA:
		mon->poison_resist=-1;
		mon->wind_resist=1;
		break;
	case MON_MEDICINE:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_DIEFAIRY:
		mon->ice_resist=1;
		break;
	case MON_GHOST:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_BAKEKASA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_GREEN_MOOK:
		mon->poison_resist=1;
		break;
	case MON_KOGASA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_CROW_TENGU:
		mon->wind_resist=1;
		break;
	case MON_ONI:
		mon->fire_resist=1;
		break;
	case MON_REMILIAYUKKURI:
		mon->poison_resist=1;
		break;
	case MON_KATPA_WATER_WIZARD:
		mon->ice_resist=1;
		break;
	case MON_YAMABUSH_TENGU:
		mon->wind_resist=1;
		break;
	case MON_HANATACA_TENGU:
		mon->poison_resist=1;
		mon->wind_resist=1;
		break;
	case MON_BLUE_ONI:
		mon->ice_resist=1;
		break;
	case MON_MUSHROOM:
		mon->poison_resist=1;
		break;
	case MON_AYA:
		mon->wind_resist=1;
		break;
	case MON_WAKASAGI:
		mon->ice_resist=1;
		break;
	case MON_YAMAME:		
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_NAZRIN:
		mon->poison_resist=1;
		break;
	case MON_DAUZING:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_YOSIKA:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_BODY:
		mon->fire_resist=1;
		break;
	case MON_NITORI:
		mon->elec_resist=2;
		mon->ice_resist=2;
		break;
	case MON_BENBEN:
	case MON_YATHASI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ORIN:		
	case MON_ORIN_CAT:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ZOMBIE_FAIRY:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_ICHIRIN:
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->elec_resist=1;
		break;
	case MON_UNZAN:
	case MON_UNZAN_PUNCH:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_PACHU:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_MAGIC_BOOK:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HOBGOBRIN_MAID:
		mon->poison_resist=1;
		break;
	case MON_HOBGOBRIN_LIBRARIAN:
		mon->ice_resist=1;
		mon->fire_resist=1;
		break;
	case MON_CHUPARCABRA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_KOAKUMA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_REMILIA:
		mon->ice_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_RAIJUU:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_TIGER:
		mon->ice_resist=1;
		break;
	case MON_DRAGON_BABY:
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YAMAWARO_NINJA:
	case MON_YAMAWARO_WAWRRIOR:
	case MON_YAMAWARO_FLAG:
		mon->fire_resist=1;
		break;
	case MON_ONBASIRA:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;		
	case MON_RED_UFO:
		mon->fire_resist=2;
		break;
	case MON_GREEN_UFO:
		mon->elec_resist=2;
		mon->poison_resist=1;
		break;
	case MON_BLUE_UFO:
		mon->ice_resist=2;
		break;
	case MON_NUE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_SANPEI_FIGHTER:
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_DEAGAMA:
		mon->poison_resist=1;
		break;
	case MON_NAMAZ:
		mon->elec_resist=1;
		break;
	case MON_HELL_CROW:
		mon->fire_resist=2;
		break;
	case MON_LANTERN_YOUKAI:
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_YINYAN:
		mon->elec_resist=2;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_YUUGENMAGAN:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;
	case MON_ELIS:
		mon->elec_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARIEL:
		mon->elec_resist=1;
		mon->ice_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SARA:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_LUIZE:
		mon->ice_resist=1;
		break;
	case MON_YUKI:
		mon->fire_resist=3;
		break;
	case MON_MAI:
		mon->ice_resist=3;
		break;
	case MON_YUMEKO:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->fire_resist=2;
		mon->poison_resist=1;
		break;
	case MON_MAGICAL_STAR:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_GOLEM:
		mon->elec_resist=3;
		mon->ice_resist=2;
		mon->fire_resist=2;
		mon->poison_resist=1;
	case MON_EVIL_EYE:
		mon->elec_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_SCHEMA_EYE:
		mon->elec_resist=3;
		mon->ice_resist=3;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;		
	case MON_FLAN:
	case MON_FLAN_BUNSIN:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_TEWI:
		break;
	case MON_CLOWNPIECE:
		mon->fire_resist=2;
		break;
	case MON_DOREMI:
		mon->elec_resist=1;
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;		
	case MON_FAIRY_HERO:
		break;
	case MON_FAIRY_SOCERER:
		mon->ice_resist=1;
		break;
	case MON_FAIRY_SUN_FLOWER:
		mon->fire_resist=1;
		break;
	case MON_MOON_RABIT_SUPPORT:
		mon->confuse_resist=1;
		break;
	case MON_MOON_RABIT_ATTACK:
		mon->confuse_resist=1;
		break;
	case MON_MOON_RABIT_ELITE:
		mon->confuse_resist=1;
		break;
	case MON_MAC:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_NIGHTMARE:
		mon->elec_resist=2;
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_LUNATIC:
		mon->elec_resist=2;
		mon->fire_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HAUNT:
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_FIRE_CAR:
		mon->ice_resist=-1;
		mon->fire_resist=3;
		mon->poison_resist=1;
		break;
	case MON_HELL_SPIDER:
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_BLOOD_HAUNT:
		mon->elec_resist=1;
		mon->fire_resist=1;
		mon->poison_resist=1;
		break;
	case MON_HELL_HOUND:
		mon->fire_resist=1;
		break;
	case MON_DESIRE:
		break;
	case MON_FLOWER_TANK:
		mon->ice_resist=1;
		mon->elec_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_EVIL_EYE_TANK:
		mon->ice_resist=1;
		mon->elec_resist=3;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_SNOW_GIRL:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		break;
	case MON_LETTY:
		mon->ice_resist=3;
		mon->fire_resist=-1;
		mon->poison_resist=1;
		break;
	case MON_YORIHIME:
		mon->ice_resist=2;
		mon->elec_resist=2;
		mon->confuse_resist=1;
		break;
	case MON_TOYOHIME:
		mon->ice_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_UTSUHO:
		mon->poison_resist=1;
		mon->fire_resist=3;
		break;
	case MON_SUIKA:
		mon->fire_resist=2;
		break;
	case MON_REIMU:
		break;
	case MON_ALICE:
		mon->elec_resist=1;
		mon->poison_resist=1;
		break;
	case MON_SEIRAN:
		mon->confuse_resist=1;
		break;
	case MON_RINGO:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_UDONGE:
		mon->elec_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_KAGUYA:
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_MOKOU:
		mon->fire_resist=3;
		break;
	case MON_NESI:
		mon->fire_resist=2;
		mon->ice_resist=2;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_SANGHAI:
	case MON_FAKE_SANGHAI:
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_HOURAI:
	case MON_FAKE_HOURAI:
		mon->elec_resist=1;
		mon->fire_resist=1;
		mon->ice_resist=1;
		mon->poison_resist=1;
		mon->confuse_resist=1;
		break;
	case MON_TOKIKO:
		mon->wind_resist=1;
		mon->poison_resist=-1;
		break;
	case MON_TOZIKO:
		mon->elec_resist=3;
		mon->ice_resist=1;
		mon->poison_resist=1;
		break;
	case MON_FUTO:
		mon->fire_resist=2;
		break;
	case MON_MAMIZO:
		break;
	}
}