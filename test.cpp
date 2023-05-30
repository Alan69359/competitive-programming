#include<bits/stdc++.h>

using namespace std;

const int N=100010;

int n,m;

struct Node{
    int s[2],p,w;
    int sum,lazy;
}tr[N];
int stk[N];

void pushrev(int x){
    swap(tr[x].s[0],tr[x].s[1]);
    tr[x].lazy^=1;
}
void pushup(int x){
    tr[x].sum=tr[tr[x].s[0]].sum^tr[x].w^tr[tr[x].s[1]].sum;
}

void pushdown(int x){
    if(tr[x].lazy){
        pushrev(tr[x].s[0]),pushrev(tr[x].s[1]);
        tr[x].lazy=0;
    }
}

bool isroot(int x){
    return tr[tr[x].p].s[0]!=x&&tr[tr[x].p].s[1]!=x;
}

void rotate(int x){
    int y=tr[x].p,z=tr[y].p;
    int k=tr[y].s[1]==x;
    if(!isroot(y))tr[z].s[tr[z].s[1]==y]=x;
    tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    pushup(y),pushup(x);
}

void splay(int x){
    int top=0,r=x;
    stk[++top]=r;
    while(!isroot(r)){
        stk[++top]=r=tr[r].p;
    }
    while(top){
        pushdown(stk[top--]);
    }
    while(!isroot(x)){
        int y=tr[x].p,z=tr[y].p;
        if(!isroot(y)){
            if((tr[y].s[1]==x)^(tr[z].s[1]==y))rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x){
    int z=x;
    for(int y=0;x;y=x,x=tr[x].p){
        splay(x);
        tr[x].s[1]=y;
        pushup(x);
    }
    splay(z);
}

void makeroot(int x){
    access(x);
    pushrev(x);
}

int findroot(int x){
    access(x);
    while(tr[x].s[0]){
        pushdown(x);
        x=tr[x].s[0];
    }
    splay(x);
    return x;
}

void split(int x,int y){
    makeroot(x);
    access(y);
}

void link(int x,int y){
    makeroot(x);
    if(findroot(y)!=x){
        tr[x].p=y;
    }
}

void cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&tr[y].p==x&&!tr[y].s[0]){
        tr[x].s[1]=tr[y].p=0;
        pushup(x);
    }
}
