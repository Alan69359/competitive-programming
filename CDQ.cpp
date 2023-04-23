#include<bits/stdc++.h>

using namespace std;

const int N=100010,M=N*2;

int n,m;

struct Data{
    int a,b,c,s,res;
    bool operator < (const Data& da) const{
        if(a!=da.a)return a<da.a;
        else if(b!=da.b)return b<da.b;
        else return c<da.c;
    }
    bool operator == (const Data& da) const{
        return a==da.a&&b==da.b&&c==da.c;
    }
}d[N],w[N];

int tr[M],ans[M];

int lowbit(int x){
    return x&-x;
}

void add(int x,int val){
    for(int i=x;i<M;i+=lowbit(i)){
        tr[i]+=val;
    }
}

int query(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res+=tr[i];
    }
    return res;
}

void msort(int l,int r){
    if(l>=r)return;
    int mid=l+(r-l)/2;
    msort(l,mid),msort(mid+1,r);
    int i=l,j=mid+1,k=0;
    while(i<=mid&&j<=r){
        if(d[i].b<=d[j].b){
            add(d[i].c,d[i].s);
            w[k++]=d[i++];
        }
        else {
            d[j].res+=query(d[j].c);
            w[k++]=d[j++];
        }
    }
    while(i<=mid){
        add(d[i].c,d[i].s);
        w[k++]=d[i++];
    }
    while(j<=r){
        d[j].res+=query(d[j].c);
        w[k++]=d[j++];
    }
    for(int i=l;i<=mid;i++){
        add(d[i].c,-d[i].s);
    }
    for(int i=l,j=0;j<k;i++,j++){
        d[i]=w[j];
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        d[i]={a,b,c,1};
    }
    sort(d,d+n);
    int k=1;
    for(int i=1;i<n;i++){
        if(d[i]==d[k-1])d[k-1].s++;
        else d[k++]=d[i];
    }
    msort(0,k-1);
    for(int i=0;i<k;i++){
        ans[d[i].res+d[i].s-1]+=d[i].s;
    }
    for(int i=0;i<n;i++){
        printf("%d\n",ans[i]);
    }
}