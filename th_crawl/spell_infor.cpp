//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: spell_infor.cpp
//
// 내용: 마법과 스킬의 정보
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "environment.h"
#include "display.h"
#include "key.h"
#include "player.h"
#include "skill_use.h"



string GetSpellInfor(spell_list spell)
{
	string text_ = SpellString(spell);
	text_ += "\n\n";
	switch(spell)
	{	
	case SPL_NONE:
		text_ += "존재하지 않는 마법이다.\n";
		break;
	case SPL_MON_TANMAC_SMALL:
		text_ += "작은 탄막을 발사한다.\n";
		break;
	case SPL_MON_TANMAC_MIDDLE:
		text_ += "적당한 탄막을 발사한다.\n";
		break;
	case SPL_MON_WATER_GUN:
		text_ += "물총을 발사한다.\n";
		break;
	case SPL_FLAME:
		text_ += "작은 화염을 탄막으로 날린다.\n";
		break;
	case SPL_FROST:
		text_ += "작은 냉기를 탄막으로 날린다.\n";
		break;	
	case SPL_MEDICINE_CLOUD:
		text_ += "콘파로~ 콘파로~ 은방울꽃의 독이 주 성분\n";
		text_ += "이 독에 갇히면 이동속도가 느려지고 중독상태가 된다.\n";
		break;
	case SPL_COLD_BEAM:
		text_ += "공기를 일직선으로 얼려서 상대에게 타격을 준다.\n";
		text_ += "냉기구름도 생기기도 한다.\n";
		break;
	case SPL_SUMMON_BUG:
		text_ += "작은 곤충들을 소환해낸다.\n";
		break;
	case SPL_CONFUSE:
		text_ += "적에게 일시적으로 혼란을 거는 정신계열마법. 혼란에 빠진 상대는 자신의 의지대로 움직이지 못한다.\n";
		text_ += "저항할 확률이 있다.\n";
		break;
	case SPL_SLOW:
		text_ += "적에게 일시적으로 감속을 거는 정신계열마법. 감속에 걸리면 모든 행동이 1.6배로 느려진다.\n";
		text_ += "저항할 확률이 있다.\n";
		break;
	case SPL_SELF_HEAL:	
		text_ += "자신을 약간 치료한다.\n";
		break;
	case SPL_BLINK:
		text_ += "짧은 거리를 순식간에 이동하는 전이계열마법.\n";
		text_ += "구름, 함정, 물같이 위험한 위치로는 이동하지 않으며 이동하는 위치는 무작위로 결정된다.\n";
		text_ += "공간이동제어가 있을 경우, 방향을 지정하여 이동하는 위치를 대략 정할 수 있다.\n";
		break;
	case SPL_SMITE:
		text_ += "상대방에게 천벌을 내린다. 시야안에 있기만 하면 성공하며 피할 수 없다.\n";
		break;
	case SPL_BURN:
		text_ += "짧은거리의 상대방을 불꽃으로 태워버리는 화염속성 기초마법.\n";
		text_ += "데미지가 좋지만 빗나갈 확률이 있다.\n";
		break;
	case SPL_FIRE_WALL:
		text_ += "원하는 위치에 불기둥을 생성하는 화염계열 마법.\n";
		text_ += "이미 몬스터가 존재하는 곳에는 사용할 수 없으며 생성이 되면 일정시간후에 저절로 사라진다.\n";
		text_ += "상대의 진로를 막거나 불기둥으로 데미지를 줄 수 있다.\n";
		break;
	case SPL_FROZEN:
		text_ += "밀착한 상대의 온도를 빼앗는 냉기속성 기초마법.\n";
		text_ += "밀착한 상대에게만 사용할 수 있지만 상대는 피할 수 없다.\n";
		break;
	case SPL_FREEZE:
		text_ += "짧은 범위안 1명의 적 주변의 공기를 순식간에 냉동시키는 마법.\n";
		text_ += "피할 수 없으며 추가로 상대를 얼려 이동속도를 느리게하는 추가 효과가 있다.\n";
		break;
	case SPL_STING:
		text_ += "마법으로 독침을 구현하여 탄막으로 발사하는 독속성 기초마법.\n";
		text_ += "맞은 상대는 약한 독에 걸리며 여러번 맞출 경우 독은 중첩된다.\n";
		break;
	case SPL_CURE_POISON:
		text_ += "자신에게 걸려있는 독을 해독하는 마법.\n";
		text_ += "사용즉시 효과를 발휘한다.\n";
		break;
	case SPL_TWIST:
		text_ += "원하는 위치의 공기의 흐름을 비트는 대기마법. 몬스터가 있는 위치에도 사용할 수 있다. \n";
		text_ += "사용한 위치에 생성되어서 몇턴간 지속된다.\n";
		break;
	case SPL_SUMMON_MOOK:
		text_ += "주변에 모옥을 소환하는 소환계열 기초마법.\n";
		text_ += "모옥이 1~2마리가 자신의 주변에 아군으로 소환된다. 소환물은 시간이 지나면 사라진다.\n";
		break;
	case SPL_FIRE_BRAND:
		text_ += "장착하고 있는 무기에 화염속성을 일시적으로 부여하는 마법. 화염속성은 화염데미지를 준다.\n";
		text_ += "이미 속성이 있거나 맨손, 아티펙트무기에는 사용할 수 가 없다.\n";
		break;
	case SPL_COLD_BRAND:
		text_ += "장착하고 있는 무기에 냉기속성을 일시적으로 부여하는 마법. 냉기속성은 냉기데미지를 준다.\n";
		text_ += "이미 속성이 있거나 맨손, 아티펙트무기에는 사용할 수 가 없다.\n";
		break;
	case SPL_POISON_BRAND:
		text_ += "장착하고 있는 무기에 독속성을 일시적으로 부여하는 마법. 독속성은 때릴때 독을 건다.\n";
		text_ += "이미 속성이 있거나 맨손, 아티펙트무기에는 사용할 수 가 없다.\n";
		break;
	case SPL_SHOCK:
		text_ += "1인적에게 전기를 통하게 하는 전기속성 기초마법.\n";
		text_ += "전기의 궤도는 정할 수 없지만 방향을 정하면 해당 방향으로 마법을 사용한다.\n";
		text_ += "해당 방향에 존재하는 적중에서 무작위의 적에게 전기가 통하여 데미지를 준다.\n";
		text_ += "전기저항이 없거나, 가까이있는 적에게 전기가 통할 확률이 높다.\n";
		break;
	case SPL_CHAIN_LIGHTNING:
		text_ += "전기가 적을 차례대로 타고가면서 다수의 적을 공격하는 강력한 전기속성마법.\n";
		text_ += "적에게 직접 조준하는건 불가능하지만 방향을 지정하여 가까이있는 적부터 차례대로 전기가 통한다.\n";
		text_ += "2번이상 전기가 타고갔을때, 시야밖에 있는 적에게도 공격이 가능하다.\n";
		break;
	case SPL_DISCHARGE:
		text_ += "전기를 내뿜어 방전시키는 전기마법. 방전상태가되면 몇턴마다 무작위로 주위적에 전격을 시전한다.\n";
		text_ += "모티브는 이쿠의 뇌운극어라는 설이...\n";
		break;
	case SPL_LEVITATION:
		text_ += "전극을 이용하여 일시적인 비행상태가 되는 마법. 깊은물같은 지형을 통과할 수 있게 된다.\n";
		break;
	case SPL_GLOW:
		text_ += "조명으로 적을 비춘다. 조명으로 비춰진 적은 일시적으로 회피가 감소한다.\n";
		text_ += "저항할 확률이 있다.\n";
		break;
	case SPL_GRAZE:
		text_ += "일시적인 그레이즈 상태가 된다. 그레이즈 상태에선 모든 원거리 탄막을 회피할 확률이 생긴다.\n";
		text_ += "틱틱틱 소리는 미지원이다.\n";
		break;
	case SPL_VEILING:
		text_ += "잠시 공기의 보호막을 만드는 대기속성 기초마법. 일시적으로 베이링상태가 된다.\n";
		text_ += "베이링 상태에서 적에게 근접 공격을 맞으면 데미지를 준다.\n";
		text_ += "1회용 마법으로 한번 데미지를 주면 보호막은 사라진다.\n";
		break;
	case SPL_INVISIBLE:
		text_ += "일시적 투명화할 수 있는 마법. 투명상태에서는 상대에게 들킬 확률이 현저히 줄어든다.\n";
		text_ += "이미 밀착해있으면 낌새를 눈치채서 따라올 수 있으며 투명을 보는 상대도 존재한다.\n";
		text_ += "투명상태에서는 P의 소모가 매우 빨라지니 주의해야한다.\n";
		break;
	case SPL_HASTE:
		text_ += "일시적인 가속을 거는 마법. 가속 상태에서는 모든 움직임이 빨라진다.\n";
		text_ += "연금술로 인한 가속이지만 다른 방법으로 얻는 가속과 중첩되진 않는다.\n";
		break;
	case SPL_SILENCE:
		text_ += "주의의 소음을 없애는 마법. 주변의 소리를 내는 행동을 금지한다.\n";
		text_ += "마법사용, 권능사용, 두루마리 읽기등이 금지된다. \n";
		text_ += "소리가 사라져 부자연스럽기때문에 은밀에 오히려 악영향을 준다. \n";
		text_ += "사용하면 범위안에 효과를 주지만 시간이 지나면 범위가 줄어든다.\n";
		break;
	case SPL_SWIFT:
		text_ += "잠시동안 빠른 이동속도를 가지게 된다.\n";
		text_ += "이동외의 행동속도에는 영향을 주지 않는다.\n";
		break;
	case SPL_MAGIC_TANMAC:
		text_ += "영력을 이용해 간단한 탄막을 날리는 기초 요술마법. 플레이어의 쇼트라고 보면 된다.\n";
		text_ += "무조건 명중하지만 데미지는 약한 편이다.\n";
		break;
	case SPL_FIRE_BALL:
		text_ += "화염구를 만들어 날리는 화염계 공격마법.\n";
		text_ += "적에 부딪히거나 목표에서 터지며 주변에 폭발데미지를 입힌다.\n";
		text_ += "자신도 가까이 있으면 데미지를 받을 수 있다.\n";
		break;
	case SPL_FIRE_BOLT:
		text_ += "거대한 화염의 탄환을 발사하는 강력한 화염계 공격마법.\n";
		text_ += "적을 관통하는 특징이 있다.\n";
		break;
	case SPL_ICE_BOLT:
		text_ += "거대한 냉기의 탄환을 발사하는 강력한 냉기계 공격마법.\n";
		text_ += "적을 관통하는 특징이 있다.\n";
		break;
	case SPL_VENOM_BOLT:
		text_ += "강력한 맹독의 탄환을 발사하는 강력한 독속성 공격마법.\n";
		text_ += "맞은 적은 독에 걸리며 적을 관통하는 특징이 있다.\n";
		break;
	case SPL_CONFUSE_CLOUD:
		text_ += "악취가 나는 구름의 구슬을 발사한다. 해당지점에서 폭발해서 구름을 만들어낸다.\n";
		text_ += "구름에 쌓이게되면 혼란에 걸리게된다. 자기자신도 걸릴 수 있다.\n";
		break;
	case SPL_POISON_CLOUD:
		text_ += "시야내 원하는 위치에 독구름 뭉치를 만들어낼 수 있다.\n";
		text_ += "시야내라면 어디든지 만들어 낼 수 있고 좁은 골목일 경우 넓게 퍼지는 특징이 있다.\n";
		break;
	case SPL_ICE_CLOUD:
		text_ += "시야내 원하는 위치에 냉기구름 뭉치를 만들어낼 수 있다.\n";
		text_ += "시야내라면 어디든지 만들어 낼 수 있고 좁은 골목일 경우 넓게 퍼지는 특징이 있다.\n";
		break;
	case SPL_SUMMON_BIRD:
		text_ += "다양한 새들을 소환할 수 있는 소환계 마법.\n";
		text_ += "파워가 높아질수록 더욱 더 강한 새들을 소환할 수 있다.\n";
		break;
	case SPL_RECALL:
		text_ += "현재 층에 있는 모든 소환물들을 자신의 주변에 불러들인다.\n";
		break;
	case SPL_TELEPORT_OTHER:
		text_ += "상대방에게 공간이동을 거는 마법. 바로 공간이동 되지 않고 약간의 딜레이가 있다.\n";
		text_ += "저항할 확률이 있다.\n";
		break;
	case SPL_TELEPORT_SELF:
		text_ += "자신에게 공간이동을 거는 마법. 바로 공간이동 되지 않고 약간의 딜레이가 있다.\n";
		break;
	case SPL_WHIRLWIND:
		text_ += "강한 회오리 바람을 상대위치에 생성시킨다.\n";
		text_ += "지속적인 데미지를 준다. 시전자인 아야는 이 바람에 면역이 있다.\n";
		break;
	case SPL_SUMMON_PENDULUM:
		text_ += "펜듈럼을 소환한다.\n";
		text_ += "펜듈럼은 공격하지않지만 소환수로의 공격을 대신 막아준다.\n";
		break;
	case SPL_SUMMON_SEKIBANKI:
		text_ += "세키반키가 자신의 머리를 띄운다.\n";
		text_ += "본체가 취약해지므로 본체를 노리자.\n";
		break;
	case SPL_WATER_CANNON:
		text_ += "물을 압축하여 발사한다.\n";
		text_ += "맞은 상대를 밀쳐낼 수 있다.\n";
		break;
	case SPL_KYOKO_SMITE:
		text_ += "쿄코의 특수 스킬. 굉음으로 상대에게 인사를 한다\n";
		text_ += "너무나도 큰 소리에 직접적인 데미지를 받는다.\n";
		text_ += "어떤 방어도 듣지않으며 아주 짧은 혼란이 걸리기도 한다.\n";
		break;
	case SPL_SUMMON_OPTION:
		text_ += "옵션을 소환하는 마법. 옵션은 소환사의 주변을 멤돌면서 시야내의 적을 요격한다.\n";
		break;
	case SPL_SUMMON_GOLEM:
		text_ += "마법의 골렘을 소환한다.\n";
		text_ += "골렘은 사용자의 파워에 따라 위력이 천차만별이다.\n";
		break;
	case SPL_HYPNOSIS:
		text_ += "상대가 인지못할정도의 작은 최면을 걸어서 상대를 자기 의지와 다르게 움직이게 할 수 있다.\n";
		text_ += "상대는 앞으로 걷고있다고 생각하는 도중에 무의식중에 랜덤한 방향으로 1칸 이동하게 된다.\n";
		text_ += "이 이동하는 방향에 벽이 있거나 다른 몬스터가 있으면 큰 데미지를 입게된다. 가끔 자신의 타겟을 잃어버린다.\n";
		text_ += "계단을 내려가는데 계단이 있는줄알고 내려갔을때 계단이 없었을때 받는 정신적 충격과 비슷한 효과이다.\n";
		break;
	case SPL_MUTE:
		text_ += "상대를 마법으로 짧은 실어증을 만든다.\n";
		text_ += "마법에 의한 실어증으로 이는 배우고 있는 마법자체를 잠시동안 잊게 하여 마법을 못쓰게한다.\n";
		text_ += "상대가 말을 안하고 마법을 쓸 수 있어도 마법에 의한 실어증이므로 이 동안은 마법을 쓸 수 없다.\n";
		break;
	case SPL_SELF_INJURY:
		text_ += "상대를 자해하게 만든다. 상대의 데미지가 높을수록 큰데미지를 입힌다.\n";
		text_ += "상대가 강할수록 효과가 좋지만 상대가 강할수록 저항할 확률도 높아지므로 조심해야한다.\n";
		//text_ += "아군인 상대에게 쓰면 충실한 아군이 자살할 수 있는 부가 효과가 있다.\n";
		//text_ += "단, 저항하는데 성공하면 아군에서 적으로 변화할 수 있다.\n";
		break;
	case SPL_CHARM:
		text_ += "상대를 마법으로 일시적인 아군으로 만든다.\n";
		text_ += "일시적인 아군이 되면 주변의 무리들과 싸우게 된다. 시간이 지나면 다시 적으로 돌아가게 된다.\n";
		//text_ += "이렇게 일시적 아군인 상태에서 자해마법을 사용하면 자살하게 된다.\n";
		break;
	case SPL_LASER:
		text_ += "일직선으로 데미지를 주는 순수 요술마법.\n";
		text_ += "적을 관통할 수 있으므로 유용하다.\n";
		break;
	case SPL_SPARK:
		text_ += "강력하고 거대한 빔을 쏘는 마법.\n";
		text_ += "스파크와 레이저는 로망이다. 탄막은 화력이다.\n";
		break;
	case SPL_SUMMON_UNZAN:
		text_ += "거대한 운잔을 소환하는 마법.\n";
		text_ += "마법이라기보단 기본이다.\n";
		break;
	case SPL_SUMMON_UNZAN_PUNCH:
		text_ += "운잔이 자신의 주먹을 상대 옆에 소환하는 마법.\n";
		text_ += "주먹에 맞으면 매우 아프다.\n";
		break;
	case SPL_SUMMON_ZOMBIE_FAIRY:
		text_ += "상대 주변에 좀비페어리를 소환하는 마법.\n";
		text_ += "굉장히 많은 좀비페어리들이 소환되므로 귀찮다.\n";
		break;
	case SPL_SUMMON_UFO:
		text_ += "미확인 비행물체를 소환하는 마법.\n";
		text_ += "벤토라는 저절로 색깔을 바꿔가면서 다른 속성 다른 저항으로 변화된다.\n";
		break;
	case SPL_HASTE_OTHER:
		text_ += "아군을 가속시키는 마법.\n";
		text_ += "근처의 아군에 가속을 걸어준다.\n";
		break;
	case SPL_HEAL_OTHER:
		text_ += "아군을 회복시키는 마법.\n";
		text_ += "근처의 아군을 회복시킨다.\n";
		break;
	case SPL_MIND_BENDING:
		text_ += "파장을 담은 탄막을 발사하여 맞은 상대의 파장을 굽힌다.\n";
		text_ += "자체에도 데미지가 있고 저항에 실패하면 상대의 속도를 낮추는 우수한 기술이지만\n";
		text_ += "파워가 올라도 데미지 상승폭이 적고 슬로우는 저항할 가능성이 있으며\n";
		text_ += "다른 디버프와 달리 상대가 회피할 수 있다는 단점이 있다.\n";
		break;
	case SPL_STONE_PUNCH:
		text_ += "맨손에 바위의 힘을 담는 연금술 마법.\n";
		text_ += "다음 1번의 공격에 한해서 맨손에 강력한 힘을 담아서 데미지를 증가시킨다.\n";
		text_ += "무기를 끼고 있을때는 사용할 수 없다.\n";
		break;
	case SPL_STONE_ARROW: 
		text_ += "바위로 만들어진 탄막.\n";
		text_ += "맞으면 아프지만 멀리 못날라가고 움직임이 직선적이라 피하기가 쉽다.\n";
		break;
	case SPL_STONE_TRAP:
		text_ += "일정시간 3*3 바닥에 밟으면 아픈 뾰족한 바위를 설치한다.\n";
		text_ += "그 위를 지나가면 피아불문 작은 데미지를 입는다. 그러나 날고 있으면 무시할 수 있다.\n";
		text_ += "파워가 높아질수록 더 많이 설치 할 수 있다.\n";
		break;
	case SPL_STONE_UPLIFT:
		text_ += "원하는 위치의 대지에 마법을 걸어 빠른 속도로 융기시키는 마법.\n";
		text_ += "뾰족한 바위가 올라오면서 작은 범위에 큰 데미지를 준다.\n";
		text_ += "파워가 낮으면 범위안에서도 폭발이 안일어날 수 있다.\n";
		break;
	case SPL_KANAME_DRILL:
		text_ += "단단한 요석을 직선으로 날린다.\n";
		text_ += "요석은 타겟에 맞으면 회전하면서 데미지를 증가시킨다.\n";
		text_ += "높은 데미지를 줄 순 있지만 적을 관통하진 못한다.\n";
		break;
	case SPL_DIAMOND_HARDNESS:
		text_ += "연금술의 힘으로 대지의 단단함을 몸에 두르는 기술.\n";
		text_ += "잠깐동안 약간의 방어력을 얻는다.\n";
		break;
	case SPL_POISON_SKIN:
		text_ += "자신의 몸에서 독기를 뿜어나오게 한다.\n";
		text_ += "방어적인 효과는 없지만 시전시간중에 근접한 모든 적에게 독을 건다.\n";
		break;
	case SPL_STONE_FORM:
		text_ += "잠시간 모든 고통에서 해방되는 무념무상의 상태가 된다.\n";
		text_ += "모든 데미지를 어느정도 반감하고 맨손 데미지가 강력해지지만 이동속도 또한 느려진다.\n";
		break;
	case SPL_KNIFE_COLLECT:
		text_ += "지속시간중에는 던진 탄막이 자동으로 회수하는 편리한 기술.\n";
		text_ += "명중 또한 소량 오른다.\n";
		break;
	case SPL_FLAN_BUSIN:
		text_ += "플랑드르의 분신을 3체 만들어내는 스펠.\n";
		text_ += "분신들은 본체보다 약하지만 폭파스펠을 똑같이 쓸 수 있다.\n";
		break;
	case SPL_BURST:
		text_ += "적을 원거리에서 터트려버린다. 저항할수도 회피할수도 없다.\n";
		break;
	case SPL_SUICIDE_BOMB:
		text_ += "공격할시 자동으로 자폭한다.\n";
		break;
	case SPL_RABBIT_HORN:
		text_ += "토끼가 큰 나팔을 이용하여 아군을 소집한다.\n";
		text_ += "사용직후 잠시동안 죽림의 몬스터 리젠율이 오른다.\n";
		break;
	case SPL_SUMMON_LESSOR_DEMON:
		text_ += "마계의 약한 마족을 소환한다.\n";
		break;
	case SPL_LUMINUS_STRIKE:
		text_ += "그레이즈 되지않는한 필중이며 빠르고 강력한 무속성 구체를 발사한다.\n";
		text_ += "일정 거리 이상의 적에게 명중시 작은 폭발이 일어나서 주변에 약한 광역데미지를 준다.\n";
		text_ += "그러나 거리가 멀어진다고 단일 타겟의 데미지는 증가하진않는다.\n";
		break;
	case SPL_FIRE_STORM:
		text_ += "선택한 위치에서 거대한 화염 폭풍이 일어난다.\n";
		text_ += "폭발한 범위 내에선 잠시간 화염구름이 남는다.\n";
		text_ += "절반 정도의 물리데미지가 있어서 화염저항이 높은 상대에도 잘 먹힌다.\n";
		break;
	case SPL_BLIZZARD: 
		text_ += "선택한 위치에서 강력한 얼음 가시가 떨어지도록 한다.\n";
		text_ += "순간 데미지는 낮지만 지속적으로 맞출 경우 엄청난 데미지를 주며 물리데미지도 겸비한다.\n";
		text_ += "사용시 해당 위치에 있는 모든 구름을 걷어낸다.\n";
		break;
	case SPL_PERFERT_FREEZE: 
		text_ += "화면상의 모든 적에게 강력한 냉기를 방출하는 마법.\n";
		text_ += "사용한 적들에게 강력한 빙결 상태이상을 부여한다.\n";
		text_ += "다만 순수 냉기 속성이므로 냉기저항이 있는 적에겐 데미지가 거의 안들어간다.\n";
		break;
	case SPL_DRAW_POWER:
		text_ += "시야내의 땅에 떨어져있는 모든 P템을 끌어모아서 P를 회복하는 마법.\n";
		text_ += "탑뷰방식에서 상단은 어디인가. 애초에 존재하긴 하는걸까?\n";
		break;
	case SPL_ANIMAL_CHANGE:
		text_ += "상대 한명을 영구히 동물로 만들어버리는 무서운 마법. 물론 동물에겐 쓸 수 없다.\n";
		text_ += "동물이 되면 강제로 자신의 동료가 된다. 또한 변신성공시 경험치도 그대로 받는다.\n";
		text_ += "동물이 된 동료는 영구적인 아군이지만 계단을 탈 수 없다.\n";
		text_ += "상대의 세기에 따라 더욱 강력한 동물로 변한다. 성공시키는건 어렵지만 성공시 효과는 탁월.\n";
		break;
	case SPL_FIELD_VIOLET:
		text_ += "파장을 조종하여 선택한 범위에 파이올렛 파장을 뿌린다.\n";
		text_ += "파장안에 든 모든 캐릭터는 적과 아군을 분간하지못하고 광기에 휩싸인다.\n";
		text_ += "이 상태로 죽은 적이라도 제대로 경험치를 받는다. 아군이나 플레이어도 광기에 휩싸일 수 있으니 조심.\n";
		break;
	case SPL_TIME_PARADOX: 				
		text_ += "탄막의 도플갱어를 만들어내서 2번 공격한다.\n";
		text_ += "사용후 패러독스 상태가 되면 딱 1번에 한해서 사용한 탄막 혹은 탄막마법이 2번 나간다.\n";
		text_ += "스파크나 화염폭풍같은 탄막이라고 보기 힘든 기술엔 적용되지 않는다.\n";
		text_ += "2번째 탄막은 탄막의 소모도 마나의 소모도 없으니 안심.\n";
		break;
	case SPL_PRIVATE_SQ: 
		text_ += "주변의 시간을 느리게하여 상대적인 가속효과를 얻는 마법.\n";
		text_ += "시야 내의 모든 적에게 슬로우를 건다. 저항할 수 있다.\n";
		break;
	case SPL_CONTROLED_BLINK: 
		text_ += "원하는 위치로 정밀하게 순간이동할 수 있는 시공마법의 꽃.\n";
		text_ += "사용후 높은 시공부작용을 받는다.\n";
		break;
	case SPL_THE_WORLD:
		text_ += "시공마법의 정점에 오른 자만이 쓸 수 있다는 궁극의 시공마법.\n";
		text_ += "잠시간 모든 시간을 멈추고 일방적으로 행동할 수 있다. 공격도 가능하다.\n";
		text_ += "어마어마한 시공부작용을 받는다. 연속으로 쓰는건 무리가 있다.\n";
		break;
	case SPL_HASTE_ALL:
		text_ += "시야 내의 아군들에게 가속을 전부 부여한다.\n";
		break;
	case SPL_HEAL_ALL:
		text_ += "시야 내의 아군들을 모두 회복시킨다.\n";
		break;
	case SPL_MOON_COMMUNICATION:
		text_ += "전파를 통신하여 아군 달토끼들을 불러모은다.\n";
		text_ += "사용중엔 움직일 수 없지만 천천히 아군들이 집결된다.\n";
		text_ += "소환된 몬스터가 아니기때문에 시전자가 죽어도 사라지지않는다.\n";
		break;
	case SPL_MOON_GUN:
		text_ += "달의 기술을 집결하여 만든 총을 쏜다.\n";
		text_ += "달의 하이테크치고는 겉모양은 별거 아닌거처럼 보인다.\n";
		text_ += "짜증나는 원시적 공격이로군!\n";
		break;
	case SPL_SUMMON_DREAM:
		text_ += "꿈을 구현화시켜 다양한 장소에서의 몬스터들을 소환하는 맥 특유의 기술.\n";
		text_ += "특정 장소에서 나오는 몬스터들이 한번에 여럿 소환된다.\n";
		break;
	case SPL_MANA_DRAIN:
		text_ += "악몽을 보여줘서 시야내의 적의 영력을 흡수하면서 데미지를 주는 스마이트형 공격.\n";
		text_ += "특이하게 지능이 낮으면 받는 데미지가 높아진다.\n";
		break;
	case SPL_INSANE:
		text_ += "대상을 미치게 만들어버린다. 저항하지 못한 상대는 광기에 빠진다.\n";
		text_ += "마법저항으로 저항할 수 있다.\n";
		break;
	case SPL_BLOOD_SMITE:
		text_ += "대상의 최대 체력에 비례한 저항불가능한 스마이트형 공격.\n";
		text_ += "최대체력이 높을수록 데미지가 커지고 데미지 반감이 되지 않으므로 전사에게도 위험하다.\n";
		break;
	case SPL_CALL_HOUND:
		text_ += "주변의 개들을 끌어모으는 울부짖음을 외친다.\n";
		text_ += "모인 개들도 다시 동료를 끌어 모을 수 있으니 되도록 빠르게 처리해야한다.\n";
		break;
	case SPL_CANNON:
		text_ += "거대한 대포알을 쏴서 폭발후 회피불가능한 데미지를 준다.\n";
		text_ += "방어력을 어느정도 관통한다.\n";
		break;
	case SPL_DOLLS_WAR:
		text_ += "근접과 공격에 강력한 상해인형과 원거리와 방어에 특화된 봉래인형을 같이 소환한다.\n";
		text_ += "상해인형은 빠르게 적을 공격하고 봉래인형은 적들의 어그로를 효과적으로 끌어모은다.\n";
		text_ += "공격뿐만 아니라 소환사가 취약한 소환술의 약점을 확실하게 보완하는 공방일체 소환술.\n";
		break;
	case SPL_FAKE_DOLLS_WAR:
		text_ += "상해인형이나 봉래인형을 소환한다.\n";
		text_ += "모조기때문에 원조의 인형보단 훨씬 약하다.\n";
		break;
	case SPL_FIRE_SPREAD:
		text_ += "전방에 부채꼴모양으로 화염의 구름을 흩뿌린다.\n";
		break;
	case SPL_STASIS:
		text_ += "대상의 전이를 방해한다. 일정시간 전이불가 디버프를 건다.\n";
		break;
	case SPL_JUMP_ATTACK:
		text_ += "거리가 떨어져있는 적에게 순식간에 접근한다.\n";
		break;
	case SPL_ALERT_NOISE: 
		text_ += "주변의 몬스터들을 깨우는 아주 큰 소음을 낸다.\n";
		break;
	case SPL_SUMMON_NAMAZ:
		text_ += "해당 위치에 거대한 나마즈를 낙하시킨다.\n";
		text_ += "낙하엔 일정시간이 걸리며 떨어진 위치에 큰 폭발이 일어난다.\n";
		break;
	default:
		text_ += "설명이 존재하지 않는 마법.\n";
		break;
	}
	
	if((SpellSchool(spell,0) == SKT_ALCHEMY || 
		SpellSchool(spell,1) == SKT_ALCHEMY ||
		SpellSchool(spell,2) == SKT_ALCHEMY)	
		&& SpellFlagCheck(spell, S_FLAG_BUF))
	{		
		text_ += "이 마법은 연금술 버프이다. 연금술 버프끼리는 중첩되지않는다.\n";
		text_ += "다른 연금술 버프가 걸린 상태에서 이 마법을 시전하면 기존의 연금술 버프가 사라진다.\n";
	}

	if(SpellFlagCheck(spell, S_FLAG_SUMMON))
	{		
		if(GetSummonMaxNumber(spell)>0)
		{
			char c_temp[128];
			sprintf_s(c_temp,128,"이 마법은 최대 %d마리까지 소환수를 소환할 수 있다.\n",GetSummonMaxNumber(spell));
			text_ += c_temp;
		}
	}
	text_ += "\n\n";

	text_ += '0'+SpellLevel(spell);
	text_ += "레벨     학파: ";
	text_ += GetSpellSchoolString(spell);
	return text_;
}

