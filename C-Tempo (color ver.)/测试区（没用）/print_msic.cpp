#include <iostream>
#include <windows.h>
#include <cstring>
#define K(VK_NONAME) GetAsyncKeyState(VK_NONAME)&0x8000
using namespace std;
void color(int ForgC,int BackC){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),((BackC&0x0F)<<4)+(ForgC&0x0F));
}
int lst[16][64]={0};
int print[1145][4];
int main(){
    memset(lst,0,sizeof lst);
    int T;
    cout<<"W,S,A,D���ƹ��\n";
	cout<<"�ո�/�س����ü�\n";
	cout<<"M����������ɫ\n";
	cout<<"N�������ķ���\n";
	cout<<"P��ʼ��ӡ\n";
	cout<<"��һ�еļ����ж�������ʱ��ʱ��Ϊ:";
    cin>>T;
    system("cls");
    int x=0,y=63;
    for(int i=64;i>=1;i--) printf("% 3d OOOOOOOO\n",i);
    int mod=0;
    COORD pos={x+4,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    int r=1,fx=1;
    while(1){
        while(!K('W')&&!K('S')&&!K('A')&&!K('D')&&!K(' ')&&!K('M')&&!K('P')&&!K('N')&&!K(VK_RETURN)) r=1;
        if(K('P')) break;
        if(K(' ')||K(VK_RETURN)){
            int track=x+fx*8-8;
            int time=63-y;
            if(track>=0&&track<16&&time>=0&&time<64){
                if(lst[track][time]){
                    lst[track][time]=0;
                    color(7,0);
                }
				else{
                    lst[track][time]=mod+1;
                    if(mod==0) color(11,0);
                    else if(mod==1) color(14,0);
                    else if(mod==2) color(0,11);
                    else if(mod==3) color(0,14);
                }
                cout<<"O";
            }
        }
        if(K('M')) mod=(mod+1)%4;
        if(K('N')) fx=3-fx;
        if(K('M')||K('W')||K('S')||K('N')) {
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
        while((K(' ')||K('M')||K('W')||K('S')||K('A')||K('D')||K('N')||K(VK_RETURN))&&r<50) {
            Sleep(1);
            r++;
        }
        Sleep(100);
    }
    system("cls");
    freopen("print.txt", "w", stdout);
    color(7,0);
    for(int i=0;i<64;i++){
        int sum=0;
        for(int j=0;j<16;j++) if(lst[j][i]!=0&&lst[j][i]!=4) sum++;
        if(!sum) continue;
        cout<<T+i<<" "<<sum<<endl;
        for(int j=0;j<16;j++) {
            if(lst[j][i]!=0&&lst[j][i]!=4) {
                int len=0;
                if(lst[j][i]==3){
                    while(i+len<64&&lst[j][i+len]!=4) len++;
                    if(i+len>=64) len=0;
                }
                int direction=(j<8)?1:2;
                int position=(j%8)+1;
                cout<<direction<<" "<<position<<" "<<lst[j][i]<<" "<<len<<"\n";
            }
        }
    }
    return 0;
}
