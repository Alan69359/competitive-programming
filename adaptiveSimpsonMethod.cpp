#include<bits/stdc++.h>

using namespace std;

const double EPS=1e-12;

double f(double x){
	return x;
}

double simpson(double l,double r){
	double mid=l+(r-l)/2;
	return (r-l)*(f(l)+4*f(mid)+f(r))/6;
}

double asr(double l,double r,double s){
	double mid=l+(r-l)/2;
	double left=simpson(l,mid),right=simpson(mid,r);
	if(fabs(left+right-s)<EPS)return left+right;
	else return asr(l,mid,left)+asr(mid,r,right);
}

int main(){
	double l,r;
	scanf("%lf%lf",&l,&r);
	printf("%lf\n",asr(l,r,simpson(l,r)));
	return 0;
}
