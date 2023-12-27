#include<bits/stdc++.h>

using namespace std;

/*
    Leecode 1312 - Minimum Insertion Steps to Make a String Palindrome
        Given a string s. In one step you can insert any character at any index of the string.
        Return the minimum number of steps to make s palindrome.
        A Palindrome String is one that reads the same backward as well as forward.

        Assume the string is abcda, then LPS of the string is aca. To make it a palindrome, we insert b and d as follows:
            abcda -> abcdba -> abdcdba
        Essentially its just size of the string minus LPS of the string, i.e s.size()-LPS(s).
        This is because LPS gives us the length of the longest palindromic part, so substracting gives the longest non-palindromic part.
        And to make the string a palindrome, we need to insert the non-palindromic part in reverse order.

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

    int minInsertions(const string& s) {
        return s.size()-longestPalindromeSubseq(s);
    }
};

int main(){
    Solution s;
    string s1 = "zzazz";
    cout << s.minInsertions(s1) << endl;
    return 0;
}