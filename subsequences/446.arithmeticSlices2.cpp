#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 446 - Arithmetic Slices II - Subsequence
        Given an integer array nums, return the number of all the arithmetic subsequences of nums.
        A sequence of numbers is called arithmetic if it consists of at least three elements and 
            if the difference between any two consecutive elements is the same.

        
        We can use DP to solve this problem.
        We can use a 2D DP array, where dp[i][diff] represents the number of arithmetic subsequences
            ending at index i with difference diff.
        
        So for every index i, we can check all the previous indices j, and see if the difference
            between arr[i] and arr[j] is the same as diff.
        If it is, then we can add dp[j][diff] to dp[i][diff], and also add 1 to dp[i][diff] because
            we can also form a new arithmetic subsequence with arr[i] and arr[j].
        
        Time complexity: O(n^2), Space complexity: O(n^2)
*/

class Solution {
public:
    int numberOfArithmeticSlicesDP(const vector<int>& arr) {
        int n = arr.size(), ans=0;
        vector<unordered_map<long, int>> dp(n, unordered_map<long, int>{});

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                long diff = 0L+arr[i]-arr[j];
                dp[i][diff] += dp[j][diff]+1;
                ans+=dp[j][diff];
            }
        }
        return ans;
    }

    int numberOfArithmeticSlices(const vector<int>& arr) {
        return numberOfArithmeticSlicesDP(arr);
    }
};

int main(){
    Solution s;
    vector<int> arr{2,4,6,8,10};
    cout << s.numberOfArithmeticSlices(arr) << endl;
    return 0;
}