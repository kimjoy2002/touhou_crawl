//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: throw.cpp
//
// 내용: 탄막던지기 관련 함수 & 탄막 그래픽 처리 등등
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "mon_infor.h"
#include "monster_texture.h"
#include "item.h"
#include "environment.h"
#include "throw.h"
#include "key.h"
#include "projectile.h"
#include "skill_use.h"
#include "rect.h"
#include "weapon.h"
#include "option_manager.h"


int GetTanmacGraphicType(tanmac_type type)
{
	switch(type)
	{
		//case TMT_BILL:
		//	return 1;
		case TMT_AMULET:
			return 2;			
		case TMT_POISON_NEEDLE:
			return 20;
		case TMT_KIKU_COMPRESSER:
			return 18;
		case TMT_DOGGOJEO:
			return 43;
		/*아이템에서 나오지않는 번호들
			return 10;
			return 11;
			return 12;
			return 13;
			return 14;
			return 15; //여까진 동근 탄막
			return 16; //큰불
			return 17; //작은불
			return 18; //아이스
			return 19; //작은아이스
			return 20; //작은독
			return 21; //전기
			return 22; //큰아이스
			return 23; //큰독
			return 24; //안개
			return 25; //에어커터
			return 26; //작은 돌
			return 27; //포션
			return 28; //카나메석
		여까지마법전용 번호들(리턴될일이 없다.)*/
		default:
			return 0;
	}
}
attack_type GetTanmacAttackType(tanmac_type type)
{
	switch(type)
	{
		case TMT_AMULET:
		case TMT_KIKU_COMPRESSER:
			return ATT_THROW_NORMAL;			
		case TMT_POISON_NEEDLE:
			return ATT_THROW_WEAK_POISON;
		default:
			break;
	}
	return ATT_THROW_NORMAL;
}
attack_type GetWeapontoTanmac(weapon_brand brand)
{
	attack_type att_type = ATT_THROW_NORMAL;
	switch(brand)
	{
		case WB_FIRE:
			att_type = ATT_THROW_FIRE;
			break;
		case WB_COLD:
			att_type = ATT_THROW_COLD;
			break;
		case WB_POISON:
			att_type = ATT_THROW_WEAK_POISON;
			break;		
		case WB_CURSE:		
		case WB_WEATHER	:
		case WB_AUTUMN:
		case WB_MANA_REGEN:
		case WB_FAST_CAST:
		case WB_PROTECT:
		default:
			break;
	}
	return att_type;	
}


