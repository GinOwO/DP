#include<bits/stdc++.h>

using namespace std;

/*
    Given an array of non-negative integers, and a value sum, determine if there is a SUBSEQUENCE of the given array with sum equal to given sum.
    
    Two cases:
        1. Take the element (iff target-arr[i]>=0)
        2. Dont take the element

    DP[n+1][target+1] = false
    Base case: 
        DP[i][0]=true for all i
        DP[0][arr[0]]=true

    From i=1 to n-1
        From x=1 to target
            DP[i][x] = DP[i-1][x] | (x>=arr[i]?DP[i-1][x-arr[i]]:false)
    
    Answer = DP[n-1][target]

    Alternatively, we can use two 1D DP array of size target+1, one for current row and one for previous row.

    Time Complexity: O(n*target), Space Complexity: O(n*target), Space Optimized: O(target)

*/

class Solution{
public:
    bool isSubsetSumDPSpace(const int target, const vector<int>& arr){
        int n = arr.size();
        vector<bool> dp(target+1, 0), ndp(target+1, 0);
        dp[0]=ndp[0]=dp[arr[0]]=1;
        
        for(int i=1; i<n; i++){
            for(int x=1; x<=target; x++)
                ndp[x] = dp[x] | (x>=arr[i]?dp[x-arr[i]]:false);
            dp = ndp;
        }
        return dp[target];
    }

    bool isSubsetSumDP(const int target, const vector<int>& arr){
        int n = arr.size();
        vector<vector<bool>> dp(n+1, vector<bool>(target+1, 0));
        for(auto&v:dp) v[0]=1;
        dp[0][arr[0]]=1;
        
        
        for(int i=1; i<n; i++){
            for(int x=1; x<=target; x++){
                bool p = dp[i-1][x]; // Not take case
                if(x>=arr[i]) p |= dp[i-1][x-arr[i]]; // Take if target doesnt become negative
                dp[i][x] = p;
            }
        }
        return dp[n-1][target];
    }

    bool isSubsetSumRec(int i, const int x, const vector<int>& arr, vector<vector<int>>& dp){
        if(x==0) return true;
        if(i==0) return x==arr[0];
        if(dp[i][x]!=-1) return dp[i][x];
        
        bool p = isSubsetSumRec(i-1, x, arr, dp); // Not take case
        if(x>=arr[i]) p |= isSubsetSumRec(i-1, x-arr[i], arr, dp); // Take if target doesnt become negative
        
        return dp[i][x] = p;
    }

    bool isSubsetSumRecDFS(int i, const int x, const vector<int>& arr, vector<vector<int>>& dp){ // Dont use, harder to tabulate
        if(x==0) return true;
        if(x<0 || i>=arr.size()) return false;
        if(dp[i][x]!=-1) return dp[i][x];
        bool p=false;
        for(int j=i; !p && j<arr.size(); j++){
            if(x>=arr[j]) p |= (dp[j][x-arr[j]] = isSubsetSumRecDFS(j+1, x-arr[j], arr, dp));
        }
        return dp[i][x]=p;
    }
    
    bool isSubsetSum(vector<int>arr, int sum){
        // vector<vector<int>> dp(arr.size()+1, vector<int>(sum+1, -1));
        // return isSubsetSumRec(arr.size()-1, sum, arr, dp);
        return isSubsetSumDPSpace(sum, arr);
    }
};

int main(){
    Solution s;
    cout << s.isSubsetSum({3, 34, 4, 12, 5, 2}, 30) << endl;
    return 0;
}