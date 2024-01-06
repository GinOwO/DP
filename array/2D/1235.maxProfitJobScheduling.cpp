#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 1235 - Maximum Profit in Job Scheduling
        You are given n jobs. The ith job starts at start[i] and ends at end[i] with profit[i].
        You cannot take overlapping jobs. Return the maximum profit you can take such that
            there are no overlapping jobs.

        Example 1:
            Input: start = [1,2,3,3], end = [3,4,5,6], profit = [50,10,40,70]
            Output: 120
            Explanation: The subset chosen is the first and fourth job. 
            Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
        
        We basically sort the arrays based on start time, as just like 
            how every 60s in Africa a minute passes, time goes forward.

        So after that we have two choices for every job, either take it or not.
        If we are not taking it, we just move on to the next job.
        If we are taking it, we take the profit of this job and recursively call
            the function for the next job that doesn't overlap with this one.
        
        We can find the next job that doesn't overlap with the i-th job by using binary search,
            by doing lowerbound on starting from i+1 to the end of the array for the end value on start value.
        
        Base case is when we reach the end of the array, we return 0.

        DP Solution:

            DP[n] = {0}
            for i=n-1 to i=0:
                DP[i] = max(DP[i+1], profit[i]+DP[lb(i+1, end[i])])

            Answer is DP[0]

        Time complexity: O(nlogn), Space complexity: O(n)
*/

class Solution {
public:
    int lb(int start, int end, const vector<vector<int>>& times){
        int l=start, r=times.size()-1, mid;
        while(l<=r){
            mid = l+(r-l)/2;
            if(end<=times[mid][0]) r=mid-1;
            else l=mid+1;
        }
        return l;
    }

    int jobSchedulingDP(const vector<vector<int>>& times) {
        vector<int> dp(times.size()+1, 0);
        for(int i=times.size()-1; i>=0; i--)
            dp[i] = max(dp[i+1], times[i][2]+dp[lb(i+1, times[i][1], times)]);
        return dp[0];
    }

    int jobSchedulingRec(int i, const vector<vector<int>>& times, 
                unordered_map<int, int>& dp) {
        if(i>=times.size()) return 0;
        if(dp.count(i)) return dp[i];

        int notTake=jobSchedulingRec(i+1, times, dp), idx = lb(i+1, times[i][1], times);
        int take=times[i][2]+jobSchedulingRec(idx, times, dp);
        return dp[i] = max(take, notTake);
    }

    int jobScheduling(vector<int>& st, vector<int>& et, vector<int>& p) {
        vector<vector<int>> times;
        for(int i=0; i<st.size(); i++)
            times.push_back({st[i], et[i], p[i]});
        
        sort(times.begin(), times.end(), [](auto&a, auto&b){
            return (a[0]<b[0]) || (a[0]==b[0] && a[1]<b[1]) || (a[0]==b[0] && a[1]==b[1] && a[2]>b[2]);
        });

        // unordered_map<int, int> dp;
        // return jobSchedulingRec(0, times, dp);
        return jobSchedulingDP(times);
    }
};

int main(){
    Solution s;
    vector<int> st, et, p;
    st = {1,2,3,3}, et = {3,4,5,6}, p = {50,10,40,70};
    cout << s.jobScheduling(st, et, p) << endl;
    return 0;
}