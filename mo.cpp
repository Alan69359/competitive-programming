#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;
typedef pair<double,double>pdd;

const int N=100010,M=200010,S=1000010,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-9;

int n,m;
int qnum,mnum;
int arr[N],cnt[N],ans[N],len;
int st[N];
vector<int>vec;
int he[N],no[N],ne[N],idx;
int dep[N],p[N][16];
int seq[N],top,fi[N],la[N];
int que[N];

struct Query{
    int id,l,r;
    int p;
}q[M];
struct Modify{
    int k,nx;
}mo[N];

int getid(int x){
    return x/len;
}

bool cmp(const Query& a,const Query& b){
    int al=getid(a.l),bl=getid(b.l);
    if(al!=bl)return al<bl;
    else return a.r<b.r;
}

bool cmp2(const Query& a,const Query& b){
    int al=getid(a.l),ar=getid(a.r);
    int bl=getid(b.l),br=getid(b.r);
    if(al!=bl)return al<bl;
    else if(ar!=br)return ar<br;
    else return a.t<b.t;
}

void add(int x,int& res){
    if(!cnt[x])res++;
    cnt[x]++;
}

void add2(int x,ll& res){
    cnt[x]++;
    res=max(res,(ll)cnt[x]*vec[x]);
}

void add3(int x,int& res){
    st[x]^=1;
    if(!st[x]){
        cnt[arr[x]]--;
        if(!cnt[arr[x]])res--;
    }
    else{
        if(!cnt[arr[x]])res++;
        cnt[arr[x]]++;
    }
}

void rem(int x,int& res){
    cnt[x]--;
    if(!cnt[x])res--;
}

void Mo(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    scanf("%d",&m);
    len=max(1,(int)sqrt((double)n*n/m));
    for(int i=0;i<m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        q[i]={i,l,r};
    }
    sort(q,q+m,cmp);
    int res=0;
    for(int k=0,i=0,j=1;k<m;k++){
        int id=q[k].id,l=q[k].l,r=q[k].r;
        while(i<r)add(arr[++i],res);
        while(i>r)rem(arr[i--],res);
        while(j<l)rem(arr[j++],res);
        while(j>l)add(arr[--j],res);
        ans[id]=res;
    }
    for(int i=0;i<m;i++){
        printf("%d\n",ans[i]);
    }
}

void Mo2(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<m;i++){
        char op[2];
        int a,b;
        scanf("%s%d%d",op,&a,&b);
        if(op[0]=='Q'){
            qnum++;
            q[qnum]={qnum,a,b,mnum};
        }
        else mo[++mnum]={a,b};
    }
    len=pow((double)n*max(1,mnum),1.0/3);
    sort(q+1,q+qnum+1,cmp2);
    int res=0;
    for(int i=0,j=1,tt=0,k=1;k<=qnum;k++){
        int id=q[k].id,l=q[k].l,r=q[k].r,t=q[k].t;
        while(i<r)add(a[++i],res);
        while(i>r)rem(a[i--],res);
        while(j<l)rem(a[j++],res);
        while(j>l)add(a[--j],res);
        while(tt<t){
            tt++;
            if(mo[tt].k>=j&&mo[tt].k<=i){
                rem(a[mo[tt].k],res);
                add(mo[tt].nx,res);
            }
            swap(a[mo[tt].k],mo[tt].nx);
        }
        while(tt>t){
            if(mo[tt].k>=j&&mo[tt].k<=i){
                rem(a[mo[tt].k],res);
                add(mo[tt].nx,res);
            }
            swap(a[mo[tt].k],mo[tt].nx);
            tt--;
        }
        ans[id]=res;
    }
    for(int i=1;i<=qnum;i++){
        printf("%d\n",ans[i]);
    }
}

