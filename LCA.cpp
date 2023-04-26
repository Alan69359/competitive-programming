#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>pii;

const int N=150001,M=N*2;

int n,m;
int he[N],no[M],we[M],ne[M],idx;
int de[N],fa[N][16];
int q[N];
int pa[N];
int st[N];
vector<pii>query[N];
int anc[N];

void add(int a,int b){
	no[idx]=b;
	ne[idx]=he[a];
	he[a]=idx++;
}

void bfs(int root){
	memset(de,0x3f,sizeof de);
	de[0]=0,de[root]=1;
	int qh=0,qt=0;
	q[0]=root;
	while(qh<=qt){
		int t=q[qh++];
		for(int i=he[t];~i;i=ne[i]){
			int j=no[i];
			if(de[j]>de[t]+1){
				de[j]=de[t]+1;
				q[++qt]=j;
				fa[j][0]=t;
				for(int k=1;k<=15;k++){
					fa[j][k]=fa[fa[j][k-1]][k-1];
				}
			}
		}
	}
}

int lca(int a,int b){
	if(de[a]<de[b])swap(a,b);
	for(int k=15;k>=0;k--){
		if(de[fa[a][k]]>=de[b]){
			a=fa[a][k];
		}
	}
	if(a==b)return a;
	for(int k=15;k>=0;k--){
		if(fa[a][k]!=fa[b][k]){
			a=fa[a][k];
			b=fa[b][k];
		}
	}
	return fa[a][0];
}

int find(int x){
	if(pa[x]==x)return x;
	else return pa[x]=find(pa[x]);
}

void tarjan(int u){
//	tarjan offline algorithm
	st[u]=1;
	for(int i=he[u];~i;i=ne[i]){
		int j=no[i];
		if(!st[j]){
			tarjan(j);
			pa[j]=u;
		}
	}
	for(auto a:query[u]){
		int b=a.first,id=a.second;
		if(st[b]==2){
			anc[id]=find(b);
		}
	}
	st[u]=2;
}

int main(){
	memset(he,-1,sizeof he);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		if(a!=b){
			query[a].push_back({b,i});
			query[b].push_back({a,i});
		}
	}
	for(int i=1;i<=n;i++){
		pa[i]=i;
	}
	tarjan(1);
	return 0;
}
