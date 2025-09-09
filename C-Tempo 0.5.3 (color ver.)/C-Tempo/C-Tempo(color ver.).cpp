#include <iostream>
#include <cmath>
#include <thread>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <fstream>
#define K(VK_NONAME) ((GetAsyncKeyState(VK_NONAME)&0x8000)?true:false)
#define MV SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos)
#pragma comment(lib,"winmm.lib")
#pragma GCC optimize(2)
using namespace std;
struct GameData{
	bool f[114];
	double sc[114];
	double acc[114];
}Dt;
struct MsicTime{
	int drc,pl,cl,len,can,gt;
}msic[1145][33];
struct Player{
	int score,acc,miss,pf,mxcb;
};
double r[114],w[114];
string btm=" ASDFGHJKQWERTYUI",SC[10]={"F","C","B","A","S","V","AP"};
string Name[114]={"Rrhar'il","Igallta","Spasmodic","Distorted Fate","DESTRUCTION 3,2,1","LingGanGU","Cure For Me","Tetoris","Bounded Quietude"};
string tips[114]={"̫�����ˣ�     ","С���� @xErufy ","С���� @͵��ͷ ","hhh            ","��л����       ",
                  "ף�����մ��AP ","���Ը��޸Ŀ���","�ڲ��ڣ�       ","����������   ",
				  "��Ҫ��������ʹ!"};
bool lk[114]={false,true,true,false,false,true,true,true,true};
double spd[114]={0,12700,7421,0,0,13700,13000,8850,10700};
int Lv[114]={0,2,1,0,0,4,15,15,20};
int pre[114]={0,2600,5300,0,0,400,7900,1300,4300};
bool autoplay=0,ky[20],SAVE=true,Music=true,bk=true,save[114],New[114];
long long product=1,x,sum=0,scoresum=0;
int vol=30,skip=1,ls=1,vname=0,combo=0,MTsum[1145],MusicSum=20;
string Big[5][10]={"####","  ##","####","####","#  #","####","####","####","####","####",
				   "#  #","   #","   #","   #","#  #","#   ","#   ","   #","#  #","#  #",
				   "#  #","   #","####","####","#  #","####","####","   #","####","####",
				   "#  #","   #","#   ","   #","####","   #","#  #","   #","#  #","   #",
				   "####","   #","####","####","   #","####","####","   #","####","####"};
string grd[5][7]={"FFFF"," CCC","BBB "," AA "," SSS","V  V","  PAP",
				  "F   ","C   ","B  B","A  A","S   ","V  V","A A A",
				  "FFFF","C   ","BBB ","AAAA"," SS ","V  V","PAPAP",
				  "F   ","C   ","B  B","A  A","   S","V  V","  A  ",
				  "F   "," CCC","BBB ","A  A","SSS "," VV ","  P  "};
