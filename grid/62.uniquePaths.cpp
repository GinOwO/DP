#include<bits/stdc++.h>

using namespace std;

/*
    LeetCode 62 - Unique Paths
        Given a grid of size m*n, find the number of unique paths from top left to bottom right
        Can only move right or down

        Since we can only move right or down, first row and first column can only be reached in 1 way, so dp[i][0]=dp[0][j]=1
        Then for (i, j) number of ways to reach is dp[i][j] = dp[i-1][j] + dp[i][j-1]
        But we can optimize space by using a single array of size n+1, as the previous row automatically becomes the current row.
        Hence dp[j] = dp[j] + dp[j-1], where i=2->m, j=1->n || inclusive. We start from i=2 as we have already filled i=1 with all 1s.
        Base case is dp[0]=0, as on empty grid we cannot reach anywhere

        Time: O(m*n), Space: O(n)
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n + 1, 1); dp[0] = 0;
        for ( int i = 2; i <= m; i++ )
            for ( int j = 1; j <= n; j++ )
                dp[j] += dp[j - 1];
        return dp[n];
    }
};

int main() {
    Solution s;
    cout << s.uniquePaths(3, 7) << endl;
    return 0;
}