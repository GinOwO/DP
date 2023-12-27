#include<bits/stdc++.h>

using namespace std;

/*
    Leecode 516 - Longest Palindromic Subsequence
        Given a string, find the length of its longest palindromic subsequence.
        If there is no palindromic subsequence, return 0.

        Essentially its just LCS of the string and its reverse.

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)
*/

class Solution {
public:
    int lcsDPSpace(const string& s1, const string& s2){
        int n=s1.size(), m=s2.size();
        vector<int> dp(m+1, 0), ndp(m+1, 0);

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(s1[i-1]==s2[j-1]) ndp[j] = 1 + dp[j-1];
                else ndp[j] = max(dp[j], ndp[j-1]);
            }
            dp = ndp;
        }
        return dp[m];
    }

    int longestPalindromeSubseq(const string& s) {
        return lcsDPSpace(s, string(s.rbegin(), s.rend()));
    }
};

int main(){
    Solution s;
    string s1 = "bbbab";
    cout << s.longestPalindromeSubseq(s1) << endl;
    return 0;
}