#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 63 - Unique Paths II
        Given a grid of size m*n, find the number of unique paths from top left to bottom right.
        Can only move right or down. Obstacles are marked as 1. Cannot move to a cell with an obstacle.

        Go through the grid, if grid[i][j]==1, dp[j]=0, else dp[j] = dp[j] + dp[j-1]

        Answer is dp[n]

        Time: O(m*n), Space: O(n)

*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n + 1, 0); dp[1] = 1;
        for ( int i = 1; i <= m; i++ )
            for ( int j = 1; j <= n; j++ ) {
                if ( !grid[i - 1][j - 1] ) dp[j] += dp[j - 1];
                else dp[j] = 0;
            }
        return dp[n];
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {0,0,0},{0,1,0},{0,0,0} };
    cout << s.uniquePathsWithObstacles(grid) << endl;
    return 0;
}