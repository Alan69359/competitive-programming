#define _CRT_SECURE_NO_WARNINGS

#include<bits/stdc++.h>
#include<utility>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=2e6+10,M=2e6+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int he[N],no[M],ne[M],idx;
int dfst[N],lowt[N],t;
int s[N],top;
bool ins[N];
int sccid[N],sccsi[N],scccnt;

void add(int a,int b){
    no[idx]=b;
    ne[idx]=he[a];
    he[a]=idx++;
}

void tarjan(int u){
	dfst[u]=lowt[u]=++t;
	s[++top]=u;
	ins[u]=true;
	for(int i=he[u];~i;i=ne[i]){
		int j=no[i];
		if(!dfst[j]){
			tarjan(j);
			lowt[u]=min(lowt[u],lowt[j]);
		}
		else if(ins[j]){
			lowt[u]=min(lowt[u],dfst[j]);
		}
	}
    if(dfst[u]==lowt[u]){
        ++scccnt;
        int id;
        do{
            id=s[top--];
            ins[id]=false;
            sccid[id]=scccnt;
        }while(id!=u);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    memset(he,-1,sizeof he);
    while(m--){
        int i,a,j,b;
        scanf("%d%d%d%d",&i,&a,&j,&b);
        i--,j--;
        add(2*i+!a,2*j+b);
        add(2*j+!b,2*i+a);
    }
    for(int i=0;i<n*2;i++){
        if(!dfst[i]){
            tarjan(i);
        }
    }
    for(int i=0;i<n;i++){
        if(sccid[i*2]==sccid[i*2+1]){
            printf("IMPOSSIBLE");
            return 0;
        }
    }
    printf("POSSIBLE\n");
    for(int i=0;i<n;i++){
        if(sccid[i*2]<sccid[i*2+1]){
            printf("0 ");
        }
        else printf("1 ");
    }
}

