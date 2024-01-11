#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 122 - Best Time to Buy and Sell Stock II
        Array of size n with n prices. Find the maximum profit that can be made by buying and selling stocks.
        Buy and sell as many times as you want, but if bought then must be sold before buying again.

        We just check if we have already bought, in which case we take the max of the two cases:
            Sell: (i, 1) -> (i+1, 0), i.e sell the stock and move to the next day
            Skip: (i, 0) -> (i+1, 0), i.e skip the current day
        If we have not bought, then we take the max of the two cases:
            Buy: (i, 0) -> (i+1, 1), i.e buy the stock and move to the next day
            Skip: (i, 0) -> (i+1, 0), i.e skip the current day

        The max of both cases is the answer

        In DP, we use a 2*n array to store the two states, i.e DP[b][i] where b=bought or not, i = price index
        The base case is DP[1][n] = 0, i.e if we have bought and we are at the last day, then we cannot sell
        The answer is DP[1][0], i.e we are the first day and we can buy

        For i=n-1->0
            DP[1][i] = max(prices[i] + DP[0][i+1], DP[1][i+1])
            DP[0][i] = max(-prices[i] + DP[1][i+1], DP[0][i+1])

        Time: O(n), Space: O(n)

        Space Optimized:
            This can be optimized into 4 variables, i.e a=DP[0][i], b=DP[1][i], x=DP[0][i+1], y=DP[1][i+1]
            For i=n-1->0
                a = max(prices[i] + y, x)
                b = max(-prices[i] + x, y)
                x=a, y=b

            Then the answer is y

            Time: O(n), Space: O(1)
*/

class Solution {
public:
    int maxProfitDPSpace(const vector<int>& prices, const int n) {
        int a, b, x = 0, y = 0;

        for ( int i = n - 1; i >= 0; i-- ) {
            a = max(prices[i] + y, x);
            b = max(-prices[i] + x, y);
            x = a, y = b;
        }
        return y;
    }

    int maxProfitDP(const vector<int>& prices, const int n) {
        vector<vector<int>> dp(2, vector<int>(n + 1, 0));

        for ( int i = n - 1; i >= 0; i-- ) {
            dp[0][i] = max(prices[i] + dp[1][i + 1], dp[0][i + 1]);
            dp[1][i] = max(-prices[i] + dp[0][i + 1], dp[1][i + 1]);
        }
        return dp[1][0];
    }

    int maxProfitRec(int i, bool b, const vector<int>& prices, vector<vector<int>>& dp) {
        if ( i == prices.size() ) return 0;

        if ( dp[b][i] != -1 ) return dp[b][i];

        int profit = 0;
        if ( b ) profit = max(-prices[i] + maxProfitRec(i + 1, 0, prices, dp), maxProfitRec(i + 1, 1, prices, dp));
        else profit = max(prices[i] + maxProfitRec(i + 1, 1, prices, dp), maxProfitRec(i + 1, 0, prices, dp));

        return dp[b][i] = profit;
    }

    int maxProfit(vector<int>& prices) {
        // vector<vector<int>> dp(2, vector<int>(prices.size()+1, -1));
        // return maxProfitRec(0, 1, prices, dp);
        return maxProfitDPSpace(prices, prices.size());
    }
};

int main() {
    Solution s;
    vector<int> prices = { 7,1,5,3,6,4 };
    cout << s.maxProfit(prices) << endl;
    return 0;
}