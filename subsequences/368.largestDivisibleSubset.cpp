#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 368 - Largest Divisible Subset
        Find the largest subset of an array of integers, such that every pair (Si, Sj) of elements in this subset satisfies:
            Si % Sj = 0 or Sj % Si = 0.
        If there are multiple solutions, return any subset.

        Same logic as printing LIS, but with a little modification:
        We change the condition from arr[j]<arr[i] to arr[i]%arr[j]==0

        Time complexity: O(n^2), Space complexity: O(n)
*/

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, 1), res(n, 0);

        sort(arr.begin(), arr.end());

        int mx = 1, idx = 0;
        for ( int i = 0; i < n; i++ ) {
            res[i] = i;
            for ( int j = 0; j < i; j++ ) {
                if ( arr[i] % arr[j] == 0 && dp[i] < dp[j] + 1 ) {
                    dp[i] = dp[j] + 1;
                    res[i] = j;
                }
            }
            if ( dp[i] > mx ) {
                mx = dp[i];
                idx = i;
            }
        }

        vector<int> ans { arr[idx] };
        while ( res[idx] != idx ) {
            idx = res[idx];
            ans.push_back(arr[idx]);
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<int> arr { 9,2,5,10,3,7,11 };
    vector<int> res = s.largestDivisibleSubset(arr);
    for ( auto& c : res ) cout << c << " ";
    cout << endl;
    return 0;
}