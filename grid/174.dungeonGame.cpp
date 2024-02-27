#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int calculateMinimumHPDPSpace(const vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<int> dp(n + 1, 1e9);

        dp[n - 1] = 1;

        for ( int i = m - 1; i >= 0; i-- ) {
            vector<int> ndp(n + 1, 1e9);
            if ( i == m - 1 ) ndp[n] = 1;

            for ( int j = n - 1; j >= 0; j-- ) {
                ndp[j] = max(min(ndp[j + 1], dp[j]) - dungeon[i][j], 1);
            }
            dp = move(ndp);
        }

        return dp[0];
    }

    int calculateMinimumHPDP(const vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 1e9));
        dp[m][n - 1] = dp[m - 1][n] = 1;

        for ( int i = m - 1; i >= 0; i-- ) {
            for ( int j = n - 1; j >= 0; j-- ) {
                dp[i][j] = max(min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }

#define isValid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)
    int calculateMinimumHPRec(int i, int j, const vector<vector<int>>& dungeon,
        vector<vector<int>>& dp) {
        int m = dungeon.size(), n = dungeon[0].size();
        if ( ( i == m - 1 && j == n ) || ( i == m && j == n - 1 ) ) return 1;
        if ( !isValid(i, j, m, n) ) return 1e9;
        if ( dp[i][j] != -1 ) return dp[i][j];

        int right = calculateMinimumHPRec(i, j + 1, dungeon, dp),
            down = calculateMinimumHPRec(i + 1, j, dungeon, dp);
        return dp[i][j] = max(min(down, right) - dungeon[i][j], 1);
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // int m = dungeon.size(), n = dungeon[0].size();
        // vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        // return calculateMinimumHPRec(0, 0, dungeon, dp);
        return calculateMinimumHPDPSpace(dungeon);
    }
};

int main() {
    Solution solution;
    vector<vector<int>> dungeon = { {-2, -3, 3}, {-5, -10, 1}, {10, 30, -5} };
    cout << solution.calculateMinimumHP(dungeon) << endl;
    return 0;
}