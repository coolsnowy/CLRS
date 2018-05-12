 #include <iostream>
 #include <string>
 #include <vector>
 void insertionSort(std::vector<int>& v) {
     for(int i = 1; i < v.size(); i++ ) {
         int key = v[i];
         int j = i - 1;
         while( j >= 0 && v[j] > key) {
             v[j+1] = v[j];
             j--;
         }
         v[j + 1] = key;
     }
 }
int main() {
     std::vector<int> v{4, 3, 4, 2, 5, 1};
     insertionSort(v);
     for(auto i : v) {
         std::cout << i<< '\t';
     }
     std::cout<<std::endl;
 }
