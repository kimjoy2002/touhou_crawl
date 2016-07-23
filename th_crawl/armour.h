//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: armour.h
//
// ³»¿ë: °©¿Ê
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

struct item_infor;


using namespace std;

enum armour_kind
{
	AMK_NORMAL, //Æò»ó¿Ê
	AMK_MIKO, //¹«³à¿Ê (È¥¶õÀúÇ×)
	AMK_WING, //³¯°³¿Ê (Àü±âÀúÇ×)
	AMK_KAPPA, //Ä±ÆÄ¿Ê (³Ã±âÀúÇ×)
	AMK_FIRE, //ºÒÁãÀÇ¿Ê (È­¿°ÀúÇ×)
	AMK_MAID, //¸ŞÀÌµå¿Ê (¸¶¹ıÀúÇ×)
	AMK_POISON, //ÀÎÇü¿Ê(µ¶ÀúÇ×)
	AMK_AUTUMN, //´ÜÇ³¿Ê(Å« Àº¹Ğ)
	AMK_MAX
};


enum material_kind
{
	MTK_ROBE,
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

