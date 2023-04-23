#include<bits/stdc++.h>

using namespace std;

const int N=10000,M=20000;

int n,m;

int he[N],no[M],we[M],ne[M],idx;
int dfst[N],lowt[N],t;
int s[N],top;
bool insta[N];

void add(int a,int b,int c){
	no[idx]=b;
	we[idx]=c;
	ne[idx]=he[a];
	he[a]=idx++;
}

void tarjan(int u){
	dfst[u]=lowt[u]=++t;
	s[++top]=u;
	insta[u]=true;
	for(int i=he[u];~i;i=ne[i]){
		int j=no[i];
		if(!dfst[j]){
			tarjan(j);
			lowt[u]=min(lowt[u],lowt[j]);
		}
		else if(insta[j]){
			lowt[u]=min(lowt[u],dfst[j]);
		}
	}
}
