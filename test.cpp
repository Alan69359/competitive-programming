#include<bits/stdc++.h>

using namespace std;

const int N=20,MOD=1e9+7;

typedef long long ll;

ll arr[N];
ll denominator=1;

ll fastexp(ll a,ll n,ll p){
    ll ans=1;
    while(n){
        if(n&1)ans=ans*a%p;
        n>>=1;
        a=a*a%p;
    }
    return ans;
}

void getdenominator(ll n){
    for(ll j=1;j<=n-1;j++){
        denominator=denominator*j%MOD;
    }
    denominator=fastexp(denominator,MOD-2,MOD)%MOD;
}

ll C(ll n,ll r){
    if(n<r)return 0;
    /*ll ans=1;*/
    /*for(ll i=1,j=n;i<=r;i++,j--){*/
    /*ans=ans*j%MOD*fastexp(i,MOD-2,MOD)%MOD;*/
    /*}*/
    /*return ans;*/
    ll nominator=1;
    for(ll i=n;i>n-r;i--){
        nominator=nominator*i%MOD;
    }
    return nominator*denominator%MOD;
}

int main(){
    ll n,m;
    scanf("%lld%lld",&n,&m);
    for(ll i=0;i<n;i++){
        scanf("%lld",&arr[i]);
    }
    getdenominator(n);
    ll ans=0;
    for(int i=0;i<1<<n;i++){
        ll a=m+n-1,b=n-1;
        int sign=1;
        for(ll j=0;j<n;j++){
            if(i>>j&1){
                sign*=-1;
                a-=arr[j]+1;
            }
        }
        ans=ans%MOD+sign*C(a%MOD,b)%MOD;
    }
    printf("%lld",(ans+MOD)%MOD);
}
