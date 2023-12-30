#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 188 - Best Time to Buy and Sell Stock IV
        Array of size n with n prices. Find the maximum profit that can be made by buying and selling stocks.
        Buy and sell at most k times.

        Same as LC 123, just replace 2 with K
*/

class Solution {
public:
    int maxProfitDPSpace(const vector<int>& prices, const int n, const int K){
        vector<vector<int>> dp(2, vector<int>(K+1, 0));
        vector<vector<int>> ndp(2,vector<int>(K+1, 0));

        for(int i=n-1; i>=0; i--){
            for(int k=0; k<=K; k++){
                ndp[1][k] = max(-prices[i] + (k>0?dp[0][k-1]:0), dp[1][k]);
                ndp[0][k] = max(dp[0][k], prices[i] + dp[1][k]);
            }
            dp = ndp;
        }
        return dp[1][K];
    }

    int maxProfitDP(const vector<int>& prices, const int n, const int K){
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(K+1, vector<int>(n+1, 0)));

        for(int i=n-1; i>=0; i--){
            for(int k=0; k<=K; k++){
                dp[1][k][i] = max(-prices[i] + (k>0?dp[0][k-1][i+1]:0), dp[1][k][i+1]);
                dp[0][k][i] = max(dp[0][k][i+1], prices[i] + dp[1][k][i+1]);
            }
        }
        return dp[1][K][0];
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

    int maxProfit(int k, vector<int>& prices) {
        // vector<vector<vector<int>>> dp(2, vector<vector<int>>(k+1, vector<int>(prices.size()+1, -1)));
        // return maxProfitRec(0, 1, k, prices, dp);
        return maxProfitDPSpace(prices, prices.size(), k);
    }
};

int main(){
    Solution sol;
    vector<int> prices = {3,2,6,5,0,3};
    cout << sol.maxProfit(2, prices) << endl;
    return 0;
}