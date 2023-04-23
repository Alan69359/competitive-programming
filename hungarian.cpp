#include<bits/stdc++.h>

using namespace std;

const int N=510,M=100010;

int n1,n2,m;
int he[N],no[M],ne[M],idx;
int match[N];
bool st[N];

void add(int a,int b){
	no[idx]=b;
	ne[idx]=he[a];
	he[a]=idx++;
}

bool find(int x){
	for(int i=he[x];~i;i=ne[i]){
		int j=no[i];
		if(!st[j]){
			st[j]=true;
			if(match[j]==0||find(match[j])){
				match[j]=x;
				return true;
			}
		}
	}
	return false;
}

int main(){
	scanf("%d%d%d",&n1,&n2,&m);
	memset(he,-1,sizeof he);
	while(m--){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);							    
	}
	int res=0;
	for(int i=1;i<=n1;i++) {
		memset(st,false,sizeof st);
		if(find(i))res++;
	}
	printf("%d",res);
	return 0;
}
