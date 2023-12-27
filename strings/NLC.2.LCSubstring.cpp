#include<bits/stdc++.h>

using namespace std;

/*
    Longest Common Substring
        Given two strings s1 and s2, find the length of their longest common substring.
        If there is no common substring, return 0.

        Same logic as LCS, but when s1[i-1]!=s2[j-1], we set dp[i][j]=0 as we are looking for a substring, not a subsequence.
        i.e We skip over the skipping over the non equal characters part

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)

*/

class Solution{
public:
    int lcSubstringDPSpace(const string& s1, const string& s2){
        int n=s1.size(), m=s2.size(), ans = 0;
        vector<int> ndp(m+1, 0), dp(m+1, 0);

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                ndp[j] = 0;
                if(s1[i-1]==s2[j-1]){
                    ndp[j] = 1 + dp[j-1];
                    ans = max(ans, ndp[j]);
                }
            }
            dp = ndp;
        }
        return ans;
    }

    int lcSubstringDP(const string& s1, const string& s2){
        int n=s1.size(), m=s2.size(), ans = 0;
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                dp[i][j] = 0;
                if(s1[i-1]==s2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    ans = max(ans, dp[i][j]);
                }
            }
        }
        return ans;
    }

    int LCSubstring(const string& s1, const string& s2){
        // return lcSubstringDP(s1, s2);
        return lcSubstringDPSpace(s1, s2);
    }
};

int main(){
    Solution s;
    string s1 = "calbdoe", s2 = "aclbde";
    cout << s.LCSubstring(s1, s2) << endl;
    return 0;
}