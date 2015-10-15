// QuickSort.cpp : 定义控制台应用程序的入口点。
// 时间复杂度：O(nlogn)

#include "stdafx.h"

template <typename T>
void quicksort(T *A, int p, int r);

template <typename T>
int partition(T *A, int p, int r);

/*
 *交换数组2个下标的值
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
		选出主元，在主元左边的都小于主元，在主元右边的都大于主元
		*/
		int q = partition(A, p, r);

		//递归排序其他的两部分
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

template <typename T>
int partition(T *A, int p, int r)
{
	//选A[r]为主元
	T x = A[r];
	int i = p - 1;

	//j指向小于主元元素的下标，i指向大于主元元素的下标，然后交换i，j位置的值
	for (int j = p; j < r; ++j)
	{
		if (A[j] <= x)
		{
			++i;
			swap(A, i, j);
		}
	}

	//交换i+1和主元下标的值
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