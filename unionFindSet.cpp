#include<bits/stdc++.h>

using namespace std;

const int N=100000;

int n;
int pa[N];

void init(){
	for(int i=1;i<=n;i++){
		pa[i]=i;
	}
}

int find(int x){
	if(pa[x]==x)return x;
	else return pa[x]=find(pa[x]);
}
