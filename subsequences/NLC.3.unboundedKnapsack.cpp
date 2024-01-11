#include<bits/stdc++.h>

using namespace std;

/*
    Unbounded Knapsack Problem
        Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
        You cannot break an item, either pick the complete item or don’t pick it (0-1 property). You can pick an item infinite times.

        Solution is essentially the same as 0/1 knapsack, in this case we just stay at the same item when we take it, i.e i and not i+1
        So notTake is the same but for take we do (i, W-wt[i], val[i]) instead of (i+1, W-wt[i], val[i]).

        For space optimized, we go from x=0->W instead of x=W->1.

        (Space Optimized only)
        dp[0] = 0 as we cannot make up 0 amount using any value as 1<=val[i]

        We go from i=n-1=>0 and for each i we calculate all the value for the weights weights using dp[x] = max(dp[x], val[i] + dp[x-wt[i]]) where x=0->W

        For i=n-1 to 0
            For x=0 to W
                dp[x] = max(dp[x], (x>=wt[i]?val[i]+dp[x-wt[i]]:0))

        Answer = dp[W]

        Time Complexity: O(n*W), Space Complexity: O(W)

*/

class Solution {
public:
    int knapsackDPSpace(int W, int* wt, int* val, int n) {
        vector<int> dp(W + 1, 0);
        for ( int i = n - 1; i >= 0; i-- )
            for ( int x = 0; x <= W; x++ )
                if ( x >= wt[i] ) dp[x] = max(dp[x], val[i] + dp[x - wt[i]]);
        return dp[W];
    }

    int knapsackDP(int W, int* wt, int* val, int n) {
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        for ( int i = n - 1; i >= 0; i-- ) {
            for ( int x = 1; x <= W; x++ ) {
                int notTake = dp[i + 1][x];
                int take = 0;
                if ( x >= wt[i] ) take = val[i] + dp[i][x - wt[i]];

                dp[i][x] = max(notTake, take);
            }
        }
        return dp[0][W];
    }

    int knapsackRec(int i, int W, int val[], int wt[], int n, vector<vector<int>>& dp) {
        if ( i == n ) return 0;
        if ( dp[i][W] != -1 ) return dp[i][W];

        int notTake = knapsackRec(i + 1, W, val, wt, n, dp), take = 0;
        if ( W >= wt[i] ) take = val[i] + knapsackRec(i, W - wt[i], val, wt, n, dp);

        return dp[i][W] = max(take, notTake);
    }

    int knapSack(int n, int W, int val[], int wt[]) {
        // vector<vector<int>> dp(n+1, vector<int>(W+1, -1));
        // return knapsackRec(0, W, val, wt, n, dp);
        return knapsackDPSpace(W, wt, val, n);
    }
};

int main() {
    Solution s;
    int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    cout << s.knapSack(3, 50, val, wt) << endl;
    return 0;
}