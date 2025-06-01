//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: texture.cpp
//
// 내용: texture클래스 정의 및 텍스쳐객체
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"
#include "textureUtility.h"
#include "monster_texture.h"
#include "texture.h"
#include "Fliename.h"
#include <WICTextureLoader.h>
#include <sys/stat.h>

#include "option_manager.h"
#include "enum.h"
#define COLOR_NUM 5
#define STYLE_NUM 11


const char *imgfile_title[MAX_TITLE] = 
{
	"./data/title.png",
	"./data/title2.png",
	//"./data/title_0.png",
	//"./data/title_1.png",
	"./data/title_3.png",
	"./data/title_4.png",
	"./data/title_5.png",
	"./data/title_6.png",
	"./data/title_7.png"
};

const char *imgfile_god[GT_LAST] =
{
	"./data/god/joon_and_sion.png",//GT_JOON_SION = GT_FIRST,
	"./data/god/byakuren.png",//GT_BYAKUREN,
	"./data/god/kanako.png",//GT_KANAKO,
	"./data/god/suwako.png",//GT_SUWAKO,
	"./data/god/minoriko.png",//GT_MINORIKO,

	"./data/god/mima.png",//GT_MIMA,
	"./data/god/shinki.png",//GT_SHINKI,
	"./data/god/yuugi.png",//GT_YUUGI,
	"./data/god/shizuha.png",//GT_SHIZUHA,
	"./data/god/hina.png",//GT_HINA,

	"./data/god/yukari.png",//GT_YUKARI,
	"./data/god/eirin.png",//GT_EIRIN,
	"./data/god/yuyuko.png",//GT_YUYUKO,
	"./data/god/satori.png",//GT_SATORI,
	"./data/god/tensi.png",//GT_TENSI,

	"./data/god/seija.png",//GT_SEIJA,
	"./data/god/lilly.png",//GT_LILLY,
	"./data/god/miko.png",//GT_MIKO,
	"./data/god/okina.png",//GT_OKINA,
	"./data/god/junko.png",//GT_JUNKO
};






TextureFile texture_dungeon01(imgfile_dungeon01);
TextureFile texture_dungeon02(imgfile_dungeon02);
TextureFile texture_monster01(imgfile_monster01);
TextureFile texture_monster02(imgfile_monster02);
TextureFile texture_players01(imgfile_players01);
TextureFile texture_item01(imgfile_item01);
TextureFile texture_item02(imgfile_item02);
TextureFile texture_item03(imgfile_item03);
TextureFile texture_laser(imgfile_laser);
TextureFile texture_dot_floor(imgfile_dot_floor);
TextureFile texture_dot_wall(imgfile_dot_wall);
TextureFile texture_dot_monster(imgfile_dot_monster);
TextureFile texture_dot_player(imgfile_dot_player);
TextureFile texture_dot_up(imgfile_dot_up);
TextureFile texture_dot_down(imgfile_dot_down);
TextureFile texture_dot_item(imgfile_dot_item);
TextureFile texture_dot_door(imgfile_dot_door);
TextureFile texture_dot_temple(imgfile_dot_temple);
TextureFile texture_dot_sea(imgfile_dot_sea);
TextureFile texture_dot_mapping_floor(imgfile_dot_mapping_floor);
TextureFile texture_dot_mapping_wall(imgfile_dot_mapping_wall);

TextureFile texture_sight_rect(imgfile_sight_rect);


TextureFile texture_title(imgfile_title[0]);

TextureFile texture_god[GT_LAST]
{ 
TextureFile(imgfile_god[0]),
TextureFile(imgfile_god[1]),
TextureFile(imgfile_god[2]),
TextureFile(imgfile_god[3]),
TextureFile(imgfile_god[4]),
TextureFile(imgfile_god[5]),
TextureFile(imgfile_god[6]),
TextureFile(imgfile_god[7]),
TextureFile(imgfile_god[8]),
TextureFile(imgfile_god[9]),
TextureFile(imgfile_god[10]),
TextureFile(imgfile_god[11]),
TextureFile(imgfile_god[12]),
TextureFile(imgfile_god[13]),
TextureFile(imgfile_god[14]),
TextureFile(imgfile_god[15]),
TextureFile(imgfile_god[16]),
TextureFile(imgfile_god[17]),
TextureFile(imgfile_god[18]),
TextureFile(imgfile_god[19])
};


textures img_title(&texture_title, 0, 0, 512, 512, 255);


textures img_god_background[GT_LAST]=
{
textures(&texture_god[0], 0, 0, 512, 512, 255),
textures(&texture_god[1], 0, 0, 512, 512, 255),
textures(&texture_god[2], 0, 0, 512, 512, 255),
textures(&texture_god[3], 0, 0, 512, 512, 255),
textures(&texture_god[4], 0, 0, 512, 512, 255),
textures(&texture_god[5], 0, 0, 512, 512, 255),
textures(&texture_god[6], 0, 0, 512, 512, 255),
textures(&texture_god[7], 0, 0, 512, 512, 255),
textures(&texture_god[8], 0, 0, 512, 512, 255),
textures(&texture_god[9], 0, 0, 512, 512, 255),
textures(&texture_god[10], 0, 0, 512, 512, 255),
textures(&texture_god[11], 0, 0, 512, 512, 255),
textures(&texture_god[12], 0, 0, 512, 512, 255),
textures(&texture_god[13], 0, 0, 512, 512, 255),
textures(&texture_god[14], 0, 0, 512, 512, 255),
textures(&texture_god[15], 0, 0, 512, 512, 255),
textures(&texture_god[16], 0, 0, 512, 512, 255),
textures(&texture_god[17], 0, 0, 512, 512, 255),
textures(&texture_god[18], 0, 0, 512, 512, 255),
textures(&texture_god[19], 0, 0, 512, 512, 255)
};



textures img_auto_wall[48] = {
	textures(&texture_dungeon01, 32),
	textures(&texture_dungeon01, 33),
	textures(&texture_dungeon01, 34),
	textures(&texture_dungeon01, 35),
	textures(&texture_dungeon01, 36),
	textures(&texture_dungeon01, 37),
	textures(&texture_dungeon01, 38),
	textures(&texture_dungeon01, 39),
	textures(&texture_dungeon01, 40),
	textures(&texture_dungeon01, 41),
	textures(&texture_dungeon01, 42),
	textures(&texture_dungeon01, 43),
	textures(&texture_dungeon01, 44),
	textures(&texture_dungeon01, 45),
	textures(&texture_dungeon01, 46),
	textures(&texture_dungeon01, 47),
	textures(&texture_dungeon01, 48),
	textures(&texture_dungeon01, 49),
	textures(&texture_dungeon01, 50),
	textures(&texture_dungeon01, 51),
	textures(&texture_dungeon01, 52),
	textures(&texture_dungeon01, 53),
	textures(&texture_dungeon01, 54),
	textures(&texture_dungeon01, 55),
	textures(&texture_dungeon01, 56),
	textures(&texture_dungeon01, 57),
	textures(&texture_dungeon01, 58),
	textures(&texture_dungeon01, 59),
	textures(&texture_dungeon01, 60),
	textures(&texture_dungeon01, 61),
	textures(&texture_dungeon01, 62),
	textures(&texture_dungeon01, 63),
	textures(&texture_dungeon01, 64),
	textures(&texture_dungeon01, 65),
	textures(&texture_dungeon01, 66),
	textures(&texture_dungeon01, 67),
	textures(&texture_dungeon01, 68),
	textures(&texture_dungeon01, 69),
	textures(&texture_dungeon01, 70),
	textures(&texture_dungeon01, 71),
	textures(&texture_dungeon01, 72),
	textures(&texture_dungeon01, 73),
	textures(&texture_dungeon01, 74),
	textures(&texture_dungeon01, 75),
	textures(&texture_dungeon01, 76),
	textures(&texture_dungeon01, 77),
	textures(&texture_dungeon01, 78),
	textures(&texture_dungeon01, 79)
};

textures img_auto_metal_wall[48] = {
	textures(&texture_dungeon01, 80),
	textures(&texture_dungeon01, 81),
	textures(&texture_dungeon01, 82),
	textures(&texture_dungeon01, 83),
	textures(&texture_dungeon01, 84),
	textures(&texture_dungeon01, 85),
	textures(&texture_dungeon01, 86),
	textures(&texture_dungeon01, 87),
	textures(&texture_dungeon01, 88),
	textures(&texture_dungeon01, 89),
	textures(&texture_dungeon01, 90),
	textures(&texture_dungeon01, 91),
	textures(&texture_dungeon01, 92),
	textures(&texture_dungeon01, 93),
	textures(&texture_dungeon01, 94),
	textures(&texture_dungeon01, 95),
	textures(&texture_dungeon01, 96),
	textures(&texture_dungeon01, 97),
	textures(&texture_dungeon01, 98),
	textures(&texture_dungeon01, 99),
	textures(&texture_dungeon01, 100),
	textures(&texture_dungeon01, 101),
	textures(&texture_dungeon01, 102),
	textures(&texture_dungeon01, 103),
	textures(&texture_dungeon01, 104),
	textures(&texture_dungeon01, 105),
	textures(&texture_dungeon01, 106),
	textures(&texture_dungeon01, 107),
	textures(&texture_dungeon01, 108),
	textures(&texture_dungeon01, 109),
	textures(&texture_dungeon01, 110),
	textures(&texture_dungeon01, 111),
	textures(&texture_dungeon01, 112),
	textures(&texture_dungeon01, 113),
	textures(&texture_dungeon01, 114),
	textures(&texture_dungeon01, 115),
	textures(&texture_dungeon01, 116),
	textures(&texture_dungeon01, 117),
	textures(&texture_dungeon01, 118),
	textures(&texture_dungeon01, 119),
	textures(&texture_dungeon01, 120),
	textures(&texture_dungeon01, 121),
	textures(&texture_dungeon01, 122),
	textures(&texture_dungeon01, 123),
	textures(&texture_dungeon01, 124),
	textures(&texture_dungeon01, 125),
	textures(&texture_dungeon01, 126),
	textures(&texture_dungeon01, 127)
};

textures img_auto_mountain_wall[48] = {
	textures(&texture_dungeon01, 128),
	textures(&texture_dungeon01, 129),
	textures(&texture_dungeon01, 130),
	textures(&texture_dungeon01, 131),
	textures(&texture_dungeon01, 132),
	textures(&texture_dungeon01, 133),
	textures(&texture_dungeon01, 134),
	textures(&texture_dungeon01, 135),
	textures(&texture_dungeon01, 136),
	textures(&texture_dungeon01, 137),
	textures(&texture_dungeon01, 138),
	textures(&texture_dungeon01, 139),
	textures(&texture_dungeon01, 140),
	textures(&texture_dungeon01, 141),
	textures(&texture_dungeon01, 142),
	textures(&texture_dungeon01, 143),
	textures(&texture_dungeon01, 144),
	textures(&texture_dungeon01, 145),
	textures(&texture_dungeon01, 146),
	textures(&texture_dungeon01, 147),
	textures(&texture_dungeon01, 148),
	textures(&texture_dungeon01, 149),
	textures(&texture_dungeon01, 150),
	textures(&texture_dungeon01, 151),
	textures(&texture_dungeon01, 152),
	textures(&texture_dungeon01, 153),
	textures(&texture_dungeon01, 154),
	textures(&texture_dungeon01, 155),
	textures(&texture_dungeon01, 156),
	textures(&texture_dungeon01, 157),
	textures(&texture_dungeon01, 158),
	textures(&texture_dungeon01, 159),
	textures(&texture_dungeon01, 160),
	textures(&texture_dungeon01, 161),
	textures(&texture_dungeon01, 162),
	textures(&texture_dungeon01, 163),
	textures(&texture_dungeon01, 164),
	textures(&texture_dungeon01, 165),
	textures(&texture_dungeon01, 166),
	textures(&texture_dungeon01, 167),
	textures(&texture_dungeon01, 168),
	textures(&texture_dungeon01, 169),
	textures(&texture_dungeon01, 170),
	textures(&texture_dungeon01, 171),
	textures(&texture_dungeon01, 172),
	textures(&texture_dungeon01, 173),
	textures(&texture_dungeon01, 174),
	textures(&texture_dungeon01, 175),
};
textures img_auto_red_wall[48] = {
	textures(&texture_dungeon01, 176),
	textures(&texture_dungeon01, 177),
	textures(&texture_dungeon01, 178),
	textures(&texture_dungeon01, 179),
	textures(&texture_dungeon01, 180),
	textures(&texture_dungeon01, 181),
	textures(&texture_dungeon01, 182),
	textures(&texture_dungeon01, 183),
	textures(&texture_dungeon01, 184),
	textures(&texture_dungeon01, 185),
	textures(&texture_dungeon01, 186),
	textures(&texture_dungeon01, 187),
	textures(&texture_dungeon01, 188),
	textures(&texture_dungeon01, 189),
	textures(&texture_dungeon01, 190),
	textures(&texture_dungeon01, 191),
	textures(&texture_dungeon01, 192),
	textures(&texture_dungeon01, 193),
	textures(&texture_dungeon01, 194),
	textures(&texture_dungeon01, 195),
	textures(&texture_dungeon01, 196),
	textures(&texture_dungeon01, 197),
	textures(&texture_dungeon01, 198),
	textures(&texture_dungeon01, 199),
	textures(&texture_dungeon01, 200),
	textures(&texture_dungeon01, 201),
	textures(&texture_dungeon01, 202),
	textures(&texture_dungeon01, 203),
	textures(&texture_dungeon01, 204),
	textures(&texture_dungeon01, 205),
	textures(&texture_dungeon01, 206),
	textures(&texture_dungeon01, 207),
	textures(&texture_dungeon01, 208),
	textures(&texture_dungeon01, 209),
	textures(&texture_dungeon01, 210),
	textures(&texture_dungeon01, 211),
	textures(&texture_dungeon01, 212),
	textures(&texture_dungeon01, 213),
	textures(&texture_dungeon01, 214),
	textures(&texture_dungeon01, 215),
	textures(&texture_dungeon01, 216),
	textures(&texture_dungeon01, 217),
	textures(&texture_dungeon01, 218),
	textures(&texture_dungeon01, 219),
	textures(&texture_dungeon01, 220),
	textures(&texture_dungeon01, 221),
	textures(&texture_dungeon01, 222),
	textures(&texture_dungeon01, 223),
};
textures img_auto_water[48] = {
	textures(&texture_dungeon01, 224),
	textures(&texture_dungeon01, 225),
	textures(&texture_dungeon01, 226),
	textures(&texture_dungeon01, 227),
	textures(&texture_dungeon01, 228),
	textures(&texture_dungeon01, 229),
	textures(&texture_dungeon01, 230),
	textures(&texture_dungeon01, 231),
	textures(&texture_dungeon01, 232),
	textures(&texture_dungeon01, 233),
	textures(&texture_dungeon01, 234),
	textures(&texture_dungeon01, 235),
	textures(&texture_dungeon01, 236),
	textures(&texture_dungeon01, 237),
	textures(&texture_dungeon01, 238),
	textures(&texture_dungeon01, 239),
	textures(&texture_dungeon01, 240),
	textures(&texture_dungeon01, 241),
	textures(&texture_dungeon01, 242),
	textures(&texture_dungeon01, 243),
	textures(&texture_dungeon01, 244),
	textures(&texture_dungeon01, 245),
	textures(&texture_dungeon01, 246),
	textures(&texture_dungeon01, 247),
	textures(&texture_dungeon01, 248),
	textures(&texture_dungeon01, 249),
	textures(&texture_dungeon01, 250),
	textures(&texture_dungeon01, 251),
	textures(&texture_dungeon01, 252),
	textures(&texture_dungeon01, 253),
	textures(&texture_dungeon01, 254),
	textures(&texture_dungeon01, 255),
	textures(&texture_dungeon01, 256),
	textures(&texture_dungeon01, 257),
	textures(&texture_dungeon01, 258),
	textures(&texture_dungeon01, 259),
	textures(&texture_dungeon01, 260),
	textures(&texture_dungeon01, 261),
	textures(&texture_dungeon01, 262),
	textures(&texture_dungeon01, 263),
	textures(&texture_dungeon01, 264),
	textures(&texture_dungeon01, 265),
	textures(&texture_dungeon01, 266),
	textures(&texture_dungeon01, 267),
	textures(&texture_dungeon01, 268),
	textures(&texture_dungeon01, 269),
	textures(&texture_dungeon01, 270),
	textures(&texture_dungeon01, 271)
};


textures img_auto_hell_wall[48] = {
	textures(&texture_dungeon01, 288),
	textures(&texture_dungeon01, 289),
	textures(&texture_dungeon01, 290),
	textures(&texture_dungeon01, 291),
	textures(&texture_dungeon01, 292),
	textures(&texture_dungeon01, 293),
	textures(&texture_dungeon01, 294),
	textures(&texture_dungeon01, 295),
	textures(&texture_dungeon01, 296),
	textures(&texture_dungeon01, 297),
	textures(&texture_dungeon01, 298),
	textures(&texture_dungeon01, 299),
	textures(&texture_dungeon01, 300),
	textures(&texture_dungeon01, 301),
	textures(&texture_dungeon01, 302),
	textures(&texture_dungeon01, 303),
	textures(&texture_dungeon01, 304),
	textures(&texture_dungeon01, 305),
	textures(&texture_dungeon01, 306),
	textures(&texture_dungeon01, 307),
	textures(&texture_dungeon01, 308),
	textures(&texture_dungeon01, 309),
	textures(&texture_dungeon01, 310),
	textures(&texture_dungeon01, 311),
	textures(&texture_dungeon01, 312),
	textures(&texture_dungeon01, 313),
	textures(&texture_dungeon01, 314),
	textures(&texture_dungeon01, 315),
	textures(&texture_dungeon01, 316),
	textures(&texture_dungeon01, 317),
	textures(&texture_dungeon01, 318),
	textures(&texture_dungeon01, 319),
	textures(&texture_dungeon01, 320),
	textures(&texture_dungeon01, 321),
	textures(&texture_dungeon01, 322),
	textures(&texture_dungeon01, 323),
	textures(&texture_dungeon01, 324),
	textures(&texture_dungeon01, 325),
	textures(&texture_dungeon01, 326),
	textures(&texture_dungeon01, 327),
	textures(&texture_dungeon01, 328),
	textures(&texture_dungeon01, 329),
	textures(&texture_dungeon01, 330),
	textures(&texture_dungeon01, 331),
	textures(&texture_dungeon01, 332),
	textures(&texture_dungeon01, 333),
	textures(&texture_dungeon01, 334),
	textures(&texture_dungeon01, 335)
};

textures img_auto_lava[48] = {
	textures(&texture_dungeon01, 352),
	textures(&texture_dungeon01, 353),
	textures(&texture_dungeon01, 354),
	textures(&texture_dungeon01, 355),
	textures(&texture_dungeon01, 356),
	textures(&texture_dungeon01, 357),
	textures(&texture_dungeon01, 358),
	textures(&texture_dungeon01, 359),
	textures(&texture_dungeon01, 360),
	textures(&texture_dungeon01, 361),
	textures(&texture_dungeon01, 362),
	textures(&texture_dungeon01, 363),
	textures(&texture_dungeon01, 364),
	textures(&texture_dungeon01, 365),
	textures(&texture_dungeon01, 366),
	textures(&texture_dungeon01, 367),
	textures(&texture_dungeon01, 368),
	textures(&texture_dungeon01, 369),
	textures(&texture_dungeon01, 370),
	textures(&texture_dungeon01, 371),
	textures(&texture_dungeon01, 372),
	textures(&texture_dungeon01, 373),
	textures(&texture_dungeon01, 374),
	textures(&texture_dungeon01, 375),
	textures(&texture_dungeon01, 376),
	textures(&texture_dungeon01, 377),
	textures(&texture_dungeon01, 378),
	textures(&texture_dungeon01, 379),
	textures(&texture_dungeon01, 380),
	textures(&texture_dungeon01, 381),
	textures(&texture_dungeon01, 382),
	textures(&texture_dungeon01, 383),
	textures(&texture_dungeon01, 384),
	textures(&texture_dungeon01, 385),
	textures(&texture_dungeon01, 386),
	textures(&texture_dungeon01, 387),
	textures(&texture_dungeon01, 388),
	textures(&texture_dungeon01, 389),
	textures(&texture_dungeon01, 390),
	textures(&texture_dungeon01, 391),
	textures(&texture_dungeon01, 392),
	textures(&texture_dungeon01, 393),
	textures(&texture_dungeon01, 394),
	textures(&texture_dungeon01, 395),
	textures(&texture_dungeon01, 396),
	textures(&texture_dungeon01, 397),
	textures(&texture_dungeon01, 398),
	textures(&texture_dungeon01, 399)
};

