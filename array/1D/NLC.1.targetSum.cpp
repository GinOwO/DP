#include<vector>
#include<utility>
#include<algorithm>
#include<iostream>

using namespace std;

// Number of unique ways to reach target sum with of given numbers, with repetition allowed
// Example: target = 4, nums = {1, 2, 3}
// Soln: {1,1,1,1}, {1,1,2}, {1,3}, {2,2}
// Output: 4
// Time: O(m*len(n)), Space: O(m+len(n))

typedef unsigned long long ll;
typedef vector<ll> VI;

ll targetSum(int target, VI&nums){
    VI dp(target+1, 0); dp[0] = 1;
    for(int i=1; i<=nums.size(); i++){
        ll k = nums[i-1];
        for(int j=k; j<=target; j++)
            dp[j] += dp[j-k];
    }
    return dp[target];
}

int main() {
    VI nums1 = {1, 2, 3};
    int target1 = 4;
    ll expected1 = 4;
    ll result1 = targetSum(target1, nums1);
    cout << (result1 == expected1 ? "Test case 1 passed" : "Test case 1 failed") << endl;

    VI nums2 = {1, 2, 3};
    int target2 = 5;
    ll expected2 = 5;
    ll result2 = targetSum(target2, nums2);
    cout << (result2 == expected2 ? "Test case 2 passed" : "Test case 2 failed") << endl;

    VI nums3 = {2, 5, 3};
    int target3 = 7;
    ll expected3 = 2;
    ll result3 = targetSum(target3, nums3);
    cout << (result3 == expected3 ? "Test case 3 passed" : "Test case 3 failed") << endl;
    return 0;
}