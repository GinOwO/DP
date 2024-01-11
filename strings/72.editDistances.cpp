#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 72 - Edit Distance
        Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
        You have the following three operations permitted on a word:
            Insert a character
            Delete a character
            Replace a character

        If the characters don't match just take the minimum of the 3 cases:
            Insert: (i, j) -> (i, j-1)
            Delete: (i, j) -> (i-1, j)
            Replace: (i, j) -> (i-1, j-1)

        Else take the diagonal value: (i, j) -> (i-1, j-1)

        Answer is dp[0][0]

        Time: O(n*m), Space: O(n*m)
*/

class Solution {
public:
    int minDistanceSpace(const string& s, const string& t) {
        const int m = s.size(), n = t.size();

        vector<int> dp(n + 1, 0), ndp(n + 1, 0);
        for ( int i = 0; i <= n; i++ ) dp[i] = i; // Base case

        for ( int i = 1; i <= m; i++ ) {
            ndp[0] = i; // Base case
            for ( int j = 1; j <= n; j++ ) {
                if ( s[i - 1] == t[j - 1] ) ndp[j] = dp[j - 1];
                else ndp[j] = 1 + min(dp[j], min(ndp[j - 1], dp[j - 1]));
            }
            dp = ndp;
        }
        return dp[n];
    }

    int minDistance(const string& s, const string& t) {
        const int m = s.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for ( int i = 0; i <= n; i++ ) dp[m][i] = n - i;
        for ( int i = 0; i <= m; i++ ) dp[i][n] = m - i;

        for ( int i = m - 1; i >= 0; i-- )
            for ( int j = n - 1; j >= 0; j-- )
                if ( s[i] == t[j] ) dp[i][j] = dp[i + 1][j + 1];
                else dp[i][j] = 1 + min(dp[i + 1][j + 1], min(dp[i][j + 1], dp[i + 1][j]));

        return dp[0][0];
    }
};

int main() {
    Solution s;
    string s1 = "sea", s2 = "eat";
    cout << s.minDistance(s1, s2) << endl;
    return 0;
}