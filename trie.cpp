#include<bits/stdc++.h>

using namespace std;

const int N=100001;

int n;
int so[N][26],cnt[N],idx;
char str[N];

void insert(char *str){
	int p=0;
	for(int i=0;str[i];i++){
		int c=str[i]-'a';
		if(!so[p][c])so[p][c]=++idx;
		p=so[p][c];
	}
	cnt[p]++;
}

int query(char *str){
	int p=0;
	for(int i=0;str[i];i++){
		int c=str[i]-'a';
		if(!so[p][c])return 0;
		else p=so[p][c];
	}
	return cnt[p];
}

int main(){
	scanf("%d",&n);
	while(n--){
		char op[2];
		scanf("%s%s",op,str);
		if(op[0]=='I')insert(str);
		else printf("%d\n",query(str));
	}
	return 0;
}
