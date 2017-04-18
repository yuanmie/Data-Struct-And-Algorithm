
// B_Tree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

#define  T 4
typedef struct B_Tree_Node
{
	int n;							//ָʾ�ý��Ĺؼ��ָ���
	int *keys;						//�ý��ؼ�������
	bool isLeaf;					//�ý���Ƿ���Ҷ�ӽ��
	struct B_Tree_Node **child;    //�ý������к��ӽ��
	struct B_Tree_Node *p;		    //�ý��ĸ����
}B_Tree_Node, *p_B_Tree_Node;

B_Tree_Node *alloact_Node()
{
	B_Tree_Node *newNode = new B_Tree_Node;
	newNode->n = 0;
	newNode->isLeaf = true;
	newNode->keys = new int[2 * T - 1];
	newNode->child = new p_B_Tree_Node[2 * T];
	newNode->p = NULL;
	for (int i = 0; i<2 * T; i++)
		newNode->child[i] = NULL;
	return newNode;
}
//���Ե�ǰ���Ϊ�����������У�Ѱ��k���ڵĽ�㣬
/*
curNode ��ʾ�õ�ǰ�����ĸ���㣬k ��Ҫ���ҵĹؼ��֣� index��������k�ڸý���е�����
�����ڵ�ǰ����в��� �����ڸý���У���ֱ�ӷ��ظý��ָ�룻���û���ҵ������Ҹý����Ҷ�ӽ�㣬�򷵻�NULL
�����������ʵ��ĺ��ӽ���в���
*/
B_Tree_Node * searchNode(B_Tree_Node *curNode, int k, int &index)
{
	int i = 0;
	while (i <= curNode->n && k >curNode->keys[i])
		i++;
	if (i<curNode->n && k == curNode->keys[i])  //�ҵ���k
	{
		index = i;
		return curNode;
	}
	if (curNode->isLeaf) //����ý����Ҷ�ӽ�㣬��k������
		return NULL;
	searchNode(curNode->child[i], k, index);

}

//splitNode_p�Ǳ����ѽ��ĸ���㣬i������Ϊi�ĺ���Ϊ������Ҫ������
//�����ѵĽ�������ģ���ô����n = 2*T - 1;������Ϊ����T-1���ؼ��ֵ��ӽ�㣬ͬʱ�����м�Ԫ�ر��������丸�ڵ���
void BTree_Child_Split(B_Tree_Node *splitNode_p, int index_child)
{
	B_Tree_Node *newChild = alloact_Node();
	newChild->n = T - 1;
	for (int i = 0; i<T - 1; i++)
	{
		newChild->keys[i] = splitNode_p->child[index_child]->keys[T + i];
	}
	splitNode_p->child[index_child]->n = T - 1;
	if (splitNode_p->child[index_child]->isLeaf != true)  //������ĵ�i�����Ӳ���Ҷ�ӽ�㣬�����ĺ�T������Ҳ�͸�newChild
	{
		newChild->isLeaf = false;
		for (int i = 0; i<T - 1; i++)
			newChild->child[i] = splitNode_p->child[i + T];
	}
	//��newChild ����ΪsplitNode_p�ĵ�i+1�����ӽ�㣬���м�ؼ�������������
	for (int i = splitNode_p->n; i >= index_child; i--)
	{
		splitNode_p->child[i + 1] = splitNode_p->child[i];
	}
	splitNode_p->n++;
	splitNode_p->child[index_child + 1] = newChild;
	for (int i = splitNode_p->n - 1; i >= index_child; i--)
	{
		splitNode_p->keys[i + 1] = splitNode_p->keys[i];
	}
	splitNode_p->keys[index_child] = splitNode_p->child[index_child]->keys[T - 1];
}

void BTree_Insert_NonFull(B_Tree_Node *nonfull, int k)
{
	int i = nonfull->n - 1;
	if (nonfull->isLeaf)
	{
		while (i >= 0 && k<nonfull->keys[i])
		{
			nonfull->keys[i + 1] = nonfull->keys[i];
			i--;
		}
		i = i + 1;
		(nonfull->n)++;
		nonfull->keys[i] = k;
	}
	else
	{
		while (i >= 0 && k<nonfull->keys[i])
			i--;
		i = i + 1;
		if (nonfull->child[i]->n == 2 * T - 1)
		{
			BTree_Child_Split(nonfull, i);
			if (k>nonfull->keys[i])
				i = i + 1;
		}
		BTree_Insert_NonFull(nonfull->child[i], k);
	}
}

//��B_Tree�м����µĹؼ��֣���Ҫ��BTree_Insert_NonFull��ʵ�֣�ȷ��ÿ�β���ʱ�����ʵĽ�㶼�Ƿ������;
//���ȣ��������Ϊ��������Ѹ����
void BTree_Insert_Node(p_B_Tree_Node *root, int k)
{
	B_Tree_Node *p = *root;
	if (p->n == 2 * T - 1) //����������
	{
		B_Tree_Node *newRoot = alloact_Node();
		newRoot->child[0] = (*root);
		newRoot->isLeaf = false;
		*root = newRoot;

		BTree_Child_Split(newRoot, 0);
		BTree_Insert_NonFull(newRoot, k);
	}
	else
		BTree_Insert_NonFull(*root, k);
}

