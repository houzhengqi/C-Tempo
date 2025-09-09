#include <bits/stdc++.h>
#include <windows.h>
#define K(VK_NONAME) ((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
#define MV SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos)
using namespace std;
string SC[10]={"  F  ","  C  ","  B  ","  A  ","  S  ","  V  "," AP  "};
struct GameData{
	bool f[114];
	double sc[114];
	double acc[114];
}Dt;
struct Pos{
	int x,y;
}POS={0,0};
int loadData(GameData* data,const char* filename){
    FILE* file=fopen(filename,"rb");
    if(file==NULL) return 0;
    fread(data,sizeof(GameData),1,file);
    fclose(file);
    return 1;
}
void saveData(const GameData* data,const char* filename){
    FILE* file=fopen(filename,"wb");
    if(file==NULL) return;
    fwrite(data,sizeof(GameData),1,file);
    fclose(file);
    return;
}
void color(int ForgC,int BackC) {
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
	return;
}
int main(){
	//SetWindowLong(GetConsoleWindow(),GWL_STYLE,GetWindowLong(GetConsoleWindow(),GWL_STYLE)&~WS_MAXIMIZEBOX);
	loadData(&Dt,"data.dat");
	for(int i=0;i<20;i++){
		if(POS.x==0&&POS.y==i) color(0,15);
		printf("%.2lf%%  ",Dt.acc[i]*100);
		color(15,0);
		cout<<" ";
	}
	cout<<endl;
	for(int i=0;i<20;i++){
		int sc=round(Dt.sc[i]);
	    if(sc<720000) sc=0;
	    else if(sc<820000) sc=1;
	    else if(sc<880000) sc=2;
	    else if(sc<920000) sc=3;
	    else if(sc<960000) sc=4;
	    else if(sc<1000000) sc=5;
	    else sc=6;
		cout<<(Dt.f[i]?SC[sc]:"  new  ")<<" ";
	}
	cout<<endl;
	for(int i=0;i<20;i++){
		if(POS.x==2&&POS.y==i) color(0,15);
		printf("%.7d",(int)Dt.sc[i]);
		color(15,0);
		cout<<" ";
	}
	while(1){
		while(!K('A')&&!K('D')&&!K('W')&&!K('S')&&!K(VK_LEFT)&&!K(VK_RIGHT)
		&&!K(VK_NUMPAD0)&&!K(VK_NUMPAD1)&&!K(VK_NUMPAD2)&&!K(VK_NUMPAD3)&&!K(VK_NUMPAD4)
		&&!K(VK_NUMPAD5)&&!K(VK_NUMPAD6)&&!K(VK_NUMPAD7)&&!K(VK_NUMPAD8)&&!K(VK_NUMPAD9)
		&&!K('0')&&!K('1')&&!K('2')&&!K('3')&&!K('4')
		&&!K('5')&&!K('6')&&!K('7')&&!K('8')&&!K('9'));
		COORD pos={0,0};MV;
		cout<<endl<<"                                                                                                                                                                                                                                                                                                                                                                                       ";
		MV;
		if(K('D')||K(VK_RIGHT)) POS.y=min(19,POS.y+1);
		if(K('A')||K(VK_LEFT)) POS.y=max(0,POS.y-1);
		if(K('W')||K(VK_UP)) POS.x=max(0,POS.x-1);
		if(K('S')||K(VK_DOWN)) POS.x=min(2,POS.x+1);
		for(int i=0;i<20;i++){
			if(POS.x==0&&POS.y==i) color(0,15);
			printf("%.2lf%%  ",Dt.acc[i]*100);
			if(K(VK_NUMPAD0)||K(VK_NUMPAD1)||K(VK_NUMPAD2)||K(VK_NUMPAD3)||K(VK_NUMPAD4)
			||K(VK_NUMPAD5)||K(VK_NUMPAD6)||K(VK_NUMPAD7)||K(VK_NUMPAD8)||K(VK_NUMPAD9)
			||K('0')||K('1')||K('2')||K('3')||K('4')
			||K('5')||K('6')||K('7')||K('8')||K('9')){
				if(POS.x==0&&POS.y==i){
					cout<<"\b\b\b\b\b\b\b       \b\b\b\b\b\b\b";
					double cnt;
					cin>>cnt;
					Dt.acc[i]=fmin((double)cnt/100,1.0);
					Dt.f[i]=true;
				}
			}
			color(15,0);
			cout<<" ";
		}
		cout<<endl;
		for(int i=0;i<20;i++){
			int sc=round(Dt.sc[i]);
		    if(sc<720000) sc=0;
		    else if(sc<820000) sc=1;
		    else if(sc<880000) sc=2;
		    else if(sc<920000) sc=3;
		    else if(sc<960000) sc=4;
		    else if(sc<1000000) sc=5;
		    else sc=6;
			if(POS.x==1&&POS.y==i) color(0,15);
			cout<<(Dt.f[i]?SC[sc]:"  new  ");
			color(15,0);
			cout<<" ";
		}
		cout<<endl;
		for(int i=0;i<20;i++){
			if(POS.x==2&&POS.y==i) color(0,15);
			printf("%.7d",(int)Dt.sc[i]);
			if(K(VK_NUMPAD0)||K(VK_NUMPAD1)||K(VK_NUMPAD2)||K(VK_NUMPAD3)||K(VK_NUMPAD4)
			||K(VK_NUMPAD5)||K(VK_NUMPAD6)||K(VK_NUMPAD7)||K(VK_NUMPAD8)||K(VK_NUMPAD9)
			||K('0')||K('1')||K('2')||K('3')||K('4')
			||K('5')||K('6')||K('7')||K('8')||K('9')){
				if(POS.x==2&&POS.y==i){
					cout<<"\b\b\b\b\b\b\b       \b\b\b\b\b\b\b";
					int cnt;
					cin>>cnt;
					Dt.sc[i]=min(1000000,cnt);
					Dt.f[i]=true;
				}
			}
			color(15,0);
			cout<<" ";
		}
		saveData(&Dt,"data.dat");
		while(K('A')||K('D')||K('W')||K('S')||K(VK_LEFT)||K(VK_RIGHT)
		||K(VK_NUMPAD0)||K(VK_NUMPAD1)||K(VK_NUMPAD2)||K(VK_NUMPAD3)||K(VK_NUMPAD4)
		||K(VK_NUMPAD5)||K(VK_NUMPAD6)||K(VK_NUMPAD7)||K(VK_NUMPAD8)||K(VK_NUMPAD9)
		||K('0')||K('1')||K('2')||K('3')||K('4')
		||K('5')||K('6')||K('7')||K('8')||K('9'));
	}
	return 0;
}
