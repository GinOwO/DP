
#include <bits/stdc++.h>

using namespace std;

int minCostClimbingStairs(vector<int>& cost) {
    int n=cost.size();
    vector<int> dp(n+2,0);
    for(int i=n-1; i>=0; i--){
        dp[i]=min(dp[i+1], dp[i+2])+cost[i];
    }
    return min(dp[0], dp[1]);
}

int main(){
    vector<vector<int>> arr = {
        {10, 15, 20},
        {1, 100, 1, 1, 1, 100, 1, 1, 100, 1},
        {0, 0, 0, 1}
    };
    for(auto&v:arr){
        cout << "Min cost to climb stairs: " << minCostClimbingStairs(v) << endl;
    }
    return 0;
}