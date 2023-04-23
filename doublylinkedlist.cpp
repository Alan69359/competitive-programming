#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int no[N],le[N],ri[N],idx;

void insert(int k,int x){
    no[idx]=x;
    le[idx]=k,ri[idx]=ri[k];
    le[ri[k]]=idx,ri[k]=idx++;
}

void remove(int x){
    le[ri[x]]=le[x];
    ri[le[x]]=ri[x];
}

int main(){
    scanf("%d",&n);
    ri[0]=1,le[1]=0;
    idx=2;
    while(n--){
        char op[3];
        scanf("%s",op);
        int k,x;
        if(op[0]=='L'){
            scanf("%d",&x);
            insert(0,x);
        }
        else if(op[0]=='R'){
            scanf("%d",&x);
            insert(le[1],x);
        }
        else if(op[0]=='D'){
            scanf("%d",&k);
            remove(k+1);
        }
        else if(!strcmp(op,"IL")){
            scanf("%d%d",&k,&x);
            insert(le[k+1],x);
        }
        else {
            scanf("%d%d",&k,&x);
            insert(k+1,x);
        }
    }
    for(int i=ri[0];i!=1;i=ri[i]){
        printf("%d ",no[i]);
    }
}

