#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;
typedef pair<double,double>pdd;

const int N=101,M=101,INF=0x3f3f3f3f;
const double EPS=1e-6;

int n;
double e[N][N];

int gaussian(){
	int r,c;
	for(c=0,r=0;c<n;c++,r++){
		int tr=r;
		for(int i=r+1;i<n;i++){
			if(fabs(e[i][c])>fabs(e[tr][c]))tr=i;
		}
		if(fabs(e[tr][c])<EPS)continue;
		for(int i=c;i<=n;i++){
			swap(e[tr][i],e[r][i]);
		}
		for(int i=n;i>=c;i--){
			e[r][i]/=e[r][c];			        
		}
		for(int i=r+1;i<n;i++){
			if(fabs(e[i][c])>EPS){
				for(int j=n;j>=c;j--){
					e[i][j]-=e[r][j]*e[i][c];
				}
			}
		}
	}
	if(r<n){
		for(int i=r;i<n;i++){
			if(fabs(e[i][n])>EPS)return 0;
		}
		return 2;
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++){
			e[i][n]-=e[i][j]*e[j][n];
		}
	}
	return 1;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n+1;j++) {
			scanf("%lf",&e[i][j]);
		}
	}
	int ans=gaussian();
	if(ans==1){
		for(int i=0;i<n;i++){
			if(fabs(e[i][n])==0)e[i][n]=0;
			printf("%.2lf\n",e[i][n]);
		}
	}
	else if(ans==2)printf("Infinite group solutions\n");
	else printf("No solution\n");
	return 0;
}
