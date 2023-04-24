#define _CRT_SECURE_NO_WARNINGS

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;

int n,m;

int abs1(int x){
    return (x^(x>>31))-(n>>31);
}

int max1(int a,int b){
    return (b&((a-b)>>31))|(a&(~(a-b)>>31));
}

int min1(int a,int b){
    return (a&((a-b)>>31))|(b&(~(a-b)>>31));
}

bool isequal(int a,int b){
    return (a^b)>=0;
}

int getbit(int a,int b){
    return (a>>b)&1;
}

int unsetbit(int a,int b){
    return a&~(1<<b);
}

int setbit(int a,int b){
    return a|(1<<b);
}

int flapbit(int a,int b){
    return a^(1<<b);
}

int main(){
    return 0;
}