void Mo3(){
    scanf("%d%d",&n,&m);
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        vec.push_back(arr[i]);
    }
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(int i=1;i<=n;i++){
        arr[i]=lower_bound(vec.begin(),vec.end(),arr[i])-vec.begin();
    }
    for(int i=0;i<m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        q[i]={i,l,r};
    }
    sort(q,q+m,cmp);
    for(int x=0;x<m;){
        int y=x;
        while(y<m&&getid(q[y].l)==getid(q[x].l))y++;
        int ta=getid(q[x].l)*len+len-1;
        while(x<y&&q[x].r<=ta){
            ll res=0;
            int id=q[x].id,l=q[x].l,r=q[x].r;
            for(int k=l;k<=r;k++){
                add2(arr[k],res);
            }
            ans[id]=res;
            for(int k=l;k<=r;k++){
                cnt[arr[k]]--;
            }
            x++;
        }
        ll res=0;
        int i=ta,j=ta+1;
        while(x<y){
            int id=q[x].id,l=q[x].l,r=q[x].r;
            while(i<r)add2(arr[++i],res);
            ll rres=res;
            while(j>l)add2(arr[--j],res);
            ans[id]=res;
            while(j<ta+1){
                cnt[arr[j++]]--;
            }
            res=rres;
            x++;
        }
        memset(cnt,0,sizeof cnt);
    }
    for(int i=0;i<m;i++){
        printf("%lld\n",ans[i]);
    }
}

void added(int a,int b){
    no[idx]=b;
    ne[idx]=he[a];
    he[a]=idx++;
}

void dfs(int u,int father){
    seq[++top]=u;
    fi[u]=top;
    for(int i=he[u];~i;i=ne[i]){
        int j=no[i];
        if(j!=father)dfs(j,u);
    }
    seq[++top]=u;
    la[u]=top;
}

void bfs(){
    memset(dep,0x3f,sizeof dep);
    dep[0]=0,dep[1]=1;
    int qh=0,qt=0;
    que[0]=1;
    while(qh<=qt){
        int t=que[qh++];
        for(int i=he[t];~i;i=ne[i]){
            int j=no[i];
            if(dep[j]>dep[t]+1){
                dep[j]=dep[t]+1;
                p[j][0]=t;
                for(int k=1;k<=15;k++)
                    p[j][k]=p[p[j][k-1]][k-1];
                que[++qt]=j;
            }
        }
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b])swap(a,b);
    for(int k=15;k>=0;k--)
        if(dep[p[a][k]]>=dep[b])
            a=p[a][k];
    if(a==b)return a;
    for(int k=15;k>=0;k--){
        if(p[a][k]!=p[b][k]){
            a=p[a][k];
            b=p[b][k];
        }
    }
    return p[a][0];
}

void Mo4(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        vec.push_back(arr[i]);
    }
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    for(int i=1;i<=n;i++){
        arr[i]=lower_bound(vec.begin(),vec.end(),arr[i])-vec.begin();
    }
    memset(he,-1,sizeof he);
    for(int i=0;i<n-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        added(a,b),added(b,a);
    }
    dfs(1,-1);
    bfs();
    for(int i=0;i<m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        if(fi[a]>fi[b])swap(a,b);
        int p=lca(a,b);
        if(a==p)q[i]={i,fi[a],fi[b]};
        else q[i]={i,la[a],fi[b],p};
    }
    len=sqrt(top);
    sort(q,q+m,cmp);
    int res=0;
    for(int k=0,i=0,j=1;k<m;k++){
        int id=q[k].id,l=q[k].l,r=q[k].r,p=q[k].p;
        while(i<r)add3(seq[++i],res);
        while(i>r)add3(seq[i--],res);
        while(j<l)add3(seq[j++],res);
        while(j>l)add3(seq[--j],res);
        if(p)add3(p,res);
        ans[id]=res;
        if(p)add3(p,res);
    }
    for(int i=0;i<m;i++){
        printf("%d\n",ans[i]);
    }
}

int main(){
    Mo4();
    return 0;
}