bool TanmacDeleteRand(tanmac_type type, bool isCanDelete_)
{
	switch(type)
	{
		case TMT_AMULET:
		case TMT_POISON_NEEDLE:
		case TMT_DOGGOJEO:
			return isCanDelete_?true:(randA(9)==0);
		case TMT_KIKU_COMPRESSER:
			return true;
		default:
			break;
	}
	return false;
}
void MakeTanmac(item_infor* t, int select_)
{

	tanmac_type type = TMT_AMULET;
	
	random_extraction<tanmac_type> rand_;

	rand_.push(TMT_POISON_NEEDLE,20);

	rand_.push(TMT_AMULET, 30);
	rand_.push(TMT_KIKU_COMPRESSER, 10);
	rand_.push(TMT_DOGGOJEO, 10);

	type = rand_.pop();
	
	if(select_ != -1)
		type = (tanmac_type)select_;

	switch(type)
	{
	case TMT_AMULET:
		t->value1 = 15;
		t->value2 = 7;
		t->value3 = 0;
		t->value4 = TMT_AMULET;
		t->value5 = 0;
		t->value6 = 0;
		t->value7 = 0;
		t->value8 = 0;
		t->num = (select_ != -1)?10:rand_int(2,8);
		t->is_pile = true;
		t->can_throw = true;
		t->image = GetTanmacBaseGraphic(t->value4);
		t->name = name_infor(GetTanmacKey(t->value4));
		t->weight = 0.5f*t->num;
		t->value = 20;
		break;
	case TMT_POISON_NEEDLE:
		t->value1 = 9;
		t->value2 = 2;
		t->value3 = 0;
		t->value4 = TMT_POISON_NEEDLE;
		t->value5 = 0;
		t->value6 = 0;
		t->value7 = 0;
		t->value8 = 0;
		t->num = (select_ != -1)?8:rand_int(3,15);
		t->is_pile = true;
		t->can_throw = true;
		t->image = GetTanmacBaseGraphic(t->value4);
		t->name = name_infor(GetTanmacKey(t->value4));
		t->weight = 0.1f*t->num;
		t->value = 2;
		break;
	case TMT_KIKU_COMPRESSER:	
		t->value1 = 1;
		t->value2 = 4;
		t->value3 = 0;
		t->value4 = TMT_KIKU_COMPRESSER;
		t->value5 = 0;
		t->value6 = 0;
		t->value7 = 0;
		t->value8 = 0;
		t->num = (select_ != -1)?10:rand_int(3,15);
		t->is_pile = true;
		t->can_throw = true;
		t->image = GetTanmacBaseGraphic(t->value4);
		t->name = name_infor(GetTanmacKey(t->value4));
		t->weight = 0.5f*t->num;
		t->value = 100;
		break;
	case TMT_DOGGOJEO:
		t->value1 = 6;
		t->value2 = 9;
		t->value3 = 0;
		t->value4 = TMT_DOGGOJEO;
		t->value5 = 0;
		t->value6 = 0;
		t->value7 = 0;
		t->value8 = 0;
		t->num = (select_ != -1) ? 10 : rand_int(2, 8);
		t->is_pile = true;
		t->can_throw = true;
		t->image = GetTanmacBaseGraphic(t->value4);
		t->name = name_infor(GetTanmacKey(t->value4));
		t->weight = 0.5f*t->num;
		t->value = 20;
		break;
	default:
		break;
	}


}
int PathToNum(int path)
{
	//레이져(주로 전기계열)의 사용타일을 정하기위한 switch문
	//7 0 1
	//6 * 2
	//5 4 3
	//위와 같은 타일대로한다.
	//여기서 십의자리에서 들어가서 일의 자리로 나간다고 가정(들어가는것과 나가는것이 바뀌어도 같음)
	//여기서 특수케이스로 8은 시작점일때, 9는 도착점일때로 취급한다.
	//해당 경로에 맞는 이미지배열의 인덱스를 리턴한다.
	//레이져형 도트를 만들때 아래와 같은 인덱스를 부여해서 만들자.(90도 이상 꺽이는건 제외했음)
	switch(path)
	{
	case 80:case 8:return 0;
	case 81:case 18:return 1;
	case 82:case 28:return 2;
	case 83:case 38:return 3;
	case 84:case 48:return 4;
	case 85:case 58:return 5;
	case 86:case 68:return 6;
	case 87:case 78:return 7;
	case 30:case 3:return 8;
	case 40:case 4:return 9;
	case 41:case 14:return 10;
	case 50:case 5:return 11;
	case 51:case 15:return 12;
	case 52:case 25:return 13;
	case 61:case 16:return 14;
	case 62:case 26:return 15;
	case 63:case 36:return 16;
	case 72:case 27:return 17;
	case 73:case 37:return 18;
	case 74:case 47:return 19;
	case 90:case 9:return 20;
	case 91:case 19:return 21;
	case 92:case 29:return 22;
	case 93:case 39:return 23;
	case 94:case 49:return 24;
	case 95:case 59:return 25;
	case 96:case 69:return 26;
	case 97:case 79:return 27;
	default:return 28;
	}
}
bool isStartGraphic(int type)
{
	if(type == 21)
		return true;
	return false;
}


textures* GetTanmacGraphic(int type, int direc, int count, int path)
{
	switch(type)
	{
	default:
	case 0://없음 이거 뜨면 버그
	case 1:
		return &img_tanmac_bill[direc];
	case 2:
		return &img_tanmac_amulet[count%2];
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		return &img_effect_tanmac_middle[type-10];
	case 16:
		return &img_tanmac_fire_big[direc];
	case 17:
		return &img_tanmac_fire_small[direc];
	case 18:
		return &img_tanmac_ice[randA(3)];
	case 19:
		return &img_tanmac_ice_small[direc];
	case 20:
		return &img_tanmac_poison_small[direc];
	case 21:
		return &img_laser[PathToNum(path)];
	case 22:
		return &img_tanmac_ice_big[direc];
	case 23:
		return &img_tanmac_poison_big[direc];
	case 24:
		return &img_fog_normal[count%2];
	case 25:
		return &img_tanmac_air[direc];
	case 26:
		return &img_tanmac_rock_small[direc];
	case 27:
		return &img_item_potion[0];
	case 28:
		return &img_tanmac_rock_big[direc];
	case 29:
		return &img_laser_small[direc%4];
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
		return &img_tanmac_small[type-30][direc%4];
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
		return &img_blast[type-36];
	case 42:
		return &img_thunder[PathToNum(path)];
	case 43:
		return &img_tanmac_doggojeo[direc];
	case 44:
		return &img_tanmac_sion[direc];
	case 45:
		return &img_autumn_edge[direc];
	case 46:
		return &img_tanmac_master_spark[direc];
	case 47:
		return &img_tanmac_sword[direc];
	case 48:
		return &img_tanmac_knife[direc];
	case 49:
		return &img_tanmac_oil_big[direc];
	}
}

