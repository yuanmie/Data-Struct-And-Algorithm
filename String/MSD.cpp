/*
第一：先按照高位，使用索引排序来划分数组
第二：在每个划分的数组中递归的调用此过程直到要划分的数组个数小于一定的阀值
*/
#include <string>

void msdSort(std::string* strs, int length){
  assert(length > 0);
  _msdSort(strs, 0, length, 0);
}

void _msdSort(std::strs, int lo, int hi, int currentIndex){
  if(lo >= hi) return;
  int M = 256; //there were 256 char
  int countSize = M + 1;
  int strLen = strs[lo].length();
  for(int i = hi - 1; i >= lo; i--){
    int count[countSize] = {0};
    int sortIndex = i;
    for (size_t indexOfstrs = lo; indexOfstrs < hi; indexOfstrs++) {
      std::string s = strs[indexOfstrs];
      size_t charIndex = (int)s[sortIndex];
      ++count[charIndex + 1];
    }
    
    for (size_t indexOfCount = 1; indexOfCount < countSize; indexOfCount++) {
      count[indexOfCount] += count[indexOfCount-1];
    }
    
    std::string copy[length];
    for (size_t indexOfstrs = lo; indexOfstrs < hi; indexOfstrs++) {
      std::string s = strs[indexOfstrs];
      size_t currentChar = s[sortIndex];
      size_t putIndex = count[currentChar];
      copy[putIndex] = s;
      ++count[currentChar];
    }
    
    for (size_t indexOfstrs = lo; indexOfstrs < hi; indexOfstrs++) {
      strs[indexOfstrs] = copy[indexOfstrs];
    }
    
  }
}

int main(){
    std::string is_one("oneongroup");
    std::string is_two("twooogroup");
    std::string is_three("threegroup");
    std::string is_three2("threfgroup");
    std::string is_three3("threggroup");
    const int M = 5;
    std::string a[M] = {is_three, is_three2, is_two, is_one, is_three3};
    for(int i = 0; i < M; i++){
        std::cout << a[i] << "\t";
    }
    mlsdSort(a, M);
        std::cout << "\nafter sort" << "\n";
    for(int i = 0; i < M; i++){
        std::cout << a[i] << "\t";
    }
}