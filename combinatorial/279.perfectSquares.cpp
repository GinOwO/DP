#include <bits/stdc++.h>

using namespace std;

/*
    LeetCode 279. Perfect Squares
        Given an integer n, return the least number of perfect square numbers that sum to n.

        We use a simple DFS approach to solve this problem. We start from n and subtract all the perfect squares less than n.
        We take the minimum of all the possible combinations and return the result after adding 1.
        The 1 is added to indicate that we have used one perfect square number in the current combination.

        Time: O(n*sqrt(n)), Space: O(n)
*/

class Solution {
public:
    int numSquaresDP(int N) {
        vector<int> dp(N + 1, 0);

        for ( int n = 1; n <= N; n++ ) {
            dp[n] = n;
            for ( int i = 1; i * i <= n; i++ ) {
                dp[n] = min(dp[n], dp[n - i * i]);
            }
            dp[n]++;
        }

        return dp[N];
    }

    int numSquaresRec(int n, vector<int>& dp) {
        if ( n == 0 ) return 0;
        if ( dp[n] != -1 ) return 1 + dp[n];

        dp[n] = n;
        for ( int i = 1; i * i <= n; i++ ) {
            dp[n] = min(dp[n], numSquaresRec(n - i * i, dp));
        }
        return 1 + dp[n];
    }

    int numSquares(int n) {
        // vector<int> dp(n+1, -1);
        // return numSquaresRec(n, dp);
        return numSquaresDP(n);
    }
};

int main() {
    Solution sol;
    cout << sol.numSquares(12) << endl;
    cout << sol.numSquares(13) << endl;
    return 0;
}