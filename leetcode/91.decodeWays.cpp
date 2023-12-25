#include<bits/stdc++.h>

using namespace std;

/*
    LeetCode 91 - Decode Ways
        Given string s with numbers, convert to letters based on alphabetical order, i.e 1->A, 2->B, ... 26->Z
        Return the number of ways to decode the string

        DP solution, base case is dp[n]=1 as empty string has 1 way to decode
        If s[i]=='0', then dp[i]=0 as 0 cannot be decoded
        Else dp[i]=dp[i+1] as s[i] can be decoded to a letter
        Then check if two digits can be decoded to a letter, if so, dp[i]+=dp[i+2]
        Return dp[0] as the number of ways to decode the string
*/

class Solution {
public:
    int numDecodingsDP(const string& s){
        int dp[103]={0}, n=s.size(); dp[n]=1;
        for(int i=n-1; i>=0; i--){
            if(s[i]=='0') dp[i] = 0;
            else dp[i]=dp[i+1];

            int k1 = s[i]-'0', k2 = -1;
            if(i+1<s.size()) k2 = k1*10 + (s[i+1]-'0');
            if((k1>0) && (k2>0 && k2<=26)) dp[i] += dp[i+2];
        }
        return dp[0];
    }

    int memo[101];
    int numDecodingsRec(const string& s, int i=0){ // DFS
        if(memo[i]!=-1) return memo[i];
        if(s[i]=='0') return 0;

        int k1 = s[i]-'0', k2 = -1, res=0;
        if(i+1<s.size()) k2 = k1*10 + (s[i+1]-'0');
        if(k1>0){
            res += numDecodingsRec(s, i+1);
            if(k2>0 && k2<=26) res += numDecodingsRec(s, i+2);
        }
        return memo[i]=res;
    }

    int numDecodings(const string& s) {
        // memset(memo, -1, 101*sizeof(int));
        // memo[s.size()]=1;
        return numDecodingsDP(s);
    }
};

int main(){
    Solution s;
    string str = "226";
    cout << s.numDecodings(str) << endl;
    return 0;
}