#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1000010,M=100001,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-9;

int n,m;
char s[N];
int su[N],fi[N],se[N],cnt[N],rk[N],he[N];

void getsu(){
	for(int i=1;i<=n;i++){
		cnt[fi[i]=s[i]]++;
	}
	for(int i=2;i<=m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=n;i;i--){
		su[cnt[fi[i]]--]=i;
	}
	for(int k=1;k<=n;k<<=1){
		int num=0;
		for(int i=n-k+1;i<=n;i++){
			se[++num]=i;
		}
		for(int i=1;i<=n;i++){
			if(su[i]>k){
				se[++num]=su[i]-k;
			}
		}
		for(int i=1;i<=m;i++){
			cnt[i]=0;
		}
		for(int i=1;i<=n;i++){
			cnt[fi[i]]++;
		}
		for(int i=2;i<=m;i++){
			cnt[i]+=cnt[i-1];
		}
		for(int i=n;i;i--){
			su[cnt[fi[se[i]]]--]=se[i];
			se[i]=0;
		}
		swap(fi,se);
		fi[su[1]]=1,num=1;
		for(int i=2;i<=n;i++){
			fi[su[i]]=(se[su[i]]==se[su[i-1]]&&se[su[i]+k]==se[su[i-1]+k])?num:++num;
		}
		if(num==n)break;
		m=num;
	}
}

void gethe(){
	for(int i=1;i<=n;i++){
		rk[su[i]]=i;
	}
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1)continue;
		if(k)k--;
		int j=su[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])k++;
		he[rk[i]]=k;
	}
}

int main(){
	scanf("%s",s+1);
	n=strlen(s+1),m=122;
	getsu();
	gethe();
	for(int i=1;i<=n;i++){
		printf("%d ",su[i]);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d ",he[i]);
	}
}
