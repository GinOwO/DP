#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 44 - Wildcard Matching
        Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
            '?' Matches any single character.
            '*' Matches any sequence of characters (including the empty sequence).
        The matching should cover the entire input string (not partial).

        Base Case:
            dp[0][0] = 1
            dp[0][j] = (p[j]=='0') for k=1..j for j=1..m, which means that if the pattern is all '*' then it matches the empty string

        In the pattern a '?' is the same as a normal match, in which case we move both pointers backward (as we are starting from the end)
        In the pattern a '*' can be either a match or skip, in which case we take the OR of the two cases:
            Skip: (i, j) -> (i, j-1), i.e move pattern pointer backward while keeping string pointer at the same position
            Match: (i, j) -> (i-1, j), i.e move string pointer backward while keeping pattern pointer at the same position

        The DP solution is as follows:

        DP[n+1][m+1] = {false}
        For i=1->n
            For j=1->m
                If (p[j] == '?') OR (s[i] == p[j]): then dp[i][j] = dp[i-1][j-1]
                If (p[j] == '*'): then dp[i][j] = dp[i][j-1] || dp[i-1][j]

        Answer is dp[n][m]

        Alternatively we can use two 1D arrays to store the previous and current rows of the DP table, which reduces the space complexity to O(m)

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)
*/

class Solution {
public:
    bool isMatchDP(const string& s, const string& p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = 1;
        for ( int j = 1; j <= m; j++ ) {
            dp[0][j] = true;
            for ( int k = 1; dp[0][j] && k <= j; k++ )
                if ( p[k - 1] != '*' ) dp[0][j] = false;
        }

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                if ( p[j - 1] == '?' || s[i - 1] == p[j - 1] ) dp[i][j] = dp[i - 1][j - 1];
                if ( p[j - 1] == '*' ) dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
        return dp[n][m];
    }

    bool isMatchRec(int i, int j, const string& s, const string& p, vector<vector<int>>& dp) {
        if ( i < 0 && j < 0 ) return 1;
        if ( i >= 0 && j < 0 ) return 0;
        if ( i < 0 && j >= 0 ) {
            for ( int k = 0; k <= j; k++ ) if ( p[k] != '*' ) return false;
            return true;
        }
        if ( dp[i][j] != -1 ) return dp[i][j];

        bool res = false;

        if ( p[j] == '?' || s[i] == p[j] ) res = isMatchRec(i - 1, j - 1, s, p, dp);
        if ( p[j] == '*' ) res = isMatchRec(i, j - 1, s, p, dp) || isMatchRec(i - 1, j, s, p, dp);

        return dp[i][j] = res;
    }

    bool isMatch(const string& s, const string& p) {
        // int n = s.size(), m = p.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return isMatchRec(n-1, m-1, s, p, dp);
        return isMatchDP(s, p);
    }
};

int main() {
    Solution s;
    cout << s.isMatch("aa", "a") << endl;
    cout << s.isMatch("aa", "*") << endl;
    cout << s.isMatch("cb", "?a") << endl;
    return 0;
}