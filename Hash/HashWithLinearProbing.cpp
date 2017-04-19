/*
这个hashtable只是为了实践基于线性探测的hash碰撞解决思路。
暂时并不能干什么。

假设插入的数据量为N，hashtable的大小为M。


*/

#include <iostream>
#include <string>

template <typename KEY, typename VALUE>
class HashTable{
public:
    HashTable(int m):M(m){
        hashArray = new VALUE[M];
        keyArray = new KEY[M];
        hasHash = new bool[M];
        //INIT
        for(int index = 0; index < M; index++){
          hasHash[index] = false;
        }
    }
    ~HashTable(){
          // release all resource
          delete[] keyArray;
          delete[] hashArray;
    }
    void push(KEY k, VALUE v);
    VALUE find(KEY t);
    void discard(KEY k);

    void debug(){
      for(int index = 0; index < M; index++){
        if(hasHash[index] && (std::cout << index << " " <<keyArray[index] << std::endl)) ;
        if(hasHash[index]  && (std::cout << hashArray[index] << std::endl)) ;
      }
    }
private:
  int hash(KEY k){
      return k % M;
  }
  
  bool equal(KEY lhs, KEY rhs){
    std::cout << lhs << " and " << rhs << std::endl;
    return lhs == rhs;
  }
  int M;
  VALUE *hashArray;
  KEY *keyArray;
  bool *hasHash;
};

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::push(KEY k, VALUE v){
    int hashcode = hash(k);
    bool collision = hasHash[hashcode];
    
    if(collision){
        //look up next empty position
        for(int start = hashcode + 1; start < M; ++start){
          if( !hasHash[start] ){
            keyArray[start] = k;
            hashArray[start] = v;
            hasHash[start] = true;
            return;
          }
        }
        
        std::cout << "push failed!!!" << std::endl;
        return;
    }
    keyArray[hashcode] = k;
    hashArray[hashcode] = v;
    hasHash[hashcode] = true;
}

template <typename KEY, typename VALUE>
VALUE HashTable<KEY, VALUE>::find(KEY k){
    VALUE defaultReturnValue;
    int hashcode = hash(k);
    bool collision = hasHash[hashcode] ;
    
    if(collision){
        //look up next empty position
        for(int start = hashcode; start < M; ++start){
          KEY current = keyArray[start];
          if(hasHash[start] && current == k ){
            return hashArray[start];
          }
        }
    }
    return defaultReturnValue;
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::discard(KEY k){
  int hashcode = hash(k);
  bool collision = hasHash[hashcode];
  
  if(collision){
      //look up next empty position
      for(int start = hashcode; start < M; ++start){
        KEY current = keyArray[start];
        if(hasHash[start] && equal(current,k)){
          hasHash[start] = false;
        }
      }
  }
}

int main(){
    HashTable<int, std::string> h(10);
    int a = 1;
    std::string s = "test string 1";
    h.push(a, s);
    //h.debug();
    std:: cout << h.find(1) << std::endl;
    h.push(10, "test string 10");
        std:: cout << h.find(77) << std::endl;
    h.push(99, "test string 99");
        std:: cout << h.find(1) << std::endl;
    h.push(56, "test string 56");
    std:: cout << "find(21)" << std::endl;
    h.discard(1);
    std:: cout << "find(1)" << std::endl;
        std:: cout << h.find(1) << std::endl;
    h.push(77, "test string 77");
        std:: cout << h.find(1) << std::endl;
        std:: cout << "find(1)" << std::endl;
}
