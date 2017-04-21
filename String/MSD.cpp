/*
第一：先按照高位，使用索引排序来划分数组
第二：在每个划分的数组中递归的调用此过程直到要划分的数组个数小于一定的阀值
*/
#include <string>
#include <iostream>
#include <cassert>

void _msdSort(std::string* strs, int lo, int hi, int currentIndex);
int charAt(const std::string& str, int index){
  assert(index >= 0);
  int strLen = str.length();
  if(index < strLen){
    return (int)str[index];
  }else{
    return -1;
  }
}
void msdSort(std::string* strs, int length){
  assert(length > 0);
  _msdSort(strs, 0, length - 1, 0);
}

void _msdSort(std::string* strs, int lo, int hi, int currentIndex){
  if(lo >= hi) return;
  int M = 256; //there were 256 char
  int countSize = M + 2;
  int length = hi - lo + 1;

  int count[countSize] = {0};
  int sortIndex = currentIndex;
  for (size_t indexOfstrs = lo; indexOfstrs <= hi; indexOfstrs++) {
    std::string s = strs[indexOfstrs];
    size_t charIndex = charAt(s, sortIndex);
    ++count[charIndex + 2];
  }
  for (size_t indexOfCount = 1; indexOfCount < countSize; indexOfCount++) {
    count[indexOfCount] += count[indexOfCount-1];
  }
  std::string copy[length];
  for (size_t indexOfstrs = lo; indexOfstrs <= hi; indexOfstrs++) {
    std::string s = strs[indexOfstrs];
    size_t currentChar = charAt(s,sortIndex);
    size_t putIndex = count[currentChar+1];
    copy[putIndex] = s;
    ++count[currentChar+1];
  }
  for (size_t indexOfstrs = lo; indexOfstrs <= hi; indexOfstrs++) {
    strs[indexOfstrs] = copy[indexOfstrs - lo];
  }
  

  for (size_t indexofCount = 0; indexofCount < countSize - 1; indexofCount++){
    _msdSort(strs, lo + count[indexofCount], lo + count[indexofCount+1] - 1, currentIndex + 1);
  }
}

int main(){
    std::string is_one("onegroup");
    std::string is_two("twogroup");
    std::string is_three("threegroup");
    std::string is_three2("threfgroup");
    std::string is_three3("threggroup");
    std::string is_three4("fdathrdseggroup");
    std::string is_three5("2fdafdthreggroup");
    std::string is_three6("31d44threggroup");
    const int M = 8;
    std::string a[M] = {is_three, is_three2, is_two, is_one, is_three3, is_three4, is_three5, is_three6};
    for(int i = 0; i < M; i++){
        std::cout << a[i] << "\t";
    }
    msdSort(a, M);
    std::cout << "\nafter sort" << "\n";
    for(int i = 0; i < M; i++){
        std::cout << a[i] << "\t";
    }
}