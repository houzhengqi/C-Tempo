#include <iostream>
using namespace std;
int main(){
	int n,m;
	freopen("print.txt","w",stdout);
	while(1){
		cin>>n>>m;
		if(n==0) return 0;
		cout<<n<<" "<<m<<endl;
		for(int i=1;i<=m;i++){
			int a,b,c,d;
			cin>>a>>b>>c>>d;
			cout<<a<<" "<<b+8<<" "<<c<<" "<<d<<endl;
		}
	}
	return 0; 
}
