#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 64 - Minimum Path Sum
        n x m grid, find min path sum from top left to bottom right
        At (i, j), can move to (i+1, j) or (i, j+1)
        DP[m+1] = 1e9.

        Let i=0 to n-1
            temp[m+1]=0, temp[0]=1e9
            Let j=0 to m-1
                If at (0, 0), temp[1]=grid[0][0]
                Else temp[j+1] = grid[i][j]+min(dp[j+1], temp[j])
            dp = temp

        Answer = dp[m]


        Time Complexity: O(n*m)
        Space Complexity: O(n*m)
*/


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> dp(m + 1, 1e9);
        for ( int i = 0; i < n; i++ ) {
            vector<int> temp(m + 1, 0); temp[0] = 1e9;
            for ( int j = 0; j < m; j++ ) {
                if ( i == 0 && j == 0 ) temp[1] = grid[0][0];
                else temp[j + 1] = grid[i][j] + min(dp[j + 1], temp[j]);
            }
            dp = temp;
        }
        return dp[m];
    }
};