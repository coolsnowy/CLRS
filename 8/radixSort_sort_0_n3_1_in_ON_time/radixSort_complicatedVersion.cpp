#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

/* Ex 8.3.4 在O（N）的世间内完成对0到n^3 - 1的n个整数进行排序 */
void show(std::vector<int> vec) {
    for (auto i : vec) {
        cout << i << '\t';
    }
    cout << endl;
}

std::vector<int> radixSort(std::vector<int> vec, int radix, int digit) {
    std::vector<int> result(vec.size(), 0);
    for(int dig = 1; dig <= digit; dig++) {
        std::vector<int> count(radix, 0);
        for (auto i : vec) {
            // digitNumber 表示整数i的第digit位数字
            int digitNumber = i % static_cast<int> (pow(radix, dig)) / static_cast<int> (pow(radix, dig - 1));
            count[digitNumber]++;
        }
        for (int i = 1; i < count.size(); i++) {
            count[i] += count[i - 1];
        }
        for (int i = vec.size() - 1; i >= 0; i--) {
            result[count[vec[i] % static_cast<int> (pow(radix, dig)) / static_cast<int> (pow(radix, dig - 1))] - 1] = vec[i];
            count[vec[i] % static_cast<int> (pow(radix, dig)) / static_cast<int> (pow(radix, dig - 1))]--;
        }
        // update the vec
        for(int i = 0; i < vec.size(); i++) {
            vec[i] = result[i];
        }
    }
    return result;
}

int main() {
    std::vector<int> vec{100, 98, 34, 20, 35, 124};
    auto result = radixSort(vec, 5, 3);
    show(result);
}