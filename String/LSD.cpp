/*
LSD字符串排序算法，适用于所有长度相等的字符串。
按照从右到左的顺序，将每个字符当做索引来进行索引排序.
假设字符串的长度为S，字符串数组的长度为N，则该排序的时候复杂度O(S*N)
该排序为稳定排序
*/
#include <cassert>
#include <iostream>
#include <string>

void mlsdSort(std::string* strs, int length){
  assert(length > 0);
  int M = 256; //there were 256 char
  int countSize = M + 1;
  int strLen = strs[0].length();
  for(int i = strLen - 1; i >= 0; i--){
    int count[countSize] = {0};
    int sortIndex = i;
    for (size_t indexOfstrs = 0; indexOfstrs < length; indexOfstrs++) {
      std::string s = strs[indexOfstrs];
      size_t charIndex = (int)s[sortIndex];
      ++count[charIndex + 1];
    }
    
    for (size_t indexOfCount = 1; indexOfCount < countSize; indexOfCount++) {
      count[indexOfCount] += count[indexOfCount-1];
    }
    
    std::string copy[length];
    for (size_t indexOfstrs = 0; indexOfstrs < length; indexOfstrs++) {
      std::string s = strs[indexOfstrs];
      size_t currentChar = s[sortIndex];
      size_t putIndex = count[currentChar];
      copy[putIndex] = s;
      ++count[currentChar];
    }
    
    for (size_t indexOfstrs = 0; indexOfstrs < length; indexOfstrs++) {
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