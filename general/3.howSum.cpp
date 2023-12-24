#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<cassert>

using namespace std;

// Display all combination of numbers that add up to target sum
// Example: target = 7, nums = {2, 3, 5}
// Soln: {{2, 2, 3}, {2, 5}}
// Time: O(n*target), Space: O(target)

typedef unsigned long long ll;
typedef vector<ll> VI;
typedef vector<VI> VII;

VII howSum(int target, VI&nums){
    VI dp(target+1, 0); dp[0] = 1;
    vector<VII> res(target+1, {{}});
    for(int i=1; i<=nums.size(); i++){
        ll k = nums[i-1];
        for(int j=k; j<=target; j++){
            dp[j] += dp[j-k];
            if(dp[j-k]){
                for(auto&v:res[j-k]){
                    VI temp(v);
                    temp.push_back(k);
                    res[j].push_back(temp);
                }
            }
        }
    }
    return res[target];
}

int main() {
    // Test case 1
    VI nums1 = {2, 3, 5};
    VII expected1 = {{2, 2, 3}, {2, 5}};
    VII result1 = howSum(7, nums1);
    assert(result1 == expected1);

    // Test case 2
    VI nums2 = {2, 4};
    VII expected2 = {{2, 2, 2, 2}, {2, 4, 4}, {4, 2, 2, 2}, {4, 4}};
    VII result2 = howSum(8, nums2);
    assert(result2 == expected2);

    // Test case 3
    VI nums3 = {7, 14};
    VII expected3 = {{7}, {14}};
    VII result3 = howSum(7, nums3);
    assert(result3 == expected3);

    // Test case 4
    VI nums4 = {3, 5, 7};
    VII expected4 = {{3, 3, 3}, {3, 5}, {7}};
    VII result4 = howSum(9, nums4);
    assert(result4 == expected4);

    cout << "All test cases passed!";
    return 0;
}