void printBFS(B_Tree_Node *t)
{
	if (NULL == t)
		return;

	//�����ǰ�ڵ����йؼ���
	cout << "[";
	for (int i = 0; i < t->n; ++i)
	{
		cout << t->keys[i];
		if (t->n - 1 != i)
			cout << " ";
	}
	cout << "]" << endl;

	//�ݹ������������
	for (int i = 0; i <= t->n; ++i)
		printBFS(t->child[i]);

}

//delete
/*
subNode,��ǰ��㣬����Ϊ��������ɾ��k
1.��k�Ƿ��������subNodeΪ���������У��������򷵻أ����������
2.��k�Ƿ�����ڵ�ǰ��㣺��1�������Ҹýڵ�ΪҶ�ӽڵ㣬��ֱ��ɾ��k;(2)�����Ҹýڵ�Ϊ�ڲ��ڵ㣬��������ۣ���3�������ڣ����ҳ������ĺ���x.ciΪ���������а���k,

Different Case:
1.�����ڵ�ǰ��㣬�Ҹý��Ϊ�ڲ���㣺
case 1:�ý����ǰ��k���ӽ��y�������ٰ���T��Ԫ�أ����ҳ�k'�滻k,���ݹ��ɾ��k';
case 2:�ý����ǰ��k���ӽ��z����ֻ����T-1��Ԫ�أ�������k���ӽ���������ٰ���T��Ԫ�أ�ͬ���ҳ�k'�滻k,�ݹ��ɾ��k';
case 3�����������ӽ���ֻ����T-1��Ԫ�أ���ô��k��z�ӽ���е�Ԫ�ؾ��鲢��y�С��ٵݹ�ɾ��k
2.k�������ڵ�ǰ�Ľ����,�����������ĺ���x.ciΪ���������С�
case 1:��x.ci�����ٰ�����T��Ԫ�أ��ݹ���ɾ��k
case 2:��x.ci��ֻ��T-1��Ԫ�أ���x.ci-1��x.ci+1��������T��Ԫ�أ��ս�x�к��ʵ�Ԫ��ȡ������x.ci,x.ci-1��x.ci+1�к��ʵ�Ԫ��ȡ������x,�ݹ�ɾ��k
case 3����x.ci-1��x.ci+1�о�ֻ��T-1��Ԫ�أ���ô��x.ci-1��x.ci�ϲ��������������ϲ�������x�к��ʵ�Ԫ����Ϊ���ǵ��м�ؼ��֡�

*/
void BTree_delete_key(B_Tree_Node *subNode, int k)
{
	int index = 0;
	B_Tree_Node *deleteNode = NULL;
	if ((deleteNode = searchNode(subNode, k, index)) == NULL)
		return;
	int keyIndex = -1;
	for (int i = 0; i<subNode->n; i++)
	{
		if (k == subNode->keys[i])
		{
			keyIndex = i;
			break;
		}
	}
	//����ڵ�ǰ��㣬�ҵ�ǰ���ΪҶ�ӽ�㣬��ֱ��ɾ��k
	//OK******************************
	if (keyIndex != -1 && subNode->isLeaf)
	{
		for (int i = keyIndex; i<subNode->n - 1; i++)
		{
			subNode->keys[i] = subNode->keys[i + 1];
		}
		(subNode->n)--;
	}
	//����ڵ�ǰ����У��ҵ�ǰ��㲻ΪҶ�ӽ��
	else if (keyIndex != -1 && subNode->isLeaf != true)
	{
		B_Tree_Node *processorNode = subNode->child[keyIndex];
		B_Tree_Node *succssorNode = subNode->child[keyIndex + 1];
		//���С��k�ĺ��ӽ��ؼ���������T
		if (processorNode->n >= T)
		{
			int k1 = processorNode->keys[processorNode->n - 1];
			subNode->keys[keyIndex] = k1;
			BTree_delete_key(processorNode, k1);
		}
		//�������k�ĺ��ӽ��ؼ���������T
		else if (succssorNode->n >= T)
		{
			int k1 = succssorNode->keys[0];
			subNode->keys[keyIndex] = k1;
			BTree_delete_key(succssorNode, k1);
		}
		//����������ӽ��ؼ�������������T,��k���Һ��ӽ��Ĺؼ��ֹ鲢��������
		else
		{
			for (int j = 0; j<T - 1; j++)
			{
				//processorNode->keys[T-1] = k;������ò�Ҫʹ��T��ʾ����Ϊ����Ǹ����Ļ����������Ĺؼ�������ΪT
				processorNode->keys[processorNode->n] = k;
				processorNode->keys[processorNode->n + 1 + j] = succssorNode->keys[j];
			}

			processorNode->n = 2 * T - 1;
			//��subNode->child[keyIndex+1]�ĺ��Ӵ������ں���
			if (!processorNode->isLeaf)
			{
				for (int j = 0; j<T; j++)
				{
					processorNode->child[T + j] = succssorNode->child[j];
				}
			}
			//�޸�subNode�е�keyֵ
			for (int j = keyIndex; j<subNode->n - 1; j++)
			{
				subNode->keys[j] = subNode->keys[j + 1];
			}
			subNode->n = subNode->n - 1;
			delete succssorNode;
			BTree_delete_key(processorNode, k);


		}

	}
	else if (keyIndex == -1) //���ڵ�ǰ�����
	{
		int childIndex = 0;
		B_Tree_Node *deleteNode = NULL;
		//Ѱ�Һ��ʵ��Ӻ��ӣ��Ը��Ӻ���Ϊ����������k
		for (int j = 0; j<subNode->n; j++)
		{
			if (k<subNode->keys[j])
			{
				childIndex = j;
				deleteNode = subNode->child[j];
				break;
			}
		}
		//������Ӻ��ӵĹؼ�����С��T,�������������
		if (deleteNode->n <= T - 1)
		{
			//deleteNode�����ֵܽ��
			B_Tree_Node *LeftNode = subNode->child[childIndex - 1];
			//deleteNode�����ֵܽ��
			B_Tree_Node *RightNode = subNode->child[childIndex + 1];
			//������ֵܽ��ؼ���������T,��������еĵ�childIndex-1��Ԫ���͸�deleteNode,��Left�е����Ԫ���͸�����㣬
			if (childIndex >= 1 && LeftNode->n >= T)
			{
				for (int i = deleteNode->n; i>0; i--)
				{
					deleteNode->keys[i] = deleteNode->keys[i - 1];
				}
				deleteNode->keys[0] = subNode->keys[childIndex];
				subNode->keys[childIndex] = LeftNode->keys[LeftNode->n - 1];
				(LeftNode->n)--;
				(deleteNode->n)++;
				BTree_delete_key(deleteNode, k);
			}
			//������ֵܹؼ��ִ���T,��������еĵ�childIndex��Ԫ���͸�deleteNode,��Right�е���СԪ���͸�����㣬
			else if (childIndex<subNode->n && RightNode->n >= T)
			{
				deleteNode->keys[deleteNode->n] = subNode->keys[childIndex];
				subNode->keys[childIndex] = RightNode->keys[0];
				for (int i = 0; i<RightNode->n - 1; i++)
					RightNode[i] = RightNode[i + 1];
				(RightNode->n)--;
				(deleteNode->n)++;
				BTree_delete_key(deleteNode, k);
			}
			//������ֵܺ����ֵܵĹؼ�������������T,�����ֵܻ����ֵ�����ϲ�
			else
			{
				if (childIndex >= 1)//���ֵܴ��ڣ��ϲ�
				{
					//��keys�ϲ�
					for (int i = 0; i<deleteNode->n; i++)
					{
						LeftNode->keys[LeftNode->n + i] = deleteNode->keys[i];
					}
					//�����Ҷ�ӽ�㣬��Ҷ��Ҳ�ϲ�
					if (!deleteNode->isLeaf)
					{
						for (int i = 0; i<deleteNode->n + 1; i++)
						{
							LeftNode->child[LeftNode->n + 1 + i] = deleteNode->child[i];
						}

					}
					LeftNode->n = LeftNode->n + deleteNode->n;

					//����subNode���ӽڵ�
					for (int i = childIndex; i<subNode->n; i++)
					{
						subNode->child[i] = subNode->child[i + 1];
					}
					BTree_delete_key(LeftNode, k);
				}
				else //�ϲ��������ֵ�
				{
					//��keys�ϲ�
					for (int i = 0; i<RightNode->n; i++)
					{
						deleteNode->keys[i + deleteNode->n] = RightNode->keys[i];
					}
					//�����Ҷ�ӽ�㣬��Ҷ�Ӻϲ�
					if (!deleteNode->isLeaf)
					{
						for (int i = 0; i<RightNode->n + 1; i++)
						{
							deleteNode->child[deleteNode->n + 1 + i] = RightNode->child[i];
						}
					}
					deleteNode->n = deleteNode->n + RightNode->n;

					//����subNode���ӽڵ�
					for (int i = childIndex + 1; i<subNode->n; i++)
					{
						subNode->child[i] = subNode->child[i + 1];
					}
					BTree_delete_key(deleteNode, k);
				}
			}

		}
		BTree_delete_key(deleteNode, k);
	}
}

void createBTree(p_B_Tree_Node *root)
{
	int a[] = { 12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17 };
	for (int i = 0; i<20; i++)
	{
		BTree_Insert_Node(root, a[i]);
		printBFS(*root);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	B_Tree_Node *root = alloact_Node();
	createBTree(&root);
	cout << "B_Tree after delete 12:" << endl;
	BTree_delete_key(root, 12);
	printBFS(root);
	cout << "B_Tree after delete 1:" << endl;
	BTree_delete_key(root, 1);
	printBFS(root);
	cout << "B_Tree after delete 9:" << endl;
	BTree_delete_key(root, 9);
	printBFS(root);
	cout << "B_Tree after delete 2:" << endl;
	BTree_delete_key(root, 2);
	printBFS(root);

	return 0;
}


