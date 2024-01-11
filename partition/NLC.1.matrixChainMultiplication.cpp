#include <bits/stdc++.h>

using namespace std;

/*
    Matrix Chain Multiplication
        A set of n-1 matrices are given in an array of size n.
        Let them be A(p,q), B(q,r), C(r,s), D(s,t) where p,q,r,s,t are the dimensions of the matrices.
        Then the array is {p,q,r,s,t} to represent the matrices {A,B,C,D}.
        The cost of multiplying two matrices A(p,q) and B(q,r) is p*q*r, it is the number of multiplications required for matrix multiplication.

        Find the minimum number of multiplications required to multiply all the matrices:
        Example, A(10, 20),B(20, 30),C(30,40) are the matrices, then (AB)C, A(BC) are the two ways to multiply them.
            For (AB)C:
                The cost of AB is 10*20*30 = 6000 | AB(10,30)
                The cost of (AB)C is 10*30*40 = 12000 | (AB)C(10,40)
                Total cost = 6000 + 12000 = 18000
            For A(BC):
                The cost of BC is 20*30*40 = 24000 | BC(20,40)
                The cost of A(BC) is 10*20*40 = 8000 | A(BC)(10,40)
                Total cost = 24000 + 8000 = 32000
            So, the minimum cost is 18000.

        We are basically taking the minimum of every possible parition in the recursion.

        In DP, we just go from bottom to top, and fill the table.
        i.e i=n-1=>1 and j=i+1=>n

        Answer is dp[1][n-1]

        Time Complexity: O(n^3), Space Complexity: O(n^2)
*/

#define int long long
class Solution {
public:
    int numberOfStepsDP(const vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for ( int i = n - 1; i >= 1; i-- ) {
            for ( int j = i + 1; j < n; j++ ) {
                int mn = 1e9;
                for ( int k = i; k < j; k++ )
                    mn = min(arr[i - 1] * arr[k] * arr[j] + dp[k + 1][j] + dp[i][k], mn);
                dp[i][j] = mn;
            }
        }
        return dp[1][n - 1];
    }

    int dfs(int i, int j, const vector<int>& arr, vector<vector<int>>& dp) {
        if ( i == j ) return 0;
        if ( dp[i][j] != -1 ) return dp[i][j];

        int mn = 1e9;
        for ( int k = i; k < j; k++ )
            mn = min(arr[i - 1] * arr[k] * arr[j] + dfs(k + 1, j, arr, dp)
                + dfs(i, k, arr, dp), mn);

        return dp[i][j] = mn;
    }

    int numberOfSteps(const vector<int>& arr) {
        // int n = arr.size();
        // vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        // return dfs(1, n-1, arr, dp);
        return numberOfStepsDP(arr);
    }
};

signed main() {
    Solution sl;
    vector<int> arr = { 1, 2, 3, 4, 3 };
    cout << sl.numberOfSteps(arr) << endl;
    return 0;
}