#include<bits/stdc++.h>

using namespace std;

/*
    Printing a Longest Increasing Subsequence
        Given an array of integers, find the longest increasing subsequence in this array.
        If there are multiple solutions, return any subsequence.

        We use the same logic as finding the length of the LIS(using DP LIS, not binary search DP). 
        But we also use a mapping array to keep track of the previous index of the element in the LIS, i.e res

        Basically when we start from a new i, we set res[i]=i, to indicate that the current element is currently the root of the LIS ending at i.
        Then we check for all j<i, if arr[j]<arr[i] and dp[i]<dp[j]+1, then we update dp[i] and res[i] to j, to indicate that the current element is now the root of the LIS ending at i.

        Then we find the index of the maximum element in dp, and use that index to rebuild the LIS using res.

        i.e we start from the index of the maximum element in dp, and we use the index stored in res to find the previous element in the LIS, and we keep doing this until we reach the root of the LIS, i.e res[idx]==idx

            idx = max(dp)
            ans[0] = arr[idx]

            While res[idx]!=idx:
                idx = res[idx]
                ans.append(arr[idx])
            
            reverse(ans)
            return ans

        We reverse the output array at the end as the LIS will be built in reverse. Alternatively, you can reserve space
        and use a pointer to the end of the array to build the LIS in correct order.

        Time complexity: O(n^2), Space complexity: O(n)
*/

vector<int> printLIS(const vector<int>& arr, int n){
    vector<int> dp(n, 1), res(n, 0);
    int mx=1, idx=0;
    for(int i=0; i<n; i++){
        res[i]=i;
        for(int j=0; j<i; j++){
            if(arr[j]<arr[i] && dp[i]<dp[j]+1){
                dp[i]=dp[j]+1;
                res[i]=j;
            }
        }
        if(dp[i]>mx){
            mx = dp[i];
            idx = i;
        }
    }

    vector<int> ans;
    ans.push_back(arr[idx]);
    while(res[idx]!=idx){
        idx = res[idx];
        ans.push_back(arr[idx]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    vector<int> arr{9,2,5,10,3,7,11};
    int n = arr.size();
    vector<int> res = printLIS(arr, n);
    for(auto&c:res) cout<<c<<" ";
    cout<<endl;    
    return 0;
}