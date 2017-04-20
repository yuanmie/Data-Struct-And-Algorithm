/*
索引字符串排序：
利用索引来对小部分字符串排序
假设数组长度为N，索引域大小为R
则该排序时间复杂度大致为O(R + N)。
该排序为稳定排序
*/
#include <string>
#include <iostream>

class IndexString{
public:
    IndexString():content(), index(-1){}
    IndexString(std::string s, int i): content(s), index(i){}
    std::string getContent(){
        return content;
    }
    int getIndex(){
        return index;
    }
private:
        std::string content;
        int index;
};

void indexStringSort(IndexString* indexStrArray, int length){
    int size = length;
    int countSize = length + 1;
    int count[countSize] = {0};

    for(int i = 0; i < length; i++){
        IndexString a = indexStrArray[i];
        //为了之后能正确统计索引的位置，故意加一
        ++count[a.getIndex() + 1];
    }

    for(int indexOfCount = 1; indexOfCount < countSize; indexOfCount++){
        //当前索引的位置等于之前索引个数之和，这就是上面为什么要加一
        count[indexOfCount] += count[indexOfCount-1];
    }

    //IndexString *copy = new IndexString[size];
    IndexString copy[size];
    int putIndex = 0;
    for(int i = 0; i < length; i++){
        IndexString a = indexStrArray[i];
        putIndex = count[a.getIndex()];
        copy[putIndex] = a;
        ++count[a.getIndex()];
    }

    for(int i = 0; i < size; i++){
        indexStrArray[i] = copy[i];
    }
}

int main(){
    IndexString is_one("one group", 1);
    IndexString is_two("tow group", 2);
    IndexString is_three("three group1", 3);
    IndexString is_three2("three group2", 3);
    IndexString is_three3("three group3", 3);
    const int M = 5;
    IndexString a[M] = {is_three, is_three2, is_two, is_one, is_three3};
    for(int i = 0; i < M; i++){
        std::cout << a[i].getContent() << "\t";
    }
    indexStringSort(a, M);
        std::cout << "\nafter sort" << "\n";
    for(int i = 0; i < M; i++){
        std::cout << a[i].getContent() << "\t";
    }
}
