#include<bits/stdc++.h>

using namespace std;

/*
    Rod/Log Cutting
        Given a log/rod of length N, an array of length N, with each index i having a price of cutting the log at that index.(1-indexed)
        That is, if length of rod is 1, its price is equal to price[1], if length is 2, its price is equal to price[2] and so on.
        Find the maximum price that can be obtained by cutting the rod in any way.

        (Space Optimized only)
        Since question has given 1-indexed price array, we will make a new array p of size N+1, where p[i] = price[i-1] and p[0] = 0
        This is done to make it 0-indexed and also to make p[0] = 0, as we cannot cut a log of length 0 and the price of cutting a log of length 0 is 0.

        dp[0] = 0 as base case
        We go from i=1->N and for each i, we go from j=i->N and update dp[j] as max(dp[j], p[i]+dp[j-i])
        This is because we can either not cut the log at all, or cut it at index i, and then cut the remaining log of length j-i.
        
        For i=1 to N
            For j=i to N
                dp[j] = max(dp[j], p[i]+dp[j-i])
        
        Answer = dp[N]

        Time Complexity: O(N^2), Space Complexity: O(N)
*/

class Solution{
public:
    int cutRodDPSpace(int price[], int N){
        vector<int> dp(N+1, 0), p{0};
        for(int i=0; i<N; i++) p.push_back(price[i]);
        
        for(int i=1; i<=N; i++)
            for(int j=i; j<=N; j++)
                dp[j] = max(dp[j], p[i]+dp[j-i]);
        return dp[N];
    }

    int cutRodDP(int price[], int N){
        vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
        for(int n=0; n<=N; n++) dp[0][n] = n*price[0];
        
        for(int i=1; i<N; i++){
            for(int n=1; n<=N; n++){
                dp[i][n] = dp[i-1][n];
                if(n>=i+1) dp[i][n] = max(dp[i][n], price[i] + dp[i][n-i-1]);
            }
        }
        return dp[N-1][N];
    }

    int cutRodRec(int i, int n, int* price, vector<vector<int>>& memo){
        if(i==0) return n*price[0];
        if(memo[i][n]!=-1) return memo[i][n];
        
        int notCut = cutRodRec(i-1, n, price, memo), cut=-1e9;
        if(n>=i+1) cut = price[i] + cutRodRec(i, n-i-1, price, memo);
        
        return memo[i][n] = max(notCut, cut);
    }

    int cutRod(int price[], int n){
        // vector<vector<int>> memo(n+1, vector<int>(n+1, -1));
        // return cutRodRec(n-1, n, price, memo);
        return cutRodDPSpace(price, n);
    }
};

int main(){
    Solution s;
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20};
    cout << s.cutRod(price, 8) << endl;
    return 0;
}