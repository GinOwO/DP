#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 416. Partition Equal Subset Sum
        Given a non-empty array nums containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
        
        Dividing an array into two subsets of equal sum means the sum of the array is even, as each subset will have sum of half of the main array. 
        If the sum is odd, we cannot divide the array into two subsets of equal sum.
        So do subset sum with target = sum/2.

        Remember to check (arr[0]<=target) and only then set dp[arr[0]]=1
    
        Alternatively, we can use two 1D DP array of size target+1, one for current row and one for previous row.
    
        Time Complexity: O(n*target), Space Optimized: O(target)
*/

class Solution {
public:
    bool isSubsetSumDP(const int target, const vector<int>& arr){
        int n = arr.size();
        vector<bool> dp(target+1, 0), ndp(target+1, 0);

        dp[0]=ndp[0]=1;
        if(arr[0]<=target) dp[arr[0]]=ndp[arr[0]]=1;
        
        for(int i=1; i<n; i++){
            for(int x=arr[i]; x<=target; x++)
                ndp[x] = dp[x] | dp[x-arr[i]];
            dp=ndp;
        }
        return dp[target];
    }

    bool canPartition(vector<int>& nums) {
        int s = accumulate(nums.begin(), nums.end(), 0);
        return s%2==0 && isSubsetSumDP(s/2, nums);
    }
};

int main(){
    Solution s;
    vector<int> nums{1, 5, 11, 5};
    cout << s.canPartition(nums) << endl;
    return 0;
}