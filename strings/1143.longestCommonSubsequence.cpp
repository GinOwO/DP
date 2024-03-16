#include<bits/stdc++.h>

using namespace std;

/*
    LeetCode 1143 - Longest Common Subsequence
        Given two strings s1 and s2, find the length of their longest common subsequence.
        If there is no common subsequence, return 0.

        DP[n+1][m+1]
        DP solution, base case is dp[n][m]=0 as empty string has no common subsequence
        If s1[i]==s2[j], then we take the character and add 1 to both i and j: (i, j) -> (i+1, j+1)
        Else we take the maximum of (i+1, j) and (i, j+1): (i, j) -> (i+1, j) or (i, j+1)

        For i=n-1 to 0
            For j=m-1 to 0
                If s1[i]==s2[j], dp[i][j] = 1 + dp[i+1][j+1]
                Else dp[i][j] = max(dp[i+1][j], dp[i][j+1])

        Answer = dp[0][0]

        Alternatively as only two previous states are required, we can use two vectors instead of a 2D array (1 for past states, 1 for current state)

        Also we can go from i=1->n and j=1->m as follows:

        For i=1 to n
            For j=1 to m
                If s1[i-1]==s2[j-1], dp[i][j] = 1 + dp[i-1][j-1]
                Else dp[i][j] = max(dp[i-1][j], dp[i][j-1])

        Time: O(n*m), Space: O(n*m), Space Optimized: O(m)
*/

class Solution {
public:
    int lcsDPSpace( const string& s1, const string& s2 ) {
        int n = s1.size( ), m = s2.size( );
        vector<int> dp( m + 1, 0 ), ndp( m + 1, 0 );

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                if ( s1 [ i - 1 ] == s2 [ j - 1 ] ) ndp [ j ] = 1 + dp [ j - 1 ];
                else ndp [ j ] = max( dp [ j ], ndp [ j - 1 ] );
            }
            dp = ndp;
        }
        return dp [ m ];
    }

    int lcsDP( const string& s1, const string& s2 ) {
        int n = s1.size( ), m = s2.size( );
        vector<vector<int>> dp( n + 1, vector<int>( m + 1, 0 ) );

        for ( int i = 1; i <= n; i++ ) {
            for ( int j = 1; j <= m; j++ ) {
                int ans = 0;
                if ( s1 [ i - 1 ] == s2 [ j - 1 ] ) ans = 1 + dp [ i - 1 ][ j - 1 ];
                else ans = max( dp [ i - 1 ][ j ], dp [ i ][ j - 1 ] );
                dp [ i ][ j ] = ans;
            }
        }
        return dp [ n ][ m ];
    }

    int lcsRec( int i, int j, const string& s1, const string& s2, vector<vector<int>>& dp ) {
        if ( i >= s1.size( ) || j >= s2.size( ) ) return 0;
        if ( dp [ i ][ j ] != -1 ) return dp [ i ][ j ];

        int ans = 0;
        if ( s1 [ i ] == s2 [ j ] ) ans = 1 + lcsRec( i + 1, j + 1, s1, s2, dp );
        else ans = max( lcsRec( i + 1, j, s1, s2, dp ), lcsRec( i, j + 1, s1, s2, dp ) );
        return dp [ i ][ j ] = ans;
    }

    int longestCommonSubsequence( const string& s1, const string& s2 ) {
        // vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));
        // return lcsRec(0, 0, s1, s2, dp);
        // return lcsDPSpace(s1, s2);`
        return lcsDP( s1, s2 );
    }
};

int main( ) {
    Solution s;
    string s1 = "abcde", s2 = "ace";
    cout << s.longestCommonSubsequence( s1, s2 ) << endl;
    return 0;
}