void setvol(int vol){
	char c[11451];
	sprintf(c,"setaudio 1 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"setaudio 2 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	//sprintf(c,"setaudio 3 volume to %d",vol);
	//mciSendString(c,NULL,0,NULL);
	//sprintf(c,"setaudio 4 volume to %d",vol);
	//mciSendString(c,NULL,0,NULL);
	sprintf(c,"setaudio 5 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"setaudio 6 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"setaudio 7 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"setaudio 8 volume to %d",vol);
	mciSendString(c,NULL,0,NULL);
	return;
}
void color(int ForgC,int BackC) {
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
	return;
}
void Vol_(bool V){
	COORD pos=(COORD){0,0};MV;
	if(V) vol=min(10,vol+1);
	else vol=max(0,vol-1);
	for(int i=0;i<vol;i++) cout<<" \n";
	color(0,11);
	for(int i=0;i<=10-vol;i++) cout<<" \n";
	color(15,0);
	pos=(COORD){0,12};MV;
	cout<<(10-vol)*10<<"    ";
	return;
}
void Vol(bool V){
    COORD pos;
	if(V){
		vol=min(50,vol+1);
		pos=(COORD){(SHORT)(vol+1),2};MV;
		color(0,11);
		cout<<" ";
	}
	else{
		vol=max(0,vol-1);
		pos=(COORD){(SHORT)(vol+2),2};MV;
		color(15,0);
		cout<<" ";
	}
	color(15,0);
	pos=(COORD){55,2};MV;
	cout<<vol*2<<"%  ";
	pos=(COORD){60,2};MV;
	cout<<"����";
	return;
}
void showcursor(bool visible){
    CONSOLE_CURSOR_INFO cursor={20,visible};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    return;
}
void setsize(int col,int row){
	char cmd[11451];
	sprintf(cmd,"mode con cols=%d lines=%d",col,row);
	system(cmd);
	return;
}
void setsize_(int col,int row){
	system("cls");
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize={0,0,(SHORT)(col+2),(SHORT)(row+2)};
    SetConsoleWindowInfo(hConsole,TRUE,&windowSize);
	return;
}
void saveData(const GameData* data,const char* filename){
    FILE* file=fopen(filename,"wb");
    if(file==NULL) return;
    fwrite(data,sizeof(GameData),1,file);
    fclose(file);
    return;
}
void loadData(GameData* data,const char* filename){
    FILE* file=fopen(filename,"rb");
    if(file==NULL) return;
    fread(data,sizeof(GameData),1,file);
    fclose(file);
    return;
}
void end(){
	mciSendString("close 1",NULL,0,NULL);
    mciSendString("close 2",NULL,0,NULL);
//    mciSendString("close 3",NULL,0,NULL);
//    mciSendString("close 4",NULL,0,NULL);
    mciSendString("close 5",NULL,0,NULL);
    mciSendString("close 6",NULL,0,NULL);
    mciSendString("close 7",NULL,0,NULL);
    mciSendString("close 8",NULL,0,NULL);
	return;
}
double Rks(){
    double d[114];
    for(int i=0;i<MusicSum;i++) d[i]=Dt.acc[i]*Lv[i];
    sort(d,d+MusicSum);
    double sum=0;
    int ans=0;
    for(int i=0;i<MusicSum;i++) ans+=!lk[i];
    for(int i=MusicSum-1;i>=MusicSum-3;i--) sum+=d[i];
    return sum/ans;
}
void Main_List_Print(int Chs){
	if(!bk) setsize(48,26);
	else setsize_(45,26);
    COORD pos;
	system("cls");
	if(Chs==0) color(14,0);
	else color(15,0);
	cout<<"-------------------------"<<endl;
	color(15,0);
	for(int i=0;i<MusicSum;i++){
		if(Chs==i) color(14,0);
		else color(15,0);
		cout<<Name[i];
		if(Chs==i) cout<<"<";
		for(int j=1;j<=20-Name[i].size();j++) cout<<" ";
		if(i==0){
			pos=(COORD){20,1};MV;
		}
		cout<<(lk[i]==0?(Chs==i?"locked":"\blocked"):"Lv.");
		if(lk[i]) printf("%.2d ",Lv[i]);
		cout<<endl;
		if(Chs==i+1||Chs==i) color(14,0);
		else color(15,0);
		cout<<"-------------------------"<<endl;
	}
	color(15,0);
	pos=(COORD){0,(SHORT)(Chs*2)};MV;
	return;
}
void Print_Move(int Chs,int Chs2,int lock){
    color(15,0);
    COORD pos;
    if(Chs==Chs2&&!lock){
        pos=(COORD){20,(SHORT)(1+2*Chs2)};MV;
        color(12,0);
        cout<<"locked ";
        return;
    }
    if(!lock){
        pos=(COORD){0,(SHORT)(2*Chs2)};MV;
        cout<<"-------------------------                   \n"<<Name[Chs2];
        for(int j=1;j<=20-Name[Chs2].size();j++) cout<<" ";
        cout<<(lk[Chs2]==0?"\blocked  ":"Lv.");
        if(lk[Chs2]) printf("%.2d    ",Lv[Chs2]);
        cout<<"\n-------------------------                  ";
        pos=(COORD){0,(SHORT)(2*Chs)};MV;
        color(14,0);
        cout<<"-------------------------                      \n"<<Name[Chs]<<"<";
        for(int j=1;j<=19-Name[Chs].size();j++) cout<<" ";
        cout<<(lk[Chs]==0?"locked ":" Lv.");
        if(lk[Chs]) printf("%.2d    ",Lv[Chs]);
        cout<<"\n-------------------------                   ";
    }
    for(int i=0;i<=25;i++){
        pos=(COORD){26,(SHORT)(ls+i)};MV;
        cout<<"                      ";
    }
    pos=(COORD){26,(SHORT)(2*max(0,Chs-6))};MV;
    if(bk) ls=2*max(0,Chs-6)-(Chs>=7?(Chs==7?2:4):0);
    else ls=2*max(0,Chs-6);
    if(Chs+6>MusicSum){
    	if(!bk){
		    pos=(COORD){26,(SHORT)(2*MusicSum-28)};MV;
		}
    	else{
    		pos=(COORD){26,(SHORT)(2*MusicSum-25)};MV;
		}
    	if(bk) ls=2*MusicSum-28;
    	else ls=2*MusicSum-24;
	}
    color(15,0);
    pos=(COORD){26,(SHORT)ls};MV;
    cout<<"  AUTOPLAY : "<<(autoplay?"ON":"OFF");
    pos=(COORD){26,(SHORT)(ls+1)};MV;
    cout<<"  MUSIC : "<<(Music?"ON":"OFF");
    pos=(COORD){26,(SHORT)(ls+2)};MV;
    cout<<"  SAVE : "<<(SAVE?"ON":"OFF");
    pos=(COORD){26,(SHORT)(ls+3)};MV;
    cout<<"  BK : "<<(bk?"ON":"OFF");
    pos=(COORD){26,(SHORT)(ls+5)};MV;
    cout<<"  R ���滺��(����SAVE)";
    pos=(COORD){26,(SHORT)(ls+6)};MV;
    cout<<"  W,S,A,D ���Ʒ���";
    pos=(COORD){26,(SHORT)(ls+7)};MV;
    cout<<"  �������Ҽ� ���Ʒ���";
    pos=(COORD){26,(SHORT)(ls+8)};MV;
    cout<<"  �ո�/�س� ѡ��";
    pos=(COORD){26,(SHORT)(ls+9)};MV;
    cout<<"  M �л���ʾ/��ϰ";
    pos=(COORD){26,(SHORT)(ls+10)};MV;
    cout<<"  ESC�˳�";
    pos=(COORD){26,(SHORT)(ls+11)};MV;
    cout<<"  Q ����/�ر���Ч";
    pos=(COORD){26,(SHORT)(ls+12)};MV;
    cout<<"  E ����/�ر��Զ�����";
    pos=(COORD){26,(SHORT)(ls+13)};MV;
    cout<<"  F �رձ߿�(���ɵ���)";
    pos=(COORD){26,(SHORT)(ls+19)};MV;
    cout<<"  C ����浵";
    pos=(COORD){26,(SHORT)(ls+14)};MV;
    int sc=round(Dt.sc[Chs]);
    if(sc<720000) sc=0;
    else if(sc<820000) sc=1;
    else if(sc<880000) sc=2;
    else if(sc<920000) sc=3;
    else if(sc<960000) sc=4;
    else if(sc<1000000) sc=5;
    else sc=6;
    if(Dt.f[Chs]&&SC[sc]=="AP"&&lk[Chs]!=0){
    	color(14,0);
		if(!save[Chs]&&New[Chs]) color(6,0);
	}
	else if(!save[Chs]&&New[Chs]) color(8,0);
    if(lk[Chs]!=0) printf("  %.07d ",(int)round(Dt.sc[Chs]));
    if(lk[Chs]!=0){
    	cout<<" "<<(Dt.f[Chs]?SC[sc]:"new")<<"   ";
		pos=(COORD){26,(SHORT)(ls+15)};MV;
	    string acc="  ACC "+to_string((int)(Dt.acc[Chs]*10000))+"%";
	    if(acc=="  ACC 0%") acc="  ACC 000%";
	    acc.insert(acc.size()-3,".");
	    cout<<acc<<"    ";
	    color(15,0);
	    pos=(COORD){26,(SHORT)(ls+16)};MV;
	    printf("  RKS %.2lf ",Rks());
	    pos=(COORD){26,(SHORT)(ls+17)};MV;
		color(7,0);
		//color(8,0);
	    cout<<"  tips:"<<tips[rand()%10];
	}
    else{
    	cout<<"  0000000 null"       ;
		pos=(COORD){26,(SHORT)(ls+15)};MV;
	    cout<<"  ACC null ";
	    color(15,0);
	    pos=(COORD){26,(SHORT)(ls+16)};MV;
	    printf("  RKS %.2lf ",Rks());
	    pos=(COORD){26,(SHORT)(ls+17)};MV;
	    //color(8,0);
	    color(7,0);
	    cout<<"  tips:"<<tips[rand()%10];
	    if(Dt.sc[Chs]!=0){
	    	pos=(COORD){26,(SHORT)(ls+25)};MV;
	    	color(4,0);
	    	cout<<"  666��������ǹ�";
		}
	}
    pos=(COORD){0,(SHORT)(2*min(MusicSum,Chs+6))};MV;
    return;
}
void Speed(int n){
	char c[11451];
	sprintf(c,"set 1 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"set 2 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	//sprintf(c,"set 3 speed %d",n);
	//mciSendString(c,NULL,0,NULL);
	//sprintf(c,"set 4 speed %d",n);
	//mciSendString(c,NULL,0,NULL);
	sprintf(c,"set 5 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"set 6 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"set 7 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	sprintf(c,"set 8 speed %d",n);
	mciSendString(c,NULL,0,NULL);
	return;
}
void Stop(){
	mciSendString("pause 1",NULL,0,NULL);
    mciSendString("pause 2",NULL,0,NULL);
//    mciSendString("pause 3",NULL,0,NULL);
//    mciSendString("pause 4",NULL,0,NULL);
    mciSendString("pause 5",NULL,0,NULL);
    mciSendString("pause 6",NULL,0,NULL);
    mciSendString("pause 7",NULL,0,NULL);
    mciSendString("pause 8",NULL,0,NULL);
    return;
}
void Start(){
	mciSendString("resume 1",NULL,0,NULL);
    mciSendString("resume 2",NULL,0,NULL);
//    mciSendString("resume 3",NULL 0,NULL);
//    mciSendString("resume 4",NULL,0,NULL);
    mciSendString("resume 5",NULL,0,NULL);
    mciSendString("resume 6",NULL,0,NULL);
    mciSendString("resume 7",NULL,0,NULL);
    mciSendString("resume 8",NULL,0,NULL);
	return;
}
void Print(string s,int x,int y){
	COORD pos=(COORD){(SHORT)x,(SHORT)y};MV;
	srand(time(0));
	for(int i=0;i<s.size();i++){
		color(8,0);
		for(int i=1;i<=5;i++){
			if(K(' ')||K(VK_RETURN)) skip=0;
			char t=rand()%94+33;
			cout<<t<<"\b";
			Sleep(skip*10);
		}
		color(15,0);
		cout<<s[i];
	}
	return;
}
void PrintBig(int n,int m){
	srand(time(0));
	color(8,0);
	COORD pos;
	for(int i=1;i<10;i++){
		int t=rand()%10;
		for(int j=1;j<=5;j++){
			if(K(' ')||K(VK_RETURN)) skip=0;
			pos=(COORD){(SHORT)(5*m),(SHORT)j};MV;
			cout<<Big[j-1][t];
		}
		Sleep(skip*15);
	}
	color(15,0);
	for(int j=1;j<=5;j++){
		pos=(COORD){(SHORT)(5*m),(SHORT)j};MV;
		cout<<Big[j-1][n];
	}
	return;
}
void PrintGrd(int sc){
	srand(time(0));
	if(sc<720000) sc=0;
	else if(sc<820000) sc=1;
	else if(sc<880000) sc=2;
	else if(sc<920000) sc=3;
	else if(sc<960000) sc=4;
	else if(sc<1000000) sc=5;
	else sc=6;
	for(int k=5;k>=1;k--){
		if(sc==6) color(6,0);
		else color(8,0);
		for(int j=1;j<=5;j++){
			COORD pos=(COORD){45,(SHORT)k};MV;
			char t=rand()%94+33;
			for(int i=0;i<grd[k-1][sc].size();i++){
				if(K(' ')||K(VK_RETURN)) skip=0;
				if(grd[k-1][sc][i]==' ') cout<<" ";
				else cout<<t;
			}
			Sleep(skip*1);
		}
		if(sc==6) color(14,0);
		else color(15,0);
		COORD pos=(COORD){45,(SHORT)k};MV;
		cout<<grd[k-1][sc];
		Sleep(skip*1);
	}
	return;
}
void Vol_UI(){
	color(15,0);
	system("cls");
	if(!bk) setsize(66,5);
	else setsize_(66,2);
	COORD pos=(COORD){2,1};MV;
	for(int i=0;i<50;i++) cout<<"-";
	cout<<"\n [";
	color(0,11);
	for(int i=1;i<=vol;i++) cout<<" ";
	color(15,0);
	pos=(COORD){52,2};MV;
	cout<<"]  "<<vol*2<<"%";
	pos=(COORD){60,2};MV;
	cout<<"����\n  ";
	for(int i=0;i<50;i++) cout<<"-";
	int ab=0;
	while(1){
		while(!K('D')&&!K('A')&&!K(VK_RETURN)&&!K(VK_SPACE)&&!K(VK_LEFT)&&!K(VK_RIGHT));
		if(K('A')||K(VK_LEFT) && vol>0) Vol(false);
		else if(K('D')||K(VK_RIGHT) && vol<50) Vol(true);
		else if(K(VK_RETURN)||K(VK_SPACE)) break;
		int ab=0;
		while(K('D')||K('A')||K(VK_RETURN)||K(VK_SPACE)||K(VK_LEFT)||K(VK_RIGHT)){
			if(K(VK_LEFT)||K(VK_RIGHT)||K('D')||K('A')) if(ab<214515) ab++;
			if(ab>=214514){
				if((K('A')||K(VK_LEFT)) && vol>0) Vol(false);
				else if((K('D')||K(VK_RIGHT)) && vol<50) Vol(true);
				else ab=0;
				Sleep(30);
			}
		}
	}
	setvol(vol*20);
	return;
}
void kick(double t,int n,bool UI){
	static int t_=0;
	if(t_==(int)(t)||!Music) return;
	if(!UI) t_=round(t);
	PlaySound(NULL,NULL,SND_PURGE);
	char name[114];
	sprintf(name,"..\\music\\Tap%d",n);
	PlaySound(TEXT(name),NULL,SND_ASYNC|SND_FILENAME|SND_NOSTOP|SND_NODEFAULT);
	return;
}
void getSystemName(){
	typedef void(__stdcall*NTPROC)(DWORD*,DWORD*,DWORD*);
	HINSTANCE hinst=LoadLibrary("ntdll.dll");
	DWORD dwMajor,dwMinor,dwBuildNumber;
	NTPROC proc=(NTPROC)GetProcAddress(hinst,"RtlGetNtVersionNumbers");
	proc(&dwMajor,&dwMinor,&dwBuildNumber);
	auto sharedUserData=(BYTE*)0x7FFE0000;
    if((int)*(ULONG*)(sharedUserData+0x260)>=22000){
		vname=7;
		return;
	}
	if(dwMajor==6&&dwMinor==3) cout<<"��֧�ֵ�ǰ�汾ϵͳ\n",system("pause"),exit(0);
	if(dwMajor==10&&dwMinor==0){
		vname=10;
		return;
	}
	OSVERSIONINFOEX osvi;
    osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
    if(GetVersionEx((OSVERSIONINFO*)&osvi)&&(osvi.dwMajorVersion==10)&&(osvi.dwMinorVersion==0&&osvi.dwBuildNumber>=22000)) vname=11;
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	#pragma warning(disable:4996)
	if(GetVersionEx((OSVERSIONINFO*)&os)){
		if(os.dwMajorVersion==6&&os.dwMinorVersion==1&&os.wProductType==VER_NT_WORKSTATION) vname=7;
		else if(os.dwMajorVersion==6&&os.dwMinorVersion==0&&os.wProductType==VER_NT_WORKSTATION) vname=10;
		else if(os.dwMajorVersion==5&&os.dwMinorVersion==1) vname=7;
		else cout<<"��֧�ֵ�ǰ�汾ϵͳ\n",system("pause"),exit(0);
	}
	else cout<<"��֧�ֵ�ǰ�汾ϵͳ\n",system("pause"),exit(0);
	return;
}
int Play(int Chs){
    if(!bk) setsize(23,17);
    else setsize_(20,14);
	color(15,0);
	system("cls");
	cout<<"ǰ��...";
	memset(msic,0,sizeof msic);
	memset(MTsum,0,sizeof MTsum);
	ifstream in;
	if(Chs==0){
		return 0;
		in.open("0.txt");
		if(Music){
			mciSendString("open ..\\music\\4.mp3 alias 0",NULL,0,NULL);
			mciSendString("play 0",NULL,0,NULL);
		}
	}
	if(Chs==1){
		in.open("1.txt");
		if(Music){
			mciSendString("open ..\\music\\1.mp3 alias 1",NULL,0,NULL);
			mciSendString("play 1",NULL,0,NULL);
		}
	}
	if(Chs==2){
		in.open("2.txt");
		if(Music){
			mciSendString("open ..\\music\\2.mp3 alias 2",NULL,0,NULL);
			mciSendString("play 2",NULL,0,NULL);
		}
	}
	if(Chs==3){
		return 0;
		in.open("3.txt");
		if(Music){
			mciSendString("open ..\\music\\3.mp3 alias 3",NULL,0,NULL);
			mciSendString("play 3",NULL,0,NULL);
		}
	}
	if(Chs==4){
		return 0;
		in.open("4.txt");
		if(Music){
			mciSendString("open ..\\music\\4.mp3 alias 4",NULL,0,NULL);
			mciSendString("play 4",NULL,0,NULL);
		}
	}
	if(Chs==5){
		in.open("5.txt");
		if(Music){
			mciSendString("open ..\\music\\5.mp3 alias 5",NULL,0,NULL);
			mciSendString("play 5",NULL,0,NULL);
		}
	}
	if(Chs==6){
		in.open("6.txt");
		if(Music){
			mciSendString("open ..\\music\\6.mp3 alias 6",NULL,0,NULL);
			mciSendString("play 6",NULL,0,NULL);
		}
	}
	if(Chs==7){
		in.open("7.txt");
		if(Music){
			mciSendString("open ..\\music\\7.mp3 alias 7",NULL,0,NULL);
			mciSendString("play 7",NULL,0,NULL);
		}
	}
	if(Chs==8){
		in.open("8.txt");
		if(Music){
		    mciSendString("open ..\\music\\8.mp3 alias 8",NULL,0,NULL);
			mciSendString("play 8",NULL,0,NULL);
		}
	}
	setvol(vol*20);
	Sleep(pre[Chs]);
	int Sum=0,x=0,y=0,TOT=0;
	in>>Sum;
	while(1){
		in>>x;
		if(!x) break;
		in>>y;
		MTsum[x]+=y;
		TOT+=y;
		for(int i=MTsum[x]-y+1;i<=MTsum[x];i++){
			in>>msic[x][i].drc>>msic[x][i].pl>>msic[x][i].cl>>msic[x][i].len;
			msic[x][i].can=1-(msic[x][i].cl!=2);msic[x][i].gt=0;
			if(msic[x][i].cl==3)
				for(int j=1;j<=msic[x][i].len;j++){
					msic[x+j][++MTsum[x+j]]=msic[x][i];
					msic[x+j][MTsum[x+j]].can=1;
					msic[x+j][MTsum[x+j]].cl=-j;
					msic[x+j][MTsum[x+j]].len=i;
				}
		}
	}
	int tm=0;
    system("cls");
	color(15,0);
	cout<<"   Q W E R T Y U I\n\n";
	cout<<"  ------------------\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  |                |\n";
	cout<<"  ------------------\n";
	cout<<"\n   A S D F G H J K\n\n\n�ո�/�س� ��ͣ\nESC �˳�";
    combo=0;
    int flsh=0; 
    using namespace std::chrono;
    using clock=steady_clock;
    auto cycle_duration=microseconds((int)spd[Chs]);
    auto next_cycle=clock::now()+cycle_duration;
    double score=0;
	int mxcmb=0,pfct=0,ot=0;
	for(double t=1;t<=Sum;t+=0.1){
		auto now=clock::now();
        auto offset=duration_cast<nanoseconds>(now-next_cycle).count();
        next_cycle+=cycle_duration;
        auto remaining=next_cycle-clock::now();
        if(remaining>microseconds(500)) std::this_thread::sleep_for(remaining-microseconds(400));
        while(clock::now()<next_cycle);
        clock::time_point pause_start;
	    microseconds total_pause_duration=microseconds(0);
	    bool is_paused=false;
		if (is_paused){
            auto now=clock::now();
            auto remaining=next_cycle-now;
            if (remaining>microseconds(500)){
                this_thread::sleep_for(remaining-microseconds(400));
            }
            while (clock::now()<next_cycle);
            next_cycle+=cycle_duration;
            continue;
        }
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS);
		score=(0.9*pfct/TOT+0.1*mxcmb/TOT)*1000000;
		if(K(' ')||K(VK_RETURN)){
			Stop();
			kick(999,11,true);
			is_paused=true;
            pause_start=clock::now();
			system("cls");
			Stop();
			color(15,0);
			COORD pos={9,6};MV;
			cout<<"����";
			pos={9,8};MV;
			cout<<"�ؿ�";
			pos={9,7};MV;
			color(0,15);
			cout<<"����";
			color(15,0);
			pos=(COORD){9,9};MV;
			cout<<"����";
			int D=2;
			while(K(' ')||K(VK_RETURN));
			while(1){
				auto now=clock::now();
                auto remaining=next_cycle-now;
                next_cycle+=cycle_duration;
				color(15,0);
				while(!K('W')&&!K(VK_UP)&&!K('S')&&!K(VK_DOWN)&&!K(' ')&&!K(VK_RETURN)&&!K('A')&&!K('D')&&!K(VK_LEFT)&&!K(VK_RIGHT));
				if(K('W')||K(VK_UP)){
					kick(999,13,true);
					D=max(1,D-1);
				}
				else if(K('S')||K(VK_DOWN)){
					kick(999,13,true);
					D=min(4,D+1);
				}
				if(K(' ')||K(VK_RETURN)){
					while(K(' ')||K(VK_RETURN));
					if(D==1){
						kick(999,1,true);
						end();
						return 0;
					}
					else if(D==2){
						kick(999,1,true);
						break;
					}
					else if(D==3){
						kick(999,1,true);
						end();
						return 1;
					}
					else if(D==4){
						kick(999,1,true);
						Vol_UI();
						kick(999,12,true);
						if(!bk) setsize(23,17);
						else setsize_(20,14);
						break;
					}
				}
				color(15,0);
				if(D==1) color(0,15);
				pos=(COORD){9,6};MV;
				cout<<"����";
				color(15,0);
				if(D==3) color(0,15);
				pos=(COORD){9,8};MV;
				cout<<"�ؿ�";
				color(15,0);
				if(D==2) color(0,15);
				pos=(COORD){9,7};MV;
				cout<<"����";
				color(15,0);
				if(D==4) color(0,15);
				pos=(COORD){9,9};MV;
				cout<<"����";
				while(K('W')||K(VK_UP)||K('S')||K(VK_DOWN)||K('A')||K('D')||K(VK_LEFT)||K(VK_RIGHT));
			}
			auto pause_end=clock::now();
            total_pause_duration+=duration_cast<microseconds>(pause_end-pause_start);
            next_cycle+=duration_cast<microseconds>(pause_end-pause_start);
            is_paused=false;
            Start();
			system("cls");
			color(15,0);
			cout<<"   Q W E R T Y U I\n\n";
			cout<<"  ------------------\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  |                |\n";
			cout<<"  ------------------\n";
			cout<<"\n   A S D F G H J K\n\n\n�ո�/�س� ��ͣ\nESC �˳�";
		}
		color(15,0);
		COORD pos={2,0};MV;  
		for(int i=9;i<=16;i++){
			color(15,0);
			cout<<" ";
			if(K(btm[i])||autoplay&&ky[i]) color(0,15);
			else color(15,0);
			cout<<btm[i];
		}
		memset(ky,0,sizeof ky);
		color(15,0);
		pos=(COORD){3,1};MV;
		if(flsh) cout<<"               ";
		int j=1;
		while(msic[int(t-1)][j].drc!=2) j++;
		color(12,0);
		if(autoplay)
			for(int j=1;j<=MTsum[int(t-1)];j++){
				if(msic[int(t-1)][j].drc!=2) continue;
				int i=msic[int(t-1)][j].pl-8;
				if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
					pos=(COORD){(SHORT)(i*2+1),1};MV;
					msic[int(t-1)][j].gt=-1;
					if(msic[int(t-1)][j].cl<0) msic[int(t-1)+msic[int(t-1)][j].cl][msic[int(t-1)][j].len].gt=-1;
					cout<<"x";
					combo=0;
				}
			}
		pos=(COORD){3,2};MV;
    	color(15,0);
		if(flsh) cout<<"---------------";
		for(int j=1;j<=MTsum[int(t)];j++){
			if(msic[int(t)][j].drc!=2) continue;
			int i=msic[int(t)][j].pl-8;
			pos=(COORD){(SHORT)(i*2+1),2};MV;
			if(K(btm[i+8])&&msic[int(t)][j].gt!=-1||autoplay){
				if(msic[int(t)][j].can||msic[int(t)][j].gt||autoplay){
					color(14,0);
					cout<<"O";
					int Tap;
					if(msic[int(t)][j].cl==1) Tap=14;
					if(msic[int(t)][j].cl==2) Tap=3;
					if(msic[int(t)][j].cl==3) Tap=14;
					if(msic[int(t)][j].cl>=0) kick(t,Tap,false);
					flsh=2;
					ot=1;
					if(!((msic[int(t)][j].cl==1)&&(int)t-t>0.5)) ky[i+8]=1;
				    if(!msic[int(t)][j].gt&&(msic[int(t)][j].cl!=3)){
						if(msic[int(t)][j].cl<0){
							int p=(msic[int(t)][j].cl==-msic[int(t)+msic[int(t)][j].cl][msic[int(t)][j].len].len);
							combo+=p;
							pfct+=p;
						}
						else combo++,pfct++;
					}
					msic[int(t)][j].gt=1;
				}
				else{
					color(15,0);
					cout<<"^";
				}
			}
			else{
				msic[int(t)][j].can=1;
				color(15,0);
				cout<<"^";
			}
		}
		for(int k=7;k>=1;k--){
			pos=(COORD){3,(SHORT)(10-k)};MV;
    		if(flsh) cout<<"               ";
			for(int j=1;j<=MTsum[int(t+k)];j++){
				if(msic[int(t+k)][j].drc!=1) continue;
				int i=msic[int(t+k)][j].pl;
				pos=(COORD){(SHORT)(2*i+1),(SHORT)(10-k)};MV;
				int cl=msic[int(t+k)][j].cl;
				if(cl==1){
					color(11,0);
					cout<<"��";
				}
				else if(cl==2){
					color(14,0);
					cout<<".";
				}
				else if(cl==3){
					color(11,0);
					cout<<"X";
				}
				else if(cl<0){
					if(msic[int(t+k)+msic[int(t+k)][j].cl][msic[int(t+k)][j].len].gt==-1){
						color(0,9);
						msic[int(t+k)][j].gt=-1;
					}
					else color(0,11);
					cout<<" ";
					color(15,0);
				}
				if(k<=2&&!K(btm[i])) msic[int(t+k)][j].can=1;
				if(msic[int(t+k)][j].cl!=2&&msic[int(t+k)][j].cl>0&&K(btm[i])&&msic[int(t+k)][j].can){
					if(!msic[int(t+k)][j].gt) combo++,pfct++;
					msic[int(t+k)][j].gt=1;
				}
			}
			for(int j=1;j<=MTsum[int(t+8-k)];j++){
				if(msic[int(t+8-k)][j].drc!=2) continue;
				int i=msic[int(t+8-k)][j].pl-8;
				pos=(COORD){(SHORT)(2*i+1),(SHORT)(10-k)};MV;
				int cl=msic[int(t+8-k)][j].cl; 
				if(cl==1){
					color(11,0);
					cout<<"��";
				}
				else if(cl==2){
					color(14,0);
					cout<<".";
				}
				else if(cl==3){
					color(11,0);
					cout<<"X";
				}
				else if(cl<0){
					if(msic[int(t+8-k)+msic[int(t+8-k)][j].cl][msic[int(t+8-k)][j].len].gt==-1){
						color(0,9);
						msic[int(t+8-k)][j].gt=-1;
					}
					else color(0,11);
					cout<<" ";
					color(15,0);
				}
				if(k>=6&&!K(btm[i+8])) msic[int(t+8-k)][j].can=1;
				if(msic[int(t+8-k)][j].cl!=2&&msic[int(t+8-k)][j].cl>0&&K(btm[i+8])&&msic[int(t+8-k)][j].can){
					if(!msic[int(t+8-k)][j].gt) combo++,pfct++;
					msic[int(t+8-k)][j].gt=1;
				}
			}
		}
		color(15,0);
		pos=(COORD){3,10};MV; 
		if(flsh) cout<<"---------------";
		for(int j=1;j<=MTsum[int(t)];j++){
			if(msic[int(t)][j].drc!=1) continue;
			int i=msic[int(t)][j].pl;
			pos=(COORD){(SHORT)(i*2+1),10};MV;
			if(K(btm[i])&&msic[int(t)][j].gt!=-1||autoplay){
				if(msic[int(t)][j].can||msic[int(t)][j].gt||autoplay){
					color(14,0);
					cout<<"O";
					int Tap;
					if(msic[int(t)][j].cl==1) Tap=14;
					if(msic[int(t)][j].cl==2) Tap=3;
					if(msic[int(t)][j].cl==3) Tap=14;
					if(msic[int(t)][j].cl>=0) kick(t,Tap,false);
					flsh=2;
					ot=1;
					if(!((msic[int(t)][j].cl==1)&&t-(int)t>0.7)) ky[i]=1;
					if(!msic[int(t)][j].gt&&(msic[int(t)][j].cl!=3)){
						if(msic[int(t)][j].cl<0){
							int p=(msic[int(t)][j].cl==-msic[int(t)+msic[int(t)][j].cl][msic[int(t)][j].len].len);
							combo+=p;
							pfct+=p;
						}
						else combo++,pfct++;
					}
					msic[int(t)][j].gt=1;
				}
				else{
					color(15,0);
					cout<<"v";
				}
			}
			else {
				msic[int(t)][j].can=1;
				color(15,0);
				cout<<"v";
			}
		}
		pos=(COORD){3,11};MV;
		if(flsh) cout<<"               ";
		color(12,0);
		if(!autoplay)
			for(int j=1;j<=MTsum[int(t-1)];j++){
				if(msic[int(t-1)][j].drc!=1) continue;
				int i=msic[int(t-1)][j].pl;
				if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
					pos=(COORD){(SHORT)(i*2+1),11};MV;
					msic[int(t-1)][j].gt=-1;
					if(msic[int(t-1)][j].cl<0) msic[int(t-1)+msic[int(t-1)][j].cl][msic[int(t-1)][j].len].gt=-1;
					cout<<"x";
					combo=0;
				}
			}
		else
			for(int j=1;j<=MTsum[int(t)];j++){
		        if(!msic[int(t)][j].gt){
		            pfct++;
		            msic[int(t)][j].gt=1;
		        }
		    }
		mxcmb=max(mxcmb,combo);
		color(15,0);
		pos=(COORD){2,12};MV;  
		for(int i=1;i<=8;i++){
			color(15,0);
			cout<<" ";
			if(K(btm[i])||autoplay&&ky[i]) color(0,15);
			else color(15,0);
			cout<<btm[i];
		}
		pos=(COORD){0,13};MV;
		color(15,0);
		if(combo>=3) cout<<combo<<"     \n"<<(autoplay?"AUTOPLAY":"combo");
		else cout<<"            \n                     ";
		if(ot){
			int out=round(score);
			pos=(COORD){12,13};MV;
			printf("%.07d",out);
			ot=0;
		}
		color(15,0);
		if(int(t+0.1)!=int(t)||t==2)flsh=1;
		else flsh=0;
		color(15,0);
		if(vname==10){
			pos=(COORD){18,3};MV;
			cout<<" ";
			pos=(COORD){18,4};MV;
			cout<<" ";
			pos=(COORD){18,5};MV;
			cout<<" ";
			pos=(COORD){18,6};MV;
			cout<<" ";
			pos=(COORD){18,7};MV;
			cout<<" ";
			pos=(COORD){18,8};MV;
			cout<<" ";
			pos=(COORD){18,9};MV;
			cout<<" ";
		}
    }
    end();
	//||
    if(!autoplay&&SAVE){
    	Dt.sc[Chs]=max(score,Dt.sc[Chs]);
		Dt.acc[Chs]=max(pfct*1.0/TOT,Dt.acc[Chs]);
		Dt.f[Chs]=1;
    	saveData(&Dt,"Data.dat");
    	save[Chs]=true;
	}
	else if(!SAVE&&!autoplay){
		Dt.sc[Chs]=max(score,Dt.sc[Chs]);
		Dt.acc[Chs]=max(pfct*1.0/TOT,Dt.acc[Chs]);
		Dt.f[Chs]=1;
		New[Chs]=true;
	}
	if(autoplay)  mxcmb=0,pfct=0,score=0;
    color(15,0);
	if(!bk) setsize(60,20);
	else setsize_(57,17);
    COORD pos=(COORD){37,0};MV;
    cout<<"Click to Skip";
    skip=1;
    int u=score;
    int prtscore[8];
    for(int i=6;i>=0;i--){
    	prtscore[i]=u%10;
    	u/=10;
	}
	string mxcb="MaxCombo "+to_string(mxcmb);
	string pf="Perfect "+to_string(pfct);
	string miss="Miss "+to_string(TOT-pfct);
	string acc="ACC "+to_string(pfct*10000/TOT)+"%";
	acc.insert(acc.size()-3,".");
	if(Music){
		if(Rks()>=20) mciSendString("open ..\\music\\d.mp3 alias LO",NULL,0,NULL);
		else if(Rks()>=15) mciSendString("open ..\\music\\c.mp3 alias LO",NULL,0,NULL);
		else if(Rks()>=10) mciSendString("open ..\\music\\b.mp3 alias LO",NULL,0,NULL);
		else mciSendString("open ..\\music\\a.mp3 alias LO",NULL,0,NULL);
		mciSendString("play LO repeat",NULL,0,NULL);
	}
	Print(Name[Chs],0,0);
    for(int t=0;t<7;t++) PrintBig(prtscore[t],t);
	Print(mxcb,0,7);
	Print(pf,15,7);
	Print(miss,30,7);
	Print(acc,40,7);
	PrintGrd(score);
	scoresum+=score;
	pos=(COORD){37,0};MV;
    cout<<"             ";
    int D=0;
	while(1){
		while(K('A')||K(VK_LEFT)||K('D')||K(VK_RIGHT)||K(' ')||K(VK_RETURN));
		color(15,0);
		if(D==0) color(0,15);
		pos={20,10};MV;
		cout<<"����";
		color(15,0);
		if(D==1) color(0,15);
		pos={35,10};MV;
		cout<<"�ؿ�";
		color(15,0);
		while(!K('A')&&!K(VK_LEFT)&&!K('D')&&!K(VK_RIGHT)&&!K(' ')&&!K(VK_RETURN));
		if(K('A')||K(VK_LEFT)){
			kick(999,13,true);
			D=0;
		}
		if(K('D')||K(VK_RIGHT)){
			kick(999,13,true);
			D=1;
		}
		if(K(' ')||K(VK_RETURN)){
			while(K(' ')||K(VK_RETURN));
			if(Music) mciSendString("close LO",NULL,0,NULL);
			if(D==1){
				kick(999,14,true);
				Vol_UI();
				kick(999,14,true);
			}
			return D;
		}
	}
	return -1;
}
void help(){
	system("echo 123>help.txt");
	ofstream out("help.txt");
	out.seekp(0);
	out<<"R ���滺��(����SAVEʹ��)\n";
	out<<"W,S,A,D ���Ʒ���\n";
	out<<"�������Ҽ� ���Ʒ���\n";
	out<<"�ո�/�س� ѡ��\n";
	out<<"M �л���ʾ/��ϰ\n";
	out<<"ESC�˳�\n";
	out<<"Q ����/�ر���Ч\n";
	out<<"E ����/�ر��Զ�����\n";
	out<<"F �رձ߿�(���ɵ���)";
	out.close();
	system("notepad help.txt");
	system("del help.txt");
	return;
}
int main(){
	srand(time(NULL));
	getSystemName();
	system("title C-Tempo");
    if(!bk) setsize(70,21);
    else setsize_(68,18);
    showcursor(false);
	SetWindowLong(GetConsoleWindow(),GWL_STYLE,GetWindowLong(GetConsoleWindow(),GWL_STYLE)&~WS_MAXIMIZEBOX);
	/*
	����Ͱ
    SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)&~WS_CAPTION);
    SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
    */
	cout<<"\n\n             CCCC         TTTTT EEEEE  M   M  PPPP    OOO \n";
	cout<<"            C               T   E      M M M  P   P  O   O\n";
	cout<<"            C      -----    T   EEEEE  M M M  PPPP   O   O\n";
	cout<<"            C               T   E      M   M  P      O   O\n";
	cout<<"             CCCC           T   EEEEE  M   M  P       OOO \n";
	cout<<"\n\n\n\n\n\n\n\n\n\n                           Click to Play";
	loadData(&Dt,"data.dat");
    COORD pos;
    color(8,0);
    pos=(COORD){57,19};MV;
	cout<<"����\"Q\"������";
    pos=(COORD){55,18};MV;
	cout<<"  ��Ч : "<<(Music?"ON ":"OFF");
	while(!K(' ')&&!K(VK_RETURN)){
		if(K('Q')){
			Music^=1;
			pos=(COORD){55,18};MV;
			cout<<"  ��Ч : "<<(Music?"ON ":"OFF");
			while(K('Q'));
		}
		if(GetFocus()==GetConsoleWindow()) cout<<1;
	}
	while(K(' ')||K(VK_RETURN));
	pos=(COORD){0,0};
	if(Music) kick(999,11,true);
	int Chs=0;
	Main_List_Print(Chs);
	Print_Move(Chs,Chs,1);
	while(1){
		int lst=(Chs+MusicSum-1)%MusicSum,nxt=(Chs+1)%MusicSum;
		while(!K('S')&&!K(VK_DOWN)&&!K('W')&&!K(VK_UP)&&!K(' ')&&!K(VK_RETURN)&&!K('M')&&!K('Q')&&!K('E')&&!K('C')&&!K('F')&&!K('R'));
		if(K('S')||K(VK_DOWN)){
			kick(999,5,true);
			Print_Move(nxt,Chs,0);
			Chs=nxt;
			Sleep(100);
		}
		if(K('W')||K(VK_UP)){
			kick(999,5,true);
			MV;
			Print_Move(lst,Chs,0);
			Chs=lst;
		}
		if(K('M')){
			kick(999,5,true);
			autoplay^=1;
			Print_Move(Chs,Chs,1);
		}
		if(K('Q')){
			Music^=1;
			if(Music) kick(999,5,true);
			Print_Move(Chs,Chs,1);
		}
		if(K('E')){
			kick(999,5,true);
			SAVE^=1;
			Print_Move(Chs,Chs,1);
		}
		if(K('C')){
			kick(999,5,true);
			while(1){
				system("cls");
				pos=(COORD){13,12};MV;
				cout<<"ȷ������浵��(Y/N)";
				char c=getch();
				if(c=='y'||c=='Y'){
					memset(&Dt,0,sizeof(Dt));
					saveData(&Dt,"data.dat");
					break;
				}
				if(c=='n'||c=='N') break;
			}
			kick(999,11,true);
			Main_List_Print(Chs);
			Print_Move(Chs,Chs,1);
		}
		if(K('F')){
			if(!bk){
				MessageBox(NULL,"�Ѿ�û�б߿���~","��ʾ",MB_OK);
				continue;
			}
			bk=false;
			MusicSum=12;
			Chs=0;
			Main_List_Print(Chs);
			Print_Move(Chs,Chs,1);
		}
		if(K('R')){
			saveData(&Dt,"data.dat");
			memset(&save,true,sizeof save);
			memset(&New,false,sizeof New);
			Print_Move(Chs,Chs,1);
		}
		if(K(' ')||K(VK_RETURN)){
			if(lk[Chs]==0) Print_Move(Chs,Chs,0);
			else{
				while(K(' ')||K(VK_RETURN));
				kick(999,12,true);
				Vol_UI();
				setvol(vol*20);
				kick(999,12,true);
				int f=Play(Chs);
				while(f==1){
					f=Play(Chs);
					loadData(&Dt,"data.dat");
				}
				Main_List_Print(Chs);
				Print_Move(Chs,Chs,1);
			}
		}
		while(K('S')||K(VK_DOWN)||K('W')||K(VK_UP)||K(' ')||K(VK_RETURN)||K('M')||K('Q')||K('E')||K('C')||K('F')||K('R'));
	}
	return 0;
}
