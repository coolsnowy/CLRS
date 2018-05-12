#include <iostream>
#include <vector>
#include <ctime>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// see website  https://blog.csdn.net/linraise/article/details/8920163

/*
 * 刚开始看到这个题目，整了半天没整明白是个什么回事，后来通过例子终于自我认为理解了。要理解上面所说的区间模糊排序。
 * 首先要点是，这是区间排序，即和快速排序不同，快速排序是每一个元素都是确定的，而这里每一个元素都是一段区间，排序结果也是不一定正确的，即是模糊的。要先理解下面的一个偏序关系

  先思考一个问题：为什么区间重叠能改善排序算法的期望运行时间呢？想明白了其实很简单，这相当于我们用快速排序一个数组时，数组中有很多重复元素，
  如果我们做一个改进，将划分从2部分变成3部分，前边部分是小于，中间是等于，后面是大于。
  那么以后每次需要划分的区间（只划分小于和大于）都可能会大大减小，这样PARTITION时就可能非常高效。
a）首先定义两个线段的偏序关系(非唯一)，如下图所示



以线段i的左端点ai为参照物，分为三种情况：

1）线段j<线段i， 此时满足b.end<a.begin

2）线段j=线段i， 此时满足b.begin≤a.begin≤b.end。这样定义的原因是：最后可以让线段j和线段i的ci均取a.begin（重叠部分）

3）线段j>线段i， 此时满足b.begin>a.begin
 为什么不是b.begin > a.end呢，题目中说了利用左边端点进行快速排序，而中间部分都是有交集的，例如利用4，7作为pivot，虽然1，4和5-7都是和中间有交集
 但是这两者本身并没有任何交集，理应放到第三部分，中间部分都是包含交集，至少包含a。begin这个点都有

通过上图我们可以清晰地感性地认知偏序小于，偏序大于，偏序等于各属于什么情况。图真是一个好东西


思考很久，我终于发现区间模糊排序本质上是快排的一种变种。
区间排序实质上是以区间为单位进行操作，所以，需要定义一个结构体保存区间首尾元素。而快排是以元素为单位排序。
通过定义偏序大于，小于和等于关系，再对快排的partition做了一点改进，使它每次都可以返回一个区间结构体，使得左边的小于，右边的大于，中间的等于。

 */
struct interval {
    int left;
    int right;
};

bool before(interval a, interval b) {
    return a.right < b.left;
}

bool after(interval a, interval b) {
    return a.left > b.left;
}

bool intersect(interval a, interval b) {
    return a.left <= b.left && a.right >= a.left;
}

interval partition(std::vector<interval> &a, int p, int r) {
    //pick an random intersect as a pivot
    srand((unsigned)time(0));
    int pick = p + rand()%(r - p);
    std::swap(a[pick], a[r]);
    interval intersection  = a[r];

    // find an intersection of the pivot and other intervals
    for(int j = p; j <= r - 1; j++) {
        if(intersect(a[j], intersection)) {
            if(a[j].left > intersection.left)
                intersection.left = a[j].left;
            if(a[j].right < intersection.right)
                intersection.right = a[j].right;
        }
    }

    // classical partition around the intersection
    int s = p;
    for(int i = p; i <= r - 1; i++) {
        if(before(a[i], intersection)) {
            using std::swap;
            swap(a[i], a[s]);
            s++;
        }
    }
    // after the for loop, s point to the first element >= key
    std::swap(a[r], a[s]);

    // group intervals including the intersection
    int t = s + 1, i = 0;
    for(t = s + 1, i = r; t <= i; ) {
        if(intersect(a[i], intersection)) {
            std::swap(a[t], a[i]);
            t++;
        } else {
            i--;
        }
    }
    // after this loop, t point to the first element > interval, not equal

    return interval{s, t - 1};
}

void fuzzySort(std::vector<interval> &a, int p, int r) {
    if(p < r) {
        interval pivot = partition(a, p, r);
        fuzzySort(a, p, pivot.left - 1);
        fuzzySort(a, pivot.right + 1, r);
    }
}

int main() {
    std::vector<interval> a{{1,2}, {3, 6}, {11, 12}, {8, 13}, {7, 8}};
    fuzzySort(a, 0, a.size() - 1);
    for(auto i : a) {
        cout << i.left << '\t' << i.right << endl;
    }
}