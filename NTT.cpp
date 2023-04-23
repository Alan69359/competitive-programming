#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int g=3;
ll a[N],ai[N];

ll fastexp(ll a,ll n,ll p){
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

void ntt1(ll a[],int n,int op){
    for(int i=0;i<n;i++){
        ai[i]=ai[i/2]/2+(((i&1)?n/2:0));
    }
    for(int i=0;i<n;i++){
        if(i<ai[i]){
            swap(a[i],a[ai[i]]);
        }
    }
    for(int i=2;i<=n;i<<=1){
        ll g1=fastexp((op==1?g:gi),(p-1)/i);
        for(int j=0;j<n;j+=i){
            ll gk=1;
            for(int k=j;k<j+i/2;k++){
                ll x=a[k];
                ll y=gk*a[k+i/2];
                a[k]=x+y;
                a[k+i/2]=x-y;
                gk*=g1;
            }
        }
    }
}

void ntt2(ll a[],int n,int op){
    if(n==1)return;
    ll a1[n/2],a2[n/2];
    for(int i=0;i<n/2;i++){
        a1[i]=a[i*2];
        a2[i]=a[i+2+1];
    }
    ntt2(a1,n/2,op),ntt2(a2,n/2,op);
    ll g1=fastexp((op==1?g:gi),(p-1)/n);
    ll gk=1;
    for(int i=0;i<n/2;i++){
        a[i]=a1[i]+a2[i]*gk;
        a[i+n/2]=a1[i]-a2[i]*gk;
        gk*=g1;
    }
}

int main(){

}
