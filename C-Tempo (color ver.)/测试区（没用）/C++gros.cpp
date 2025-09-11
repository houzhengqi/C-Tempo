#include <bits/stdc++.h>
#include <string>
#include <Windows.h>
#define K(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void color(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
struct MsicTime{
	int drc,pl,cl,len,can,gt;
}msic[1145][9];
int combo=0;
int MTsum[1145];
int MusicSum=5;
string btm=" ASDFGHJK";
string Name[114]={"Rrhar'il","Igallta","Spasmodic","Distorted Fate","DESTRUCTION 3,2,1"};
void Main_List_Print(int Chs){
	//
	HANDLE hOutput;
    COORD coord={0,0};
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    SetConsoleActiveScreenBuffer(hOutBuf);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=0;
    cci.dwSize=1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);
    //
	
    DWORD bytes=0;
    char data[1500];
    
	system("cls");
	if(Chs==0)color(14,0);else color(15,0);
	cout<<"--------------------"<<endl;
	color(15,0);
	for(int i=0;i<5;i++){
		if(Chs==i)color(14,0);else color(15,0);
		cout<<Name[i];if(Chs==i)cout<<"<";cout<<endl;
		if(Chs==i+1 || Chs==i)color(14,0);else color(15,0);
		cout<<"--------------------"<<endl;
	}
	ReadConsoleOutputCharacterA(hOutput, data, 1500, coord, &bytes);
    WriteConsoleOutputCharacterA(hOutBuf, data, 1500, coord, &bytes);
	
}
void Play(int Chs){
	//
	HANDLE hOutput;
    COORD coord={0,0};
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    SetConsoleActiveScreenBuffer(hOutBuf);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=0;
    cci.dwSize=1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);
    //
	color(15,0);
	system("cls");
	cout<<"loading...";
	memset(msic,0,sizeof(msic));
	if(Chs==0)freopen("0.in","r",stdin);
	if(Chs==1)freopen("1.in","r",stdin);
	if(Chs==2)freopen("2.in","r",stdin);
	if(Chs==3)freopen("3.in","r",stdin);
	if(Chs==4)freopen("4.in","r",stdin);
	if(Chs==5)freopen("5.in","r",stdin);
	int Sum=0,x=0,y=0;
	scanf("%d",&Sum);
	while(1){
		scanf("%d",&x);if(!x)break;scanf("%d",&y);
		MTsum[x]=y;//cout<<x<<" "<<y<<"\n";
		for(int i=1;i<=y;i++)
			{scanf("%d%d%d%d",&msic[x][i].drc,&msic[x][i].pl,&msic[x][i].cl,&msic[x][i].len);
			msic[x][i].can=1-(msic[x][i].cl==1);msic[x][i].gt=0;}
	}
	int tm=0;
	
    DWORD bytes=0;
    char data[1500];
    
    combo=0;
	for(double t=1;t<=Sum;t+=0.05){
		//system("cls");
		color(15,0);
		cout<<"   E R T Y U I O P\n\n";
		cout<<" -----------------\n";
		for(int k=7;k>=1;k--){
			int j=1;
			cout<<" ";
			cout<<" |";
			for(int i=1;i<=8;i++){
				if(i==msic[int(t+k)][j].pl){
					int cl=msic[int(t+k)][j].cl;
					if(cl==1)cout<<"V";else if(cl==2)cout<<".";j++;
					if(k<=3 && !K(btm[i]))msic[int(t+k)][j].can=1;
					if(K(btm[i]) && msic[int(t+k)][j].can){if(!msic[int(t+k)][j].gt)combo++;msic[int(t+k)][j].gt=1;}
				}
				else cout<<" ";
				if(i!=8)cout<<" ";
			}
			cout<<"|\n";
		}
		int j=1;
		cout<<"  -";
		for(int i=1;i<=8;i++){
			if(i==msic[int(t)][j].pl){
				if(K(btm[i])){
				if(msic[int(t)][j].can || msic[int(t)][j].gt){cout<<"O-";if(!msic[int(t)][j].gt)combo++;msic[int(t)][j].gt=1;}
				else cout<<"v-";
				}
				else {msic[int(t)][j].can=1;cout<<"v-";}
				j++;
			}
			else cout<<"--";
		}
		cout<<"\n  "; 
		j=1;
		for(int i=1;i<=8;i++){
			if(i==msic[int(t-1)][j].pl){
				if(!msic[int(t-1)][j].gt){cout<<" x";combo=0;}
				else cout<<"  ";
				j++;
			}
			else cout<<"  ";
		}
		cout<<"\n   A S D F G H J K\n";
		if(combo>=3)cout<<combo<<"\ncombo";
		//Sleep(1);
        ReadConsoleOutputCharacterA(hOutput, data, 1500, coord, &bytes);
        WriteConsoleOutputCharacterA(hOutBuf, data, 1500, coord, &bytes);
    }
}
int main(){
	cout<<"           CCCC    +       +      GGG   RR    OO    SSS\n";
	cout<<"          C        +       +     G  G  R  R  O  O  S\n";
	cout<<"          C     +++++++ +++++++   GGG  R     O  O   SS\n";
	cout<<"          C        +       +    G   G  R     O  O     S\n";
	cout<<"           CCCC    +       +     GGG   R      OO   SSS\n";
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n                       Click to Play";
	while(!K(' '));
	while(K(' '));
	system("cls"); 
	int Chs=0;
	while(1){
		Main_List_Print(Chs);
		while(!K('S') && !K('W') && !K(' '));
		if(K('S')){Chs=min(Chs+1,MusicSum-1);while(K('S'));}
		else if(K('W')){Chs=max(Chs-1,0);while(K('W'));}
		else Play(Chs);
	}
}
