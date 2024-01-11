#include<bits/stdc++.h>

using namespace std;

/*
    LeetCode 1463 - Cherry Pickup II
        2 Robots, start from top left and top right in a maze of size n x m. Collect maximum cherries. No obstacles
        Robots can move to the next row in 3 ways: left, right, or stay in the same column
        Use a 3D memo. As both are moving in the same row, it means r1==r2, using this we can eliminate the 4D
        Hence just go through all possible 9 combos: r+1, c+{-1, 0, 1} and take max of all
        If it goes out of bounds, return -1e9
        If on last row, if both on same cell, return grid[r][c1], else return grid[r][c1]+grid[r][c2]
        At every recursion, take cherry = grid[r][c1]+grid[r][c2]. To prevent double counting, if both on same cell do cherry = grid[r][c1]
        Return max of all 9 combos + cherry
        Time: O(n^3), Space: O(n^3)

    Tabulation:
        3D -> 2D, using prev, current. Let dp, ndp of size mxm
        Base case is last row, copy that to dp.
        Since last row is already filled, start from r=n-2
        Let r=n-1->0, c1=0->m-1, c2=0->m-1 || inclusive
        At every cell, take cherry = grid[r][c1]+grid[r][c2]. To prevent double counting, if both on same cell do cherry = grid[r][c1]

        Let i=-1->1, j=-1->1 || inclusive
        If c1, c2 are in bounds, take mx = max(mx, dp[c1+i][c2+j])

        Let ndp[c1][c2] = mx+cherry, which is the max of all 9 combos + cherry

        Then dp = ndp, this is done inside c2 loop

        Return dp[0][m-1] as ans is stored here and not in dp[0][0]

        Time: O(n^3), Space: O(n^2)
*/

class Solution {
public:
    int cherryPickup2ManMemo(const vector<vector<int>>& grid, const int m, int r, int c1, int c2, int*** memo2P) {
        if ( c1 < 0 || c2 < 0 || c1 >= m || c2 >= m ) return -1e8;
        if ( r == grid.size() - 1 ) {
            if ( c1 == c2 ) return grid[r][c1];
            else return grid[r][c1] + grid[r][c2];
        }

        if ( memo2P[r][c1][c2] != -1 ) return memo2P[r][c1][c2];

        int ans = 0, x = -1e8;
        if ( c1 == c2 ) ans = grid[r][c1];
        else ans = grid[r][c1] + grid[r][c2];

        for ( int i = -1; i < 2; i++ )
            for ( int j = -1; j < 2; j++ )
                x = max(x, cherryPickup2ManMemo(grid, m, r + 1, c1 + i, c2 + j, memo2P));

        ans += x;
        return memo2P[r][c1][c2] = ans;
    }

    int cherryPickup(vector<vector<int>>& grid) {
        const int n = grid.size(), m = grid[0].size();

        // memset(memo2P, -1, 71*71*71*sizeof(int));
        // int memo2P[71][71][71];
        // return cherryPickup2ManMemo(grid, m, 0, 0, m-1);

        vector<vector<int>>  dp(m, vector<int>(m, 0));
        vector<vector<int>> ndp(m, vector<int>(m, 0));
        for ( int i = 0; i < m; i++ ) {
            for ( int j = 0; j < m; j++ ) {
                if ( i == j ) dp[i][j] = grid[n - 1][j];
                else dp[i][j] = grid[n - 1][i] + grid[n - 1][j];
            }
        }

        for ( int r = n - 2; r >= 0; r-- ) {
            for ( int c1 = 0; c1 < m; c1++ ) {
                for ( int c2 = 0; c2 < m; c2++ ) {
                    int mx = -1e9, ans;
                    if ( c1 == c2 ) ans = grid[r][c1];
                    else ans = grid[r][c1] + grid[r][c2];

                    for ( int i = -1; i < 2; i++ )
                        for ( int j = -1; j < 2; j++ )
                            if ( c1 + i >= 0 && c2 + j >= 0 && c1 + i < m && c2 + j < m )
                                mx = max(mx, dp[c1 + i][c2 + j]);

                    ndp[c1][c2] = mx + ans;
                }
            }
            dp = ndp;
        }
        return dp[0][m - 1];
    }
};

int main() {
    vector<vector<int>> grid = { {0,1,-1},{1,0,-1},{1,1,1} };
    cout << Solution().cherryPickup(grid) << endl;
    return 0;
}