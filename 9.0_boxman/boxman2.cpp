#include "boxman2.h"

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

	if (isValid(nxt)){
		if (map[man.r][man.c] == MAN_DES){
			if (map[nxt.r][nxt.c] == FLR){
				changeMap(&man, DES);//��С��λ�øĳ�Ŀ�ĵ�
				changeMap(&nxt, MAN);//�ı�С����һλ�ø�ΪС��
				man = nxt;
			}else if (map[nxt.r][nxt.c] == DES){//��һλ����Ŀ�ĵ�
				changeMap(&man, DES);//��С��λ�øĳ�Ŀ�ĵ�
				changeMap(&nxt, MAN_DES);//�ı�С����һλ�ø�ΪС��վ��Ŀ�ĵ���
				man = nxt;
			}else if (map[nxt.r][nxt.c] == BOX || map[nxt.r][nxt.c] == HIT){
				if(map[nxt_nxt.r][nxt_nxt.c] == DES){//����ǰ����Ŀ�ĵ�
					changeMap(&nxt_nxt, HIT);//С�˵����¸�Ϊ���е�����
					changeMap(&man, DES);//��С��λ�øĳ�Ŀ�ĵ�
					changeMap(&nxt, MAN);//�ı�С����һλ��,��ΪС��
					man = nxt;
				}else if(map[nxt_nxt.r][nxt_nxt.c] == FLR){//����ǰ���ǵ�
					changeMap(&nxt_nxt, BOX);//�ı�������һλ��,��Ϊ����
					changeMap(&man, DES);//��С��λ�øĳ�Ŀ�ĵ�
					changeMap(&nxt, MAN);//�ı�С����һλ��,��ΪС��
					man = nxt;
				}
			}
		}else{
			if (map[nxt.r][nxt.c] == FLR){
				changeMap(&man, FLR);//��С��λ�øĳɵذ�
				changeMap(&nxt, MAN);//�ı�С����һλ��,��ΪС��
				man = nxt;
			}else if (map[nxt.r][nxt.c] == DES){//��һλ����Ŀ�ĵ�
				changeMap(&man, FLR);//��С��λ�øĳɵذ�
				changeMap(&nxt, MAN_DES);//�ı�С����һλ��,��ΪС��վ��Ŀ�ĵ���
				man = nxt;
			}else if (map[nxt.r][nxt.c] == BOX){
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
			}else if (map[nxt.r][nxt.c] == HIT){
				if(map[nxt_nxt.r][nxt_nxt.c] == DES){//����ǰ����Ŀ�ĵ�
					changeMap(&nxt_nxt, HIT);//С�˵����¸�Ϊ���е�����
					changeMap(&man, FLR);//��С��λ�øĳɵذ�
					changeMap(&nxt, MAN_DES);//�ı�С����һλ��,��Ϊ��Ŀ�ĵ��ϵ�С��
					man = nxt;
				}else if(map[nxt_nxt.r][nxt_nxt.c] == FLR){//����ǰ���ǵ�
					changeMap(&nxt_nxt, BOX);//�ı�������һλ��,��Ϊ����
					changeMap(&man, FLR);//��С��λ�øĳɵذ�
					changeMap(&nxt, MAN_DES);//�ı�С����һλ��,��Ϊ��Ŀ�ĵ��ϵ�С��
					man = nxt;
				}
			}
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
	settextstyle(FONT_HEIGHT,0 , _T("����"));
	//easyX����ַ�
	TCHAR s[5];//s������2��15(=2*8-1)�η�������
	_stprintf_s(s, _T("%d"), TIMES, sizeof(s));
	TCHAR t[5];//s������2��15(=2*8-1)�η�������
	_stprintf_s(t, _T("%d"), times, sizeof(t));

	if (success){
		//drawtext(_T("��ϲ��~ \n �����ڳ�Ϊ��һ���ϸ�İ�������˾����"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);//ֻ����������ַ���
		outtextxy(TEXT_W_START, TEXT_H_START, "��ϲ��~ \n �����ڳ�Ϊ��һֻ�ϸ�İ������⣡");
		outtextxy(TEXT_W_START, TEXT_H_START+LINE_HEIGHT, "���߹��Ĳ���Ϊ:");//8����(��ð��)
		outtextxy(TEXT_W_START+8*FONT_WIDTH, TEXT_H_START+LINE_HEIGHT, t);
		outtextxy(TEXT_W_START, TEXT_H_START+2*LINE_HEIGHT, "�趨ͨ�ز���Ϊ:");//8����(��ð��)
		outtextxy(TEXT_W_START+8*FONT_WIDTH, TEXT_H_START+2*LINE_HEIGHT, s);
	}else {
		//drawtext(_T("��������",TIMES,"��,ʧ�ܣ�"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);��-ֻ����������ַ���
		outtextxy(TEXT_W_START, TEXT_H_START, "�����趨����:");//7����(��ð��)
		outtextxy(TEXT_W_START+7*FONT_WIDTH, TEXT_H_START, s);
		outtextxy(TEXT_W_START, TEXT_H_START+LINE_HEIGHT, "ʧ�ܵ�����������!");
	}
	Sleep(5000);
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
	loadimage(&images[MAN_DES], _T("man.bmp"), CELL, CELL, true);
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			putimage(START_CELLX+c*CELL, START_CELLY+r*CELL, &images[map[r][c]]);
			if (map[r][c] == MAN){//ȷ��С�˳�ʼλ��
				man.c = c;
				man.r = r;
			}
		}
	}
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
	closegraph();//�ǵùر�ͼ��
	return 0;
}

//˳�����:��A��ʹ��B,��BҪ��A֮ǰ����