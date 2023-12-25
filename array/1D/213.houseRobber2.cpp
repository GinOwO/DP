
#include<iostream>
#include<vector>

using namespace std;

/*
    Leecode 213. House Robber II
        Maximum Non adjacent sum on cyclic array
        Time Complexity: O(n)
        Space Complexity: O(1)
*/


int rob(const vector<int>& nums) {
    int n=nums.size(), a=0, b=0, c, d;
    if(n==1) return nums[0];
    for(int i=n-1; i>=1; i--){
        c=max(a, b+nums[i]);
        b=a; a=c;
    }
    d=a; b=0; a=0;
    for(int i=n-2; i>=0; i--){
        c=max(a, b+nums[i]);
        b=a; a=c;
    }
    return max(a,d);
}

int main(){
    vector<int> nums={1,2,3,1};
    cout<<rob(nums)<<endl;
    return 0;
}

