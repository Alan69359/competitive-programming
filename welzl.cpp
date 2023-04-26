#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;
typedef pair<double,double>pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;
const double PI=acos(-1);

int n,m;

int dcmp(double x,double y){
	if(fabs(x-y)<EPS)return 0;
	else if(x<y)return -1;
	else return 1;
}

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
	bool operator == (Point b){
		return (!dcmp(x,b.x)&&!dcmp(y,b.y));
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

struct Circle{
	Point p;
	double r;
};

Point operator + (Point p,Vector v){
	return {p.x+v.i,p.y+v.j};
}

double cross(Vector a,Vector b){
	return a.i*b.j-b.i*a.j;
}

Vector getvector(Point p){
	return {p.x,p.y}; 
}

Point rotate(Vector a,double b){
	return {a.i*cos(b)+a.j*sin(b),-a.i*sin(b)+a.j*cos(b)};
}

double getdistance3(Point a,Point b){
	double dx=a.x-b.x;
	double dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

Point getintersection(Point p,Vector v,Point q,Vector w){
	/* intersection of two vector */
	Vector u=getvector(p)-getvector(q);
	double t=cross(w,u)/cross(v,w);
	return p+v*t;
}

pair<Point,Point> getnorm(Point a,Point b){
	Point m={(a.x+b.x)/2,(a.y+b.y)/2};
	return {m,rotate(getvector(b-a),PI/2)};
}

Circle getcircle(Point a,Point b,Point c){
	auto u=getnorm(a,b),v=getnorm(a,c);
	Point p=getintersection(u.first,getvector(u.second),v.first,getvector(v.second));
	return {p,getdistance3(p,a)};
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&po[i].x,&po[i].y);
	}
	random_shuffle(po,po+n);
	Circle c({po[0],0});
	for(int i=1;i<n;i++){
		if(dcmp(c.r,getdistance3(c.p,po[i]))<0){
			c={po[i],0};
			for(int j=0;j<i;j++){
				if(dcmp(c.r,getdistance3(c.p,po[j]))<0){
					c={(po[i]+po[j])/2,getdistance3(po[i],po[j])/2};
					for(int k=0;k<j;k++){
						if(dcmp(c.r,getdistance3(c.p,po[k]))<0){
							c=getcircle(po[i],po[j],po[k]);
						}
					}
				}
			}
		}
	}
	printf("%.10lf\n",c.r);
	printf("%.10lf %.10lf",c.p.x,c.p.y);
}
