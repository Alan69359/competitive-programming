#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=150001,M=N*2,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int he[N],no[M],we[M],ne[M],idx;
int di[N];
bool st[N];

void add(int a,int b,int c){
	no[idx]=b;
	we[idx]=c;
	ne[idx]=he[a];
	he[a]=idx++;
}

int spfa(){
	memset(di,0x3f,sizeof di);
	di[1]=0;
	queue<int>q;
	q.push(1);
	st[1]=true;
	while(!q.empty()){
		int t=q.front();
		q.pop();
		st[t]=false;
		for(int i=he[t];~i;i=ne[i]){
			int j=no[i];
			if(di[j]>di[t]+we[i]){
				di[j]=di[t]+we[i];
				if(!st[j]){
					q.push(j);
					st[j]=true;
				}
			}
		}
	}
	return di[n];
}

int main(){
	scanf("%d%d",&n,&m);
	memset(he,-1,sizeof he);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	int res=spfa();
	if(res==INF)printf("impossible");
	else printf("%d",res);
	return 0;
}
