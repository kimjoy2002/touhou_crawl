//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: armour.h
//
// 내용: 갑옷
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

struct item_infor;


using namespace std;

enum armour_kind
{
	AMK_NORMAL, //평상옷
	AMK_MIKO, //무녀옷 (혼란저항)
	AMK_WING, //날개옷 (전기저항)
	AMK_KAPPA, //캇파옷 (냉기저항)
	AMK_FIRE, //불쥐의옷 (화염저항)
	AMK_MAID, //메이드옷 (마법저항)
	AMK_POISON, //인형옷(독저항)
	AMK_AUTUMN, //단풍옷(큰 은밀)
	AMK_MAX
};


enum material_kind
{
	MTK_ROBE=0,
	MTK_LEATHER,
	MTK_CHAIN,
	MTK_PLATE,
	MTK_MAX
};



enum armour_value
{
	AMV_AC,
	AMV_MAX_EV,
	AMV_MIN_EV
};

string GetMaterialString(material_kind kind_);
void MakeBaseArmour(armour_kind type, material_kind material, item_infor* t);
void MakeArmourEnchant(int good_bad, item_infor* t);
int ArmourExceptopn(armour_kind type);
void equipArmour(armour_kind type, int value);

armour_kind GetRandomArmourType(int good_bad);
int GetMaterial(material_kind kind, armour_value value_);

