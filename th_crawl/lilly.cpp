//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: lilly.cpp
//
// 내용: 릴리
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "lilly.h"
#include "unit.h"
#include "monster.h"
#include "environment.h"
#include "mon_infor.h"
#include "skill_use.h"


int getMaxFairyName(){return 20;};

name_infor fairy_name[] =
{
	name_infor("메이",false),
	name_infor("미토리",false),
	name_infor("나노",false),
	name_infor("나나",false),
	name_infor("사츠키",false),
	name_infor("아카",false),
	name_infor("아오",false),
	name_infor("아이",false),
	name_infor("우미",false),
	name_infor("피카",false),

	name_infor("마저리",false),
	name_infor("소냐",false),
	name_infor("미아",false),
	name_infor("샤인",true),
	name_infor("파이",false),
	name_infor("루시",false),
	name_infor("리자",false),
	name_infor("이브",false),
	name_infor("에리카",false),
	name_infor("소조보",false)
};






extern char temp_speak[100];
const char* fairy_speak(monster* monster_info, int personal, FAIRY_SPEAK type)
{
	
	switch(monster_info->id)
	{
	case MON_DIEFAIRY:
		switch(type)
		{
		case FS_NORMAL:
				switch(randA(5))
				{
				case 0:
					sprintf(temp_speak,"%s%s꽃을 당신에게 선물했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 1:
					sprintf(temp_speak,"%s%s당신에게 웃어보였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;					
				case 2:
					sprintf(temp_speak,"%s%s수줍은듯 고개를 돌렸다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;				
				case 3:
					sprintf(temp_speak,"%s%s날개를 파닥였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;	
				case 4:
					sprintf(temp_speak,"%s%s당신에게 손을 흔들었다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				case 5:
					sprintf(temp_speak,"%s%s꽃을 줍고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
					return temp_speak;
				}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s고개를 끄덕였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s마음을 굳게 먹은듯하다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s반갑게 인사를 했다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
	case MON_SUNNY:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"보이지않으면 몰래 다가갈 수 있어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"이제 요정의 시대가 온거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"요정의 힘을 한데 모을때가 왔어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"질 생각이 들지않는걸!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"난 지금이 가장 재미있는 것 같아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"점점 강해지는 기분이 들어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
			break;
		case FS_ENTER:
			sprintf(temp_speak,"%s%s말했다. \"요정의 힘을 모을 수 있다면 가세하겠어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"진짜 팀워크를 보여주겠어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s외쳤다. \"써니 도착!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case MON_LUNAR:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"가끔씩은 조용히 커피를 마시고 싶어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"팀을 구성하면 요정이라도 꽤 강한거네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"이렇게 깊게 들어온적은 처음인데.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"소리를 죽이면 귀찮은 마법도 막을 수 있어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"잠깐 앉아서 책이라도 읽지 않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"역시 요정은 물량이 최고지.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
			break;
		case FS_ENTER:
			sprintf(temp_speak,"%s%s말했다. \"동료가 되면 때리지않을거야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"나도 할땐 한다고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"아픈건 싫어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case MON_STAR:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"요정이 모이면 이렇게 강한걸!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"아 잠깐만, 이곳에 좋은 식재료가\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"주변에 많은 반응이 있어, 몸 조심해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"왠지 보물찾기 같아서 즐거워!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"내 탐지 능력으론 정확한 적은 알 수 없어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"뭐 먹고 싶은 것 없어? 가끔씩은 요리를 할까 하는데\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
			break;
		case FS_ENTER:
			sprintf(temp_speak,"%s%s말했다. \"당신 편에 붙는게 더 이득일거 같네.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s말했다. \"요정들의 진정한 공포를 보여주는거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"겨우 돌아왔어. 다음엔 조심하지않으면...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case MON_CIRNO:		
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"날 따라와!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"더 강한 적이 필요해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"내 진짜 힘을 보여줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s당신에게 냉동개구리를 자랑스럽게 건네줬다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"내가 널 지켜줄게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"이 몸의 뒤에 있으면 안전할거라고!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s외쳤다. \"특별히 이 몸의 부하로 삼아주지!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"이런건 나 혼자서도 충분해!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s외쳤다. \"방금전엔 실수였어! 방금 그 녀석은 어디야??\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case MON_CLOWNPIECE:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"이 불꽃을 보고 멀쩡했던 사람은 없었어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"좀 더 광기를!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"정말 재밌어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s횃불을 이리저리 흔들고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"좀 더 속도를 올려서 가자!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"요정들의 세상이다!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s외쳤다. \"알겠어! 그 쪽이 더 즐거울거같아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"잇츠! 루나틱 타임!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"웰컴!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	default:
		break;
	}





	switch(personal)
	{
	default:		
	case FP_NORMAL:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"장난을 싫어하는 요정은 없어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"가끔씩은 나도 메이드를 해볼까 생각이 들곤해.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"어떤 장난을 칠때보다 지금이 제일 재밌어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"우린 최고의 팀이야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"새로운 친구들과 만나는건 항상 설레여!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s외쳤다. \"요정이 핍박받지 않은 시대를 위하여!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s말했다. \"나라도 도움이 될 수 있을까?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"요정을 위하여!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"요정은 죽지않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case FP_SHY:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"저기... 고마워\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s얼굴을 붉히고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s조심스럽게 말했다. \"나도 힘이 되고 있지?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s당신에게 존경의 시선을 날린다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"무리하지마...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s마음을 ",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s수줍게 고개를 끄덕였다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s말했다. \"...열심히 해볼게!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"부활할 수 있어도 죽는건 싫어...\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case FP_BRAVE:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"누구도 우릴 막을 순 없어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s말했다. \"지금 질 것 같은 생각이 들지 않아!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"난 싸우는게 제일 재밌어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"자, 다음 상대는 누구야?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"난 최강이 될거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"요정이 세상을 지배하는거야!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s자신있게 외쳤다. \"이제부턴 나한테 맡겨!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s외쳤다. \"돌격 앞으로!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"이젠 걱정마! 내가 돌아왔어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case FP_COLD:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"이젠 요정도 머리를 쓰는 시대야.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s가지고 있던 책을 읽고 있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s말했다. \"적의 정보를 알면 상대도 쉬울거야\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"가지고 있는 물건은 항상 체크하고있어?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"난 널 믿고있어\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"동료는 많을 수록 좋아\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s말했다. \"좋아. 힘을 빌려줄게\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s말했다. \"알겠어 그 작전대로 하자\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"방금 전엔 실수였어.\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	case FP_ANNOY:
		switch(type)
		{
		case FS_NORMAL:
			switch(randA(5))
			{
			case 0:
				sprintf(temp_speak,"%s%s말했다. \"놀자! 놀자!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			case 1:
				sprintf(temp_speak,"%s%s정신없이 비행하고있다.",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;		
			case 2:
				sprintf(temp_speak,"%s%s당신에게 돌멩이를 내밀었다. \"내가 주운 돌멩이!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 3:
				sprintf(temp_speak,"%s%s말했다. \"재밌는 장난이 떠올랐어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 4:
				sprintf(temp_speak,"%s%s말했다. \"저기저기, 숨박꼭질하지 않을래?\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;			
			case 5:
				sprintf(temp_speak,"%s%s말했다. \"재밌어! 재밌어!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
				return temp_speak;
			}
		case FS_ENTER:
			sprintf(temp_speak,"%s%s외쳤다. \"저기저기, 뭐하고 놀꺼야??\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_FAIRY_WAR:
			sprintf(temp_speak,"%s%s말했다. \"새로운 놀이야? 나도 낄래 낄래!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		case FS_REVIVE:
			sprintf(temp_speak,"%s%s말했다. \"아직 안 끝났지? 계속 놀자!\"",monster_info->GetName()->name.c_str(), monster_info->GetName()->name_is(true));
			return temp_speak;
		}
		break;
	}
	
	return "<릴리 요정 에러메세지>";

}



void GetFairyExp(int exp)
{
	int enter_ = 0;
	for(auto it = env[current_level].mon_vector.begin(); it != env[current_level].mon_vector.end();it++)
	{
		for(int i = 0; i<5;i++)
		{
			if(you.god_value[GT_LILLY][i] == 1)
			{
				if(it->isLive() && (*it).isUserAlly() && it->map_id == you.lilly_allys[i].map_id && current_level == you.lilly_allys[i].floor)
				{				
					you.lilly_allys[i].exp += exp;

					while(level_up_value[you.lilly_allys[i].level-1] <= you.lilly_allys[i].exp)
					{
						you.lilly_allys[i].level++;

						while(you.lilly_allys[i].level> it->level)
						{
							it->LevelUpdown(1,6.0f,1.0f);
							if(it->isYourShight())
							{
								printarray(false,false,false,CL_normal,3,it->name.name.c_str(),it->name.name_is(true),"강해졌다. ");
								enter_++;
								if(enter_>=4)
									enterlog();
							}
						}

						int prev_id = it->id;
						switch(it->id)
						{
						case MON_FAIRY_GREEN:
							if(it->level >= 5)
							{
								it->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_BLUE:
							if(it->level >= 7)
							{
								it->ChangeMonster(MON_FAIRY_BLUE_MAGICIAN,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_RED:
							if(it->level >= 8)
							{
								it->ChangeMonster(MON_FAIRY_RED_COMMANDER,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_GREEN_WARRIOR:
							if(it->level >= 12)
							{
								it->ChangeMonster(MON_FAIRY_HERO,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_BLUE_MAGICIAN:
							if(it->level >= 10)
							{
								it->ChangeMonster(MON_FAIRY_SOCERER,M_FLAG_ALLY);
							}
							break;
						case MON_FAIRY_RED_COMMANDER:
							if(it->level >= 13)
							{
								it->ChangeMonster(MON_FAIRY_GREEN_WARRIOR,M_FLAG_ALLY);
							}
							break;
						case MON_SUNNY:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_LASER,20));
							}
							break;
						case MON_LUNAR:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_SMITE,20));
							}
							break;
						case MON_STAR:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_HASTE_OTHER,20));
							}
							break;
						case MON_DIEFAIRY:
							if(it->level == 13)
							{
								it->spell_lists.push_back(spell(SPL_HEAL_OTHER,20));
							}
							break;
						}
						if(prev_id != it->id)
						{						
							you.lilly_allys[i].id = it->id;
							if(!(it->flag & M_FLAG_UNIQUE))
							{
								it->name.name = fairy_name[you.lilly_allys[i].name].name;
								it->name.name_type = fairy_name[you.lilly_allys[i].name].name_type;
							}
							if(it->isYourShight())
							{
								if(enter_>0)
								{
									enterlog();
									enter_ = 0;
								}
								printarray(true,false,false,CL_normal,6,"그동안 쌓은 경험으로 ",mondata[prev_id].name.name.c_str(),"에서 ",mondata[it->id].name.name.c_str(),mondata[it->id].name.name_do(true),"되었다.");
								
							}
						}					
					}
				}
			}
		}
	}
	enterlog();
}






