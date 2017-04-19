/*
这个是用环形数组实现的队列
时间复杂度：
插入时间复杂度为O(1)
删除时间复杂度为O(1)
空间复杂度为O(n)
*/
#include <iostream>

template <typename T>
class ArrayQueue{
public:
	ArrayQueue(){ ArrayQueue(10); }
	ArrayQueue(int n) :size(n+1){ 
		S = new T[n];
		head = tail =  0;
	}
	~ArrayQueue(){
		 delete[] S; 
	};
	void enqueue(T t);
	void dequeue();
	T top();
	bool empty();

private:
	int size;
	T *S;
	int head;
	int tail;
};

template <typename T>
void ArrayQueue<T>::enqueue(T t){
	//queue is not full
	bool full = ( head != (tail+1) % size );
	if (full){
		S[tail] = t;
		tail = (tail+1) % size;
	}else{
		std::cout << "ArrayQueue is full, can't enqueue!!!" << std::endl;
	}
}

template <typename T>
void ArrayQueue<T>::dequeue()
{
	if (!empty()){
		head = (head + 1) % size;
	}else {
		std::cout << "ArrayQueue is empty, can't dequeue!!!" << std::endl;
	}
}

template <typename T>
T ArrayQueue<T>::top(){
	if (!empty()){
		return S[head];
	}else{
		std::cout << "ArrayQueue is empty!!!" << std::endl;
		return NULL;
	}
}

template <typename T>
bool ArrayQueue<T>::empty(){
	return head == tail;
}

int main(){
	ArrayQueue<int> S(2);
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

