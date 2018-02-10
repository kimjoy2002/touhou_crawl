//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: speak.cpp
//
// 내용: 몬스터의 대사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "speak.h"
#include "player.h"


char temp_speak[100];

char* Get_Speak(int mon_id, monster* monster_info, monster_speak_type type)
{ //투명일때?
	if(type == MST_FOUND)
	{
		sprintf(temp_speak,"%s%s외쳤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
		return temp_speak;
	}
	switch(mon_id)
	{
	case MON_REIMUYUKKURI:
	case MON_MARISAYUKKURI:
		if(type == MST_NORMAL)
		{
			sprintf(temp_speak,"%s%s외쳤다. \"느긋하게 있으라구!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;	
	case MON_RUMIA:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"그런건가-\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"%s%s 먹어도 되는 %s?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),job_type_string[you.job],job_string_back[you.job]?"은":"는",tribe_type_string[you.tribe]);
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"던전은 좁아- 자꾸 벽에 부딫힌단 말이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"넌 뭘 위해 던전을 탐험하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"내 어둠에서 나가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"최근 인간을 전혀 잡아먹지 못했어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"그런건가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s멍하니 하늘을 바라봤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s이 쪽을 뚫어지게 쳐다봤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s외쳤다. \"요전에 어느 %s에게 습격당할뻔한 적이 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[randA(TRI_MAX-1)]);
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"그랬던가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어디있어???\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"눈앞이 핑핑 돈다아-\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s팔을 앞으로 나란히 자세를 취했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_MISTIA:
		if(type == MST_NORMAL)
		{
			switch(randA(15))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"노래 한곡 듣고 가는게 어때?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"다음 노래는 너를 위한 진혼곡이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"노래 가사를 외울 필요는 없어. 즉흥곡이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"방해하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"도망치면 노래를 들려줄 수 없잖아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"좋아, 관객은 충분하군.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"두루마리가 땅에 떨어져있었지만 읽을 순 없었어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"니가 부를 소절은 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				string sing, song;
				switch(randA(16))
				{
				case 0:sing = "빠른 비트의";break;
				case 1:sing = "차분한";break;
				case 2:sing = "슬픈 곡조의";break;
				case 3:sing = "박자가 맞지 않는";break;
				case 4:sing = "가사 센스가 없는";break;
				case 5:sing = "들쑥날쑥한 음의";break;
				case 6:sing = "스타카토의";break;
				case 7:sing = "길게 늘어지는";break;
				case 8:sing = "평범한";break;
				case 9:sing = "정체를 알수없는";break;
				case 10:sing = "발랄한";break;
				case 11:sing = "어디선가 들어본";break;
				case 12:sing = "괴성의";break;
				case 13:sing = "전파적인";break;
				case 14:sing = "흥겨운";break;
				case 15:sing = "느린";break;
				case 16:sing = "귀여운";break;
				}
				switch(randA(13))
				{
				case 0:song = "락을";break;
				case 1:song = "발라드를";break;
				case 2:song = "힙합을";break;
				case 3:song = "랩을";break;
				case 4:song = "동요를";break;
				case 5:song = "알엔비를";break;
				case 6:song = "재즈를";break;
				case 7:song = "메탈을";break;
				case 8:song = "블루스를";break;
				case 9:song = "댄스곡을";break;
				case 10:song = "트로트를";break;
				case 11:song = "성악을";break;
				case 12:song = "자장가를";break;
				case 13:song = "장르없는 곡을";break;
				}
				sprintf(temp_speak,"%s%s%s %s 불렀다",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true),sing.c_str(),song.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"어질어질~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"날개가 마비되버렸어-\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"으아\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s박자 음정이 하나도 맞지 않는 노래를 불렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				sprintf(temp_speak,"%s%s신비한 음색의 노래를 불렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s유혹하는듯한 노래를 불렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s정신에 영향을 끼치는 노래를 불렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			}

		}
	case MON_WRIGGLE:
		if(type == MST_NORMAL)
		{
			switch(randA(10))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"이 곳을 지나가려하다니 좋은 배짱이네!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어둡고 습한 곳은 벌레들의 천국이지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"벌레들을 무시하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"혼자서 싸우겠다는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"거기! 발밑을 조심해! 밟을뻔했잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"아아~ 지루하군.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"대군을 상대로 네가 이길 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"이런 곳도 나쁘진 않아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s더듬이를 움직였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s망토를 펄럭였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s주위에 각종 벌레들이 꼬이기 시작했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"난 나비인가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"제대로 걸을수가 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s위태롭게 비틀비틀거린다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s의 더듬이가 서로 엉켰다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(3))
			{
			case 0:
				sprintf(temp_speak,"%s%s벌레무리를 불러냈다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s벌레들을 모으는 손짓을 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s벌레들과 얘기를 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
	case MON_CIRNO:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"죽어라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"얼려주마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"요정이라고 얕보는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"던전의 끝은 9층이라고 들었어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"눈앞에 강적이 있잖아? 좀 긴장해봐!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"이제 그만 포기하시지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"근처에 개구리가 없어. 너라도 얼려주마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s위협적으로 팔을 크게 벌렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s의 주위에 얼음조각이 생겨났다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s팔짱을 끼고 기세등등하게 서있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s중얼거렸다. \"3.14159265358979....\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"난 지금 요정의 삶에 대해서 심각하게 고찰 중이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"머리가 상쾌해진거같아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"아, 이런 리본이 비뚤어져있었군.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(4))
			{
			case 0:
				sprintf(temp_speak,"%s%s기세좋게 기술을 외쳤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s의 손에서 냉기가 모였다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s냉기의 흐름을 제어했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s팔을 크게 벌렸다가 상대를 향해 손을 뻗었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s냉기의 주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_MEDICINE:
		if(type == MST_NORMAL)
		{
			switch(randA(11))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"방울아, 해치워버려!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				if(you.poison_resist>0)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"어째서 독에 멀쩡한거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"독이 너무 강했던걸까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 2:
				if(you.s_poison)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"강한척하지마. 벌써 독에 비틀비틀거리고 있잖아?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"안심하긴 아직 일러!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"은방울꽃밭으로 돌아가고 싶어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"아직 독은 많이 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"가스와 안개는 전~혀 달라.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"방울아, %s%s 나타났어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[you.tribe],tribe_string_back[you.tribe]?"이":"가");
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"방울아. 근처에 새로운 독 꽃은 없을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"나에게 접근했던 녀석은 모두 독에 죽어버렸어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s팔을 벌리고 한바퀴 빙글돌았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s웃으면서 독을 내뿜고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 11:
				sprintf(temp_speak,"%s%s주위엔 독안개가 퍼지고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"방울아! 어디있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"으으, 머리가 아파...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"몸이 내 생각대로 움직이지 않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"무서워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"콘파로~ 콘파로~ 독아 모여라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s팔을 번쩍 들어올렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s독을 모았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_DIEFAIRY:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:
				sprintf(temp_speak,"%s%s위협적인 자세를 취했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s이 쪽의 상태를 엿보고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s날개를 파닥였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s가지고있는 꽃을 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s끄덕였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s울먹였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s손에 탄막을 모았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스러워 보인다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s울고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s방향을 잡지 못하고 비틀거린다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s똑바로 날지 못한다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KISUME:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				sprintf(temp_speak,"%s%s머리를 흔들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s이 쪽을 보고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s달그락 소리를 낸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s두레박에 얼굴을 숨겼다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s빼꼼 얼굴을 내밀었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s두레박과 함께 흔들리고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s일순간 무서운 표정을 지었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_CHEN:
		if(type == MST_NORMAL)
		{	
			switch(randA(12))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"여기서 헤매게 되면 최후!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"여긴 이제부터 우리들의 집인데 나가주지 않겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"고양이를 이정도 모으는데 개다래나무가 너무 많이 들었어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"여긴 마요이가보다 더 헤매기 쉬운거같아...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"고양이에게 다친 상처만 없었더라면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"모두 공격해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"너정도는 식신화도 필요 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"냐옹!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"냐냥!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s외쳤다. \"후갹!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s손톱을 세웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 11:
				sprintf(temp_speak,"%s%s고양이 눈을 하고 입을 크게 벌리며 위협했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 12:
				sprintf(temp_speak,"%s%s팔을 마구 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"냐..냐냥!?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"개..개다래열매???\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"땅이 움직이고 있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s허공에 팔을 휘두른다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KOGASA:
		if(type == MST_NORMAL)
		{	
			switch(randA(12))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"원망스러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"왁!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"놀라지 않았어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"요즘 인간들은 놀라지도 않아서 재미 없는걸...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"이 던전엔 공포 두루마리라는 전설의 템이 있대. 대단하네!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"쓸쓸히 버려진 도구들의 아픔을 느끼는게 좋아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"너도 결국 필요없는 도구는 던전에 버려둘 뿐이잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"산성비에 녹아버려!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"원망해버릴거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s외쳤다. \"놀랬다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s우산을 빙글빙글 돌렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 11:
				sprintf(temp_speak,"%s%s한쪽 눈을 감고 혀를 내밀었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 12:
				sprintf(temp_speak,"%s%s들고있는 우산의 혀가 움직였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"원망스럽던가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"눈이 핑핑 돈다아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s의 우산에 달려있는 눈이 빙글빙글 돈다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s우산을 이리저리 흔들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_SUNNY:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"요정의 힘을 얕보지마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"보이지 않는 적과 싸울 수 있겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				if(monster_info->GetInvisible() && !you.invisible_view)
					sprintf(temp_speak,"%s%s외쳤다. \"여기지롱~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"이크, 이쪽이 들켜버렸다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"이런 곳에선 일광욕을 할 수 없잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"팀플레이란걸 보여줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"자, 공격!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				if(monster_info->GetInvisible() && !you.invisible_view)
					sprintf(temp_speak,"%s%s외쳤다. \"어때! 어디있는지 모르겠지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else if(monster_info->GetInvisible() && you.invisible_view)
					sprintf(temp_speak,"%s%s외쳤다. \"어째서 내가 보이는 거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"여기서 이렇게 빛을 굴절 시키면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"어라? 땅이 울렁거리고있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"넌 어째서 커졌다 작아졌다 하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				sprintf(temp_speak,"%s%s손을 모았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s빛을 내기 시작했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s빛을 굴절시켰다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_LUNAR:
		if(type == MST_NORMAL)
		{	
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"싸울 수 밖에 없나...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"여기선 달이 보이지 않아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"소리가 들리지않을텐데 어떻게?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"두루마리는 소리내서 읽어야 효과를 낸다는 건 알고있지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"도망치지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"내 입은 밤이 아니라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"어지러워! 이럴땐 소리를 줄이면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"시끄러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s의 주변이 고요해지기 시작했다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_STAR:
		if(type == MST_NORMAL)
		{	
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"이미 캐릭터 생성창부터 오고있는건 알고있었어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"이런 던전에서 감지능력은 참 편해. 치트라고?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"우린 세명이서 팀이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				if(you.s_invisible || you.togle_invisible)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"투명해져있어도 보인다니까!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"도망쳐도 보여, 숨어도 보여. 포기하는게 좋아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 4:
				if(you.s_invisible || you.togle_invisible)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"써니의 투명보다도 어설프잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"숨바꼭질이라면 질 자신이 없는걸!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;

				}
			case 5:
				if(you.s_invisible || you.togle_invisible)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"모습을 숨기는게 통한다고 생각한거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"싸움은 자신없긴하지만.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"두명.. 아니 세명?!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어지러워서 도망칠수도 없어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;		
	case MON_YAMABIKO:
		if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s엄청난 소리의 메아리로 주의를 끌었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_KYOUKO:
		if(type == MST_NORMAL)
		{	
			switch(randA(11))
			{
			case 0:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"안녕하세요-!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s중얼거렸다. \"아~제~ 아~제~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s중얼거렸다. \"시~무~ 등~등~주~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"던전에 %s의 비명이 메아리칠거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[you.tribe]);
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"목소리가 작다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"이렇게 불필요한 살생을 일삼다니!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"던전에서의 메아리는 모두 야마비코때문이지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"아이 참, 청소하는데 바닥에 왜이렇게 쓸데없는 물건들이 많은거지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"메아리가 단순한 자연현상이라니, 미신이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s귀를 파닥였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s불경을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 11:
				sprintf(temp_speak,"%s%s아주 큰 소리로 소리를 질렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"살려줘-!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"당- 했- 다-!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s매우 크게 외쳤다. \"으아아아-!!!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s귀를 난잡하게 파닥였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(2))
			{
			case 0:
				sprintf(temp_speak,"%s%s굉음을 냈다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s엄청난 소리로 인사를 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s귀가 깨질듯한 소리로 불경을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_FORTUNE_TELLER:
		if(type == MST_NORMAL)
		{	
			switch(randA(9))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"또냐! 너도 날 퇴치하러 온거냐!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"인간으로서의 생활은 부질없구나!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"난 이제 요괴로 다시 태어난 것이다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"환상향에서 인간으로 살아가는게 얼마나 고된지 아는가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"그래! 죽음이 해답이다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"날 방해하겠다면 너도 잠재워주마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"너도 머리를 노릴 셈이냐!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"나는 인간을 포기하겠다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s미친듯이 웃었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s이를 갈았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_MOMIZI:
		if(type == MST_NORMAL)
		{	
			switch(randA(6))
			{
			case 0:
				sprintf(temp_speak,"%s%s머리를 감쌌다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s울부짖었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s칼을 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s방패를 들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s이빨을 드러냈다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s짖었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s사납게 노려봤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(1))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스러워 보인다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s도움을 청했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_AYA:
		if(type == MST_NORMAL)
		{	
			switch(you.tribe)
			{
			case TRI_HUMAN:
				switch(randA(8))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"인간이 요괴의 산에 들어온 겁니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"적당히 봐줄테니 진심으로 덤벼보세요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"날라가버리세요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"기삿거리는 없습니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"최신 정보 가득한 붕붕마루 신문! 한번 구독해보시지 않으시겠습니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"혹시 이 던전에 대해 아시는것이 있으십니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"도망치시면 곤란합니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s외쳤다. \"칩입자가 인간이었습니까? 겁도 없으시군요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 8:
					sprintf(temp_speak,"%s%s외쳤다. \"요괴의 산엔 함부로 출입이 금지되어있습니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case TRI_CROWTENGU:
				switch(randA(9))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"아아, 너는... %s이었던가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),you.user_name.name.c_str());
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"아아, 네 신문은 읽어봤어. 흥미로운것도 없었지만\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"뭐하는거야, 네 취재혼은 겨우 그 정도야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"어차피 나의 붕붕마루 신문에 대적할 상대는 못되지만!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"이번 이변의 기사화는 양보못해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"난 스피드로는 지지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"신문대회가 얼마남지 않았다고 이런 비열한 수를 쓰는 거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s외쳤다. \"집단에 배신할 셈이야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 8:
					sprintf(temp_speak,"%s%s외쳤다. \"요괴의 산에서 난동부린다는 까마귀텐구의 소식은 들었어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 9:
					sprintf(temp_speak,"%s%s외쳤다. \"텐구끼리의 싸움인가...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case TRI_WOLFTENGU:
				switch(randA(5))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"어라, 경비는 어떻게 된겁니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"경비를 지켜야할 자가 이런 짓을...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"백랑텐구들은 우리 까마귀텐구를 얕보는걸까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"칩입자가 있다는 얘기를 들었지만 설마 백랑텐구일줄은 몰랐네요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"경비를 하던 백랑텐구들은 어떻게 된겁니까? 아, 당신이었군요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"집단에 배신할 셈입니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;

			case TRI_ONI:
				switch(randA(7))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"이야, 이거 큰일났습니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s중얼거렸다. \"설마 칩입자가 오니일줄이야...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"아야야야, 왜 당신이 여기에?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"당신이 함부로 산에 오시면 모두가 곤란합니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"아, 어쩔 수 없는 정당방어입니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"여기서 져주시는게 산의 요괴 모두에게 평화롭습니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"아뇨아뇨, 먼저 공격할 생각은 없었습니다만.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s외쳤다. \"아야야야\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			default://기본대화
				switch(randA(6))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"깨끗하고 올바른 샤메이마루입니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"기삿거리는 없습니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s중얼거렸다. \"카메라가 이상한데... 캇파에게 맡겨야하나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"아아, 곤란하군요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"최신 정보 가득한 붕붕마루 신문! 한번 구독해보시지 않으시겠습니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"혹시 이 던전에 대해 아시는것이 있으십니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"도망치시면 곤란합니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"제어가 되질 않습니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"아야야야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"제대로 날고 있습니까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"산이 마치 던전화된처럼 보입니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"당신은 누구죠?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s부채를 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s의 주위에 바람이 요동친다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}		
		break;
	case MON_WAKASAGI:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"물을 더럽히지마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"다른 곳은 어떻게 되어있는 거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"주변의 요정들이 날뛰고 있어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"물 속이라면 지지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"여기에 모아둔 돌멩이들이 어디에 갔을까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"물 속에 빠져죽는 사람들도 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s유아하게 헤엄쳤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s위협적으로 물을 튀기고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"살려줘!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"아파! 아파!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s바둥거렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s살기위해 몸부림치고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s신비한 선율로 노래했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s아름다운 선율로 노래했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_YAMAME:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"난 이 곳이 마음에 드는걸.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"그렇게 있으면 요괴들에게 잡아먹힐지 모른다구?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				if(you.s_sick)
				{
					sprintf(temp_speak,"%s%s웃었다. \"괜찮아? 안색이 안좋아보이는데?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"어디보자 너에게 맞는 질병은...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 3:				
				if(you.s_sick)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"그런 상태로 싸울 수 있겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"회복 물약은 충분하겠지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 4:
				if(you.s_sick)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"그 질병이 좋은 향신료가 될꺼야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"내 능력을 알고 있어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 5:
				if(you.tribe == TRI_KAPPA)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"캇파들은 시끄럽구만.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"오랫만의 사냥감이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 6:
				if(you.s_sick && you.s_poison)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"질병과 독... 최고의 조합이잖아?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"놀러온거야? 아니면 죽으러?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 7:
				if(randA(10))
				{
					sprintf(temp_speak,"%s%s외쳤다. \"건강을 생각하는건 어때.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else //야마메입니까(웃음)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"뭘 웃냐, 죽여버린다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s의 주변에 불운한 공기가 감돌고 있다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"이건 새로운 질병인가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어지러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s빙글빙글 돌고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s바닥에서 구르고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s손을 들어 올렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_NAZRIN:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"무슨 보물을 찾고 있고있는거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어라? 나와 찾는 물건이 같은거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				if(you.haveGoal()) //플레이어가 (룬)을 1개이상 들고 있을때
				{
					sprintf(temp_speak,"%s%s외쳤다. \"다우징이 반응하고있어... 룬을 가지고 있는건가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"너도 룬을 찾고 있는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"오브란걸 주웠지만 이건 다른걸까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"쥐들을 무시하면 큰코 다칠텐데?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"이봐, %s. 이런 물건을 보지못했어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[you.tribe]);
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"곤란하군. 길이 이렇게 복잡해서야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"그렇군, 새끼쥐들도 배고파하니까 여기서 식사를 해볼까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"이번에도 꽝인가.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s외쳤다. \"재밌네. 쥐를 얕보는걸까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"미안해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"다신 안 그럴게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s다우징을 휘두르고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s자신의 꼬리를 물었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s다우징을 정렬했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s펜듈럼을 진동시킨다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_YOSIKA:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"가~까이 오~지마~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"뭐~더~라?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"우~어어~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:			
				sprintf(temp_speak,"%s%s외쳤다. \"아프지 않아~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"좀비는 영원 불멸이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"나는 이 곳을 지키도록 명령을 받았어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"강시에게 잔재주는 안통해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"너도 우리들의 동료가 되는거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"당~했~다~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"우,우... 우,아...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s시를 읇고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s이리저리 뛰어다니고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}	
		break;
	case MON_SEKIBANKI:
	case MON_SEKIBANKI_HEAD:
		if(type == MST_NORMAL)
		{
			switch(randA(9))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"무서워서 걷지도 못하게 해주마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"공포에 떨어라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"나를 보고도 가만히 있을 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"그래, 난 로쿠로쿠비야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				if(mon_id == MON_SEKIBANKI_HEAD)
					sprintf(temp_speak,"%s%s외쳤다. \"뭐하고 있나, 몸통아? 냉큼 와서 붙지 못하고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"난 머리를 떼어놔도 죽지않는다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				if(mon_id == MON_SEKIBANKI_HEAD)
					sprintf(temp_speak,"%s%s외쳤다. \"좋다, 내가 가주지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"후후, 내 능력을 보고 놀라지않을 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"윳쿠리란 생명체... 대체 뭐하는 놈들이지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"이전에 %s에게 윳쿠리로 오해받았다...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[randA(TRI_MAX-1)]);
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"그 누구라도 나를 두려워하지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s의 머리가 흔들리고 있다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				if(mon_id == MON_SEKIBANKI_HEAD)
					sprintf(temp_speak,"%s%s외쳤다. \"내 몸통, 내 몸통은 어디지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"머리가 어지러워! 새 머리를 줘!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"안돼!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s위태롭게 움직인다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s빙글빙글 돌아간다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			if(mon_id == MON_SEKIBANKI_HEAD)
				return NULL;
			switch(randA(1))
			{
			case 0: 
				sprintf(temp_speak,"%s%s머리를 부유시킨다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s의 머리가 날라다니기 시작한다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}		
		break;
	case MON_NITORI:		
		if(type == MST_NORMAL)
		{	
			switch(you.tribe)
			{
			case TRI_HUMAN:
				switch(randA(5))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"게겍, 인간?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"인간이 어째서 여기에 들어온거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"이봐 인간! 이 물건을 한번 사보지않겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"시리코다마를 바치러 온거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"옛날부터 인간과 캇파는 맹우였으니까 물러나주지않겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"새로운 도구의 시험을 해볼 수 있겠군!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case TRI_CROWTENGU:
				switch(randA(6))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"또 카메라가 필요한거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"카메라를 그렇게 함부로 다루지말라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"텐구의 취재는 사양하겠어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"왜 갑자기 공격하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"이번엔 내가 한수 보여주도록하지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"이번에 발명한 텐구의 스피드도 따라잡을 로켓... 어라? 작동하지않아?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"실력을 한번 볼까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case TRI_KAPPA:
				switch(randA(6))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"기술력은 내가 더 높은거같은데?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"현무의 계곡을 버리지마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"캇파가 밖에 나가서 뭘 하려는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"너구나! 주변을 마구잡이로 공격한다는 캇파가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"멍하니 있지말고 시스템의 수리를 도와주지 않겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"여긴 일손이 부족하다고! 너라도 돕지그래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"기술력 교환인가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case TRI_ONI:
				switch(randA(7))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"히익!?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s중얼거렸다. \"위험해... 위험해...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s중얼거렸다. \"여기서 오니를 만날줄이야...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"얼른 광학미채장치를...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"아뇨 이건 제가 싸우고 싶어서 싸운게 아니라...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"봐주시면 안될까요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s땀을 흘리고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s눈동자가 흔들린다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			default://기본대화
				switch(randA(7))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"캇파의 기술력을 봐라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					if(you.invisible_view)
					{
						sprintf(temp_speak,"%s%s외쳤다. \"어라 이 광학미채 고장난건가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						
					}
					else
					{
						sprintf(temp_speak,"%s%s외쳤다. \"광학미채를 시험해볼때가 왔군!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					}
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s중얼거렸다. \"오이가 먹고 싶어졌는데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"요즘 장사가 안되서 말이지, 너도 하나 사보지 않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"사지도 않을거면 나가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"여긴 내 주무대라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					if(you.god != GT_NONE)
						sprintf(temp_speak,"%s%s외쳤다. \"너도 종교같은걸 믿는거야? 나약하잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					else
						sprintf(temp_speak,"%s%s외쳤다. \"역시 너도 종교는 필요없다고 생각하는거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s외쳤다. \"이번에 새로 만든 신제품이야. 가격은 오이로 해도 좋아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"히익!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"살려주세요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s비명을 지른다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s의 가방에서 정체를 알수없는 도구가 튀어나온다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s가방에서 새 도구를 꺼냈다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s스위치를 눌렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_KEGERO:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"나랑 싸울거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"물리고 싶은거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"털 처리가 곤란해질거같아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"조용하게 있고싶었어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"개가 아니야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"늑대에게 쫓기고 살아남을 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s울부짖었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s발톱을 세웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"너무 어지러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"침착해져야해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s머리를 잡고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s머리를 흔들고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}	
		break;
	case MON_PARSI:
		//파르시는 크롤의 도날드 포지션. 다양한 던전, 신에 대한 대응 반응.
		if(type == MST_NORMAL)
		{	
			switch(randA(2)) //0은 노말, 1은 신, 2는 던전에 대한 질투
			{
			case 0:
				switch(randA(8))
				{
				case 0:
					sprintf(temp_speak,"%s%s외쳤다. \"부러워 부러워 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s중얼거렸다. \"파르파르파르파르파르...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"죽어도 다시 시작하는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"플레이어에게 조종받는다는건 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"나보다 행복해보여! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"어떻게 그렇게 아이템을 많이 들고 있는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"계단을 마음대로 이용할 수 있다는건 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s외쳤다. \"강하잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 8:
					sprintf(temp_speak,"%s%s외쳤다. \"네게 원한은 없지만, 공격할 이유정도는 얼마든지 만들 수 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}				
				break;
			case 1:
				switch(you.god)
				{
				default:
					switch(randA(0))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"그건 버그 신이잖아! 버그는 안 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_NONE:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"무신론자야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"신의 힘이 없어도 꽤 강하잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"혹시 신을 믿는 방법을 모르는거 아니야? p를 누르라고 p!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"신들이란 요구하는건 많지 제한하는 것도 많지...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"어쨌든 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"가끔 전도 하는 종교인들때문에 귀찮아... 너도 그렇지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"네게 원한은 없지만, 내가 너를 공격할 이유정도는 얼마든지 만들 수 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_JOON_AND_SION:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_BYAKUREN:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"마법사의 힘이야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"마법사면서도 굉장한 힘이잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"책이 너무 많아보이네! 나도 한권 줘! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"불교를 믿는데 술을 마실 수 있는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"불교는 요괴도 받아주는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"마법을 잘 써서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"다리 엄청빠르잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_KANAKO:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"그 단순 강력한 신의 힘 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"멋진 기둥이잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"너네 신의 개성넘치는 머리스타일! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"나에게 달려들어올거야? 그 무식함 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"혼자서 여러명을 상대할 생각이야? 그 무모함 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"신의 죽은 무슨 맛이야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_SUWAKO:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"그 신의 ZUN모 귀엽잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"재앙신을 믿는거야? 괜찮아? 어쨌든 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"개구리는 징그럽지않아? 그 비위가 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"무슨 권능을 원한거야? 알수없어서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"땅에서도 헤엄칠 수 있는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"이 던전의 개구리들 생각보다 강하잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_MINORIKO:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"고구마 맛있을거같아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"나도 고구마 하나 주지 않겠어? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"맛있을거같은 냄새가 나! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"역시 먹을걸 주는 신이란 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"던전에서 농사라도 할 생각이야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"잠깐 그 말도 안되는 회복력은 뭐야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_MIMA:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"강력한 마법이잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"마법이란 뭘 부수기위해서 쓰는거야? 무식해서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"마나가 떨어지면 어떻게 될지 궁금하네. 그 아슬아슬함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"그런 위험한 마법을 나에게 향하지말라고! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"너네 신의 이름을 난 들어본적이 없어. 매니악해서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"너네 신은 왜 몇년째 똑같은 소재로 인기있는거야? 그 꾸준함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"구작에서 신작에 오고싶어한다고? 난 구작에 출현한게 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_SHINKI:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"신이라고 창조도 하는건가. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"구작결계가 뭐? 난 언제나 2면보스인데! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"친구가 많아 보이네. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"판데모니움은 너무 길어. 지겹지않아? 그 근성이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"악마를 부릴 수 있다고 생각하는거야? 긍정적인 마음이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"악마의 배신에 죽으면 변명거리가 생기겠네. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"나에게도 P템을 가져갈거야? 수집욕이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_YUUGI:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"왜 유우기랑 친한거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"잠깐만! 던지지마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"레슬링 선수라도 되는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"유우기는 내 편이라고 생각했는데, 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"엥? 너가 왜 유우기의 힘을 쓰는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"뭐야, 자꾸 잡지말라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"싸우면서 술을 마시는 여유로움이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_SHIZUHA:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"오는지 몰랐어. 조용함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"뭐야 암살하려고한거야? 대사도 못할뻔했잖아, 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"자고있었는데 너의 질투심에 깨버렸어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"단풍이 이쁘네. 하나주지 않겠어? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"들키면 도망갈거야? 도망빨라서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"가을 타고 있는거야? 그 고독함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"잠깐, 단풍잎때문에 근처가 지저분해졌잖아. 청소안해도 되는 녀석은 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_HINA:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"저주가 좋아? 그 생각이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"나도 이전에 저주받은 단검을 주워버렸어. 그런걸 좋아할 수 있는 너가 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"오지마! 저주가 옮잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"너네 신은 그렇게 도는데 어지럽지않을까? 달팽이관이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"2면보스 선배. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"저주에 재앙받을게 무섭지않아? 그 용감함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"나도 액땜해주지 않겠어? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_YUKARI:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"안 쓰는 공간이동 두루마리 좀 나눠주지않겠어? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"나도 움직이는게 귀찮을땐 순간이동 해보고싶어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"맞으면 도망치는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"식신으로 사는건 어때? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"나 그거 포탈이란 게임에서 봤어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"지저에도 왠지 표지판을 들고다니는 애를 봤어. 표지판 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"나도 한번 그 틈새에 들어가보고싶어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_EIRIN:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"스스로 실험대상을 자처한거야? 그 용감함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"그 독물약 맛있어? 왠지 맛있어 보여 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"위기에서 마비물약을 먹을 생각을 하는 그 자신감이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"여기 능력치저하물약을 몇개 주웠어. 회복물약과 바꿔줘!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"약물 중독인거야? 왠지 불량해보여서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"물약 많아보이네, 나도 좀 나눠줘. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"봉래의 약은 만들 수 없는거야? 불로불사 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_YUYUKO:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"동료가 많아보이네, 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"유령은 차갑네, 여름에 시원할거같아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"죽여서까지 영혼으로 부려먹고있는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"유령으로 사는건 쾌적해 보여서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"심령현상 매니아야? 행복해보이네 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"설마 날 영혼으로 만들꺼야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"오싹오싹해. 호러에 강한가봐? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_SATORI:
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"애완동물 취급받고 있는거야? 귀여움받아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"마음 읽혀도 아무렇지도 않아? 그 순수한 마음 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"내 마음을 읽으려고해도 질투밖에 없을거야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"애완동물이 되면 새 이름을 받는거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"사토리의 새로운 애완동물이야? 친구가 많을거같아 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"애완동물이란 마음 편해보이네. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				case GT_TENSI:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"넌 마조야? 아픈것도 좋아할 수 있는건 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"너와 싸우면 무슨일이 생길지몰라! 저리가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"그런 신을 믿으면서 잘도 여기까지왔네. 그 운이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"넌 항상 신을 믿으면서 스릴 넘치겠네. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"비상의 검은 부러워! 하지만 신을 믿고싶진 않아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"너 머리위에 돌이 떨어지는거 안보여? 그 둔함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"땅이 흔들리잖아. 그 통제불능 신에게 말해서 어떻게 좀 해보라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
			case GT_SEIJA:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"그 지명수배 아마노자쿠를 믿는거야? 취향 참 특이하네\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"그 물건들은 전부 다른 신들에게서 훔친거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"도망자는 왠지 영화같아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"넌 아마노자쿠의 말을 믿을 수 있는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"지금은 별로 뒤집어지고 싶진않은데.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"점점 신앙심이 낮아지고있는게 눈에 보이는걸\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"나라면 아마노자쿠를 믿는 일은 안하겠어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
			case GT_LILLY:
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"요정들은 생각없이 사는 것 같아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"요정들은 죽어도 되살아나잖아? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"요정들이 세봐야 얼마나 세겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"넌 편하게 뒤에서 싸움을 구경해도 되니 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"별로 요정들이랑 친해지고싶은 생각은 없어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"친구가 많아보여서 부럽네! 정말 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"친구를 위해서 목숨을 버릴 수 있어? 아니 목숨을 위해 친구를 버리겠지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
			case GT_MIKO:
				switch (randA(6))
				{
				case 0:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak, "%s%s외쳤다. \"\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case GT_OKINA:
				switch (randA(6))
				{
				case 0:
					sprintf(temp_speak, "%s%s외쳤다. \"등 뒤가 수상한데...?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak, "%s%s외쳤다. \"문 여는데 선수구나! 부러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak, "%s%s외쳤다. \"혹시 잠긴 문을 따주는 열쇠수리공이라도 하는거야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak, "%s%s외쳤다. \"전용 백댄서라니 마치 아이돌같네! 부러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak, "%s%s외쳤다. \"문 뒤에서 왜 그렇게 살금살금 다니는거야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak, "%s%s외쳤다. \"저기 다니기 불편한 곳에 벽에 있는데 문 좀 열어줄래?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak, "%s%s외쳤다. \"문을 손 안대고도 열 수 있는거야? 부러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
			case GT_JUNKO:
				switch (randA(6))
				{
				case 0:
					sprintf(temp_speak, "%s%s외쳤다. \"혹시 소모품 남는 거 있어? 나 좀 빌려줄래?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak, "%s%s외쳤다. \"단순 무식하게 쎄보여서 부러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak, "%s%s외쳤다. \"대체 뭘 그렇게 원망하고 있는거야? 질투라면 안지지만\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak, "%s%s외쳤다. \"순수해보이니 부러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak, "%s%s외쳤다. \"그 살의는 나에게 향하지 말아줄래?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak, "%s%s외쳤다. \"너는 그것을 축복이라고 생각하는거야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak, "%s%s외쳤다. \"순수한 힘이란 부럽네!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				break;
				}
				break;				
			case 2:
				if(current_level<MAX_DUNGEUN_LEVEL){
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"던전엔 아이템이 많이 떨어져 있어서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"난 다른 층에 가보고 싶어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"지상세계 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"캇파나 인간들은 단체로 다니잖아. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"이 던전은 매우 조잡하게 생겼어. 다른 게임의 깔끔한 던전 생성 알고리즘 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"o를 눌러봤어? 자동탐색 알고리즘이 정말 멍청하다구! 다른 게임의 길찾기 알고리즘 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"혹시 대지의 스펠카드 가지고 있어? 벽을 허물 수 있다는건 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}				
				else if(current_level == TEMPLE_LEVEL){
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"제단이 정말 많네. 넌 뭘 믿을거지? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"날 신전까지 끌어다주다니 그 친절함 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"날 신전까지 보내줘도 난 신을 안믿을거야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"여기는 아무도 없고 조용하네. 창고로도 쓸 수 있겠어 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"날 왜 이곳으로 데려 온거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"여긴 부러운것 투성이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"신들은 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=MISTY_LAKE_LEVEL && current_level<=MISTY_LAKE_LEVEL+MAX_MISTY_LAKE_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"안개의 호수엔 마음 편해보이는 요정들이 많아. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"물이 왜 이렇게 많지? 헤엄칠수 있는 것들은 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"안개때문에 잘 보이지않아. 눈이 좋은 녀석들이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"요정들은 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"여긴 깨끗한 물이 많아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"요정들은 하늘을 날 수 있네. 하늘을 날면 빠지지않아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"물속을 헤엄치는 인어들도 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=YOUKAI_MOUNTAIN_LEVEL && current_level<=YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"이 텐구 캇파들 친구 많을거같아. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"직장인 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"조직생활은 현실에 충실한 애들 같아서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"캇파들의 도구 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"텐구들의 스피드 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"조금 전에 굉장한 캇파들의 비행기을 봤어! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"난 이 캇파 텐구들이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=SCARLET_LEVEL && current_level<=SCARLET_LEVEL+MAX_SCARLET_LEVEL) {					
					switch(randA(6))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"이 큰 저택의 주인은 일 안해도 되겠지? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"메이드옷 귀여워서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"이 홉고블린들은 뭐지? 일을 대신 해준다는건 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"조금 전에 추파카브라를 봤어. 저런 신기한걸 키우다니 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"메이드 요정들 일도 안하고 놀고 있었어! 놀면서 일하다니 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"지저에도 저택을 가진 요괴가 있어. 저택을 소유하다니 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"메이드 요정들이 홍차를 마시고 있었어. 홍차 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=SCARLET_LIBRARY_LEVEL && current_level<=SCARLET_LIBRARY_LEVEL+MAX_SCARLET_LIBRARY_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"책이 잔뜩이네. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 책이 나도 모르는 마법을 쓰고 있었어. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"책 좀 몇개 주워가도될까? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"이렇게 넓은 도서관이라니. 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"책 주제에 강하잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"조금 전에 도서관 주인과 만났어. 쿨해보여서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=SCARLET_UNDER_LEVEL && current_level<=SCARLET_UNDER_LEVEL+MAX_SCARLET_UNDER_LEVEL) {					
					switch(randA(3))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"난 왜 여기있는거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"악마의 여동생이 이 곳에 있어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 혼쭐이 났어. 그 강함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"이런 곳에서 나오지 않는데도 인기만점이잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=BAMBOO_LEVEL && current_level<=BAMBOO_LEVEL+MAX_BAMBOO_LEVEL) {					
					switch(randA(7))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"길을 잃었어! 좀 도와주지않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"토끼들은 길을 알고있는걸까? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"조금 전에 죽창에 찔릴 뻔했어. 그런 무기 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 행운의 흰토끼와 만났어. 그 행운이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"어라? 계속 같은 곳을 멤돌고 있는 느낌이.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"방금 전에 토끼들이 토끼를 부르고있었거든, 친구가 많은걸까 부러워.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 6:
						sprintf(temp_speak,"%s%s외쳤다. \"토끼가 너무 많아서 감당이 안되는데 광역 마법 가진거 있어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 7:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 큰 폭탄을 멘 토끼가 자폭했지뭐야. 그 무식함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=EIENTEI_LEVEL && current_level<=EIENTEI_LEVEL+MAX_EIENTEI_LEVEL) {					
					switch(randA(3))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"이상한 곳에 들어와버렸어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"이런 곳에 근사한 저택이 있잖아! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"여기선 달이 크게 보이는 걸! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"여기에도 토끼들이 잔뜩이잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=SUBTERRANEAN_LEVEL && current_level<=SUBTERRANEAN_LEVEL+MAX_SUBTERRANEAN_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"잘 왔어, 지저에\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"어딜 그렇게 급하게 가는거야? 즐거워보이니 부럽네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"구지 이렇게 모험할필요가 있을까? 돌아가는게 네 신상에 좋을거야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"현재 지하 666층... 정도일까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"왠지 지저애들이 나보다 쎄진 느낌이 드는걸... 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"지저에서 얼마나 버틸 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=YUKKURI_LEVEL && current_level<=YUKKURI_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"저 이상하게 생긴 생물체들은 뭐지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"얘네들은 걱정없이 사는 것 같아 부러워.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"얘네들 의외로 쎄잖아. 머리만 있는데! 부러워.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"왠지 맛있는 냄새가 나...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"이렇게 보고있으니 좀 징그럽네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"윳쿠리라고 하는거야? 너무 시끄러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=DEPTH_LEVEL && current_level<=DEPTH_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"벌써 여기까지 온거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"여기선 온갖 요괴들이 잔뜩 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"이상한 세계로 가는 포탈들이 잔뜩 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"여긴 지저로 가는 통로도 있어. 네가 갈 수 있는 곳은 아니겠지만!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"유에프오라고? 왠지 미스테리해서 부러워.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"오니? 왜 오니들이 지상에 이렇게 많이 올라와있는거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=DREAM_LEVEL && current_level<=DREAM_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"여기는 꿈의 세계라고 하는 거 같은데, 나는 꿈을 꾸고 있는건가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"개미핥기처럼 보여도 엄청 쎄구나! 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"꿈의 세계란 어디로든 갈 수 있는거야? 편리해보여서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"글쎄, 저 둥둥떠다니는 유령은 뭐지? 처음 보는걸.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"아까부터 내 영력이 바닥이야! 영력은 안쓰지만\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 이 쪽은 막혀있었는데!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=MOON_LEVEL && current_level<=MOON_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"이 엄청나게 많은 물은 뭐지? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"이상한 토끼들에게 쫓기고 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"모두 하이테크라서 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"달이라고? 내가 달에 온거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"아까부터 머리가 어지러운데.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"이럴줄 알았으면 비행을 배워두는건데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=PANDEMONIUM_LEVEL && current_level<=PANDEMONIUM_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"마계라고? 은근히 잘 발전되어있네! 부러워.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"똑같이 생긴 애들이 많은거같아. 내 착각인거겠지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"좀 전에 길을 물어봤는데 운이라고 하더라고, 이게 말이 돼?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"이상한 눈알들은 적아군 할거없이 마구 공격해, 미쳤다고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"마계도 살기 좋은거처럼 보이는데, 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"마계는 정말 넓네. 그 거대함이 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else if(current_level>=HAKUREI_LEVEL && current_level<=HAKUREI_LAST_LEVEL) {					
					switch(randA(5))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"신사라고 들었더니 요괴 천지잖아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 1:
						sprintf(temp_speak,"%s%s외쳤다. \"벌써 룬을 그만큼 모은거야? 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 2:
						sprintf(temp_speak,"%s%s외쳤다. \"이상한 탱크들때문에 도망쳐왔어. 탱크 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 3:
						sprintf(temp_speak,"%s%s외쳤다. \"난 음양옥이 이정도로 고생해야될 물건인지 잘 모르겠는데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 4:
						sprintf(temp_speak,"%s%s외쳤다. \"음양옥은 대체 뭐지? 룬은 대체 뭐야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					case 5:
						sprintf(temp_speak,"%s%s외쳤다. \"여기까지 온 그 강함, 순수하게 부러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}				
					break;
				}
				else {
					switch(randA(0))
					{
					case 0:
						sprintf(temp_speak,"%s%s외쳤다. \"여긴 버그 던전이야. 아니면 제작자가 추가하는걸 까먹었던지\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
						return temp_speak;
					}
					break;
				}				
				break;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"부럽지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"행복해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s파르파르 중얼거린다..",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s의 초록색 눈이 반짝이면서 주문을 외운다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}		
		break;
	case MON_BENBEN:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"츠쿠모가미를 무시하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"내 음악을 버틸 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"최강의 도구가 누구인지 알려줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"너도 도구를 버리는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s비파를 연주하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s연주에 집중하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"어지러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"불협화음이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s엉터리 연주를 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s불협화음으로 연주를 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s신비한 선율로 연주했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s곧은 선율로 연주했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_YATHASI:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"내 상대를 해주지 않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"너의 상대는 바로 나야! \"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"언니의 알기쉬운 음악으로는 안되니까!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"어딜 보고 있는거야, 상대는 나라구.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s고토를 연주하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s연주에 집중하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"안돼!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"연주에 집중이 안돼!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s엇박자 연주를 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s엉터리 연주를 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s기교있는 선율로 연주했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s아름다운 선율로 연주했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;		
	case MON_ORIN:
		if(type == MST_NORMAL)
		{
			if(you.god == GT_SATORI)
			{
				switch(randA(7))
				{
				case 0:		
					sprintf(temp_speak,"%s%s외쳤다. \"짜잔.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:	
					sprintf(temp_speak,"%s%s외쳤다. \"네가 사토리님의 새로운 애완동물이야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"그러네, 누가 더 사토리님에 어울리는 애완동물인지 시험해볼까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"오쿠랑은 만나봤어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"그래서 너는 고양이야? 개야? 아님 까마귀?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"여기 새로운 신참 애완동물이 들어왔을때 쓰는 일정표인데 일단 아침에는...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"고양이들이 밥을 달라고 하고있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s꼬리를 흔들면서 울었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			}
			else
			{
				switch(randA(7))
				{
				case 0:		
					sprintf(temp_speak,"%s%s외쳤다. \"짜잔.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:	
					if(you.tribe != TRI_WRAITH)
						sprintf(temp_speak,"%s%s외쳤다. \"언니 얼마나 강해? 죽으면 시체 좀 받아갈게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					else
						sprintf(temp_speak,"%s%s외쳤다. \"유령도 먹으면 맛있을거같아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					if(you.tribe != TRI_WRAITH)
						sprintf(temp_speak,"%s%s외쳤다. \"죽었을때 오린 운송을 불러줘!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					else
						sprintf(temp_speak,"%s%s외쳤다. \"이미 죽어있는거야? 유령 생활은 쾌적해?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"이 던전엔 시체가 잔뜩 있어. 행복해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"언니, 제법 강해보이는데?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					if(you.tribe != TRI_WRAITH)
						sprintf(temp_speak,"%s%s외쳤다. \"강한 시체는 운반할 보람이 있지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					else
						sprintf(temp_speak,"%s%s외쳤다. \"저기저기 언니의 시체는 어디있어? 내가 언니와 함께 운반해줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s들떠있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 7:
					sprintf(temp_speak,"%s%s냐옹냐옹 소리내고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스럽게 외쳤다. \"멍멍!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s혼란스럽게 외쳤다. \"까악까악!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s두 눈이 핑핑 돌고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s원령을 모으기 시작했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s손을 들어올렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_ICHIRIN:
		if(type == MST_NORMAL)
		{
			if(you.god == GT_BYAKUREN)
			{
				switch(randA(4))
				{
				case 0:		
					sprintf(temp_speak,"%s%s외쳤다. \"혹시 이번에 새로 묘렌사에 들어온 동료분이신가요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"이번 승부는 수련을 위한 결투로!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"묘렌사의 최강을 걸고 도전합니다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"좋습니다! 오세요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"오랫만에 수행이군요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			}
			else
			{
				switch(randA(6))
				{
				case 0:		
					sprintf(temp_speak,"%s%s외쳤다. \"문답무용!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s외쳤다. \"힘으로 얘기하는거면 자신있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 2:
					sprintf(temp_speak,"%s%s외쳤다. \"운잔의 주먹을 정면으로 맞고 버틸 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 3:
					sprintf(temp_speak,"%s%s외쳤다. \"포교 활동을 하고있어. 물론 일단은 주먹의 대화로!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 4:
					sprintf(temp_speak,"%s%s외쳤다. \"너에게 일단 한방을 먹이라고 운잔이 말하고 있어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s외쳤다. \"왜 불필요한 살생을 하고 있는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 6:
					sprintf(temp_speak,"%s%s외쳤다. \"더 이상의 난동은 이 이치린이 용납하지않겠다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"갑자기 술기운이...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어제 너무 많이 마셨나...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s머리를 부여잡고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s이상한 방향에 주먹질을 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s운잔을 불렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_PACHU:
		if(type == MST_NORMAL)
		{
			switch(randA(10))
			{
			case 0:		
				sprintf(temp_speak,"%s%s중얼거렸다. \"%s%s 처리하는데 가장 좋은 마법은...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[you.tribe],tribe_string_back[you.tribe]?"을":"를");
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"...도서관에선 조용히 해줘\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"마침 시험대상을 찾고있던 마법이 있었어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"저항은 충분해? 모든 속성에 대비는 해놨어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"잠시만 기다려 지금 필요한 마법이 적혀있는 책을 찾아보고\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"이번엔 이 마법은 어때?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s중얼거렸다. \"오늘의 불청객은 %s인가... 딱 시험해볼 마법이 있었어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),tribe_type_string[you.tribe]);
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s말했다. \"여기선 조심해, 책이 손상되니까.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s말했다. \"혹시 책을 가지러온거야? 미안하지만 방범대책은 한두번 해본게 아니라\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s말했다. \"잠시만 기다려줘 약점을 찾고있으니까\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s%s이쪽을 무시하는 듯이 책을 읽고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s중얼거렸다. \"...방심했어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s중얼거렸다. \"천식이 심해져서...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s기침을 심하게 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s책을 거꾸로 들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s책을 읽어 주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s손가락을 표적에 가리켰다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s책을 펼쳐 상대에게 향했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s하늘을 향해 손을 들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s의 책에서 빛이 나기 시작했다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s의 손에서 작은 불꽃이 일어났다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}		
		break;		
	case MON_KOAKUMA:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:
				sprintf(temp_speak,"%s%s위협적인 자세를 취했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s이 쪽의 상태를 엿보고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s날개를 파닥였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s가지고있는 책을 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s끄덕였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s웃음지었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s손에 탄막을 모았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스러워 보인다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s눈이 핑핑돌고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s방향을 잡지 못하고 비틀거린다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s똑바로 날지 못한다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_MEIRIN:
		if(type == MST_NORMAL)
		{
			switch(randA(6))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"칩입자? 여기서는 못 지나간다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"대련의 상대은 아닌거 같네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"앗... 잠깐 자고있었던거 뿐이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"문지기를 얕보지마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"태세성군의 부하인가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s기합을 넣고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s태극권을 추고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"눈이 핑핑 돈다~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"죄송해요 사쿠야씨!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s눈이 핑핑돌고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s허공에 발길질을 하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;	
	case MON_SAKUYA:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"청소의 방해이지만...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"또 청소의 방해를 하는건가요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"이것도 청소의 일환으로 해둘게요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"곧 당신의 시간은 멈출거에요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"이것은 속임수가 없는 마술입니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"아가씨에게 가시려는건가요? 시간을 멈춰서라도 막겠어요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"시간은 멈춰서라도 시간을 벌 수 있으니까요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"당신도 이 저택에 고용된 것인가요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s나이프를 이 쪽에 향했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"아아 아가씨...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"아아 눈앞이 돌고있어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s나이프를 떨어뜨렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s비틀거리고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s의 모습이 잠깐동안 사라졌다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s회중시계를 손에 쥐었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;	
	case MON_REMILIA:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"즐거운 밤이 될거같네\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"흡혈귀에 이길 수 있을거라 생각하는거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"우리 애완동물 추파를 괴롭힌게 너일까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"지금 보여주는 힘은 내 힘의 1할이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"이미 너에게 이길 운명은 없는것 같은데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"미안하지만 근접전이라면 지지않아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"저택에 소란을 피우고 있다는 칩입자가 너구나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"심심풀이로는 괜찮을려나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s날개를 크게 펼친다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"우-\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"어지러워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s쭈그리고 앉아 머리를 감쌌다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s손에서 붉은 기운을 모았다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s손짓을 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;	
	case MON_KASEN:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"수행을 더 쌓고 오도록!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"힘을 함부로 다루면 언젠간 큰일을 당하게 될거야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"더 이상 원하는대로 냅두지 않겠어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s외쳤다. \"칸다! 저녀석을 낚아채!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				if(you.tribe != TRI_ONI)
					sprintf(temp_speak,"%s%s외쳤다. \"설교가 필요할거같네\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"이런 곳에서 옛 동료를 만나고 싶진않았는데...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				if(you.god != GT_YUUGI)
					sprintf(temp_speak,"%s%s외쳤다. \"어때? 너도 내 밑에서 수행해보지않겠어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"이 힘은... 유우기의 힘?!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"아, 아냐! 난 오니가 아니라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"그만해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s의 팔에 감겨있던 붕대가 풀렸다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_FLAN:
		if(type == MST_NORMAL)
		{
			switch(randA(10)) 
			{
			case 0:		
				if(you.tribe == TRI_HUMAN)
					sprintf(temp_speak,"%s%s외쳤다. \"이 곳에 인간이 오는건 드문데?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다.  \"어라, 길을 잃은거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"그리고 아무도 없게 될까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"컨티뉴는 막혀있으니깐!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				if(you.tribe == TRI_HUMAN)
					sprintf(temp_speak,"%s%s외쳤다. \"인간은 케이크의 형태로 밖에 본적이 없는데 말이지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"그래 좀 더 버텨보라구!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"장난감이 들어왔네!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"어라 무모하지않아?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak,"%s%s외쳤다. \"어느 부분이 제일 잘 터질까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:
				sprintf(temp_speak,"%s%s외쳤다. \"불저항은 쓸모가 없을껄!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:
				sprintf(temp_speak,"%s%s외쳤다. \"아무리 갑옷을 칭칭 둘러도 도망쳐도... 도망칠 수 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 9:
				sprintf(temp_speak,"%s%s외쳤다. \"이번엔 반대편이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 10:
				sprintf(temp_speak,"%s의 날개가 반짝인다.",monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:
				sprintf(temp_speak,"%s%s난폭하게 지팡이를 휘두르고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s소름끼치게 웃었다. \"아하하!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s주변 기물을 닥치는대로 파괴하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s이쪽을 향해 손을 뻗었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s손짓을 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_RABIT_SUPPORT:
		if(type == MST_MAGIC)
		{
			sprintf(temp_speak,"%s%s나팔을 힘껏 불었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}	
		break;
	case MON_TEWI:
		if(type == MST_NORMAL)
		{
			switch(randA(7))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"길을 잃은거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"토끼들아 모여라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"난 그렇게 강하지않으니까 무시하고 지나가는게 좋아~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"토끼들이 떠들썩하더니 네가 원인이구나.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				{
					string way;					
					switch(randA(7))
					{
					case 0:way = "북";break;
					case 1:way = "동";break;
					case 2:way = "남";break;
					case 3:way = "서";break;
					case 4:way = "북동";break;
					case 5:way = "북서";break;
					case 6:way = "남동";break;
					case 7:way = "남서";break;
					}
					sprintf(temp_speak,"%s%s외쳤다. \"여기서 %s쪽으로 가면 원하는 곳으로 갈 수 있을꺼야~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true),way.c_str());
					return temp_speak;
				}
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"잠깐! 날 죽이면 죽림에서 탈출할 수 없어진다고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:		
				sprintf(temp_speak,"%s%s외쳤다. \"대나무를 자르다보면 낮은 확률로 숨겨진 템이 나오는거 알고 있었어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:		
				sprintf(temp_speak,"%s%s외쳤다. \"물론 전부 거짓말이야 우사~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(3))
			{
			case 0:
				sprintf(temp_speak,"%s%s외쳤다. \"거짓말해서 미안해요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s외쳤다. \"전 거짓말한적이 없어요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s외쳤다. \"착하게 살게요 살려주세요!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak,"%s%s울먹거리고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s큰 소리로 지원을 요청한다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_CLOWNPIECE:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"It's Lunatic Time!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"요정들아! 좀 더 속도를 올려서 가자!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				if(you.s_lunatic)
					sprintf(temp_speak,"%s%s외쳤다. \"그거 좋은 표정이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"여긴 예전에 비하면 훨씬 살기 좋은데!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"꺄하하!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				if(you.s_lunatic)
					sprintf(temp_speak,"%s%s외쳤다. \"그래 미쳐있는게 보기 좋다구!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"이 횃불을 보고도 미치지않을 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				if(you.s_lunatic)
					sprintf(temp_speak,"%s%s외쳤다. \"이미 넌 미쳐있는거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"곧 미치게될거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스러워하며 숨을 내쉬고있다. \"하아, 하아...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s말했다. \"어째서??\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s말했다. \"내가 미쳐있어야 되는게 아닌데...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s횃불을 거칠게 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_DOREMI:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"일단은 자고있으렴, 달콤한 꿈을 만들어줄테니까\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"악몽에 얼마나 버틸 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"슬슬 잠이 오지않아?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"영원한 꿈을...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"깨어나기엔 아직 이른 시간이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"이건 새로운 악몽인가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"그만해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_HELL_HOUND:
		if(type == MST_NORMAL)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s짖었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s하늘을 향해 길게 울부짖었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_LETTY:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"흑막 등장~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"뭐? 뚱뚱하다고? 아직도 그런 얘기를!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"지하는 서늘해서 좋단말이야. 지저는 너무 뜨겁지만.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				if(you.god == GT_SHIZUHA || you.god == GT_MINORIKO)
					sprintf(temp_speak,"%s%s외쳤다. \"가을은 이미 끝난지 오래야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"겨울의 힘을 보여줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				if(you.god == GT_SHIZUHA || you.god == GT_MINORIKO)
					sprintf(temp_speak,"%s%s외쳤다. \"가을이 뭐가 좋은거지? 이해할수가 없단말이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else
					sprintf(temp_speak,"%s%s외쳤다. \"그렇게 얕보지않는게 좋을텐데 말이지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"벌써 봄인거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"안돼! 겨울은 아직 끝나지않았어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_YORIHIME:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"칩입자? 달토끼들은 뭘하고있던거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"내가 직접 나서야겠어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"또 지상인인가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"당신의 목적은 뭐지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"부대! 목표를 공격해라!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s칼을 이리저리 휘두르고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s말했다. \"크윽, 이정도로...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s말했다. \"잠시만 시간이 있으면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s신령을 불러내기 시작한다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_TOYOHIME:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"더러움을 가진 지상의 죄인인가요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"살고 죽는것, 그것이 당신의 죄입니다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"달의 최신병기 앞에서 당신은 무엇을 할 수 있지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"더러움을 가진 자여, 얼른 여기서 떠나길\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"웃을 수 있는 것도 지금 뿐일거야\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란스러워하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s말했다. \"대체, 어떻게...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s말했다. \"이런 일이 생길리가...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s부채를 살짝 휘둘렀다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_UTSUHO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"칩입자 발견! 핵융합로의 반응을 정지하고 칩입자를 제거한다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"퓨전하지않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"복잡한건 모르겠지만 일단 한방 터트리면 되는거 아니야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"큰거 한방 나간다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"너를 쓰러트린 다음엔 지상에 도전할꺼야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"핵에너지로 흔적도 없이 녹아버려!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"우뉴?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"핵반응 제어불능! 제어불능!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s이곳저곳에 탄막을 쏘고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s제어봉을 타겟을 향해 조준했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_SUIKA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"오? 같이 한잔할래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"술 안주가 필요했거든, 가벼운 운동이면 되려나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"결국은 모이게 되어있지, 당신도 그렇게 모인거야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				if(you.tribe == TRI_ONI)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"못보던 녀석인데... 넌 어디 출신이지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"오니의 힘을 얕보는 순간 게임은 끝난거지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 4:						
				if(you.god == GT_YUUGI)
				{
					sprintf(temp_speak,"%s%s외쳤다. \"오! 유기잖아? 언제 같이 마셔야지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				else
				{
					sprintf(temp_speak,"%s%s외쳤다. \"오랫만에 연회나 열어볼까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				}
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"오니는 거짓말안한다고! ..가끔할지도\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"아하하, 취한다~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"난 항상 취해있는걸!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s헤롱헤롱거리고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s안개를 모으기 시작했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_REIMU:
		break;
	case MON_ALICE:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"새로운 인형을 시험해보기 딱 좋겠어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"탄막은 브레인이지, 당연한 얘기를 하고 있어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"전력을 다할거라고 생각해? 뒤가 없는건 질색이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"술사는 불필요한 전투를 하지않는다. 소환술사의 기본이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"몇몇 사람들은 인형보다 내 군화를 더 무서워하는거같아...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"얼른 도망쳐야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"제대로 인형을 조종할수가 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_SEIRAN:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"지금부터 정화활동에 들어간다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"일단 쏜다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"여기는 세이란, 적과 접촉했다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"이글래빗의 척후병 세이란, 타겟과 접촉, 정화를 실시한다.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s투덜거렸다. \"월급도 적지, 일은 고달프지...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"메이데이! 메이데이!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"달토끼 부대는 왜 지원이 안오는거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_RINGO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"지상에도 꽤 강한 자가 있다는 얘기를 들었는데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"척후병이 말한 애가 너일까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"여기는 조사부대 이글래빗, 타겟은 놓치지않아.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"알고있는게 많은 것도 그리 편하진 않더라고.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:	
				sprintf(temp_speak,"%s%s외쳤다. \"이런 근무조건이면 지상에서 사는것도 나쁘지않으려나\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"말단 생활은 질렸어~\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"여기는 링고! 위험상황에 처했다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s중얼거렸다. \"좋지않은걸\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s얼굴을 가리고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s경단을 먹으면서 주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_UDONGE:
		if(type == MST_NORMAL)
		{
			switch(randA(4))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"내 눈을 보고 미치지않을 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"지상의 토끼들은 별로 도움이 되지않아, 내가 나선다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"이 길을 지나칠 순 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"네가 보고있는 것은 진짜가 아니야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:		
				sprintf(temp_speak,"%s%s외쳤다. \"나도 3체로 분신하거나 환각을 걸거나 하고싶었어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"어째서 내가 혼란스러운거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"이럴리가... 나는 광기에 걸리지않을텐데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s눈에서 광기를 내보냈다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_KAGUYA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"이런 곳까지 찾아오다니 환영 인사를 해야겠네\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"이나바들은 뭘하고있는거야 참\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"너도 룬을 훔치러 온거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"그다지 움직이고 싶진않은데, 금방 쓰러져줄거지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:	
				sprintf(temp_speak,"%s%s외쳤다. \"넌 얼마나 많은 난제를 풀 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"그래, 영원히 고통받는거야\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"도와줘 에이린!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"안돼! 일하기 싫어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s머리를 잡고 혼란스러워하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_MOKOU:
		break;		
	case MON_TOKIKO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"책읽는 시간을 방해한 죄값을 치를거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"이 책은 빼앗기지않을꺼야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"너도 이 책을 노리는거지? 절대로 주지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"정말이지, 그 점주에게도 책을 돌려받아야하는데!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:	
				sprintf(temp_speak,"%s%s외쳤다. \"이름? 그런게 뭐가 중요해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"나도 조용히 있고 싶단말이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s울먹였다. \"나도 이름이 있었으면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s울먹였다. \"아직 나도 출현의 기회가...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s날개를 혼란스럽게 파닥이고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_TOZIKO:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"해치워주마!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"어리석은 것!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"이런 이런...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:		
				sprintf(temp_speak,"%s%s외쳤다. \"아직도 하나요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:	
				sprintf(temp_speak,"%s%s외쳤다. \"전기가 얼마나 잘 통하려나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"불쌍한 것!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"이 곳은 어디인가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"또 후토 네놈의 짓인가!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s하늘에 전기를 내뿜고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s전기를 끌어다 모으고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_FUTO:
		if(type == MST_NORMAL)
		{
			switch(randA(8))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"그대는 내 부활을 축복해주기위해 왔는가?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"흠, 자네의 운세를 보도록 하지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				if(!you.s_unluck) //흉 버프가 안걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"풍수를 읽는다면 못 읽을게 없다네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else //흉 버프가 걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"자네의 운... 어긋나있구려.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:	
				if(!you.s_unluck) //흉 버프가 안걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"속는 셈 치고 운세 한번 보는건 어떠나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else //흉 버프가 걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"이런이런... 조만간 큰 재앙을 당할것이야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"이보게! 그 접시를 깨버리면 화를 부른다고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"접시를 아무리 세봐도 1장이 모자라...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:		
				sprintf(temp_speak,"%s%s외쳤다. \"자네가 혹시 불에 잘타는지 시험해봐도 되나?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 7:		
				sprintf(temp_speak,"%s%s외쳤다. \"새로 개발한 비술의 시험을 해봐도되나? 조금 불길해질뿐이라네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 8:	
				if(!you.s_unluck) //흉 버프가 안걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"잠깐만 기다리게나! 내가 복을 부르는 술법을 사용해주지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				else //흉 버프가 걸려있을때
					sprintf(temp_speak,"%s%s외쳤다. \"어이쿠. 실수로 자네의 운을 건드렸구려. 곧 돌려놓도록하지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"토지코! 어디있는가! 얼른 날 도와주게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"부처가 눈앞에... 얼른 불태워버려야...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란하고 있다. \"이보게! 조금 움직이기 힘들어서 그런데 도와주겠나!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s접시에 기운을 모으고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_MAMIZO: //사투리 어떻게 쓰냐
		if(type == MST_NORMAL)
		{
			switch(randA(1))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"후~ 참으로 어리석구먼 \"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"자, 탄막변화 10판 승부! 시작해봅시다 그랴!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:	
				sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(0))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란하고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"부처가 눈앞에... 얼른 불태워버려야...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s혼란하고 있다. \"이보게! 조금 움직이기 힘들어서 그런데 도와주겠나!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(1))
			{
			case 0:
				sprintf(temp_speak,"%s%s나뭇잎에 기운을 불어넣는다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s곰방대를 물고 크게 연기를 만들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_SEIGA:
		if(type == MST_NORMAL)
		{
			switch(randA(5))
			{
			case 0:		
				sprintf(temp_speak,"%s%s외쳤다. \"재밌는 분이네요. 어디 실력을 시험해볼까요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s외쳤다. \"새로운 술법의 실험대가 필요했는데, 딱 좋을때 오셨어요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:		
				sprintf(temp_speak,"%s%s외쳤다. \"시해선에 관심이 있으세요? 제가 도와드리죠.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:	
				sprintf(temp_speak,"%s%s외쳤다. \"강시도 잘 보면 귀엽다고요. 강시가 되보시는건 어떤가요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak,"%s%s외쳤다. \"제 요시카는 꽤 튼튼하답니다. 몇번이고 상대해보셔도 좋아요.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:		
				sprintf(temp_speak,"%s%s외쳤다. \"강한 힘이 보고 싶을뿐이에요. 한번 겨뤄볼까요?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_CONFUSE)
		{
			switch(randA(2))
			{
			case 0:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"제법이시네요...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:		
				sprintf(temp_speak,"%s%s혼란하고 있다. \"연단으로 단련한 저를 이렇게 몰아붙이시다니...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak,"%s%s바닥에 구멍을 뚫으려고 시도했다",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if(type == MST_MAGIC)
		{
			switch(randA(0))
			{
			case 0:
				sprintf(temp_speak,"%s%s술법을 부렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}		
		break;
	case MON_MURASA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"승선을 환영합니다. 목적지는 저승이 되겠습니다.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				if (you.s_none_move)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"닻에 묶여있는 모습이 보기 좋네요.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else 
				{
					sprintf(temp_speak, "%s%s외쳤다. \"잠시만 거기 멈춰주시겠어요? 정박하겠습니다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 2:
				if (you.s_none_move)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"닻이 있는 한 도망칠 순 없을겁니다.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"이 쯤에서 닻을 내려볼까요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"수영은 할 줄 아시나요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"피의 연못... 그리워지네요.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"구명조끼는 챙기셨나요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"배가... 기울어졌다...!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"하필 이럴때 배 멀미가...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s국자를 이리저리 휘두르고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s닻을 높이 들었다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KEINE:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"과제 검사를 하겠어. 없을때마다 박치기 한번이야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘의 역사 수업은 온 몸으로 느끼는게 좋을거야.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"서당의 학생을 지키기 위해서라면 누구든 용서하지않아.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"너의 역사는 받아가겠어.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				if (you.tribe == TRI_HUMAN)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"인간과 싸우는건 꺼림직하지만... 어쩔 수 없지.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"그 인간에겐 손도 못대게 해주겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"네가 이기는 역사는 없을거야!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"큭, 봉인이 풀려버려!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"내가 제정신일때 도망쳐!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s머리를 쥐어뜯고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KEINE2:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"이 모습을 봤으니 살려보낼 수 없겠지\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"뿔에 받혀본 적 있어?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"이제 내가 이길 역사를 만들면 될 뿐이야\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"엉덩이를 내밀어라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"벌받을 시간이다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"태도가 나쁜 학생에겐 박치기형이다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이 상태에선 정신이 민감해서...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"얼른 진정하지 않으면...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s머리를 흔들면서 울부짖고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_YOUMU:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"요괴가 제련한 이 누관검이 벨 수 없는건, %s 없어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true), randA(2)? (randA(1)?"거의":"별로"):"아주 조금밖에");
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"일단 벤다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"마침 손질할 나무가 필요했던거야!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"이번에 수행한 검술을 시험해봐야겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"가까이 붙는다! 그리고 벤다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"쫄래 쫄래 도망치지마!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"유유코님! 어디 계세요!?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s땅에 넘어졌다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s사방에 검을 휘두르고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s검을 눈앞으로 모았다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_LYRICA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"나는 손대지 않고도 연주할 수 있어. 장기전이라면 내가 이기지\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"이번 연주의 관객은 너 혼자일까?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"가끔씩은 혼자서 라이브도 하고 싶어\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"언니들보단 내가 더 잘하지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이 곡이 끝날때까진 살아남아줘~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s의 키보드가 하늘에 떠다니면서 곡을 연주하고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어라, 박자를 맞출수가 없어.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어라 방금 쳤던 악보가 어디갔지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s불협화음으로 연주하고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 건반이 저절로 연주되고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_MERLIN:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"내 연주를 듣고 무사했던 식량은 없지\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				if (you.s_confuse)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"즐거워 보이는데~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"아직 내 음악을 듣고 멀쩡한거야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 2:
				if (you.s_confuse)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"내 음악을 들으면 조울증에 걸릴거야\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"좀 만 귀 기울여줄래?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"좀 더 신나는 곡을 연주할테니까 기다려~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이번 합주는 대 성공이야!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s의 트럼펫이 마음을 울리는 소리를 내고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"행복해~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이런 기분 오랫만이야\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s의 트럼펫이 시끄러운 나팔소리를 지르고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 트럼펫이 저절로 연주되고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_LUNASA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"식량 역할이 등장했나\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				if (you.s_slow)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"그래, 그대로 침착하고 있으라고\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"좀 더 차분하게 있는게 어때?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 2:
				if (you.s_slow)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"내 음악을 들은 이상 도망칠 순 없을거야\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"너무 들떠있는건 좋지않아\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"뭐가 그렇게 급한거지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이번 합주는 관객이 시시한걸\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s의 바이올린이 소름끼치는 소리를 낸다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"언니로서 침착해야할 내가...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"바이올린의 선이 느슨해진것같아...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s의 바이올린이 유리가 깨질듯한 소음을 낸다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 바이올린이 저절로 연주되고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_KOMACHI:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"시간떼우기 좋은 상대인걸?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"아냐, 벼, 별로 땡땡이치고있던건 아니라고\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"어디 사신다운 일도 가끔씩은 해볼까?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"혹시 도망칠 생각은 아니겠지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"혹시 새로운 자살 희망자일까?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"뱃사공 일은 지루하단말이지, 가끔씩은 몸쓰는 일도 하고싶어진다고\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"꺙!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"시... 시키 이키키님?! 땡땡이 치고 있지않았어요!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s바닥에 굴러 넘어졌다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s낫을 크게 들었다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_IKU:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				if (you.god == GT_TENSI)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"또 큰 아씨는 이상한 장난감을 주워서는...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"곧 있으면 큰 지진이 일어날거에요\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 1:
				if (you.god == GT_TENSI)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"큰 아씨에게 휘둘리는게 즐거우신가요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"좀 짜릿할텐데 괜찮겠나요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 2:
				if (you.god == GT_TENSI)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"큰 아씨에겐 조금 벌이 필요할 것 같군요.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"오늘 던전의 날씨는 천둥 번개가 치겠습니다.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"던전은 좀 답답하네요. 얼른 하늘위로 날고싶은데 말이죠\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이런 던전에 지진이 나면 어떻게 될까요?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"던전안에서도 번개를 만드는건 생각보다 어렵지 않아요.\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"지진이... 아니 지진이 아니야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"공기의 흐름을 얼른 타지않으면...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s하늘을 부자연스럽게 날고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(1))
			{
			case 0:
				sprintf(temp_speak, "%s의 주변에 정전기가 일어나고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s하늘 높이 손을 뻗었다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_LARVA:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"신세계의 신이라도 될 것 같아!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"우와! 싸움이다 싸움!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"한여름밤의 전쟁이다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘따라 힘이 넘쳐흘러!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘은 마음껏 날뛰겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"누구에게도 질 것 같지 않아!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어~라?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"항복!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s의 더듬이가 혼란스럽게 흔들리고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_NEMUNO:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"여기는 내 영역이다! 얼른 꺼져!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"볼일 없으면 얼른 내 집에서 나가!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"나가지않는다면 배를 갈라주겠어\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"어떻게 이런 곳까지 들어온거지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				if (you.tribe == TRI_CROWTENGU || you.tribe == TRI_WOLFTENGU)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"텐구라고? 불가침 조약을 맺었을 터인데?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"네가 누군지 알바 아니야. 얼른 나가!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"무력으로라도 쫓아내겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak, "%s%s외쳤다. \"누가 누굴보고 야만적이라는거지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"무... 무슨일이야!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어지러워!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s칼을 마구 휘두르고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_AUNN:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"이 제단은 내가 지키겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"가까워지면 물어버리겠어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"칩입자 발견! 제단을 지키겠어요!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"제단은 이상무!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s으르렁거리고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s사납게 짖고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"왜 이렇게 어지럽지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"나는 수호신으로서 제단을 지켜야...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s바닥에 뒹굴고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_NARUMI:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"내 마법을 시험해볼 상대를 찾고 있어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"너는 이 마법을 버틸 수 있을까?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"뒈져라 %s자식아!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true), tribe_type_string[you.tribe]);
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"잔념무념, 또 다음 생애에!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이 곳에서 쭉 혼자 있었어...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘따라 적을 한방에 날려버릴 마법을 쓸 수 있을 것 같아!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어라~ 여긴 어디?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"뭐야~ 이거\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s빙글빙글 돌고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_MAI2:
		if (type == MST_NORMAL || type == MST_CONFUSE)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘의 춤은 이거야!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"직접 싸울 필요도 없어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"테스트를 시작해볼까!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"네 상대는 내가 아니지!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"오키나님에게 거역할 셈이야?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"너도 곧 동료가 될지도 모르겠네!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_SATONO:
		if (type == MST_NORMAL || type == MST_CONFUSE)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"스승님에 눈밖에 난건 너야? 불쌍하네~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"날 잡아도 소용없을거야~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘 춤도 완벽한걸\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"힘내라 힘내라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"백댄서는 직접 싸우지않지~\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"직접 상대할 필요가 없을뿐이야\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s주문을 외웠다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KOKORO:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"희망의 가면은 어디있지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"최강의 자리를 두고 나와 겨뤄라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"오늘의 가면은 무엇을 사용하지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"넌 감정이 뭔지 알고 있어?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"가면극이라면 준비되어있어\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"다음 가면은 이걸로 해볼까...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이건 혼란할때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"어지러울땐 이 가면... 아 아닌가?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s가면을 세 개 정도 겹쳐써버렸다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s가지고 있는 가면 중 하나를 썼다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	case MON_KOKORO1:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"그대로 끝장내주마!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"최강의 자리를 두고 나와 겨뤄라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"불타버려라! 이 자식!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"이 자식! 면허가지고있냐! 내려라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이것은 분노할때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"이 끓어오르는 감정을 주체할 수 없어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이건 혼란할때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"너무 분노해서 앞이 안보여!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s가면을 거꾸로 쓰고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 가면에서 불이 뿜어져나온다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_KOKORO2:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"이런 약골이 상대라니 정말 슬프구나\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"너의 죽음은 미리 슬퍼해주지\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"뼈 속까지 얼어붙어라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"흑흑흑...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"이건 슬플때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"슬픈 표정은 어떻게 짓는 거지?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이건 혼란할때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"눈물로 앞이 보이질않아!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s가면이 어긋나 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 가면에서 싸늘한 냉기가 뿜어져나온다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_KOKORO3:
		if (type == MST_NORMAL)
		{
			switch (randA(5))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"벌써부터 승리의 기쁨이 넘쳐나는구나\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s외쳤다. \"오랫만에 싸울 상대를 찾아 기쁘구나!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"이건 승리의 포즈!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"해냈다!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"전기 통구이가 되어라!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"같이 가면극을 하지않을래?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"이건 혼란할때 쓰는 가면!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"너무 기뻐서 시야가 흔들리고있어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s가면을 땅에 떨어뜨렸다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s의 가면에서 정전기가 생겨나고 있다.", monster_info->GetName()->name.c_str());
				return temp_speak;
			}
		}
		break;
	case MON_SUMIREKO:
		if (type == MST_NORMAL)
		{
			switch (randA(6))
			{
			case 0:
				sprintf(temp_speak, "%s%s외쳤다. \"오랫만에 환상향에 도착했어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				if (you.tribe == TRI_HUMAN)
				{
					sprintf(temp_speak, "%s%s외쳤다. \"역시 환상향에도 인간은 있는거구나\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
				else
				{
					sprintf(temp_speak, "%s%s외쳤다. \"오호, %s라 흥미깊은데\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true), tribe_type_string[you.tribe]);
					return temp_speak;
				}
			case 2:
				sprintf(temp_speak, "%s%s외쳤다. \"비봉클럽의 초대 회장의 명예를 걸고 이겨주마\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 3:
				sprintf(temp_speak, "%s%s외쳤다. \"여고생이란게 얼마나 강한 생물인지 알고 있어?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 4:
				sprintf(temp_speak, "%s%s외쳤다. \"환상향의 주민은 전부 호전적이구나...\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 5:
				sprintf(temp_speak, "%s%s외쳤다. \"초능력을 쓰는 인간을 본적 있어?\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 6:
				sprintf(temp_speak, "%s%s기세 좋은 포즈를 취하고 있다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_CONFUSE)
		{
			switch (randA(2))
			{
			case 0:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"집에 가고 싶어!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"얼른 도망쳐야해!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 2:
				sprintf(temp_speak, "%s%s혼란하고 있다. \"엄마 살려줘!\"", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		else if (type == MST_MAGIC)
		{
			switch (randA(0))
			{
			case 0:
				sprintf(temp_speak, "%s%s숟가락을 들고 힘을 집중했다.", monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		}
		break;
	default:
		break;
	}
	if(type == MST_MAGIC)
	{
		sprintf(temp_speak,"%s%s주문을 외웠다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
		return temp_speak;
	}
	else if(type == MST_CONFUSE)
	{
		sprintf(temp_speak,"%s%s혼란스러워 하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
		return temp_speak;
	}
	sprintf(temp_speak,"%s%s외쳤다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_do(true));
	return temp_speak;
}