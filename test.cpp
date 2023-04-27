#include<bits/stdc++.h>

using namespace std;

const int N=55,M=5e4+50;

int f[N][M];

int dp(int a,int b){
    int &f1=f[a][b];
    if(f1!=-1)return f1;
    if(!a)return f1=!(b%2);
    if(b==1)return dp(a+1,0);
    if(a&&dp(a-1,b))return f1=0;
    if(b&&dp(a,b-1))return f1=0;
    if(a>=2&&dp(a-2,b+(b?3:2)))return f1=0;
    if(a&&b&&dp(a-1,b+1))return f1=0;
    return f1=1;
}

int main(){
    memset(f,-1,sizeof f);
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
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
        if(dp(a,b)==0)printf("YES\n");
        else printf("NO\n");
    }
}