textures* GetBorderGraphic(coord_def center, coord_def target, int size_x, int size_y, int count)
{
    int dx = target.x - center.x;
    int dy = target.y - center.y;

    bool isWhiteTile = (center.x + center.y + count) % 2 == 0;

	if(!(((abs(dx) - size_x == 0 || abs(dx) - size_x == 1) && size_y >= abs(dy)) ||
      ((abs(dy) - size_y == 0 || abs(dy) - size_y == 1) && size_x >= abs(dx)))) {
        return nullptr;
	}
	
	int direction = 0;
    if (dx > 0 && dy < 0 && abs(dx) == abs(dy)) direction = 4; // ↗
    else if (dx > 0 && dy > 0 && abs(dx) == abs(dy)) direction = 5;  // ↘
    else if (dx < 0 && dy > 0 && abs(dx) == abs(dy)) direction = 6; // ↙
    else if (dx < 0 && dy < 0 && abs(dx) == abs(dy)) direction = 7; // ↖
    else if (abs(dy) > abs(dx) && (dy == -size_y || dy == 1+size_y)) direction = 0;     // ↑
    else if (abs(dy) < abs(dx) && (dx == size_x || dx == -1-size_x)) direction = 1; // →
    else if (abs(dy) > abs(dx) && (dy == size_y || dy == -1-size_y)) direction = 2; // ↓
    else if (abs(dy) < abs(dx) && (dx == -size_x || dx == 1+size_x)) direction = 3; // ←
    else
        return nullptr; 

    int index = isWhiteTile ? direction : direction + 8;

    if (index < 0 || index >= 16) {
        return nullptr;
	}		

	return &img_border[index];
}

textures* GetTanmacBaseGraphic(int type)
{
	switch(type)
	{
	default://없음 이거 뜨면 버그
	//case TMT_BILL:
	//	return &img_tanmac_bill[1];
		return &img_tanmac_bill[1];
	case TMT_AMULET:
		return &img_tanmac_amulet[0];
	case TMT_POISON_NEEDLE:
		return &img_item_needle;
	case TMT_KIKU_COMPRESSER:
		return &img_item_kikuichi;
	case TMT_DOGGOJEO:
		return &img_item_doggojeo;
	}
}

