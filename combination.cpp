#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int a[N][N];
ll factorial[N],infactorial[N];
int p;

ll fastexp(int a,int n,int p){
    ll res=1;
    while(n){
        if(n&1){
            res=res*a%p;
        }
        n>>=1;
        a=(ll)a*a%p;
    }
    return res;		
}

void init1(){
    for(int i=0;i<N;i++){
        for(int j=0;j<=i;j++){
            if(!j)a[i][j]=1;
            else a[i][j]=(a[i-1][j]+a[i-1][j-1])%mod;
        }
    }
}

void init2(){
    factorial[0]=infactorial[0]=1;
    for(int i=1;i<N;i++){
        factorial[i]=factorial[i-1]*i;
        infactorial[i]=infactorial[i-1]*fastexp(i,MOD-2,1);
    }
}

ll C(int n,int r){
    if(n<r)return 0;
    else return factorial[n]*infactorial[r]*infactorial[n-r];
}

ll P(int n,int r){
    if(n<r)return 0;
    else return factorial[n]*infactorial[n-r];
}

void f1(){
    init1();
    int n,r;
    scanf("%d%d",&n,&r);
    printf("%d",a[n][r]);
}

void f2(){
    init2();
    int n,r;
    scanf("%d%d",&n,&r);
    printf("%d",factorial[n]*infactorial[r]*infactorial[n-r]);
}

ll lucas(ll a,ll b){
    if(a<p&&b<p){
        return C(a,b);
    }
    else return C(a%p,b%p)*lucas(a/p,b/p);
}

void f3(){

}

int main(){
    init1();
    init2();
}
