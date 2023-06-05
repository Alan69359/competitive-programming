#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;

const int N=1e6+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
char s[N];
int sa[N],bucket[N],a1[N],co[N],rank0[N],he[N];

void getsa(){
	for(int i=1;i<=n;i++)co[bucket[i]=s[i]]++;
	for(int i=1;i<=m;i++)co[i]+=co[i-1];
	for(int i=n;i;i--)sa[co[bucket[i]]--]=i;
	for(int k=1;k<=n;k<<=1){
		int num=0;
		for(int i=n-k+1;i<=n;i++)a1[++num]=i;
		for(int i=1;i<=n;i++){
			if(sa[i]>k){
				a1[++num]=sa[i]-k;
			}
		}
        memset(co,0,sizeof co);
		for(int i=1;i<=n;i++)co[bucket[i]]++;
		for(int i=2;i<=m;i++)co[i]+=co[i-1];
		for(int i=n;i;i--){
			sa[co[bucket[a1[i]]]--]=a1[i];
		}
        memset(a1,0,sizeof a1);
		swap(bucket,a1);
        bucket[sa[1]]=1,num=1;
		for(int i=2;i<=n;i++){
            if(a1[sa[i]]==a1[sa[i-1]]&&a1[sa[i]+k]==a1[sa[i-1]+k]){
                bucket[sa[i]]=num;
            }
            else bucket[sa[i]]=++num;
		}
		if(num==n)break;
		m=num;
	}
}

void gethe(){
	for(int i=1;i<=n;i++)rank0[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++){
		if(rank0[i]==1)continue;
		if(k)k--;
		int j=sa[rank0[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])k++;
		he[rank0[i]]=k;
	}
}

int main(){
	scanf("%s",s+1);
	n=strlen(s+1),m=122;
	getsa();
	gethe();
	for(int i=1;i<=n;i++){
		printf("%d ",sa[i]);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d ",he[i]);
	}
}
