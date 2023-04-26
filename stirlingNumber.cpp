#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=10001,M=100001,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int f1[N][N],f2[N][N];

void stirlingnumber1(){
//	stirling numbers of the first kind
	scanf("%d%d",&n,&m);
	f1[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f1[i][j]=(f1[i-1][j-1]+(ll)(i-1)*f1[i-1][j])%MOD;
		}
	}
	printf("%d",f1[n][m]);
}

void stirlingnumber2(){
//	stirling numbers of the second kind
	scanf("%d%d",&n,&m);
	f2[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f2[i][j]=(f2[i-1][j-1]+(ll)j*f2[i-1][j])%MOD;
		}
	}
	printf("%d",f2[n][m]);
}


int main(){
	return 0;
}
