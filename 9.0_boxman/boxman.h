/*******************************************
*游戏规则:
*1.控制小人移动:w上,s下,a左,d右,q退出
*
*2.注意:箱子到达目的地后不能移动
*小人不能跨越目的地/箱子/墙
*
*3.目标:以最少步数,把所有箱子推至目的地
********************************************/

#include <iostream>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>//_kbhit()和_getch()

//墙: 0，地板: 1，箱子目的地: 2,  小人: MAN,	箱子: BOX, 箱子命中目标: HIT
//舞台宽度960*768mm
//舞台图片
//loadimage 最后一个参数:是否是拉伸图片,true false差别不大

#define ROW 9
#define COLUMN 12
#define SCREEN_WIDTH 1190
#define SCREEN_HEIGHT 800
#define START_CELLX (SCREEN_WIDTH-COLUMN*CELL)/2
#define START_CELLY (SCREEN_HEIGHT-ROW*CELL)/2
#define CELL 61

#define LEFTK 'a'//UP+K-keyboard
#define RIGHTK 'd'
#define DOWNK 's'
#define UPK 'w'
#define QUITK 'q'

#define isValid(pic) pic.c >= 0 && pic.c < COLUMN && pic.r >= 0 && pic.r < ROW  && map[nxt.r][nxt.c] != HIT//判断下一位置是否超过格子群或是否为箱子目的地
#define TIMES 80//最快58步
typedef enum REFER Refer;
typedef enum KEY Key;

enum REFER{//refer-指代,设置为三个字母,游戏地图整齐
	WAL,//墙
	FLR,//普通地板
	DES,//目的地地板
	MAN,//小人
	BOX,//箱子
	HIT,//到达目的地的箱子
	ALL
}pic;

IMAGE images[ALL];
IMAGE bg_image;//bg-blackground-background

enum KEY{//键入方向,有限
	UP,
	DOWN,
	LEFT,
	RIGHT,
}key;

struct _POS{
	int r;
	int c;
}man, box;
