#include <iostream>
#include <cmath>
#include <thread>
#include <windows.h>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <atomic>
#include <conio.h>
#include <shellapi.h>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma GCC optimize(2)
using namespace std;
struct GameData{
    bool f[114];
    double sc[114];
    double acc[114];
    bool achievements[20];
    int achievementProgress[20];
    time_t totalPlayTime;
    int consecutivePlays;
}Dt;
struct MsicTime{
    int drc,pl,cl,len,can,gt;
}msic[1145][33];
double r[114],w[114];
string btm=" ASDFGHJKQWERTYUI";
string SC[10]={"F","C","B","A","S","V","AP"};
string Name[114]={"Rrhar'il","Igallta","Spasmodic","Distorted Fate","DESTRUCTION 3,2,1","LingGanGU","Cure For Me","Tetoris","Bounded Quietude","caidan~","caidanPlus~","114514"};
string tips[114]={"太带派了！     ","小红书 @xErufy ","小红书 @偷妈头 ","hhh            ","感谢游玩       ","祝你早日打出AP ","试试改修改开关","在不在？       ","打歌容易上瘾   ","不要当播放器使!"};
bool lk[114]={false,true,true,false,false,true,true,true,true,false,false,false};
int spd[114];
int Lv[114]={0,2,1,0,0,4,15,15,20,-1,-1,-1};
int pre[114];
bool autoplay,ky[20],SAVE=true,Music=true,border=true,save[114],New[114],refresh;
long long scoresum;
atomic<bool> stop_flag;
int vol=30,skip=1,ls=1,combo,MTsum[1145],MusicSum=20;
string Big[5][10]={"####","  ##","####","####","#  #","####","####","####","####","####",
                   "#  #","   #","   #","   #","#  #","#   ","#   ","   #","#  #","#  #",
                   "#  #","   #","####","####","#  #","####","####","   #","####","####",
                   "#  #","   #","#   ","   #","####","   #","#  #","   #","#  #","   #",
                   "####","   #","####","####","   #","####","####","   #","####","####"};
string grd[5][7]={"####"," ###","### "," ## "," ###","#  #","  ###",
                  "#   ","#   ","#  #","#  #","#   ","#  #","# # #",
                  "####","#   ","### ","####"," ## ","#  #","#####",
                  "#   ","#   ","#  #","#  #","   #","#  #","  #  ",
                  "#   "," ###","### ","#  #","### "," ## ","  #  "};
