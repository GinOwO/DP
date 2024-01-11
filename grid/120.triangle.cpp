#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

/*
    Leetcode 120 - Triangle
        Triangle Slide Down - Minimum cost path
        Two vectors: One for current row(ndp), and prev row(dp)
        For each row take min of two adjacent elements from prev row
        Time: O(n^2), Space: O(n)
*/

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(), m = triangle.back().size(), l, r;
    vector<int> dp(m, 0), ndp(m, 0);
    for ( int i = n - 1; i >= 0; i-- ) {
        for ( int j = i; j >= 0; j-- )
            ndp[j] = triangle[i][j] + ( i == n - 1 ? 0 : min(dp[j], dp[j + 1]) );
        dp = ndp;
    }
    return dp[0];
}

int main() {
    vector<vector<int>> triangle = { {2},{3,4},{6,5,7},{4,1,8,3} };
    cout << minimumTotal(triangle) << endl;
    return 0;
}