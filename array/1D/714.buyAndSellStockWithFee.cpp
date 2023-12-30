#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 714 - Best Time to Buy and Sell Stock with Transaction Fee
        Same as LC 122, but just change this line during sale:
            prices[i] + maxProfitRec(i+1, 1, prices, dp)
        To:
            prices[i] - fee + maxProfitRec(i+1, 1, prices, dp, fee)
        
        Essentially a fee is charged for every sale, so just substract that from the profit when taking max during sale.
        Also add in fee into the function call.

        Time: O(n), Space: O(n), Space Optimized: O(1)

        Not going to implement DP here as it is the same as LC 122
*/

class Solution {
public:
    int maxProfitRec(int i, bool b, const vector<int>& prices, vector<vector<int>>& dp, const int fee){
        if(i==prices.size()) return 0;

        if(dp[b][i]!=-1) return dp[b][i];

        int profit = 0;
        if(b) profit = max(
                        -prices[i] + maxProfitRec(i+1, 0, prices, dp, fee), 
                        maxProfitRec(i+1, 1, prices, dp, fee)
                    );
        else profit = max(
                        prices[i]-fee + maxProfitRec(i+1, 1, prices, dp, fee), 
                        maxProfitRec(i+1, 0, prices, dp, fee)
                    );

        return dp[b][i] = profit;
    }

    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(2, vector<int>(prices.size()+1, -1));
        return maxProfitRec(0, 1, prices, dp, fee);
    }
};

int main(){
    Solution sol;
    vector<int> prices = {1,3,2,8,4,9};
    int fee = 2;
    cout<<sol.maxProfit(prices, fee)<<endl;
    return 0;
}