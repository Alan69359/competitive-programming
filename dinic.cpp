#include<bits/stdc++.h>

using namespace std;

const int N=10010,M=200010,INF=1e8;

int n,m,s,t;
int he[N],no[M],fl[M],ne[M],idx;
int q[N],lev[N],notfull[N];

void add(int a, int b, int c){
    no[idx]=b,fl[idx]=c,ne[idx]=he[a],he[a]=idx++;
    no[idx]=a,fl[idx]=0,ne[idx]=he[b],he[b]=idx++;
}

bool bfs(){
    int qh=0,qt=0;
    memset(lev,-1,sizeof lev);
    q[0]=s,lev[s]=0,notfull[s]=he[s];
	while(qh<=qt){
        int top=q[qh++];
        for(int i=he[top];~i;i=ne[i]){
			int j=no[i];
			if(lev[j]==-1&&fl[i]){
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
        if(lev[j]==lev[u]+1&&fl[i]){
			int top=dfs(j,min(fl[i],limit-flow));
		    if(!top)lev[j]=-1;
			fl[i]-= top,fl[i^1]+=top,flow+=top;															        
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

void ini(){
    memset(he,-1,sizeof he);
}

int getid(int i,int isleft){
    return 2*i-isleft;
}

void backtrack(){
    for(int i=0;i<idx;i+=2){
        fl[i]+=fl[i^1];
        fl[i^1]=0;
    }
}

int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
    ini();
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);								    
	}
	printf("%d",dinic());
	return 0;				
}
