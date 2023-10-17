#include<bits/stdc++.h>

using namespace std;

const int N=5010,M=100010,INF=1e8;

int n,m,s,t;
int he[N],no[M],fl[M],we[M],ne[M],idx;
int q[N],d[N],preno[N],infl[N];
bool st[N];

void add(int a,int b,int c,int d){
    no[idx]=b,fl[idx]=c,we[idx]=d,ne[idx]=he[a],he[a]=idx++;
    no[idx]=a,fl[idx]=0,we[idx]=-d,ne[idx]=he[b],he[b]=idx++;
}

bool spfa(int op){
    int qh=0,qt=1;
    memset(d,-0x3f*op,sizeof d);
    memset(infl,0,sizeof infl);
    q[0]=s,d[s]=0;
    infl[s]=INF;
    while(qh!=qt){
        int top=q[qh++];
        if(qh==N)qh=0;
        st[top]=false;
        for(int i=he[top];~i;i=ne[i]){
            int j=no[i];
            if(fl[i]&&-d[j]*op>-(d[top]+we[i])*op){
                d[j]=d[top]+we[i];
                preno[j]=i;
                infl[j]=min(fl[i],infl[top]);
                if(!st[j]){
                    q[qt++]=j;
                    if(qt==N)qt=0;
                    st[j]=true;
                }
            }
        }
    }
    return infl[t]>0;
}

void ek(int &flow,int &cost,int op){
    flow=cost=0;
    while(spfa(op)){
        int maxf=infl[t];
        flow+=maxf,cost+=maxf*d[t];
        for(int i=t;i!=s;i=no[preno[i]^1]){
            fl[preno[i]]-=maxf;
            fl[preno[i]^1]+=maxf;
        }
    }
}

void ini(){
    memset(he,-1,sizeof he);
}

void backtrack(){
    for(int i=0;i<idx;i+=2){
        fl[i]+=fl[i^1];
        fl[i^1]=0;
    }
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    while(m--){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,c,d);
    }
    int flow,cost;
    ek(flow,cost);
    printf("%d %d",flow,cost);
    return 0;
}
