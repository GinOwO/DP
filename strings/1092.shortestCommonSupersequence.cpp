#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 1092 - Shortest Common Supersequence
        Given two strings s1 and s2, return the shortest string that has both s1 and s2 as subsequences.  
        If multiple answers exist, you may return any of them.

        We'll do this similar to how we print the LCS. We populate the DP table.
        Then we start from dp[n][m] and go backwards, if its part of the lcs, then we add it once and decrement i and j both.
        Else we only add the character from the string whose pointer is being moved back.

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)
*/

class Solution {
public:
    int lcsDP(const string& s1, const string& s2, vector<vector<int>>& dp){
        int n=s1.size(), m=s2.size();

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                int ans = 0;
                if(s1[i-1]==s2[j-1]) ans = 1 + dp[i-1][j-1];
                else ans = max(dp[i-1][j], dp[i][j-1]);
                dp[i][j] = ans;
            }
        }
        return dp[n][m];
    }

    string shortestCommonSupersequence(const string& s1, const string& s2){
        int n=s1.size(), m=s2.size(); string lcs; 
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        lcs.resize(n+m-lcsDP(s1, s2, dp));
        int i=n, j=m, k=lcs.size()-1;

        while(i>0 && j>0){
            if(s1[i-1]==s2[j-1]){
                lcs[k--] = s1[i-1];
                i--; j--;
            }
            else if(dp[i-1][j]>dp[i][j-1]) lcs[k--] = s1[--i];
            else lcs[k--] = s2[--j];
        }
        while(i>0) lcs[k--] = s1[--i];
        while(j>0) lcs[k--] = s2[--j];
        return lcs;
    }
};

int main(){
    Solution s;
    string s1 = "abac", s2 = "cab";
    cout << s.shortestCommonSupersequence(s1, s2) << endl;
    return 0;
}