textures img_auto_oil[48] = {
	textures(&texture_dungeon01, 416),
	textures(&texture_dungeon01, 417),
	textures(&texture_dungeon01, 418),
	textures(&texture_dungeon01, 419),
	textures(&texture_dungeon01, 420),
	textures(&texture_dungeon01, 421),
	textures(&texture_dungeon01, 422),
	textures(&texture_dungeon01, 423),
	textures(&texture_dungeon01, 424),
	textures(&texture_dungeon01, 425),
	textures(&texture_dungeon01, 426),
	textures(&texture_dungeon01, 427),
	textures(&texture_dungeon01, 428),
	textures(&texture_dungeon01, 429),
	textures(&texture_dungeon01, 430),
	textures(&texture_dungeon01, 431),
	textures(&texture_dungeon01, 432),
	textures(&texture_dungeon01, 433),
	textures(&texture_dungeon01, 434),
	textures(&texture_dungeon01, 435),
	textures(&texture_dungeon01, 436),
	textures(&texture_dungeon01, 437),
	textures(&texture_dungeon01, 438),
	textures(&texture_dungeon01, 439),
	textures(&texture_dungeon01, 440),
	textures(&texture_dungeon01, 441),
	textures(&texture_dungeon01, 442),
	textures(&texture_dungeon01, 443),
	textures(&texture_dungeon01, 444),
	textures(&texture_dungeon01, 445),
	textures(&texture_dungeon01, 446),
	textures(&texture_dungeon01, 447),
	textures(&texture_dungeon01, 448),
	textures(&texture_dungeon01, 449),
	textures(&texture_dungeon01, 450),
	textures(&texture_dungeon01, 451),
	textures(&texture_dungeon01, 452),
	textures(&texture_dungeon01, 453),
	textures(&texture_dungeon01, 454),
	textures(&texture_dungeon01, 455),
	textures(&texture_dungeon01, 456),
	textures(&texture_dungeon01, 457),
	textures(&texture_dungeon01, 458),
	textures(&texture_dungeon01, 459),
	textures(&texture_dungeon01, 460),
	textures(&texture_dungeon01, 461),
	textures(&texture_dungeon01, 462),
	textures(&texture_dungeon01, 463)
};


textures img_auto_snow[48] = {
	textures(&texture_dungeon02, 0),
	textures(&texture_dungeon02, 1),
	textures(&texture_dungeon02, 2),
	textures(&texture_dungeon02, 3),
	textures(&texture_dungeon02, 4),
	textures(&texture_dungeon02, 5),
	textures(&texture_dungeon02, 6),
	textures(&texture_dungeon02, 7),
	textures(&texture_dungeon02, 8),
	textures(&texture_dungeon02, 9),
	textures(&texture_dungeon02, 10),
	textures(&texture_dungeon02, 11),
	textures(&texture_dungeon02, 12),
	textures(&texture_dungeon02, 13),
	textures(&texture_dungeon02, 14),
	textures(&texture_dungeon02, 15),
	textures(&texture_dungeon02, 16),
	textures(&texture_dungeon02, 17),
	textures(&texture_dungeon02, 18),
	textures(&texture_dungeon02, 19),
	textures(&texture_dungeon02, 20),
	textures(&texture_dungeon02, 21),
	textures(&texture_dungeon02, 22),
	textures(&texture_dungeon02, 23),
	textures(&texture_dungeon02, 24),
	textures(&texture_dungeon02, 25),
	textures(&texture_dungeon02, 26),
	textures(&texture_dungeon02, 27),
	textures(&texture_dungeon02, 28),
	textures(&texture_dungeon02, 29),
	textures(&texture_dungeon02, 30),
	textures(&texture_dungeon02, 31),
	textures(&texture_dungeon02, 32),
	textures(&texture_dungeon02, 33),
	textures(&texture_dungeon02, 34),
	textures(&texture_dungeon02, 35),
	textures(&texture_dungeon02, 36),
	textures(&texture_dungeon02, 37),
	textures(&texture_dungeon02, 38),
	textures(&texture_dungeon02, 39),
	textures(&texture_dungeon02, 40),
	textures(&texture_dungeon02, 41),
	textures(&texture_dungeon02, 42),
	textures(&texture_dungeon02, 43),
	textures(&texture_dungeon02, 44),
	textures(&texture_dungeon02, 45),
	textures(&texture_dungeon02, 46),
	textures(&texture_dungeon02, 47)
};


textures img_dungeon01[] = {
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 0, 0, 32, 32, 255), //땅1
					textures(&texture_dungeon01, 0, 0, 32, 32, 255),
					textures(&texture_dungeon01, 256, 0, 288, 32, 255),
					textures(&texture_dungeon01, 384, 0, 416, 32, 255),
					textures(&texture_dungeon01, 512, 0, 544, 32, 255), //마계땅1
					textures(&texture_dungeon01, 544, 0, 576, 32, 255),
					textures(&texture_dungeon01, 576, 0, 608, 32, 255),
					textures(&texture_dungeon01, 608, 0, 640, 32, 255),
					textures(&texture_dungeon01, 640, 0, 672, 32, 255),

					textures(&texture_dungeon01, 672, 0, 704, 32, 255),
					textures(&texture_dungeon01, 704, 0, 736, 32, 255), //마계땅7
					textures(&texture_dungeon01, 480, 0, 512, 32, 255),
					textures(&texture_dungeon01, 480, 330, 512, 362, 255),
					textures(&texture_dungeon01), //오일
					textures(&texture_dungeon01), //바다
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),

					textures(&texture_dungeon01), //문열림 25
					textures(&texture_dungeon01), //계단
					textures(&texture_dungeon01), //계단
					textures(&texture_dungeon01), //계단-신전
					textures(&texture_dungeon01), //계단-안개
					textures(&texture_dungeon01), //계단-요괴산
					textures(&texture_dungeon01), //계단-홍마					
					textures(&texture_dungeon01), //계단홍마도서관
					textures(&texture_dungeon01), //계단홍마지하
					textures(&texture_dungeon01), //계단죽림

					textures(&texture_dungeon01), //계단영원정
					textures(&texture_dungeon01), //계단지저
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),

					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),//플로어 더미끝		

					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),					
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),

					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01),
					textures(&texture_dungeon01, 64, 0, 96, 32, 255),//벽70
					textures(&texture_dungeon01, 32, 0, 64, 32, 255),//돌벽
					textures(&texture_dungeon01, 128, 0, 160, 32, 255),//붉은벽
					textures(&texture_dungeon01, 160, 0, 192, 32, 255),//책장
					textures(&texture_dungeon01, 224, 0, 256, 32, 255),//대나무

					textures(&texture_dungeon01, 736, 0, 768, 32, 255), //마계벽1
					textures(&texture_dungeon01, 768, 0, 800, 32, 255), //마계벽2
					textures(&texture_dungeon01, 800, 0, 832, 32, 255), //마계벽3
					textures(&texture_dungeon01, 832, 0, 864, 32, 255), //마계벽4
					textures(&texture_dungeon01, 864, 0, 896, 32, 255), //마계벽5
					textures(&texture_dungeon01, 896, 0, 928, 32, 255), //마계벽6
					textures(&texture_dungeon01, 928, 0, 960, 32, 255), //마계벽7

					textures(&texture_dungeon01, 256, 0, 288, 32, 255),//나무
					textures(&texture_dungeon01, 256, 0, 288, 32, 255),//해바라기
					textures(&texture_dungeon01, 256, 0, 288, 32, 255),//지옥벽
					textures(&texture_dungeon01, 192, 0, 224, 32, 255),//철벽
					textures(&texture_dungeon01, 448, 0, 480, 32, 255),//벽2
					textures(&texture_dungeon01, 480, 0, 512, 32, 255),//벽3
					textures(&texture_item01, 3, 255), //닫힌문
					textures(&texture_dungeon01), //포장마차
					textures(&texture_dungeon01), //묘비
					textures(&texture_dungeon02), //눈사람
					textures(&texture_dungeon01),//유리
					textures(&texture_dungeon01),//석상
					textures(&texture_dungeon01, 256, 0, 288, 32, 255),//석상2
					textures(&texture_dungeon01, 96, 0, 128, 32, 255),//바다
					textures(&texture_dungeon01, 96, 0, 128, 32, 255)//용암
};

textures img_dungeon_object[][3] = {
				{textures(&texture_item01, 4, 255),textures(&texture_item01, 4, 255),textures(&texture_item01, 4, 255)},
				{textures(&texture_item01, 5, 255),textures(&texture_item01, 5, 255),textures(&texture_item01, 5, 255)},//계단내
				{textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255)},//계단올
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단신전
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단안개
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단요괴
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단홍마
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단홍마도서관
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단홍마지하
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단죽림
				
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단영원정
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단지저
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)},//계단윳쿠리
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단짐승길
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단꿈
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단달
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단마계
				{textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255),textures(&texture_item01, 213, 255)}, //계단히쿠레이
				{textures(&texture_item03, 29, 255), textures(&texture_item03, 29, 255),textures(&texture_item03, 29, 255) }, //계단꿈의포탈
				{textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255),textures(&texture_item01, 6, 255)},//계단
				{textures(&texture_item03, 25, 255),textures(&texture_item03, 25, 255),textures(&texture_item03, 25, 255)}, //죠온&시온

				{textures(&texture_item01, 121, 255),textures(&texture_item01, 121, 255),textures(&texture_item01, 121, 255)}, //뱌쿠렌
				{textures(&texture_item01, 122, 255),textures(&texture_item01, 122, 255),textures(&texture_item01, 122, 255)}, //카나코
				{textures(&texture_item01, 123, 255),textures(&texture_item01, 123, 255),textures(&texture_item01, 123, 255)}, //스와코
				{textures(&texture_item01, 124, 255),textures(&texture_item01, 124, 255),textures(&texture_item01, 124, 255)}, //미노리코
				{textures(&texture_item01, 125, 255),textures(&texture_item01, 125, 255),textures(&texture_item01, 125, 255)}, //미마
				{textures(&texture_item01, 126, 255),textures(&texture_item01, 126, 255),textures(&texture_item01, 126, 255)}, //신키
				{textures(&texture_item01, 127, 255),textures(&texture_item01, 127, 255),textures(&texture_item01, 127, 255)},  //유우기
				{textures(&texture_item01, 128, 255),textures(&texture_item01, 220, 255),textures(&texture_item01, 221, 255)}, //시즈하
			    {textures(&texture_item01, 129, 255),textures(&texture_item01, 129, 255),textures(&texture_item01, 129, 255)}, //히나
			    {textures(&texture_item01, 130, 255),textures(&texture_item01, 130, 255),textures(&texture_item01, 130, 255)}, //유카리
			    
				{textures(&texture_item01, 131, 255),textures(&texture_item01, 131, 255),textures(&texture_item01, 131, 255)}, //에이린
				{textures(&texture_item01, 132, 255),textures(&texture_item01, 132, 255),textures(&texture_item01, 132, 255)}, //유유코
			    {textures(&texture_item01, 133, 255),textures(&texture_item01, 133, 255),textures(&texture_item01, 133, 255)}, //사토리
			    {textures(&texture_item01, 134, 255),textures(&texture_item01, 134, 255),textures(&texture_item01, 134, 255)}, //텐시
				{textures(&texture_item01, 236, 255),textures(&texture_item01, 236, 255),textures(&texture_item01, 236, 255)}, //세이자				
				{textures(&texture_item01, 175, 255),textures(&texture_item01, 175, 255),textures(&texture_item01, 175, 255)}, //릴리
				{textures(&texture_item01, 173, 255), textures(&texture_item01, 173, 255), textures(&texture_item01, 173, 255) }, //미코
				{textures(&texture_item02, 168, 255), textures(&texture_item02, 168, 255), textures(&texture_item02, 168, 255) }, //오키나
				{textures(&texture_item02, 169, 255), textures(&texture_item02, 170, 255), textures(&texture_item02, 171, 255) }, //순호
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},  //시키에이키

				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}, //케이키
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}, //텐큐
//textures img_command_wide_search(&texture_item03, 192, 255);
//textures img_command_wide_search(&texture_item03, 193, 255);
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}, //벽
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },

				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },

				{textures(&texture_item02, 160, 255),textures(&texture_item02, 160, 255),textures(&texture_item02, 160, 255) },
				{ textures(&texture_item02, 159, 255),textures(&texture_item02, 159, 255),textures(&texture_item02, 159, 255) },
				{ textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255) },
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
				{textures(&texture_item03, 195, 255),textures(&texture_item03, 195, 255),textures(&texture_item03, 195, 255)},
				{textures(&texture_item03, 196, 255),textures(&texture_item03, 196, 255),textures(&texture_item03, 196, 255)},
				{textures(&texture_item03, 197, 255),textures(&texture_item03, 197, 255),textures(&texture_item03, 197, 255)},
				{textures(&texture_item01, 168, 255),textures(&texture_item01, 168, 255),textures(&texture_item01, 168, 255)},
				{textures(&texture_item01, 222, 255),textures(&texture_item01, 222, 255),textures(&texture_item01, 222, 255)},
				{textures(&texture_item02, 161, 255),textures(&texture_item02, 161, 255),textures(&texture_item02, 161, 255)},
				{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)},
			{textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255),textures(&texture_item01, 2, 255)}
};


textures img_mons_default(&texture_monster01, 47, 255);

textures img_mons_reimu_yukkuri(&texture_monster01, 0, 255);
textures img_mons_rat(&texture_monster01, 1, 255);
textures img_mons_fairy_green(&texture_monster01, 2, 255);
textures img_mons_fairy_blue(&texture_monster01, 3, 255);
textures img_mons_fairy_red(&texture_monster01, 4, 255);
textures img_mons_mook(&texture_monster01, 5, 255);
textures img_mons_crow(&texture_monster01, 6, 255);
textures img_mons_crane(&texture_monster01, 7, 255);
textures img_mons_spider(&texture_monster01, 8, 255);
textures img_mons_snake(&texture_monster01, 9, 255);
textures img_mons_katpa(&texture_monster01, 59, 255);
textures img_mons_katpa_gun(&texture_monster01, 59, 255);
textures img_mons_fairy_green_warroir(&texture_monster01, 10, 255);
textures img_mons_fairy_blue_magician(&texture_monster01, 11, 255);
textures img_mons_fairy_red_commander(&texture_monster01, 12, 255);
textures img_mons_human_woman(&texture_monster01,19, 255);
textures img_mons_human_man(&texture_monster01, 20, 255);
textures img_mons_human_yinyang(&texture_monster01, 21, 255);
textures img_mons_human_priest(&texture_monster01, 22, 255);
textures img_mons_human_samuri(&texture_monster01, 23, 255);
textures img_mons_firefly(&texture_monster01, 24, 255);
textures img_mons_butterfly(&texture_monster01, 25, 255);
textures img_mons_ghost[] = {textures(&texture_monster01, 26, 255),
				textures(&texture_monster01, 27, 255),
				textures(&texture_monster01, 28	, 255)};
textures img_mons_bakekasa(&texture_monster01, 29, 255);
textures img_mons_green_mook(&texture_monster01, 30, 255);
textures img_mons_orange_mook(&texture_monster01, 31, 255);
textures img_mons_gray_mook(&texture_monster01, 32, 255);
textures img_mons_frog(&texture_monster01, 33, 255);
textures img_mons_black_cat(&texture_monster01, 34, 255);
textures img_mons_orange_cat(&texture_monster01, 35, 255);
textures img_mons_white_cat(&texture_monster01, 36, 255);
textures img_mons_crow_tengu(&texture_monster01, 38, 255);
textures img_mons_oni(&texture_monster01, 37, 255);
textures img_mons_marisa_yukkuri(&texture_monster01, 45, 255);
textures img_mons_aya_yukkuri(&texture_monster01, 46, 255);
textures img_mons_remila_yukkuri(&texture_monster01, 49, 255);
textures img_mons_alice_yukkuri(&texture_monster01, 50, 255);
textures img_mons_yamabiko(&texture_monster01, 51, 255);
textures img_mons_katpa_spear(&texture_monster01, 60, 255);
textures img_mons_katpa_water_wizard(&texture_monster01, 61, 255);
textures img_mons_yamabush_tengu(&texture_monster01, 52, 255);
textures img_mons_hanataca_tengu(&texture_monster01, 53, 255);
textures img_mons_blue_oni(&texture_monster01, 54, 255);
textures img_mons_mushroom(&texture_monster01, 55, 255);
textures img_mons_new_kappa(&texture_monster01, 59, 255);
textures img_mons_new_kappa_spear(&texture_monster01, 60, 255);
textures img_mons_new_kappa_wizard(&texture_monster01, 61, 255);

textures img_mons_magic_book[] = 
{
	textures(&texture_monster01, 85, 255),
	textures(&texture_monster01, 86, 255),
	textures(&texture_monster01, 87, 255),
	textures(&texture_monster01, 88, 255)
};
textures img_mons_hobgobrin(&texture_monster01, 89, 255);
textures img_mons_hobgobrin_maid(&texture_monster01, 90, 255);
textures img_mons_hobgobrin_librarian(&texture_monster01, 91, 255);
textures img_mons_hobgobrin_temp(&texture_monster01, 92, 255);
textures img_mons_maid_fairy(&texture_monster01, 93, 255);
textures img_mons_chuparcabra(&texture_monster01, 94, 255);
textures img_mons_eagle(&texture_monster01, 99, 255);
textures img_mons_tiger(&texture_monster01, 100, 255);
textures img_mons_raijuu(&texture_monster01, 101, 255);
textures img_mons_dragon_baby(&texture_monster01, 102, 255);

textures img_mons_yamawaro_ninja(&texture_monster01, 104, 255);
textures img_mons_yamawaro_warrior(&texture_monster01, 105, 255);
textures img_mons_yamawaro_flag(&texture_monster01, 106, 255);
textures img_mons_option(&texture_monster01, 107, 255);
textures img_mons_golem(&texture_monster01, 108, 255);
textures img_mons_onbasira(&texture_monster01, 109, 255);
textures img_mons_red_ufo(&texture_monster01, 110, 255);
textures img_mons_blue_ufo(&texture_monster01, 111, 255);
textures img_mons_green_ufo(&texture_monster01, 112, 255);
textures img_mons_sanpei_fighter(&texture_monster01, 115, 255);
textures img_mons_vamp_bat(&texture_monster01, 116, 255);
textures img_mons_dagama(&texture_monster01, 117, 255);

textures img_mons_rabit(&texture_monster01, 118, 255);
textures img_mons_youkai_rabit(&texture_monster01, 119, 255);
textures img_mons_namaz(&texture_monster01, 120, 255);
textures img_mons_hell_crow(&texture_monster01, 121, 255);
textures img_mons_raccoon(&texture_monster01, 122, 255);
textures img_mons_lantern_youkai(&texture_monster01, 123, 255);
textures img_mons_yinyan(&texture_monster01, 124, 255);
textures img_mons_yugenmagan(&texture_monster01, 125, 255);
textures img_mons_elise(&texture_monster01, 126, 255);
textures img_mons_sariel(&texture_monster01, 127, 255);
textures img_mons_sara(&texture_monster01, 128, 255);
textures img_mons_louise(&texture_monster01, 129, 255);
textures img_mons_yuki(&texture_monster01, 130, 255);
textures img_mons_mai(&texture_monster01, 131, 255);
textures img_mons_yumeko(&texture_monster01, 132, 255);
textures img_mons_evil_eye(&texture_monster01, 133, 255);
textures img_mons_little_imp(&texture_monster01, 134, 255);
textures img_mons_schema_eye(&texture_monster01, 138, 255);
textures img_mons_bomb_rabbit(&texture_monster01, 139, 255);
textures img_mons_spear_rabbit(&texture_monster01, 140, 255);
textures img_mons_support_rabbit(&texture_monster01, 141, 255);
textures img_mons_magic_rabbit(&texture_monster01, 142, 255);


