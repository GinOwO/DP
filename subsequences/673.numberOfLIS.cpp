#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 673 - Number of Longest Increasing Subsequence
        Given an integer array nums, return the number of longest increasing subsequences.

        We use cnt[i] to keep track of the number of LIS of length dp[i] ending at index i.
        The answer is the sum of all cnt[i] where dp[i] is the maximum length of LIS.
        The count will only increase if the length of LIS increases by 1, i.e dp[i]=dp[j]+1, where j<i, 
        else it just takes the value of cnt[j].
        
        DP[n] = cnt[n] = {1}
        For i=1->n-1
            For j=0->i-1
                if arr[j]<arr[i] && dp[j]+1>dp[i]: dp[i]=dp[j]+1, cnt[i]=cnt[j]
                if arr[j]<arr[i] && dp[j]+1==dp[i]: cnt[i]+=cnt[j]
        
        sum = 0
        For i=0->n-1
            if dp[i]==mx: sum+=cnt[i]
        
        Answer is sum

    Time: O(n^2), Space: O(n)
*/

class Solution {
public:
    int findNumberOfLISDP(const vector<int>& arr){
        int n = arr.size(), mx=1, idx=0;
        vector<int> dp(n, 1), cnt(n, 1);

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                if(arr[j]<arr[i] && dp[j]+1>dp[i]){
                    dp[i]=dp[j]+1;
                    cnt[i]=cnt[j];
                }
                else if(arr[j]<arr[i] && dp[j]+1==dp[i]){
                    cnt[i]+=cnt[j];
                }
            }
            mx = max(dp[i], mx);
        }
        
        int sum=0;
        for(int i=0; i<n; i++)
            if(mx==dp[i]) sum+=cnt[i];

        return sum;
    }

    int findNumberOfLIS(vector<int>& nums) {
        return findNumberOfLISDP(nums);
    }
};

int main(){
    Solution sol;
    vector<int> arr = {1,3,5,4,7};
    cout<<sol.findNumberOfLIS(arr)<<endl;
    return 0;
}