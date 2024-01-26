#include <bits/stdc++.h>

using namespace std;

/*
    LeetCode 576 - Out of Boundary Paths
        Given a grid of size m*n, and a starting position (sr, sc), find the number of ways to go out of bounds
        Can only move up, down, left, right
        Can move at most mx steps

        Use a 3D memo, as we have 3 variables, i, j and mx
        If out of bounds, return 1
        If mx==0, return 0
        If memo[i][j][mx]!=-1, return memo[i][j][mx]
        Else, ans = 0, and for all 4 directions, ans += findPaths(i+dir[k], j+dir[k+1], m, n, mx-1)
        Return memo[i][j][mx] = ans

        Time: O(m*n*mx), Space: O(m*n*mx)
*/


#define isValid(i, j, m, n) (i>=0 && i<m && j>=0 && j<n)

constexpr int dir[] = { 0, -1, 0, 1, 0 };
constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int findPathsRec(int i, int j, int m, int n, int mx, vector<vector<vector<int>>>& memo) {
        if ( !isValid(i, j, m, n) ) return 1;

        if ( memo[i][j][mx] != -1 ) return memo[i][j][mx];

        int ans = 0;
        for ( int k = 0; k < 4; k++ ) {
            if ( mx > 0 ) ans = ( ans + findPathsRec(i + dir[k], j + dir[k + 1], m, n, mx - 1, memo) ) % MOD;
        }
        return memo[i][j][mx] = ans;
    }

    int findPaths(int m, int n, int mx, int sr, int sc) {
        vector<vector<vector<int>>> memo(m + 1, vector<vector<int>>(n + 1, vector<int>(mx + 1, -1)));
        return findPathsRec(sr, sc, m, n, mx, memo);
    }
};

int main() {
    Solution sol;
    cout << sol.findPaths(2, 2, 2, 0, 0) << endl;
    cout << sol.findPaths(1, 3, 3, 0, 1) << endl;

    return 0;
}