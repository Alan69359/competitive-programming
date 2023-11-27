#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int a[N],b[N];

void mergeSort(int s[],int l,int r){
	if(l==r)return;
	int m=l+(r-l)/2;
	mergeSort(s,l,m);
	mergeSort(s,m+1,r);
	int k=0,i=l,j=m+1;
	while(i<=m&&j<=r){
		if(s[i]<=s[j])b[k++]=s[i++];
		else b[k++]=s[j++];
	}
    while(i<=m){
        b[k++]=s[i++];
    }
    while(j<=r){
        b[k++]=s[j++];
    }
    for(int i=l,j=0;i<=r;i++,j++){
        s[i]=b[j];
    }
}

int main(){
    scanf("%d",n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    mergeSort(a,0,n-1);
}