textures img_named_seiran(&texture_monster01, 147, 255);
textures img_named_ringo(&texture_monster01, 148, 255);
textures img_mons_fairy_green_hero(&texture_monster01, 149, 255);
textures img_mons_fairy_green_socerer(&texture_monster01, 150, 255);
textures img_mons_fairy_green_himawari(&texture_monster01, 151, 255);
textures img_mons_moon_rabbit_attack(&texture_monster01, 152, 255);
textures img_mons_moon_rabbit_supporter(&texture_monster01, 153, 255);
textures img_mons_moon_rabbit_elite(&texture_monster01, 154, 255);
textures img_mons_mac(&texture_monster01, 155, 255);
textures img_mons_nightmare(&texture_monster01, 156, 255);
textures img_mons_lunatic(&texture_monster01, 157, 255);
textures img_mons_haunt[] = 
{
	textures(&texture_monster01, 158, 255),
	textures(&texture_monster01, 159, 255),
	textures(&texture_monster01, 160, 255)
};
textures img_mons_fire_car(&texture_monster01, 161, 255);
textures img_mons_hell_spider(&texture_monster01, 162, 255);
textures img_mons_blood_haunt(&texture_monster01, 163, 255);
textures img_mons_hell_dog(&texture_monster01, 164, 255);
textures img_mons_flower_tank[] = 
{
	textures(&texture_monster01, 165, 255),
	textures(&texture_monster01, 166, 255)
};
textures img_mons_evil_eye_tank(&texture_monster01, 167, 255);
textures img_mons_snow_girl(&texture_monster01, 168, 255);
textures img_named_letty(&texture_monster01, 169, 255);
textures img_named_yorihime(&texture_monster01, 170, 255);
textures img_named_toyohime(&texture_monster01, 171, 255);
textures img_named_utsuho(&texture_monster01, 172, 255);
textures img_named_suika(&texture_monster01, 173, 255);
textures img_named_reimu(&texture_monster01, 174, 255);
textures img_named_alice(&texture_monster01, 175, 255);
textures img_named_udonge(&texture_monster01, 176, 255);
textures img_named_kaguya(&texture_monster01, 177, 255);
textures img_mons_nesi(&texture_monster01, 178, 255);
textures img_mons_sanghai[] = 
{
	textures(&texture_monster01, 179, 255),
	textures(&texture_monster01, 181, 255)
};
textures img_mons_hourai[] = 
{
	textures(&texture_monster01, 180, 255),
	textures(&texture_monster01, 182, 255)
};

textures img_mons_youmu_yukkuri(&texture_monster01, 183, 255);
textures img_mons_tokiko(&texture_monster01, 184, 255);
textures img_mons_toziko(&texture_monster01, 185, 255);
textures img_mons_futo(&texture_monster01, 186, 255);
textures img_mons_mamizo(&texture_monster01, 187, 255);
textures img_mons_seiga(&texture_monster01, 188, 255);
textures img_mons_close_door(&texture_item02, 162, 255);

textures img_mons_anchor(&texture_monster01, 190, 255);
textures img_mons_mask_angry(&texture_monster01, 212, 255);
textures img_mons_mask_sad(&texture_monster01, 213, 255);
textures img_mons_mask_happy(&texture_monster01, 214, 255);
textures img_mons_trash[] =
{
	textures(&texture_monster01, 216, 255),
	textures(&texture_monster01, 217, 255),
	textures(&texture_monster01, 218, 255),
	textures(&texture_monster01, 219, 255)
};

textures img_mons_occult_long(&texture_monster01, 220, 255);
textures img_mons_occult_disk(&texture_monster01, 221, 255);
textures img_mons_occult_small(&texture_monster01, 222, 255);
textures img_mons_occult_kunekune(&texture_monster01, 223, 255);
textures img_mons_kaname(&texture_monster01, 224, 255);
textures img_mons_sheep(&texture_monster01, 225, 255);
textures img_mons_bee(&texture_monster01, 226, 255);
textures img_mons_bush(&texture_item02, 175, 255);
textures img_mons_sion(&texture_monster01, 227, 255);

textures img_named_hatate(&texture_monster01, 228, 255);
textures img_mons_dancing_weapon(&texture_monster01, 229, 255);
textures img_mons_cursed_doll(&texture_monster01, 230, 255);
textures img_named_doreking(&texture_monster01, 231, 255);

textures img_mons_curiosity(&texture_monster01, 232, 255);
textures img_mons_desire_red(&texture_monster01, 233, 255);
textures img_mons_desire_green(&texture_monster01, 234, 255);
textures img_mons_desire_blue(&texture_monster01, 235, 255);

textures img_mons_fog_fairy(&texture_monster02, 20, 255);
textures img_mons_tsuchinoko(&texture_monster02, 21, 255);
textures img_mons_vine(&texture_monster02, 22, 255);
textures img_mons_security_fairy_maid(&texture_monster02, 23, 255);
textures img_mons_big_slime(&texture_monster02, 24, 255);
textures img_mons_small_slime(&texture_monster02, 25, 255);
textures img_mons_new_yamabush_tengu(&texture_monster02, 26, 255);
textures img_mons_new_hanataca_tengu(&texture_monster02, 27, 255);
textures img_mons_haniwa(&texture_monster02, 28, 255);
textures img_mons_horse_haniwa(&texture_monster02, 36, 255);

textures img_mons_haniwa_spearman(&texture_monster02, 43, 255);
textures img_mons_haniwa_archer(&texture_monster02, 44, 255);
textures img_mons_haniwa_cavalry(&texture_monster02, 45, 255);

textures img_mons_wolf_spirit(&texture_monster02, 49, 255);
textures img_mons_eagle_spirit(&texture_monster02, 50, 255);
textures img_mons_otter_spirit(&texture_monster02, 51, 255);

textures img_mons_haniwa_equipments[] =
{
	textures(&texture_monster02, 29, 255), //칼 (R)
	textures(&texture_monster02, 30, 255), //방패 (L)
	textures(&texture_monster02, 31, 255), //보조칼 (L)
	textures(&texture_monster02, 32, 255), //지팡이 (R)
	textures(&texture_monster02, 33, 255), //헬멧
	textures(&texture_monster02, 34, 255), //활(LR)
	textures(&texture_monster02, 35, 255), //창(LR)
	textures(&texture_monster02, 46, 255), //응급상자(R)
	textures(&texture_monster02, 48, 255), //황금방패(L)
	textures(&texture_monster02, 37, 255), //칼 (R, 승마)
	textures(&texture_monster02, 38, 255), //보조칼 (L, 승마)
	textures(&texture_monster02, 39, 255), //지팡이 (R, 승마)
	textures(&texture_monster02, 40, 255), //헬멧 (승마)
	textures(&texture_monster02, 41, 255), //활 (LR, 승마)
	textures(&texture_monster02, 42, 255), //창 (LR, 승마)
	textures(&texture_monster02, 47, 255), //응급상자(R, 승마)
};

textures img_mons_stonetower[] =
{
	textures(&texture_monster01, 237, 255),
	textures(&texture_monster01, 238, 255),
	textures(&texture_monster01, 239, 255),
	textures(&texture_monster02, 18, 255),
	textures(&texture_monster02, 19, 255)
};
textures img_mons_security_door(&texture_item03, 214, 255);


textures img_named_rumia(&texture_monster01, 13, 255);
textures img_named_mistia(&texture_monster01, 14, 255);
textures img_named_wriggle(&texture_monster01, 15, 255);
textures img_named_cirno(&texture_monster01, 16, 255);
textures img_named_medicine(&texture_monster01, 17, 255);
textures img_named_diefairy(&texture_monster01, 18, 255);
textures img_named_kisume(&texture_monster01, 39, 255);
textures img_named_chen(&texture_monster01,40, 255);
textures img_named_kogasa(&texture_monster01, 41, 255);
textures img_named_sunny(&texture_monster01, 42, 255);
textures img_named_lunar(&texture_monster01, 43, 255);
textures img_named_star(&texture_monster01, 44, 255);
textures img_named_sigmund(&texture_monster01, 48, 255);
textures img_named_kyouko(&texture_monster01, 56, 255);
textures img_named_momizi(&texture_monster01, 57, 255);
textures img_named_aya(&texture_monster01, 58, 255);
textures img_named_wakasagi(&texture_monster01, 62, 255);
textures img_named_yamame(&texture_monster01, 63, 255);
textures img_named_nazrin(&texture_monster01, 64, 255);
textures img_mons_dauzing(&texture_monster01, 65, 255);
textures img_named_yosika(&texture_monster01, 66, 255);
textures img_named_sekibanki(&texture_monster01, 67, 255);
textures img_named_sekibanki_body(&texture_monster01, 68, 255);
textures img_named_sekibanki_head(&texture_monster01, 69, 255);
textures img_named_nitori(&texture_monster01, 70, 255);
textures img_named_kagero(&texture_monster01, 71, 255);
textures img_named_parsi(&texture_monster01, 72, 255);
textures img_named_benben(&texture_monster01, 73, 255);
textures img_named_yathasi(&texture_monster01, 74, 255);
textures img_named_orin(&texture_monster01, 75, 255);
textures img_named_orin_cat(&texture_monster01, 76, 255);
textures img_mons_zombiefairy(&texture_monster01, 77, 255);
textures img_named_ichirin(&texture_monster01, 78, 255);
textures img_named_unzan(&texture_monster01, 79, 255);
textures img_named_unzan_punch[] = 
{
	textures(&texture_monster01, 80, 255),
	textures(&texture_monster01, 81, 255),
	textures(&texture_monster01, 82, 255),
	textures(&texture_monster01, 83, 255)
};
textures img_named_pachu(&texture_monster01, 84, 255);
textures img_named_koakuma(&texture_monster01, 95, 255);
textures img_named_meirin(&texture_monster01, 96, 255);
textures img_named_sakuya(&texture_monster01, 97, 255);
textures img_named_remilia(&texture_monster01, 98, 255);
textures img_named_kasen(&texture_monster01, 103, 255);
textures img_named_koishi(&texture_monster01, 113, 255);
textures img_named_nue(&texture_monster01, 114, 255);
textures img_named_flandre(&texture_monster01, 143, 255);
textures img_named_tewi(&texture_monster01, 144, 255);
textures img_named_clownpiece(&texture_monster01, 145, 255);
textures img_named_doremi(&texture_monster01, 146, 255);
textures img_named_murasa(&texture_monster01, 189, 255);
textures img_named_keine(&texture_monster01, 191, 255);
textures img_named_keine2(&texture_monster01, 192, 255);
textures img_named_youmu(&texture_monster01, 193, 255);
textures img_named_lyrica(&texture_monster01, 194, 255);
textures img_named_merlin(&texture_monster01, 195, 255);
textures img_named_lunasa(&texture_monster01, 196, 255);
textures img_named_komachi(&texture_monster01, 197, 255);
textures img_named_iku(&texture_monster01, 200, 255);
textures img_named_larva(&texture_monster01, 201, 255);
textures img_named_nemuno(&texture_monster01, 202, 255);
textures img_named_aunn(&texture_monster01, 203, 255);
textures img_named_narumi(&texture_monster01, 204, 255);
textures img_named_mai(&texture_monster01, 206, 255);
textures img_named_satono(&texture_monster01, 205, 255);
textures img_named_kokoro[] =
{
	textures(&texture_monster01, 208, 255),
	textures(&texture_monster01, 209, 255),
	textures(&texture_monster01, 210, 255),
	textures(&texture_monster01, 211, 255)
};
textures img_named_sumireko(&texture_monster01, 215, 255);
textures img_named_reimu2(&texture_monster01, 198, 255);
textures img_mons_misyaguzi(&texture_monster01, 199, 255);

textures img_mons_eika(&texture_monster01, 236, 255);
textures img_mons_urumi(&texture_monster02, 0, 255);
textures img_mons_kutaka(&texture_monster02, 1, 255);
textures img_mons_yachie(&texture_monster02, 2, 255);
textures img_mons_mayumi(&texture_monster02, 3, 255);
textures img_mons_saki(&texture_monster02, 4, 255);
textures img_mons_yuma(&texture_monster02, 5, 255);
textures img_mons_yuma_drainform(&texture_monster02, 6, 255);
textures img_mons_enoko(&texture_monster02, 7, 255);
textures img_mons_chiyari(&texture_monster02, 8, 255);
textures img_mons_sonbiten(&texture_monster02, 9, 255);
textures img_mons_sonbiten_spintowin(&texture_monster02, 52, 255);
textures img_mons_hisami(&texture_monster02, 10, 255);
textures img_mons_tsukasa(&texture_monster02, 11, 255);
textures img_mons_ubame(&texture_monster02, 12, 255);
textures img_mons_chimi(&texture_monster02, 13, 255);
textures img_mons_nareko(&texture_monster02, 14, 255);
textures img_mons_mike(&texture_monster02, 15, 255);
textures img_mons_takane(&texture_monster02, 16, 255);
textures img_mons_sannyo(&texture_monster02, 17, 255);








textures img_play_reimu(&texture_players01, 0, 255);
textures img_play_marisa(&texture_players01, 1, 255);
textures img_play_sanae(&texture_players01, 2, 255);
textures img_play_momizi(&texture_players01, 3, 255);
textures img_play_normal(&texture_players01, 4, 255);
textures img_play_yamame(&texture_players01, 5, 255);
textures img_play_mokou[] = {
		textures(&texture_players01, 6, 255),
		textures(&texture_players01, 7, 255),
		textures(&texture_players01, 8, 255)
};
textures img_playable_character[STYLE_NUM][COLOR_NUM] = {
	{textures(&texture_players01, 32),
	textures(&texture_players01, 33),
	textures(&texture_players01, 34),
	textures(&texture_players01, 35),
	textures(&texture_players01, 36)},

	{textures(&texture_players01, 37),
	textures(&texture_players01, 38),
	textures(&texture_players01, 39),
	textures(&texture_players01, 40),
	textures(&texture_players01, 41) },

	{ textures(&texture_players01, 42),
	textures(&texture_players01, 43),
	textures(&texture_players01, 44),
	textures(&texture_players01, 45),
	textures(&texture_players01, 46) },

	{ textures(&texture_players01, 47),
	textures(&texture_players01, 48),
	textures(&texture_players01, 49),
	textures(&texture_players01, 50),
	textures(&texture_players01, 51) },


	{ textures(&texture_players01, 52),
	textures(&texture_players01, 53),
	textures(&texture_players01, 54),
	textures(&texture_players01, 55),
	textures(&texture_players01, 56) },

	{ textures(&texture_players01, 57),
	textures(&texture_players01, 58),
	textures(&texture_players01, 59),
	textures(&texture_players01, 60),
	textures(&texture_players01, 61) },


	{ textures(&texture_players01, 62),
	textures(&texture_players01, 63),
	textures(&texture_players01, 64),
	textures(&texture_players01, 65),
	textures(&texture_players01, 66) },


	{ textures(&texture_players01, 67),
	textures(&texture_players01, 68),
	textures(&texture_players01, 69),
	textures(&texture_players01, 70),
	textures(&texture_players01, 71) },


	{ textures(&texture_players01, 72),
	textures(&texture_players01, 73),
	textures(&texture_players01, 74),
	textures(&texture_players01, 75),
	textures(&texture_players01, 76) },


	{ textures(&texture_players01, 77),
	textures(&texture_players01, 78),
	textures(&texture_players01, 79),
	textures(&texture_players01, 80),
	textures(&texture_players01, 81) },


	{ textures(&texture_players01, 82),
	textures(&texture_players01, 83),
	textures(&texture_players01, 84),
	textures(&texture_players01, 85),
	textures(&texture_players01, 86) }
};

textures img_play_item_cloak[2] = {
	textures(&texture_players01, 96),
	textures(&texture_players01, 97)
};
textures img_play_item_glove[1] = {
	textures(&texture_players01, 128)
};
textures img_play_item_boot[1] = {
	textures(&texture_players01, 160)
};
textures img_play_item_body[17] = {
	textures(&texture_players01, 192),
	textures(&texture_players01, 193),
	textures(&texture_players01, 194),
	textures(&texture_players01, 195),
	textures(&texture_players01, 196),
	textures(&texture_players01, 197),
	textures(&texture_players01, 198),
	textures(&texture_players01, 199),
	textures(&texture_players01, 200),
	textures(&texture_players01, 201),
	textures(&texture_players01, 202),
	textures(&texture_players01, 203),
	textures(&texture_players01, 204),
	textures(&texture_players01, 205),
	textures(&texture_players01, 206),
	textures(&texture_players01, 207),
	textures(&texture_players01, 208)
};
textures img_play_item_hat[7] = {
	textures(&texture_players01, 224),
	textures(&texture_players01, 225),
	textures(&texture_players01, 226),
	textures(&texture_players01, 227),
	textures(&texture_players01, 228),
	textures(&texture_players01, 229),
	textures(&texture_players01, 230)
};
textures img_play_item_shield[4] = {
	textures(&texture_players01, 256),
	textures(&texture_players01, 257),
	textures(&texture_players01, 258),
	textures(&texture_players01, 259)
};
textures img_play_item_weapon[21] = {
	textures(&texture_players01, 288),
	textures(&texture_players01, 289),
	textures(&texture_players01, 290),
	textures(&texture_players01, 291),
	textures(&texture_players01, 292),
	textures(&texture_players01, 293),
	textures(&texture_players01, 294),
	textures(&texture_players01, 295),
	textures(&texture_players01, 296),
	textures(&texture_players01, 297),
	textures(&texture_players01, 298),
	textures(&texture_players01, 299),
	textures(&texture_players01, 300),
	textures(&texture_players01, 301),
	textures(&texture_players01, 302),
	textures(&texture_players01, 303),
	textures(&texture_players01, 304),
	textures(&texture_players01, 305),
	textures(&texture_players01, 306),
	textures(&texture_players01, 307),
	textures(&texture_players01, 308)
};
textures img_play_item_tribe[1] = {
	textures(&texture_players01, 320)
};






textures img_item_armor_robe(&texture_item01, 7, 255);
textures img_item_armor_cloak(&texture_item01, 8, 255);
textures img_item_armor_robe_sanae(&texture_item01, 9, 255);
textures img_item_armor_glove(&texture_item01, 10, 255);
textures img_item_armor_boot(&texture_item01, 11, 255);
textures img_item_armor_helmet[] = {
	textures(&texture_item02, 75, 255),
	textures(&texture_item01, 12, 255),
	textures(&texture_item02, 76, 255),
	textures(&texture_item02, 77, 255),
	textures(&texture_item02, 78, 255),
	textures(&texture_item02, 79, 255),
	textures(&texture_item02, 74, 255)
};
textures img_item_armor_armour_0(&texture_item01, 136, 255);
textures img_item_armor_armour_1(&texture_item01, 137, 255);
textures img_item_armor_armour_2(&texture_item01, 138, 255);
textures img_item_armor_armour_3(&texture_item01, 139, 255);

textures img_item_autumn_armour[] =
{	
	textures(&texture_item01, 176, 255),
	textures(&texture_item01, 177, 255),
	textures(&texture_item01, 178, 255),
	textures(&texture_item01, 179, 255),
	textures(&texture_item01, 180, 255)
};


textures img_item_armor_relec(&texture_item01, 223, 255);
textures img_item_armor_rcold(&texture_item01, 224, 255);
textures img_item_armor_rfire(&texture_item01, 225, 255);
textures img_item_armor_rmagic(&texture_item01, 226, 255);
textures img_item_armor_rpois(&texture_item01, 227, 255);


textures img_item_evo_pagoda(&texture_item01, 228, 255);
textures img_item_evo_air_scroll(&texture_item01, 229, 255);
textures img_item_evo_dream_soul(&texture_item01, 230, 255);
textures img_item_evo_bomb(&texture_item03, 26, 255);
textures img_item_evo_ghost_ball(&texture_item03, 27, 255);
textures img_item_evo_sky_torpedo(&texture_item03, 28, 255);
textures img_item_evo_hammer(&texture_item01, 231, 255);



textures img_item_weapon_gohey(&texture_item01, 33, 255);
textures img_item_weapon_dagger(&texture_item01, 34, 255);
textures img_item_weapon_katana(&texture_item01, 35, 255);
textures img_item_weapon_scimitar(&texture_item01, 36, 255);
textures img_item_weapon_greatsword(&texture_item01, 37, 255);
textures img_item_weapon_broomstick(&texture_item01, 38, 255);
textures img_item_weapon_handaxe(&texture_item01, 39, 255);
textures img_item_weapon_battleaxe(&texture_item01, 40, 255);
textures img_item_weapon_anchor(&texture_item01, 41, 255);
textures img_item_weapon_spear(&texture_item01, 42, 255);
textures img_item_weapon_scythe(&texture_item01, 43, 255);
textures img_item_weapon_trident(&texture_item01, 44, 255);
textures img_item_weapon_smalllance(&texture_item01, 45, 255);
textures img_item_weapon_umbrella(&texture_item01, 46, 255);
textures img_item_weapon_knife(&texture_item01, 47, 255);
textures img_item_weapon_shortsword(&texture_item01, 48, 255);
textures img_item_weapon_gohey2(&texture_item01, 49, 255);
textures img_item_weapon_hammer(&texture_item01, 50, 255);
textures img_item_weapon_onbasira(&texture_item01, 51, 255);
textures img_item_weapon_roundshield(&texture_item01, 52, 255);
textures img_item_weapon_shield(&texture_item01, 53, 255);
textures img_item_weapon_momizishield(&texture_item01, 54, 255);
textures img_item_weapon_kiteshield(&texture_item01, 55, 255);
textures img_item_weapon_chakram(&texture_item02, 173, 255);
textures img_item_weapon_javelin(&texture_item02, 174, 255);
textures img_item_weapon_dauzing_rod(&texture_item02, 218, 255);
textures img_item_weapon_bamboo_spear(&texture_item02, 219, 255);


