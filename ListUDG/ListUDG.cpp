/**
* C++: �ڽӱ��ʾ��"����ͼ(List Undirected Graph)"
*
*/
#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
// �ڽӱ�
class ListUDG
{
private: // �ڲ���
	// �ڽӱ��б��Ӧ������Ķ���
	class ENode
	{
	public:
		int ivex;           // �ñ���ָ��Ķ����λ��
		ENode *nextEdge;    // ָ����һ������ָ��
	};

	// �ڽӱ��б�Ķ���
	class VNode
	{
	public:
		char data;          // ������Ϣ
		ENode *firstEdge;   // ָ���һ�������ö���Ļ�
	};

private: // ˽�г�Ա
	int mVexNum;             // ͼ�Ķ������Ŀ
	int mEdgNum;             // ͼ�ıߵ���Ŀ
	VNode mVexs[MAX];

public:
	// �����ڽӱ��Ӧ��ͼ(�Լ�����)
	ListUDG();
	// �����ڽӱ��Ӧ��ͼ(�����ṩ������)
	ListUDG(char vexs[], int vlen, char edges[][2], int elen);
	~ListUDG();

	// ���������������ͼ
	void DFS();
	// ����������������������Ĳ�α�����
	void BFS();
	// ��ӡ�ڽӱ�ͼ
	void print();

private:
	// ��ȡһ�������ַ�
	char readChar();
	// ����ch��λ��
	int getPosition(char ch);
	// ���������������ͼ�ĵݹ�ʵ��
	void DFS(int i, int *visited);
	// ��node�ڵ����ӵ�list�����
	void linkLast(ENode *list, ENode *node);
};

/*
* �����ڽӱ��Ӧ��ͼ(�Լ�����)
*/
ListUDG::ListUDG()
{
	char c1, c2;
	int v, e;
	int i, p1, p2;
	ENode *node1, *node2;

	// ����"������"��"����"
	cout << "input vertex number: ";
	cin >> mVexNum;
	cout << "input edge number: ";
	cin >> mEdgNum;
	if (mVexNum < 1 || mEdgNum < 1 || (mEdgNum >(mVexNum * (mVexNum - 1))))
	{
		cout << "input error: invalid parameters!" << endl;
		return;
	}

	// ��ʼ��"�ڽӱ�"�Ķ���
	for (i = 0; i<mVexNum; i++)
	{
		cout << "vertex(" << i << "): ";
		mVexs[i].data = readChar();
		mVexs[i].firstEdge = NULL;
	}

	// ��ʼ��"�ڽӱ�"�ı�
	for (i = 0; i<mEdgNum; i++)
	{
		// ��ȡ�ߵ���ʼ����ͽ�������
		cout << "edge(" << i << "): ";
		c1 = readChar();
		c2 = readChar();

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		// ��ʼ��node1
		node1 = new ENode();
		node1->ivex = p2;
		// ��node1���ӵ�"p1���������ĩβ"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
		// ��ʼ��node2
		node2 = new ENode();
		node2->ivex = p1;
		// ��node2���ӵ�"p2���������ĩβ"
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			linkLast(mVexs[p2].firstEdge, node2);
	}
}

/*
* �����ڽӱ��Ӧ��ͼ(�����ṩ������)
*/
ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
{
	char c1, c2;
	int i, p1, p2;
	ENode *node1, *node2;

	// ��ʼ��"������"��"����"
	mVexNum = vlen;
	mEdgNum = elen;
	// ��ʼ��"�ڽӱ�"�Ķ���
	for (i = 0; i<mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	// ��ʼ��"�ڽӱ�"�ı�
	for (i = 0; i<mEdgNum; i++)
	{
		// ��ȡ�ߵ���ʼ����ͽ�������
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		// ��ʼ��node1
		node1 = new ENode();
		node1->ivex = p2;
		// ��node1���ӵ�"p1���������ĩβ"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
		// ��ʼ��node2
		node2 = new ENode();
		node2->ivex = p1;
		// ��node2���ӵ�"p2���������ĩβ"
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			linkLast(mVexs[p2].firstEdge, node2);
	}
}

/*
* ��������
*/
ListUDG::~ListUDG()
{
}

/*
* ��node�ڵ����ӵ�list�����
*/
void ListUDG::linkLast(ENode *list, ENode *node)
{
	ENode *p = list;

	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

/*
* ����ch��λ��
*/
int ListUDG::getPosition(char ch)
{
	int i;
	for (i = 0; i<mVexNum; i++)
	if (mVexs[i].data == ch)
		return i;
	return -1;
}

/*
* ��ȡһ�������ַ�
*/
char ListUDG::readChar()
{
	char ch;

	do {
		cin >> ch;
	} while (!((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')));

	return ch;
}


/*
* ���������������ͼ�ĵݹ�ʵ��
*/
void ListUDG::DFS(int i, int *visited)
{
	ENode *node;

	visited[i] = 1;
	cout << mVexs[i].data << " ";
	node = mVexs[i].firstEdge;
	while (node != NULL)
	{
		if (!visited[node->ivex])
			DFS(node->ivex, visited);
		node = node->nextEdge;
	}
}

/*
* ���������������ͼ
*/
void ListUDG::DFS()
{
	int i;
	int visited[MAX];       // ������ʱ��

	// ��ʼ�����ж��㶼û�б�����
	for (i = 0; i < mVexNum; i++)
		visited[i] = 0;

	cout << "DFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
			DFS(i, visited);
	}
	cout << endl;
}

/*
* ����������������������Ĳ�α�����
*/
void ListUDG::BFS()
{
	int head = 0;
	int rear = 0;
	int queue[MAX];     // �������
	int visited[MAX];   // ������ʱ��
	int i, j, k;
	ENode *node;

	for (i = 0; i < mVexNum; i++)
		visited[i] = 0;

	cout << "BFS: ";
	for (i = 0; i < mVexNum; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			cout << mVexs[i].data << " ";
			queue[rear++] = i;  // �����
		}
		while (head != rear)
		{
			j = queue[head++];  // ������
			node = mVexs[j].firstEdge;
			while (node != NULL)
			{
				k = node->ivex;
				if (!visited[k])
				{
					visited[k] = 1;
					cout << mVexs[k].data << " ";
					queue[rear++] = k;
				}
				node = node->nextEdge;
			}
		}
	}
	cout << endl;
}

/*
* ��ӡ�ڽӱ�ͼ
*/
void ListUDG::print()
{
	int i, j;
	ENode *node;

	cout << "List Graph:" << endl;
	for (i = 0; i < mVexNum; i++)
	{
		cout << i << "(" << mVexs[i].data << "): ";
		node = mVexs[i].firstEdge;
		while (node != NULL)
		{
			cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
			node = node->nextEdge;
		}
		cout << endl;
	}
}

int main()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'C' },
		{ 'A', 'D' },
		{ 'A', 'F' },
		{ 'B', 'C' },
		{ 'C', 'D' },
		{ 'E', 'G' },
		{ 'F', 'G' } };
	int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);
	ListUDG* pG;

	// �Զ���"ͼ"(����������)
	//pG = new ListUDG();
	// �������е�"ͼ"
	pG = new ListUDG(vexs, vlen, edges, elen);

	pG->print();   // ��ӡͼ
	pG->DFS();     // ������ȱ���
	pG->BFS();     // ������ȱ���

	return 0;
}
