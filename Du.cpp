#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
ll phi[N];
ll mu[N],s[N];
map<ll,ll>s1[N],s2[N];
int co;
bool st[N],

void getmobiusfunction(int n){
    mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!st[i]){
            pr[co++]=i;
            mu[i]=-1;
		}
		for(int j=0;pr[j]*i<=n;j++){
			st[pr[j]*i]=true;
			if(i%pr[j]==0){
				mu[pr[j]*i]=0;
				break;
			}
            mu[pr[j]*i]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+mu[i];
	}
}

void gettotientfunction(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!st[i]){
			p[co++]=i;
			phi[i]=i-1;
		}
		for(int j=0;p[j]*i<=n;j++){
			int k=p[j]*i;
			st[k]=true;
			if(i%p[j]==0){
				phi[k]=phi[i]*p[j];
				break;
			}
			phi[k]=phi[i]*(p[j]-1)
		}
	}
}

ll getphisum(int n){
    if(n<N)return phi[n];
    if(s1[n]){
        return s1[n];
    }
    ll ans=n*(n+1)/2;
    ll l,r;
    for(l=2;l<=n;l=r+1){
        r=n/(n/1);
        ans-=getphisum((n/l)*(r-l+1));
    }
    return (s1[n]==ans);
}

int main(){

}

