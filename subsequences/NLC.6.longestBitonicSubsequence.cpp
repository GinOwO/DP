#include<bits/stdc++.h>

using namespace std;

/*
    Length of Longest Bitonic Subsequence
        A subsequence of a given sequence is called Bitonic if it is first increasing, then decreasing.
        Example: {1,2,3,4,5,6,7,8,9} is a bitonic sequence as its increase before 5 and decreasing after 5, 
                but {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3} is not.
        
        Note that the sequence can be strictly increasing or decreasing, i.e {1,2,3,4,5,6,7,8,9} is a bitonic sequence.

        The idea here is to find the LIS for the array in both directions, i.e from left to right and right to left.
        This gives us the length of the increasing subsequence ending at each index from the left and
        the length of the decreasing subsequence starting at each index from the right.

        Then we just find the maximum of the sum of the two values at each index, and subtract 1 from it 
        as otherwise we will be counting the element at that index twice.

        DP[n] = DPReverse[n] = {1}
        For i=1->n-1
            For j=0->i-1
                if arr[i] > arr[j]: DP[i] = max(DP[i], DP[j]+1)
                if arr[n-i-1] > arr[n-j-1]: DPReverse[n-i-1] = max(DPReverse[n-i-1], DPReverse[n-j-1]+1)

        Max = 0
        For i=0->n-1
            Max = max(Max, DP[i]+DPReverse[i]-1)
        
        Answer is Max

        Time: O(n^2), Space: O(n)
*/

class Solution {
public:
    int lengthOfLBS(vector<int>&arr){
        int n = arr.size(), mx=1;
        vector<int> dp(n, 1), dpReverse(n, 1);

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                if(arr[j]<arr[i]) dp[i]=max(dp[j]+1, dp[i]);
                if(arr[n-j-1]<arr[n-i-1]) dpReverse[n-i-1]=max(dpReverse[n-j-1]+1, dpReverse[n-i-1]);
            }
        }
        for(int i=0; i<n; i++) mx = max(mx, dp[i]+dpReverse[i]-1);

        return mx;
    }
};

int main(){
    Solution s;
    vector<int> arr = {0,2,3,4,100,6,7,8,9,8,7,6,100,4,3};
    cout<<s.lengthOfLBS(arr)<<endl;
    return 0;
}