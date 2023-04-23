#include<bits/stdc++.h>

using namespace std;

const int N=100001,M=N*2,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int pa[N];

struct Edge{
	int a,b,c;
	bool operator < (const Edge &ed){
		return c<ed.c;
	}
}ed[M];

int find(int x){
	if(pa[x]==x)return x;
	else return pa[x]=find(pa[x]);
}

int kruskal(){
	sort(ed,ed+m);
	for(int i=1;i<=n;i++){
		pa[i]=i;
	}
	int ans=0;
	for(int i=0;i<m;i++){
		int a=ed[i].a,b=ed[i].b,c=ed[i].c;
		a=find(a),b=find(b);
		if(a!=b){
			pa[a]=b;
			ans+=c;
			//printf("%d edge: %c to %c of weight %d\n",i,ed[i].a+'a',ed[i].b+'a',c);	
		}
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		ed[i]={a,b,c};
	}
	int res=kruskal();
	printf("%d\n",res);
	return 0;
}
