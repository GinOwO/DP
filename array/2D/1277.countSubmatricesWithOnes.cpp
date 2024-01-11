#include<bits/stdc++.h>

using namespace std;

/*
    LeetCode: 1277. Count Square Submatrices with All Ones
        Given a 2d array of size mxn, find the number of square submatrices with all ones.

        Logic is that, each single element is a square matrix of size 1x1, so we can count them(assuming value is 1 in that cell).
        Now this will be the case for the first row and first column, so they will be essentially copied as it is.

        Now by definition a square needs equal sides, and as we have already formed the square of size 1x1, we will now check for 2x2.
        Now, its already the base case that if a cell is 1, it forms a square of 1x1, so it should increase the count there.
        But, it also means that the number of squares which can be formed with that cell acting as its bottom right corner is 1+min(top, left, diagonally top left).
        i.e for (i, j) and arr[i][j] = 1, the number of squares which can be formed with (i, j) as bottom right corner is
            1+min(arr[i-1][j], arr[i][j-1], arr[i-1][j-1]).

        Doing this for all cells, we will get the matrix where a single cell at (i, j) will have the number of squares which can be formed with (i, j) as bottom right corner.
        Hence, we can just add all the elements of the matrix to get the answer.

        Time: O(m*n), Space: O(m*n)

        Note that we can just reuse the given input matrix to store the number of squares which can be formed with (i, j) as bottom right corner.
        As it already satisfies the base cases of first row and first column being the same as input(as it itself is the input), we will start from (1, 1) and not (0, 0).

        This reduces Auxiliary space to O(1).
*/


class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for ( int i = 1; i <= m; i++ ) {
            for ( int j = 1; j <= n; j++ ) {
                if ( matrix[i - 1][j - 1] ) dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                else dp[i][j] = 0;
            }
        }
        return accumulate(dp.begin(), dp.end(), 0, [](const int a, const vector<int>& v) {
            return a + accumulate(v.begin(), v.end(), 0);
            });
    }
};

int main() {
    Solution s;
    vector<vector<int>> matrix { {0,1,1,1},{1,1,1,1},{0,1,1,1} };
    cout << s.countSquares(matrix) << endl;
    return 0;
}