#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;
int a[N];

void quickSort(int a[],int l,int r) {
	if(l==r)return;
    int i=l-1,j=r+1,x=a[l+(r-l)/2];
    while(i<j){
        do{
            i++;
        }while(a[i]<x);
        do{
            j--;
        }while(a[j]>x);
        if(i<j)swap(a[i],a[j]);
    }
    quickSort(a,l,j);
    quickSort(a,j+1,r);
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        quickSort(a,0,n-1);
    }
}

