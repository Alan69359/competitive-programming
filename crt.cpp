#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

int n;

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

ll mod(ll a,ll b){
	return (a%b+b)%b;
}

ll crt(){
	scanf("%d",&n);
	bool find=true;
	ll a1,m1;
	scanf("%lld%lld",&a1,&m1);
	for(int i=1;i<n;i++){
		ll a2,m2;
		scanf("%lld%lld",&a2,&m2);
		ll k1,k2;
		ll d=exgcd(a1,a2,k1,k2);
		if((m2-m1)%d){
			find=false;
			break;
		}
		k1*=(m2-m1)/d;
		k1=mod(k1,a2/d);
		m1+=a1*k1;
		a1=abs(a1/d*a2);
	}
	if(find)return mod(m1,a1);
	else return -1;
}
