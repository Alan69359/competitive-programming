#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int>pii;

const int N=200001;

int n;
int we[N],dist[N],le[N],ri[N],idx;
int pa[N];

bool cmp(int x,int y){
	if(we[x]!=we[y])return we[x]<we[y];
	else return x<y;
}

int find(int x){
	if(pa[x]==x)return x;
	else return pa[x]=find(pa[x]);
}

int merge(int x, int y){
	if(!x||!y)return x+y;
	if(cmp(y,x))swap(x,y);
	ri[x]=merge(ri[x],y);
	if(dist[ri[x]]>dist[le[x]])swap(le[x],ri[x]);
	dist[x]=dist[ri[x]]+1;
	return x;
}

int main(){
	scanf("%d",&n);
	we[0]=2e9;
	while(n--){
		int t,x,y;
		scanf("%d%d",&t,&x);
		if(t==1){
			we[++idx]=x;
			dist[idx]=1;
			pa[idx]=idx;
		}
		else if(t==2){
			scanf("%d",&y);
			x=find(x),y=find(y);
			if(x!=y){
				if(cmp(y,x))swap(x,y);
				pa[y]=x;
				merge(x,y);
			}
		}
		else if(t==3){
			printf("%d\n",we[find(x)]);
		}
		else{
			x=find(x);
			if(cmp(ri[x],le[x])){
				swap(le[x],ri[x]);
			}
			pa[x]=le[x];
			pa[le[x]]=le[x];
			merge(le[x],ri[x]);
		}
	}
}
