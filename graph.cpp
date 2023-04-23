#include<bits/stdc++.h>

using namespace std;

const int N=1,M=1;

int n,m;

int he[N],no[M],we[M],ne[M],idx;

void add(int a,int b,int c){
	no[idx]=b;
	we[idx]=c;
	ne[idx]=he[a];
	he[a]=idx++;
}