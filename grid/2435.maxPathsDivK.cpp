#include <bits/stdc++.h>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
public:
    int numberOfPathsDP(const int k, const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, 0)));
        dp[0][0][grid[0][0] % k] = 1;

        for ( int i = 0; i < m; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                if ( i == 0 && j == 0 ) continue;
                for ( int sum = 0; sum < k; sum++ ) {
                    int rem = ( sum + grid[i][j] ) % k;
                    if ( i ) dp[i][j][rem] += dp[i - 1][j][sum];
                    if ( j ) dp[i][j][rem] += dp[i][j - 1][sum];
                    dp[i][j][rem] %= MOD;
                }
            }
        }
        return dp[m - 1][n - 1][0];
    }

    int numberOfPathsRec(int i, int j, int sum, const int k, const vector<vector<int>>& grid,
        vector<vector<vector<int>>>& dp) {

        int m = grid.size(), n = grid[0].size();
        if ( i >= m || j >= n ) return 0;

        int rem = ( sum + grid[i][j] ) % k;
        if ( i == m - 1 && j == n - 1 ) return rem == 0;

        if ( dp[i][j][sum % k] != -1 ) return dp[i][j][sum % k];

        int r = numberOfPathsRec(i, j + 1, rem, k, grid, dp),
            d = numberOfPathsRec(i + 1, j, rem, k, grid, dp);
        return dp[i][j][sum % k] = ( r % MOD + d % MOD ) % MOD;
    }

    int numberOfPaths(vector<vector<int>>& grid, int k) {
        // int m = grid.size(), n = grid[0].size();
        // vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
        // return numberOfPathsRec(0, 0, 0, k, grid, dp);
        return numberOfPathsDP(k, grid);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int k = 5;
    cout << sol.numberOfPaths(grid, k) << endl;
    return 0;
}