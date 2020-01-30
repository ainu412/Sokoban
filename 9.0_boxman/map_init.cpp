#include "boxman.h"

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

//把坐标(x,y)的格子换成REFER对应图片
void changeMap(struct _POS *object, Refer pic){//定义枚举变量后函数调用-enum类型而非int型
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
		changeMap(&man, FLR);//把小人位置改成地板
		changeMap(&nxt, MAN);//改变小人下一位置改为小人
		man = nxt;
	}else if (isValid(nxt_nxt) && map[nxt.r][nxt.c] == BOX){
		if(map[nxt_nxt.r][nxt_nxt.c] == DES){//箱子前面是目的地
			changeMap(&nxt_nxt, HIT);//小人的下下个为击中的箱子
			changeMap(&man, FLR);//把小人位置改成地板
			changeMap(&nxt, MAN);//改变小人下一位置,改为小人
			man = nxt;
		}else if(map[nxt_nxt.r][nxt_nxt.c] == FLR){//箱子前面是地
			changeMap(&nxt_nxt, BOX);//改变箱子下一位置,改为箱子
			changeMap(&man, FLR);//把小人位置改成地板
			changeMap(&nxt, MAN);//改变小人下一位置,改为小人
			man = nxt;
		}
	}
}

//遍历判断地图中是否所有目的地都击中,即遍历判断是否全部不是DES目的地
bool success(){
	for (int r=0; r<ROW; r++){
		for (int c=0; c<COLUMN; c++){
			if (map[r][c] == DES)	return false;//若某列某行为目的地,则未成功
		}
	}
	return true;
}

void closingScene(bool success){	
	putimage(0, 0, &bg_image); 
	settextcolor(WHITE);
	RECT rec = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	settextstyle(30, 0, _T("黑体"));
	if (success){
		drawtext(_T("恭喜您~ \n 您终于成为了一个合格的搬箱子老司机！"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
	}else {
		drawtext(_T("超过步数了,失败！"), &rec,	DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	Sleep(1000);
}

int main(){
	//搭台子
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_image, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
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
	int times = 0;
	while (1){
		if (_kbhit()){
			char ch = _getch();
			times++;
			if (times  > TIMES){
				closingScene(success());//打印失败
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
			}if (success()){//先移动地图,再判断成功
				Sleep(100);//若成功先在成功位置停留0.1s
				closingScene(success());//打印成功
				break;//退出
			}
			Sleep(100);//间隔0.1s实行控制,防止程序运行频率过高,影响速度
		}
	}
	closegraph();
	return 0;
}

//顺序编译:若A中使用B,则B要在A之前声明