/*
这个是用链表实现的双端队列
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
			 std::cout << current->content << std::endl;
       next = current->next;
       delete current;
       current = next;
     }
     head = NULL;
		 tail = NULL;
	};
	void push_front(T t);
	void push_back(T t);
	void pop_front();
	void pop_back();
	T front();
  T back();
	bool empty();
  int size();

private:
  class Node{
  public:
    T content;
    Node* next;
		Node* prev;
    Node(T t):content(t), next(NULL), prev(NULL){}
  };
	int _size;
	Node *head;
	Node *tail;
};

template <typename T>
void LinkedQueue<T>::push_back(T t){
	Node* newNode = new Node(t);
  if(head == NULL){
    head = newNode;
    tail = head;
  }else{
    tail->next = newNode;
		newNode->prev = tail;
    tail = newNode;
  }
  ++_size;
}

template <typename T>
void LinkedQueue<T>::push_front(T t){
	Node* newNode = new Node(t);
  if(head == NULL){
    head = newNode;
    tail = head;
  }else{
    newNode->next = head;
		head->prev = newNode;
    head = newNode;
  }
  ++_size;
}

template <typename T>
void LinkedQueue<T>::pop_front()
{
	assert(!empty());
  Node* newHead = head->next;
  delete head;
  head = newHead;
  --_size;
}


template <typename T>
void LinkedQueue<T>::pop_back()
{
	assert(!empty());

  Node* newTail = tail->prev;
  delete tail;
	newTail->next = NULL;
  tail = newTail;
  --_size;
}

template <typename T>
T LinkedQueue<T>::front(){
  assert(!empty());
	return head->content;
}

template <typename T>
T LinkedQueue<T>::back(){
  assert(!empty());
	return tail->content;
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
	S.push_back(10);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	S.push_back(20);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	
	S.push_back(30);
	std::cout << "s is empty? :" << S.empty() << std::endl;
	S.pop_front();
	std::cout << "s is empty? :" << S.empty() << std::endl;
	
	S.pop_back();
	std::cout << "s is empty???? :" << S.empty() << std::endl;
	return 0;
}

