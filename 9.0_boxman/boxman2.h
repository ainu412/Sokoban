/*******************************************
*��Ϸ����:
*1.����С���ƶ�:w��,s��,a��,d��,q�˳�
*
*2.ע��:�˿��԰����Ӵ�����Ŀ�ĵ����ƿ�
*С�˲��ܴ�����/ǽ���߹�
*�˿��Դ�����Ŀ�ĵ����߹�
*
*3.Ŀ��:�����ٲ���,��������������Ŀ�ĵ�
********************************************/

#include <iostream>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>//_kbhit()��_getch()

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

#define isValid(pic) pic.c >= 0 && pic.c < COLUMN && pic.r >= 0 && pic.r < ROW  //�ж���һλ���Ƿ񳬹�����Ⱥ

#define TIMES 80//���58��
static int times = 0;//ֻ���ڰ��������ͷ�ļ���cpp�ļ���ʹ��
#define FONT_HEIGHT 30
#define FONT_WIDTH 30
#define LINE_HEIGHT 40
#define TEXT_W_START 200
#define TEXT_H_START 150
typedef enum REFER Refer;
typedef enum KEY Key;

enum REFER{//refer-ָ��,����Ϊ������ĸ,��Ϸ��ͼ����
	WAL,//ǽ
	FLR,//��ͨ�ذ�
	DES,//Ŀ�ĵصذ�
	MAN,//С��
	BOX,//����
	HIT,//����Ŀ�ĵص�����
	MAN_DES,//վ��Ŀ�ĵ��ϵ�С��
	ALL
}pic;

IMAGE images[ALL];
IMAGE bg_image;//bg-blackground-background

enum KEY{//���뷽��,����
	UP,
	DOWN,
	LEFT,
	RIGHT,
}key;

struct _POS{
	int r;
	int c;
}man, box;
