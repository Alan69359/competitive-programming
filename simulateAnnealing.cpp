#include<bits/stdc++.h>

using namespace std;

typedef pair<double,double>pdd;

const int N = 101;

int n;
pdd p[N];
double ans=1e8;

double rand(double l,double r){
	return (double)rand()/RAND_MAX*(r-l)+l;	
}

double getDist(pdd a,pdd b){
	double dx=a.first-b.first;
	double dy=a.second-b.second;
	return sqrt(dx*dx+dy*dy);
}

double sum(pdd randp){
	double res=0;
	for(int i=0;i<n;i++){
		res+=getDist(randp,p[i]);
	}
	ans=min(ans,res);
	return res;
}

void simulate_anneal(){
	pdd curp(rand(0,10000),rand(0,10000));
	for(double t=1e4;t>1e-4;t*=0.99){
		pdd newp(rand(curp.first-t,curp.first+t),rand(curp.second-t,curp.second=t));
		double delta=sum(newp)-sum(curp);
		if(exp(-delta/t)>rand(0,1)){
			curp=newp;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&p[i].first,&p[i].second);
	}
	for(int i=0;i<100;i++){
		simulate_anneal();
	}
	printf("%lf\n",ans);
	return 0;
}
