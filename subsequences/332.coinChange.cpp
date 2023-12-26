#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 332 - Coin Change
        Given an array of coins and a total amount, find the minimum number of coins required to make up that amount.
        Infinite supply of each coin. Sorted array of coins.

        DP[n+1][amount+1]

        (Space Optimized 2 only)
        As 1<=coins[i]<=amount, dp[0] = 0 as we cannot use any coin to make up 0 amount 
        We set all other cases to a sentiel say INT_MAX-1

        We go from i=1->amount and for each i, we go through all coins and check if we can use that coin to make up the amount
        If coin is greater than amount, we stop checking for that amount as all coins will be greater than amount

        For i=1 to amount
            For c=0 to n-1
                if coins[c]>i break
                dp[i] = min(dp[i], dp[i-coins[c]]+1)
        
        Answer = dp[amount]

        Time Complexity: O(n*amount), Space Complexity: O(amount)
*/


class Solution {
public:
    int coinChangeDPSpace2(const int amount, vector<int>& coins){
        vector<int> dp(amount+1,INT_MAX-1); dp[0]=0;

        sort(coins.begin(), coins.end());

        for(int i=1; i<=amount; i++){
            for(auto&c:coins){
                if(c>i) break; // if sorted
                if(c<=i) dp[i]=min(dp[i],dp[i-c]+1);
            }
        }
        
        return (dp[amount]==INT_MAX-1)?-1:dp[amount];
    }

    int coinChangeDPSpace(const int amount, const vector<int>& coins){
        int n = coins.size();
        vector<int> dp(amount+1, 0), ndp(amount+1, 0);
        for(int t=0; t<=amount; t++) dp[t] = (t%coins[0]==0)?t/coins[0]:1e9;

        for(int i=1; i<n; i++){
            for(int x=1; x<=amount; x++){
                int notTake = dp[x];
                int take = 1e9;
                if(coins[i]<=x) take = 1+ndp[x-coins[i]];
                ndp[x] = min(notTake, take);
            }
            dp = ndp;
        }
        return dp[amount]==1e9?-1:dp[amount];
    }

    int coinChangeDP(const int amount, const vector<int>& coins){
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
        for(int t=0; t<=amount; t++) dp[0][t] = (t%coins[0]==0)?t/coins[0]:1e9;

        for(int i=1; i<n; i++){
            for(int x=1; x<=amount; x++){
                int notTake = dp[i-1][x];
                int take = 1e9;
                if(coins[i]<=x) take = 1+dp[i][x-coins[i]];
                dp[i][x] = min(notTake, take);
            }
        }
        return dp[n-1][amount]==1e9?-1:dp[n-1][amount];
    }

    int coinChangeRec(int i, int x, const vector<int>& coins, vector<vector<int>>& dp){
        if(i==0) return (x%coins[i]==0)?x/coins[i]:1e9;
        if(dp[i][x]!=-1) return dp[i][x];

        int notTake = coinChangeRec(i-1, x, coins, dp);
        int take = 1e9;
        if(coins[i]<=x) take = 1+coinChangeRec(i, x-coins[i], coins, dp);

        return dp[i][x] = min(notTake, take);
    }

    int coinChange(vector<int>& coins, int amount){
        // vector<vector<int>> dp(coins.size()+1, vector<int>(amount+1, -1));
        // int ans = coinChangeRec(coins.size()-1, amount, coins, dp);
        // return ans==1e9?-1:ans;
        return coinChangeDPSpace2(amount, coins);
    }
};