LOCALIZATION_ENUM_KEY GetTanmacKey(int type)
{
	switch(type)
	{
	default://없음 이거 뜨면 버그
		return LOC_SYSTEM_ITEM_TANMAC_BUG;
	case TMT_AMULET:
		return LOC_SYSTEM_ITEM_TANMAC_AMULET;
	case TMT_POISON_NEEDLE:
		return LOC_SYSTEM_ITEM_TANMAC_POISON_NEEDLE;
	case TMT_KIKU_COMPRESSER:
		return LOC_SYSTEM_ITEM_TANMAC_KIKU_COMPRESSER;
	case TMT_DOGGOJEO:
		return LOC_SYSTEM_ITEM_TANMAC_DOGGOJEO;
	}
}
coord_def throwtanmac_(int graphic_type, textures* t_, beam_iterator& beam, const beam_infor &infor_, item* item_, bool effect_delete, bool mimic_)
{
	beam.init();
	coord_def prev = beam.start_pos();
	int penetrate = infor_.penetrate;
	int direc = beam.GetDirec();
	int length = 1;
	int count = 0;
	int path = 8;
	switch(infor_.type1)
	{
	case BMT_NORMAL:
	case BMT_WALL:
	case BMT_PENETRATE:
	default:
		if(isStartGraphic(graphic_type))
		{
			coord_def postion_ = prev;
			int path_ = 80+GetPosToDirec(prev,(*beam));
			if(graphic_type || !item_)
				env[current_level].MakeEffect(postion_,GetTanmacGraphic(graphic_type, direc, count++,path_),false);
			else if(item_) //자체 그래픽이 없고 item일 경우 item 그래픽을 그대로 쓴다.
				env[current_level].MakeEffect(postion_,item_->image,false);
		}
		while(env[current_level].isMove(*(beam),true) && penetrate>0 && length>0)
		{
			for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
			{
				if((*it).isLive() && (*it).position.x == (*beam).x && (*it).position.y == (*beam).y &&
					!(*it).isPassedBullet(infor_.order)
					)
				{
					attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
					if((*it).damage(temp_att))
						penetrate--;
				}
			}
			if(!infor_.order->isplayer() && you.position.x == (*beam).x && you.position.y == (*beam).y &&				
				!you.isPassedBullet(infor_.order)
				) //플레이어는 자기자신에게 맞지않는 조건은 나중에 지울까?
			{
				attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
				if(you.damage(temp_att))
					penetrate--;
			}
			path = 10*GetPosToDirec((*beam),prev);
			coord_def postion_ = (*beam);
			prev = *(beam++);
			path += (penetrate>0 && length>0)?GetPosToDirec(prev,(*beam)):9;
			if(t_)
				env[current_level].MakeEffect(postion_,t_,false);
			else if(graphic_type || !item_)
				env[current_level].MakeEffect(postion_,GetTanmacGraphic(graphic_type, direc, count++,path),false);
			else if(item_) //자체 그래픽이 없고 item일 경우 item 그래픽을 그대로 쓴다.
				env[current_level].MakeEffect(postion_,item_->image,false);
			Sleep(16);
			length++;
			if(pow((float)abs(beam.start_pos().x-(*beam).x),2)+pow((float)abs(beam.start_pos().y-(*beam).y),2)>(infor_.length)*(infor_.length))
				break;
			if(infor_.type1 == BMT_NORMAL || infor_.type1 == BMT_WALL)
				env[current_level].ClearEffect();
		}
		if(infor_.type1 == BMT_WALL && !env[current_level].isMove(*(beam),true) && penetrate>0 &&  infor_.max_damage>length)
		{
			prev = *(beam++);
			//벽에 부딪히는?
		}

		if(item_ && !mimic_ && (infor_.order != &you || !you.s_knife_collect))
		{
			if(!(item_->type>=ITM_THROW_FIRST && item_->type<ITM_THROW_LAST) || !TanmacDeleteRand((tanmac_type)item_->value4, false))
			{
				if (item_->type == ITM_WEAPON_LONGBLADE && item_->value0 == 3)
				{//철륜
					env[current_level].ClearEffect();
					beam--;
					coord_def pos_;
					while (length>1)
					{
						pos_ = *(beam--);
						if (t_)
							env[current_level].MakeEffect(pos_, t_, false);
						else if (graphic_type || !item_)
							env[current_level].MakeEffect(pos_, GetTanmacGraphic(graphic_type, direc, count++, path), false);
						else if (item_) //자체 그래픽이 없고 item일 경우 item 그래픽을 그대로 쓴다.
							env[current_level].MakeEffect(pos_, item_->image, false);
						Sleep(16);
						env[current_level].ClearEffect();
						length--;
					}
					item* temp = env[current_level].AddItem(beam.start_pos(), item_, 1);
					temp->throw_item = true;
					if(you.additem(temp, false))
						env[current_level].DeleteItem(temp);
				}
				else
				{
					item* temp = env[current_level].AddItem(prev, item_, 1);
					temp->throw_item = true;
				}
			}
		}
		break;
	}
	Sleep(60);
	if(effect_delete)
		env[current_level].ClearEffect();
	return prev;
}

coord_def throwtanmac(textures* t_, beam_iterator& beam, const beam_infor &infor_, item* item_, bool effect_delete, bool mimic_)
{
	return throwtanmac_(0, t_, beam, infor_, item_, effect_delete, mimic_);
}

coord_def throwtanmac(int graphic_type, beam_iterator& beam, const beam_infor &infor_, item* item_, bool effect_delete, bool mimic_)
{
	return throwtanmac_(graphic_type, NULL, beam, infor_, item_, effect_delete, mimic_);
}


