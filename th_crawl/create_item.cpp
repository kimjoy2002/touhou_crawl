//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: create_item.cpp
//
// 내용: 맵에 맞는 아이템을 생성한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "item.h"
#include "spellcard.h"



extern void Set_X_Y(int &x_, int x, int rand_x, int &y_, int y, int rand_y);

void create_id_to_item(int id, int level);

struct item_group
{
	int id; //고유번호 <- 고유번호
	int min_level; //최소레벨 <- 나오는 던전 층
	int max_level; //최대레벨 <- 나오는 던전 층
	int percent; //확률  <- 나올 빈도를 결정한다.
	int rare; //레어도
};


item_group item_index[] = //아이템 목록(꼭 2번째를 내림차순으로 정렬)
{
	{0,0,SCARLET_LEVEL_LAST_LEVEL,20,1}, //잡 탄막들
	{1,0,SCARLET_LEVEL_LAST_LEVEL,5,1}, //기타방어구들(장갑, 부츠, 망토등)
	{21,0,SCARLET_LEVEL_LAST_LEVEL,2,1}, //음식
	
	
	{2,0,7,70,1}, //초반 잘나오는 좋은 물약들
	{3,0,7,80,1}, //초반 잘나오는 좋은 두루마리들
	{4,0,7,15,1}, //초반 잘나오는 나쁜 물약들
	//{5,0,7,15,1}, //초반 잘나오는 나쁜 두루마리들
	{6,0,7,80,1}, //초반용 무기
	{7,0,7,20,1}, //초반용 방어구
	{8,0,7,15,1}, //초반용 좋은 반지, 아뮬렛들
	{9,0,7,1,1}, //초반용 나쁜 반지, 아뮬렛들
	{10,0,7,3,1}, //초반용 방패
	{11,0,7,0,1}, //초반용 빈칸
	{12,0,7,0,1}, //초반용 빈칸
	{26,0,7,5,1},//스펠카드
	{27,2,4,2,1},//아티펙트무기
	{28,2,4,2,1},//아티펙트방어구
	{29,2,4,2,1},//아티펙트반지

	{25,2,SCARLET_LEVEL_LAST_LEVEL,3,1}, //책
	
	{13,5,SCARLET_LEVEL_LAST_LEVEL,70,1}, //중반 잘나오는 좋은 물약들
	{14,5,SCARLET_LEVEL_LAST_LEVEL,70,1}, //중반 잘나오는 좋은 두루마리들
	{15,5,SCARLET_LEVEL_LAST_LEVEL,15,1}, //중반 잘나오는 나쁜 물약들
	//{16,5,SCARLET_LEVEL_LAST_LEVEL,15,1}, //중반 잘나오는 나쁜 두루마리들
	{17,5,SCARLET_LEVEL_LAST_LEVEL,80,1}, //중반용 무기들(가끔 저주)
	{18,5,SCARLET_LEVEL_LAST_LEVEL,20,1}, //중반용 방어구
	{19,5,SCARLET_LEVEL_LAST_LEVEL,15,1}, //중반용 좋은 반지, 아뮬렛들
	{20,5,SCARLET_LEVEL_LAST_LEVEL,1,1}, //중반용 나쁜 반지, 아뮬렛들
	{22,5,SCARLET_LEVEL_LAST_LEVEL,3,1}, //중반용 방패
	{23,5,SCARLET_LEVEL_LAST_LEVEL,0,1}, //중반용 빈칸
	{24,5,SCARLET_LEVEL_LAST_LEVEL,0,1}, //중반용 빈칸
	{26,5,SCARLET_LEVEL_LAST_LEVEL,5,1},
	{27,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//아티펙트무기
	{28,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//아티펙트방어구
	{29,5,SCARLET_LEVEL_LAST_LEVEL,4,1},//아티펙트반지

	//윳쿠리
	{13,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //중반 잘나오는 좋은 물약들
	{14,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //중반 잘나오는 좋은 두루마리들
	{17,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,30,1}, //중반용 무기들(가끔 저주)
	{18,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,30,1}, //중반용 방어구
	{19,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,30,1}, //중반용 좋은 반지, 아뮬렛들
	{0,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //잡 탄막들
	{1,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1}, //기타방어구들(장갑, 부츠, 망토등)
	{21,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,5,1}, //음식
	{22,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,5,1}, //중반용 방패
	{25,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,20,1}, //책
	{26,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1}, //스펠카드
	{27,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//아티펙트무기
	{28,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//아티펙트방어구
	{29,YUKKURI_LAST_LEVEL,YUKKURI_LAST_LEVEL,10,1},//아티펙트반지

	//판데모니엄
	{13,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,70,1}, //중반 잘나오는 좋은 물약들
	{14,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,70,1}, //중반 잘나오는 좋은 두루마리들
	{15,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,30,1}, //중반 잘나오는 나쁜 물약들
	{17,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,80,1}, //중반용 무기들(가끔 저주)
	{18,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,20,1}, //중반용 방어구
	{19,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //중반용 좋은 반지, 아뮬렛들
	{0,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,20,1}, //잡 탄막들
	{1,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //기타방어구들(장갑, 부츠, 망토등)
	{25,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,10,1}, //책
	{26,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,15,1}, //스펠카드
	{21,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,5,1}, //음식
	{22,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,5,1}, //중반용 방패
	{27,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//아티펙트무기
	{28,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//아티펙트방어구
	{29,PANDEMONIUM_LEVEL,PANDEMONIUM_LAST_LEVEL,4,1},//아티펙트반지


	{-1,0,0,0,0}

};

item_infor& id_to_item(int id, item_infor* item_);


item_infor& CreateFloorItem(int floor, item_infor* item_)
{
	int i = 0, total=0;
	vector<item_group*> group;
	group.reserve(128);
	while(item_index[i].id != -1)
	{
		if(item_index[i].min_level<=floor && item_index[i].max_level>=floor && item_index[i].percent)
		{
			group.push_back(&item_index[i]);
			total+=item_index[i].percent;
		}
		else if(item_index[i].min_level > floor)
			break;
		i++;
	}

	int rand_ = randA_1(total);
	vector<item_group*>::iterator it;
	for(it = group.begin(); it != group.end(); it++)
	{
		if(rand_<=(*it)->percent)
		{
			id_to_item((*it)->id, item_);
			return (*item_);
		}
		else
			rand_ -= (*it)->percent;
	
	}

}




void create_item(int floor, int num_)
{
	if(num_ == 0)
		return;

	int i = 0, total=0, num = num_?num_:10;
	vector<item_group*> group;
	group.reserve(128);
	while(item_index[i].id != -1)
	{
		if(item_index[i].min_level<=floor && item_index[i].max_level>=floor && item_index[i].percent)
		{
			group.push_back(&item_index[i]);
			total+=item_index[i].percent;
		}
		else if(item_index[i].min_level > floor)
			break;
		i++;
	}

	for(int i = 0; i<num; i++)
	{
		int rand_ = randA_1(total);
		vector<item_group*>::iterator it;
		for(it = group.begin(); it != group.end(); it++)
		{
			if(rand_<=(*it)->percent)
			{
				create_id_to_item((*it)->id, floor);
				break;
			}
			else
				rand_ -= (*it)->percent;
	
		}
	}
}


item_infor& id_to_item(int id, item_infor* item_)
{	
	switch(id)
	{
	case 0:
		makeitem(ITM_THROW_TANMAC, 0,item_);
		break;
	case 1:
		makeitem((item_type)rand_int(ITM_ARMOR_HEAD,ITM_ARMOR_BOOT),rand_int(2,-1),item_);
		break;
	case 2: //굿 초반물약
		makeitem(ITM_POTION,randA(1)>0?1:(randA(60)?2:3),item_);
		break;
	case 3: //굿 초반스크롤
		makeitem(ITM_SCROLL,randA(2)>0?1:(randA(60)?2:3),item_);
		break;
	case 4: //배드 초반물약
		makeitem(ITM_POTION,-1,item_);
		break;
	case 5: //배드 초반스크롤
		makeitem(ITM_SCROLL,-1,item_);
		break;
	case 6: //흔한 무기
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(6)?0:(randA(3)?1:-1),item_);
		break;
	case 7://흔한 방어구
		makeitem((item_type)(ITM_ARMOR_BODY_FIRST+randA(randA(ITM_ARMOR_BODY_LAST-ITM_ARMOR_BODY_FIRST-1))),randA(4)?1:(randA(3)?1:-1),item_);
		break;
	case 8://흔한 좋은 장신구
		makeitem(1/*randA(4)*/?ITM_RING:ITM_SPELLCARD,1,item_);
		break;
	case 9://흔한 나쁜 장신구
		makeitem(1/*randA(4)*/?ITM_RING:ITM_SPELLCARD,-1,item_);
		break;
	case 10://흔한 방패
		makeitem(ITM_ARMOR_SHIELD,randA(4)?0:(randA(3)?1:-1),item_);
		break;

		
	case 13: //굿 중반물약
		makeitem(ITM_POTION,randA(1)>0?1:(randA(30)?2:3),item_);
		break;
	case 14: //굿 중반스크롤
		makeitem(ITM_SCROLL,randA(2)>0?1:(randA(30)?2:3),item_);
		break;
	case 15: //배드 중반물약
		makeitem(ITM_POTION,randA(3)?-1:-2,item_);
		break;
	case 16: //배드 중반스크롤
		makeitem(ITM_SCROLL,randA(3)?-1:-2,item_);
		break;
	case 17: //중반 무기 - 고침
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(3)?0:(randA(3)?1:-1),item_);
		break;
	case 18://중반 방어구 - 고침
		makeitem((item_type)rand_int(ITM_ARMOR_BODY_FIRST,ITM_ARMOR_BODY_LAST-1),randA(3)?0:(randA(3)?1:-1),item_);
		break;
	case 19://중반 좋은 장신구
		makeitem(/*randA(4)*/1?ITM_RING:ITM_SPELLCARD,randA(2)?2:1,item_);
		break;
	case 20://중반 나쁜 장신구
		makeitem(/*randA(4)*/1?ITM_RING:ITM_SPELLCARD,randA(1)?-2:-1,item_);
		break;
	case 21://음식
		makeitem(ITM_FOOD,0,item_);
		break;
	case 22://중반 방패
		makeitem(ITM_ARMOR_SHIELD,randA(3)?0:(randA(3)?1:-1),item_);
		break;
	case 25://책
		makeitem(ITM_BOOK,0,item_);
		break;
	case 26://스펠카드
		makeitem(ITM_SPELL,0,item_);
		//index.push_back(createSpellCard(1, 0, item_));
		break;
	case 27://아티펙트 무기
		makeitem((item_type)rand_int(ITM_WEAPON_FIRST,ITM_WEAPON_CLOSE),randA(2)?0:(randA(3)?1:-1),item_);
		item_->artifact = true;
		break;
	case 28://아티펙트 방어구
		makeitem((item_type)(ITM_ARMOR_BODY_FIRST+randA(randA(ITM_ARMOR_BODY_LAST-ITM_ARMOR_BODY_FIRST-1))),randA(2)?0:(randA(3)?1:-1),item_);
		item_->artifact = true;
		break;
	case 29://아티펙트 반지
		makeitem(ITM_RING,randA(9)?1:-1,item_);
		item_->artifact = true;
		break;
	default:
		break;
	}
	return (*item_);
}

void create_id_to_item(int id, int level)
{
	vector<item_infor> index;
	item_infor temp;


	index.push_back(id_to_item(id, &temp));

	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1),rand_x=0,rand_y=0, r=2+index.size()/3,k=0;
	for(vector<item_infor>::iterator it=index.begin();it!=index.end();it++)
	{ 
		int x_ = 0, y_ = 0;
		Set_X_Y(x_, x, rand_x, y_, y, rand_y);
		while(!env[level].isMove(x_,y_) || (env[level].dgtile[x_][y_].flag & FLAG_NO_ITEM) || env[level].isStair(x_,y))
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
		item* item_ = env[level].MakeItem(coord_def(x_,y_),(*it));
		if((*it).artifact)
		{
			if((item_->type>=ITM_WEAPON_FIRST && item_->type< ITM_WEAPON_LAST)||(item_->type>=ITM_ARMOR_FIRST && item_->type< ITM_ARMOR_LAST)||(item_->type>=ITM_JEWELRY_FIRST && item_->type< ITM_JEWELRY_LAST))
			{ //아티펙트 만들기
					MakeArtifact(item_,item_->curse?-1:1);
			}
		}

		k = 0;
		r=2+index.size()/3;
		rand_x=rand_int(-r,r);
		rand_y=rand_int(-r,r);
	}


}