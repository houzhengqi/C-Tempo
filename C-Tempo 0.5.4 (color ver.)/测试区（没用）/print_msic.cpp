#include <iostream>
#include <windows.h>
#define K(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
void color(int ForgC,int BackC){
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}
int lst[8][64],print[1145][4];
int main(){
	int T;
	cout<<"W,S,A,D���ƹ��\n�ո�/�س����ü�\nM����������ɫ\nN�������ķ���\nP��ʼ��ӡ\n��һ�еļ����ж�������ʱ��ʱ��Ϊ:";
	cin>>T;
	system("cls");
	int x=0,y=63;
	for(int i=64;i>=1;i--){
		printf("% 3d OOOOOOOO\n",i);
	}
	int mod=0;
	COORD pos = {x+4,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	int r=1,fx=1;
	while(1){
		while(!K('W')&&!K('S')&&!K('A')&&!K('D')&&!K(' ')&&!K('M')&&!K('P')&&!K('N')&&!K(VK_RETURN)) r=1;
		if(K('P')) break;
		if(K(' ')||K(VK_RETURN)){
			if(lst[x+fx*8-8][63-y]){
				lst[x+fx*8-8][63-y]=0;
				color(7,0);
			}
			else{
				lst[x+fx*8-8][63-y]=mod+1;
				if(mod==0) color(11,0);
				else if(mod==1) color(14,0);
				else if(mod==2) color(0,11);
				else if(mod==3) color(0,14);
			}
			cout<<"O";
		}
		if(K('M')) mod=(mod+1)%4;
		if(K('N')) fx=3-fx;
		if(K('M')||K('W')||K('S')||K('N')){
			color(7,0);
			COORD pos={18,max(0,y-1)};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
			cout<<"                           ";
			pos={18,y+1};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
			cout<<"                              ";
			pos={18,y};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
			cout<<"MOD:";
			if(mod==0) cout<<"����  ";
			else if(mod==1) cout<<"�Ƽ�  ";
			else if(mod==2) cout<<"HOLD��ͷ  ";
			else if(mod==3) cout<<"HOLD��β  ";
			cout<<"����"<<(fx==1?"down      ":"up      ");
		}
		if(K('W')) if(y) y--;
		if(K('S')) if(y<63) y++;
		if(K('A')) if(x) x--;
		if(K('D')) if(x<7) x++;
		COORD pos={x+4,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
		while(K(' ')||((K('M')||K('W')||K('S')||K('A')||K('D')||K('N')||K(VK_RETURN))&&r<50)){
			Sleep(1);
			r++;
		}
		Sleep(100);
	}
	system("cls");
	freopen("print.txt","w",stdout);
	color(7,0);
	for(int i=0;i<64;i++){
		int sum=0;
		for(int j=0;j<16;j++) if(lst[j][i]!=4&&lst[j][i]!=0) sum++;
		if(!sum) continue;
		cout<<T+i<<" "<<sum<<endl;
		for(int j=0;j<16;j++){
			int len=0;
			if(lst[j][i]==3) while(lst[j][i+len]!=4) len++;
			if(lst[j][i]!=4&&lst[j][i]!=0) cout<<j/8+1<<" "<<j+1<<" "<<lst[j][i]<<" "<<len<<"\n";
		}
	}
	return 0; 
}
