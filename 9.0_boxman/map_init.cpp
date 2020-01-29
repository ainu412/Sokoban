#include <iostream>
#include <graphics.h>
#include <Windows.h>
//ǽ: 0���ذ�: 1������Ŀ�ĵ�: 2,  С��: 3,	����: 4, ��������Ŀ��: 5
//��̨���960*768mm
//��̨ͼƬ
//loadimage ���һ������:�Ƿ�������ͼƬ,true false��𲻴�
IMAGE images[6];
IMAGE bg_image;//bg-blackground-background
#define ROW 9
#define COLUMN 12
#define SCREEN_WIDTH 1190
#define SCREEN_HEIGHT 800
#define START_CELLX (SCREEN_WIDTH-COLUMN*CELL)/2
#define START_CELLY (SCREEN_HEIGHT-ROW*CELL)/2
#define CELL 61

/*��Ϸ��ͼ*/
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
	//��̨��
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image,_T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_image);

	//���ظ���ͼƬ
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