textures img_item_artifact_shortsword(&texture_item02, 220, 255);
textures img_item_artifact_bamboo_spear(&texture_item02, 221, 255);
textures img_item_artifact_hammer(&texture_item02, 222, 255);
textures img_item_artifact_onbasira(&texture_item02, 223, 255);
textures img_item_artifact_gohey(&texture_item02, 224, 255);
textures img_item_artifact_dagger(&texture_item02, 225, 255);
textures img_item_artifact_katana(&texture_item02, 226, 255);
textures img_item_artifact_scimitar(&texture_item02, 227, 255);
textures img_item_artifact_greatsword(&texture_item02, 228, 255);
textures img_item_artifact_broomstick(&texture_item02, 229, 255);
textures img_item_artifact_handaxe(&texture_item02, 230, 255);
textures img_item_artifact_battleaxe(&texture_item02, 231, 255);
textures img_item_artifact_anchor(&texture_item02, 232, 255);
textures img_item_artifact_spear(&texture_item02, 233, 255);
textures img_item_artifact_scythe(&texture_item02, 234, 255);
textures img_item_artifact_trident(&texture_item02, 235, 255);
textures img_item_artifact_chakram(&texture_item02, 236, 255);
textures img_item_artifact_umbrella(&texture_item02, 237, 255);
textures img_item_artifact_knife(&texture_item02, 238, 255);
textures img_item_artifact_dauzing_rod(&texture_item02, 239, 255);
textures img_item_artifact_javelin(&texture_item02, 207, 255);





textures img_item_food_bread(&texture_item01, 0, 255);
textures img_item_food_p_item(&texture_item01, 63, 255);

textures img_item_potion[] = {textures(&texture_item02, 0, 255),
	textures(&texture_item02, 1, 255),
	textures(&texture_item02, 2, 255),
	textures(&texture_item02, 3, 255),
	textures(&texture_item02, 4, 255),
	textures(&texture_item02, 5, 255),
	textures(&texture_item02, 6, 255),
	textures(&texture_item02, 7, 255),
	textures(&texture_item02, 8, 255),
	textures(&texture_item02, 9, 255),
	textures(&texture_item02, 10, 255),
	textures(&texture_item02, 11, 255),
	textures(&texture_item02, 12, 255),
	textures(&texture_item02, 13, 255),
	textures(&texture_item02, 14, 255),
	textures(&texture_item02, 15, 255),
	textures(&texture_item02, 16, 255),
	textures(&texture_item02, 17, 255),
	textures(&texture_item02, 18, 255),
	textures(&texture_item02, 19, 255)
};


textures img_item_scroll(&texture_item01, 14, 255);

textures img_item_book[] = {textures(&texture_item02, 32, 255),
	textures(&texture_item02, 33, 255),
	textures(&texture_item02, 34, 255),
	textures(&texture_item02, 35, 255),
	textures(&texture_item02, 36, 255),
	textures(&texture_item02, 37, 255),
	textures(&texture_item02, 38, 255)
};


textures img_item_potion_kind[] = { textures(&texture_item02, 48, 255),
textures(&texture_item02, 49, 255),
textures(&texture_item02, 50, 255),
textures(&texture_item02, 51, 255),
textures(&texture_item02, 52, 255),
textures(&texture_item02, 53, 255),
textures(&texture_item02, 54, 255),
textures(&texture_item02, 55, 255),
textures(&texture_item02, 56, 255),
textures(&texture_item02, 57, 255),
textures(&texture_item02, 58, 255),
textures(&texture_item02, 59, 255),
textures(&texture_item02, 60, 255),
textures(&texture_item02, 61, 255),
textures(&texture_item02, 62, 255),
textures(&texture_item02, 63, 255),
textures(&texture_item02, 64, 255) };


textures img_item_spellcard_kind[] = { textures(&texture_item02, 65, 255),
textures(&texture_item02, 66, 255),
textures(&texture_item02, 67, 255),
textures(&texture_item02, 68, 255),
textures(&texture_item02, 69, 255),
textures(&texture_item02, 70, 255),
textures(&texture_item02, 71, 255)};

textures img_item_scroll_kind[] = { textures(&texture_item02, 80, 255),
textures(&texture_item02, 81, 255),
textures(&texture_item02, 82, 255),
textures(&texture_item02, 83, 255),
textures(&texture_item02, 84, 255),
textures(&texture_item02, 85, 255),
textures(&texture_item02, 86, 255),
textures(&texture_item02, 87, 255),
textures(&texture_item02, 88, 255),
textures(&texture_item02, 89, 255),
textures(&texture_item02, 90, 255),
textures(&texture_item02, 91, 255),
textures(&texture_item02, 92, 255),
textures(&texture_item02, 93, 255),
textures(&texture_item02, 94, 255),
textures(&texture_item02, 95, 255),
textures(&texture_item02, 96, 255),
textures(&texture_item02, 97, 255),
textures(&texture_item02, 98, 255),
textures(&texture_item02, 99, 255) };


textures img_item_amulet_kind[] = { textures(&texture_item02, 112, 255),
textures(&texture_item02, 113, 255),
textures(&texture_item02, 114, 255),
textures(&texture_item02, 115, 255),
textures(&texture_item02, 116, 255),
textures(&texture_item02, 117, 255),
textures(&texture_item02, 118, 255),
textures(&texture_item02, 119, 255),
textures(&texture_item02, 120, 255),
textures(&texture_item02, 121, 255)
};

textures img_item_ring_kind[] = { textures(&texture_item02, 128, 255),
textures(&texture_item02, 129, 255),
textures(&texture_item02, 130, 255),
textures(&texture_item02, 131, 255),
textures(&texture_item02, 132, 255),
textures(&texture_item02, 133, 255),
textures(&texture_item02, 134, 255),
textures(&texture_item02, 135, 255),
textures(&texture_item02, 136, 255),
textures(&texture_item02, 137, 255),
textures(&texture_item02, 138, 255),
textures(&texture_item02, 139, 255),
textures(&texture_item02, 140, 255),
textures(&texture_item02, 141, 255),
textures(&texture_item02, 142, 255),
textures(&texture_item02, 143, 255),
textures(&texture_item02, 144, 255),
textures(&texture_item02, 145, 255),
textures(&texture_item02, 146, 255),
textures(&texture_item02, 147, 255),
textures(&texture_item02, 148, 255),//더미
textures(&texture_item02, 149, 255)//더미
};



textures img_item_ring[] = { textures(&texture_item02, 176, 255),
textures(&texture_item02, 177, 255),
textures(&texture_item02, 178, 255),
textures(&texture_item02, 179, 255),
textures(&texture_item02, 180, 255),
textures(&texture_item02, 181, 255),
textures(&texture_item02, 182, 255),
textures(&texture_item02, 183, 255),
textures(&texture_item02, 184, 255),
textures(&texture_item02, 185, 255),
textures(&texture_item02, 186, 255),
textures(&texture_item02, 187, 255),
textures(&texture_item02, 188, 255),
textures(&texture_item02, 189, 255),
textures(&texture_item02, 190, 255),
textures(&texture_item02, 191, 255),
textures(&texture_item02, 192, 255),
textures(&texture_item02, 193, 255),
textures(&texture_item02, 194, 255)
};

textures img_item_artifact_ring(&texture_item02, 197, 255);

textures img_item_goal(&texture_item01, 135, 255);
textures img_item_cat_tree(&texture_item02, 163, 255);
textures img_item_rune(&texture_item01, 214, 255);

textures img_item_amulet(&texture_item01, 16, 255);

textures img_item_needle(&texture_item01, 141, 255);
textures img_item_kikuichi(&texture_item01, 142, 255);
textures img_item_doggojeo(&texture_item02, 172, 255);

textures img_item_spellcard(&texture_item01, 181, 255);
textures img_item_sweet_potato(&texture_item01, 182, 255); 
textures img_item_chocolet(&texture_item02, 164, 255);
textures img_item_cucumber(&texture_item02, 165, 255);
textures img_item_broken_camera(&texture_item02, 166, 255);
textures img_item_kappa_trash(&texture_item02, 167, 255);

textures img_item_skeleton[] = { textures(&texture_item03, 206, 255),
textures(&texture_item03, 207, 255),
textures(&texture_item03, 208, 255)
};

textures img_effect_select(&texture_item01, 1, 255);
textures img_effect_slience(&texture_item01, 111, 255);
textures img_effect_auto_pick(&texture_item01, 143, 255);
textures img_effect_lunatic(&texture_dungeon01, 288, 0, 320, 32, 255);
textures img_effect_freeze(&texture_dungeon01, 320, 0, 352, 32, 255);
textures img_effect_gold(&texture_dungeon01, 352, 0, 384, 32, 255);
textures img_effect_sleep(&texture_dungeon01, 960, 0, 992, 32, 255);
textures img_effect_white(&texture_dungeon01, 992, 0, 1024, 32, 255);
textures img_effect_sion(&texture_dungeon01, 0, 296, 32, 328, 255);


textures img_item_empty_itembox(&texture_item03, 61, 255);
textures img_item_select_itembox(&texture_item03, 62, 255);
textures img_item_equip_itembox(&texture_item03, 63, 255);
textures img_item_curse_itembox(&texture_item03, 64, 255);
textures img_item_evokable_itembox(&texture_item03, 65, 255);
textures img_item_speciel_itembox(&texture_item03, 66, 255);
textures img_item_maycurse_itembox(&texture_item03, 189, 255);

textures img_command_autotravel(&texture_item03, 67, 255);
textures img_command_autoattack(&texture_item03, 68, 255);
textures img_command_100sleep(&texture_item03, 69, 255);
textures img_command_magic(&texture_item03, 70, 255);
textures img_command_skill(&texture_item03, 71, 255);
textures img_command_shout(&texture_item03, 162, 255);
textures img_command_skill_view(&texture_item03, 72, 255);
textures img_command_tanmac_on(&texture_item03, 73, 255);
textures img_command_tanmac_off(&texture_item03, 74, 255);
textures img_command_tanmac_auto(&texture_item03, 75, 255);
textures img_command_pickon(&texture_item03, 76, 255);
textures img_command_pickoff(&texture_item03, 77, 255);
textures img_command_help(&texture_item03, 78, 255);
textures img_command_quit(&texture_item03, 79, 255);
textures img_command_Y(&texture_item03, 80, 255);
textures img_command_N(&texture_item03, 84, 255);
textures img_command_empty(&texture_item03, 83, 255);
textures img_command_X(&texture_item03, 81, 255);
textures img_command_door(&texture_item03, 163, 255);
textures img_command_pray(&texture_item03, 164, 255);
textures img_command_more_item(&texture_item03, 165, 255);
textures img_command_more_view(&texture_item03, 166, 255);
textures img_command_wide_search(&texture_item03, 191, 255);
textures img_command_info_character(&texture_item03, 167, 255);
textures img_command_info_faith(&texture_item03, 168, 255);
textures img_command_info_iden(&texture_item03, 169, 255);
textures img_command_info_property(&texture_item03, 170, 255);
textures img_command_info_spell(&texture_item03, 171, 255);
textures img_command_info_learn_spell(&texture_item03, 172, 255);
textures img_command_info_rune(&texture_item03, 173, 255);
textures img_command_info_dungeon(&texture_item03, 174, 255);
textures img_command_info_log(&texture_item03, 190, 255);
textures img_command_info_dump(&texture_item03, 175, 255);
textures img_command_inventory(&texture_item03, 176, 255);
textures img_command_discard(&texture_item03, 177, 255);
textures img_command_eat(&texture_item03, 178, 255);
textures img_command_read(&texture_item03, 179, 255);
textures img_command_drink(&texture_item03, 180, 255);
textures img_command_throw(&texture_item03, 181, 255);
textures img_command_evoke(&texture_item03, 182, 255);
textures img_command_equip_weapon(&texture_item03, 183, 255);
textures img_command_unequip_weapon(&texture_item03, 184, 255);
textures img_command_equip_armour(&texture_item03, 185, 255);
textures img_command_unequip_armour(&texture_item03, 186, 255);
textures img_command_equip_jewelry(&texture_item03, 187, 255);
textures img_command_unequip_jewelry(&texture_item03, 188, 255);


textures img_command_alphabet_small[26] = {
	textures(&texture_item03, 85, 255),
	textures(&texture_item03, 86, 255),
	textures(&texture_item03, 87, 255),
	textures(&texture_item03, 88, 255),
	textures(&texture_item03, 89, 255),
	textures(&texture_item03, 90, 255),
	textures(&texture_item03, 91, 255),
	textures(&texture_item03, 92, 255),
	textures(&texture_item03, 93, 255),
	textures(&texture_item03, 94, 255),
	textures(&texture_item03, 95, 255),
	textures(&texture_item03, 96, 255),
	textures(&texture_item03, 97, 255),
	textures(&texture_item03, 98, 255),
	textures(&texture_item03, 99, 255),
	textures(&texture_item03, 100, 255),
	textures(&texture_item03, 101, 255),
	textures(&texture_item03, 102, 255),
	textures(&texture_item03, 103, 255),
	textures(&texture_item03, 104, 255),
	textures(&texture_item03, 105, 255),
	textures(&texture_item03, 106, 255),
	textures(&texture_item03, 107, 255),
	textures(&texture_item03, 108, 255),
	textures(&texture_item03, 109, 255),
	textures(&texture_item03, 110, 255)
};


textures img_command_alphabet_large[26]= {
	textures(&texture_item03, 111, 255),
	textures(&texture_item03, 112, 255),
	textures(&texture_item03, 113, 255),
	textures(&texture_item03, 114, 255),
	textures(&texture_item03, 115, 255),
	textures(&texture_item03, 116, 255),
	textures(&texture_item03, 117, 255),
	textures(&texture_item03, 118, 255),
	textures(&texture_item03, 119, 255),
	textures(&texture_item03, 120, 255),
	textures(&texture_item03, 121, 255),
	textures(&texture_item03, 122, 255),
	textures(&texture_item03, 123, 255),
	textures(&texture_item03, 124, 255),
	textures(&texture_item03, 125, 255),
	textures(&texture_item03, 126, 255),
	textures(&texture_item03, 127, 255),
	textures(&texture_item03, 128, 255),
	textures(&texture_item03, 129, 255),
	textures(&texture_item03, 130, 255),
	textures(&texture_item03, 131, 255),
	textures(&texture_item03, 132, 255),
	textures(&texture_item03, 133, 255),
	textures(&texture_item03, 134, 255),
	textures(&texture_item03, 135, 255),
	textures(&texture_item03, 136, 255)
};


textures img_command_number[25]= {
	textures(&texture_item03, 137, 255),
	textures(&texture_item03, 138, 255),
	textures(&texture_item03, 139, 255),
	textures(&texture_item03, 140, 255),
	textures(&texture_item03, 141, 255),
	textures(&texture_item03, 142, 255),
	textures(&texture_item03, 143, 255),
	textures(&texture_item03, 144, 255),
	textures(&texture_item03, 145, 255),
	textures(&texture_item03, 146, 255),
	textures(&texture_item03, 147, 255),
	textures(&texture_item03, 148, 255),
	textures(&texture_item03, 149, 255),
	textures(&texture_item03, 150, 255),
	textures(&texture_item03, 151, 255),
	textures(&texture_item03, 152, 255),
	textures(&texture_item03, 153, 255),
	textures(&texture_item03, 154, 255),
	textures(&texture_item03, 155, 255),
	textures(&texture_item03, 156, 255),
	textures(&texture_item03, 157, 255),
	textures(&texture_item03, 158, 255),
	textures(&texture_item03, 159, 255),
	textures(&texture_item03, 160, 255),
	textures(&texture_item03, 161, 255)
};



textures img_effect_tanmac_middle[] = 
{
	textures(&texture_item01, 57, 255),
	textures(&texture_item01, 58, 255),
	textures(&texture_item01, 59, 255),
	textures(&texture_item01, 60, 255),
	textures(&texture_item01, 61, 255),
	textures(&texture_item01, 62, 255)
};

textures img_hp_graphic[5] = 
{
	textures(&texture_item01, 256, 125, 288, 127, 255),
	textures(&texture_item01, 256, 119, 288, 121, 255),
	textures(&texture_item01, 256, 113, 288, 115, 255),
	textures(&texture_item01, 256, 107, 288, 109, 255),
	textures(&texture_item01, 256, 101, 288, 103, 255)
};

textures img_tanmac_bill[] = {textures(&texture_item01, 17, 255),
							  textures(&texture_item01, 18, 255),
							  textures(&texture_item01, 19, 255),
							  textures(&texture_item01, 20, 255),
							  textures(&texture_item01, 21, 255),
							  textures(&texture_item01, 22, 255),
							  textures(&texture_item01, 23, 255),
							  textures(&texture_item01, 24, 255)
};

textures img_tanmac_amulet[] = {textures(&texture_item01, 25, 255),
							    textures(&texture_item01, 26, 255)
};



textures img_fog_normal[] = {textures(&texture_item01, 64, 255),
							    textures(&texture_item01, 65, 255),
							    textures(&texture_item01, 66, 255),
							    textures(&texture_item01, 67, 255)
};
textures img_fog_fire[] = {textures(&texture_item01, 68, 255),
							    textures(&texture_item01, 69, 255),
							    textures(&texture_item01, 70, 255),
							    textures(&texture_item01, 71, 255)
};
textures img_fog_cold[] = {textures(&texture_item01, 72, 255),
								textures(&texture_item01, 73, 255),
							    textures(&texture_item01, 74, 255),
							    textures(&texture_item01, 75, 255),
};
textures img_fog_dark[] = {textures(&texture_item01, 76, 255),
								textures(&texture_item01, 77, 255),
							    textures(&texture_item01, 78, 255),
							    textures(&texture_item01, 79, 255)
};
textures img_fog_poison[] = {textures(&texture_item01, 80, 255),
							    textures(&texture_item01, 81, 255),
							    textures(&texture_item01, 82, 255),
							    textures(&texture_item01, 83, 255)
};
textures img_fog_slow[] = {textures(&texture_item01, 84, 255),
							    textures(&texture_item01, 85, 255),
							    textures(&texture_item01, 86, 255),
							    textures(&texture_item01, 87, 255)
};
textures img_fog_heavenly_storm[] = {textures(&texture_item03, 209, 255),
	textures(&texture_item03, 210, 255),
	textures(&texture_item03, 211, 255),
	textures(&texture_item03, 212, 255)
};

textures img_fog_sion[3][4] = { {textures(&texture_item03, 13, 255),
textures(&texture_item03, 14, 255),
textures(&texture_item03, 15, 255),
textures(&texture_item03, 16, 255)},

{ textures(&texture_item03, 4, 255),
textures(&texture_item03, 5, 255),
textures(&texture_item03, 6, 255),
textures(&texture_item03, 7, 255) },

{ textures(&texture_item03, 9, 255),
textures(&texture_item03, 10, 255),
textures(&texture_item03, 11, 255),
textures(&texture_item03, 12, 255) }
};





textures img_tanmac_oil_big[] = {textures(&texture_laser, 133, 255),
								textures(&texture_laser, 134, 255),
							    textures(&texture_laser, 135, 255),
							    textures(&texture_laser, 136, 255),
								textures(&texture_laser, 137, 255),
								textures(&texture_laser, 138, 255),
							    textures(&texture_laser, 139, 255),
							    textures(&texture_laser, 140, 255)
};

textures img_tanmac_fire_big[] = {textures(&texture_item01, 88, 255),
								textures(&texture_item01, 89, 255),
							    textures(&texture_item01, 90, 255),
							    textures(&texture_item01, 91, 255),
								textures(&texture_item01, 92, 255),
								textures(&texture_item01, 93, 255),
							    textures(&texture_item01, 94, 255),
							    textures(&texture_item01, 95, 255)
};
textures img_tanmac_fire_small[] = {textures(&texture_item01, 96, 255),
							    textures(&texture_item01, 97, 255),
							    textures(&texture_item01, 98, 255),
							    textures(&texture_item01, 99, 255),
								textures(&texture_item01, 100, 255),
							    textures(&texture_item01, 101, 255),
							    textures(&texture_item01, 102, 255),
							    textures(&texture_item01, 103, 255)
};
textures img_tanmac_ice[] = {textures(&texture_item01, 104, 255),
								textures(&texture_item01, 105, 255),
							    textures(&texture_item01, 106, 255),
							    textures(&texture_item01, 107, 255)
};
textures img_tanmac_ice_big[] = {textures(&texture_item01, 160, 255),
							    textures(&texture_item01, 161, 255),
							    textures(&texture_item01, 162, 255),
							    textures(&texture_item01, 163, 255),
								textures(&texture_item01, 164, 255),
							    textures(&texture_item01, 165, 255),
							    textures(&texture_item01, 166, 255),
							    textures(&texture_item01, 167, 255)
};
textures img_tanmac_ice_small[] = {textures(&texture_item01, 112, 255),
							    textures(&texture_item01, 113, 255),
							    textures(&texture_item01, 114, 255),
							    textures(&texture_item01, 115, 255),
								textures(&texture_item01, 116, 255),
							    textures(&texture_item01, 117, 255),
							    textures(&texture_item01, 118, 255),
							    textures(&texture_item01, 119, 255)
};
textures img_tanmac_poison_big[] = {textures(&texture_item01, 152, 255),
								textures(&texture_item01, 153, 255),
							    textures(&texture_item01, 154, 255),
							    textures(&texture_item01, 155, 255),
								textures(&texture_item01, 156, 255),
								textures(&texture_item01, 157, 255),
							    textures(&texture_item01, 158, 255),
							    textures(&texture_item01, 159, 255)
};
textures img_tanmac_poison_small[] = {textures(&texture_item01, 144, 255),
							    textures(&texture_item01, 145, 255),
							    textures(&texture_item01, 146, 255),
							    textures(&texture_item01, 147, 255),
								textures(&texture_item01, 148, 255),
							    textures(&texture_item01, 149, 255),
							    textures(&texture_item01, 150, 255),
							    textures(&texture_item01, 151, 255)
};

