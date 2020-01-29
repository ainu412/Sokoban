#include <iostream>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>

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

#define isValid(pic) pic.c >= 0 && pic.c < COLUMN && pic.r >= 0 && pic.r < ROW //判断下一位置是否超过格子群

enum REFER{//refer-指代,设置为三个字母,游戏地图整齐
	WAL,//墙
	FLR,//普通地板
	DES,//目的地地板
	MAN,//小人
	BOX,//箱子
	HIT,//到达目的地的箱子
	ALL
}pic;
/*游戏地图*/
int map[ROW][COLUMN] = {
	{   WAL,  WAL,   WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL	},
	{   WAL,  FLR,   WAL,  FLR,  FLR,  FLR,  FLR,  FLR,  FLR,  FLR,  WAL,  WAL	},
	{   WAL,  FLR,	 BOX,  FLR,  WAL,  DES,  FLR,  WAL,  DES,  FLR,  WAL,  WAL	},
	{   WAL,  FLR,   WAL,  FLR,  WAL,  FLR,  WAL,  WAL,  FLR,  FLR,  FLR,  WAL	},
	{   WAL,  FLR,   WAL,  DES,  WAL,  FLR,  FLR,  BOX,  FLR,  FLR,  FLR,  WAL	},
	{   WAL,  FLR,   FLR,  FLR,  WAL,  MAN,  FLR,  FLR,  FLR,  BOX,  FLR,  WAL	},
	{   WAL,  FLR,   DES,  FLR,  FLR,  BOX,  FLR,  FLR,  FLR,  FLR,  FLR,  WAL	},
	{   WAL,  FLR,   WAL,  WAL,  FLR,  WAL,  FLR,  FLR,  WAL,  WAL,  FLR,  WAL	},
	{   WAL,  WAL,   WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL,  WAL	},
};

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
}man;

//把坐标(x,y)的格子换成REFER对应图片
void changeMap(int r, int c, enum REFER pic){//定义枚举变量后函数调用-enum类型而非int型
	map[r][c] = pic;
	putimage(START_CELLX+c*CELL, START_CELLY+r*CELL, &images[pic]);
}

void keyCtrl(enum KEY key){
	struct _POS nxt = man;

	switch(key){
	case UP: 
		nxt.r--;
		break;
	case DOWN:
		nxt.r++;
		break;
	case LEFT:
		nxt.c--;
		break;
	case RIGHT:
		nxt.c++;
		break;		
	}
	if (isValid(man) && map[nxt.r][nxt.c] == FLR){
		changeMap(man.r, man.c, FLR);//把小人位置改成地板
		changeMap(nxt.r, nxt.c, MAN);//改变小人下一位置改为小人
		man = nxt;
	}
}

int main(){
	//搭台子
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image,_T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_image);

	//加载格子图片
	loadimage(&images[WAL], _T("wall.bmp"), CELL, CELL, true); 
	loadimage(&images[FLR], _T("floor.bmp"), CELL, CELL, true); 
	loadimage(&images[DES], _T("des.bmp"), CELL, CELL, true); 
	loadimage(&images[MAN], _T("man.bmp"), CELL, CELL, true); 
	loadimage(&images[BOX], _T("box.bmp"), CELL, CELL, true); 
	loadimage(&images[HIT], _T("box.bmp"), CELL, CELL, true);
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			putimage(START_CELLX+c*CELL, START_CELLY+r*CELL, &images[map[r][c]]);
			if (map[r][c] == MAN){//确定小人初始位置
				man.c = c;
				man.r = r;
			}
		}
	}
	bool quit = false;
	while (quit == false){
		if (_kbhit()){
			char ch = _getch();
			if (ch == UPK){
				keyCtrl(UP);
			}else if (ch == DOWNK){
				keyCtrl(DOWN);
			}else if (ch == LEFTK){
				keyCtrl(LEFT);
			}else if (ch == RIGHTK){
				keyCtrl(RIGHT);
			}else if (ch == QUITK){
				quit = true;
			}
		}
		Sleep(100);//间隔0.1s实行控制,防止程序运行频率过高,影响速度
	}

	system("pause");
	return 0;
}

//顺序编译:若A中使用B,则B要在A之前声明