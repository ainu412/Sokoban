#include "boxman.h"

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

//������(x,y)�ĸ��ӻ���REFER��ӦͼƬ
void changeMap(struct _POS *object, Refer pic){//����ö�ٱ�����������-enum���Ͷ���int��
	map[object->r][object->c] = pic;
	putimage(START_CELLX+object->c*CELL, START_CELLY+object->r*CELL, &images[pic]);
}

void keyCtrl(Key key){
	struct _POS nxt = man;
	struct _POS nxt_nxt = man;

	switch(key){
	case UP: 
		nxt.r--;
		nxt_nxt.r-=2;
		break;
	case DOWN:
		nxt.r++;
		nxt_nxt.r+=2;
		break;
	case LEFT:
		nxt.c--;
		nxt_nxt.c-=2;
		break;
	case RIGHT:
		nxt.c++;
		nxt_nxt.c+=2;
		break;		
	}
	if (isValid(nxt) && map[nxt.r][nxt.c] == FLR){
		changeMap(&man, FLR);//��С��λ�øĳɵذ�
		changeMap(&nxt, MAN);//�ı�С����һλ�ø�ΪС��
		man = nxt;
	}else if (isValid(nxt_nxt) && map[nxt.r][nxt.c] == BOX){
		if(map[nxt_nxt.r][nxt_nxt.c] == DES){//����ǰ����Ŀ�ĵ�
			changeMap(&nxt_nxt, HIT);//С�˵����¸�Ϊ���е�����
			changeMap(&man, FLR);//��С��λ�øĳɵذ�
			changeMap(&nxt, MAN);//�ı�С����һλ��,��ΪС��
			man = nxt;
		}else if(map[nxt_nxt.r][nxt_nxt.c] == FLR){//����ǰ���ǵ�
			changeMap(&nxt_nxt, BOX);//�ı�������һλ��,��Ϊ����
			changeMap(&man, FLR);//��С��λ�øĳɵذ�
			changeMap(&nxt, MAN);//�ı�С����һλ��,��ΪС��
			man = nxt;
		}
	}
}

//�����жϵ�ͼ���Ƿ�����Ŀ�ĵض�����,�������ж��Ƿ�ȫ������DESĿ�ĵ�
bool success(){
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			if (map[r][c] == DES)	return false;//��ĳ��ĳ��ΪĿ�ĵ�,��δ�ɹ�
		}
	}
	return true;
}

void closingScene(bool success){	
	putimage(0, 0, &bg_image); 
	settextcolor(WHITE);
	RECT rec = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	settextstyle(30, 0, _T("����"));
	if (success){
		drawtext(_T("��ϲ��~ \n �����ڳ�Ϊ��һ���ϸ�İ�������˾����"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
	}else {
		drawtext(_T("����������,ʧ�ܣ�"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	Sleep(1000);
}

int main(){
	//��̨��
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
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
				man.c = c;
				man.r = r;
			}
		}
	}
	int times = 0;
	while (1){
		if (_kbhit()){
			char ch = _getch();
			times++;
			if (times  > TIMES){
				closingScene(success());//��ӡʧ��
				break;
			}else if (ch == UPK){
				keyCtrl(UP);
			}else if (ch == DOWNK){
				keyCtrl(DOWN);
			}else if (ch == LEFTK){
				keyCtrl(LEFT);
			}else if (ch == RIGHTK){
				keyCtrl(RIGHT);
			}else if (ch == QUITK){
				break;
			}if (success()){//���ƶ���ͼ,���жϳɹ�
				Sleep(100);//���ɹ����ڳɹ�λ��ͣ��0.1s
				closingScene(success());//��ӡ�ɹ�
				break;//�˳�
			}
			Sleep(100);//���0.1sʵ�п���,��ֹ��������Ƶ�ʹ���,Ӱ���ٶ�
		}
	}
	closegraph();
	return 0;
}

//˳�����:��A��ʹ��B,��BҪ��A֮ǰ����