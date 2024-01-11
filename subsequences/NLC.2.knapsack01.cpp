#include<bits/stdc++.h>

using namespace std;

/*
    0/1 Knapsack Problem
        Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
        You cannot break an item, either pick the complete item or don’t pick it (0-1 property).

        DP[n+1][W+1]
        Base Case: DP[0][x]=0 for all x
        Base Case: DP[i][0]=0 for all i

        If we dont take the ith item, we just do i+1 and W
        If we take the ith item, we do i+1 and W-wt[i]
        Then we do max of both as max(take, notTake), where take = (i+1, W, 0) and notTake = (i+1, W-wt[i], val[i])

        Converting to tabular form we will go with x=W->1 and i=n-1=>0

        For i=n-1 to 0
            For x=W to 1
                DP[i][x] = max(DP[i+1][x], (x>=wt[i]?val[i]+DP[i+1][x-wt[i]]:0))

        Answer = DP[0][W]

        Alternatively, we can use a single 1D DP array of size W+1, as the previous row is
        the same as the current row when we move from x=W->1 as it will not modify the values on the right when moving right to left.

        Recursive Solution(without Memo):
            Time Complexity: O(2^n), Space Complexity: O(n)

        Recursive Solution(with Memo):
            Time Complexity: O(n*W), Space Complexity: O(n*W)

        DP Solution:
            Time Complexity: O(n*W), Space Complexity: O(n*W), Space Optimized: O(W)
*/

class Solution {
public:
    int knapsackDPSpace(int W, vector<int> wt, vector<int> val, int n) {
        vector<int> dp(W + 1, 0);
        for ( int i = n - 1; i >= 0; i-- )
            for ( int x = W; x >= 0; x-- )
                if ( x >= wt[i] ) dp[x] = max(dp[x], val[i] + dp[x - wt[i]]);
        return dp[W];
    }

    int knapsackDP(int W, vector<int> wt, vector<int> val, int n) {
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        for ( int i = n - 1; i >= 0; i-- ) {
            for ( int x = 1; x <= W; x++ ) {
                int notTake = dp[i + 1][x];
                int take = 0;
                if ( x >= wt[i] ) take = val[i] + dp[i + 1][x - wt[i]];

                dp[i][x] = max(notTake, take);
            }
        }
        return dp[0][W];
    }

    int knapsackRec(int i, int W, const vector<int>& wt, const vector<int>& val, const int n, vector<vector<int>>& dp) {
        if ( i == n ) return 0;
        if ( dp[i][W] != -1 ) return dp[i][W];

        int notTake = knapsackRec(i + 1, W, wt, val, n, dp);
        int take = 0;
        if ( wt[i] <= W ) take = val[i] + knapsackRec(i + 1, W - wt[i], wt, val, n, dp);

        return dp[i][W] = max(notTake, take);
    }

    int knapsack(int W, vector<int> wt, vector<int> val, int n) {
        // vector<vector<int>> dp(n+1, vector<int>(W+1, -1));
        // return knapsackRec(0, W, wt, val, n, dp);
        return knapsackDPSpace(W, wt, val, n);
    }
};

int main() {
    Solution s;
    vector<int> val = { 60, 100, 120 };
    vector<int> wt = { 10, 20, 30 };
    cout << s.knapsack(50, wt, val, 3) << endl;
    return 0;
}