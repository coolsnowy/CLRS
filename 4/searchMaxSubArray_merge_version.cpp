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

SubArray findMaxCrossingSubArray(std::vector<int>& vec, int lo, int mid, int hi) {
    int maxLeftSum = 0x80000000, maxRightSum = 0x80000000;
    // fuck !!! define the new index, not modify the lo and hi
    // otherwise the follow for loop will be wrong, becasue the lo and hi is the condition of for loop
    int minLeft = mid, maxRight = mid+1;
    int sum = 0;
    for(int i = mid; i >= lo; i--) {
        sum += vec[i];
        if(sum >= maxLeftSum) {
            maxLeftSum = sum;
            minLeft = i;
        }
    }
    sum = 0;
    for(int i = mid + 1; i <= hi; i++) {
        sum += vec[i];
        if(sum >= maxRightSum) {
            maxRightSum = sum;
            maxRight = i;
        }
    }
    int maxSum = maxLeftSum + maxRightSum;
    if(maxSum < 0)
        return SubArray(-1, -1, 0);
    return SubArray(minLeft, maxRight, maxSum);
}
SubArray findMaxSubArray(std::vector<int>& vec, int lo, int hi) {
    if(lo >= hi) {
        if (vec[lo] >= 0) return SubArray(lo, lo, vec[lo]);
        else return SubArray(-1, -1, 0);
    } else {
        int mid = lo + (hi - lo) / 2;
        SubArray leftResult = findMaxSubArray(vec, lo, mid);
        SubArray rightResult = findMaxSubArray(vec, mid + 1, hi);
        SubArray crossingResul = findMaxCrossingSubArray(vec, lo, mid, hi);
        if(crossingResul.sum >= leftResult.sum && crossingResul.sum >= rightResult.sum) {
            return crossingResul;
        } else if(rightResult.sum >= crossingResul.sum && rightResult.sum >= leftResult.sum) {
            return rightResult;
        } else if (leftResult.sum > crossingResul.sum && leftResult.sum >= rightResult.sum)
        return leftResult;
    }

}

int main() {
    //std::vector<int> vec{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    std::vector<int> vec{-1, -2, -3};
    auto result = findMaxSubArray(vec, 0, vec.size() - 1);
    cout<<result.lo
        <<'\t'<<result.hi<<'\t'
                         <<result.sum<<endl;
}