#include<bits/stdc++.h>

using namespace std;

const int N=10010,S=55,M=1e6+10;

int n;
int tr[N*S][26],cnt[N*S],idx;
int q[N*S],fail[N*S];

void insert(char *s){
    int p=0;
    for(int i=0;s[i];i++){
        int c=s[i]-'a';
        if(!tr[p][c])tr[p][c]=++idx;
        p=tr[p][c];
    }
    cnt[p]++;
}

void build(){
    int qh=0,qt=-1;
    for(int i=0;i<26;i++){
        if(tr[0][i])q[++qt]=tr[0][i];
    }
    while(qh<=qt){
        int t=q[qh++];
        for(int i=0;i<26;i++){
            if(tr[t][i]){
                fail[tr[t][i]]=tr[fail[t]][i];
                q[++qt]=tr[t][i];
            }
            else {
                tr[t][i]=tr[fail[t]][i];
            }
        }
    }
}

int query(char *s){
    int p=0;
    int res=0;
    for(int i=0;s[i];i++){
        int c=s[i]-'a';
        p=tr[p][c];
        for(int j=p;j&&cnt[j]!=-1;j=fail[j]){
            res+=cnt[j];
            cnt[j]=-1;
        }
    }
    return res;
}

int main(){
    char s[M];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",s);
		insert(s);
	}
	build();
	scanf("%s",s);
	printf("%d\n",query(s));
}