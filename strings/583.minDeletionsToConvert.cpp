#include<bits/stdc++.h>

using namespace std;

/*
    Leecode 583 - Delete Operation for Two Strings
        Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
        In one step, you can delete exactly one character in either string.

        Lets take 2 strings s1="sea" and s2="eat". To make them same, we need to delete "s" and "t" from s1 and s2 respectively.
        The LCS of s1 and s2 is "ea", so to convert s1 to the LCS, we need to delete "s" from the LCS, similarly for s2.
        Hence the answer is s1.size()+s2.size()-2*LCS(s1, s2).

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)

*/

class Solution {
public:
    int lcsDPSpace(const string& s1, const string& s2) {
        int n = s1.size(), m = s2.size();
        vector<int> dp(m + 1, 0), ndp(m + 1, 0);

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                if ( s1[i - 1] == s2[j - 1] ) ndp[j] = 1 + dp[j - 1];
                else ndp[j] = max(dp[j], ndp[j - 1]);
            }
            dp = ndp;
        }
        return dp[m];
    }

    int minDistance(const string& w1, const string& w2) {
        return w1.size() + w2.size() - 2 * lcsDPSpace(w1, w2);
    }
};

int main() {
    Solution s;
    string s1 = "sea", s2 = "eat";
    cout << s.minDistance(s1, s2) << endl;
    return 0;
}