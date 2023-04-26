#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=1000001,M=10000010;

int n,m;
int ne[M];
char s1[M],s2[N];

void kmp(){
	scanf("%d%s%d%s",&n,s1+1,&m,s2+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&s1[i]!=s1[j+1])j=ne[j];
		if(s1[i]==s1[j+1])j++;
		ne[i]=j;
	}
	for(int i=1,j=0;i<=m;i++){
		while(j&&s2[i]!=s1[j+1])j=ne[j];
		if(s2[i]==s1[j+1])j++;
		if(j==n){
			printf("%d ",i-n);
			j=ne[j];
		}
	}
}
