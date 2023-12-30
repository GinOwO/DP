#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 300 - Longest Increasing Subsequence
        Given an integer array nums, return the length of the longest strictly increasing subsequence.

        The normal recursive solution is:

        F(i, prev, arr[], n) = 
            If i==n: return 0
            len = F(i+1, p, arr, n)     // Skip case
            If p==-INF OR arr[i]>arr[p]:  // Match case or first element
                len = max(len, 1+F(i+1, i, arr, n)) 
            return len
        
        This can be easily converted into a DP solution using a 2D array:
            DP[n+1][n+1] = {-INF}
            For i=n->0
                For p=0->n
                    len = DP[i+1][p]
                    If p==0 OR arr[i]>arr[p]:
                        len = max(len, 1+DP[i+1][i])
                    DP[i][p] = len
            Answer is DP[0][0]

        Time: O(n^2), Space: O(n^2)

        This can be reduced into two 1D arrays, which can again be reduced to a single 1D array, which reduces space complexity to O(n):
            DP[n] = {1} // Base case as in a completely decreasing array, the answer is 1, i.e a single element
            For i=1->n-1
                For j=0->i-1
                    if arr[i] > arr[j]: DP[i] = max(DP[i], DP[j]+1)

            Answer is max(DP[i])
        
        Time: O(n^2), Space: O(n)


    Alternative DP solution which is O(nlogn) time and O(n) space.

        Essentially the idea behind this is that we keep a vector say res. Let the input be arr = {9,2,5,10,3,7,11}.
        The answer in this case is 4, i.e {2,5,7,11} or {2,5,10,11} or {2,5,7,11} or {2,3,7,11}.

        We iterate over arr, then we find the lowerbound of the current element(say c) in res, 
            i.e the position where c can be inserted without disturbing the non-decreasing sequence.
        
        If the lowerbound is equal to the size of res, i.e it is bigger than all elements in res, then we just append c to res.
        Else we replace the element at the lowerbound with c.

        The answer will be the size of res.

        
        Intution: 
        Think of res as a an array of stacks, where the top of the stack is the smallest element and
        the all elements of the ith stack is smaller than the elements of the (i+1)th stack:

            At the start, res = []
            First we look for 9, which will give an index of 1, hence we insert:
            
            res = |9|

            Next we look for 2, which will give an index of 0, hence we can put it above 9:

                  |2|
            res = |9|

            Next we look for 5, which will give an index of 1 as 5 is bigger than 2, hence we can put it in a new stack:

                  | 2 |
            res = | 9 | 5 |

            Next we look for 10, which will give an index of 2 as 10 is bigger than 2 and 5, hence we can put it in a new stack:

                  | 2 |
            res = | 9 | 5 | 10 |
            
            At every step, imagine if the top of the ith stack is connected to the top of the (i-1)th stack, like 10 <- 5 <- 2.

            Next we look for 3, which will give an index of 1 as 3 is bigger than 2, but less than 5, hence we can put it above 5:

                  | 2 | 3 |
            res = | 9 | 5 | 10 |

            Now the link becomes 10 <- 3 <- 2

            Next we look for 7, which will give an index of 2 as 7 is bigger than 2 and 3 but less than 10, hence put it above 10:

                  | 2 | 3 | 7  |
            res = | 9 | 5 | 10 |

            Finally, we look for 11, which will give an index of 3 as 11 is bigger than 2, 3, 7 and 10, hence put it in a new stack:

                  | 2 | 3 | 7  |
            res = | 9 | 5 | 10 | 11 |

            Now the link becomes 11 <- 10 <- 7 <- 3 <- 2.

            The answer is the size of res/number of stacks, i.e 4.

            And now since we are only using the top of stack and don't care about the rest of the elements below it,
            we can just store the top of the stack in res, which reduces space complexity to O(n).

            And since lowerbound is O(logn) as it uses binary search, doing it for n elements of the array uses O(n) time for a total of O(nlogn) time.

            Time: O(nlogn), Space: O(n)

            Note that this only stores the topological data needed solely to find the length of the LCS, it cannot be used to find the LCS itself.
*/

class Solution {
public:
    int lengthOfLISDP(const vector<int>& arr){
        int n = arr.size(), mx=1;
        vector<int> dp(n, 1);

        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++)
                if(arr[j]<arr[i]) dp[i]=max(dp[j]+1, dp[i]);
            mx = max(dp[i], mx);
        }

        return mx;
    }

    int lb(const vector<int>& arr, int x){
        int l=0, r=arr.size()-1, mid;
        while(l<=r){
            mid = l+(r-l>>1);
            if(arr[mid]>=x) r=mid-1;
            else l=mid+1;
        }
        return l;
    }

    int lengthOfLIS(const vector<int>& arr){
        vector<int> res;

        for(auto&c:arr){
            int idx = lb(res, c);
            if(idx >= res.size()) res.push_back(c);
            else res[idx] = c;
        }
        return res.size();
    }
};

int main(){
    Solution sol;
    vector<int> arr = {10,9,2,5,3,7,101,18};
    cout<<sol.lengthOfLIS(arr)<<endl;
    return 0;
}