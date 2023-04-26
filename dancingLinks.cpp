#include<bits/stdc++.h>

using namespace std;

const int N=5510;

int n,m;
int l[N],r[N],u[N],d[N],s[N],row[N],col[N],idx;
int ans[N],top;

void init(){
    for(int i=0;i<=m;i++){
        l[i]=i-1,r[i]=i+1;
        u[i]=d[i]=i;
    }
    l[0]=m,r[m]=0;
    idx=m+1;
}

void add(int &qh,int &qt,int x,int y){
    row[idx]=x,col[idx]=y,s[y]++;
    u[idx]=y,d[idx]=d[y];
    u[d[y]]=idx,d[y]=idx;
    r[qh]=l[qt]=idx;
    r[idx]=qt,l[idx]=qh;
    qt=idx++;
}

void delet(int p){
    r[l[p]]=r[p],l[r[p]]=l[p];
    for(int i=d[p];i!=p;i=d[i]){
        for(int j=r[i];j!=i;j=r[j]){
            s[col[j]]--;
            u[d[j]]=u[j],d[u[j]]=d[j];
        }
    }
}

void resum(int p){
    for(int i=u[p];i!=p;i=u[i]){
        for(int j=l[i];j!=i;j=l[j]){
            u[d[j]]=j,d[u[j]]=j;
            s[col[j]]++;
        }
    }
    r[l[p]]=p,l[r[p]]=p;
}

int main(){
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=n;i++){
        int qh=idx,qt=idx;
        for(int j=1;j<=m;j++){
            int x;
            scanf("%d",&x);
            if(x)add(qh,qt,i,j);
        }
    }
    return 0;
}