bool ThrowShock(int graphic_type, const coord_def &start, const coord_def &target, const beam_infor &infor_)
{
	beam_iterator beam(start,start);
	if(!CheckThrowPath(start,target,beam))
		return false;
	beam.init();
	coord_def prev = beam.start_pos();
	int direc = beam.GetDirec();
	int count = 0;
	bool end = false;
	int path = 8;
	if((*beam) == target)
		end = true;
	if(isStartGraphic(graphic_type))
	{
		coord_def postion_ = prev;
		int path_ = 80+GetPosToDirec(prev,(*beam));

		if(graphic_type)
			env[current_level].MakeEffect(postion_,GetTanmacGraphic(graphic_type, direc, count++,path_),false);
	}
	while(env[current_level].isMove(*(beam),true))
	{
		path = 10*GetPosToDirec((*beam),prev);
		coord_def postion_ = (*beam);
		prev = *(beam++);
		path += (!end)?GetPosToDirec(prev,(*beam)):9;

		if(graphic_type)
			env[current_level].MakeEffect(postion_,GetTanmacGraphic(graphic_type, direc, count++,path),false);
		if(end)
			break;
		if((*beam) == target)
			end = true;
	}
	for(vector<monster>::iterator it=env[current_level].mon_vector.begin();it!=env[current_level].mon_vector.end();it++)
	{
		if((*it).isLive() && (*it).position.x == target.x && (*it).position.y == target.y &&
			!(*it).isPassedBullet(infor_.order)
			)
		{
			attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
			(*it).damage(temp_att);
		}
	}
	if(!infor_.order->isplayer() && you.position.x == target.x && you.position.y == target.y &&
		!you.isPassedBullet(infor_.order)
		) //플레이어는 자기자신에게 맞지않는 조건은 나중에 지울까?
	{
		attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
		you.damage(temp_att);
	}
	return true;
	//이 함수를 부르고난후에 sleep(120)와 env[current_level].ClearEffect()는 알아서 부르자.
}


bool ThrowSector(int graphic_type,beam_iterator& beam, const beam_infor &infor_, float sector_ , function<void(coord_def)> func_, bool reverse_, bool effect_delete)
{	
	
	beam.init();
	coord_def prev = beam.start_pos();
	int direc = beam.GetDirec();
	int count = 0;
	int path = 8;
	switch(infor_.type1)
	{
	case BMT_NORMAL:
	case BMT_WALL:
	case BMT_PENETRATE:
	default:
		if(isStartGraphic(graphic_type))
		{
			coord_def postion_ = prev;
			int path_ = 80+GetPosToDirec(prev,(*beam));
			if(graphic_type)
				env[current_level].MakeEffect(postion_,GetTanmacGraphic(graphic_type, direc, count++,path_),false);
		}
		{
			vector<sector_check> vec_;
			float angle_ = beam.GetAngle();
			for(int i = -infor_.length; i <= infor_.length;i++)
			{
				for(int j = -infor_.length; j <= infor_.length;j++)
				{
					if(i*i+j*j>(infor_.length+1)*(infor_.length+1)-1 || (i==0 && j==0))
						continue;

					float angle2_ = atan2((float)j, (float)i);
					float a_ = cos(angle2_-angle_);
					float b_ = cos(sector_);
					if(a_ >= b_)
					{
						vec_.push_back(sector_check(beam.start_pos()+coord_def(i,j),i*i+j*j));
					}
				}
			}
			sort(vec_.begin(),vec_.end(),[](sector_check& s1, sector_check& s2){
				return s1.length < s2.length;
			});
			int temp_len_ = 1;
			for(auto it = vec_.begin();it!=vec_.end();it++)
			{
				if(it->length> temp_len_*temp_len_)
				{
					temp_len_++;
					Sleep(16);
					if(infor_.type1 == BMT_NORMAL || infor_.type1 == BMT_WALL)
						env[current_level].ClearEffect();
				}	
				if(env[current_level].isMove(it->pos,true) && (!infor_.order || !infor_.order->isplayer() || env[current_level].isInSight(it->pos)) 
					&& (!infor_.order ||  infor_.order->isSightnonblocked(it->pos)))
				{
					path = 10*GetPosToDirec(beam.start_pos(),it->pos);
					if(graphic_type)
							env[current_level].MakeEffect(it->pos,GetTanmacGraphic(graphic_type, direc, count++,path),false);
					for(vector<monster>::iterator it2=env[current_level].mon_vector.begin();it2!=env[current_level].mon_vector.end();it2++)
					{
						if((*it2).isLive() && (*it2).position.x == it->pos.x && (*it2).position.y == it->pos.y &&
							!(*it2).isPassedBullet(infor_.order)
							)
						{
							attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
							if((*it2).damage(temp_att))
							{
							}
						}
					}
				}	
			}
			if(reverse_)
			{
				sort(vec_.begin(),vec_.end(),[](sector_check& s1, sector_check& s2){
					return s1.length > s2.length;
				});
			}
			temp_len_ = 1;
			for(auto it = vec_.begin();it!=vec_.end();it++)
			{
				func_(it->pos);
			}
		
		}			
		
			//if(!infor_.order->isplayer() && you.position.x == (*beam).x && you.position.y == (*beam).y &&				
			//	!you.isPassedBullet(infor_.order)
			//	) //플레이어는 자기자신에게 맞지않는 조건은 나중에 지울까?
			//{
			//	attack_infor temp_att(infor_.damage,infor_.max_damage,infor_.accuracy,infor_.order,infor_.p_type,infor_.type2,infor_.name);
			//	if(you.damage(temp_att))
			//		penetrate--;
			//}
			//
			//coord_def postion_ = (*beam);
			//prev = *(beam++);
			//path += (penetrate>0 && length>0)?GetPosToDirec(prev,(*beam)):9;

			//Sleep(16);
			//length++;
			//if(pow((float)abs(beam.start_pos().x-(*beam).x),2)+pow((float)abs(beam.start_pos().y-(*beam).y),2)>infor_.length*infor_.length)
			//	break;
			//if(infor_.type1 == BMT_NORMAL)
			//	env[current_level].ClearEffect();
		//}
		//if(infor_.type1 == BMT_WALL && !env[current_level].isMove(*(beam),true) && penetrate>0 && length>0)
		//{
		//	prev = *(beam++);
		//	//벽에 부딪히는?
		//}
		break;
	}
	if(infor_.type1 == BMT_NORMAL){		
		Sleep(16);
		env[current_level].ClearEffect();
	}
	else
		Sleep(300);
	if(effect_delete)
		env[current_level].ClearEffect();
	return true;
}

