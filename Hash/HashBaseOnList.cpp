/*
这个hashtable只是为了实践基于链表的hash碰撞解决思路。
暂时并不能干什么。

假设插入的数据量为N，hashtable的大小为M，则均摊每条链表的长度为N/M。
以此来计算复杂度：
push:O(N/M)
find:O(N/M)
discard:O(N/M)
*/

#include <iostream>
#include <string>

template <typename KEY, typename VALUE>
class HashTable{
public:
    HashTable(int m):M(m){
        hashArray = new Node* [M];
        for(int index = 0; index < M; index++){
            hashArray[index] = NULL;
        }
    }
    ~HashTable(){
          // release all resource
          Node *head = NULL;
          for(int index = 0; index < M; index++){
              head = hashArray[index];
              if(head != NULL){
                  Node* next = NULL;
                  while(head != NULL){
                      next = head->next;
                      delete head;
                      head = next;
                  }
              }
          }
          delete[] hashArray;
    }
    void push(KEY k, VALUE v);
    VALUE find(KEY t);
    void discard(KEY k);

private:
  class Node{
  public:
    KEY content;
    VALUE v;
    Node *next;
    Node(KEY t, VALUE v):content(t), v(v), next(NULL){}
};

  int hash(KEY k){
      return k % M;
  }
  int M;
  Node **hashArray;
};

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::push(KEY k, VALUE v){
    int hashcode = hash(k);
    Node *head = hashArray[hashcode];
    bool collision = (head != NULL);
    Node *newNode = new Node(k , v);
    if(collision){
        newNode->next = head;
    }
    hashArray[hashcode] = newNode;
}

template <typename KEY, typename VALUE>
VALUE HashTable<KEY, VALUE>::find(KEY k){
    VALUE defaultReturnValue;
    int hashcode = hash(k);
    Node *head = hashArray[hashcode];
    bool collision = (head != NULL);
    if(collision){
        while(head != NULL){
            if(head->content == k){
                return head->v;
            }
            head = head->next;
        }
    }
    return defaultReturnValue;
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::discard(KEY k){
    int hashcode = hash(k);
    Node *head = hashArray[hashcode];
    bool collision = (head != NULL);
    if(collision){
        Node *prev = NULL;
        while(head != NULL){
            if(head->content == k){
                if(prev == NULL){
                    hashArray[hashcode] = head->next;
                }else{
                    prev->next = head->next;
                }
                delete head;
                return;
            }
            prev = head;
            head = head->next;
        }
    }
}

int main(){
    HashTable<int, std::string> h(10);
    h.push(1, "test string 1");
    std:: cout << h.find(1) << std::endl;
    h.push(10, "test string 10");
        std:: cout << h.find(77) << std::endl;
    h.push(99, "test string 99");
        std:: cout << h.find(1) << std::endl;
    h.push(56, "test string 56");
    h.discard(1);
        std:: cout << h.find(1) << std::endl;
    h.push(77, "test string 77");
        std:: cout << h.find(1) << std::endl;
}
