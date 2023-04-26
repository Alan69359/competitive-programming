#include<bits/stdc++.h>

using namespace std;

const int N=5010,M=100010,INF=1e8;

int n,m,s,t;
int he[N],no[M],ca[M],we[M],ne[M],idx;
int q[N],d[N],preno[N],flow[N];
bool st[N];

void add(int a,int b,int c,int d){
    no[idx]=b,ca[idx]=c,we[idx]=d,ne[idx]=he[a],he[a]=idx++;
    no[idx]=a,ca[idx]=0,we[idx]=-d,ne[idx]=he[b],he[b]=idx++;
}

bool spfa(){
    int qh=0,qt=1;
    memset(d,0x3f,sizeof d);
    memset(flow,0,sizeof flow);
    q[0]=s;
    d[s]=0;
    flow[s]=INF;
    while(qh!=qt){
        int top=q[qh++];
        if(qh==N)qh=0;
        st[top]=false;
        for(int i=he[top];~i;i=ne[i]){
            int j=no[i];
            if(ca[i]&&d[j]>d[top]+we[i]){
                d[j]=d[top]+we[i];
                preno[j]=i;
                flow[j]=min(ca[i],flow[top]);
                if(!st[j]){
                    q[qt++]=j;
                    if(qt==N)qt=0;
                    st[j]=true;
                }
            }
        }
    }
    return flow[t]>0;
}

void ek(int &curf,int &cost){
    curf=cost=0;
    while(spfa()){
        int maxf=flow[t];
        curf+=maxf,cost+=maxf*d[t];
        for(int i=t;i!=s;i=no[preno[i]^1]){
            ca[preno[i]]-=maxf;
            ca[preno[i]^1]+=maxf;
        }
    }
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    memset(he,-1,sizeof he);
    while(m--){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,c,d);
    }
    int fl,cost;
    ek(fl,cost);
    printf("%d %d",fl,cost);
    return 0;
}