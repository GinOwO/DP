#include<vector>
#include<utility>
#include<iostream>

using namespace std;

// Traveller can only move down or right
// Traveller(m-1, n) + traveller(m, n-1), base case traveller(1,1) = 1, (0,x) = (x,0) = 0, (m,n) = (n,m)
// Time: O(mn), Space: O(m+n)
// dp[m][n] = dp[m-1][n] + dp[m][n-1]
// dp[1][1] = 1
// dp[0][x] = dp[x][0] = 0
// dp[m] = dp[m-1] + dp[m]

typedef vector<unsigned long long> VI;

unsigned long long traveller(int&& m, int&& n, VI& memo){
    for(int i=1; i<=min(m,n); i++){
        for(int j=1; j<=max(m,n); j++){
            if(i==1 && j==1) memo[j] = 1;
            else memo[j] += memo[j-1];
        }
    }
    return memo[max(m,n)];
}

int main(){
    VI memo(20,0);
    cout << traveller(18,18, memo) << endl;
    
}