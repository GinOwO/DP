#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 1048 - Longest String Chain
        Given a list of words, each word consists of English lowercase letters.
        Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.
        For example, "abc" is a predecessor of "abac".
        A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, 
        where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
        Return the longest possible length of a word chain with words chosen from the given list of words.

        Intution:
        We sort the words by length, and then we use the same logic as LIS, but instead of comparing the values, we compare the strings.
        i.e if s1 is a predecessor of s2, then we can add a character to s1 to make it equal to s2.
        So we just check if s1 is a predecessor of s2, and if it is, then we update dp[i] = max(dp[i], 1+dp[j])
        Answer is max(dp[i])

        Time: O(n^2), Space: O(n)
*/

class Solution {
public:
    inline bool compare(const string& s1, const string& s2){
        int m=s1.size(), n=s2.size(), i=0, j=0;
        if(m!=n+1) return false;

        while(i<m){
            if(s1[i]==s2[j]) j++;
            i++;
        }
        return i==m && j==n;
    }

    int lengthOfLISDP(vector<string>& arr){
        int n = arr.size(), mx=1, idx=0;
        vector<int> dp(n, 1);

        sort(arr.begin(), arr.end(), [](auto&s1, auto&s2){return s1.size()<s2.size();});

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++)
                if(compare(arr[i],arr[j])) dp[i]=max(dp[j]+1, dp[i]);
            mx = max(dp[i], mx);
        }

        return mx;
    }

    int longestStrChain(vector<string>& words) {
        return lengthOfLISDP(words);
    }
};

int main(){
    Solution sol;
    vector<string> arr = {"a","b","ba","bca","bda","bdca"};
    cout<<sol.longestStrChain(arr)<<endl;
    return 0;
}