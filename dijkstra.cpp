#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>pii;

const int N=150001,M=N*2;

int n,m,st,en;
int he[N],no[M],we[M],ne[M],idx;
int dist[N];
bool state[N];

void add(int a,int b,int c){
	no[idx]=b;
	we[idx]=c;
	ne[idx]=he[a];
	he[a]=idx++;
}

int dijk(){
	memset(dist,0x3f,sizeof dist);
	dist[st]=0;
	priority_queue<pii,vector<pii>,greater<pii>>h;
	h.push({0,st});
	while(!h.empty()){
		auto t=h.top();
		h.pop();
		state[t.second]=true;
		for(int i=he[t.second];~i;i=ne[i]){
			int j=no[i];
			if(dist[j]>dist[t.second]+we[i]){
				dist[j]=dist[t.second]+we[i];
				h.push({dist[j],j});
			}
		}
	}
	return dist[en];
}

int main(){
	scanf("%d%d%d%d",&n,&m,&st,&en);
	memset(he,-1,sizeof he);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	int res=dijk();
	printf("%d\n",res);
	return 0;
}
