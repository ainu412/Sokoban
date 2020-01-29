#include <iostream>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>
//ǽ: 0���ذ�: 1������Ŀ�ĵ�: 2,  С��: MAN,	����: BOX, ��������Ŀ��: HIT
//��̨���960*768mm
//��̨ͼƬ
//loadimage ���һ������:�Ƿ�������ͼƬ,true false��𲻴�

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

#define isValid(pos) pos.x>=0 && pos.x<ROW && pos.y>=0 && pos.y<COLUMN
enum _PROPS{//refer-ָ��
	WAL,//ǽ
	FLR,//��ͨ�ذ�
	DES,//Ŀ�ĵصذ�
	MAN,//С��
	BOX,//����
	HIT,//����Ŀ�ĵص�����
	ALL
}prop;
enum _DIRECTION{//���뷽��,����
	UP,
	DOWN,
	LEFT,
	RIGHT,
}direct;

struct _POS{
	int x;
	int y;
}man;

/*��Ϸ��ͼ*/
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

/**********************************
*�ı���Ϸ��ͼ��ͼ
*
*
*
***********************************/
void changeMap(int line, int column, enum _PROPS prop){
	map[line][column] = prop;
	putimage(START_CELLX+column*CELL, START_CELLY+line*CELL, &images[prop]);
}

void gameControl(enum _DIRECTION direct){
	int x = man.x;
	int y = man.y;

	struct _POS next_pos = man;
		switch(direct){
		case UP: 
			next_pos.x--;
			break;
		case DOWN:
			next_pos.x++;
			break;
		case LEFT:
			next_pos.y--;
			break;
		case RIGHT:
			next_pos.y++;
			break;		
		}

	if (isValid(man) && map[next_pos.x][next_pos.y] == FLR){
			changeMap(next_pos.x, next_pos.y, MAN);
			changeMap(man.x, man.y, FLR);
			man = next_pos;
	}
}



int main(){
	//��̨��
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image,_T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_image);

	//���ظ���ͼƬ
	loadimage(&images[WAL], _T("wall.bmp"), CELL, CELL, true); 
	loadimage(&images[FLR], _T("floor.bmp"), CELL, CELL, true); 
	loadimage(&images[DES], _T("des.bmp"), CELL, CELL, true); 
	loadimage(&images[MAN], _T("man.bmp"), CELL, CELL, true); 
	loadimage(&images[BOX], _T("box.bmp"), CELL, CELL, true); 
	loadimage(&images[HIT], _T("box.bmp"), CELL, CELL, true);
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			putimage(START_CELLX+c*CELL, START_CELLY+r*CELL, &images[map[r][c]]);
			if (map[r][c] == MAN){//ȷ��С�˳�ʼλ��
				man.x = c;
				man.y = r;
			}
		}
	}
	bool quit = false;
	while (quit == false){
		if (_kbhit()){
			char ch = _getch();
			if (ch == UPK){
				gameControl(UP);
			}else if (ch == DOWNK){
				gameControl(DOWN);
			}else if (ch == LEFTK){
				gameControl(LEFT);
			}else if (ch == RIGHTK){
				gameControl(RIGHT);
			}else if (ch == QUITK){
				quit = true;
			}
		}
		Sleep(100);//���0.1sʵ�п���,��ֹ��������Ƶ�ʹ���,Ӱ���ٶ�
	}

	system("pause");
	return 0;
}