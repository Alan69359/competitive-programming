#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=110,M=100001,INF=0x3f3f3f3f,MOD=1e9+7;

int n;
int phi[N][N];
int p[N],co;
int p2[N][2];
int p3[N];
bool st[N];

void linearsieve(int n) {
	for(int i=2;i<=n;i++){
        if(!st[i]){
            p[co++]=i;
        }
		for(int j=0;p[j]*i<=n;j++){
			st[i*p[j]]=true;
			if(i%p[j]==0)break;
		}
	}
}

void primefactorization(int x){
    int j=0;
    for(int i=0;i<co;i++){
        int prime=p[i];
		if(x%prime==0){
			int count=0;
			while(x%i==0){
				x/=i;
				count++;
			}
			p2[j][0]=i,p2[j][1]=count;
            j++;
		}
	}
	if(x>1){
		p2[j][0]=x,p2[j][1]=1;
	}
}

void primefactorization2(int n){
//  factorize n!
    int j=0;
    for(int i=0;i<co;i++){
        int prime=p[i];
        int count=0;
        for(int k=n;k;k/=prime){
            count+=k/prime;
        }
		p2[j][0]=prime,p2[j][1]=count;
        j++;
    }
}

int phifun1(int x){
	int ans=x;
	for(int i=2;i<=x/i;i++){
		if(x%i==0){
			while(x%i==0)x/=i;
			ans=ans/i*(i-1);
		}
	}
	if(x>1){
		ans=ans/x*(x-1);
	}
	return ans;
}

void phifun2(int x){
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

ll fastexp(int a,int n,int p){
	ll ans=1;
	while(n){
		if(n&1){
			ans=(ll)ans*a%p;
		}
		n>>=1;
		a=(ll)a*a%p;
	}
	return ans;		
}

ll slowmul(ll a,ll n,ll p){
    ll ans=0;
    while(n){
        if(n&1){
            ans=(ans+a)%p;
            a=(a+a)%p;
            n>>=1;
        }
    }
    return ans;
}

int gcd(int a,int b){
	if(!b)return a;
	else return gcd(b,a%b);
}

ll lcm(int a,int b){
	return (ll)a*b/gcd(a,b);
}

int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

int main(){
	return 0;
}
