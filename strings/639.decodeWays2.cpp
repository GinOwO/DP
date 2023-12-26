#include<bits/stdc++.h>

using namespace std;
/*
    LeetCode 639 - Decode Ways II
        Given string s with numbers and *, convert to letters based on alphabetical order, i.e 1->A, 2->B, etc
        * represents wildcard, can be any number from 1 to 9
        Return the number of ways to decode the string

        DP solution, base case is dp[n]=1 as empty string has 1 way to decode
        If s[i]=='0', then dp[i]=0 as 0 cannot be decoded. We go from i= n-1 => 0 | inclusive
        
        If s[i] is a * then it can be decoded to 9 letters, so dp[i] += 9 * dp[i+1]
            If s[i+1] is a * then (s[i],s[i+1]) can be 15 letters from 11 to 26 => 26-11 = 15. 
                Hence dp[i] = 15 * dp[i+2]
            Else s[i+1] is a digit. Then the * in s[i] can either be 1 or 2, 
                so dp[i] += (s[i+1]>='7'?1:2) * dp[i+2]:

                As if its 1<=s[i]<=6 then * can be 1 or 2, i.e 11 to 16 or 21 to 26, so 2 ways to decode
                Else if its 7<=s[i]<=9 then * can only be 1, i.e 17 to 19, so 1 way to decode
        
        If s[i] is not a * then its just a single letter, so dp[i] += dp[i+1]
            If s[i+1] is not a *, then its a digit and (s[i],s[i+1]) can be decoded to
                letters from 10 to 26, if yes then do dp[i] += dp[i+2]

            Else if s[i+1] is a *, then two possibilities depending on value of s[i]
                If s[i] is 1, then * can be 1 to 9, i.e 11 to 19, so dp[i] += 9 * dp[i+2]
                Else if s[i] is 2, then * can be 1 to 6, i.e 21 to 26, so dp[i] += 6 * dp[i+2]
            
        Alternatively as only two previous states are required, we can use three variables instead of an array (2 for past states: dp[i+1], dp[i+2], 1 for current state: dp[i])

        Time: O(n), Space: O(1)
*/

class Solution {
    const int MOD = 1e9+7;
public:
    int numDecodingsDP(const string& s){
        long long n=s.size(), c=1, p1=0, p2=0;

        for(int i=n-1; i>=0; i--){
            p2=p1; p1=c; c=0;

            if(s[i]=='0') continue;
            if(s[i] == '*'){
                c = (c + 9*(p1%MOD))%MOD;
                if(i+1<n){
                    if(s[i+1]!='*') c = (c + (s[i+1]>='7'?1:2)*(p2%MOD))%MOD;
                    else c = (c + 15*(p2%MOD))%MOD;
                }
            }
            else{
                c = (c + p1%MOD)%MOD;
                if(i+1<n){
                    int k = -1;
                    if(s[i+1]!='*') k = (s[i]-'0')*10 + s[i+1]-'0';
                    if(10<=k && k<=26)
                        c = (c + (p2%MOD))%MOD;
                    else if(k==-1 && s[i]=='1')
                        c = (c + 9*(p2%MOD))%MOD;
                    else if(k==-1 && s[i]=='2')
                        c = (c + 6*(p2%MOD))%MOD;
                }
            }
        }
        
        return c;
    }

    long long numDecodingsRec(const string& s, int i, vector<long long>& memo){ // DFS
        if(i>s.size() || s[i]=='0') return 0;
        if(memo[i]!=-1) return memo[i];

        long long res = 0;

        if(s[i] == '*'){
            res = (res + 9 * numDecodingsRec(s, i+1, memo)%MOD)%MOD;
            if(i+1<s.size()){
                if(s[i+1]!='*') res = (res + (s[i+1]>='7'?1:2)*(numDecodingsRec(s, i+2, memo)%MOD))%MOD;
                else res = (res + 15 * (numDecodingsRec(s, i+2, memo)%MOD))%MOD;
            }
        }
        else{
            res = (res + numDecodingsRec(s, i+1, memo)%MOD)%MOD;
            if(i+1<s.size()){
                int k = -1;
                if(s[i+1]!='*') k = (s[i]-'0')*10 + s[i+1]-'0';
                if(10<=k && k<=26)
                    res = (res + numDecodingsRec(s, i+2, memo)%MOD)%MOD;
                else if(k==-1 && s[i]=='1')
                    res = (res + 9 * (numDecodingsRec(s, i+2, memo)%MOD))%MOD;
                else if(k==-1 && s[i]=='2')
                    res = (res + 6 * (numDecodingsRec(s, i+2, memo)%MOD))%MOD;
            }
        }

        return memo[i]=res;
    }

    int numDecodings(const string& s) {
        // vector<long long> memo(s.size()+1, -1); 
        // memo[s.size()] = 1;
        // return numDecodingsMemo(s, 0, memo);
        return numDecodingsDP(s);
    }
};

int main(){
    string str = "7*9*3*6*3*0*5*4*9*7*3*7*1*8*3*2*0*0*6*";
    cout << Solution().numDecodings(str) << endl;
    return 0;
}