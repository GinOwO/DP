#include<vector>
#include<utility>
#include<iostream>
#include<climits>
#include<map>
#include<assert.h>

using namespace std;

// Paint houses - Leetcode 256
// N houses, 3 colors, paint each house with a color such that no two adjacent houses have same color with min cost
// Make DP[5]. Set DP[0] and DP[4] to INT_MAX
// New array nDP[5] = INT_MAX. nDP[i]=min(DP[i-1], DP[i], DP[i+1])+cost[i-1]
// Copy nDP to DP. In the end, return min(DP)
// Time: O(n), Space: O(1)

int minCost(const vector<vector<int>>& arr){
    int n = arr.size();
    vector<int> dp(5, 0); dp[0]=dp[4]=INT_MAX;
    for(auto&v:arr){
        vector<int> nDP(5, INT_MAX);
        for(int i=1; i<=3; i++)
            nDP[i] = v[i-1]+min(dp[i-1], min(dp[i], dp[i+1]));
        dp = nDP;
    }
    int mn = INT_MAX;
    for(auto&c:dp) mn = min(mn, c);
    return mn;
}

int main(){
    // Paint houses - Leetcode 256
    map<vector<vector<int>>, int> arr = {
        {{{17,2,17},{16,16,5},{14,3,19}}, 10},
        {{{7,6,2}}, 2}, 
        {{{7,6,2},{1,2,3}}, 4}
    };
    for(auto&[v, ans]:arr){
        int res = minCost(v);
        cout << "Min cost to paint houses: " << res << endl;
        assert(res==ans);
    }
    return 0;
}

