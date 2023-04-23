#include<bits/stdc++.h>

using namespace std;

const int N=201,INF=0x3f;

int n,m,k;
int d[N][N];

void floyd(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int k=1;k<=n;k++){
		for(int j=1;j<=n;j++){
			d[k][j]=(k==j?0:INF);
		}
	}
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		d[a][b]=min(d[a][b],c);
	}
	floyd();
	while(k--){
		int a,b;
		scanf("%d%d",&a,&b);
		if(d[a][b]>INF/2)printf("impossible\n");
		else printf("%d\n",d[a][b]);
	}
	return 0;
}
