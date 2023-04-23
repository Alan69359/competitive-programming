#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int p[N],co;
int phi[N][N];
bool st[N];

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

int main(){
    return 0;
}
