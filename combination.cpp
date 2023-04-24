#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int a[N][N];
ll factorial[N],infactorial[N];
int mod;
int p[N],co;
int pp1[N][2],pp2[N][2],pp3[N][2];
int sum[N];

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
        factorial[i]=factorial[i-1]*i%mod;
        infactorial[i]=infactorial[i-1]*fastexp(i,mod-2,mod)%mod;
    }
}

ll C1(int n,int r){
    if(n<r)return 0;
    else return factorial[n]*infactorial[r]%mod*infactorial[n-r]%mod;
}

ll P(int n,int r){
    if(n<r)return 0;
    else return factorial[n]*infactorial[n-r]%mod;
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

ll C2(int n,int r){
    ll ans=1;
    for(int i=1,j=n;i<=r;i++,j--){
        ans=ans*j%mod*fastexp(i,mod-2,mod)%mod;
    }
    return ans;
}

ll lucas(ll a,ll b,ll p){
    if(a<p&&b<p){
        return C2(a,b);
    }
    else return C2(a%p,b%p)*lucas(a/p,b/p,p)%p;
}

void f3(){
    int n,r,p;
    scanf("%d%d%d",&n,&r,&p);
    printf("%lld",lucas(n,r,p));
}

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

void primefactorization(int p[][2],int x){
    int j=0;
    for(int i=0;i<co;i++){
        int prime=p[i];
		if(x%prime==0){
			int count=0;
			while(x%i==0){
				x/=i;
				count++;
			}
			p[j][0]=i,p[j][1]=count;
            j++;
		}
	}
	if(x>1){
		p[j][0]=x,p[j][1]=1;
	}
}

vector<int>multiple(vector<int>&a,int b){
	vector<int>c;
	int comp=0;
	for(int i=0;i<a.size()||comp;i++){
		if(i<a.size())comp+=a[i]*b;
		c.push_back(comp%10);
		comp/=10;
	}
	while(c.size()>1&&c.back()==0)c.pop_back();
	return c;
}

int getcount(int p[][2],int prime){
    for(int i=0;i<6;i++){
        if(p[i][0]==prime)return p[i][1];
    }
    return 0;
}

void f4(){
    int n,r;
    scanf("%d%d",&n,&r);
    linearsieve(5010);
    primefactorization(pp1,a);
    primefactorization(pp2,b);
    primefactorization(pp3,a-b);
    for(int i=0;i<co;i++){
        int prime=p[i];
        sum[i]=pp1[][1]-pp2[][1]-pp3[][1];
    }
    vector<int>ans;
    ans.push_back(1);
    for(int i=0;i<co;i++){
        for(int j=0;j<sum[i];j++){
            res=multi(res,p[i]);
        }
    }
    for(int i=ans.size()-1;i>=0;i--){
        printf("%d",ans[i]);
    }
}

int main(){
    return 0;
}