string GetSkillInfor(skill_list skill)
{
	string text_ = SkillString(skill);
	text_ += "\n\n";
	switch(skill)
	{	
	case SKL_NONE:
		text_ += "존재하지 않는 능력이다.\n";
		break;
	case SKL_KANAKO_1:
		text_ += "카나코님의 힘을 구현화하여 상대에게 순간적인 돌진을 할 수 있게된다.\n";
		text_ += "자신의 근접공격력, 신앙심과 거리에 비례해서 데미지가 들어가며\n";
		text_ += "사용후 이동속도가 느려지는 버프를 받게된다.\n";
		text_ += "이 버프중엔 건신초래돌을 추가적으로 사용할 수 없다.\n";
		break;
	case SKL_KANAKO_2:
		text_ += "카나코님의 기둥을 땅에 꽂는다.\n";
		text_ += "기둥은 캐릭터들의 이동을 막으며 신앙심에 비례한 체력을 가지게 된다.\n";
		text_ += "다만 기둥은 적이던 아군이건 원거리 공격을 맞지않고 통과시킨다.\n";
		text_ += "또한 신자는 이 기둥 옆에 있을때는 약간의 데미지증가 버프를 받게 된다.\n";
		text_ += "기둥은 한번에 여러개를 꽂을 수 있으나 버프는 중첩되지않는다.\n";
		break;
	case SKL_KANAKO_3:
		text_ += "카나코님의 바람을 구현화하여 무기에 휘감게 된다.\n";
		text_ += "이때 하는 공격은 바람의 힘을 받아 넓은 범위를 공격할 수 있게된다.\n";
		text_ += "근접 공격은 주변 8방향의 모든 적을 한번에 공격하고 원거리 공격은 모든 적을 관통하게된다.\n";
		text_ += "신앙심에 비례하여 지속시간이 늘어나며 공격력은 늘어나지 않는다.\n";
		break;
	case SKL_GRAZE:
		text_ += "그레이즈 상태가 된다. 그레이즈 상태에선 모든 원거리 탄막을 회피할 확률이 생긴다.\n";
		text_ += "틱틱틱 소리는 미지원이다.\n";
		break;
	case SKL_GRAZE_OFF:
		text_ += "그레이즈 상태를 없앤다.\n";
		break;
	case SKL_LEVITATION:
		text_ += "일시적인 비행 상태가 된다. 깊은물같은 지형을 통과할 수 있게 된다.\n";
		break;
	case SKL_LEVITATION_OFF:
		text_ += "비행 상태를 없앤다.\n";
		break;
	case SKL_INVISIBLE:
		text_ += "일시적 투명화할 수 있는 능력. 투명상태에서는 상대에게 들킬 확률이 현저히 줄어든다.\n";
		text_ += "이미 밀착해있으면 낌새를 눈치채서 따라올 수 있으며 투명을 보는 상대도 존재한다.\n";
		text_ += "또 투명상태에서는 P의 소모가 매우 빨라지니 주의해야한다.\n";
		break;
	case SKL_INVISIBLE_OFF:
		text_ += "투명 상태를 없앤다.\n";
		break;
	case SKL_EIRIN_0:
		text_ += "당신은 가지고 있는 물약을 던질 수 있다.\n";
		text_ += "던진 위치엔 3*3크기로 구름이 생성된다. 구름의 종류는 물약의 종류에따라 정해진다.\n";
		text_ += "이로운 물약은 던져도 연기구름만 생긴다. 해로운 물약을 던져야 강력한 구름이 나온다.\n";
		break;
	case SKL_EIRIN_1:
		text_ += "에이린에게 몸을 맡겨 원하는대로 몸을 개조한다.\n";
		text_ += "원하는 스탯을 선택하면 그 외의 스탯이 모두 원하는 스탯으로 반영구적으로 옮겨진다.\n";
		text_ += "옮겨지는 수치는 신앙심에 따라 2~5로 유동적으로 변하며 언제라도 다시 스탯을 옮길 수 있다.\n";
		text_ += "중첩은 되지않는다. 한번 스탯을 선택하면 다시 개조하기전엔 계속 효과가 이어진다.\n";
		break;
	case SKL_EIRIN_2:
		text_ += "높은 신앙심과 파워1칸을 소모하여 순간적으로 체력을 대부분 채워주는 에이린의 궁극 권능.\n";
		text_ += "효과는 강력하지만 사용후 일정시간이 지나면 회복한 수치만큼 그대로 부작용 데미지를 받게된다.\n";
		break;
	case SKL_BYAKUREN_1:
		text_ += "일시적으로 지능을 강화시키는 뱌쿠렌의 신체강화마법.\n";
		text_ += "지능이 5증가하고 마법성공률, 파워가 증가하며 마나 회복속도도 증가한다.\n";
		break;
	case SKL_BYAKUREN_2:
		text_ += "일시적으로 각력을 강화시키는 뱌쿠렌의 신체강화마법. (W)\n";
		text_ += "이동속도가 매우 매우 빨라진다. 신속과 중첩되지 않으며 지속시간은 짧은 편이다.\n";
		text_ += "가히 초인이라 부를만 하군!\n";
		break;
	case SKL_SIZUHA_1:
		text_ += "단풍의 위에 서있는 적들에게 광기를 불어넣는다.\n";
		text_ += "단풍 위에 있는 적들에게 마법저항을 비교하여 혼란을 전부 건다.\n";
		break;
	case SKL_SIZUHA_2:
		text_ += "당신이 끼고 있는 아티펙트가 아닌 몸통 방어구를 단풍 방어구로 바꾼다.\n";
		text_ += "단풍방어구는 시즈하를 믿고있는동안 당신의 은밀을 크게 올려준다.\n";
		text_ += "단, 옷의 종류가 단풍옷으로 바꿔져서 기존의 저항력은 사라진다.\n";
		text_ += "이 단풍방어구는 한번 바꾸면 기존의 방어구로는 되돌릴 수 없다.\n";
		break;		
	case SKL_SIZUHA_3:
		text_ += "당신이 들고있는 무기에 영구적으로 단풍브랜드와 +1~2의 인챈트를 부여한다.\n";
		text_ += "단풍브랜드가 붙은 무기는 단검이 아니라도 커다란 암습데미지를 줄 수 있고\n";
		text_ += "단검인 경우엔 평범한 공격에도 암습의 확률을 준다.\n";
		break;		
	case SKL_MINORIKO_1:
		text_ += "당신에게 걸려있는 나쁜 디버프와 능력치 저하를 회복한다.\n";
		text_ += "즉시 회복되나 사용에는 신앙심과 적은양의 P를 소모한다.\n";
		break;		
	case SKL_MINORIKO_2:
		text_ += "당신이 들고 있는 음식을 소모하여 체력을 크게 회복한다.\n";
		text_ += "높은 신앙과 마나는 물론 또한 P도 1칸을 소모하는 고비용의 권능이다.\n";
		text_ += "만복도를 많이 회복하는 음식이 체력회복량도 조금 더 많다.\n";
		break;
	case SKL_YUUGI_1:
		text_ += "당신이 가지고있는 물약 1개를 소모하여 취기를 얻는다.\n";
		text_ += "원래 물약의 성능은 얻지못한다.\n";
		break;		
	case SKL_YUUGI_2:
		text_ += "밀착한 상대를 잡아 저먼 스플렉스를 건다.\n";
		text_ += "상당한 데미지를 주면서 위치를 바꿀 수 있다.\n";
		text_ += "만약 잡고있는 상태라면 해당 상대에겐 신앙심 소모없이 기술을 사용할 수 있다.\n";
		break;		
	case SKL_YUUGI_3:
		text_ += "밀착한 상대를 들어올려 멀리 던져버린다.\n";
		text_ += "던진 위치엔 큰 충격파가 일어나 날라간 상대 주위로 범위 데미지를 준다.\n";
		text_ += "너무 가까이 던지면 던진 플레이어도 데미지를 입을 수 있다.\n";
		text_ += "만약 잡고있는 상태라면 해당 상대에겐 신앙심 소모없이 기술을 사용할 수 있다.\n";
		break;		
	case SKL_YUUGI_4:
		text_ += "오니의 힘을 빌어 굉장한 소리로 포효한다.\n";
		text_ += "시야내의 적들은 일정 확률로 포효에 기가 죽어 벙어리 상태가 된다.\n";
		text_ += "벙어리 상태가 된 적은 당분간 마법을 사용할 수 없다.\n";
		text_ += "만약 잡고있는 상태라면 해당 상대에겐 무조건 벙어리 상태로 만든다.\n";
		break;		
	case SKL_YUUGI_5:
		text_ += "오니의 궁극기인 삼보필살을 사용한다. 3턴간 3번의 폭발이 순차적으로 일어난다.\n";
		text_ += "폭발 범위는 점차 커져서 거의 시야 전체를 커버한다.\n";
		text_ += "만약 잡고있는 상태라면 해당 상대에겐 보통의 2배 데미지를 입힌다.\n";
		break;	
	case SKL_SATORI_1:
		text_ += "상대의 트라우마를 일깨운다.\n";
		text_ += "성공하면 상대는 공포 상태가 되어 이쪽으로부터 도망치기 시작한다.\n";
		break;		
	case SKL_SATORI_2:	
		text_ += "상대의 마음을 읽어낸다. 사용한 상대의 모든 생각을 읽게 된다.\n";
		text_ += "만약 대상이 동물형인경우 호감을 사서 영구적인 아군이 된다. 그러나 계단이용은 불가능해진다.\n";
		text_ += "동물형이 아닌 경우엔 명중과 회피가 매우 큰 폭으로 떨어지며 디버프에 대한 저항력이 사라진다.\n";
		text_ += "사용할때 적의 마법저항력에 비례해서 시전 턴수가 필요하며 그동안 아무행동도 할 수 없다.\n";
		text_ += "시간동안 시야에서 사라지거나 혼란,마비가 걸리면 실패하고 자신의 레벨이 올라갈수록 턴수는 줄어든다.\n";
		break;	
	case SKL_SHINKI_1:
		text_ += "하급 마족들의 작은 무리를 소환한다.\n";
		text_ += "하급 마족들은 전투엔 별다른 도움은 안되겠지만 신앙심소모가 매우 적고 양으로 승부할 수 있다.\n";
		break;
	case SKL_SHINKI_2:
		text_ += "중급 마족 1명을 무작위로 소환한다.\n";
		text_ += "사라, 루이즈, 엘리스중에 무작위로 소환되어 당신을 도와준다.\n";
		text_ += "4%의 확률로 당신을 배신할 수 있다.\n";
		break;
	case SKL_SHINKI_3:	
		text_ += "상급 마족 1명을 무작위로 소환한다.\n";
		text_ += "유키, 마이, 유겐마간중에 무작위로 소환되어 당신을 도와준다.\n";
		text_ += "4%의 확률로 당신을 배신할 수 있다.\n";
		break;
	case SKL_YUYUKO_ON:	
		text_ += "유령의 소환을 시작한다.\n";
		text_ += "유령의 소환에는 비용이 들지않으며 한번 발동해두면 끝없이 유령을 불러들인다.\n";
		break;
	case SKL_YUYUKO_OFF:	
		text_ += "유령의 소환을 종료한다.\n";
		text_ += "언제든지 원할때 다시 유령을 불러들일 수 있다.\n";
		break;
	case SKL_YUYUKO_1:
		text_ += "유령을 원하는 위치로 이동시킬 수 있다.\n";
		text_ += "지정한 위치로 주변에 있는 유령들이 한꺼번에 이동된다.\n";
		break;
	case SKL_YUYUKO_2:
		text_ += "유령의 소환을 잠시간 가속한다.\n";
		text_ += "일정시간동안 어마어마한 속도로 유령의 수가 불어난다.\n";
		break;
	case SKL_YUYUKO_3:
		text_ += "1명의 영혼을 구속시켜서 자신의 노예로 삼는다.\n";
		text_ += "영혼이 구속된 상대를 일정시간 내에 잡으면 영구적인 아군으로 삼을 수 있다.\n";
		text_ += "구속된 영혼은 원본보다는 약해지지만 원본이 쓰는 마법이나 특징을 그대로 가지고 있다.\n";
		text_ += "또한 구속된 영혼은 1체까지 밖에 들고다닐 수 없다. 2번째 대상을 포획하면 원래가지고있던 영혼이 풀려난다.\n";
		break;
	case SKL_YUKARI_1:
		text_ += "시야내의 원하는 틈새로부터 지원사격을 요청한다.\n";
		text_ += "틈새로부터 적을 응시하는 이형의 눈이 나타나 적을 공격한다.\n";
		text_ += "이형의 눈은 낮은 체력을 가지고 있으므로 주의.\n";
		break;
	case SKL_YUKARI_2:
		text_ += "시야내의 원하는 틈새로 공간이동을 할 수 있다. 한번 사용한 틈새는 닫힌다.\n";
		text_ += "영력과 신앙심을 제외한 별다른 디메리트 없이 순식간에 이동이 가능하다.\n";
		break;
	case SKL_YUKARI_3:
		text_ += "공격을 막아주는 결계를 잠시동안 소환한다.\n";
		text_ += "결계를 사용하면 방패처럼 사용할 수 있으며 방패를 장착하고있어도 성능을 상승시킨다.\n";
		text_ += "결계로 만들어진 방패는 마법패널티등을 받지 않는다.\n";
		break;
	case SKL_YUKARI_4:
		text_ += "유카리가 경계를 건드려서 일정턴동안 선택한 위치를 중심으로 화면이 그대로 고정된다.\n";
		text_ += "고정된 상태의 지형은 시야가 이동되지않으며 상하좌우가 루프된다.\n";
		text_ += "또한 고정된 지형에 들어오지않은 적들은 차원고정이 끝나기전에 움직일 수 없다.\n";
		text_ += "계단을 타게되면 차원 고정은 풀린다.\n";
		break;
	case SKL_SWAKO_JUMP:
		text_ += "2칸의 짧은 거리를 한번에 이동할 수 있다.\n";
		text_ += "효과는 적지만 영력소모가 적고 연속으로 쓸 수 있다.\n";
		text_ += "비행이나 수영이 가능해도 물가로는 점프할 수 없다.\n";
		break;
	case SKL_SWAKO_TEMPLE:
		text_ += "현재 서있는 위치에 스와코님의 신전을 세울 수 있다.\n";
		text_ += "사용시 큰 파워가 소모되지만 신앙심을 얻을 수 있다.\n";
		break;
	case SKL_SWAKO_WATER_GUN:
		text_ += "원거리의 적에게 물총을 쏠 수 있다.\n";
		text_ += "위력은 낮지만 큰 비용없이 연사할 수 있는 것이 장점이다.\n";
		break;
	case SKL_SWAKO_TOUGUE:
		text_ += "원거리의 적에게 커다란 혀를 이용하여 근처로 끌고 온다.\n";
		text_ += "사격형식으로 나가므로 사이에 막혀있다면 맞출 수 없다.\n";
		break;
	case SKL_SWAKO_CURSE:
		text_ += "적 하나에 재앙을 내려서 독과 감속효과를 건다.\n";
		text_ += "독저항이 있어도 마법저항이 높아도 상관없이 걸 수 있지만\n";
		text_ += "적이 나보다 강력할수록 감속 시간은 짧아진다.\n";
		break;
	case SKL_SWAKO_DIGGING:
		text_ += "사거리안의 일직선상에 있는 모든 벽을 굴착한다.\n";
		text_ += "사용시 생각보다 큰 소음이 난다.\n";
		break;
	case SKL_SWAKO_SUMMON_FLOG:
		text_ += "잠시동안 아군의 개구리를 소환한다.\n";
		text_ += "신도의 레벨에 비례해서 강력한 개구리가 나온다.\n";
		break;
	case SKL_SWAKO_STATUE:
		text_ += "잠시동안 개구리 석상을 위치에 소환한다.\n";
		text_ += "석상은 유리 벽과 같아서 시야는 통하지만 이동과 사격을 모두 막을 수 있다.\n";
		text_ += "일정 시간이 지나면 사라진다.\n";
		break;
	case SKL_SWAKO_RAIN:
		text_ += "주변에 거대한 물웅덩이를 만든다.\n";
		text_ += "깊은 물은 날거나 수영할 수 없는 적의 이동을 막는다.\n";
		text_ += "추가로 아군 개구리를 여럿 소환한다.\n";
		text_ += "자신이 날 수 없거나 수영할 수 없으면 자신도 움직일 수 없게 된다.\n";
		break;
	case SKL_SWAKO_SLEEP:
		text_ += "잠시동안 땅속에 박혀서 모든 공격으로부터 무적이 되고 체력과 영력을 회복한다.\n";
		text_ += "또한 턴동안 주변의 적들이 플레이어를 놓치고 이리저리 이동하게 된다.\n";
		text_ += "일정 시간이 지나면 잠에서 깨지만 그 반작용으로 짧은 감속에 걸린다.\n";
		break;
	case SKL_SWAKO_MISYAGUZI:
		text_ += "강력한 미샤구지님을 잠시동안 소환한다.\n";
		break;
	case SKL_HINA_1:
		text_ += "저주가 걸려있는 장비의 마이너스 인챈트를 플러스로 바꾼다.\n";
		text_ += "P의 소모를 제외한 별다른 비용은 들지 않는다.\n";
		break;
	case SKL_HINA_2:
		text_ += "현재 들고있는 무기에 저주를 걸면서 일시적으로 저주 브랜드가 부여된다.\n";
		text_ += "저주브랜드가 붙은 무기는 저항이 불가능한 독데미지를 적에게 줄 수 있고\n";
		text_ += "일정 확률로 감속 효과를 준다. 브랜드가 걸려있거나 걸 수 없으면 힘이 강화된다.\n";
		text_ += "들고있는 무기에 이미 저주가 걸려있으면 사용할 수 없다.\n";
		break;
	case SKL_HINA_3:
		text_ += "현재 장착하고 있는 방어구에 저주를 걸면서 일시적으로 모든 데미지를 반사한다.\n";
		text_ += "몸통 방어구에 저주를 걸때는 더욱 더 긴 지속시간을 가진다.\n";
		text_ += "장착하고 있는 방어구에 이미 저주가 걸려있으면 사용할 수 없다.\n";
		break;
	case SKL_HINA_4:
		text_ += "현재 장착하고 있는 장신구에 저주를 걸면서 체력과 영력을 회복한다.\n";
		text_ += "장착하고 있는 장신구에 이미 저주가 걸려있으면 사용할 수 없다.\n";
		break;
	case SKL_HINA_5:
		text_ += "당신이 들고있는 무기에 영구적으로 저주브랜드와 +1~2의 인챈트를 부여한다.\n";
		text_ += "저주브랜드가 붙은 무기는 저항이 불가능한 독데미지를 적에게 줄 수 있고\n";
		text_ += "일정 확률로 감속 효과를 준다.\n";
		break;		
	case SKL_JUMPING_ATTACK: 
		text_ += "사거리 안에 든 목표 주변 8타일로 순식간에 접근하며 공격한다.\n";
		text_ += "단, 밀착한 대상으론 쓸 수 없다.\n";
		text_ += "사용후 일정시간 피로가 쌓여서 연속 사용은 안된다.\n";
		break;
	case SKL_BREATH:
		text_ += "발현된 용의 속성에 맞는 브레스를 일직선으로 발사한다.\n";
		text_ += "사용후 일정시간 피로가 쌓여서 연속 사용은 안된다.\n";
		break;
	case SKL_TORMENT:
		text_ += "시야내의 있는 적들의 체력을 절반으로 만들어버리는 무서운 기술.\n";
		text_ += "당신이 악마의 피를 이어받고있기때문에, 당신은 이 피해로부터 면역이다.\n";
		break;
	default:
		text_ += "모르는 능력.\n";
		break;
	}
	return text_;
}



string GetSpellSchoolString(spell_list spell)
{
	string str_;
	int k=0;
	char temp[50];
	for(int i=0;i<3 && SpellSchool(spell,i) != SKT_ERROR;i++)
	{
		if(i)
		{
			k+=sprintf_s(temp+k,50-k,"/");
		}
		k+=sprintf_s(temp+k,50-k,"%s",skill_string(SpellSchool(spell,i)));
	}
	str_ = temp;
	return temp;
}