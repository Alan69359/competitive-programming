#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=2e6+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int tot=1,last=1;

struct Node{
    int maxlen,fa;
    int ch[26];
}no[N];

char str[N];
ll f[N],ans;
int he[N],no[N],ne[N],idx;

void add(int a,int b){
    no[idx]=b;
    ne[idx]=he[a];
    he[a]=idx++;
}

void extend(int c){
    int p=last,np=last=++tot;
    f[tot]=1;
    no[np].maxlen=no[p].maxlen+1;
    for(;p&&!no[p].ch[c];p=no[p].fa){
        no[p].ch[c]=np;
    }
    if(!p){
        no[np].fa=1;
    }
    else {
        int q=no[p].ch[c];
        if(no[q].maxlen==no[p].maxlen+1){
            no[np].fa=q;
        }
        else {
            int nq=++tot;
            no[nq]=no[q];
            no[nq].maxlen=no[p].maxlen+1;
            no[q].fa=no[np].fa=nq;
            for(;p&&no[p].ch[c]==q;p=no[p].fa){
                no[p].ch[c]=nq;
            }
        }
    }
}

void dfs(int u){
    for(int i=he[u];~i;i=ne[i]){
        int j=no[i];
        dfs(j);
        f[u]+=f[j];
    }
    if(f[u]>1){
        ans=max(ans,f[u]*no[u].maxlen);
    }
}

int main(){
    scanf("%s",str);
    for(int i=0;str[i];i++){
        extend(str[i]-'a');
    }
    memset(he,-1,sizeof he);
    for(int i=2;i<=tot;i++){
        add(no[i].fa,i);
    }
    dfs(1);
    printf("%lld",ans);
}
