#include<bits/stdc++.h>

using namespace std;

const int N=501,M=10001,INF=0x3f3f3f3f;

int n,m,k;
int di[N],backup[N];
int res=0x3f;

struct Edge{
	int a,b,w;
}ed[M];

bool bellmanford(){
	memset(di,0x3f,sizeof di);
	di[1]=0;
	for(int i=0;i<k;i++){
		memcpy(backup,di,sizeof di);
		for(int j=0;j<m;j++){
			int a=ed[j].a,b=ed[j].b,w=ed[j].w;
			di[b]=min(di[b],backup[a]+w);
		}
	}
	if(di[n]>0x3f/2)return false;
	else {
		res=di[n];
		return true;
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		ed[i]={a,b,w};
	}
	if(!bellmanford()){
		printf("impossible");
	}
	else printf("%d",res);
	return 0;
}
