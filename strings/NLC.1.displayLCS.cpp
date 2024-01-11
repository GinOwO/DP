#include<bits/stdc++.h>

using namespace std;

/*
    Display LCS
        Given two strings s1 and s2, find the longest common subsequence between them.
        If there is no common subsequence, return empty string.

        Use same logic as finding length of LCS, store the resulting dp table.

        Then start from dp[n][m] and go backwards,
        If s1[i-1]==s2[j-1], then add s1[i-1] to the answer and go to dp[i-1][j-1], i.e (i, j, s) -> (i-1, j-1, s+s1[i-1])
        Else go to the maximum of dp[i-1][j] and dp[i][j-1], i.e (i, j, s) -> (i-1, j, s) or (i, j-1, s)

        When i==0 or j==0 stop the loop as lcs has been found.

        Time: O(n*m), Space: O(n*m)
*/

class Solution {
public:
    int lcsDP(const string& s1, const string& s2, vector<vector<int>>& dp) {
        int n = s1.size(), m = s2.size();

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                int ans = 0;
                if ( s1[i - 1] == s2[j - 1] ) ans = 1 + dp[i - 1][j - 1];
                else ans = max(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] = ans;
            }
        }
        return dp[n][m];
    }

    string printLCS(const string& s1, const string& s2) {
        int n = s1.size(), m = s2.size(); string lcs;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        lcs.resize(lcsDP(s1, s2, dp));
        int i = n, j = m, k = lcs.size() - 1;

        while ( i > 0 && j > 0 ) {
            if ( s1[i - 1] == s2[j - 1] ) {
                lcs[k--] = s1[i - 1];
                i--; j--;
            }
            else if ( dp[i - 1][j] > dp[i][j - 1] ) i--;
            else j--;
        }
        return lcs;
    }
};

int main() {
    Solution s;
    string s1 = "calbde", s2 = "alcde";
    cout << s.printLCS(s1, s2) << endl;
    return 0;
}