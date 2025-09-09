#include <iostream>
#include <windows.h>
#define K(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void color(int ForgC, int BackC) {
    WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
    return;
}
int sumt,cnt;
struct node{
	int clr,tm;
}ovo[11451][17];
int ln[11451][17];
void Move(int x,int y){
	COORD pos=(COORD){(SHORT)(y-1),(SHORT)(x-1)};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	return;
}
void print(int t){
	for(int i=t+1;i<=t+7;i++){
		Move(t+9-i,2);
		color(15,0);
		cout<<"                ";
		Move(t+9-i,2);
		for(int j=1;j<=8;j++){
			node k=ovo[i][j];
			if(k.clr==0){
				if(ln[i][j]) color(0,15);
				cout<<" ";
				color(15,0);
				cout<<" ";
			}
			else if(k.clr==1) cout<<"กý";
			else if(k.clr==2) cout<<". ";
			else if(k.clr==3) cout<<"X ";
		}
	}
	Move(9,19);
	cout<<"ึก"<<t<<"  ";
	return;
}
int main() {
	freopen("print.txt","r",stdin);
	cout<<"------------------\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"|                |\n";
	cout<<"------------------\n";
	cin>>sumt;
	int in1,in2,u=0;
	cin>>in1;
	while(in1){
		cin>>in2;
		for(int i=1;i<=in2;i++){
			int d,p,c,t;
			cin>>d>>p>>c>>t;
			ovo[in1][p].clr=c;
			ovo[in1][p].tm=t;
			if(c==3) for(int j=1;j<=t-1;j++) ln[in1+j][p]=1;
		}
		cin>>in1;
	}
	int T=1,pl=1;
	print(T);
	Move(8,pl*2);
	while(1){
		if(K('W')) T=max(0,T-1);
		if(K('S')) T++;
		if(K('A')) pl=max(0,pl-1);
		if(K('D')) pl=min(8,pl+1);
		if(K(VK_RETURN)){
			while(K(VK_RETURN));
			Move(9,21);
			cout<<"     ";
			Move(9,21);
			int t=0;
			while(!K(VK_RETURN)){
				for(int i='0';i<='9';i++){
					if(K(i)){
						t=t*10+i-'0';
						cout<<i-'0';
						while(K(i));
					}
				}
				if(K(VK_NUMPAD0)){
					t=t*10+0;
					cout<<0;
					while(K(VK_NUMPAD0));
				}
				if(K(VK_NUMPAD1)){
					t=t*10+1;
					cout<<1;
					while(K(VK_NUMPAD1));
				}
				if(K(VK_NUMPAD2)){
					t=t*10+2;
					cout<<2;
					while(K(VK_NUMPAD2));
				}
				if(K(VK_NUMPAD3)){
					t=t*10+3;
					cout<<3;
					while(K(VK_NUMPAD3));
				}
				if(K(VK_NUMPAD4)){
					t=t*10+4;
					cout<<4;
					while(K(VK_NUMPAD4));
				}
				if(K(VK_NUMPAD5)){
					t=t*10+5;
					cout<<5;
					while(K(VK_NUMPAD5));
				}
				if(K(VK_NUMPAD6)){
					t=t*10+6;
					cout<<6;
					while(K(VK_NUMPAD6));
				}
				if(K(VK_NUMPAD7)){
					t=t*10+7;
					cout<<7;
					while(K(VK_NUMPAD7));
				}
				if(K(VK_NUMPAD8)){
					t=t*10+8;
					cout<<8;
					while(K(VK_NUMPAD8));
				}
				if(K(VK_NUMPAD9)){
					t=t*10+9;
					cout<<9;
					while(K(VK_NUMPAD9));
				}
				if(K(VK_BACK)&&t){
					t=t/10;cout<<"\b \b";
					while(K(VK_BACK));
				}
			}
			T=t;
			while(K(VK_RETURN));
			print(T);
			color(15,0);
		}
		if(K('W')||K('S')) print(T);
		Move(8,pl*2);
		cnt=0;
		while((K('W')||K('S')||K('A')||K('D'))&&!K('F')){
			if(K('W')||K('S')) cnt=min(cnt+1,154514);
			if(cnt>=154514){
				if(K('W')) T=max(0,T-1);
				if(K('S')) T++;
				print(T);
				Sleep(10);
			}
			if(!K('W')&&!K('S')) cnt=0;
		}
		while(!K('W')&&!K('S')&&!K('A')&&!K('D')&&!K(VK_RETURN));
	}
    return 0;
}
