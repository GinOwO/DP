#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestValidParenthesesMemo(int i, int k, const string& s, vector<vector<int>>& memo) {
        if ( i == s.size() ) return k == 0 ? 0 : -1e9;
        if ( k < 0 ) return -1e9;

        if ( memo[i][k] != -1 ) return memo[i][k];

        int take = -1e9, notTake = longestValidParenthesesMemo(i + 1, 0, s, memo);
        int x = k + ( s[i] == ')' ? -1 : 1 );
        if ( x >= 0 ) {
            take = 1 + longestValidParenthesesMemo(i + 1, x, s, memo);
        }

        return memo[i][k] = max(take, notTake);
    }

    int longestValidParenthesesRec(int i, int k, const string& s) {
        if ( i == s.size() ) return k == 0 ? 0 : -1e9;
        if ( k < 0 ) return -1e9;

        int take = -1e9, notTake = longestValidParenthesesRec(i + 1, 0, s);
        k += s[i] == ')' ? -1 : 1;
        if ( k >= 0 ) {
            take = 1 + longestValidParenthesesRec(i + 1, k, s);
        }
        else return -1e9;

        return max(take, notTake);
    }

    int longestValidParentheses(const string& s) {
        vector<vector<int>> memo(s.size() + 1, vector<int>(s.size() + 1, -1));
        return longestValidParenthesesRec(0, 0, s);
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("()(()") << endl;
}
