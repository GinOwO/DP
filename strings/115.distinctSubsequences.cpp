#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 115 - Distinct Subsequences
        Given two strings s(n) and t(m), return the number of distinct subsequences of s which equals t.
        Example: s = "babgbag", t = "bag", ans = 5

        We'll just recurse over the strings and use a pick/not pick logic.
        We'll always consider the not pick case, and if the characters match, we'll consider the pick case as well.
        Not pick: (i, j) -> (i-1, j)
        Pick: (i, j) -> (i-1, j-1)

        Answer is the sum of both cases. We start from n-1 and m-1

        For DP, dp[i][j] = dp[i-1][j] + (s[i]==t[j])*dp[i-1][j-1]. Base case is dp[i][0]=1 for all i
        We can optimize the space to O(m) by using a 1D array.
        As the right values are not being used after j passes over them, we'll go j=m->1 instead of j=1->m.
        So, we get base case as dp[0] = 1 and the loop becomes:

        For i=1->n:
            for j=m->1:
                if(s[i]==t[j]) dp[j] += dp[j-1]

        Answer is in dp[m]

        Note: For leetcode, it can produce an overflow issue with dp table, even if we use long long.
        Unsigned long long can work, but just use this condition instead:
            if(s[i]==t[j] && dp[i][j]<INT_MAX-dp[i-1][j-1])

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)
*/

class Solution {
public:
    int numDistinctDPSpace(const string& s, const string& t) {
        int n = s.size(), m = t.size();
        vector<int> dp(m + 1, 0); dp[0] = 1;

        for ( int i = 1; i <= n; i++ )
            for ( int j = m; j >= 1; j-- )
                if ( s[i - 1] == t[j - 1] ) dp[j] += dp[j - 1];

        return dp[m];
    }

    int numDistinctDP(const string& s, const string& t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for ( auto& v : dp ) v[0] = 1;

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                dp[i][j] = dp[i - 1][j];
                if ( s[i - 1] == t[j - 1] ) dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return dp[n][m];
    }

    int numDistinctRec(int i, int j, const string& s, const string& t, vector<vector<int>>& dp) {
        if ( i < 0 || j < 0 ) return j < 0;
        if ( dp[i][j] != -1 ) return dp[i][j];

        int notTake = numDistinctRec(i - 1, j, s, t, dp), take = 0;
        if ( s[i] == t[j] ) take = numDistinctRec(i - 1, j - 1, s, t, dp);

        return dp[i][j] = notTake + take;
    }

    int numDistinct(const string& s, const string& t) {
        // int n = s.size(), m = t.size();
        // vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        // return numDistinctRec(s.size()-1, t.size()-1, s, t, dp);
        return numDistinctDPSpace(s, t);
    }
};

int main() {
    Solution s;
    string s1 = "babgbag", s2 = "bag";
    cout << s.numDistinct(s1, s2) << endl;
    return 0;
}