// List.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct ListNode
{
	int value;
	struct ListNode* pNext;
};

typedef struct ListNode L;

L* initNode()
{
	L* head;
	head->value = 0;
	head->pNext = NULL;
}

L* list_search(L* head, int k)
{
	L* x = head;
	while (x != NULL && x->value != k)
		x = x->pNext;

	return x;
}

void list_insert(L* head, int k)
{

}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

