#include<bits/stdc++.h>

using namespace std;


/*
    Leetcode 931 - Minimum Falling Path Sum
        Minimum cost path - Square matrix of size n
        Two vectors: One for current row(ndp), and prev row(dp), size of both = n+2
        n+2 to ignore boundary conditions. Set first and last to sentinel value
        For each row(1<=i,j<=n) take min(dp[j-1], dp[j], dp[j+1]) and add to matrix[i][j] and store in ndp[j]
        Time: O(n^2), Space: O(n)
*/

int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> dp(n + 2, 0); dp[0] = dp[n + 1] = 1e9;
    vector<int> ndp(dp);
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= n; j++ ) {
            ndp[j] = matrix[i - 1][j - 1] + min(dp[j - 1], min(dp[j], dp[j + 1]));
        }
        dp = ndp;
    }
    return *min_element(dp.begin() + 1, dp.end() - 1);
}

int main() {
    vector<vector<int>> matrix = { {2,1,3},{6,5,4},{7,8,9} };
    cout << minFallingPathSum(matrix) << endl;
    return 0;
}