#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool jumpRec(int i, vector<int>& nums, vector<int>& memo) {
        if ( i < 0 || i >= nums.size() ) return false;
        if ( nums[i] == 0 ) return true;

        if ( memo[i] != -1 ) return memo[i];

        int a = false, b = false;
        if ( i + nums[i] < nums.size() ) a = jumpRec(i + nums[i], nums, memo);
        if ( i - nums[i] >= 0 ) b = jumpRec(i - nums[i], nums, memo);

        return memo[i] = a || b;
    }

    bool canReach(vector<int>& arr, int start) {
        vector<int> memo(5e4 + 2, -1);
        return jumpRec(start, arr, memo);
    }
};

int main() {
    Solution s;
    vector<int> arr = { 4,2,3,0,3,1,2 };
    cout << s.canReach(arr, 2) << endl;
}