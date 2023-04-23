#include<bits/stdc++.h>

using namespace std;

const int N=100001;

int n,m,idx2=1;
int he[N],no[N],ne[N],idx;
int in[N],se[N];
int q[N];

void add(int a,int b){
	no[idx]=b;
	ne[idx]=he[a];
	he[a]=idx++;			
}

bool tsort(){
    int qh=0,qt=-1;
	for(int i=1;i<=n;i++){
        if(!in[i]){
            q[++qt]=i;
        }
	}
    while(qh<=qt){
        int t=q[qh++];
		se[idx2++]=t;
		for(int i=he[t];~i;i=ne[i]){
			int j=no[i];
			in[j]--;
			if(!in[j]){
                q[++qt]=j;
			}
		}
	}
	return qt==n-1;
}

int main(){
	scanf("%d%d",&n,&m);
	memset(he,-1,sizeof he);
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		in[b]++;
	}
	if(tsort()){
		for(int i=1;i<=n;i++){
			printf("%d ",se[i]);
		}
	}
	else printf("-1");
	return 0;
}
