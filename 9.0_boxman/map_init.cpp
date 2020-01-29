#include <iostream>
#include <graphics.h>
#include <Windows.h>
//墙: 0，地板: 1，箱子目的地: 2,  小人: 3,	箱子: 4, 箱子命中目标: 5
//舞台宽度960*768mm
//舞台图片
//loadimage 最后一个参数:是否是拉伸图片,true false差别不大
IMAGE images[6];
IMAGE bg_image;//bg-blackground-background
#define ROW 9
#define COLUMN 12
#define SCREEN_WIDTH 1190
#define SCREEN_HEIGHT 800
#define START_CELLX (SCREEN_WIDTH-COLUMN*CELL)/2
#define START_CELLY (SCREEN_HEIGHT-ROW*CELL)/2
#define CELL 61

/*游戏地图*/
int map[ROW][COLUMN] = {
{   0,  0,  0,  0,  0,  0,  0,  0,  0,	0,  0,  0	},
{   0,  1,  0,  1,  1,  1,  1,  1,  1,	1,  0,  0	},
{	0,	1,	4,	1,	0,	2,	1,	0,	2,	1,	0,	0	},
{	0,	1,	0,	1,	0,	1,	0,	0,	1,	1,	1,	0	},
{	0,	1,	0,	2,	0,	1,	1,	4,	1,	1,	1,	0	},
{	0,	1,	1,	1,	0,	3,	1,	1,	1,	4,	1,	0	},
{	0,	1,	2,	1,	1,	4,	1,	1,	1,	1,	1,	0	},
{	0,	1,	0,	0,	1,	0,	1,	1,	0,	0,	1,	0	},
{	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
};

int main1(){
	//搭台子
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image,_T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_image);

	//加载格子图片
	loadimage(&images[0], _T("wall.bmp"), CELL, CELL, true); 
	loadimage(&images[1], _T("floor.bmp"), CELL, CELL, true); 
	loadimage(&images[2], _T("des.bmp"), CELL, CELL, true); 
	loadimage(&images[3], _T("man.bmp"), CELL, CELL, true); 
	loadimage(&images[4], _T("box.bmp"), CELL, CELL, true); 
	loadimage(&images[5], _T("box.bmp"), CELL, CELL, true);
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			putimage(START_CELLX+c*CELL, START_CELLY+r*CELL, &images[map[r][c]]);
		}
	}


	system("pause");
	return 0;
}