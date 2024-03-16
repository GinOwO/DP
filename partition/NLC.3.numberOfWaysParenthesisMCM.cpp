#include <bits/stdc++.h>

using namespace std;

class Solution {
    int numberOfWaysParenthesisDP( const int n ) {
        vector<vector<int>> DP( n + 1, vector<int>( n + 1, 0 ) );
        for ( int i = 0; i <= n; i++ ) DP [ i ][ i ] = 1;

        for ( int i = n - 1; i >= 0; i-- ) {
            for ( int j = i + 1; j <= n; j++ ) {
                for ( int k = i; k < j; k++ ) {
                    DP [ i ][ j ] += DP [ i ][ k ] * DP [ k + 1 ][ j ];
                }
            }
        }

        return DP [ 0 ][ n ];
    }

    int numberOfWaysParenthesisRec( const int i, const int j ) {
        if ( i == j ) return 1;

        int ans = 0;
        for ( int k = i; k < j; k++ ) {
            ans += numberOfWaysParenthesisRec( i, k ) * numberOfWaysParenthesisRec( k + 1, j );
        }

        return ans;
    }
public:
    int numberOfWaysParenthesis( int n ) {
        return numberOfWaysParenthesisDP( n - 1 );
    }
};

int main( ) {
    Solution sol;
    for ( int i = 1; i <= 5; i++ )
        cout << i << '\t' << sol.numberOfWaysParenthesis( i ) << '\n';
    return 0;
}