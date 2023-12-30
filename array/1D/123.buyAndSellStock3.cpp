#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 123 - Best Time to Buy and Sell Stock III
        Array of size n with n prices. Find the maximum profit that can be made by buying and selling stocks.
        Buy and sell at most twice.

        We can use the same approach as 122, but we need to keep track of the number of transactions.
        We can use a 2*k*n array to store the two states, i.e DP[b][k][i] where b=bought or not, k=number of transactions, i = price index
        Here k=2, so DP[2][3][n] = {0}
        
        The base case is DP[1][k][n] = 0, i.e if we have bought and we are at the last day, then we cannot sell
        The answer is DP[1][2][0], i.e we are the first day and we can buy

        For i=n-1->0
            For k=0->2
                DP[1][k][i] = max(-prices[i] + (k>0?DP[0][k-1][i+1]:0), DP[1][k][i+1])
                DP[0][k][i] = max(prices[i] + DP[1][k][i+1], DP[0][k][i+1])
        
        Time: O(n), Space: O(n)

        Space Optimized:
            This can be optimized into 2*3 arrays, i.e 1 for DP[0][k][i], and 1 for DP[1][k][i]
            For i=n-1->0
                For k=0->2
                    NDP[1][k] = max(-prices[i] + (k>0?DP[0][k-1]:0), DP[1][k])
                    NDP[0][k] = max(prices[i] + DP[1][k], DP[0][k])
                DP = NDP
            
            Then the answer is DP[1][2]

            Time: O(n), Space: O(1) as we are using a fixed size array 2*3

*/

class Solution {
public:
    int maxProfitDPSpace(const vector<int>& prices, const int n){
        vector<vector<int>> dp(2, vector<int>(2+1, 0));
        vector<vector<int>> ndp(2,vector<int>(2+1, 0));

        for(int i=n-1; i>=0; i--){
            for(int k=0; k<=2; k++){
                ndp[1][k] = max(-prices[i] + (k>0?dp[0][k-1]:0), dp[1][k]);
                ndp[0][k] = max(dp[0][k], prices[i] + dp[1][k]);
            }
            dp = ndp;
        }
        return dp[1][2];
    }

    int maxProfitDP(const vector<int>& prices, const int n){
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(2+1, vector<int>(n+1, 0)));

        for(int i=n-1; i>=0; i--){
            for(int k=0; k<=2; k++){
                dp[1][k][i] = max(-prices[i] + (k>0?dp[0][k-1][i+1]:0), dp[1][k][i+1]);
                dp[0][k][i] = max(dp[0][k][i+1], prices[i] + dp[1][k][i+1]);
            }
        }
        return dp[1][2][0];
    }

    int maxProfitRec(int i, bool b, int k, const vector<int>& prices, vector<vector<vector<int>>>& dp){
        if(i==prices.size()) return 0;

        if(dp[b][k][i]!=-1) return dp[b][k][i];

        int trans=-1e9, skip=-1e9;
        if(b){ 
            if(k>0) trans = -prices[i] + maxProfitRec(i+1, 0, k-1, prices, dp);
            skip = maxProfitRec(i+1, 1, k, prices, dp);
        }
        else{
            trans = prices[i] + maxProfitRec(i+1, 1, k, prices, dp);
            skip = maxProfitRec(i+1, 0, k, prices, dp);
        }

        return dp[b][k][i] = max(trans, skip);
    }

    int maxProfit(vector<int>& prices) {
        // vector<vector<vector<int>>> dp(2, vector<vector<int>>(3, vector<int>(prices.size()+1, -1)));
        // return maxProfitRec(0, 1, 2, prices, dp);
        return maxProfitDPSpace(prices, prices.size());
    }
};

int main(){
    Solution sol;
    vector<int> prices = {3,3,5,0,0,3,1,4};
    cout<<sol.maxProfit(prices)<<endl;
    return 0;
}