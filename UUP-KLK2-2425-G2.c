#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int powsum(int x)
{
	int sum = 0;
	while (x)
	{
		sum += pow(x%10, 2);
		x/=10;
	}
	return sum;
}

int iter(int a, int n)
{
	while(n--)
	{
		a = powsum(a);
	}
	return a;
}

int rek(int a, int n)
{
	if (n == 0)
		return a;
	return rek(powsum(a), n-1);
}

int isdigit(int x)
{
	return (x >= '0' && x <= '9');
}

void prvi()
{
	int a, n;
	scanf("%d%d", &a, &n);
	printf("%d\n", iter(a, n));
	printf("%d\n", rek(a, n));
}

void pronadji_min_max(char *s, int *min, int *max)
{
	char *temp = s;
	int num = 0;
	while (*temp != '\0')
	{
		//printf("%d %d %d\n",*temp, *min, *max);
		if (isdigit(*temp))
		{
			if (num != 0)
			{
				if (num > *max)
					*max = num;
				if (num < *min)
					*min = num;
			}
			num = 0;
		} else num++;
		temp++;
	}
	if (num != 0)
	{
		if (num > *max)
			*max = num;
		if (num < *min)
			*min = num;
	}
}

void ocistiString(char *ulaz, char *izlaz)
{
	int min = 1000000, max = 0;
	pronadji_min_max(ulaz, &min, &max);
	char *startizlaz = izlaz;
	char *temp = ulaz;
	while (*temp != '\0')
	{
		if (!isdigit(*temp))
		{
			*izlaz = *temp;
			izlaz++;
		} else
		{
			char *starttemp = temp;
			int num = *temp - '0';
			temp++;
			while (*temp != '\0' && isdigit(*temp))
			{
				num = num * 10 + (*temp - '0');
				temp++; 
			}
			if (!(num >= min && num <= max))
			{
				//printf("USAO ZA NUM: %d\n", num);
				while (num)
				{
					*izlaz = *starttemp;
					izlaz++, starttemp++;
					num /= 10;
				}
				*izlaz = '\0';
			}
			temp--;
		}
		temp++;
	}
	*izlaz = '\0';
}

void drugi()
{
	char ulazni[100], izlazni[100];
	fgets(ulazni, 100, stdin);
	ulazni[strlen(ulazni)-1] = '\0';
	//printf("%d %d", min, max);
	
	ocistiString(ulazni, izlazni);
	puts(izlazni);
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int isValidnoPolje(int i, int j, int n, int m, int polja)
{
	return (i - polja >= 0 && j - polja >= 0 && i + polja < n && j + polja < m);
}

int nadji_neparni(int mat[100][100], int n, int m)
{
	for (int k = min(n, m) - (min(n, m) % 2 == 0); k > 0; k-=2)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (mat[i][j] % k == 0)
				{
					int polja = k/2;
					if (isValidnoPolje(i, j, n, m, polja))
						return k;
				}
			}
		}
	}
	return 0;
}

int nadji_parni(int mat[100][100], int n, int m)
{
	for (int k = max(2, min(n, m) - (min(n, m) % 2 == 1)); k > 0; k-=2)
	{
		for (int i = 0; i < n-1; i++)
		{
			for (int j = 0; j < m-1; j++)
			{
				if (mat[i][j] % k == 0 && mat[i][j+1] % k == 0 && mat[i+1][j] % k == 0 && mat[i+1][j+1] % k == 0)
				{
					int polja = k/2-1;
					if (isValidnoPolje(i, j, n, m, polja) && isValidnoPolje(i, j+1, n, m, polja) && isValidnoPolje(i+1, j, n, m, polja) && isValidnoPolje(i+1, j+1, n, m, polja))
						return k;
				}
			}
		}
	}
	return 0;
}

void stampaj_neparne(int mat[100][100], int n, int m, int k)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mat[i][j] % k == 0)
			{
				int polja = k/2;
				if (isValidnoPolje(i, j, n, m, polja))
				{
					printf("%d %d, %d\n", i-polja, j-polja, mat[i][j]);
				}
			}
		}
	}
}

void stampaj_parne(int mat[100][100], int n, int m, int k)
{
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < m-1; j++)
		{
			if (mat[i][j] % k == 0 && mat[i][j+1] % k == 0 && mat[i+1][j] % k == 0 && mat[i+1][j+1] % k == 0)
			{
				int polja = k/2-1;
				if (isValidnoPolje(i, j, n, m, polja) && isValidnoPolje(i, j+1, n, m, polja) && isValidnoPolje(i+1, j, n, m, polja) && isValidnoPolje(i+1, j+1, n, m, polja))
				{
					printf("%d %d, %d %d %d %d\n", i-polja, j-polja, mat[i][j], mat[i][j+1], mat[i+1][j], mat[i+1][j+1]);
				}
			}
		}
	}
}

void treci()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int mat[100][100];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &mat[i][j]);
	
	int maxneparni = nadji_neparni(mat, n, m);
	int maxparni = nadji_parni(mat, n, m);
	//printf("MaxNeparni: %d\n", maxneparni);
	//printf("MaxParni: %d\n", maxparni);
	
	if (maxparni > maxneparni)
		stampaj_parne(mat, n, m, maxparni);
	else
		stampaj_neparne(mat, n, m, maxneparni);
	
}

int main()
{
	//prvi();
	//drugi();
	//treci();
}
