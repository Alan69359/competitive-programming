#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double>pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int q[N],qh,qt;

int main(){
    scanf("%d",&n);
    qt=-1;
    while(n--){
        char op[6];
        int x;
        scanf("%s",op);
        if(!strcmp(op,"push")){
            scanf("%d",&x);
            q[++qt]=x;
        }
        else if(!strcmp(op,"pop")){
            qh++;
        }
        else if(!strcmp(op,"empty")){
            if(qh>qt){
                printf("YES\n");
            }
            else printf("NO\n");
        }
        else printf("%d\n",q[qh]);
    }
}
