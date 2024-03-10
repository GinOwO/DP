#include <bits/stdc++.h>

using namespace std;

/*
    Given a number n, find the number of integer partitions of n.
        An integer partition of n is a way of writing n as a sum of positive integers.
        For example, the integer partitions of 4 are:
            [4], [3, 1], [2, 2], [2, 1, 1], [1, 1, 1, 1]
        So the output for n = 4 would be 5.

    Solution #1: Recursion
        The base case is when n == 0, we have 1 way to get the target sum
        If n < 0 or k == 0, we have 0 ways to get the target sum as we have exhausted all the numbers

        The way to generate all possible combinations is to have two function calls:
            1. One where we keep repeating the same component k while reducing n i.e n - k which means
                using k again and again until we reach the target sum or exceed it
            2. One where we move to the next number while keeping n same i.e k - 1

        The answer is the sum of the two function calls.
        Note that wasted function calls can be avoided by doing a check if n >= k before doing the first check,
            this means the 2nd base case becomes simply `k == 0` instead of `k == 0 || n < 0`

        Time: O(2^n), Space: O(n)

    Solution #2: DP
        Let DP[N][N]

        DP[k][n] represents the number of ways to get the target sum n using numbers from 1 to k
        We are switching position of k and n since since k follows k and k - 1, i.e current and previous rows
            which is going to be useful in space optimization

        Base Case is DP[k][0] = 1 for all k as we have 1 way to get the target sum 0 i.e by not using any number

        For k = 1 to N
            For n = 0 to N
                DP[k][n] = DP[k - 1][n]
                if n >= k
                    DP[k][n] += DP[k][n - k]

        The answer is DP[N][N]

        Time: O(N^2), Space: O(N^2)

    Solution #3: DP Space Optimization
        Since we are using only k and k-1, we can use two 1D arrays to store the values of dp[k] and dp[k-1].
        But if we look closer we can see that we will not change the previous values and will take them down as is,
            hence a single 1D array is enough to store the values of dp[k] and dp[k-1]

        Let DP[N]

        Base Case is DP[0] = 1 as we have 1 way to get the target sum 0 i.e by not using any number

        For k = 1 to N
            For n = k to N
                DP[n] += DP[n - k]

        The answer is DP[N]

        Time: O(N^2), Space: O(N)

        Note: We are starting the loop for n from k to N to avoid the if condition and because the value just gets copied down
            anyway.
*/

class Solution {
    int numberOfIntegerPartitionsDPSpace( int N ) {
        vector<int> dp( N + 1, 0 );
        dp [ 0 ] = 1;

        for ( int k = 1; k <= N; k++ ) {
            for ( int n = k; n <= N; n++ ) {
                dp [ n ] += dp [ n - k ];
            }
        }

        return dp [ N ];
    }

    int numberOfIntegerPartitionsDP( int N ) {
        vector<vector<int>> dp( N + 1, vector<int>( N + 1, 0 ) );
        dp [ 0 ][ 0 ] = 1;

        for ( int k = 1; k <= N; k++ ) {
            for ( int n = 0; n <= N; n++ ) {
                dp [ k ][ n ] = dp [ k - 1 ][ n ];
                if ( n >= k ) dp [ k ][ n ] += dp [ k ][ n - k ];
            }
        }

        return dp [ N ][ N ];
    }

    int numberOfIntegerPartitionsRec( int n, int k ) {
        if ( n == 0 ) return 1;
        if ( k == 0 ) return 0;

        int stayK = 0, nextK = 0;
        nextK = numberOfIntegerPartitionsRec( n, k - 1 );
        if ( n >= k ) stayK = numberOfIntegerPartitionsRec( n - k, k );

        return stayK + nextK;
    }

public:
    int numberOfIntegerPartitions( int n ) {
        return numberOfIntegerPartitionsDPSpace( n );
    }
};

int main( ) {
    Solution sol;
    int n = 4;
    cout << sol.numberOfIntegerPartitions( n ) << '\n';
    return 0;
}