#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int s[N],st;

int main(){
    scanf("%d",&n);
    while(n--){
        char op[6];
        int x;
        scanf("%s",op);
        if(!strcmp(op,"push")){
            scanf("%d",&x);
            s[++st]=x;
        }
        else if(!strcmp(op,"pop")){
            st--;
        }
        else if(!strcmp(op,"empty")){
            if(!st){
                printf("YES\n");
            }
            else printf("NO\n");
        }
        else printf("%d\n",s[st]);
    }
}