textures img_tanmac_air[] ={textures(&texture_item01, 184, 255),
								textures(&texture_item01, 185, 255),
							    textures(&texture_item01, 186, 255),
							    textures(&texture_item01, 187, 255),
								textures(&texture_item01, 188, 255),
								textures(&texture_item01, 189, 255),
							    textures(&texture_item01, 190, 255),
							    textures(&texture_item01, 191, 255)

};
textures img_tanmac_rock_small[] = {textures(&texture_item01, 192, 255),
								textures(&texture_item01, 193, 255),
							    textures(&texture_item01, 194, 255),
							    textures(&texture_item01, 195, 255),
								textures(&texture_item01, 196, 255),
								textures(&texture_item01, 197, 255),
							    textures(&texture_item01, 198, 255),
							    textures(&texture_item01, 199, 255)
};
textures img_tanmac_rock_big[] = {textures(&texture_item01, 200, 255),
								textures(&texture_item01, 201, 255),
							    textures(&texture_item01, 202, 255),
							    textures(&texture_item01, 203, 255),
								textures(&texture_item01, 204, 255),
								textures(&texture_item01, 205, 255),
							    textures(&texture_item01, 206, 255),
							    textures(&texture_item01, 207, 255)
};
textures img_tanmac_doggojeo[] = { textures(&texture_item02, 208, 255),
								textures(&texture_item02, 209, 255),
								textures(&texture_item02, 210, 255),
								textures(&texture_item02, 211, 255),
								textures(&texture_item02, 212, 255),
								textures(&texture_item02, 213, 255),
								textures(&texture_item02, 214, 255),
								textures(&texture_item02, 215, 255)
};

textures img_tanmac_sion[] = { textures(&texture_item03, 17, 255),
textures(&texture_item03, 18, 255),
textures(&texture_item03, 19, 255),
textures(&texture_item03, 20, 255),
textures(&texture_item03, 21, 255),
textures(&texture_item03, 22, 255),
textures(&texture_item03, 23, 255),
textures(&texture_item03, 24, 255)
};

textures img_tanmac_master_spark[] = { textures(&texture_item03, 37, 255),
textures(&texture_item03, 38, 255),
textures(&texture_item03, 39, 255),
textures(&texture_item03, 40, 255),
textures(&texture_item03, 41, 255),
textures(&texture_item03, 42, 255),
textures(&texture_item03, 43, 255),
textures(&texture_item03, 44, 255)
};

textures img_tanmac_sword[] = { textures(&texture_item03, 45, 255),
textures(&texture_item03, 46, 255),
textures(&texture_item03, 47, 255),
textures(&texture_item03, 48, 255),
textures(&texture_item03, 49, 255),
textures(&texture_item03, 50, 255),
textures(&texture_item03, 51, 255),
textures(&texture_item03, 52, 255)
};
textures img_tanmac_knife[] = { textures(&texture_item03, 53, 255),
textures(&texture_item03, 54, 255),
textures(&texture_item03, 55, 255),
textures(&texture_item03, 56, 255),
textures(&texture_item03, 57, 255),
textures(&texture_item03, 58, 255),
textures(&texture_item03, 59, 255),
textures(&texture_item03, 60, 255)
};
textures img_tanmac_missle[] = { textures(&texture_item03, 215, 255),
textures(&texture_item03, 216, 255),
textures(&texture_item03, 217, 255),
textures(&texture_item03, 218, 255),
textures(&texture_item03, 219, 255),
textures(&texture_item03, 220, 255),
textures(&texture_item03, 221, 255),
textures(&texture_item03, 222, 255)
};






textures img_tanmac_small[6][4] =
{
	{textures(&texture_laser, 36, 255),textures(&texture_laser, 37, 255),textures(&texture_laser, 38, 255), textures(&texture_laser, 39, 255)},
	{textures(&texture_laser, 40, 255),textures(&texture_laser, 41, 255),textures(&texture_laser, 42, 255), textures(&texture_laser, 43, 255)},
	{textures(&texture_laser, 44, 255),textures(&texture_laser, 45, 255),textures(&texture_laser, 46, 255), textures(&texture_laser, 47, 255)},
	{textures(&texture_laser, 48, 255),textures(&texture_laser, 49, 255),textures(&texture_laser, 50, 255), textures(&texture_laser, 51, 255)},
	{textures(&texture_laser, 52, 255),textures(&texture_laser, 53, 255),textures(&texture_laser, 54, 255), textures(&texture_laser, 55, 255)},
	{textures(&texture_laser, 56, 255),textures(&texture_laser, 57, 255),textures(&texture_laser, 58, 255), textures(&texture_laser, 59, 255)}
};


textures img_joypad_arrow[] = {textures(&texture_item03, 198, 255),
								textures(&texture_item03, 199, 255),
							    textures(&texture_item03, 200, 255),
							    textures(&texture_item03, 201, 255),
								textures(&texture_item03, 202, 255),
								textures(&texture_item03, 203, 255),
							    textures(&texture_item03, 204, 255),
							    textures(&texture_item03, 205, 255)
};



textures img_blizzard[] = {textures(&texture_item01, 215, 255),
							    textures(&texture_item01, 216, 255),
								textures(&texture_item01, 217, 255),
								textures(&texture_item01, 218, 255)};


textures img_fog_tonado[] = {textures(&texture_laser, 96, 255),
							    textures(&texture_laser, 97, 255),
								textures(&texture_laser, 98, 255),
								textures(&texture_laser, 99, 255)};
textures img_blast[] = {textures(&texture_laser, 100, 255),
							    textures(&texture_laser, 101, 255),
								textures(&texture_laser, 102, 255),
								textures(&texture_laser, 103, 255),
								textures(&texture_laser, 104, 255),
								textures(&texture_laser, 105, 255),
								textures(&texture_laser, 132, 255)};
textures img_autumn_edge[] = { textures(&texture_laser, 106, 255),
			textures(&texture_laser, 107, 255),
			textures(&texture_laser, 108, 255),
			textures(&texture_laser, 109, 255),
			textures(&texture_laser, 110, 255),
			textures(&texture_laser, 111, 255),
			textures(&texture_laser, 112, 255),
			textures(&texture_laser, 113, 255) };


textures img_fog_thunder[] = {textures(&texture_item01, 232, 255),
							    textures(&texture_item01, 233, 255),
								textures(&texture_item01, 234, 255),
								textures(&texture_item01, 235, 255)};


textures img_laser[] = {textures(&texture_laser, 0, 255),
							    textures(&texture_laser, 1, 255),
							    textures(&texture_laser, 2, 255),
							    textures(&texture_laser, 3, 255),
								textures(&texture_laser, 4, 255),
							    textures(&texture_laser, 5, 255),
							    textures(&texture_laser, 6, 255),
							    textures(&texture_laser, 7, 255),
								textures(&texture_laser, 8, 255),
								textures(&texture_laser, 9, 255),
							    textures(&texture_laser, 10, 255),
							    textures(&texture_laser, 11, 255),
								textures(&texture_laser, 12, 255),
								textures(&texture_laser, 13, 255),
							    textures(&texture_laser, 14, 255),
							    textures(&texture_laser, 15, 255),
								textures(&texture_laser, 16, 255),
							    textures(&texture_laser, 17, 255),
							    textures(&texture_laser, 18, 255),
							    textures(&texture_laser, 19, 255),
								textures(&texture_laser, 20, 255),
							    textures(&texture_laser, 21, 255),
							    textures(&texture_laser, 22, 255),
							    textures(&texture_laser, 23, 255),
								textures(&texture_laser, 24, 255),
								textures(&texture_laser, 25, 255),
							    textures(&texture_laser, 26, 255),
							    textures(&texture_laser, 27, 255),
								textures(&texture_laser, 28, 255),
								textures(&texture_laser, 29, 255),
							    textures(&texture_laser, 30, 255),
							    textures(&texture_laser, 31, 255)
};





textures img_thunder[] = {textures(&texture_laser, 64, 255),
							    textures(&texture_laser, 65, 255),
							    textures(&texture_laser, 66, 255),
							    textures(&texture_laser, 67, 255),
								textures(&texture_laser, 68, 255),
							    textures(&texture_laser, 69, 255),
							    textures(&texture_laser, 70, 255),
							    textures(&texture_laser, 71, 255),
								textures(&texture_laser, 72, 255),
								textures(&texture_laser, 73, 255),
							    textures(&texture_laser, 74, 255),
							    textures(&texture_laser, 75, 255),
								textures(&texture_laser, 76, 255),
								textures(&texture_laser, 77, 255),
							    textures(&texture_laser, 78, 255),
							    textures(&texture_laser, 79, 255),
								textures(&texture_laser, 80, 255),
							    textures(&texture_laser, 81, 255),
							    textures(&texture_laser, 82, 255),
							    textures(&texture_laser, 83, 255),
								textures(&texture_laser, 84, 255),
							    textures(&texture_laser, 85, 255),
							    textures(&texture_laser, 86, 255),
							    textures(&texture_laser, 87, 255),
								textures(&texture_laser, 88, 255),
								textures(&texture_laser, 89, 255),
							    textures(&texture_laser, 90, 255),
							    textures(&texture_laser, 91, 255),
								textures(&texture_laser, 92, 255),
								textures(&texture_laser, 93, 255),
							    textures(&texture_laser, 94, 255),
							    textures(&texture_laser, 95, 255)

};

textures img_border[] = {textures(&texture_laser, 116, 255),
	textures(&texture_laser, 117, 255),
	textures(&texture_laser, 118, 255),
	textures(&texture_laser, 119, 255),
	textures(&texture_laser, 120, 255),
	textures(&texture_laser, 121, 255),
	textures(&texture_laser, 122, 255),
	textures(&texture_laser, 123, 255),
	textures(&texture_laser, 124, 255),
	textures(&texture_laser, 125, 255),
	textures(&texture_laser, 126, 255),
	textures(&texture_laser, 127, 255),
	textures(&texture_laser, 128, 255),
	textures(&texture_laser, 129, 255),
	textures(&texture_laser, 130, 255),
	textures(&texture_laser, 131, 255)
};


textures img_laser_small[] = {
	textures(&texture_laser, 32, 255),
	textures(&texture_laser, 33, 255),
	textures(&texture_laser, 34, 255),
	textures(&texture_laser, 35, 255)
};

textures img_effect_autumn_leave[] = {
	textures(&texture_item01, 169, 255),
	textures(&texture_item01, 170, 255),
	textures(&texture_item01, 171, 255),
	textures(&texture_item01, 172, 255)
};

textures img_effect_gold_floor[] = {
	textures(&texture_item03, 0, 255),
	textures(&texture_item03, 1, 255),
	textures(&texture_item03, 2, 255)
};

textures img_mon_kaguya_quiz[] = {
	textures(&texture_item03, 32, 255),
	textures(&texture_item03, 33, 255),
	textures(&texture_item03, 34, 255),
	textures(&texture_item03, 35, 255),
	textures(&texture_item03, 36, 255)
};



textures img_effect_rock_trap(&texture_item01, 183, 255);
textures img_effect_halo(&texture_laser, 114, 255);
textures img_effect_veiling(&texture_laser, 115, 255);

textures img_effect_sun(&texture_dungeon01, 349);
textures img_effect_rain(&texture_dungeon01, 350);
textures img_effect_fog(&texture_dungeon01, 351);

textures img_effect_rock_uplift[] = {
	textures(&texture_item01, 208, 255),
	textures(&texture_item01, 209, 255),
	textures(&texture_item01, 210, 255),
	textures(&texture_item01, 211, 255),
	textures(&texture_item01, 212, 255)	
};

textures img_effect_emerald_uplift[] = {
	textures(&texture_item01, 237, 255),
	textures(&texture_item01, 238, 255)
};



textures img_effect_schema[] = {
	textures(&texture_monster01, 135, 255),
	textures(&texture_monster01, 136, 255),
	textures(&texture_monster01, 137, 255)
	
};


textures img_state_sleep(&texture_item01, 27, 255);
textures img_state_wardering(&texture_item01, 28, 255);
textures img_state_confuse(&texture_item01, 29, 255);
textures img_state_poison(&texture_item01, 30, 255);
textures img_state_paralysis(&texture_item01, 31, 255);
textures img_state_scary(&texture_item01, 32, 255);
textures img_state_ally(&texture_item01, 108, 255);
textures img_state_summon(&texture_item01, 109, 255);
textures img_state_haste(&texture_item01, 110, 255);
textures img_state_lunatic(&texture_item01, 219, 255);
textures img_state_slow(&texture_item01, 239, 255);
textures img_state_neutral(&texture_item03, 194, 255);
textures img_state_calling(&texture_item03, 213, 255);

textures dot_floor(&texture_dot_floor, 0, 0, 1, 1, 255);
textures dot_wall(&texture_dot_wall, 0, 0, 1, 1, 255);
textures dot_monster(&texture_dot_monster, 0, 0, 1, 1, 255);
textures dot_player(&texture_dot_player, 0, 0, 1, 1, 255);
textures dot_up(&texture_dot_up, 0, 0, 1, 1, 255);
textures dot_down(&texture_dot_down, 0, 0, 1, 1, 255);
textures dot_item(&texture_dot_item, 0, 0, 1, 1, 255);
textures dot_door(&texture_dot_door, 0, 0, 1, 1, 255);
textures dot_temple(&texture_dot_temple, 0, 0, 1, 1, 255);
textures dot_sea(&texture_dot_sea, 0, 0, 1, 1, 255);
textures dot_mapping_floor(&texture_dot_mapping_floor, 0, 0, 1, 1, 255);
textures dot_mapping_wall(&texture_dot_mapping_wall, 0, 0, 1, 1, 255);
textures sight_rect(&texture_sight_rect, 0, 0, 64, 64, 255);
textures explore_forbid_small(&texture_item02, 217, 255);
textures explore_forbid_big(&texture_item02, 216, 255);

//-----------------------------------------------------------
//TextureFile 클래스
//-----------------------------------------------------------

//TextureFile 클래스의 생성자
TextureFile::TextureFile(LPCSTR _name)
{
	name = _name;
	pTexture = NULL;
}

//TextureFile 클래스의 소멸자
TextureFile::~TextureFile()
{
	if(pTexture) {
		pTexture->Release();
		pTexture = nullptr;
	}
}

//로딩
bool TextureFile::loading(ID3D11Device* device, ID3D11DeviceContext* context)
{
    struct stat st = {};
    if (stat(name, &st) == -1) {
        return false;
	}
	std::wstring wname = ConvertUTF8ToUTF16(name);

    HRESULT hr = DirectX::CreateWICTextureFromFileEx(
        device,
        context,
		wname.c_str(),
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		DirectX::WIC_LOADER_FORCE_SRGB,
        nullptr,
        &pTexture
    );

    return SUCCEEDED(hr);
}

//-----------------------------------------------------------
//textures 클래스
//-----------------------------------------------------------

//textures 클래스의 생성자
textures::textures(TextureFile* _texture, int left, int top, int right, int bottom, int alphas)
{
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	alpha = alphas;
	texture = _texture; 
	normal = false;
}
textures::textures(TextureFile* _texture, int mon_num, int alphas)
{
	rect.left = (mon_num%16)*32;
	rect.top = (mon_num/16)*33;
	rect.right = (mon_num%16)*32+32;
	rect.bottom = (mon_num/16)*33+32;
	alpha = alphas;
	texture = _texture;
	normal = false;
}
textures::textures(TextureFile* _texture, int mon_num)
{
	rect.left = (mon_num % 32) * 32;
	rect.top = (mon_num / 32) * 33;
	rect.right = (mon_num % 32) * 32 + 32;
	rect.bottom = (mon_num / 32) * 33 + 32;
	alpha = 255;
	texture = _texture;
	normal = false;
}
textures::textures(TextureFile* _texture)
{
	rect.left = (0 % 16) * 32;
	rect.top = (0 / 16) * 33;
	rect.right = (0 % 16) * 32 + 32;
	rect.bottom = (0 / 16) * 33 + 32;
	alpha = 255;
	texture = _texture;
	normal = true;
}


//textures 클래스의 소멸자
textures::~textures()
{
}

//드로우(배경)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, int alphas)
{
	if(!texture)
		return true;
    float x = static_cast<float>(option_mg.getWidth()) / 2.0f;
    float y = static_cast<float>(option_mg.getHeight()) / 2.0f;

    return SpriteDraw(
        pSprite,
        rect,
        1.0f, 1.0f,  // scale
        0.0f,        // rotation
        x, y,
        texture->pTexture,
        D3DCOLOR_RGBA(255, 255, 255, alphas)
    );
}

//드로우(위치)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, int alphas)
{	
	if(!texture)
		return true;
	return SpriteDraw(
		pSprite,
		rect,
		1.0f, 1.0f,        // scale x/y
		0.0f,              // rotation
		x, y,              // position
		texture->pTexture,
		D3DCOLOR_RGBA(255, 255, 255, alphas)
	);
}
//드로우(위치,색깔)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, D3DCOLOR color)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, 1.0f, 1.0f, 0.0f, x, y, texture->pTexture,color);
	
	return true;
}

//드로우(위치, 회전)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, float rotation, int alphas)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, 1.0f, 1.0f, rotation, x, y, texture->pTexture,D3DCOLOR_RGBA(255,255,255,alphas));
	
	return true;
}


//드로우(위치, 회전, 크기)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, float rotation, float scale_x, float scale_y, int alphas)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, scale_x, scale_y, rotation, x, y, texture->pTexture,D3DCOLOR_RGBA(255,255,255,alphas));
	
	return true;
}

//드로우(위치, 회전, 크기,색깔)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, float x, float y, float rotation, float scale_x, float scale_y, D3DCOLOR color)
{
	if(!texture)
		return true;
	SpriteDraw(pSprite, rect, scale_x, scale_y, rotation, x, y, texture->pTexture,color);
	
	return true;
}


//드로우(배경, 특정 잘라쓰기)
bool textures::draw(shared_ptr<DirectX::SpriteBatch> pSprite, RECT rc, int alphas)
{
	if(!texture)
		return true;
	float x = static_cast<float>(option_mg.getWidth()) / 2.0f;
	float y = static_cast<float>(option_mg.getHeight()) / 2.0f;

	return SpriteDraw(
		pSprite,
		rc,
		1.0f, 1.0f,         // scale
		0.0f,               // rotation
		x, y,
		texture->pTexture,
		D3DCOLOR_RGBA(255, 255, 255, alphas)
	);
}


