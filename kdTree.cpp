#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int k,root,cu;

struct Kd{
    int l,r;
    double va[k];
    double mi[k],ma[k];
    bool operator < (cosnt Kd &kd) const{
        return v[k]<kd.v[k];
    }
}tr[N];

int getmedian(int )

void pushup(int u){
    Kd &le=tr[u].l,&ri=tr[u].r;
    for(int i=0;i<2;i++){
        if(le){
            tr[u].mi[i]=min(tr[u].mi[i],tr[le].mi[i]);
            tr[u].ma[i]=max(tr[u].ma[i],tr[le].ma[i]);
        }
        if(ri){
            tr[u].mi[i]=min(tr[u].mi[i],tr[ri].mi[i]);
            tr[u].ma[i]=max(tr[u].ma[i],tr[ri].ma[i]);
        }
    }
}

int build(int l,int r,int dimension){
    if(l>r)return 0;
    int mid=(l+r)>>1;
    k=dimension;
    int median=nth_element(tr+l,tr+mid,tr+r+1);
    tr[mid].l=build(l,mid-1,k^1);
    tr[mid].r=build(mid+1,r,k^1);
    pushup(mid);
    return mid;
}

int main(){
    return 0;
}
