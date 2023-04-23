#include<bits/stdc++.h>

using namespace std;

const int N=300001,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;
const double EPS=1e-8;
const double PI=acos(-1);

int n,m;
int arr[N];
ll a[N],b[N];

struct Complex{
	double x,y;
	Complex operator + (const Complex &b)const{
		return {x+b.x,y+b.y};
	}
	Complex operator - (const Complex &b)const{
		return {x-b.x,y-b.y};
	}Complex operator * (const Complex &b)const{
		return {x*b.x-y*b.y,x*b.y+y*b.x};
	}
}a[N],b[N];

int rev[N],maxb,len;

void fft(Complex a[],int inv){
	for(int i=0;i<len;i++){
		if(i<rev[i]){
			swap(a[i],a[rev[i]]);
		}
	}
	for(int mid=1;mid<len;mid<<=1){
		auto w1=Complex({cos(PI/mid),inv*sin(PI/mid)});
		for(int i=0;i<len;i+=mid*2){
			auto wnk=Complex({1,0});
			for(int j=0;j<mid;j++,wnk=wnk*w1){
				auto x=a[i+j],y=wnk*a[i+j+mid];
				a[i+j]=x+y,a[i+j+mid]=x-y;
			}
		}
	}
}

void fft1(Complex a[],int n,int op){
    for(int i=0;i<n;i++){
        ai[i]=ai[i/2]/2+((i&1)?n/2:0);
    }
    for(int i=0;i<n;i++){
        if(i<ai[i]){
            swap(a[i],a[ai[i]]);
        }
    }
    for(int i=2;i<=n;i<<=1){
        Complex w1({cos(2*PI/i),sin(2*PI/i)*op});
        for(int j=0;j<n;j+=i){
            Complex wk({1,0});
            for(int k=j;k<j+i/2;k++){
                Complex x=a[k];
                Complex y=a[k+i/2]*wk;
                a[k]=x+y;
                a[k+i/2]=x-y;
                wk=wk*w1;
            }
        }
    }
}

void fft2(Complex a[],int n,int op){
    if(n==1)return;
    Complex a1[n/2],a2[n/2];
    for(int i=0;i<n/2;i++){
        a1[i]=a[i*2];
        a2[i]=a[i*2+1];
    }
    fft2(a1,n/2,op),fft2(a2,n/2,op);
    Complex w1({cos(2*PI/n),sin(2*PI/n)*op});
    Complex wk({1,0});
    for(int i=0;i<n/2;i++){
        a[i]=a1[i]+a2[i]*wk;
        a[i+n/2]=a1[i]-a2[i]*wk;
        wk=wk*w1;
    }
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++){
		scanf("%lf",&a[i].x);
	}
	for(int i=0;i<=m;i++){
		scanf("%lf",&b[i].x);
	}
	while((1<<maxb)<n+m+1){
		maxb++;
	}
	len=1<<maxb;
	for(int i=0;i<len;i++){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(maxb-1));
	}
	fft(a,1),fft(b,1);
	for(int i=0;i<len;i++){
		a[i]=a[i]*b[i];
	}
	fft(a,-1);
	for(int i=0;i<=n+m;i++){
		printf("%d ",(int)(a[i].x/len+0.5));
	}
	return 0;
}
