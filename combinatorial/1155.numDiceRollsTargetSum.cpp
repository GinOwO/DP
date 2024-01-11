#include<bits/stdc++.h>

using namespace std;

/*
    1155. Number of Dice Rolls With Target Sum
        n dice, k faces, return ways to get target sum

        DP[n+1][target+1]
        Base Case is DP[0][0] = 1 as n==0 and target==0 means we have 1 way to get target sum
        For each dice, we will go through all possible targets. Each face also has k possible values, meaning a sum of 1 to k
        So, for each dice, we will go through all possible faces and all possible targets

        For i=1 to n
            For t=1 to target
                For x=1 to k
                    if t>=x
                        DP[i][t] += DP[i-1][t-x]

        We can eliminate the if condition by starting the loop from x=t to k

        For i=1 to n
            For t=1 to target
                For x=t to k
                    DP[i][t] += DP[i-1][t-x]

        As we are using i and i-1, we can instead use two 1D arrays to store the values of dp[i] and dp[i-1]
        This will reduce the space complexity from O(n*target) to O(target)

        For i=1 to n
            For t=1 to target
                For x=t to k
                    ndp[t] += dp[t-x]
            dp = ndp

        Time: O(n*target*k), Space: O(target)
*/

class Solution {
    const int MOD = 1e9 + 7;
public:
    int numRollsToTargetDPSpace(const int n, const int k, const int target) {
        // vector<int> dp(target+1, 0), ndp(target+1, 0);
        int dp[1001] = { 0 }, ndp[1001] = { 0 };
        dp[0] = 1;

        for ( int i = 1; i <= n; i++ ) {
            for ( int t = 1; t <= target; t++ ) {
                int q = min(k, t); ndp[t] = 0;
                for ( int x = 1; x <= q; x++ )
                    ndp[t] = ( ndp[t] + ( dp[t - x] % MOD ) ) % MOD;
            }
            memcpy(dp, ndp, 1001 * sizeof(int));
        }
        return ndp[target];
    }

    int numRollsToTargetDP(const int n, const int k, const int target) {
        int dp[31][1001] = { 0 };
        dp[0][0] = 1;

        for ( int i = 1; i <= n; i++ ) {
            for ( int t = 1; t <= target; t++ ) {
                int ans = 0;
                for ( int x = 1; x <= k; x++ ) {
                    if ( t >= x ) ans = ( ans + ( dp[i - 1][t - x] % MOD ) ) % MOD;
                }
                dp[i][t] = ans;
            }
        }
        return dp[n][target];
    }

    int numRollsToTargetRec(const int& n, const int& k, const int& target, vector<vector<int>>& memo) {
        if ( n == 0 ) return ( target == 0 );
        if ( memo[n][target] != -1 ) return memo[n][target];
        int ans = 0;

        for ( int x = 1; x <= k; x++ )
            if ( target >= x ) ans = ( ans + ( numRollsToTargetRec(n - 1, k, target - x, memo) % MOD ) ) % MOD;
        return memo[n][target] = ans;
    }

    int numRollsToTarget(int n, int k, int target) {
        // vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
        // return numRollsToTargetRec(n, k, target, dp);
        // return numRollsToTargetDP(n, k, target);
        return numRollsToTargetDPSpace(n, k, target);
    }
};

int main() {
    Solution s;
    cout << s.numRollsToTarget(1, 6, 3) << endl;
    cout << s.numRollsToTarget(2, 6, 7) << endl;
    cout << s.numRollsToTarget(2, 5, 10) << endl;
    cout << s.numRollsToTarget(1, 2, 3) << endl;
    cout << s.numRollsToTarget(30, 30, 500) << endl;
    return 0;
}