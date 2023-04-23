#include<bits/stdc++.h>

using namespace std;

const int N=2000,M=2010;

int n,x,y;
struct Node{
    char s[N+1];
    int cnt,l,r;
}se[M];

char str[2000010];
int bin[M],qt;

void move(int k){
    x=se[0].r;
    while(k>se[x].cnt){
        k-=se[x].cnt;
        x=se[x].r;
    }
    y=k-1;
}

void add(int x,int u){
    se[u].r=se[x].r;
    se[se[u].r].l=u;
    se[x].r=u;
    se[u].l=x;
}

void rem(int u){
    se[se[u].r].l=se[u].l;
    se[se[u].l].r=se[u].r;
    se[u].l=se[u].r=se[u].cnt=0;
    bin[++qt]=u;
}

void inser(int k){
    if(y<se[x].cnt-1){
        int u=bin[qt--];
        for(int i=y+1;i<se[x].cnt;i++){
            se[u].s[se[u].cnt++]=se[x].s[i];
        }
        se[x].cnt=y+1;
        add(x,u);
    }
    int i=x;
    for(int j=0;j<k;){
        int u=bin[qt--];
        while(se[u].cnt<N&&j<k){
            se[u].s[se[u].cnt++]=str[j++];
        }
        add(i,u);
        i=u;
    }
}

void delet(int k){
    if(se[x].cnt-1-y>=k){
        for(int i=y+k+1,j=y+1;i<se[x].cnt;i++,j++){
            se[x].s[j]=se[x].s[i];
        }
        se[x].cnt-=k;
    }
    else {
        k-=se[x].cnt-y-1;
        se[x].cnt=y+1;
        while(se[x].r&&k>=se[se[x].r].cnt){
            int u=se[x].r;
            k-=se[u].cnt;
            rem(u);
        }
        int u=se[x].r;
        for(int i=0,j=k;j<se[u].cnt;i++,j++){
            se[u].s[i]=se[u].s[j];
        }
        se[u].cnt-=k;
    }
}

void get(int k){
    if(se[x].cnt-1-y>=k){
        for(int i=0,j=y+1;i<k;i++,j++){
            printf("%c",se[x].s[j]);
        }
    }
    else {
        k-=se[x].cnt-y-1;
        for(int i=y+1;i<se[x].cnt;i++){
            printf("%c",se[x].s[i]);
        }
        int i=x;
        while(se[i].r&&k>=se[se[i].r].cnt){
            int u=se[i].r;
            for(int i=0;i<se[u].cnt;i++){
                printf("%c",se[u].s[i]);
            }
            k-=se[u].cnt;
            i=u;
        }
        int u=se[i].r;
        for(int i=0;i<k;i++){
            printf("%c",se[u].s[i]);
        }
    }
    printf("\n");
}

void merge(){
    for(int i=se[0].r;i;i=se[i].r){
        while(se[i].r&&se[i].cnt+se[se[i].r].cnt<N){
            int r=se[i].r;
            for(int j=se[i].cnt,k=0;k<se[r].cnt;j++,k++){
                se[i].s[j]=se[r].s[k];
            }
            if(x==r){
                x=i;
                y+=se[i].cnt;
            }
            se[i].cnt+=se[r].cnt;
            rem(r);
        }
    }
}

int main(){
    for(int i=1;i<M;i++){
        bin[++qt]=i;
    }
    scanf("%d",&n);
    char op[10];
    str[0]='#';
    inser(1);
    move(1);
    while(n--){
        int a;
        scanf("%s",op);
        if(!strcmp(op,"Move")){
            scanf("%d",&a);
            move(a+1);
        }
        else if(!strcmp(op,"Insert")){
            scanf("%d",&a);
            int i=0,k=a;
            while(a){
                scanf("%c",&str[i]);
                if(str[i]>=32&&str[i]<=126){
                    i++,a--;
                }
            }
            inser(k);
            merge();
        }
        else if(!strcmp(op,"Delete")){
            scanf("%d",&a);
            delet(a);
            merge();
        }
        else{
            scanf("%d",&a);
            get(a);
        }
    }
}