int texturetoint(textures* input)
{
	if (input == NULL)
		return -1;

	if(input == &img_mons_default)
		return 0;
	else if(input == &img_mons_reimu_yukkuri)
		return 1;
	else if(input == &img_play_reimu)
		return 2;
	else if(input == &img_item_armor_robe)
		return 3;
	else if(input == &img_item_armor_cloak)
		return 4;
	else if(input == &img_item_armor_robe_sanae)
		return 5;
	else if(input == &img_item_armor_glove)
		return 6;
	else if(input == &img_item_armor_boot)
		return 7;
	else if(input == &img_item_armor_helmet[1])
		return 8;
	else if(input == &img_item_weapon_dagger)
		return 9;
	else if(input == &img_item_food_bread)
		return 10;
	else if(input == &img_item_potion[0])
		return 11;
	else if(input == &img_item_scroll)
		return 12;
	else if(input == &img_item_ring[0])
		return 13;
	else if(input == &img_item_amulet)
		return 14;
	else if(input == &img_effect_select)
		return 15;
	else if(input == &img_tanmac_bill[1])
		return 16;
	else if(input == &img_tanmac_amulet[0])
		return 17;
	else if(input == &img_item_weapon_gohey)
		return 18;
	else if(input == &img_item_weapon_katana)
		return 19;
	else if(input == &img_item_weapon_scimitar)
		return 20;
	else if(input == &img_item_weapon_greatsword)
		return 21;
	else if(input == &img_item_weapon_broomstick)
		return 22;
	else if(input == &img_item_weapon_handaxe)
		return 23;
	else if(input == &img_item_weapon_battleaxe)
		return 24;
	else if(input == &img_item_weapon_anchor)
		return 25;
	else if(input == &img_item_weapon_spear)
		return 26;
	else if(input == &img_item_weapon_scythe)
		return 27;
	else if(input == &img_item_weapon_trident)
		return 28;
	else if(input == &img_item_weapon_smalllance)
		return 29;
	else if(input == &img_item_weapon_umbrella)
		return 30;
	else if(input == &img_item_weapon_knife)
		return 31;
	else if(input == &img_item_weapon_shortsword)
		return 32;
	else if(input == &img_item_weapon_gohey2)
		return 33;
	else if(input == &img_item_weapon_hammer)
		return 34;
	else if(input == &img_item_weapon_onbasira)
		return 35;
	else if(input == &img_item_weapon_roundshield)
		return 36;
	if(input == &img_item_weapon_shield)
		return 37;
	else if(input == &img_item_weapon_momizishield)
		return 38;
	else if(input == &img_item_weapon_kiteshield)
		return 39;
	else if(input == &img_mons_rat)
		return 40;
	else if(input == &img_mons_fairy_green)
		return 41;
	else if(input == &img_mons_fairy_blue)
		return 42;
	else if(input == &img_mons_fairy_red)
		return 43;
	else if(input == &img_mons_mook)
		return 44;
	else if(input == &img_mons_crow)
		return 45;
	else if(input == &img_mons_crane)
		return 46;
	else if(input == &img_mons_spider)
		return 47;
	else if(input == &img_mons_snake)
		return 48;
	else if(input == &img_mons_katpa)
		return 49;
	else if(input == &img_mons_katpa_gun)
		return 50;
	else if(input == &img_mons_fairy_green_warroir)
		return 51;
	else if(input == &img_mons_fairy_blue_magician)
		return 52;
	else if(input == &img_mons_fairy_red_commander)
		return 53;
	else if(input == &img_named_rumia)
		return 54;
	else if(input == &img_named_mistia)
		return 55;
	else if(input == &img_named_wriggle)
		return 56;
	else if(input == &img_named_cirno)
		return 57;
	else if(input == &img_item_food_p_item)
		return 58;
	else if(input == &img_fog_normal[0])
		return 59;
	else if(input == &img_fog_fire[0])
		return 60;
	else if(input == &img_fog_cold[0])
		return 61;
	else if(input == &img_fog_dark[0])
		return 62;
	else if(input == &img_fog_poison[0])
		return 63;
	else if(input == &img_fog_slow[0])
		return 64;
	else if(input == &img_mons_human_woman)
		return 65;
	else if(input == &img_mons_human_man)
		return 66;
	else if(input == &img_mons_human_yinyang)
		return 67;
	else if(input == &img_mons_human_priest)
		return 68;
	else if(input == &img_mons_human_samuri)
		return 69;
	else if(input == &img_mons_firefly)
		return 70;
	else if(input == &img_mons_butterfly)
		return 71;
	else if(input == &img_named_medicine)
		return 72;
	else if(input == &img_named_diefairy)
		return 73;
	else if(input == &img_tanmac_fire_big[1])
		return 74;
	else if(input == &img_tanmac_fire_small[1])
		return 75;
	else if(input == &img_tanmac_ice[0])
		return 76;
	else if(input == &img_tanmac_ice_small[0])
		return 77;
	else if(input == &img_item_goal)
		return 78;
	else if(input == &img_play_marisa)
		return 79;
	else if(input == &img_play_sanae)
		return 80;
	else if(input == &img_item_armor_armour_0)
		return 81;
	else if(input == &img_item_armor_armour_1)
		return 82;
	else if(input == &img_item_armor_armour_2)
		return 83;
	else if(input == &img_item_armor_armour_3)
		return 84;	
	else if(input == &img_item_book[0])
		return 85;
	else if(input == &img_tanmac_ice_small[0])
		return 86;
	else if(input == &img_mons_ghost[0])
		return 87;
	else if(input == &img_mons_ghost[1])
		return 88;
	else if(input == &img_mons_ghost[2])
		return 89;
	else if(input == &img_mons_bakekasa)
		return 90;
	else if(input == &img_mons_green_mook)
		return 91;
	else if(input == &img_mons_orange_mook)
		return 92;
	else if(input == &img_mons_gray_mook)
		return 93;
	else if(input == &img_mons_frog)
		return 94;
	else if(input == &img_mons_black_cat)
		return 95;
	else if(input == &img_mons_orange_cat)
		return 96;
	else if(input == &img_mons_white_cat)
		return 97;
	else if(input == &img_mons_crow_tengu)
		return 98;
	else if(input == &img_mons_oni)
		return 99;
	else if(input == &img_mons_marisa_yukkuri)
		return 100;
	else if(input == &img_mons_aya_yukkuri)
		return 101;
	else if(input == &img_named_kisume)
		return 102;
	else if(input == &img_named_chen)
		return 103;
	else if(input == &img_named_kogasa)
		return 104;
	else if(input == &img_named_sunny)
		return 105;
	else if(input == &img_named_lunar)
		return 106;
	else if(input == &img_named_star)
		return 107;
	else if(input == &img_tanmac_ice_big[0])
		return 108;
	else if(input == &img_tanmac_poison_big[0])
		return 109;
	else if(input == &img_mons_remila_yukkuri)
		return 110;
	else if(input == &img_mons_alice_yukkuri)
		return 111;
	else if(input == &img_mons_yamabiko)
		return 112;
	else if(input == &img_mons_katpa_spear)
		return 113;
	else if(input == &img_mons_katpa_water_wizard)
		return 114;
	else if(input == &img_mons_yamabush_tengu)
		return 115;
	else if(input == &img_mons_hanataca_tengu)
		return 116;
	else if(input == &img_mons_blue_oni)
		return 117;
	else if(input == &img_mons_mushroom)
		return 118;
	else if(input == &img_named_kyouko)
		return 119;
	else if(input == &img_named_momizi)
		return 120;
	else if(input == &img_named_aya)
		return 121;
	else if(input == &img_mons_new_kappa)
		return 122;
	else if(input == &img_mons_new_kappa_spear)
		return 123;
	else if(input == &img_mons_new_kappa_wizard)
		return 124;
	// else if(input == &img_mons_test)
	// 	return 125;
	else if(input == &img_mons_magic_book[0])
		return 126;
	else if(input == &img_mons_magic_book[1])
		return 127;
	else if(input == &img_mons_magic_book[2])
		return 128;
	else if(input == &img_mons_magic_book[3])
		return 129;
	else if(input == &img_mons_hobgobrin)
		return 130;
	else if(input == &img_mons_hobgobrin_maid)
		return 131;
	else if(input == &img_mons_hobgobrin_librarian)
		return 132;
	else if(input == &img_mons_hobgobrin_temp)
		return 133;
	else if(input == &img_mons_maid_fairy)
		return 134;
	else if(input == &img_mons_chuparcabra)
		return 135;
	else if(input == &img_mons_eagle)
		return 136;
	else if(input == &img_mons_tiger)
		return 137;
	else if(input == &img_mons_raijuu)
		return 138;
	else if(input == &img_mons_dragon_baby)
		return 139;
	else if(input == &img_mons_yamawaro_ninja)
		return 140;
	else if(input == &img_mons_yamawaro_warrior)
		return 141;
	else if(input == &img_mons_yamawaro_flag)
		return 142;
	else if(input == &img_named_wakasagi)
		return 143;
	else if(input == &img_named_yamame)
		return 144;
	else if(input == &img_named_nazrin)
		return 145;
	else if(input == &img_mons_dauzing)
		return 146;
	else if(input == &img_named_yosika)
		return 147;
	else if(input == &img_named_sekibanki)
		return 148;
	else if(input == &img_named_sekibanki_body)
		return 149;
	else if(input == &img_named_sekibanki_head)
		return 150;
	else if(input == &img_named_nitori)
		return 151;
	else if(input == &img_named_kagero)
		return 152;
	else if(input == &img_named_parsi)
		return 153;
	else if(input == &img_named_benben)
		return 154;
	else if(input == &img_named_yathasi)
		return 155;
	else if(input == &img_named_orin)
		return 156;
	else if(input == &img_named_orin_cat)
		return 157;
	else if(input == &img_mons_zombiefairy)
		return 158;
	else if(input == &img_named_ichirin)
		return 159;
	if(input == &img_named_unzan)
		return 160;
	else if(input == &img_named_unzan_punch[0])
		return 161;
	else if(input == &img_named_unzan_punch[1])
		return 162;
	else if(input == &img_named_unzan_punch[2])
		return 163;
	else if(input == &img_named_unzan_punch[3])
		return 164;
	else if(input == &img_named_pachu)
		return 165;
	else if(input == &img_named_koakuma)
		return 166;
	else if(input == &img_named_meirin)
		return 167;
	else if(input == &img_named_sakuya)
		return 168;
	else if(input == &img_named_remilia)
		return 169;
	else if(input == &img_named_kasen)
		return 170;
	else if(input == &img_effect_autumn_leave[0])
		return 171;
	else if(input == &img_effect_autumn_leave[1])
		return 172;
	else if(input == &img_effect_autumn_leave[2])
		return 173;
	else if(input == &img_effect_autumn_leave[3])
		return 174;
	else if(input == &img_item_autumn_armour[0])
		return 175;
	else if(input == &img_item_autumn_armour[1])
		return 176;
	else if(input == &img_item_autumn_armour[2])
		return 177;
	else if(input == &img_item_autumn_armour[3])
		return 178;
	else if(input == &img_item_autumn_armour[4])
		return 179;
	else if(input == &img_tanmac_air[0])
		return 180;
	else if(input == &img_tanmac_rock_small[0])
		return 181;
	else if(input == &img_mons_option)
		return 182;
	else if(input == &img_mons_golem)
		return 183;
	else if(input == &img_mons_onbasira)
		return 184;
	else if(input == &img_item_needle)
		return 185;
	else if(input == &img_item_kikuichi)
		return 186;
	else if(input == &img_item_spellcard)
		return 187;
	else if(input == &img_item_sweet_potato)
		return 188;	
	else if(input == &img_mons_red_ufo)
		return 189;
	else if(input == &img_mons_blue_ufo)
		return 190;
	else if(input == &img_mons_green_ufo)
		return 191;
	else if(input == &img_named_koishi)
		return 192;
	else if(input == &img_named_nue)
		return 193;
	else if(input == &img_mons_sanpei_fighter)
		return 194;
	else if(input == &img_mons_vamp_bat)
		return 195;
	else if(input == &img_mons_dagama)
		return 196;
	else if(input == &img_play_momizi)
		return 197;
	else if(input == &img_play_normal)
		return 198;
	else if(input == &img_tanmac_rock_big[0])
		return 199;
	else if(input == &img_effect_rock_trap)
		return 200;
	else if(input == &img_effect_rock_uplift[0])
		return 201;
	else if(input == &img_effect_rock_uplift[1])
		return 202;
	else if(input == &img_effect_rock_uplift[2])
		return 203;
	else if(input == &img_effect_rock_uplift[3])
		return 204;
	else if(input == &img_effect_rock_uplift[4])
		return 205;
	else if(input == &img_mons_rabit)
		return 206;
	else if(input == &img_mons_youkai_rabit)
		return 207;
	else if(input == &img_mons_namaz)
		return 208;
	else if(input == &img_mons_hell_crow)
		return 209;
	else if(input == &img_mons_raccoon)
		return 210;
	else if(input == &img_mons_lantern_youkai)
		return 211;
	else if(input == &img_mons_yinyan)
		return 212;
	else if(input == &img_mons_yugenmagan)
		return 213;
	else if(input == &img_mons_elise)
		return 214;
	else if(input == &img_mons_sariel)
		return 215;
	else if(input == &img_mons_sara)
		return 216;
	else if(input == &img_mons_louise)
		return 217;
	else if(input == &img_mons_yuki)
		return 218;
	else if(input == &img_mons_mai)
		return 219;
	else if(input == &img_mons_yumeko)
		return 220;
	else if(input == &img_mons_evil_eye)
		return 221;
	else if(input == &img_mons_little_imp)
		return 222;
	else if(input == &img_mons_schema_eye)
		return 223;
	else if(input == &img_effect_schema[0])
		return 224;
	else if(input == &img_effect_schema[1])
		return 225;
	else if(input == &img_effect_schema[2])
		return 226;	
	else if(input == &img_mons_bomb_rabbit)
		return 227;
	else if(input == &img_mons_spear_rabbit)
		return 228;
	else if(input == &img_mons_support_rabbit)
		return 229;
	else if(input == &img_mons_magic_rabbit)
		return 230;
	else if(input == &img_named_flandre)
		return 231;
	else if(input == &img_named_tewi)
		return 232;
	else if(input == &img_named_clownpiece)
		return 233;
	else if(input == &img_named_doremi)
		return 234;
	else if(input == &img_item_rune)
		return 235;
	else if(input == &img_blizzard[0])
		return 236;
	else if(input == &img_named_seiran)
		return 237;
	else if(input == &img_named_ringo)
		return 238;
	else if(input == &img_mons_fairy_green_hero)
		return 239;
	else if(input == &img_mons_fairy_green_socerer)
		return 240;
	else if(input == &img_mons_fairy_green_himawari)
		return 241;
	else if(input == &img_mons_moon_rabbit_attack)
		return 242;
	else if(input == &img_mons_moon_rabbit_supporter)
		return 243;
	else if(input == &img_mons_moon_rabbit_elite)
		return 244;
	else if(input == &img_mons_mac)
		return 245;
	else if(input == &img_mons_nightmare)
		return 246;
	else if(input == &img_mons_lunatic)
		return 247;
	else if(input == &img_mons_haunt[0])
		return 248;
	else if(input == &img_mons_haunt[1])
		return 249;
	else if(input == &img_mons_haunt[2])
		return 250;
	else if(input == &img_mons_fire_car)
		return 251;
	else if(input == &img_mons_hell_spider)
		return 252;
	else if(input == &img_mons_blood_haunt)
		return 253;
	else if(input == &img_mons_hell_dog)
		return 254;
	else if(input == &img_mons_flower_tank[0])
		return 255;
	else if(input == &img_mons_flower_tank[1])
		return 256;
	else if(input == &img_mons_evil_eye_tank)
		return 257;
	else if(input == &img_mons_snow_girl)
		return 258;
	else if(input == &img_named_letty)
		return 259;
	else if(input == &img_named_yorihime)
		return 260;
	else if(input == &img_named_toyohime)
		return 261;
	else if(input == &img_named_utsuho)
		return 262;
	else if(input == &img_named_suika)
		return 263;
	else if(input == &img_named_reimu)
		return 264;
	else if(input == &img_named_alice)
		return 265;
	else if(input == &img_named_udonge)
		return 266;
	else if(input == &img_named_kaguya)
		return 267;
	else if(input == &img_mons_nesi)
		return 268;
	else if(input == &img_mons_sanghai[0])
		return 269;
	else if(input == &img_mons_sanghai[1])
		return 270;
	else if(input == &img_mons_hourai[0])
		return 271;
	else if(input == &img_mons_hourai[1])
		return 272;
	else if(input == &img_play_yamame)
		return 273;
	else if(input == &img_play_mokou[0])
		return 274;
	else if(input == &img_play_mokou[1])
		return 275;
	else if(input == &img_play_mokou[2])
		return 276;	
	else if(input == &img_item_armor_relec)
		return 277;
	else if(input == &img_item_armor_rcold)
		return 278;
	else if(input == &img_item_armor_rfire)
		return 279;
	else if(input == &img_item_armor_rmagic)
		return 280;
	else if(input == &img_item_armor_rpois)
		return 281;
	if(input == &img_item_evo_pagoda)
		return 282;
	else if(input == &img_item_evo_air_scroll)
		return 283;
	else if(input == &img_item_evo_dream_soul)
		return 284;
	else if(input == &img_item_evo_hammer)
		return 285;	
	else if(input == &img_mons_youmu_yukkuri)
		return 286;		
	else if(input == &img_laser_small[0])
		return 287;	
	else if(input == &img_tanmac_small[0][0])
		return 288;
	else if(input == &img_tanmac_small[1][0])
		return 289;
	else if(input == &img_tanmac_small[2][0])
		return 290;
	else if(input == &img_tanmac_small[3][0])
		return 291;
	else if(input == &img_tanmac_small[4][0])
		return 292;
	else if(input == &img_tanmac_small[5][0])
		return 293;
	else if(input == &img_fog_tonado[0])
		return 294;
	else if(input == &img_blast[0])
		return 295;
	else if(input == &img_thunder[0])
		return 296;
	else if(input == &img_mons_tokiko)
		return 297;
	else if(input == &img_fog_thunder[0])
		return 298;
	else if(input == &img_item_potion[1])
		return 299;
	else if(input == &img_item_potion[2])
		return 300;
	else if(input == &img_item_potion[3])
		return 301;
	else if(input == &img_item_potion[4])
		return 302;
	else if(input == &img_item_potion[5])
		return 303;
	else if(input == &img_item_potion[6])
		return 304;
	else if(input == &img_item_potion[7])
		return 305;
	else if(input == &img_item_potion[8])
		return 306;
	else if(input == &img_item_potion[9])
		return 307;
	else if(input == &img_item_potion[10])
		return 308;
	else if(input == &img_item_potion[11])
		return 309;
	else if(input == &img_item_potion[12])
		return 310;
	else if(input == &img_item_potion[13])
		return 311;
	else if(input == &img_item_potion[14])
		return 312;
	else if(input == &img_item_potion[15])
		return 313;
	else if(input == &img_item_potion[16])
		return 314;
	else if(input == &img_item_potion[17])
		return 315;
	else if(input == &img_item_potion[18])
		return 316;
	else if(input == &img_item_potion[19])
		return 317;
	else if(input == &img_item_book[1])
		return 318;
	else if(input == &img_item_book[2])
		return 319;
	else if(input == &img_item_book[3])
		return 320;
	else if(input == &img_item_book[4])
		return 321;
	else if(input == &img_item_book[5])
		return 322;
	else if(input == &img_item_book[6])
		return 323;	
	else if(input == &img_mons_toziko)
		return 324;
	else if(input == &img_mons_futo)
		return 325;
	else if(input == &img_mons_mamizo)
		return 326;
	else if(input == &img_mons_seiga)
		return 327;
	else if(input == &img_effect_emerald_uplift[0])
		return 328;
	else if(input == &img_effect_emerald_uplift[1])
		return 329;
	else if (input == &img_named_murasa)
		return 330;
	else if (input == &img_named_keine)
		return 331;
	else if (input == &img_named_keine2)
		return 332;
	else if (input == &img_named_youmu)
		return 333;
	else if (input == &img_named_lyrica)
		return 334;
	else if (input == &img_named_merlin)
		return 335;
	else if (input == &img_named_lunasa)
		return 336;
	else if (input == &img_named_komachi)
		return 337;
	else if (input == &img_named_iku)
		return 338;
	else if (input == &img_named_larva)
		return 339;
	else if (input == &img_named_nemuno)
		return 340;
	else if (input == &img_named_aunn)
		return 341;
	else if (input == &img_named_narumi)
		return 342;
	else if (input == &img_named_mai)
		return 343;
	else if (input == &img_named_satono)
		return 344;
	else if (input == &img_named_kokoro[0])
		return 345;
	else if (input == &img_named_kokoro[1])
		return 346;
	else if (input == &img_named_kokoro[2])
		return 347;
	else if (input == &img_named_kokoro[3])
		return 348;
	else if (input == &img_named_sumireko)
		return 349;
	else if (input == &img_mons_anchor)
		return 350;
	else if (input == &img_mons_mask_angry)
		return 351;
	else if (input == &img_mons_mask_sad)
		return 352;
	else if (input == &img_mons_mask_happy)
		return 353;
	else if (input == &img_mons_trash[0])
		return 354;
	else if (input == &img_mons_trash[1])
		return 355;
	else if (input == &img_mons_trash[2])
		return 356;
	else if (input == &img_mons_trash[3])
		return 357;
	else if (input == &img_mons_occult_long)
		return 358;
	else if (input == &img_mons_occult_disk)
		return 359;
	else if (input == &img_mons_occult_small)
		return 360;
	else if (input == &img_mons_occult_kunekune)
		return 361;
	else if (input == &img_mons_close_door)
		return 362;
	else if (input == &img_item_cat_tree)
		return 363;
	else if (input == &img_item_chocolet)
		return 364;
	else if (input == &img_item_cucumber)
		return 365;
	else if (input == &img_item_broken_camera)
		return 366;
	else if (input == &img_item_kappa_trash)
		return 367;
	else if (input == &img_mons_kaname)
		return 368;
	else if (input == &img_mons_sheep)
		return 369;
	else if (input == &img_mons_bee)
		return 370;
	else if (input == &img_item_ring[1])
		return 371;
	else if (input == &img_item_ring[2])
		return 372;
	else if (input == &img_item_ring[3])
		return 373;
	else if (input == &img_item_ring[4])
		return 374;
	else if (input == &img_item_ring[5])
		return 375;
	else if (input == &img_item_ring[6])
		return 376;
	else if (input == &img_item_ring[7])
		return 377;
	else if (input == &img_item_ring[8])
		return 378;
	else if (input == &img_item_ring[9])
		return 379;
	else if (input == &img_item_ring[10])
		return 380;
	else if (input == &img_item_ring[11])
		return 381;
	else if (input == &img_item_ring[12])
		return 382;
	else if (input == &img_item_ring[13])
		return 383;
	else if (input == &img_item_ring[14])
		return 384;
	else if (input == &img_item_ring[15])
		return 385;
	else if (input == &img_item_ring[16])
		return 386;
	else if (input == &img_item_ring[17])
		return 387;
	else if (input == &img_item_ring[18])
		return 388;
	else if (input == &img_item_artifact_ring)
		return 389;
	else if (input == &img_item_weapon_chakram)
		return 390;
	else if (input == &img_item_weapon_javelin)
		return 391;
	else if (input == &img_item_doggojeo)
		return 392;
	else if (input == &img_item_weapon_dauzing_rod)
		return 393;
	else if (input == &img_item_weapon_bamboo_spear)
		return 394;
	else if (input == &img_named_sigmund)
		return 395;
	else if (input == &img_mons_bush)
		return 396;
	else if (input == &img_item_artifact_shortsword)
		return 397;
	else if (input == &img_item_artifact_bamboo_spear)
		return 398;
	else if (input == &img_item_artifact_hammer)
		return 399;
	if (input == &img_item_artifact_onbasira)
		return 400;
	else if (input == &img_item_artifact_gohey)
		return 401;
	else if (input == &img_item_artifact_dagger)
		return 402;
	else if (input == &img_item_artifact_katana)
		return 403;
	else if (input == &img_item_artifact_scimitar)
		return 404;
	else if (input == &img_item_artifact_greatsword)
		return 405;
	else if (input == &img_item_artifact_broomstick)
		return 406;
	else if (input == &img_item_artifact_handaxe)
		return 407;
	else if (input == &img_item_artifact_battleaxe)
		return 408;
	else if (input == &img_item_artifact_anchor)
		return 409;
	else if (input == &img_item_artifact_spear)
		return 410;
	else if (input == &img_item_artifact_scythe)
		return 411;
	else if (input == &img_item_artifact_trident)
		return 412;
	else if (input == &img_item_artifact_chakram)
		return 413;
	else if (input == &img_item_artifact_umbrella)
		return 414;
	else if (input == &img_item_artifact_knife)
		return 415;
	else if (input == &img_item_artifact_dauzing_rod)
		return 416;
	else if (input == &img_item_artifact_javelin)
		return 417;
	else if (input == &img_play_item_cloak[0])
		return 418;
	else if (input == &img_play_item_cloak[1])
		return 419;
	else if (input == &img_play_item_glove[0])
		return 420;
	else if (input == &img_play_item_boot[0])
		return 421;
	else if (input == &img_play_item_body[0])
		return 422;
	else if (input == &img_play_item_body[1])
		return 423;
	else if (input == &img_play_item_body[2])
		return 424;
	else if (input == &img_play_item_body[3])
		return 425;
	else if (input == &img_play_item_body[4])
		return 426;
	else if (input == &img_play_item_body[5])
		return 427;
	else if (input == &img_play_item_body[6])
		return 428;
	else if (input == &img_play_item_body[7])
		return 429;
	else if (input == &img_play_item_body[8])
		return 430;
	else if (input == &img_play_item_body[9])
		return 431;
	else if (input == &img_play_item_body[10])
		return 432;
	else if (input == &img_play_item_body[11])
		return 433;
	else if (input == &img_play_item_body[12])
		return 434;
	else if (input == &img_play_item_body[13])
		return 435;
	else if (input == &img_play_item_body[14])
		return 436;
	else if (input == &img_play_item_body[15])
		return 437;
	else if (input == &img_play_item_body[16])
		return 438;
	else if (input == &img_play_item_hat[0])
		return 439;
	else if (input == &img_play_item_hat[1])
		return 440;
	else if (input == &img_play_item_hat[2])
		return 441;
	else if (input == &img_play_item_hat[3])
		return 442;
	else if (input == &img_play_item_hat[4])
		return 443;
	else if (input == &img_play_item_hat[5])
		return 444;
	else if (input == &img_play_item_shield[0])
		return 445;
	else if (input == &img_play_item_shield[1])
		return 446;
	else if (input == &img_play_item_shield[2])
		return 447;
	else if (input == &img_play_item_shield[3])
		return 448;
	else if (input == &img_play_item_weapon[0])
		return 449;
	else if (input == &img_play_item_weapon[1])
		return 450;
	else if (input == &img_play_item_weapon[2])
		return 451;
	else if (input == &img_play_item_weapon[3])
		return 452;
	else if (input == &img_play_item_weapon[4])
		return 453;
	else if (input == &img_play_item_weapon[5])
		return 454;
	else if (input == &img_play_item_weapon[6])
		return 455;
	else if (input == &img_play_item_weapon[7])
		return 456;
	else if (input == &img_play_item_weapon[8])
		return 457;
	else if (input == &img_play_item_weapon[9])
		return 458;
	else if (input == &img_play_item_weapon[10])
		return 459;
	else if (input == &img_play_item_weapon[11])
		return 460;
	else if (input == &img_play_item_weapon[12])
		return 461;
	else if (input == &img_play_item_weapon[13])
		return 462;
	else if (input == &img_play_item_weapon[14])
		return 463;
	else if (input == &img_play_item_weapon[15])
		return 464;
	else if (input == &img_play_item_weapon[16])
		return 465;
	else if (input == &img_play_item_weapon[17])
		return 466;
	else if (input == &img_play_item_weapon[18])
		return 467;
	else if (input == &img_play_item_weapon[19])
		return 468;
	else if (input == &img_play_item_tribe[0])
		return 469;
	else if (input == &img_play_item_weapon[20])
		return 470;
	else if (input == &img_item_armor_helmet[0])
		return 471;
	else if (input == &img_item_armor_helmet[2])
		return 472;
	else if (input == &img_item_armor_helmet[3])
		return 473;
	else if (input == &img_item_armor_helmet[4])
		return 474;
	else if (input == &img_item_armor_helmet[5])
		return 475;
	else if (input == &img_effect_gold_floor[0])
		return 476;
	else if (input == &img_effect_gold_floor[1])
		return 477;
	else if (input == &img_effect_gold_floor[2])
		return 478;
	else if (input == &img_fog_sion[0][0])
		return 479;
	else if (input == &img_fog_sion[1][0])
		return 480;
	else if (input == &img_fog_sion[2][0])
		return 481;
	else if (input == &img_mons_sion)
		return 482;
	else if(input == &img_blast[2])
		return 483;
	else if (input == &img_named_hatate)
		return 484;
	else if (input == &img_mons_dancing_weapon)
		return 485;
	else if (input == &img_mons_cursed_doll)
		return 486;
	else if (input == &img_effect_halo)
		return 487;
	else if(input == &img_effect_veiling)
		return 488;
	else if (input == &img_item_evo_bomb)
		return 489;
	else if (input == &img_item_evo_ghost_ball)
		return 490;
	else if (input == &img_item_evo_sky_torpedo)
		return 491;
	else if (input == &img_named_doreking)
		return 492;
	else if (input == &img_mons_curiosity)
		return 493;
	else if (input == &img_mons_desire_red)
		return 494;
	else if (input == &img_mons_desire_green)
		return 495;
	else if (input == &img_mons_desire_blue)
		return 496;
	else if (input == &img_mon_kaguya_quiz[0])
		return 497;
	else if (input == &img_mon_kaguya_quiz[1])
		return 498;
	else if (input == &img_mon_kaguya_quiz[2])
		return 499;
	else if (input == &img_mon_kaguya_quiz[3])
		return 500;
	else if (input == &img_mon_kaguya_quiz[4])
		return 501;
	else if (input == &img_named_reimu2)
		return 502; 
	else if (input == &img_item_armor_helmet[6])
		return 503;
	else if (input == &img_play_item_hat[6])
		return 504;
	else if (input == &img_mons_misyaguzi)
		return 505;
	else if (input == &img_mons_eika)
		return 506;
	else if (input == &img_mons_stonetower[0])
		return 507;
	else if (input == &img_mons_stonetower[1])
		return 508;
	else if (input == &img_mons_stonetower[2])
		return 509;
	else if (input == &img_mons_urumi)
		return 510;
	else if (input == &img_mons_kutaka)
		return 511;
	else if (input == &img_mons_yachie)
		return 512;
	else if (input == &img_mons_mayumi)
		return 513;
	else if (input == &img_mons_saki)
		return 514;
	else if (input == &img_mons_yuma)
		return 515;
	else if (input == &img_mons_yuma_drainform)
		return 516;
	else if (input == &img_mons_enoko)
		return 517;
	else if (input == &img_mons_chiyari)
		return 518;
	else if (input == &img_mons_sonbiten)
		return 519;
	else if (input == &img_mons_hisami)
		return 520;
	else if (input == &img_mons_tsukasa)
		return 521;
	else if (input == &img_mons_ubame)
		return 522;
	else if (input == &img_mons_chimi)
		return 523;
	else if (input == &img_mons_nareko)
		return 524;
	else if (input == &img_mons_mike)
		return 525;
	else if (input == &img_mons_takane)
		return 526;
	else if (input == &img_mons_sannyo)
		return 527;
	else if (input == &img_mons_stonetower[3])
		return 528;
	else if (input == &img_mons_stonetower[4])
		return 529;
	else if (input == &img_mons_fog_fairy)
		return 530;
	else if (input == &img_mons_tsuchinoko)
		return 531;
	else if (input == &img_mons_vine)
		return 532;
	else if (input == &img_mons_security_fairy_maid)
		return 533;
	else if (input == &img_mons_big_slime)
		return 534;
	else if (input == &img_mons_small_slime)
		return 535;
	else if (input == &img_mons_new_yamabush_tengu)
		return 536;
	else if (input == &img_mons_new_hanataca_tengu)
		return 537;
	else if (input == &img_mons_haniwa)
		return 538;
	else if (input == &img_mons_horse_haniwa)
		return 539;
	else if (input == &img_mons_haniwa_spearman)
		return 540;
	else if (input == &img_mons_haniwa_archer)
		return 541;
	else if (input == &img_mons_haniwa_cavalry)
		return 542;
	else if (input == &img_mons_wolf_spirit)
		return 543;
	else if (input == &img_mons_eagle_spirit)
		return 544;
	else if (input == &img_mons_otter_spirit)
		return 545;
	else if (input == &img_mons_sonbiten_spintowin)
		return 546;
	else if(input == &img_tanmac_oil_big[1])
		return 547;
	else if(input == &img_item_skeleton[0])
		return 548;
	else if(input == &img_item_skeleton[1])
		return 549;
	else if(input == &img_item_skeleton[2])
		return 550;
	else if(input == &img_fog_heavenly_storm[0])
		return 551;
	else if(input == &img_mons_security_door)
		return 552;
	else if(input == &img_tanmac_missle[0] ||
		input == &img_tanmac_missle[1]||input == &img_tanmac_missle[2] ||
		input == &img_tanmac_missle[3]||input == &img_tanmac_missle[4] ||
		input == &img_tanmac_missle[5]||input == &img_tanmac_missle[6] ||
		input == &img_tanmac_missle[7])
		return 553;
	else
	{
		for (int i = 0; i < STYLE_NUM; i++)
		{
			for (int j = 0; j < COLOR_NUM; j++)
			{
				if(input == &img_playable_character[i][j])
					return 1000 + (i * COLOR_NUM) + j;
			}
		}
	}
	return 0;
}


