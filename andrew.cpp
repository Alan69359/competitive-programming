#include<bits/stdc++.h>

using namespace std;

typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10;
const double EPS=1e-8;

int n;

struct Point{
	double x,y;
	Point(double x1=0,double y1=0){
		x=x1,y=y1;
	}
	Point operator + (Point b){
		return {x+b.x,y+b.y};
	}
	Point operator - (Point b){
		return {x-b.x,y-b.y};
	}
	Point operator * (double b){
		return {x*b,y*b};
	}
	Point operator / (double b){
		return {x/b,y/b};
	}
}po[N];

struct Vector{
	double i,j;
	Vector(double i1=0,double j1=0){
		i=i1,j=j1;
	}
	Vector operator + (Vector b){
		return {i+b.i,j+b.j};
	}
	Vector operator - (Vector b){
		return {i-b.i,j-b.j};
	}
	Vector operator * (double b){
		return {i*b,j*b};
	}
	Vector operator / (double b){
		return {i/b,j/b};
	}	
}ve[N];

int s[N];
bool st[N];

double cross(Vector a,Vector b){
	return a.i*b.j-b.i*a.j;
}

Vector getvector(Point p){
	return {p.x,p.y}; 
}

double getarea(Vector a,Vector b,Vector c){
	return cross(b-a,c-a);
}

double getdistance3(Point a,Point b){
	double dx=a.x-b.x;
	double dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

bool cmp(Point a,Point b){
	if(a.x!=b.x)return a.x<b.x;
	else return a.y<=b.y;
}

double andrew(){
	sort(po,po+n,cmp);
	int top=0;
	for(int i=0;i<n;i++) {
		while(top>=2&&
			getarea(getvector(po[s[top-1]]),getvector(po[s[top]]),getvector(po[i]))<=0){
			if(getarea(getvector(po[s[top-1]]),getvector(po[s[top]]),getvector(po[i]))<0){
				st[s[top--]]=false;
			}
			else top--;
		}
		s[++top]=i;
		st[i]=true;
	}
	st[0]=false;
	for(int i=n-1;i>=0;i--){
		if(st[i])continue;
		while(top>=2&&getarea(getvector(po[s[top-1]]),getvector(po[s[top]]),getvector(po[i]))<=0)top--;
		s[++top]=i;
	}
	double res=0;
	for(int i=2;i<=top;i++){
		res+=getdistance3(po[s[i-1]],po[s[i]]);
	}
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&po[i].x,&po[i].y);
	}
	double res=andrew();
	printf("%.2lf",res);
	return 0;
}
