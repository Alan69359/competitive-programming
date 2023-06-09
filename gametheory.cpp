#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=55,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int f1[N];
int set0[N];
int f2[N][M];
int a0[N];

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

int sg1(int x){
    if(f1[x]!=-1)return f1[x];
    unordered_set<int>s;
    for(int i=0;i<m;i++){
        int co=set0[i];
        if(x>=co){
            s.insert(sg1(x-co));
        }
    }
    for(int i=0;;i++){
        if(!s.count(i)){
            return f1[x]=i;
        }
    }
}

int nim3(){
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&set0[i]);
    }
    scanf("%d",&n);
    memset(f1,-1,sizeof f1);
    int res=0;
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        res^=sg1(a);
    }
    if(res)return 0;
    else return 1;
}

int sg2(int x){
    if(f1[x]!=-1)return f1[x];
    unordered_set<int>s;
    for(int i=0;i<x;i++){
        for(int j=0;j<=i;j++){
            s.insert(sg2(i)^sg2(j));
        }
    }
    for(int i=0;;i++){
        if(!s.count(i)){
            return f1[x]=i;
        }
    }
}

int nim4(){
    scanf("%d",&n);
    memset(f1,-1,sizeof f1);
    int res=0;
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        res^=sg2(a);
    }
    if(res)return 0;
    else return 1;
}

int dp1(int a,int b){
    int &f=f2[a][b];
    if(f!=-1)return f;
    if(!a)return f=!(b%2);
    if(b==1)return dp1(a+1,0);
    if(a&&dp1(a-1,b))return f=0;
    if(b&&dp1(a,b-1))return f=0;
    if(a>=2&&dp1(a-2,b+(b?3:2)))return f=0;
    if(a&&b&&dp1(a-1,b+1))return f=0;
    return f=1;
}

int nim5(){
    scanf("%d",&n);
    memset(f2,-1,sizeof f2);
    int a=0,b=0;
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        if(x==1)a++;
        else {
            if(!b)b+=x;
            else b+=x+1;
        }
    }
    return dp1(a,b);
}

int nim6(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a0[i]);
    }
    int l[N][N],r[N][N];
    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=len+i-1;
            if(len==1){
                l[i][j]=r[i][j]=a0[i];
            }
            else {
                int le=l[i][j-1],ri=r[i][j-1];
                int x=a0[j];
                if(ri==x)l[i][j]=0;
                else if((x<le&&x<ri)||(x>le&&x>ri))l[i][j]=x;
                else if(le>ri)l[i][j]=x-1;
                else l[i][j]=x+1;

                le=l[i+1][j],ri=r[i+1][j];
                x=a0[i];
                if(le==x)r[i][j]=0;
                else if((x<le&&x<ri)||(x>le&&x>ri))r[i][j]=x;
                else if(ri>le)r[i][j]=x-1;
                else r[i][j]=x+1;
            }
        }
    }
    if(n==1)return 1;
    else return (l[2][n]!=a0[1]);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int res=nim6();
        printf("%d\n",res);
    }
}