bool CheckThrowPath(coord_def start,coord_def target, beam_iterator &beam, bool passdoor)
{
	//if(!(env[current_level].dgtile[target.x][target.y].flag & FLAG_INSIGHT))
	//	return false;
	bool intercept = false;
	for(int i=RT_BEGIN;i!=RT_END;i++)
	{
		beam_iterator it(start,target,(round_type)i);
		while(!intercept && !it.end())
		{
			if((!env[current_level].dgtile[(*it).x][(*it).y].isMove(true,false,false)) && (!passdoor || !env[current_level].dgtile[(*it).x][(*it).y].isCloseDoor()))
			{
				intercept = true;
				break;
			}
			it++;
		}
		if(intercept == false)
		{
			beam = it;
			return true;
		}
		intercept = false;
	}
	return false;
}

void paintpath(coord_def c_, beam_iterator &beam, list<item>::iterator item_, bool set, projectile_infor* infor_, int m_len_, float sector_)
{
	if(m_len_ == -1)
		m_len_ = beam.GetMaxLength();

	if(infor_->smite)
	{
		int range_ = 0;
		if(infor_->spell == -1 && item_!=you.item_list.end() && item_->type >= ITM_THROW_FIRST && item_->type < ITM_THROW_LAST && item_->value4 == TMT_KIKU_COMPRESSER)
			range_ = 1;
		else 
			range_ = infor_->skill?GetSpellBombRange((skill_list)infor_->spell):GetSpellBombRange((spell_list)infor_->spell);

		if(range_)
		{
			rect_iterator rit(c_,range_, range_);
			for(;!rit.end();rit++)
			{
				if(set)
					env[current_level].dgtile[(*rit).x][(*rit).y].flag = env[current_level].dgtile[(*rit).x][(*rit).y].flag | FLAG_LIGHT;
				else
					env[current_level].dgtile[(*rit).x][(*rit).y].flag = env[current_level].dgtile[(*rit).x][(*rit).y].flag & ~FLAG_LIGHT;	
			}
		}
		return;
	}



	if(sector_)
	{
		vector<sector_check> vec_;
		float angle_ = beam.GetAngle();
		for(int i = -m_len_; i <= m_len_;i++)
		{
			for(int j = -m_len_; j <= m_len_;j++)
			{
				if(i*i+j*j>(m_len_+1)*(m_len_+1)-1 || (i==0 && j==0))
					continue;

				float angle2_ = atan2((float)j, (float)i);
				float a_ = cos(angle2_-angle_);
				float b_ = cos(sector_);
				if(a_ >= b_)
				{
					vec_.push_back(sector_check(beam.start_pos()+coord_def(i,j),i*i+j*j));
				}
			}
		}
		sort(vec_.begin(),vec_.end(),[](sector_check& s1, sector_check& s2){
			return s1.length < s2.length;
		});
		for(auto it = vec_.begin();it!=vec_.end();it++)
		{
			if(env[current_level].isMove(it->pos,true) && env[current_level].isInSight(it->pos) && you.isSightnonblocked(it->pos))
			{
				if(set)
					env[current_level].dgtile[it->pos.x][it->pos.y].flag = env[current_level].dgtile[it->pos.x][it->pos.y].flag | FLAG_LIGHT;
				else
					env[current_level].dgtile[it->pos.x][it->pos.y].flag = env[current_level].dgtile[it->pos.x][it->pos.y].flag & ~FLAG_LIGHT;	
			}
		}
	}
	else 
	{
		int range_ = 0;

		if (infor_->spell == -4) //매직봄 전용...
			range_ = 2;
		else if(infor_->spell == -1 && item_!=you.item_list.end() && item_->type >= ITM_THROW_FIRST && item_->type < ITM_THROW_LAST && item_->value4 == TMT_KIKU_COMPRESSER)
			range_ = 1;
		else 
			range_ = infor_->skill?GetSpellBombRange((skill_list)infor_->spell):GetSpellBombRange((spell_list)infor_->spell);
		
		if(range_)
		{
			for(beam.init();!beam.end();)
			{
				auto temp_beam = beam++;
				//스마이트형이 아닌경우 부딪히면 터지기 마련이다.
				bool block_ = false;
				if(!env[current_level].isMove(*(beam),true))
				{
					beam = temp_beam;
					block_ = true;
				}



				if (infor_->spell == -4) {
					for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if ((*it).isLive() && 
							(((*it).position.x == (*temp_beam).x && (*it).position.y == (*temp_beam).y) ||
							((*it).position.x == (*beam).x && (*it).position.y == (*beam).y)))
						{
							beam = temp_beam;
							block_ = true;
							break;
						}
					}
				}
				else {
					for (vector<monster>::iterator it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end(); it++)
					{
						if ((*it).isLive() && (*it).position.x == (*temp_beam).x && (*it).position.y == (*temp_beam).y &&
							!(*it).isPassedBullet(&you)
							)
						{
							beam = temp_beam;
							block_ = true;
							break;
						}
					}
				}

				if(block_)
					break;

				if(set)
					env[current_level].dgtile[(*temp_beam).x][(*temp_beam).y].flag = env[current_level].dgtile[(*temp_beam).x][(*temp_beam).y].flag | FLAG_LIGHT;
				else
					env[current_level].dgtile[(*temp_beam).x][(*temp_beam).y].flag = env[current_level].dgtile[(*temp_beam).x][(*temp_beam).y].flag & ~FLAG_LIGHT;	
			}
			rect_iterator rit((*beam),range_, range_);
			for(;!rit.end();rit++)
			{
				if(set)
					env[current_level].dgtile[(*rit).x][(*rit).y].flag = env[current_level].dgtile[(*rit).x][(*rit).y].flag | FLAG_LIGHT;
				else
					env[current_level].dgtile[(*rit).x][(*rit).y].flag = env[current_level].dgtile[(*rit).x][(*rit).y].flag & ~FLAG_LIGHT;	
			}
		}
		else
		{

			for(beam.init();!beam.end();beam++)
			{
				if(set)
					env[current_level].dgtile[(*beam).x][(*beam).y].flag = env[current_level].dgtile[(*beam).x][(*beam).y].flag | FLAG_LIGHT;
				else
					env[current_level].dgtile[(*beam).x][(*beam).y].flag = env[current_level].dgtile[(*beam).x][(*beam).y].flag & ~FLAG_LIGHT;	
			}
			if(set)
				env[current_level].dgtile[(*beam).x][(*beam).y].flag = env[current_level].dgtile[(*beam).x][(*beam).y].flag | FLAG_LIGHT;
			else
				env[current_level].dgtile[(*beam).x][(*beam).y].flag = env[current_level].dgtile[(*beam).x][(*beam).y].flag & ~FLAG_LIGHT;	
		}
	}
}