textures* inttotexture(int input)
{
	if (input == -1)
	{
		return NULL;
	}
	else if (input >= 1000) 
	{
		int cur = input - 1000;
		return &img_playable_character[cur / COLOR_NUM][cur % COLOR_NUM];
	}

	switch(input)
	{
	case 1:
		return &img_mons_reimu_yukkuri;
	case 2:
		return &img_play_reimu;
	case 3:
		return &img_item_armor_robe;
	case 4:
		return &img_item_armor_cloak;
	case 5:
		return &img_item_armor_robe_sanae;
	case 6:
		return &img_item_armor_glove;
	case 7:
		return &img_item_armor_boot;
	case 8:
		return &img_item_armor_helmet[1];
	case 9:
		return &img_item_weapon_dagger;
	case 10:
		return &img_item_food_bread;
	case 11:
		return &img_item_potion[0];
	case 12:
		return &img_item_scroll;
	case 13:
		return &img_item_ring[0];
	case 14:
		return &img_item_amulet;
	case 15:
		return &img_effect_select;
	case 16:
		return &img_tanmac_bill[1];
	case 17:
		return &img_tanmac_amulet[0];
	case 18:
		return &img_item_weapon_gohey;
	case 19:
		return &img_item_weapon_katana;
	case 20:
		return &img_item_weapon_scimitar;
	case 21:
		return &img_item_weapon_greatsword;
	case 22:
		return &img_item_weapon_broomstick;
	case 23:
		return &img_item_weapon_handaxe;
	case 24:
		return &img_item_weapon_battleaxe;
	case 25:
		return &img_item_weapon_anchor;
	case 26:
		return &img_item_weapon_spear;
	case 27:
		return &img_item_weapon_scythe;
	case 28:
		return &img_item_weapon_trident;
	case 29:
		return &img_item_weapon_smalllance;
	case 30:
		return &img_item_weapon_umbrella;
	case 31:
		return &img_item_weapon_knife;
	case 32:
		return &img_item_weapon_shortsword;
	case 33:
		return &img_item_weapon_gohey2;
	case 34:
		return &img_item_weapon_hammer;
	case 35:
		return &img_item_weapon_onbasira;
	case 36:
		return &img_item_weapon_roundshield;
	case 37:
		return &img_item_weapon_shield;
	case 38:
		return &img_item_weapon_momizishield;
	case 39:
		return &img_item_weapon_kiteshield;		
	case 40:
		return &img_mons_rat;
	case 41:
		return &img_mons_fairy_green;
	case 42:
		return &img_mons_fairy_blue;
	case 43:
		return &img_mons_fairy_red;
	case 44:
		return &img_mons_mook;
	case 45:
		return &img_mons_crow;
	case 46:
		return &img_mons_crane;
	case 47:
		return &img_mons_spider;
	case 48:
		return &img_mons_snake;
	case 49:
		return &img_mons_katpa;
	case 50:
		return &img_mons_katpa_gun;
	case 51:
		return &img_mons_fairy_green_warroir;
	case 52:
		return &img_mons_fairy_blue_magician;
	case 53:
		return &img_mons_fairy_red_commander;
	case 54:
		return &img_named_rumia;
	case 55:
		return &img_named_mistia;
	case 56:
		return &img_named_wriggle;
	case 57:
		return &img_named_cirno;
	case 58:
		return &img_item_food_p_item;
	case 59:
		return &img_fog_normal[0];
	case 60:
		return &img_fog_fire[0];
	case 61:
		return &img_fog_cold[0];
	case 62:
		return &img_fog_dark[0];
	case 63:
		return &img_fog_poison[0];
	case 64:
		return &img_fog_slow[0];
	case 65:
		return &img_mons_human_woman;
	case 66:
		return &img_mons_human_man;
	case 67:
		return &img_mons_human_yinyang;
	case 68:
		return &img_mons_human_priest;
	case 69:
		return &img_mons_human_samuri;
	case 70:
		return &img_mons_firefly;
	case 71:
		return &img_mons_butterfly;
	case 72:
		return &img_named_medicine;
	case 73:
		return &img_named_diefairy;
	case 74:
		return &img_tanmac_fire_big[1];
	case 75:
		return &img_tanmac_fire_small[1];
	case 76:
		return &img_tanmac_ice[0];
	case 77:
		return &img_tanmac_ice_small[0];
	case 78:
		return &img_item_goal;
	case 79:
		return &img_play_marisa;
	case 80:
		return &img_play_sanae;
	case 81:
		return &img_item_armor_armour_0;
	case 82:
		return &img_item_armor_armour_1;
	case 83:
		return &img_item_armor_armour_2;
	case 84:
		return &img_item_armor_armour_3;
	case 85:
		return &img_item_book[0];
	case 86:
		return &img_tanmac_ice_small[0];
	case 87:
		return &img_mons_ghost[0];
	case 88:
		return &img_mons_ghost[1];
	case 89:
		return &img_mons_ghost[2];
	case 90:
		return &img_mons_bakekasa;
	case 91:
		return &img_mons_green_mook;
	case 92:
		return &img_mons_orange_mook;
	case 93:
		return &img_mons_gray_mook;
	case 94:
		return &img_mons_frog;
	case 95:
		return &img_mons_black_cat;
	case 96:
		return &img_mons_orange_cat;
	case 97:
		return &img_mons_white_cat;
	case 98:
		return &img_mons_crow_tengu;
	case 99:
		return &img_mons_oni;
	case 100:
		return &img_mons_marisa_yukkuri;
	case 101:
		return &img_mons_aya_yukkuri;
	case 102:
		return &img_named_kisume;
	case 103:
		return &img_named_chen;
	case 104:
		return &img_named_kogasa;
	case 105:
		return &img_named_sunny;
	case 106:
		return &img_named_lunar;
	case 107:
		return &img_named_star;
	case 108:
		return &img_tanmac_ice_big[0];
	case 109:
		return &img_tanmac_poison_big[0];
	case 110:
		return &img_mons_remila_yukkuri;
	case 111:
		return &img_mons_alice_yukkuri;
	case 112:
		return &img_mons_yamabiko;
	case 113:
		return &img_mons_katpa_spear;
	case 114:
		return &img_mons_katpa_water_wizard;
	case 115:
		return &img_mons_yamabush_tengu;
	case 116:
		return &img_mons_hanataca_tengu;
	case 117:
		return &img_mons_blue_oni;
	case 118:
		return &img_mons_mushroom;
	case 119:
		return &img_named_kyouko;
	case 120:
		return &img_named_momizi;
	case 121:
		return &img_named_aya;
	case 122:
		return &img_mons_new_kappa;
	case 123:
		return &img_mons_new_kappa_spear;
	case 124:
		return &img_mons_new_kappa_wizard;
	case 125:
		// return &img_mons_test;
		return &img_mons_new_kappa_wizard;
	case 126:
		return &img_mons_magic_book[0];
	case 127:
		return &img_mons_magic_book[1];
	case 128:
		return &img_mons_magic_book[2];
	case 129:
		return &img_mons_magic_book[3];
	case 130:
		return &img_mons_hobgobrin;
	case 131:
		return &img_mons_hobgobrin_maid;
	case 132:
		return &img_mons_hobgobrin_librarian;
	case 133:
		return &img_mons_hobgobrin_temp;
	case 134:
		return &img_mons_maid_fairy;
	case 135:
		return &img_mons_chuparcabra;
	case 136:
		return &img_mons_eagle;
	case 137:
		return &img_mons_tiger;
	case 138:
		return &img_mons_raijuu;
	case 139:
		return &img_mons_dragon_baby;
	case 140:
		return &img_mons_yamawaro_ninja;
	case 141:
		return &img_mons_yamawaro_warrior;
	case 142:
		return &img_mons_yamawaro_flag;
	case 143:
		return &img_named_wakasagi;
	case 144:
		return &img_named_yamame;
	case 145:
		return &img_named_nazrin;
	case 146:
		return &img_mons_dauzing;
	case 147:
		return &img_named_yosika;
	case 148:
		return &img_named_sekibanki;
	case 149:
		return &img_named_sekibanki_body;
	case 150:
		return &img_named_sekibanki_head;
	case 151:
		return &img_named_nitori;
	case 152:
		return &img_named_kagero;
	case 153:
		return &img_named_parsi;
	case 154:
		return &img_named_benben;
	case 155:
		return &img_named_yathasi;
	case 156:
		return &img_named_orin;
	case 157:
		return &img_named_orin_cat;
	case 158:
		return &img_mons_zombiefairy;
	case 159:
		return &img_named_ichirin;
	case 160:
		return &img_named_unzan;
	case 161:
		return &img_named_unzan_punch[0];
	case 162:
		return &img_named_unzan_punch[1];
	case 163:
		return &img_named_unzan_punch[2];
	case 164:
		return &img_named_unzan_punch[3];
	case 165:
		return &img_named_pachu;
	case 166:
		return &img_named_koakuma;
	case 167:
		return &img_named_meirin;
	case 168:
		return &img_named_sakuya;
	case 169:
		return &img_named_remilia;
	case 170:
		return &img_named_kasen;
	case 171:
		return &img_effect_autumn_leave[0];
	case 172:
		return &img_effect_autumn_leave[1];
	case 173:
		return &img_effect_autumn_leave[2];
	case 174:
		return &img_effect_autumn_leave[3];
	case 175:
		return &img_item_autumn_armour[0];
	case 176:
		return &img_item_autumn_armour[1];
	case 177:
		return &img_item_autumn_armour[2];
	case 178:
		return &img_item_autumn_armour[3];
	case 179:
		return &img_item_autumn_armour[4];
	case 180:
		return &img_tanmac_air[0];
	case 181:
		return &img_tanmac_rock_small[0];
	case 182:
		return &img_mons_option;
	case 183:
		return &img_mons_golem;		
	case 184:
		return &img_mons_onbasira;
	case 185:
		return &img_item_needle;
	case 186:
		return &img_item_kikuichi;
	case  187:
		return &img_item_spellcard;
	case 188:
		return &img_item_sweet_potato;
	case 189:
		return &img_mons_red_ufo;
	case 190:
		return &img_mons_blue_ufo;
	case 191:
		return &img_mons_green_ufo;
	case 192:
		return &img_named_koishi;
	case 193:
		return &img_named_nue;
	case 194:
		return &img_mons_sanpei_fighter;
	case 195:
		return &img_mons_vamp_bat;
	case 196:
		return &img_mons_dagama;
	case 197:
		return &img_play_momizi;
	case 198:
		return &img_play_normal;		
	case 199:
		return &img_tanmac_rock_big[0];
	case 200:
		return &img_effect_rock_trap;
	case 201:
		return &img_effect_rock_uplift[0];
	case 202:
		return &img_effect_rock_uplift[1];
	case 203:
		return &img_effect_rock_uplift[2];
	case 204:
		return &img_effect_rock_uplift[3];
	case 205:
		return &img_effect_rock_uplift[4];
	case 206:
		return &img_mons_rabit;
	case 207:
		return &img_mons_youkai_rabit;
	case 208:
		return &img_mons_namaz;
	case 209:
		return &img_mons_hell_crow;
	case 210:
		return &img_mons_raccoon;
	case 211:
		return &img_mons_lantern_youkai;
	case 212:
		return &img_mons_yinyan;
	case 213:
		return &img_mons_yugenmagan;
	case 214:
		return &img_mons_elise;
	case 215:
		return &img_mons_sariel;
	case 216:
		return &img_mons_sara;
	case 217:
		return &img_mons_louise;
	case 218:
		return &img_mons_yuki;
	case 219:
		return &img_mons_mai;
	case 220:
		return &img_mons_yumeko;
	case 221:
		return &img_mons_evil_eye;
	case 222:
		return &img_mons_little_imp;
	case 223:
		return &img_mons_schema_eye;
	case 224:
		return &img_effect_schema[0];
	case 225:
		return &img_effect_schema[1];
	case 226:
		return &img_effect_schema[2];
	case 227:
		return &img_mons_bomb_rabbit;
	case 228:
		return &img_mons_spear_rabbit;
	case 229:
		return &img_mons_support_rabbit;
	case 230:
		return &img_mons_magic_rabbit;
	case 231:
		return &img_named_flandre;
	case 232:
		return &img_named_tewi;
	case 233:
		return &img_named_clownpiece;
	case 234:
		return &img_named_doremi;
	case 235:
		return &img_item_rune;
	case 236:
		return &img_blizzard[0];
	case 237:
		return &img_named_seiran;
	case 238:
		return &img_named_ringo;
	case 239:
		return &img_mons_fairy_green_hero;
	case 240:
		return &img_mons_fairy_green_socerer;
	case 241:
		return &img_mons_fairy_green_himawari;
	case 242:
		return &img_mons_moon_rabbit_attack;
	case 243:
		return &img_mons_moon_rabbit_supporter;
	case 244:
		return &img_mons_moon_rabbit_elite;
	case 245:
		return &img_mons_mac;
	case 246:
		return &img_mons_nightmare;
	case 247:
		return &img_mons_lunatic;
	case 248:
		return &img_mons_haunt[0];
	case 249:
		return &img_mons_haunt[1];
	case 250:
		return &img_mons_haunt[2];
	case 251:
		return &img_mons_fire_car;
	case 252:
		return &img_mons_hell_spider;
	case 253:
		return &img_mons_blood_haunt;
	case 254:
		return &img_mons_hell_dog;
	case 255:
		return &img_mons_flower_tank[0];
	case 256:
		return &img_mons_flower_tank[1];
	case 257:
		return &img_mons_evil_eye_tank;
	case 258:
		return &img_mons_snow_girl;
	case 259:
		return &img_named_letty;
	case 260:
		return &img_named_yorihime;
	case 261:
		return &img_named_toyohime;
	case 262:
		return &img_named_utsuho;
	case 263:
		return &img_named_suika;
	case 264:
		return &img_named_reimu;
	case 265:
		return &img_named_alice;
	case 266:
		return &img_named_udonge;
	case 267:
		return &img_named_kaguya;
	case 268:
		return &img_mons_nesi;
	case 269:
		return &img_mons_sanghai[0];
	case 270:
		return &img_mons_sanghai[1];
	case 271:
		return &img_mons_hourai[0];
	case 272:
		return &img_mons_hourai[1];
	case 273:
		return &img_play_yamame;
	case 274:
		return &img_play_mokou[0];
	case 275:
		return &img_play_mokou[1];
	case 276:
		return &img_play_mokou[2];		
	case 277:
		return &img_item_armor_relec;
	case 278:
		return &img_item_armor_rcold;
	case 279:
		return &img_item_armor_rfire;
	case 280:
		return &img_item_armor_rmagic;
	case 281:
		return &img_item_armor_rpois;
	case 282:
		return &img_item_evo_pagoda;
	case 283:
		return &img_item_evo_air_scroll;
	case 284:
		return &img_item_evo_dream_soul;
	case 285:	
		return &img_item_evo_hammer;
	case 286:	
		return &img_mons_youmu_yukkuri;
	case 287:
		return &img_laser_small[0];
	case 288:
		return &img_tanmac_small[0][0];
	case 289:
		return &img_tanmac_small[1][0];
	case 290:
		return &img_tanmac_small[2][0];
	case 291:
		return &img_tanmac_small[3][0];
	case 292:
		return &img_tanmac_small[4][0];
	case 293:
		return &img_tanmac_small[5][0];
	case 294:
		return &img_fog_tonado[0];
	case 295:
		return &img_blast[0];
	case 296:
		return &img_thunder[0];
	case 297:
		return &img_mons_tokiko;
	case 298:
		return &img_fog_thunder[0];		
	case 299:
		return &img_item_potion[1];
	case 300:
		return &img_item_potion[2];
	case 301:
		return &img_item_potion[3];
	case 302:
		return &img_item_potion[4];
	case 303:
		return &img_item_potion[5];
	case 304:
		return &img_item_potion[6];
	case 305:
		return &img_item_potion[7];
	case 306:
		return &img_item_potion[8];
	case 307:
		return &img_item_potion[9];
	case 308:
		return &img_item_potion[10];
	case 309:
		return &img_item_potion[11];
	case 310:
		return &img_item_potion[12];
	case 311:
		return &img_item_potion[13];
	case 312:
		return &img_item_potion[14];
	case 313:
		return &img_item_potion[15];
	case 314:
		return &img_item_potion[16];
	case 315:
		return &img_item_potion[17];
	case 316:
		return &img_item_potion[18];
	case 317:
		return &img_item_potion[19];		
	case 318:
		return &img_item_book[1];
	case 319:
		return &img_item_book[2];
	case 320:
		return &img_item_book[3];
	case 321:
		return &img_item_book[4];
	case 322:
		return &img_item_book[5];
	case 323:
		return &img_item_book[6];
	case 324:
		return &img_mons_toziko;
	case 325:
		return &img_mons_futo;
	case 326:
		return &img_mons_mamizo;
	case 327:
		return &img_mons_seiga;
	case 328:
		return &img_effect_emerald_uplift[0];
	case 329:
		return &img_effect_emerald_uplift[1];
	case 330:
		return &img_named_murasa;
	case 331:
		return &img_named_keine;
	case 332:
		return &img_named_keine2;
	case 333:
		return &img_named_youmu;
	case 334:
		return &img_named_lyrica;
	case 335:
		return &img_named_merlin;
	case 336:
		return &img_named_lunasa;
	case 337:
		return &img_named_komachi;
	case 338:
		return &img_named_iku;
	case 339:
		return &img_named_larva;
	case 340:
		return &img_named_nemuno;
	case 341:
		return &img_named_aunn;
	case 342:
		return &img_named_narumi;
	case 343:
		return &img_named_mai;
	case 344:
		return &img_named_satono;
	case 345:
		return &img_named_kokoro[0];
	case 346:
		return &img_named_kokoro[1];
	case 347:
		return &img_named_kokoro[2];
	case 348:
		return &img_named_kokoro[3];
	case 349:
		return &img_named_sumireko;
	case 350:
		return &img_mons_anchor;
	case 351:
		return &img_mons_mask_angry;
	case 352:
		return &img_mons_mask_sad;
	case 353:
		return &img_mons_mask_happy;
	case 354:
		return &img_mons_trash[0];
	case 355:
		return &img_mons_trash[1];
	case 356:
		return &img_mons_trash[2];
	case 357:
		return &img_mons_trash[3];
	case 358:
		return &img_mons_occult_long;
	case 359:
		return &img_mons_occult_disk;
	case 360:
		return &img_mons_occult_small;
	case 361:
		return &img_mons_occult_kunekune;
	case 362:
		return &img_mons_close_door;
	case 363:
		return &img_item_cat_tree;
	case 364:
		return &img_item_chocolet;
	case 365:
		return &img_item_cucumber;
	case 366:
		return &img_item_broken_camera;
	case 367:
		return &img_item_kappa_trash;
	case 368:
		return &img_mons_kaname;
	case 369:
		return &img_mons_sheep;
	case 370:
		return &img_mons_bee;
	case 371:
		return &img_item_ring[1];
	case 372:
		return &img_item_ring[2];
	case 373:
		return &img_item_ring[3];
	case 374:
		return &img_item_ring[4];
	case 375:
		return &img_item_ring[5];
	case 376:
		return &img_item_ring[6];
	case 377:
		return &img_item_ring[7];
	case 378:
		return &img_item_ring[8];
	case 379:
		return &img_item_ring[9];
	case 380:
		return &img_item_ring[10];
	case 381:
		return &img_item_ring[11];
	case 382:
		return &img_item_ring[12];
	case 383:
		return &img_item_ring[13];
	case 384:
		return &img_item_ring[14];
	case 385:
		return &img_item_ring[15];
	case 386:
		return &img_item_ring[16];
	case 387:
		return &img_item_ring[17];
	case 388:
		return &img_item_ring[18];
	case 389:
		return &img_item_artifact_ring;
	case 390:
		return &img_item_weapon_chakram;
	case 391:
		return &img_item_weapon_javelin;
	case 392:
		return &img_item_doggojeo;
	case 393:
		return &img_item_weapon_dauzing_rod;
	case 394:
		return &img_item_weapon_bamboo_spear;
	case 395:
		return &img_named_sigmund;
	case 396:
		return &img_mons_bush;
	case 397:
		return &img_item_artifact_shortsword;
	case 398:
		return &img_item_artifact_bamboo_spear;
	case 399:
		return &img_item_artifact_hammer;
	case 400:
		return &img_item_artifact_onbasira;
	case 401:
		return &img_item_artifact_gohey;
	case 402:
		return &img_item_artifact_dagger;
	case 403:
		return &img_item_artifact_katana;
	case 404:
		return &img_item_artifact_scimitar;
	case 405:
		return &img_item_artifact_greatsword;
	case 406:
		return &img_item_artifact_broomstick;
	case 407:
		return &img_item_artifact_handaxe;
	case 408:
		return &img_item_artifact_battleaxe;
	case 409:
		return &img_item_artifact_anchor;
	case 410:
		return &img_item_artifact_spear;
	case 411:
		return &img_item_artifact_scythe;
	case 412:
		return &img_item_artifact_trident;
	case 413:
		return &img_item_artifact_chakram;
	case 414:
		return &img_item_artifact_umbrella;
	case 415:
		return &img_item_artifact_knife;
	case 416:
		return &img_item_artifact_dauzing_rod;
	case 417:
		return &img_item_artifact_javelin;
	case 418:
		return &img_play_item_cloak[0];
	case 419:
		return &img_play_item_cloak[1];
	case 420:
		return &img_play_item_glove[0];
	case 421:
		return &img_play_item_boot[0];
	case 422:
		return &img_play_item_body[0];
	case 423:
		return &img_play_item_body[1];
	case 424:
		return &img_play_item_body[2];
	case 425:
		return &img_play_item_body[3];
	case 426:
		return &img_play_item_body[4];
	case 427:
		return &img_play_item_body[5];
	case 428:
		return &img_play_item_body[6];
	case 429:
		return &img_play_item_body[7];
	case 430:
		return &img_play_item_body[8];
	case 431:
		return &img_play_item_body[9];
	case 432:
		return &img_play_item_body[10];
	case 433:
		return &img_play_item_body[11];
	case 434:
		return &img_play_item_body[12];
	case 435:
		return &img_play_item_body[13];
	case 436:
		return &img_play_item_body[14];
	case 437:
		return &img_play_item_body[15];
	case 438:
		return &img_play_item_body[16];
	case 439:
		return &img_play_item_hat[0];
	case 440:
		return &img_play_item_hat[1];
	case 441:
		return &img_play_item_hat[2];
	case 442:
		return &img_play_item_hat[3];
	case 443:
		return &img_play_item_hat[4];
	case 444:
		return &img_play_item_hat[5];
	case 445:
		return &img_play_item_shield[0];
	case 446:
		return &img_play_item_shield[1];
	case 447:
		return &img_play_item_shield[2];
	case 448:
		return &img_play_item_shield[3];
	case 449:
		return &img_play_item_weapon[0];
	case 450:
		return &img_play_item_weapon[1];
	case 451:
		return &img_play_item_weapon[2];
	case 452:
		return &img_play_item_weapon[3];
	case 453:
		return &img_play_item_weapon[4];
	case 454:
		return &img_play_item_weapon[5];
	case 455:
		return &img_play_item_weapon[6];
	case 456:
		return &img_play_item_weapon[7];
	case 457:
		return &img_play_item_weapon[8];
	case 458:
		return &img_play_item_weapon[9];
	case 459:
		return &img_play_item_weapon[10];
	case 460:
		return &img_play_item_weapon[11];
	case 461:
		return &img_play_item_weapon[12];
	case 462:
		return &img_play_item_weapon[13];
	case 463:
		return &img_play_item_weapon[14];
	case 464:
		return &img_play_item_weapon[15];
	case 465:
		return &img_play_item_weapon[16];
	case 466:
		return &img_play_item_weapon[17];
	case 467:
		return &img_play_item_weapon[18];
	case 468:
		return &img_play_item_weapon[19];
	case 469:
		return &img_play_item_tribe[0];
	case 470:
		return &img_play_item_weapon[20];
	case 471:
		return &img_item_armor_helmet[0];
	case 472:
		return &img_item_armor_helmet[2];
	case 473:
		return &img_item_armor_helmet[3];
	case 474:
		return &img_item_armor_helmet[4];
	case 475:
		return &img_item_armor_helmet[5];
	case 476:
		return &img_effect_gold_floor[0];
	case 477:
		return &img_effect_gold_floor[1];
	case 478:
		return &img_effect_gold_floor[2];
	case 479:
		return &img_fog_sion[0][0];
	case 480:
		return &img_fog_sion[1][0];
	case 481:
		return &img_fog_sion[2][0];
	case 482:
		return &img_mons_sion;
	case 483:
		return &img_blast[2];
	case 484:
		return &img_named_hatate;
	case 485:
		return &img_mons_dancing_weapon;
	case 486:
		return &img_mons_cursed_doll;
	case 487:
		return &img_effect_halo;
	case 488:
		return &img_effect_veiling;
	case 489:
		return &img_item_evo_bomb;
	case 490:
		return &img_item_evo_ghost_ball;
	case 491:
		return &img_item_evo_sky_torpedo;
	case 492:
		return &img_named_doreking;
	case 493:
		return &img_mons_curiosity;
	case 494:
		return &img_mons_desire_red;
	case 495:
		return &img_mons_desire_green;
	case 496:
		return &img_mons_desire_blue;
	case 497:
		return &img_mon_kaguya_quiz[0];
	case 498:
		return &img_mon_kaguya_quiz[1];
	case 499:
		return &img_mon_kaguya_quiz[2];
	case 500:
		return &img_mon_kaguya_quiz[3];
	case 501:
		return &img_mon_kaguya_quiz[4];
	case 502:
		return &img_named_reimu2;
	case 503:
		return &img_item_armor_helmet[6];
	case 504:
		return &img_play_item_hat[6];
	case 505:
		return &img_mons_misyaguzi;
	case 506:
		return &img_mons_eika;
	case 507:
		return &img_mons_stonetower[0];
	case 508:
		return &img_mons_stonetower[1];
	case 509:
		return &img_mons_stonetower[2];
	case 510:
		return &img_mons_urumi;
	case 511:
		return &img_mons_kutaka;
	case 512:
		return &img_mons_yachie;
	case 513:
		return &img_mons_mayumi;
	case 514:
		return &img_mons_saki;
	case 515:
		return &img_mons_yuma;
	case 516:
		return &img_mons_yuma_drainform;
	case 517:
		return &img_mons_enoko;
	case 518:
		return &img_mons_chiyari;
	case 519:
		return &img_mons_sonbiten;
	case 520:
		return &img_mons_hisami;
	case 522:
		return &img_mons_ubame;
	case 523:
		return &img_mons_chimi;
	case 524:
		return &img_mons_nareko;
	case 525:
		return &img_mons_mike;
	case 526:
		return &img_mons_takane;
	case 527:
		return &img_mons_sannyo;
	case 528:
		return &img_mons_stonetower[3];
	case 529:
		return &img_mons_stonetower[4];
	case 530:
		return &img_mons_fog_fairy;
	case 531:
		return &img_mons_tsuchinoko;
	case 532:
		return &img_mons_vine;
	case 533:
		return &img_mons_security_fairy_maid;
	case 534:
		return &img_mons_big_slime;
	case 535:
		return &img_mons_small_slime;
	case 536:
		return &img_mons_new_yamabush_tengu;
	case 537:
		return &img_mons_new_hanataca_tengu;
	case 538:
		return &img_mons_haniwa;
	case 539:
		return &img_mons_horse_haniwa;
	case 540:
		return &img_mons_haniwa_spearman;
	case 541:
		return &img_mons_haniwa_archer;
	case 542:
		return &img_mons_haniwa_cavalry;
	case 543:
		return &img_mons_wolf_spirit;
	case 544:
		return &img_mons_eagle_spirit;
	case 545:
		return &img_mons_otter_spirit;
	case 546:
		return &img_mons_sonbiten_spintowin;
	case 547:
		return &img_tanmac_oil_big[1];
	case 548:
		return &img_item_skeleton[0];
	case 549:
		return &img_item_skeleton[1];
	case 550:
		return &img_item_skeleton[2];
	case 551:
		return &img_fog_heavenly_storm[0];
	case 552:
		return &img_mons_security_door;
	case 553:
		return &img_tanmac_missle[1];
	default:
		return &img_mons_default;
	}
}


textures* statetotexture(monster_state_simple state_)
{
	switch(state_)
	{
	case MSS_SLEEP:
		return &img_state_sleep;
	case MSS_WANDERING:
		return &img_state_wardering;
	case MSS_CONFUSE:
		return &img_state_confuse;
	case MSS_POISON:
		return &img_state_poison;
	case MSS_SLOW:
		return &img_state_slow;
	case MSS_PARALYSE:
		return &img_state_paralysis;
	case MSS_SCARY:
		return &img_state_scary;
	case MSS_ALLY:
		return &img_state_ally;
	case MSS_SUMMON:
		return &img_state_summon;
	case MSS_HASTE:
		return &img_state_haste;
	case MSS_FEAR:
		return &img_state_scary;
	case MSS_LUNATIC:
		return &img_state_lunatic;
	case MSS_NEUTRAL:
		return &img_state_neutral;
	case MSS_COMMUNICATION:
		return &img_state_calling;
	default:
		return nullptr;
	}
}