struct Achievement {
    string name;
    string description;
    bool unlocked;
    int progress;
    int target;
};
Achievement achievements[15]={
    {"初出茅庐","完成任意一首歌曲",false,0,1},
    {"完美主义者","任意歌曲ACC达到100%",false,0,1},
    {"全连大师","任意歌曲达成Full Combo",false,0,1},
    {"节奏达人","总游戏时长超过10分钟",false,0,600},
    {"收藏家","解锁所有可玩歌曲",false,0,1},
    {"彩蛋猎人","发现彩蛋歌曲",false,0,1},
    {"坚持不懈","连续游玩5首歌曲",false,0,5},
    {"精准打击","单局游戏ACC超过95%",false,0,1},
    {"百万分数","单局得分超过1,000,000",false,0,1},
    {"连击之王","达成200连击",false,0,200},
    {"全难度制霸","所有难度歌曲都完成",false,0,1},
    {"夜猫子","在深夜时段玩游戏",false,0,1},
    {"周末战士","在周末完成游戏",false,0,1},
    {"完美连击","单局无Miss完成",false,0,1}
};
int achievementCount=14;
int unlockedAchievements=0;
time_t totalPlayTime=0;
time_t gameStartTime=0;
int consecutivePlays=0;
int lastPlayedSong=-1;
void color(int ForgC,int BackC){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),((BackC&0x0F)<<4)+(ForgC&0x0F));
    return;
}
void setsize(int col,int row){
    char cmd[114];
    sprintf(cmd,"mode %d,%d",col,row);
    system(cmd);
    return;
}
void setsize_(int col,int row){
    color(15,0);
    system("cls");
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize={0,0,(SHORT)(col+2),(SHORT)(row+2)};
    SetConsoleWindowInfo(hConsole,TRUE,&windowSize);
    return;
}
void kick(double t,int n,bool ui){
    static int t_=0;
    if(t_==(int)(t)||!Music) return;
    if(!ui) t_=round(t);
    PlaySound(NULL,NULL,SND_PURGE);
    char name[114];
    sprintf(name,"..\\music\\Tap%d",n);
    PlaySound(name,NULL,SND_ASYNC|SND_FILENAME|SND_NOSTOP|SND_NODEFAULT);
    return;
}
void clrscr(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    DWORD size=csbi.dwSize.X*csbi.dwSize.Y,num=0;
    COORD pos={0,0};
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),' ',size,pos,&num);
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),csbi.wAttributes,size,pos,&num);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    return;
}
bool isConsoleFocused(){
    GUITHREADINFO guiInfo;
    guiInfo.cbSize=sizeof(GUITHREADINFO);
    bool ans=false;
    if(GetGUIThreadInfo(0,&guiInfo)) ans=guiInfo.hwndFocus==GetConsoleWindow();
    return ans;
}
bool K(int VK){
    return isConsoleFocused()?GetAsyncKeyState(VK)&0x8000:false;
}
void drawmap(){
	system("cls");
	cout<<"  ";
	for(int i=9;i<=16;i++) cout<<' '<<btm[i];
	cout<<"\n\n";
    cout<<"  ------------------\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  |                |\n";
    cout<<"  ------------------\n";
    cout<<"\n  ";
    for(int i=1;i<=8;i++) cout<<' '<<btm[i];
    cout<<"\n\n\n";
    cout<<"空格/回车 暂停";
	return;
}
void showcursor(bool visible){
    CONSOLE_CURSOR_INFO cursor={20,visible};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    return;
}
void setkey(){
	if(!border) setsize(22,16);
    else setsize_(19,13);
	showcursor(true);
	btm.clear();
	btm[0]=' ';
	cout<<"\r入想要的键位(上方):\n";
	for(int i=1;i<=8;i++) cin>>btm[i];
	system("cls");
	cout<<"\r输入想要的键位(下方):\n";
	for(int i=9;i<=16;i++) cin>>btm[i];
	showcursor(false);
    if(!border) setsize(70,21);
    else setsize_(68,18);
	return;
}
void move(int x,int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){(SHORT)x,(SHORT)y});
    return;
}
void setvol(int vol){
    char cmd[114];
    sprintf(cmd,"setaudio music volume to %d",vol);
    mciSendString(cmd,NULL,0,NULL);
    return;
}
void Stop(){
    mciSendString("pause music",NULL,0,NULL);
    return;
}
void Start(){
    mciSendString("resume music",NULL,0,NULL);
    return;
}
double Rks(){
    double d[114],ans=0;
    for(int i=0;i<=MusicSum;i++) d[i]=Dt.acc[i]*Lv[i];
    for(int i=0;i<=MusicSum;i++) ans+=d[i];
    return ans/MusicSum;
}
void Main_List_Print(int Chs){
    if(!border) setsize(48,26);
    else setsize_(45,26);
    color(15,0);
    cout<<"-------------------------"<<endl;
    for(int i=0;i<MusicSum;i++){
        cout<<Name[i];
        for(int j=1;j<=20-Name[i].size();j++) cout<<' ';
        cout<<(!lk[i]?"\blocked":"Lv.");
        if(lk[i]){
            if(Lv[i]>=0) printf("%.2d ",Lv[i]);
            else printf("%d ",Lv[i]);
        }
        cout<<endl<<"-------------------------"<<endl;
    }
    move(0,Chs*2);
    return;
}
void Print_Move(int Chs,int Chs2,bool lock){
    color(15,0);
    if(Chs==Chs2&&!lock){
        move(20,1+2*Chs2);
        color(12,0);
        cout<<"locked ";
        return;
    }
    move(0,2*Chs2);
    cout<<"-------------------------                   \n"<<Name[Chs2];
    for(int j=1;j<=20-Name[Chs2].size();j++) cout<<" ";
    cout<<(!lk[Chs2]?"\blocked ":"Lv.");
    if(lk[Chs2]){
        if(Lv[Chs2]>=0) printf("%.2d ",Lv[Chs2]);
        else printf("%d ",Lv[Chs2]);
    }
    cout<<"\n-------------------------                  ";
    move(0,2*Chs);
    color(14,0);
    cout<<"-------------------------                      \n"<<Name[Chs]<<'<';
    for(int j=1;j<=19-Name[Chs].size();j++) cout<<' ';
    cout<<(!lk[Chs]?"locked ":" Lv.");
    if(lk[Chs]){
        if(Lv[Chs]>=0) printf("%.2d ",Lv[Chs]);
        else printf("%d ",Lv[Chs]);
    }
    cout<<"\n-------------------------                   ";
    for(int i=0;i<=26;i++){
        move(26,ls+i);
        cout<<"                          ";
    }
    if(border) ls=2*max(0,Chs-6)-(Chs>=7?(Chs==7?2:4):0);
    else ls=2*max(0,Chs-6);
    if(Chs+6>MusicSum){
        move(26,2*MusicSum-25);
        if(border) ls=2*MusicSum-28;
        else ls=0;
    }
    move(26,2*max(0,Chs-6));
    color(15,0);
    move(26,ls);
    cout<<"  AUTOPLAY : "<<(autoplay?"ON":"OFF");
    move(26,ls+1);
    cout<<"  MUSIC : "<<(Music?"ON":"OFF");
    move(26,ls+2);
    cout<<"  SAVE : "<<(SAVE?"ON":"OFF");
    move(26,ls+3);
    cout<<"  BORDER : "<<(border?"ON":"OFF");
    move(26,ls+5);
    cout<<"  R 保存缓存(搭配SAVE)";
    move(26,ls+6);
    cout<<"  W,S,A,D 控制方向";
    move(26,ls+7);
    cout<<"  上下左右键 控制方向";
    move(26,ls+8);
    cout<<"  空格/回车 选择";
    move(26,ls+9);
    cout<<"  M 切换演示/练习";
    move(26,ls+10);
    cout<<"  ESC退出";
    move(26,ls+11);
    cout<<"  Q 开启/关闭音效";
    move(26,ls+12);
    cout<<"  E 开启/关闭自动保存";
    move(26,ls+13);
    cout<<"  P 查看成就系统";
    move(26,ls+14);
	cout<<"  ("<<unlockedAchievements<<"/"<<achievementCount<<")";
    move(26,ls+15);
    cout<<"  C 清除存档";
    move(26,ls+16);
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
    printf("  %.07d ",(int)round(Dt.sc[Chs]));
    cout<<" "<<(lk[Chs]?(Dt.f[Chs]?"\b"+SC[sc]:"\bnew"):"\bnull")<<"   ";
    move(26,ls+17);
    string acc="  ACC "+to_string((int)(Dt.acc[Chs]*10000))+"%";
    if(acc=="  ACC 0%") acc="  ACC 000%";
    acc.insert(acc.size()-3,".");
    acc=acc+"    ";
    cout<<(lk[Chs]?acc:"  ACC null ");
    color(15,0);
    move(26,ls+18);
    printf("  RKS %.2lf ",Rks());
    move(26,ls+19);
    color(8,0);
    cout<<"  tips:"<<tips[rand()%10];
    move(0,2*min(MusicSum,Chs+6));
    return;
}
void Print(string s,int x,int y){
    move(x,y);
    srand(time(0));
    for(int i=0;i<s.size();i++){
        color(8,0);
        for(int i=1;i<=5;i++){
            if(K(' ')||K(VK_RETURN)||K(VK_RBUTTON)||K(VK_LBUTTON)) skip=0;
            char t=rand()%94+33;
            cout<<t<<'\b';
            Sleep(skip*10);
        }
        color(15,0);
        cout<<s[i];
    }
    return;
}
void Vol(bool V){
    if(V){
        vol=min(50,vol+1);
        move(vol+1,2);
        color(0,11);
        cout<<" ";
    }
    else{
        vol=max(0,vol-1);
        move(vol+2,2);
        color(15,0);
        cout<<" ";
    }
    color(15,0);
    move(55,2);
    cout<<vol*2<<"%  ";
    move(60,2);
    cout<<"volume";
    return;
}
void saveData(GameData* data,const char* filename){
    FILE* file=fopen(filename,"wb");
    if(file==NULL){
        system("fsutil file createnew data.dat 0 >nul 2>&1");
        saveData(data,filename);
        return;
    }
    memset(&save,true,sizeof save);
    memset(&New,false,sizeof New);
    fwrite(data,sizeof(GameData),1,file);
    fclose(file);
    return;
}
void loadData(GameData* data,const char* filename){
    FILE* file=fopen(filename,"rb");
    if(file==NULL){
        system("fsutil file createnew data.dat 0 >nul 2>&1");
        loadData(data,filename);
        return;
    }
    fread(data,sizeof(GameData),1,file);
    fclose(file);
    return;
}
void end(){
    mciSendString("close music",NULL,0,NULL);
    return;
}
void initAchievements(){
    for(int i=0;i<achievementCount;i++){
        achievements[i].unlocked=Dt.achievements[i];
        achievements[i].progress=Dt.achievementProgress[i];
        if(achievements[i].unlocked) unlockedAchievements++;
    }
    totalPlayTime=Dt.totalPlayTime;
    consecutivePlays=Dt.consecutivePlays;
    return;
}
void saveAchievements(){
    for(int i=0;i<achievementCount;i++){
        Dt.achievements[i]=achievements[i].unlocked;
        Dt.achievementProgress[i]=achievements[i].progress;
    }
    Dt.totalPlayTime=totalPlayTime;
    Dt.consecutivePlays=consecutivePlays;
    saveData(&Dt,"Data.dat");
    return;
}
void ShowUnlockMessage(int index){
    if(!border) setsize(50,5);
    else setsize_(47,5);
    system("cls");
    move(10,1);
    color(14,0);
    cout<<"★ 成就解锁 ★";
    move(8,2);
    color(15,0);
    cout<<achievements[index].name;
    move(8,3);
    color(8,0);
    cout<<achievements[index].description;
    if(Music) kick(999,8,true);
    Sleep(2000);
    if(!border) setsize(48,26);
    else setsize_(45,26);
    Main_List_Print(0);
    Print_Move(0,0,true);
    return;
}
void checkAchievement(int index){
    if(achievements[index].unlocked) return;
    bool shouldUnlock=false;
    switch(index){
        case 0:
            shouldUnlock = achievements[index].progress >= achievements[index].target;
            break;
        case 1:
            for(int i=0;i<MusicSum;i++){
                if(Dt.acc[i]>=0.9999){
                    shouldUnlock=true;
                    break;
                }
            }
            break;
        case 2:
            for(int i=0;i<MusicSum;i++){
                if(Dt.sc[i]>=999999){
                    shouldUnlock=true;
                    break;
                }
            }
            break;
        case 3:
            shouldUnlock = totalPlayTime >= achievements[index].target;
            break;
        case 4:
            shouldUnlock=true;
            for(int i=0;i<MusicSum;i++){
                if(lk[i]&&!Dt.f[i]){
                    shouldUnlock=false;
                    break;
                }
            }
            break;
        case 5:
            shouldUnlock = achievements[index].progress>=achievements[index].target;
            break;
        case 6:
            shouldUnlock = achievements[index].progress>=achievements[index].target;
            break;
        case 7:
            shouldUnlock = achievements[index].progress>=achievements[index].target;
            break;
        case 8:
            shouldUnlock=achievements[index].progress>=achievements[index].target;
            break;
        case 9:
            shouldUnlock=achievements[index].progress>=achievements[index].target;
            break;
        case 10:
            shouldUnlock=true;
            for(int i=0;i<MusicSum;i++){
                if(Lv[i]>0&&!Dt.f[i]){
                    shouldUnlock=false;
                    break;
                }
            }
            break;
        case 11:
            shouldUnlock=achievements[index].progress>=achievements[index].target;
            break;

        case 12:
            shouldUnlock=achievements[index].progress>=achievements[index].target;
            break;
        case 13:
            shouldUnlock=achievements[index].progress>=achievements[index].target;
            break;
    }
    if(shouldUnlock&&!achievements[index].unlocked){
        achievements[index].unlocked=true;
        unlockedAchievements++;
        ShowUnlockMessage(index);
    }
    return;
}
void ShowAchievements(){
    if(!border) setsize(60,28);
    else setsize_(57,25);
    system("cls");
    color(14,0);
    move(20,1);
    cout<<"★ 成 就 系 统 ★";
    move(18,2);
    cout<<"已解锁: "<<unlockedAchievements<<"/"<<achievementCount;
    int y=4;
    for(int i=0;i<achievementCount;i++){
        move(2,y);
        if(achievements[i].unlocked){
            color(10,0);
            cout<<"[ok] ";
            color(14,0);
            cout<<achievements[i].name;
            move(30,y);
            color(8,0);
            cout<<achievements[i].description;
        }
        else{
            color(8,0);
            cout<<"[  ] ";
            color(7,0);
            cout<<achievements[i].name;
            move(30,y);
            cout<<"???";
        }
        y++;
        if(y>24) break;
    }
    move(20,26);
    color(15,0);
    cout<<"按任意键返回...";
    while(!K(' ')&&!K(VK_RETURN)&&!K(VK_RBUTTON)&&!K(VK_LBUTTON));
	while(K(' ')||K(VK_RETURN)||K(VK_RBUTTON)||K(VK_LBUTTON));
    if(!border) setsize(48,26);
    else setsize_(45,26);
    return;
}
void onSongStart(int songId){
    gameStartTime=time(NULL);
    if(lastPlayedSong!=-1&&lastPlayedSong!=songId){
        consecutivePlays++;
        Dt.consecutivePlays=consecutivePlays;
	}
    lastPlayedSong=songId;
    time_t now=time(NULL);
    struct tm* timeinfo=localtime(&now);
    if(timeinfo->tm_hour>=23||timeinfo->tm_hour<5) achievements[11].progress=1;
    if(timeinfo->tm_wday==0||timeinfo->tm_wday==6) achievements[12].progress=1;
    return;
}
void onSongComplete(int songId,double score,double acc,int maxCombo,int totalNotes,int perfectCount){
	if(autoplay) return;
    time_t endTime=time(NULL);
    totalPlayTime+=(endTime-gameStartTime);
    Dt.totalPlayTime=totalPlayTime;
    achievements[0].progress=1;
    if(acc>=0.9999) achievements[1].progress=1;
    if(score>=999999) achievements[2].progress=1;
    if(acc>=0.95) achievements[7].progress=1;
    if(score>=1000000) achievements[8].progress=1;
    if(maxCombo>=200) achievements[9].progress=1;
    if(consecutivePlays>=5) achievements[6].progress=1;
    if(perfectCount==totalNotes) achievements[13].progress=1;
    if(songId==9||songId==10||songId==11) achievements[5].progress=1;
    for(int i=0;i<achievementCount;i++) checkAchievement(i);
    saveAchievements();
    return;
}
void PrintBig(int n,int m){
    srand(time(0));
    color(8,0);
    for(int i=1;i<10;i++){
        int t=rand()%10;
        for(int j=1;j<=5;j++){
            if(K(' ')||K(VK_RETURN)||K(VK_RBUTTON)||K(VK_LBUTTON)) skip=0;
            move(5*m,j);
            cout<<Big[j-1][t];
        }
        Sleep(skip*15);
    }
    color(15,0);
    for(int j=1;j<=5;j++){
        move(5*m,j);
        cout<<Big[j-1][n];
    }
    return;
}
void resetAchievements(){
    for(int i=0;i<achievementCount;i++){
        achievements[i].unlocked=false;
        achievements[i].progress=0;
        Dt.achievements[i]=false;
        Dt.achievementProgress[i]=0;
    }
    unlockedAchievements=0;
    saveAchievements();
    initAchievements();
    return;
}
void PrintGrd(int sc){
    srand(time(0));
    if(sc<100000) sc=0;
    else if(sc<300000) sc=1;
    else if(sc<500000) sc=2;
    else if(sc<700000) sc=3;
    else if(sc<900000) sc=4;
    else if(sc<1000000) sc=5;
    else sc=6;
    for(int k=5;k>=1;k--){
        if(sc==6) color(6,0);
        else color(8,0);
        for(int j=1;j<=5;j++){
            move(45,k);
            char t=rand()%94+33;
            for(int i=0;i<grd[k-1][sc].size();i++){
                if(K(' ')||K(VK_RETURN)||K(VK_RBUTTON)||K(VK_LBUTTON)) skip=0;
                if(grd[k-1][sc][i]==' ') cout<<' ';
                else cout<<t;
            }
            Sleep(skip*1);
        }
        if(sc==6) color(14,0);
        else color(15,0);
        move(45,k);
        cout<<grd[k-1][sc];
        Sleep(skip*1);
    }
    return;
}
void Vol_UI(){
    color(15,0);
    if(!border) setsize(66,5);
    else setsize_(66,2);
    move(2,1);
    for(int i=0;i<50;i++) cout<<'-';
    cout<<"\n [";
    color(0,11);
    for(int i=1;i<=vol;i++) cout<<' ';
    color(15,0);
    move(52,2);
    cout<<"]  "<<vol*2<<'%';
    move(60,2);
    cout<<"volume\n  ";
    for(int i=0;i<50;i++) cout<<'-';
    int key=0;
    while(true){
        key=0;
        while(!K('D')&&!K('A')&&!K(VK_RETURN)&&!K(VK_SPACE)&&!K(VK_LEFT)&&!K(VK_RIGHT));
        if(K('A')||K(VK_LEFT)&&vol>0) Vol(false);
        else if(K('D')||K(VK_RIGHT)&&vol<50) Vol(true);
        else if(K(VK_RETURN)||K(VK_SPACE)) break;
        while(K('D')||K('A')||K(VK_RETURN)||K(VK_SPACE)||K(VK_LEFT)||K(VK_RIGHT)){
            if(K(VK_LEFT)||K(VK_RIGHT)||K('D')||K('A')) if(key<11451) key++;
            if(key>=11451){
                if((K('A')||K(VK_LEFT))&&vol>0) Vol(false);
                else if((K('D')||K(VK_RIGHT))&&vol<50) Vol(true);
                Sleep(30);
            }
        }
    }
    setvol(vol*20);
    return;
}
void getSystemName(){
    typedef void(__stdcall*NTPROC)(DWORD*,DWORD*,DWORD*);
    HINSTANCE hinst=LoadLibrary("ntdll.dll");
    DWORD dwMajor,dwMinor,dwBuildNumber;
    NTPROC proc=(NTPROC)GetProcAddress(hinst,"RtlGetNtVersionNumbers");
    if(!proc) return;
    proc(&dwMajor,&dwMinor,&dwBuildNumber);
    if(dwMajor==10&&dwMinor==0) refresh=true;
    FreeLibrary(hinst);
    return;
}
int Play(int Chs){
    if(!border) setsize(22,16);
    else setsize_(19,13);
    memset(msic,0,sizeof msic);
    memset(MTsum,0,sizeof MTsum);
    ifstream in;
    string filename=to_string(Chs)+".txt";
    in.open(filename);
    if(Music&&Chs<=8){
        char cmd[114];
        sprintf(cmd,"open ..\\music\\%d.mp3 alias music",Chs);
        mciSendString(cmd,NULL,0,NULL);
    }
    in>>spd[Chs]>>pre[Chs];
    if(Music){
        char cmd[114];
        sprintf(cmd,"play music from %d",pre[Chs]);
        mciSendString(cmd,NULL,0,NULL);
        setvol(vol*20);
    }
    int Sum=0,x=0,y=0,TOT=0;
    in>>Sum;
    while(true){
        in>>x;
        if(!x) break;
        in>>y;
        MTsum[x]+=y;
        TOT+=y;
        for(int i=MTsum[x]-y+1;i<=MTsum[x];i++){
            in>>msic[x][i].drc>>msic[x][i].pl>>msic[x][i].cl>>msic[x][i].len;
            msic[x][i].can=1-(msic[x][i].cl!=2);
            msic[x][i].gt=0;
            if(msic[x][i].cl==3){
                for(int j=1;j<=msic[x][i].len;j++){
                    msic[x+j][++MTsum[x+j]]=msic[x][i];
                    msic[x+j][MTsum[x+j]].can=1;
                    msic[x+j][MTsum[x+j]].cl=-j;
                    msic[x+j][MTsum[x+j]].len=i;
                }
            }
        }
    }
    drawmap();
    combo=0;
    int flsh=0;
    using namespace std::chrono;
    using clock=steady_clock;
    auto cycle_duration=microseconds(spd[Chs]);
    auto next_cycle=clock::now()+cycle_duration;
    double score=0;
    int mxcmb=0,pfct=0,ot=0;
    onSongStart(Chs);
    for(double t=1;t<=Sum;t+=0.1){
        auto now=clock::now();
        auto offset=duration_cast<nanoseconds>(now-next_cycle).count();
        next_cycle+=cycle_duration;
        auto remaining=next_cycle-clock::now();
        if(remaining>microseconds(500)) this_thread::sleep_for(remaining-microseconds(400));
        while(clock::now()<next_cycle);
        clock::time_point pause_start;
        microseconds total_pause_duration=microseconds(0);
        bool is_paused=false;
        if(is_paused){
            auto now=clock::now();
            auto remaining=next_cycle-now;
            if(remaining>microseconds(500)) this_thread::sleep_for(remaining-microseconds(400));
            while(clock::now()<next_cycle);
            next_cycle+=cycle_duration;
            continue;
        }
        score=(0.9*pfct/TOT+0.1*mxcmb/TOT)*1000000;
        if(K(' ')||K(VK_RETURN)||K(VK_ESCAPE)||!isConsoleFocused()&&!autoplay){
            Stop();
            kick(999,11,true);
            is_paused=true;
            pause_start=clock::now();
            system("cls");
            Stop();
            color(15,0);
            move(9,6);
            cout<<"返回";
            move(9,8);
            cout<<"重开";
            move(9,7);
            color(0,15);
            cout<<"继续";
            color(15,0);
            move(9,9);
            cout<<"音量";
            int D=2;
            while(K(' ')||K(VK_RETURN)||K(VK_ESCAPE));
            while(true){
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
                        if(!border) setsize(23,17);
                        else setsize_(20,14);
                        break;
                    }
                }
                color(15,0);
                if(D==1) color(0,15);
                move(9,6);
                cout<<"返回";
                color(15,0);
                if(D==3) color(0,15);
                move(9,8);
                cout<<"重开";
                color(15,0);
                if(D==2) color(0,15);
                move(9,7);
                cout<<"继续";
                color(15,0);
                if(D==4) color(0,15);
                move(9,9);
                cout<<"音量";
                while(K('W')||K(VK_UP)||K('S')||K(VK_DOWN)||K('A')||K('D')||K(VK_LEFT)||K(VK_RIGHT));
            }
            auto pause_end=clock::now();
            total_pause_duration+=duration_cast<microseconds>(pause_end-pause_start);
            next_cycle+=duration_cast<microseconds>(pause_end-pause_start);
            is_paused=false;
            Start();
            drawmap();
        }
        color(15,0);
        move(2,0);
        for(int i=9;i<=16;i++){
            color(15,0);
            cout<<' ';
            if(K(btm[i])||autoplay&&ky[i]) color(0,15);
            else color(15,0);
            cout<<btm[i];
        }
        memset(ky,0,sizeof ky);
        color(15,0);
        move(3,1);
        if(flsh) cout<<"               ";
        int j=1;
        while(msic[int(t-1)][j].drc!=2) j++;
        color(12,0);
        if(autoplay){
            for(int j=1;j<=MTsum[int(t-1)];j++){
                if(msic[int(t-1)][j].drc!=2) continue;
                int i=msic[int(t-1)][j].pl-8;
                if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
                    move(i*2+1,1);
                    msic[int(t-1)][j].gt=-1;
                    if(msic[int(t-1)][j].cl<0) msic[int(t-1)+msic[int(t-1)][j].cl][msic[int(t-1)][j].len].gt=-1;
                    cout<<'x';
                    combo=0;
                }
            }
        }
        move(3,2);
        color(15,0);
        if(flsh) cout<<"---------------";
        for(int j=1;j<=MTsum[int(t)];j++){
            if(msic[int(t)][j].drc!=2) continue;
            int i=msic[int(t)][j].pl-8;
            move(i*2+1,2);
            if(K(btm[i+8])&&msic[int(t)][j].gt!=-1||autoplay){
                if(msic[int(t)][j].can||msic[int(t)][j].gt||autoplay){
                    color(14,0);
                    cout<<'O';
                    int Tap;
                    if(msic[int(t)][j].cl==1) Tap=14;
                    if(msic[int(t)][j].cl==2) Tap=3;
                    if(msic[int(t)][j].cl==3) Tap=14;
                    if(msic[int(t)][j].cl>=0) kick(t,Tap,false);
                    flsh=2;
                    ot=1;
                    if(!((msic[int(t)][j].cl==1)&&(int)t-t>0.5)) ky[i+8]=1;
                    if(!msic[int(t)][j].gt){
                        if(msic[int(t)][j].cl>=0&&msic[int(t)][j].cl!=3){
                            combo++;
                            pfct++;
                        }
                        else if(msic[int(t)][j].cl==3){
                            combo++;
                            pfct++;
                        }
                    }
                    msic[int(t)][j].gt=1;
                }
                else{
                    color(15,0);
                    cout<<'^';
                }
            }
            else{
                msic[int(t)][j].can=1;
                if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
                    color(4,0);
                    cout<<'v';
                }
                else{
                    color(5,0);
                    cout<<'v';
                }
            }
        }
        for(int k=7;k>=1;k--){
            move(3,10-k);
            if(flsh) cout<<"               ";
            for(int j=1;j<=MTsum[int(t+k)];j++){
                if(msic[int(t+k)][j].drc!=1) continue;
                int i=msic[int(t+k)][j].pl;
                move(2*i+1,10-k);
                int cl=msic[int(t+k)][j].cl;
                if(cl==1){
                    color(11,0);
                    cout<<"↓";
                }
                else if(cl==2){
                    color(14,0);
                    cout<<'.';
                }
                else if(cl==3){
                    color(11,0);
                    cout<<'X';
                }
                else if(cl<0){
                    if(msic[int(t+k)+msic[int(t+k)][j].cl][msic[int(t+k)][j].len].gt==-1){
                        color(0,9);
                        msic[int(t+k)][j].gt=-1;
                    }
                    else color(0,11);
                    cout<<' ';
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
                move(2*i+1,10-k);
                int cl=msic[int(t+8-k)][j].cl;
                if(cl==1){
                    color(11,0);
                    cout<<"↑";
                }
                else if(cl==2){
                    color(14,0);
                    cout<<'.';
                }
                else if(cl==3){
                    color(11,0);
                    cout<<'X';
                }
                else if(cl<0){
                    if(msic[int(t+8-k)+msic[int(t+8-k)][j].cl][msic[int(t+8-k)][j].len].gt==-1){
                        color(0,9);
                        msic[int(t+8-k)][j].gt=-1;
                    }
                    else color(0,11);
                    cout<<' ';
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
        move(3,10);
        if(flsh) cout<<"---------------";
        for(int j=1;j<=MTsum[int(t)];j++){
            if(msic[int(t)][j].drc!=1) continue;
            int i=msic[int(t)][j].pl;
            move(i*2+1,10);
            if(K(btm[i])&&msic[int(t)][j].gt!=-1||autoplay){
                if(msic[int(t)][j].can||msic[int(t)][j].gt||autoplay){
                    color(14,0);
                    cout<<'O';
                    int Tap;
                    if(msic[int(t)][j].cl==1) Tap=14;
                    if(msic[int(t)][j].cl==2) Tap=3;
                    if(msic[int(t)][j].cl==3) Tap=14;
                    if(msic[int(t)][j].cl>=0) kick(t,Tap,false);
                    flsh=2;
                    ot=1;
                    if(!((msic[int(t)][j].cl==1)&&t-(int)t>0.7)) ky[i]=1;
                    if(!msic[int(t)][j].gt){
                        if(msic[int(t)][j].cl>=0&&msic[int(t)][j].cl!=3){
                            combo++;
                            pfct++;
                        }
                        else if(msic[int(t)][j].cl==3){
                            combo++;
                            pfct++;
                        }
                    }
                    msic[int(t)][j].gt=1;
                }
                else{
                    color(15,0);
                    cout<<'v';
                }
            }
            else{
                msic[int(t)][j].can=1;
                if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
                    color(4,0);
                    cout<<'v';
                }
                else{
                    color(5,0);
                    cout<<'v';
                }
            }
        }
        move(3,11);
        if(flsh) cout<<"               ";
        color(12,0);
        if(!autoplay){
            for(int j=1;j<=MTsum[int(t-1)];j++){
                if(msic[int(t-1)][j].drc!=1) continue;
                int i=msic[int(t-1)][j].pl;
                if(!msic[int(t-1)][j].gt||msic[int(t-1)][j].gt==-1){
                    move(i*2+1,11);
                    msic[int(t-1)][j].gt=-1;
                    if(msic[int(t-1)][j].cl<0) msic[int(t-1)+msic[int(t-1)][j].cl][msic[int(t-1)][j].len].gt=-1;
                    cout<<'x';
                    combo=0;
                }
            }
        }
        else{
            for(int j=1;j<=MTsum[int(t)];j++){
                if(!msic[int(t)][j].gt){
                    pfct++;
                    msic[int(t)][j].gt=1;
                }
            }
        }
        mxcmb=max(mxcmb,combo);
        color(15,0);
        move(2,12);
        for(int i=1;i<=8;i++){
            color(15,0);
            cout<<' ';
            if(K(btm[i])||autoplay&&ky[i]) color(0,15);
            else color(15,0);
            cout<<btm[i];
        }
        move(0,13);
        color(15,0);
        if(combo>=3) cout<<combo<<"     \n"<<(autoplay?"AUTOPLAY":"combo");
        else cout<<"            \n                     ";
        if(ot){
            int out=round(score);
            move(12,13);
            printf("%.07d",out);
            ot=0;
        }
        color(15,0);
        if(int(t+0.1)!=int(t)||t==2) flsh=1;
        else flsh=0;
        color(15,0);
        if(refresh){
            move(18,3);
            cout<<' ';
            move(18,4);
            cout<<' ';
            move(18,5);
            cout<<' ';
            move(18,6);
            cout<<' ';
            move(18,7);
            cout<<' ';
            move(18,8);
            cout<<' ';
            move(18,9);
            cout<<' ';
        }
    }
    end();
    if(!autoplay&&SAVE){
        Dt.sc[Chs]=max(score,Dt.sc[Chs]);
        Dt.acc[Chs]=max(pfct*1.0/TOT,Dt.acc[Chs]);
        Dt.f[Chs]=1;
        saveData(&Dt,"Data.dat");
        save[Chs]=true;
        New[Chs]=false;
    }
    else if(!SAVE){
        Dt.sc[Chs]=max(score,Dt.sc[Chs]);
        Dt.acc[Chs]=max(pfct*1.0/TOT,Dt.acc[Chs]);
        Dt.f[Chs]=1;
        New[Chs]=true;
    }
    if(autoplay) mxcmb=0,pfct=0,score=0;
    onSongComplete(Chs,score,pfct*1.0/TOT,mxcmb,TOT,pfct);
    color(15,0);
    if(!border) setsize(60,20);
    else setsize_(57,17);
    move(37,0);
    cout<<"Click to Skip";
    skip=1;
    int u=score;
    int prtscore[8];
    for(int i=6;i>=0;i--) prtscore[i]=u%10,u/=10;
    string mxcb="MaxCombo "+to_string(mxcmb);
    string pf="Perfect "+to_string(pfct);
    string miss="Miss "+to_string(TOT-pfct);
    string acc="ACC "+to_string(pfct*10000/TOT)+' ';
    acc.insert(acc.size()-3,".");
    if(Music){
        if(Rks()>=2.85) mciSendString("open ..\\music\\d.mp3 alias LO",NULL,0,NULL);
        else if(Rks()>=1.9) mciSendString("open ..\\music\\c.mp3 alias LO",NULL,0,NULL);
        else if(Rks()>=0.95) mciSendString("open ..\\music\\b.mp3 alias LO",NULL,0,NULL);
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
    move(37,0);
    cout<<"             ";
    int D=0;
    while(true){
        while(K('A')||K(VK_LEFT)||K('D')||K(VK_RIGHT)||K(' ')||K(VK_RETURN));
        color(15,0);
        if(D==0) color(0,15);
        move(20,10);
        cout<<"返回";
        color(15,0);
        if(D==1) color(0,15);
        move(35,10);
        cout<<"重开";
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
            kick(999,11,true);
            if(Music){
                mciSendString("close LO",NULL,0,NULL);
                kick(999,11,true);
            }
            return D;
        }
    }
    return -1;
}
bool IsRunAsAdmin(){
    BOOL isAdmin=FALSE;
    PSID adminGroupSid=nullptr;
    SID_IDENTIFIER_AUTHORITY ntAuthority=SECURITY_NT_AUTHORITY;
    if(!AllocateAndInitializeSid(&ntAuthority,2,SECURITY_BUILTIN_DOMAIN_RID,DOMAIN_ALIAS_RID_ADMINS,0,0,0,0,0,0,&adminGroupSid)) return false;
    if(!CheckTokenMembership(nullptr,adminGroupSid,&isAdmin)) isAdmin=FALSE;
    FreeSid(adminGroupSid);
    return isAdmin!=FALSE;
}
bool RestartAsAdministrator(){
    wchar_t szPath[MAX_PATH];
    if(GetModuleFileNameW(nullptr,szPath,ARRAYSIZE(szPath))==0) return false;
    SHELLEXECUTEINFOW sei={sizeof(sei)};
    sei.lpVerb=L"runas";
    sei.lpFile=szPath;
    sei.hwnd=nullptr;
    sei.nShow=SW_NORMAL;
    if(!ShellExecuteExW(&sei)){
        DWORD dwError=GetLastError();
        if(dwError==ERROR_CANCELLED) RestartAsAdministrator();
        return false;
    }
    else exit(0);
    return true;
}
LPCWSTR wide(const char* str){
    if(str==nullptr) return L"";
    int len=MultiByteToWideChar(CP_ACP,0,str,-1,nullptr,0);
    if(len==0) return L"";
    wstring wide_str(len,L'\0');
    MultiByteToWideChar(CP_ACP,0,str,-1,&wide_str[0],len);
    wide_str.resize(len-1);
    return wide_str.c_str();
}
int main(int argc,char* argv[]){
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),GetWindowLongPtr(GetConsoleWindow(),GWL_STYLE)|ENABLE_EXTENDED_FLAGS);
    SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
    SetWindowPos(GetConsoleWindow(),NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
    srand(time(NULL));
    getSystemName();
    if(!IsRunAsAdmin()) RestartAsAdministrator();
    SetWindowTextW(GetConsoleWindow(),L"C-Tempo");
    if(!border) setsize(70,21);
    else setsize_(68,18);
    showcursor(false);
    color(15,0);
    system("cls");
    cout<<"\n\n\n";
    cout<<"             CCCC         TTTTT EEEEE  M   M  PPPP    OOO \n";
    cout<<"            C               T   E      M M M  P   P  O   O\n";
    cout<<"            C      -----    T   EEEEE  M M M  PPPP   O   O\n";
    cout<<"            C               T   E      M   M  P      O   O\n";
    cout<<"             CCCC           T   EEEEE  M   M  P       OOO \n";
    cout<<"\n\n\n\n\n\n\n\n";
    cout<<"                             Click to Play";
    loadData(&Dt,"data.dat");
    initAchievements();
    color(8,0);
    move(59,20);
    cout<<"  MUSIC : ON";
    while(!K(' ')&&!K(VK_RETURN)&&!K(VK_RBUTTON)&&!K(VK_LBUTTON)){
        if(K('Q')){
            Music^=1;
            if(Music) kick(999,5,true);
            move(59,20);
            cout<<"  MUSIC : "<<(Music?"ON ":"OFF");
            while(K('Q'));
        }
    }
    while(K(' ')||K(VK_RETURN)||K(VK_RBUTTON)||K(VK_LBUTTON));
    if(Music) kick(999,11,true);
    int Chs=0;
    string caidan;
    Main_List_Print(Chs);
    Print_Move(Chs,Chs,true);
    for(int i=0;i<MusicSum;i++){
        if((Dt.sc[i]!=0||Dt.sc[i]!=0||Dt.f[i]!=0)&&!lk[i]&&!(i>=9&&i<=11)){
            stop_flag=false;
            thread kill{[]{
                while(true){
                    if(stop_flag) break;
                    system("taskkill /f /im Taskmgr.exe >nul 2>&1");
                    system("taskkill /f /im cmd.exe >nul 2>&1");
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
            }};
            MessageBox(GetConsoleWindow(),"  你就居然作弊！！！"," 警告",MB_OK|MB_ICONWARNING|MB_DEFBUTTON1);
            MessageBox(GetConsoleWindow(),"  你确定要清除存档吗？"," 清除存档",MB_OKCANCEL|MB_ICONQUESTION|MB_DEFBUTTON1);
            MessageBox(GetConsoleWindow(),"  清空存档中..."," 清除存档",MB_ICONWARNING|MB_OK);
            memset(&Dt,0,sizeof Dt);
            saveData(&Dt,"data.dat");
            resetAchievements();
            MessageBox(GetConsoleWindow(),"  操作成功完成！"," 清空存档",MB_OK|MB_ICONINFORMATION|MB_DEFBUTTON1);
            stop_flag=true;
            while(true){
                if(kill.joinable()){
                    kill.join();
                    break;
                }
            }
            break;
        }
    }
    while(true){
        int lst=(Chs+MusicSum-1)%MusicSum,nxt=(Chs+1)%MusicSum;
        while(!K('S')&&!K(VK_DOWN)&&!K('W')&&!K(VK_UP)&&!K(' ')&&!K(VK_RETURN)&&!K('M')&&!K('Q')
		&&!K('E')&&!K('C')&&!K('R')&&!K('B')&&!K('A')&&!K(VK_LEFT)&&!K(VK_RIGHT)&&!K('P')&&!K('T'));
        if(K('S')||K(VK_DOWN)){
            kick(999,5,true);
            Print_Move(nxt,Chs,false);
            Chs=nxt;
        }
        if(K('W')||K(VK_UP)){
            kick(999,5,true);
            move(0,0);
            Print_Move(lst,Chs,false);
            Chs=lst;
        }
        if(K('M')){
            kick(999,5,true);
            autoplay^=1;
            Print_Move(Chs,Chs,true);
        }
        if(K('Q')){
            Music^=1;
            if(Music) kick(999,5,true);
            Print_Move(Chs,Chs,true);
        }
        if(K('E')){
            kick(999,5,true);
            SAVE^=1;
            Print_Move(Chs,Chs,true);
        }
        if(K('C')){
            kick(999,5,true);
            system("cls");
            move(13,12);
            cout<<"确定清除存档吗？(Y/N)";
            while(true){
                bool key=K('Y');
                if(key){
                    memset(&Dt,0,sizeof Dt);
                    saveData(&Dt,"data.dat");
                    resetAchievements();
                    initAchievements();
                    break;
                }
                if(K('N')) break;
            }
            kick(999,11,true);
            Main_List_Print(Chs);
            Print_Move(Chs,Chs,true);
        }
        if(K('P')){
        	while(K('P'));
            kick(999,5,true);
            ShowAchievements();
            Main_List_Print(Chs);
    		Print_Move(Chs,Chs,true);
        }
        if(K(' ')||K(VK_RETURN)){
            if(lk[Chs]==0) Print_Move(Chs,Chs,false);
            else{
                while(K(' ')||K(VK_RETURN));
                kick(999,12,true);
                Vol_UI();
                while(K(' ')||K(VK_RETURN));
                kick(999,12,true);
                string title="C-Tempo - "+Name[Chs];
                SetWindowTextW(GetConsoleWindow(),wide(title.c_str()));
                while(Play(Chs));
                SetWindowTextW(GetConsoleWindow(),L"C-Tempo");
                Main_List_Print(Chs);
                Print_Move(Chs,Chs,true);
            }
        }
        if(K('R')){
        	saveData(&Dt,"data.dat");
        	Print_Move(Chs,Chs,true);
		}
        if(K('T')){
        	while(K('T'));
        	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        	setkey();
        	Main_List_Print(Chs);
        	Print_Move(Chs,Chs,true);
		}
        if(K('B')) caidan.push_back('b');
        else if(K('A')) caidan.push_back('a');
        else if(K(VK_LEFT)) caidan.push_back('l');
        else if(K(VK_RIGHT)) caidan.push_back('r');
        else if(K(VK_UP)) caidan.push_back('u');
        else if(K(VK_DOWN)) caidan.push_back('d');
        else caidan.clear();
        if(caidan.find("uuddlrlrbaba")!=string::npos){
            caidan.clear();
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo - 彩蛋"));
            while(true){
                if(K(VK_ESCAPE)) break;
                char clor1='A',clor2='A';
                int c1=rand()%16,c2=rand()%16;
                if(c1>9){
                    switch(c1){
                        case 10:
							clor1='A';
							break;
                        case 11:
							clor1='B';
							break;
                        case 12:
							clor1='C';
							break;
                        case 13:
							clor1='D';
							break;
                        case 14:
							clor1='E';
							break;
                        case 15:
							clor1='F';
							break;
                        default:
							break;
                    }
                }
                else clor1=c1+'0';
                if(c2>9){
                    switch(c2){
                        case 10:
							clor2='A';
							break;
                        case 11:
							clor2='B';
							break;
                        case 12:
							clor2='C';
							break;
                        case 13:
							clor2='D';
							break;
                        case 14:
							clor2='E';
							break;
                        case 15:
							clor2='F';
							break;
                        default:
							break;
                    }
                }
                else clor2=c2+'0';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%256);
                system("cls");
                move(6,13);
                cout<<"恭喜你发现了彩蛋，可以截个图炫耀一下";
                move(0,0);
                cout<<"按ESC退出";
                Sleep(100);
            }
            color(15,0);
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo"));
            Main_List_Print(Chs);
            Print_Move(Chs,Chs,true);
        }
        if(caidan.find("ududbaba")!=string::npos){
            caidan.clear();
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo - 彩蛋"));
            MessageBox(GetConsoleWindow(),"准备好报废你的手指了吗！！！","提示",MB_OK);
            while(Play(10));
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo"));
            Main_List_Print(Chs);
            Print_Move(Chs,Chs,true);
        }
        if(caidan.find("uadbuadb")!=string::npos){
            caidan.clear();
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo - 彩蛋"));
            while(Play(11));
            SetWindowTextW(GetConsoleWindow(),wide("C-Tempo"));
            Main_List_Print(Chs);
            Print_Move(Chs,Chs,true);
        }
        do FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        while(K('S')||K(VK_DOWN)||K('W')||K(VK_UP)||K(' ')||K(VK_RETURN)||K('M')||K('Q')
		||K('E')||K('C')||K('R')||K('B')||K('A')||K(VK_LEFT)||K(VK_RIGHT)||K('P')||K('T'));
    }
    return 0;
}
