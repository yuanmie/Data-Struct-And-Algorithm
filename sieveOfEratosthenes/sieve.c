#include <stdio.h>
#include <malloc.h>
void sieve(int);

int main(int argc, char *argv)
{
     int n = 10;
     sieve(n);
     return 0;
}

void sieve(int n)
{
     int *a;
     a = (int *)malloc(n * sizeof(int));
     int i = 0, j = 0;

     //初始化数组中的元素为1，代表真
     for (i = 2; i <= n; i++)
     {
	  a[i] = 1;
     }

     for (i = 2; i <= n; i++)
     {
	  //选出第一个素数
	  if (a[i] == 1)
	  {
	       //将2i，3i...设为0
	       for (j = i; (i * j) <= n; j++)
	       {
		    a[i * j] = 0;
	       }
	  }
     }

     //数组中值为1的项的下标就是素数
     printf("\nPrimes numbers from 1 to %d are:", n);
     for (i = 2; i <= n; i++)
     {
	  if (a[i] == 1)
	       printf("%d, ", i);
     }

     printf("\n");
}
