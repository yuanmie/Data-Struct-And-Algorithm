/*
这个是用链表实现的队列
时间复杂度：
插入时间复杂度为O(1)
删除时间复杂度为O(1)
空间复杂度为O(n)
*/
#include <iostream>
#include <cassert>

template <typename T>
class LinkedQueue{
public:
	LinkedQueue():head(NULL), tail(NULL){}
	~LinkedQueue(){
		 //release all the node
     Node *current = head;
     Node *next = NULL;
     while(current != NULL){
       next = current->next;
       delete current;
       current = next;
     }
     head = NULL;
	};
	void enqueue(T t);
	void dequeue();
	T top();
	bool empty();
  int size();

private:
  class Node{
  public:
    T content;
    Node* next;
    Node(T t):content(t), next(NULL){}
  };
	int _size;
	Node *head;
	Node *tail;
};

template <typename T>
void LinkedQueue<T>::enqueue(T t){
	Node* newNode = new Node(t);
  if(head == NULL){
    head = newNode;
    tail = head;
  }else{
    tail->next = newNode;
    tail = tail->next;
  }
  ++_size;
}

template <typename T>
void LinkedQueue<T>::dequeue()
{
	assert(!empty());
  Node* newHead = head->next;
  delete head;
  head = newHead;
  --_size;
}

template <typename T>
T LinkedQueue<T>::top(){
  assert(!empty());
	return head->content;
}

template <typename T>
bool LinkedQueue<T>::empty(){
	return head == NULL;
}

template <typename T>
int LinkedQueue<T>::size(){
	return _size;
}
int main(){
	LinkedQueue<int> S;
	std::cout << "s is empty? :" << S.empty() << std::endl;
	S.enqueue(10);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	S.enqueue(20);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	
	S.enqueue(30);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	S.dequeue();
	std::cout << "s is empty? :" << S.empty() << std::endl;
	return 0;
}

