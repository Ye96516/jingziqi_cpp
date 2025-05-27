#include <graphics.h>
#include <iostream>
using namespace std;
char BoardData[3][3]={
	{'-','-','-'},
	{'-','-','-'},
	{'-','-','-'},
};
char CurrentPiece='o';
struct Screen{
    static int px;  // 声明静态成员变量（在结构体内部）
	static int py;
	static int sx;  // 声明静态成员变量（在结构体内部）
	static int sy;
};
int Screen::px=100;
int Screen::py=200;
int Screen::sx=600;
int Screen::sy=600;

void PrintArray(char v[3][3]){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
		if(i==2){
			cout<<endl;
		}
	}
};
//判断胜利
bool CheckWin(char e){
	int c=0;
	//横竖判断
	for(int i=0;i<3;++i){
		for(int ii=0;ii<3;++ii){
			if(BoardData[i][ii]==e){
			c+=1;
			}else{
				c=0;
				break;
			}
		}
		if (c==3){
			return true;
		}
	}
	//斜线判断
	for(int i=0;i<3;++i){
		if(BoardData[i][i]==e){
			c+=1;
		}else{
			c=0;
			break;
		}
	}
	for(int i=2;i>-1;--i){
		if(BoardData[i][i]==e){
			c+=1;
		}else{
			c=0;
			break;
		}
	}
	if (c==3){
		return true;
		}
	return false;
};
//判断平局
bool CheckDraw(){
	for(int i=0;i<3;++i){
		for(int ii=0;ii<3;++ii){
			if(BoardData[i][ii]=='-'){
				return false;
			}
		}
	}
	return true;
};
//绘制棋盘
void DrawBoard(){
	line(0,200,600,200);
	line(0,400,600,400);
	line(200,0,200,600);
	line(400,0,400,600);
};
//绘制棋子
void DrawPiece(){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			switch (BoardData[i][j])
			{
			case 'o':
				circle(200*j+100,200*i+100,100);
				break;
			case 'x':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
    			break;
			}
		}
	}
};
//绘制提示信息
void DrawTip(){
	static TCHAR str[64];
	_stprintf_s(str,_T("当前棋子类型：%c"),CurrentPiece);
	//输出文字的颜色
	settextcolor(RGB(255,175,45));
	//输出文字的内容和位置
	outtextxy(0,0,str);
};
//处理落子
void HandleMove(int x,int y){
	x=x/200;
	y=y/200;
	if(BoardData[y][x]=='-'){
		BoardData[y][x]=CurrentPiece;
		// PrintArray(BoardData);
		if(CurrentPiece=='o'){
			CurrentPiece='x';
		}else{
			CurrentPiece='o';
		}
	}
};
//入口函数
int main()
{	//初始化屏幕
	initgraph(Screen::sx,Screen::sy);
	//设置窗口初始位置
    SetWindowPos(
        GetHWnd(),           // 窗口句柄
        NULL,           // 无层级调整
        Screen::px,Screen::py,        // 新的左上角坐标 (x, y)
       0,0,           // 不修改窗口尺寸（保持原尺寸）
        SWP_NOZORDER | SWP_NOSIZE
    );

	//游戏运行状态
	bool IsRunning = true;
	//游戏主循环
	// PrintArray(BoardData);
	while (IsRunning)
	{
		DWORD StartTime = GetTickCount();
		//事件处理
		ExMessage msg;
		// PrintArray(BoardData);
		while(peekmessage(&msg)){
			if (msg.message==WM_LBUTTONDOWN){
				HandleMove(msg.x,msg.y);
			}
		}
		
		//渲染处理
		BeginBatchDraw();
		cleardevice();
		//初始化棋盘
		DrawBoard();
		//绘制棋子
		DrawPiece();
		//提示
		DrawTip();
		FlushBatchDraw();
		
		if (CheckWin('x')){
			MessageBox(GetHWnd(),_T("x获胜"),_T("游戏结束"),MB_OK);
			IsRunning=false;
		}else if(CheckWin('o')){
			MessageBox(GetHWnd(),_T("o获胜"),_T("游戏结束"),MB_OK);
			IsRunning=false;
		}else if(CheckDraw()){
			MessageBox(GetHWnd(),_T("平局"),_T("游戏结束"),MB_OK);
			IsRunning=false;
		};
		DWORD FinishTime = GetTickCount();
		float DeltaTime=(FinishTime-StartTime)/1000.0f;
		if(DeltaTime<1.0/60.0){
			Sleep(DeltaTime-1.0/60.0);
		};
	}
	


	

	return 0;
}