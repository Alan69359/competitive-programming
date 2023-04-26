#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;
typedef pair<double,double>pdd;

const int N=101,M=101,INF=0x3f3f3f3f;
const double EPS=1e-6;

int n;
double a1[N][N];
int a2[N][N];

int gaussian1(){
    int r,c;
    for(c=0,r=0;c<n;c++){
        int tr=r;
        for(int i=r+1;i<n;i++){
            if(fabs(a1[i][c])>fabs(a1[tr][c]))tr=i;
        }
        if(fabs(a1[tr][c])<EPS)continue;
        for(int i=c;i<=n;i++){
            swap(a1[tr][i],a1[r][i]);
        }
        for(int i=n;i>=c;i--){
            a1[r][i]/=a1[r][c];			        
        }
        for(int i=r+1;i<n;i++){
            if(fabs(a1[i][c])>EPS){
                for(int j=n;j>=c;j--){
                    a1[i][j]-=a1[r][j]*a1[i][c];
                }
            }
        }
        r++;
    }
    if(r<n){
        for(int i=r;i<n;i++){
            if(fabs(a1[i][n])>EPS)return 0;
        }
        return 2;
    }
    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<n;j++){
            a1[i][n]-=a1[i][j]*a1[j][n];
        }
    }
    return 1;
}

int gaussian2(){
    int r,c;
    for(c=0,r=0;c<n;c++){
        int tr=r;
        for(int i=r+1;i<n;i++){
            if(a2[i][c]>a2[tr][c])tr=i;
        }
        if(!a2[tr][c])continue;
        for(int i=c;i<=n;i++){
            swap(a2[tr][i],a2[r][i]);
        }
        for(int i=r+1;i<n;i++){
            if(a2[i][c]){
                for(int j=n;j>=c;j--){
                    a2[i][j]^=a2[r][j];
                }
            }
        }
        r++;
    }
    if(r<n){
        for(int i=r;i<n;i++){
            if(a2[i][n])return 0;
        }
        return 2;
    }
    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<n;j++){
            a2[i][n]^=a2[i][j]&a2[j][n];
        }
    }
    return 1;
}

int f1(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++) {
            scanf("%lf",&a1[i][j]);
        }
    }
    int ans=gaussian1();
    if(ans==1){
        for(int i=0;i<n;i++){
            if(fabs(a1[i][n])==0)a1[i][n]=0;
            printf("%.2lf\n",a1[i][n]);
        }
    }
    else if(ans==2)printf("Infinite group solutions\n");
    else printf("No solution\n");
}

int f2(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++) {
            scanf("%d",&a2[i][j]);
        }
    }
    int ans=gaussian2();
    if(ans==1){
        for(int i=0;i<n;i++){
            printf("%d\n",a2[i][n]);
        }
    }
    else if(ans==2)printf("Multiple sets of solutions\n");
    else printf("No solution\n");
}

int main(){
    f2();
    return 0;
}
