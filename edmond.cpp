#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=110,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
pdd a1[N];
bool g[N][N];
double d[N][N],d2[N][N];
int ined[N],ined2[N];
int dfst[N],lowt[N],t;
int s[N],top;
bool ins[N];
int sccid[N],sccsi[N],scccnt;
int s2[N],ins2[N];

void dfs(int u){
    s2[u]=true;
    for(int i=1;i<=n;i++){
        if(g[u][i]&&!s2[i]){
            dfs(i);
        }
    }
}

bool isconnect(){
    memset(s2,0,sizeof s2);
    dfs(1);
    for(int i=1;i<=n;i++){
        if(!s2[i]){
            return false;
        }
    }
    return true;
}

double getdistance(int a,int b){
    double dx=a1[a].first-a1[b].first;
    double dy=a1[a].second-a1[b].second;
    return sqrt(dx*dx+dy*dy);
}

void tarjan(int u){
    //  label the strongly connected component id of every node
    dfst[u]=lowt[u]=++t;
    s[++top]=u;
    ins[u]=true;
    int j=ined[u];
    if(!dfst[j]){
        tarjan(j);
        lowt[u]=min(lowt[u],lowt[j]);
    }
    else if(ins[j]){
        lowt[u]=min(lowt[u],dfst[j]);
    }
    if(dfst[u]==lowt[u]){
        scccnt++;
        int id;
        do{
            id=s[top--];
            ins[id]=false;
            sccid[id]=scccnt;
        }while(id!=u);
    }
}

double edmond(){
    double ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(g[i][j]){
                d[i][j]=getdistance(i,j);
            }
            else d[i][j]=INF;
        }
    }
    while(1){
        for(int i=1;i<=n;i++){
            ined[i]=i;
            for(int j=1;j<=n;j++){
                if(d[ined[i]][i]>d[j][i]){
                    ined[i]=j;
                }
            }
        }
        memset(dfst,0,sizeof dfst);
        t=scccnt=0;
        for(int i=1;i<=n;i++){
            if(!dfst[i]){
                tarjan(i);
            }
        }
        if(scccnt==n){
            for(int i=2;i<=n;i++){
                ans+=d[ined[i]][i];
            }
            break;
        }
        for(int i=2;i<=n;i++){
            if(sccid[ined[i]]==sccid[i]){
                ans+=d[ined[i]][i];
            }
        }
        for(int i=1;i<=scccnt;i++){
            for(int j=1;j<=scccnt;j++){
                d2[i][j]=INF;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(d[i][j]<INF&&sccid[i]!=sccid[j]){
                    int a=sccid[i],b=sccid[j];
                    if(sccid[ined[j]]==sccid[j]){
                        d2[a][b]=min(d2[a][b],d[i][j]-d[ined[j]][j]);

                    }
                    else d2[a][b]=min(d2[a][b],d[i][j]);
                }
            }
        }
        n=scccnt;
        memcpy(d,d2,sizeof d);
    }
    return ans;
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        for(int i=1;i<=n;i++){
            scanf("%lf%lf",&a1[i].first,&a1[i].second);
        }
        memset(g,0,sizeof g);
        while(m--){
            int a,b;
            scanf("%d%d",&a,&b);
            if(a!=b&&b!=1){
                g[a][b]=true;
            }
        }
        if(!isconnect()){
            printf("poor snoopy\n");
        }
        else printf("%.2lf\n",edmond());
    }
}