list<item>::iterator ThrowSelect()
{
	view_item(IVT_THROW,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
	while(1)
	{
		InputedKey inputedKey;
		int key_ = waitkeyinput(inputedKey, true);


		if(key_ == VK_RETURN || key_ == GVK_BUTTON_A || key_ == GVK_BUTTON_A_LONG) {
			int char_ = DisplayManager.positionToChar();
			if(char_) {
				if(key_ == GVK_BUTTON_A_LONG) {
					key_ = -1;
					inputedKey.mouse = MKIND_ITEM_DESCRIPTION;
					inputedKey.val1 = char_;
				} else {
					key_ = char_;
				}
			}
		}


		if( (key_ >= 'a' && key_ <= 'z') || (key_ >= 'A' && key_ <= 'Z') )
		{
			list<item>::iterator it = you.GetItemIterator(key_);
			if(it != you.item_list.end())
			{
				changedisplay(DT_GAME);
				return it;
			}
		}
		else if(key_ == VK_DOWN)//-----이동키-------
		{
			DisplayManager.addPosition(1);
		}
		else if(key_ == VK_UP)
		{
			DisplayManager.addPosition(-1);
		}
		else if(key_ == VK_PRIOR)
		{
			changemove(-option_mg.getHeight());
		}
		else if(key_ == VK_NEXT)
		{
			changemove(option_mg.getHeight());
		}						//-----이동키끝-------
		else if(key_ == '*')
			view_item(IVT_SELECT,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
		else if(key_ == -1) {			
			if(inputedKey.mouse == MKIND_ITEM_DESCRIPTION) {
				int get_item_move_ = getDisplayMove();
				if(iteminfor_(inputedKey.val1, true))
					break;
				rollback_item(IVT_THROW,LOC_SYSTEM_DISPLAY_MANAGER_THROW);
				setDisplayMove(get_item_move_);
			} else if(inputedKey.mouse == MKIND_SCROLL_UP) {
				changemove(-32);  //아래
			} else if(inputedKey.mouse == MKIND_SCROLL_DOWN) {
				changemove(32);  //위
			} else if(inputedKey.isRightClick()) {
				break;
			}
		}
		else if(key_ == VK_ESCAPE||
			key_ == GVK_BUTTON_B || 
			key_ == GVK_BUTTON_B_LONG)
			break;
	}
	changedisplay(DT_GAME);
	return you.item_list.end();
}

bool throw_prev_fail(bool no_speak){
	if(you.s_lunatic)
	{
		if(!no_speak)
			printlog(LocalzationManager::locString(LOC_SYSTEM_LUNATIC_PENALTY_THROW),true,false,false,CL_danger);
		return true;
	}
	if (you.s_evoke_ghost) {
		if(!no_speak)
			printlog(LocalzationManager::locString(LOC_SYSTEM_GHOST_PENALTY_THROW), true, false, false, CL_normal);
		return true;
	}
	return false;
}

void Quick_Throw(list<item>::iterator it, vector<monster>::iterator it2, bool auto_)
{
	if(throw_prev_fail(false))
	{
		return;
	}
	beam_iterator beam(you.position,you.position);
	projectile_infor infor(7,true,false);
	int short_ = Common_Throw(it, it2, beam, &infor, -1,  0, auto_);
	if(short_)
	{
		if(it != you.item_list.end())
		{
			if((*it).can_throw)
				you.throw_weapon = &(*it);
			unit *unit_ = env[current_level].isMonsterPos(you.search_pos.x,you.search_pos.y,0, &(you.target));
			if(unit_ == &you)
				return;
			if(unit_)
				you.youAttack(unit_);
			if(you.Throw(it,you.search_pos,short_==2,beam))
			{				
				you.SetBattleCount(30);
				//you.SkillTraining(SKT_TANMAC,2);
				you.TurnEnd();
			}
			you.SetPrevAction('f');
		}	

	}
}


void Select_Throw()
{
	if(throw_prev_fail(false))
	{
		return;
	}
	list<item>::iterator it = ThrowSelect();
	if(it==you.item_list.end() && you.GetThrowIter() == you.item_list.end() ) {
		return;
	}
	Quick_Throw(it!=you.item_list.end()?it:you.GetThrowIter(),you.GetTargetIter(), false);
}