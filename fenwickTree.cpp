#include<bits/stdc++.h>

using namespace std;

const int N=200001;

int n;
int a[N];
int tr[N];

int lsb(int x){
	return x&-x;
}

void add(int x,int c){
	for(int i=x;i<=n;i+=lsb(i)){
		tr[x]+=c;
	}
}

int sum(int x){
	int res=0;
	for(int i=x;i;i-=lsb(i)){
		res+=tr[i];
	}
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	return 0;
}
