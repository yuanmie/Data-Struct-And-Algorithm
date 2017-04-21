/*
快速3向字符串排序，将数组划为小于，等于，大于3类。
然后递归的采用同样的步骤，达到排序的目的。
时间复杂度为：
O(n) = n/3 + n/3 + n/3 + O(n/3) + O(n/3) + O(n/3)
==> O(n) = (nlog_3^n)
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>

using std::string;
using std::cout;

void _quick3Sort(string* strs, int lo, int hi, int d);

int charAt(const std::string& str, int index){
  assert(index >= 0);
  int strLen = str.length();
  if(index < strLen){
    return (int)str[index];
  }else{
    return -1;
  }
}

void swap(string* str, int src, int dest){
  string temp = str[src];
  str[src] = str[dest];
  str[dest] = temp;
}

void quick3Sort(string* strs, int length){
  assert(length > 0);
  _quick3Sort(strs, 0, length-1, 0);
}

void _quick3Sort(string* strs, int lo, int hi, int d){
  if(lo >= hi) return;
  
  int v = charAt(strs[lo], d);
  int i = lo + 1;
  int lt = lo;
  int gt = hi;
  while( i <= gt ){
    int t = charAt(strs[i], d);
    if(t < v){
      swap(strs, i, lt);
      ++i;
      ++lt;
    }else if(t > v){
      swap(strs, i, gt);
      --gt;
    }else{
      ++i;
    }
  }
  
  _quick3Sort(strs, lo, lt-1, d);
  if(v > 0){
    _quick3Sort(strs, lt, gt, d+1);
  }
  _quick3Sort(strs, gt+1, hi, d);
}

int main(){
  string s1("are");
  string s2("by");
  string s3("sea");
  string s4("seashells");
  string s5("seashells");
  string s6("sells");
  string s7("sells");
  string s8("she");
  string s9("she");
  string s10("shells");
  string s11("shore");
  string s12("surely");
  string s13("the");
  string s14("the");
  int M = 14;
  string strs[M] = {s1,s11,s14,s12,s13,s8,s9,s10,s2,s3,s7,s6,s5,s4};
  for(int i = 0; i < M; i++){
      std::cout << strs[i] << "\t";
  }
  printf("start sort\n");
  quick3Sort(strs, 14);
  printf("after sort\n");
  for(int i = 0; i < M; i++){
      std::cout << strs[i] << "\t";
  }
}