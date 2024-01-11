#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    Leecode 198. House Robber
        Maximum Non adjacent sum
        Time Complexity: O(n)
        Space Complexity: O(1)
*/

unordered_map<int, int> memo;
int robMemo(const vector<int>& nums, const int i = 0) {
    if ( i >= nums.size() ) return 0;
    if ( memo.count(i) ) return memo[i];
    return memo[i] = max(nums[i] + robMemo(nums, i + 2), robMemo(nums, i + 1));
}

int robDP(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n + 2, 0);
    for ( int i = n - 1; i >= 0; i-- )
        dp[i] = max(dp[i + 1], dp[i + 2] + nums[i]);
    return dp[0];
}

int rob(vector<int>& nums) {
    int n = nums.size(), a = 0, b = 0, c;
    for ( int i = n - 1; i >= 0; i-- ) {
        c = max(a, b + nums[i]);
        b = a; a = c;
    }
    return a;
}

int main() {
    vector<int> nums = { 1,2,3,1 };
    cout << rob(nums) << endl;
    return 0;
}