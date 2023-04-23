#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int s[N];
int pr[N],st[N],co;
int mu[N];

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

int main(){
	return 0;
}
