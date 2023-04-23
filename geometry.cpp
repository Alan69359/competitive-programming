#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<double,double>pdd;
typedef pair<int,int>pii;

const int N=1e4+10,M=1e5+10;
const double EPS=1e-8;
const double PI=acos(-1);

vector<int>xxx;
int n,m;
int q[N];
int s[N],top;
int i1,i2;
bool st2[N][N];
pii y[N];

int sign(double x){
	if(fabs(x)<EPS)return 0;
	else if(x<0)return -1;
	else return 1;
}

int dcmp(double x,double y){
	if(fabs(x-y)<EPS)return 0;
	else if(x<y)return -1;
	else return 1;
}

double randEPS(){
	return ((double)rand()/RAND_MAX-0.5)*EPS;
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

struct Vector3{
	double x,y,z;
	void shake(){
		x+=randEPS(),y+=randEPS(),z+=randEPS();
	}
	Vector3 operator + (Vector3 q){
		return {x+q.x,y+q.y,z+q.z};
	}
	Vector3 operator - (Vector3 q){
		return {x-q.x,y-q.y,z-q.z};
	}
}ve3[N];

struct Plane{
	int v[3];
}pl[N],npl[N];

struct Segment{
	Point a,b;
	Segment(Point a1=0,Point b1=0){
		a=a1,b=b1;
	}
}se[N];

struct Circle{
	Point c;
	double r;
	Circle(){
		c={0,0},r=0;
	}
	Circle(double r1){
		c={0,0};
		r=r1;
	}
	Circle(Point c1,double r1){
		c=c1,r=r1;
	}
}ci[N];

struct Rectangle{
	Point lu,rd;
	Rectangle(Point p1={0,0},Point p2={0,0}){
		lu=p1,rd=p2;
	}
}re[N];

void print(Segment s){
	printf("(%lf,%lf)->(%lf,%lf)\n",s.a.x,s.a.y,s.b.x,s.b.y);
}
void print(Point p){
	printf("(%lf,%lf)\n",p.x,p.y);
}
void print(Vector3 v){
	printf("(%lf,%lf,%lf)",v.x,v.y,v.z);
}
void print(Plane p){
	printf("(%lf,%lf,%lf)\n",ve3[p.v[0]].x,ve3[p.v[0]].y,ve3[p.v[0]].z);
	printf("(%lf,%lf,%lf)\n",ve3[p.v[1]].x,ve3[p.v[1]].y,ve3[p.v[1]].z);
	printf("(%lf,%lf,%lf)\n",ve3[p.v[2]].x,ve3[p.v[2]].y,ve3[p.v[2]].z);
}

Point operator + (Point p,Vector v){
	return {p.x+v.i,p.y+v.j};
}

double dot(Vector a,Vector b){
	return a.i*b.i+a.j*b.j;
}
double dot(Vector3 a,Vector3 b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

double cross(Vector a,Vector b){
	return a.i*b.j-b.i*a.j;
}
Vector3 cross(Vector3 a,Vector3 b){
	return {a.y*b.z-b.y*a.z,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
}

double getlength(Vector a){
	/* printf("(%lf,%lf) %lf\n",a.i,a.j,sqrt(dot(a,a))); */
	return sqrt(dot(a,a));
}
double getlength(Vector3 a){
	return sqrt(dot(a,a));
}

Vector getvector(Point p){
	return {p.x,p.y}; 
}
Vector getvector(Vector v){
	return v/getlength(v);
}
Vector getvector(Segment s){
	return {s.b.x-s.a.x,s.b.y-s.a.y};
}

double getangle(Vector a,Vector b){
	return acos(dot(a,b)/getlength(a)/getlength(b));
}
double getangle(Segment s){
	return atan2(s.b.y-s.a.y,s.b.x-s.a.x);
}

Point rotate(Vector a,double b){
	return {a.i*cos(b)+a.j*sin(b),-a.i*sin(b)+a.j*cos(b)};
}

pair<Point,Point> getnormal(Point a,Point b){
	Point m={(a.x+b.x)/2,(a.y+b.y)/2};
	return {m,rotate(getvector(b-a),PI/2)};
}
Vector3 getnormal(Plane p){
	return cross((ve3[p.v[1]]-ve3[p.v[0]]),ve3[p.v[2]]-ve3[p.v[0]]);
}

double getdistance1(Point p,Segment s){
	/* distance between Point and line */
	Vector v1=getvector(s),v2=getvector(p)-getvector(s.a);
	return fabs(cross(v1,v2)/getlength(v1));
}

double getdistance2(Point p,Segment s){
	/* distance between point and segment */
	if(s.a==s.b)return getlength(getvector(p)-getvector(s.a));
	Vector v1=getvector(s.b)-getvector(s.a);
	Vector v2=getvector(p)-getvector(s.a);
	Vector v3=getvector(p)-getvector(s.b);
	if(sign(dot(v1,v2))<0){
		return getlength(v2);
	}
	else if(sign(dot(v1,v3))>0){
		return getlength(v3);
	}
	else return getdistance1(p,s);
}

bool isonsegment(Point p,Point a,Point b){
	return !sign(cross(getvector(p-a),getvector(p-b)))&&sign(dot(getvector(p-a),getvector(p-b)))<=0;
}

Point getintersection(Point a,Vector va,Point b,Vector vb);
double getdistance3(Point a,Point b){
	return getlength(getvector(b)-getvector(a));
}

double getdistance(Circle c,Point p,Point q){
	Point i=getintersection(p,getvector(q)-getvector(p),ci[0].c,getvector(rotate((getvector(q)-getvector(p)),PI/2)));
	double d=getdistance3(c.c,i);
	if(!isonsegment(i,p,q)){
		d=min(getdistance3(c.c,p),getdistance3(c.c,q));
	}
	return d;
}

Point getintersection(Point a,Vector va,Point b,Vector vb){
	/* intersection point of two vector */
	Vector ba=getvector(a)-getvector(b);
	double k=cross(vb,ba)/cross(va,vb);
	return a+va*k;
}
Point getintersection(Segment s,Segment t){
	/* intersection of two segment */
	return getintersection(s.a,getvector(s.b)-getvector(s.a),t.a,getvector(t.b)-getvector(t.a));
}
pair<Point,Point> getintersection(Circle c,Point p,Point q){
	Vector pq=getvector(q)-getvector(p);
	Point in=getintersection(p,pq,ci[0].c,getvector(rotate(pq,PI/2)));
	Point pc,qc;
	double d=getdistance3(c.c,in);
	if(dcmp(ci[0].r,d)>0){
		double l=sqrt(ci[0].r*ci[0].r-getdistance3(ci[0].c,in)*getdistance3(ci[0].c,in));
		pc=in+getvector(pq*-1)*l;
		qc=in+getvector(pq)*l;
	}
	return{pc,qc};
}

double getarea(Point a,Point b,Point c){
	return cross(getvector(b-a),getvector(c-a));
}
double getarea(Plane p){
	Vector3 normal=getnormal(p);
	return getlength(normal)/2;
}
double getarea(Circle c,Point p,Point q){
	//	area of a sector
	Vector pv=getvector(p),qv=getvector(q);
	double theta=acos(dot(pv,qv)/getlength(pv)/getlength(qv));
	if(sign(cross(pv,qv))<0)theta=-theta;
	return ci[0].r*ci[0].r*theta/2;
}
double getintersectionarea(Circle c,Point p,Point q){
	Vector pv=getvector(p),qv=getvector(q);
	double pr=getdistance3(c.c,p),qr=getdistance3(c.c,q);
	if(dcmp(c.r,pr)>=0&&dcmp(c.r,qr)>=0){
		return cross(pv,qv)/2;
	}
	else if(!sign(cross(pv,qv))){
		return 0;
	}
	pair<Point,Point>i=getintersection(c,p,q);
	double d=getdistance(c,p,q);
	if(dcmp(c.r,d)<=0){
		return getarea(c,p,q);
	}
	else if(dcmp(c.r,pr)>=0){
		return cross(pv,getvector(i.second))/2+getarea(c,i.second,q);
	}
	else if(dcmp(c.r,qr)>=0){
		return getarea(c,p,i.first)+cross(getvector(i.first),qv)/2;
	}
	else{
		return getarea(c,p,i.first)+cross(getvector(i.first),getvector(i.second))/2+getarea(c,i.second,q);
	}
}

Point getprojection(Point p,Segment s){
	Vector v=getvector(s);
	return s.a+v*(dot(v,getvector(p)-getvector(s.a))/dot(v,v));
}
double getprojection(Point a,Point b,Point c){
	Vector ac=getvector(c)-getvector(a),ab=getvector(b)-getvector(a);
	return dot(ac,ab/getlength(ab));
}

Circle getcircle(Point a,Point b,Point c){
	auto u=getnormal(a,b),v=getnormal(a,c);
	Point p=getintersection(u.first,getvector(u.second),v.first,getvector(v.second));
	return {p,getdistance3(p,a)};
}

bool cmp1(Segment s1,Segment s2){
	double a1=getangle(s1),a2=getangle(s2);
	if(!dcmp(a1,a2)){
		return getarea(s1.a,s1.b,s2.b)<0;
	}
	else return a1<a2;
}

bool isonright(Segment s,Segment t,Segment u){
	Point p=getintersection(t,u);
	return sign(getarea(s.a,s.b,p))<=0;
}

Point po2[N];

double f1(){
	//	return half-plane intersection
	sort(se,se+i2,cmp1);
	int qh=0,qt=-1;
	for(int i=0;i<i2;i++){
		if(i&&!dcmp(getangle(se[i]),getangle(se[i-1])))continue;
		while(qh+1<=qt&&isonright(se[i],se[q[qt-1]],se[q[qt]]))qt--;
		while(qh+1<=qt&&isonright(se[i],se[q[qh]],se[q[qh+1]]))qh++;
		q[++qt]=i;
	}
	while(qh+1<=qt&&isonright(se[q[qh]],se[q[qt-1]],se[q[qt]]))qt--;
	while(qh+1<=qt&&isonright(se[q[qt]],se[q[qh]],se[q[qh+1]]))qt--;
	q[++qt]=q[qh];
	int k=0;
	for(int i=qh;i<qt;i++){
		po2[k++]=getintersection(se[q[i]],se[q[i+1]]);
	}
	double ans=0;
	for(int i=1;i+1<k;i++){
		ans+=getarea(po2[0],po2[i],po2[i+1]);
	}
	return ans/2;
}

bool isabove(Plane p,Vector3 v){
	return dot((v-ve3[p.v[0]]),getnormal(p))>=0;
}

void getconvex3(){
	pl[m++]={0,1,2};
	pl[m++]={2,1,0};
	for(int i=3;i<n;i++){
		int cnt=0;
		for(int j=0;j<m;j++){
			bool up=isabove(pl[j],ve3[i]);
			if(!up)npl[cnt++]=pl[j];
			for(int k=0;k<3;k++){
				st2[pl[j].v[k]][pl[j].v[(k+1)%3]]=up;
			}
		}
		for(int j=0;j<m;j++){
			for(int k=0;k<3;k++){
				int a=pl[j].v[k],b=pl[j].v[(k+1)%3];
				if(st2[a][b]&&!st2[b][a]){
					npl[cnt++]={a,b,i};
				}
			}
		}
		m=cnt;
		for(int j=0;j<m;j++){
			pl[j]=npl[j];
		}
	}
}

bool cmp2(Point a,Point b){
	if(a.x!=b.x)return a.x<b.x;
	else return a.y<=b.y;
}

double rotatingcalipers(){
	if(top<=2)return getdistance3(po[0],po[n-1]);
	double ans=0;
	for(int i=0,j=2;i<top;i++){
		Point a=po[s[i]],b=po[s[i+1]];
		while(getarea(a,b,po[s[j]])<getarea(a,b,po[s[j+1]])){
			j=(j+1)%top;
		}
		ans=max(ans,max(getdistance3(a,po[s[j]]),getdistance3(b,po[s[j]])));
	}
	return ans;
}

bool st[N];

void andrew(){
	sort(po,po+n,cmp2);
	top=0;
	for(int i=0;i<n;i++) {
		while(top>=2&&getarea(po[s[top-1]],po[s[top]],po[i])<=0){
			if(getarea(po[s[top-1]],po[s[top]],po[i])<0){
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
		while(top>=2&&getarea(po[s[top-1]],po[s[top]],po[i])<=0){
			top--;
		}
		s[++top]=i;
	}
	top--;
}

void delaunaytriangulation(){
	scanf("%lf%d",&ci[0].r,&n);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&po[i].x,&po[i].y);
	}
	double ans=0;
	for(int i=0;i<n;i++){
		ans+=getintersectionarea(ci[0],po[i],po[(i+1)%n]);
	}
	printf("%.2lf\n",fabs(ans));
}

ll line(ll x1,ll x2){
	int cnt=0;
	for(int i=0;i<n;i++){
		if(re[i].lu.x<=x1&&re[i].rd.x>=x2){
			y[cnt++]={re[i].lu.y,re[i].rd.y};
		}
	}
	if(!cnt)return 0;
	sort(y,y+cnt);
	/* for(int i=0;i<cnt;i++){ */
	/* 	printf("%d %d\n",y[i].first,y[i].second); */
	/* } */
	ll res=0;
	int st=y[0].first,en=y[0].second;
	for(int i=1;i<cnt;i++){
		if(y[i].first<=en){
			en=max(en,y[i].second);
		}
		else {
			res+=en-st;
			st=y[i].first,en=y[i].second;
		}
	}
	res+=en-st;
	return res*(x2-x1);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf%lf",&re[i].lu.x,&re[i].lu.y,&re[i].rd.x,&re[i].rd.y);
		xxx.push_back(re[i].lu.x),xxx.push_back(re[i].rd.x);
	}
	sort(xxx.begin(),xxx.end());
	ll ans=0;
	for(int i=0;i+1<xxx.size();i++){
		if(xxx[i]!=xxx[i+1]){
			ans+=line(xxx[i],xxx[i+1]);
			/* printf("%d\n",line(xxx[i],xxx[i+1])); */
		}
	}
	printf("%lld",ans);
}
