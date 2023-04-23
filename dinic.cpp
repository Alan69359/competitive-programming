#include<bits/stdc++.h>

using namespace std;

const int N=10010,M=200010,INF=1e8;

int n,m,s,t;
int he[N],no[M],f[M],ne[M],idx;
int q[N],lev[N],notfull[N];

void add(int a, int b, int c){
    no[idx]=b,f[idx]=c,ne[idx]=he[a],he[a]=idx++;
    no[idx]=a,f[idx]=0,ne[idx]=he[b],he[b]=idx++;
}

bool bfs(){
    int qh=0,qt=0;
    memset(lev,-1,sizeof lev);
    q[0]=s,lev[s]=0,notfull[s]=he[s];
	while(qh<=qt){
        int top=q[qh++];
        for(int i=he[top];~i;i=ne[i]){
			int j=no[i];
			if(lev[j]==-1&&f[i]){
				lev[j]=lev[top]+1;
				notfull[j]=he[j];
				if(j==t)return true;
				q[++qt]=j;
			}
		}
	}
	return false;
}

int dfs(int u,int limit){
    if(u==t)return limit;
    int flow=0;
	for(int i=notfull[u];~i&&flow<limit;i=ne[i]){
        notfull[u]=i;
        int j=no[i];
        if(lev[j]==lev[u]+1&&f[i]){
			int top=dfs(j,min(f[i],limit-flow));
		    if(!top)lev[j]=-1;
			f[i]-= top,f[i^1]+=top,flow+=top;															        
		}								    
	}
	return flow;			
}

int dinic(){
    int res=0,flow;
	while(bfs()){
		while(flow=dfs(s,INF)){
            res+=flow;
		}
	}
	return res;		
}

int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(he,-1,sizeof he);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);								    
	}
	printf("%d",dinic());
	return 0;				
}
