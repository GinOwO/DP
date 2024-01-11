#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 309 - Best Time to Buy and Sell Stock with Cooldown
        Same as LC 122, but just change this line during sale:
            prices[i] + maxProfitRec(i+1, 1, prices, dp)
        To:
            prices[i] + maxProfitRec(i+2, 1, prices, dp)
        i.e change (i+1) -> (i+2) since cd of 1 day. More generally if cd is k days, then change (i+1) -> (i+k+1)

        Time: O(n), Space: O(n), Space Optimized: O(1)

        Not going to implement DP here as it is the same as LC 122
*/

class Solution {
public:
    int maxProfitRec(int i, bool b, const vector<int>& prices, vector<vector<int>>& dp) {
        if ( i >= prices.size() ) return 0;

        if ( dp[b][i] != -1 ) return dp[b][i];

        int profit = 0;
        if ( b ) profit = max(-prices[i] + maxProfitRec(i + 1, 0, prices, dp), maxProfitRec(i + 1, 1, prices, dp));
        else profit = max(prices[i] + maxProfitRec(i + 2, 1, prices, dp), maxProfitRec(i + 1, 0, prices, dp));

        return dp[b][i] = profit;
    }

    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(prices.size() + 1, -1));
        return maxProfitRec(0, 1, prices, dp);
    }
};

int main() {
    Solution sol;
    vector<int> prices = { 1,2,3,0,2 };
    cout << sol.maxProfit(prices) << endl;
    return 0;
}