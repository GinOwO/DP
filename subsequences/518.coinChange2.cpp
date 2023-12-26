#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 518 - Coin Change 2
        Given an array of coins and a total amount, find the number of ways to make up that amount.
        Infinite supply of each coin. Sorted array of coins.
        Order of coins does not matter. [1,2] and [2,1] are same.

        (Space Optimized 2 only)
        dp[0] = 1 as we can make up 0 amount in 1 way, by not taking any coin, i.e empty set
        We set all other cases to 0

        We go from i=0->n-1 and for each i, we go through all amounts and check if we can use that coin to make up the amount
        We start from x=coins[i] as we cannot make up amount less than coins[i] using coins[i]

        As we can make by definition make (in a unique way) an amount k if there exists a coin of value k: dp[x-coins[i]] = dp[k-k] = dp[0] = 1 in the first iteration
        This handles increasing the value of dp[x] when a coin of value x is encountered in coins array.

        For i=0 to n-1
            For x=coins[i] to amount
                dp[x] += dp[x-coins[i]]
        
        Answer = dp[amount]

        Time Complexity: O(n*amount), Space Complexity: O(amount)
*/

class Solution {
public:
    int changeDPSpace2(const int amount, const vector<int>& coins){
        int n = coins.size();
        vector<int> dp(amount+1, 0); dp[0] = 1;

        for(int i=0; i<n; i++)
            for(int x=coins[i]; x<=amount; x++)
                dp[x] += dp[x-coins[i]];
        
        return dp[amount];
    }

    int changeDPSpace(const int amount, const vector<int>& coins){
        int n = coins.size();
        vector<int> dp(amount+1, 0), ndp(amount+1, 0);

        for(int i=0; i<=amount; i++) dp[i] = i%coins[0]==0;

        for(int i=1; i<n; i++){
            for(int x=0; x<=amount; x++){
                int notTake = dp[x], take = 0;
                if(x>=coins[i]) take = ndp[x-coins[i]];
                ndp[x] = take + notTake;
            }
            dp = ndp;
        }
        return dp[amount];
    }

    int changeDP(const int amount, const vector<int>& coins){
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount+1, 0));

        for(int i=0; i<=amount; i++) dp[0][i] = i%coins[0]==0;

        for(int i=1; i<n; i++){
            for(int x=0; x<=amount; x++){
                int notTake = dp[i-1][x], take = 0;
                if(x>=coins[i]) take = dp[i][x-coins[i]];
                dp[i][x] = take + notTake;
            }
        }
        return dp[n-1][amount];
    }

    int changeRec(int i, int x, const vector<int>& coins, vector<vector<int>>& dp){
        if(i==0) return x%coins[i]==0;
        if(dp[i][x]!=-1) return dp[i][x];

        int notTake = changeRec(i-1, x, coins, dp), take = 0;
        if(x>=coins[i]) take = changeRec(i, x-coins[i], coins, dp);
        return dp[i][x] = take + notTake;
    }

    int change(int amount, vector<int>& coins) {
        // vector<vector<int>> dp(coins.size(), vector<int>(amount+1, -1));
        // return changeRec(coins.size()-1, amount, coins, dp);
        return changeDPSpace2(amount, coins);
    }
};

int main(){
    Solution s;
    vector<int> coins = {1,2,5};
    cout << s.change(5, coins) << endl;
    return 0;
}