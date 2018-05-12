#include <iostream>
#include <vector>
using std::cout;
using std::endl;

class SubArray {
public :
    int lo;
    int hi;
    int sum;
    SubArray(int a, int b, int c) : lo(a), hi(b), sum(c) {
    }
    SubArray() : lo(0), hi(0), sum(0) {}
};

/*
 * 这是一道非常经典的动态规划的题目，用到的思路我们在别的动态规划题目中也很常用，以后我们称为”局部最优和全局最优解法“。
    基本思路是这样的，在每一步，我们维护两个变量，一个是全局最优，就是到当前元素为止最优的解是，一个是局部最优，就是必须包含当前元素的最优的解。
     接下来说说动态规划的递推式（这是动态规划最重要的步骤，递归式出来了，基本上代码框架也就出来了）。假设我们已知第i步的global[i]（全局最优）和local[i]（局部最优），
     那么第i+1步的表达式是：
    local[i+1]=Math.max(A[i], local[i]+A[i])，就是局部最优是一定要包含当前元素，所以不然就是上一步的局部最优local[i]+当前元素A[i]（
     因为local[i]一定包含第i个元素，所以不违反条件），但是如果local[i]是负的，那么加上他就不如不需要的，所以不然就是直接用A[i]；
    global[i+1]=Math(local[i+1],global[i])，有了当前一步的局部最优，那么全局最优就是当前的局部最优或者还是原来的全局最优
     （所有情况都会被涵盖进来，因为最优的解如果不包含当前元素，那么前面会被维护在全局最优里面，如果包含当前元素，那么就是这个局部最优）。
 */
int findMaxSubArray(std::vector<int>& vec, int lo, int hi) {
    int global = vec[0];
    int local = vec[0];
    for(int i = lo + 1; i <= hi; ++i) {
        local = std::max(vec[i], local + vec[i]);
        global = std::max(local, global);
    }
    return global;
}

// leetcode 上的解法
int maxSubArray(std::vector<int>& nums) {
    int size = nums.size();
    std::vector<int> dp(size, 0);
    if(nums.empty()) return 0;
    dp[0] = nums[0];
    int max = nums[0];
    for(int i = 1; i < size; i++) {
        dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
        max = std::max(dp[i], max);
    }
    return max;
}

int main() {
    std::vector<int> vec{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    //std::vector<int> vec{-1, -2, -3};
    auto result = findMaxSubArray(vec, 0, vec.size() - 1);
    cout<<result<<endl;
}