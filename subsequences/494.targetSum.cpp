#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 494 - Target Sum
        Given an array of integers nums and an integer target.
        Insert + or - before each integer in nums to get target sum. Must use all integers in nums.
        Return the number of ways to get target sum.

        Use count partitions with given difference d: s1-s2=d where s1>s2 and s1+s2=sum. Adding both equations, we get s1=(sum+d)/2
        Here d = target, which means we just need to find the number of partitions with difference (totalSum-target)/2

        An edge case is when arr[0]==0, in that case set dp[0]=2. This is because we can either take 0 or not take 0 to get 0 sum, 
        otherwise we will get 0 sum only by not taking any element, hence set to dp[0]=1.


        Time Complexity: O(n*target), Space Complexity: O(n*target), Space Optimized: O(target)
*/

class Solution {
public:
    int countSubsetSumDP(const int target, const vector<int>& arr){
        int n = arr.size();
        vector<int> dp(target+1, 0), ndp(target+1, 0);
        
        dp[0] = (arr[0]==0)?2:1;

        if(arr[0]!=0 && arr[0]<=target) dp[arr[0]]=1;
        
        for(int i=1; i<n; i++){
            for(int x=0; x<=target; x++)
                ndp[x] = dp[x] + (x>=arr[i]?dp[x-arr[i]]:0);
            dp=ndp;
        }

        return dp[target];
    }

    int findTargetSumWaysDP(int target, const vector<int>& nums) {
        int s = accumulate(nums.begin(), nums.end(), 0);
        if(s<target || (s-target)%2) return 0;
        return countSubsetSumDP((s-target)/2, nums);
    }

    int findTargetSumWaysRec(const int i, const int target, const vector<int>& nums, 
    const int n, unordered_map<int, unordered_map<int, int>>& dp){
        if(i==n) return target==0;
        if(dp[i].count(target)) return dp[i][target];

        return dp[i][target] = findTargetSumWaysRec(i+1, target-nums[i], nums, n, dp) +
                               findTargetSumWaysRec(i+1, target+nums[i], nums, n, dp);
    }

    int findTargetSumWays(const vector<int>& nums, int target) {
        // unordered_map<int, unordered_map<int, int>> dp;
        // return findTargetSumWaysRec(0, target, nums, nums.size(), dp);
        return findTargetSumWaysDP(target, nums);
    }
};

int main(){
    Solution s;
    vector<int> nums{1, 1, 1, 1, 1};
    cout << s.findTargetSumWays(nums, 3) << endl;
    return 0;
}