#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int isPrime(int x)
{
	for (int i = 2; i <= x/2; i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

int findNextPrime(int x)
{
	x++;
	while (1)
	{
		if (isPrime(x))
			return x;
		x++;
	}
}

int findLastPrime(int x)
{
	x--;
	while (x > 1)
	{
		if (isPrime(x))
			return x;
		x--;
	}
	return x;
}

double iter(int n)
{
	int donji = 1;
	int fib1 = 1, fib2 = 1;
	for (int i = 0; i < n+1; i++)
		donji = findNextPrime(donji);
	for (int i = 0; i < n-1; i++)
	{
		fib2 += fib1;
		fib1 = fib2 - fib1;
	}
	//printf("Donji: %d\n", donji);
	//printf("Fib1: %d Fib2: %d\n", fib1, fib2);
	double sum = sqrt(1.0 * fib2 / donji);
	donji = findLastPrime(donji);
	fib1 = fib2 - fib1;
	fib2 = fib2 - fib1;
	for (int i = 0; i < n; i++)
	{
		//printf("Donji: %d\n", donji);
		//printf("Fib1: %d Fib2: %d\n", fib1, fib2);
		sum = sqrt(1.0 * fib2 / donji + sum);
		donji = findLastPrime(donji);
		fib1 = fib2 - fib1;
		fib2 = fib2 - fib1;
	}
	return sum;
}

double rek(int n, int donji, int fib1, int fib2)
{
	if (n == 0)
		return sqrt(1.0 * fib1 / donji);
	return sqrt(1.0 * fib1 / donji + rek(n-1, findNextPrime(donji), fib2, fib1 + fib2));
}

void prvi()
{
	int n;
	scanf("%d", &n);
	printf("%lf\n", iter(n));
	printf("%lf\n", rek(n, 2, 1, 1));
}

void stampaj_matricu(int mat[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

void drugi()
{
	int n;
	scanf("%d", &n);
	int mat[100][100];
	int br = 1;
	
	for (int j = n-1; j >= 0; j--)
		for (int tempi = 0, tempj = j; tempj < n; tempi++, tempj++)
			mat[tempi][tempj] = (br++ % 10);
			
	for (int i = 1; i < n; i++)
		for (int tempj = 0, tempi = i; tempi < n; tempi++, tempj++)
			mat[tempi][tempj] = (br++ % 10);
			
	stampaj_matricu(mat, n);
}

void siftuj_string(char *start)
{
	while (*(start+1) != '\0')
	{
		*start = *(start+1);
		start++;
	}
	*start = '\0';
}

void siftuj_string_k_puta(char *start, int k)
{
	while (k--)
	{
		siftuj_string(start);
		start--;
	}
}

void treci()
{
	char s[100];
	fgets(s, 100, stdin);
	s[strlen(s)-1] = '\0';
	int n = strlen(s);
	
	int map[26] = {0};
	char *start = s;
	while (*start != '\0')
	{
		map[*start - 'a'] = (map[*start - 'a']+1) % 26;
		start++;
	}
	start = s+1;
	int len = 1;
	while (*start != '\0')
	{
		if (*start == *(start-1))
			len++;
		else
		{
			siftuj_string_k_puta(start-1, len-1);
			start -= (len-1);
			len = 1;
		}
		start++;
	}
	siftuj_string_k_puta(start-1, len-1);
	
	puts(s);
	
	start = s;
	while (*start != '\0')
	{
		//printf("%d\n", map[*start - 'a']);
		*start = (*start + map[*start-'a']) % 'z';
		start++;
	}
	puts(s);
}

int main()
{
	//prvi();
	//drugi();
	//treci();
}

