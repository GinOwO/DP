#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 741 - Cherry Pickup
        Go from top left to bottom right, and then bottom right to top left and collect maximum cherries
        Optimization is to consider the fact that moving one person from top left to bottom right and back is the same as moving 2 people from top left to bottom right
        Use a 3D memo. As both are moving together, it means r1+c1 = r2+c2, using this we can eliminate the 4D
        Hence just go through all possible directions, i.e vertical and horizontal: vv, hh, hv, vh and take max of all
        If going out of bounds or hitting a thorn, return -1e9
        If one person reaches bottom right, return the value at that cell
        At every recursion, take cherry = grid[r1][c1]+grid[r2][c2]. To prevent double counting, if both on same cell do cherry = grid[r1][c1]
        Return max of all 4 directions + cherry
        Time: O(n^3), Space: O(n^3)
*/

class Solution {
private:
    // r1+c1==r2+c2, hence get 3d map using c2 = r1+c1-r2
    // int memo2P[50][50][50] = {-1}; // with a bit more changes
    map<pair<pair<int, int>, int>, int> memo2P;
    int cherryPickup2ManMemo(vector<vector<int>>& grid, const int n, int r1 = 0, int c1 = 0, int r2 = 0) {
        if ( memo2P.count({ {r1,c1}, r2 }) ) return memo2P[{{r1, c1}, r2}];

        int c2 = r1 + c1 - r2;
        if ( r1 >= n || c1 >= n || r2 >= n || c2 >= n || grid[r1][c1] == -1 || grid[r2][c2] == -1 ) return -1e9;
        if ( r1 == n - 1 && c1 == n - 1 ) return grid[r1][c1];

        int ans = 0;
        if ( r1 == r2 && c1 == c2 ) ans = grid[r1][c1];
        else ans = grid[r1][c1] + grid[r2][c2];

        int hh = cherryPickup2ManMemo(grid, n, r1, c1 + 1, r2);
        int hv = cherryPickup2ManMemo(grid, n, r1, c1 + 1, r2 + 1);
        int vh = cherryPickup2ManMemo(grid, n, r1 + 1, c1, r2);
        int vv = cherryPickup2ManMemo(grid, n, r1 + 1, c1, r2 + 1);

        ans += max(max(vv, hh), max(hv, vh));
        return memo2P[{{r1, c1}, r2}] = ans;
    }

    int cherryPickup2Man(vector<vector<int>>& grid, const int n, int r1 = 0, int c1 = 0, int r2 = 0, int c2 = 0) {
        if ( r1 >= n || c1 >= n || r2 >= n || c2 >= n || grid[r1][c1] == -1 || grid[r2][c2] == -1 ) return -1e9;
        if ( r1 == n - 1 && c1 == n - 1 ) return grid[r1][c1];

        int ans = 0;
        if ( r1 == r2 && c1 == c2 ) ans = grid[r1][c1];
        else ans = grid[r1][c1] + grid[r2][c2];

        int hh = cherryPickup2Man(grid, n, r1, c1 + 1, r2, c2 + 1);
        int hv = cherryPickup2Man(grid, n, r1, c1 + 1, r2 + 1, c2);
        int vh = cherryPickup2Man(grid, n, r1 + 1, c1, r2, c2 + 1);
        int vv = cherryPickup2Man(grid, n, r1 + 1, c1, r2 + 1, c2);

        ans += max(max(vv, hh), max(hv, vh));
        return ans;
    }

    vector<map<pair<int, int>, int>> memo { {},{} };
    int cherryPickupRecMemo(vector<vector<int>>& grid, const int n, const int i = 0, const int j = 0, int dir = 1) {
        if ( n == 1 ) return grid[0][0];
        if ( memo[dir < 0 ? 0 : 1].count({ i,j }) ) return memo[dir == 1 ? 0 : -1][{i, j}];
        if ( dir == 1 && i == n - 1 && j == n - 1 ) return cherryPickupRec(grid, n, i, j, -1);
        if ( dir == -1 && i == 0 && j == 0 ) return 0;
        if ( i < 0 || j < 0 || i >= n || j >= n || grid[i][j] == -1 ) return -1e9;
        int q = grid[i][j]; grid[i][j] = 0;
        int ans = max(cherryPickupRec(grid, n, i + dir, j, dir), cherryPickupRec(grid, n, i, j + dir, dir)) + q;
        grid[i][j] = q;
        return memo[dir < 0 ? 0 : 1][{i, j}] = ans;
    }

    int cherryPickupRec(vector<vector<int>>& grid, const int n, const int i = 0, const int j = 0, int dir = 1) {
        if ( n == 1 ) return grid[0][0];
        if ( dir == 1 && i == n - 1 && j == n - 1 ) return cherryPickupRec(grid, n, i, j, -1);
        if ( dir == -1 && i == 0 && j == 0 ) return 0;
        if ( i < 0 || j < 0 || i >= n || j >= n || grid[i][j] == -1 ) return -1e9;
        int q = grid[i][j]; grid[i][j] = 0;
        int ans = max(cherryPickupRec(grid, n, i + dir, j, dir), cherryPickupRec(grid, n, i, j + dir, dir)) + q;
        grid[i][j] = q;
        return ans;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        return max(cherryPickup2ManMemo(grid, grid.size()), 0);
    }
};

int main() {
    vector<vector<int>> grid = { {0,1,-1},{1,0,-1},{1,1,1} };
    cout << Solution().cherryPickup(grid) << endl;
    return 0;
}