 #include <iostream>
 #include <string>
 #include <vector>
 void merge(std::vector<int>& vec, std::vector<int>& aux, int lo, int mid, int hi) {
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
             vec[index++] = aux[j++];
         }
     }

 }
 void mergeSort(std::vector<int>& vec, std::vector<int>& aux, int lo, int hi) {
     if(lo >= hi) return ;
     int mid = lo + (hi - lo) / 2;
     mergeSort(vec, aux, lo, mid);
     mergeSort(vec, aux, mid + 1, hi);
     merge(vec, aux, lo, mid, hi);
 }
 void mergeSort(std::vector<int>& vec) {
     std::vector<int> aux(vec.size(), 0);
     mergeSort(vec, aux, 0, vec.size() - 1);
 }
int main() {
     std::vector<int> v{4, 3, 4, 2, 5, 1};
     mergeSort(v);
     for(auto i : v) {
         std::cout << i<< '\t';
     }
     std::cout<<std::endl;
 }
