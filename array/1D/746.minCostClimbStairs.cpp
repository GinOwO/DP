
#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 746. Min Cost Climbing Stairs
        Array of costs to climb stairs. Can climb 1 or 2 steps. Find min cost to reach top
        DP[n+2], n+2 to ignore boundary conditions. 
        dp[i] = min(dp[i+1], dp[i+2])+cost[i]
        Answer = min(dp[0], dp[1])

        Time Complexity: O(n)
        Space Complexity: O(n)
*/

int minCostClimbingStairs(vector<int>& cost) {
    int n=cost.size();
    vector<int> dp(n+2,0);
    for(int i=n-1; i>=0; i--)
        dp[i]=min(dp[i+1], dp[i+2])+cost[i];
    
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