#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
int merge(std::vector<int>& vec, std::vector<int>& aux, int lo, int mid, int hi) {
    int inversion = 0;
    for(int i = lo; i <= hi; i++) {
        aux[i] = vec[i];
    }
    int i = lo, j = mid + 1, index = lo;
    while(index <= hi) {
        if(i > mid) vec[index++] = aux[j++];
        else if(j > hi) vec[index++] = aux[i++];
        else if(aux[i] <= aux[j]) {
            vec[index++] = aux[i++];
        } else {
            vec[index] = aux[j];
            // here is important, not j - i
            //如果j-i相当于把右边数组已经插入进去的也算上了，就多算了，实际上只包含左边数组插入位置*包含该元素）之后的所有元素
            inversion += (mid - i + 1);
            index++;
            j++;
        }
    }
    return inversion;

}
int  mergeSort(std::vector<int>& vec, std::vector<int>& aux, int lo, int hi) {
    if(lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    int inversion = 0;
    inversion += mergeSort(vec, aux, lo, mid);
    inversion += mergeSort(vec, aux, mid + 1, hi);
    inversion += merge(vec, aux, lo, mid, hi);
    return inversion;
}
int  mergeSort(std::vector<int>& vec) {
    std::vector<int> aux(vec.size(), 0);
    int result = mergeSort(vec, aux, 0, vec.size() - 1);
    return result;
}
int main() {
    std::vector<int> v{2, 3, 8, 6, 1, 0};
    auto result = mergeSort(v);
    cout<<result<<endl;
}