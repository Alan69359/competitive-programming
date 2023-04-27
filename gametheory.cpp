#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int f[N];
int set0[N];

int nim1(){
    scanf("%d",&n);
    int res=0;
    while(n--){
        int a;
        scanf("%d",&a);
        res^=a;
    }
    if(res)return 0;
    else return 1;
}

int nim2(){
    scanf("%d",&n);
    int res=0;
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);
        if(i&1)res^=a;
    }
    if(res)return 0;
    else return 1;
}

int sg(int x){
    if(f[x]!=-1)return f[x];
    unordered_set<int>s;
    for(int i=0;i<m;i++){
        int co=set0[i];
        if(x>=co){
            s.insert(sg(x-co));
        }
    }
    for(int i=0;;i++){
        if(!s.count(i)){
            return f[x]=i;
        }
    }
}

int nim3(){
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&set0[i]);
    }
    scanf("%d",&n);
    memset(f,-1,sizeof f);
    int res=0;
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        res^=sg(a);
    }
    if(res)return 0;
    else return 1;
}

int main(){
    int res=nim3();
    if(res==0)printf("Yes");
    else printf("No");
}
