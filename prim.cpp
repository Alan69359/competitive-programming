#include<bits/stdc++.h>

using namespace std;

const int N=501,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int d[N][N];
int di[N];
bool st[N];

int prim(){
	memset(di,0x3f,sizeof di);
	int res=0;
	di[1]=0;
	for(int i=0;i<n;i++){
		int t=-1;
		for(int j=1;j<=n;j++){
			if(!st[j]&&(t==-1||di[t]>di[j])){
				t=j;
			}
		}
		res+=di[t];
		for(int j=1;j<=n;j++){
			di[j]=min(di[j],d[t][j]);
		}
		st[t]=true;
	}
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&d[i][j]);
		}
	}
	int res=prim();
	printf("%d\n",res);
	return 0;
}
