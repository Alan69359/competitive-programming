#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-9;

int n,m;
//string s1,s2;
char s1[N],s2[N];
vector<int>v1,v2,v3;
bool fl=false;
int n1,n2;

void scan(string s,vector<int>&v){
	for(int i=s.length()-1;i>=0;i--){
		v.push_back(s[i]-'0');
	}
}

bool cmp(vector<int>&a,vector<int>&b){
	if(a.size()!=b.size()){
		return a.size()>b.size();
	}
	for(int i=a.size()-1;i>=0;i--){
		if(a[i]!=b[i])return a[i]>b[i];
	}
	return true;
}

vector<int>add(vector<int>&a,vector<int>&b){
	vector<int>c;
	int s=0;
	for(int i=0;i<a.size()||i<b.size();i++){
		if(i<a.size())s+=v1[i];
		if(i<b.size())s+=v2[i];
		c.push_back(s%10);
		s/=10;
	}
	if(s)c.push_back(1);
	return c;
}

vector<int>subtract(vector<int>&a,vector<int>&b){
	if(!cmp(a,b)){
		a.swap(b);
		fl=true;
	}
	vector<int>c;
	int comp=0;
	for(int i=0;i<a.size();i++){
		comp=a[i]-comp;
		if(i<b.size())comp-=b[i];
		c.push_back((comp+10)%10);
		comp=(comp<0?1:0);
	}
	while(c.size()>1&&c.back()==0)c.pop_back();
	return c;
}

vector<int>multiple(vector<int>&a,int b){
	vector<int>c;
	int comp=0;
	for(int i=0;i<a.size()||comp;i++){
		if(i<a.size())comp+=a[i]*b;
		c.push_back(comp%10);
		comp/=10;
	}
	while(c.size()>1&&c.back()==0)c.pop_back();
	return c;
}

vector<int>divide(vector<int>&a,int b,int &r){
	vector<int>c;
	r=0;
	for(int i=a.size()-1;i>=0;i--){
		r=r*10+a[i];
		c.push_back(r/b);
		r%=b;
	}
	reverse(c.begin(),c.end());
	while(c.size()>1&&c.back()==0)c.pop_back();
	return c;
}

int main(){
	scanf("%s%d",s1,&n1);
	scan(s1,v1);
	int r;
	v3=divide(v1,n1,r);
	for(int i=v3.size()-1;i>=0;i--){
		printf("%d",v3[i]);
	}
	printf("\n%d",r);
}
