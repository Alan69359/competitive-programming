#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int a[N];

ll stein1(ll a,ll b){
    if(a<b)swap(a,b);
    if(!b)return a;
    else if((!(a&1))&&(!(b&1))){
        return stein1(a>>1,b>>1)<<1;
    }
    else if((!(a&1))&&(b&1)){
        return stein1(a>>1,b);
    }
    else if((!(a&1))&&(b&1)){
        return stein1(a>>1,b);
    }
    else return stein1(a-b,b);
}

ll stein2(ll a,ll b){
    int k=1;        
    while((!(a&1))&&(!(b&1))){
        a>>=1,b>>=1;
        k<<=1;
    } 
    while(!(a&1))a>>=1;
    while(!(b&1))b>>=1;
    if(a<b)swap(a,b);
    while(a!=b){
        a-=b;
        if(a<b)swap(a,b);
    } 
    return a*k;
}

int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%lld",stein2(a,b));
    return 0;
}
