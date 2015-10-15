// QuickSort.cpp : �������̨Ӧ�ó������ڵ㡣
// ʱ�临�Ӷȣ�O(nlogn)

#include "stdafx.h"

template <typename T>
void quicksort(T *A, int p, int r);

template <typename T>
int partition(T *A, int p, int r);

/*
 *��������2���±��ֵ
*/
template <typename T>
void swap(T *A, int i, int j)
{
	T temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

template <typename T>
void quicksort(T *A, int p, int r)
{
	if (p < r)
	{
		/*
		ѡ����Ԫ������Ԫ��ߵĶ�С����Ԫ������Ԫ�ұߵĶ�������Ԫ
		*/
		int q = partition(A, p, r);

		//�ݹ�����������������
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

template <typename T>
int partition(T *A, int p, int r)
{
	//ѡA[r]Ϊ��Ԫ
	T x = A[r];
	int i = p - 1;

	//jָ��С����ԪԪ�ص��±꣬iָ�������ԪԪ�ص��±꣬Ȼ�󽻻�i��jλ�õ�ֵ
	for (int j = p; j < r; ++j)
	{
		if (A[j] <= x)
		{
			++i;
			swap(A, i, j);
		}
	}

	//����i+1����Ԫ�±��ֵ
	swap(A, i + 1, r);
	return i + 1;
}



template <typename T>
void test(T *A, int len, char* testname)
{
	printf("\nthis is %s", testname);
	printf("before quicksort\n");

	for (int index = 0; index < len; index++)
	{
		printf("\t%d", A[index]);
	}

	quicksort(A, 0, len - 1);
	printf("\nafter quicksort\n");

	for (int index = 0; index < len; index++)
	{
		printf("\t%d", A[index]);
	}
	printf("\n");
}

void test1()
{
	double array[] = { 1.1, 4.2, 0.4, 2.0 };
	test(array, 4, "test1");
}

void test2()
{
	int array[] = { 2, 4, 1, 6, 8, 0, 9 };
	test(array, 7, "test2");
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
}