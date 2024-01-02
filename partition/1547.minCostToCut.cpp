#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 1547. Minimum Cost to Cut a Stick
        Given a wooden stick of length n units. The stick is labelled from 0 to n.
        Cost of cutting the stick is equal to the length of the stick to be cut. 
        For example if you have stick of length 10, and you cut it at 4 into two 
            pieces of size 4 and 6, the cost for this is 10. Then if you cut the 6, it will cost another 6
            So total cost is 10+6 = 16.
        
        Given an array cuts where cuts[i] denotes a position you should perform a cut at, find the minimum cost to do all the cuts.
        Cuts can be performed in any order, but all cuts must be performed.

        Time Complexity: O(n^3), Space Complexity: O(n^2)
*/


class Solution {
public:
    int minCostDP(const vector<int>& cuts){
        int n=cuts.back(), c=cuts.size()-2;
        vector<vector<int>> dp(c+2, vector<int>(c+2, 0));
        for(int i=c; i>=1; i--){
            for(int j=i; j<=c; j++){
                dp[i][j] = 1e9;
                for(int k=i; k<=j; k++)
                    dp[i][j] = min(dp[i][k-1]+dp[k+1][j], dp[i][j]);
                dp[i][j]+=cuts[j+1]-cuts[i-1];
            }
        }
        return dp[1][c];
    }

    int dfs(int i, int j, const vector<int>& cuts, unordered_map<int, unordered_map<int, int>>& dp){
        if(i>j) return 0;
        if(dp[i].count(j)) return dp[i][j];

        dp[i][j] = 1e9;
        for(int k=i; k<=j; k++)
            dp[i][j] = min(dfs(i, k-1, cuts, dp)+dfs(k+1, j, cuts, dp)+cuts[j+1]-cuts[i-1], dp[i][j]);
        return dp[i][j];
    }

    int minCost(int n, vector<int>& cuts){
        cuts.push_back(n);
        cuts.push_back(0);
        sort(cuts.begin(), cuts.end());
        // unordered_map<int, unordered_map<int, int>> mp;
        // return dfs(1, cuts.size()-2, cuts, mp);
        return minCostDP(cuts);
    }
};

int main(){
    Solution sol;
    int n=9;
    vector<int> cuts = {5,6,1,4,2};
    cout<<sol.minCost(n, cuts)<<endl;
    return 0;
}