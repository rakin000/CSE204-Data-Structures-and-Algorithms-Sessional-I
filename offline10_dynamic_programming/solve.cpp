#include <iostream>
using namespace std;

const int N = 100 + 6;
const int S = 1e4 + 10;
const int64_t mod = 1e9 + 7;
int64_t dp[N][S];
int64_t csum[S];

int main(){
    int n;
    cin>>n;
    int s;
    cin>>s; 
    int f[n];
    for(int i=0;i<n;i++) cin>>f[i];

    for(int i=0;i<=s;i++)
        dp[0][i] = 0;
    for(int i=1;i<=min(f[0],s);i++)
        dp[0][i] = 1;
    csum[0] = 0;
    for(int i=1;i<=s;i++)
        csum[i] = (csum[i-1] + dp[0][i])%mod ;

    for(int i=1;i<n;i++){
        for(int j=s;j>=0;j--){
            dp[i][j] = (csum[ max(j-1,0) ] - csum[ max(j-f[i]-1,0) ] + mod ) %mod;
        }
        csum[0] = dp[i][0];
        for(int j=1;j<=s;j++)
            csum[j] = (csum[j-1] + dp[i][j])%mod ;
    }
    cout<<dp[n-1][s]<<endl;
}