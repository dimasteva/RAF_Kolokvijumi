#include <stdio.h>
#include <math.h>
#include <string.h>

long long faktorijel(int n)
{
	if (n == 1)
		return 1;
	return n * faktorijel(n-1);
}

double iter(int n)
{
	double sum = (n%2 == 0)? 1 : faktorijel(n);
	int sign = n%2; // 0 - plus, 1 - minus
	int mstart = (n%2==0)? 3 : 2;
	int fstart = (n%2==0)? n-1 : n-2;
	int gstart = (n%2==0)? 2 : 3;
	int gfstart = (n%2==0)? n-2 : n-1;
	for (int i = 1; i < n; i++)
	{
		if (sign)
		{
			//printf("%d * %d - %lld / %lf\n", mstart, mstart, faktorijel(gfstart), sum);
			sum = mstart * mstart - faktorijel(gfstart) / sum;
			gfstart -= 2;
			mstart += 2;
		} else
		{
			//printf("%lld! + sqrt(%d / %lf)\n", fstart, gstart * gstart, sum);
			sum = faktorijel(fstart) + sqrt(gstart*gstart/sum);
			gstart+=2;
			fstart-=2;
		}
		sign ^= 1;
	}
	return sum;
}

double rek(int n, int sign, int fstart, int gfstart)
{
	if (n == 1)
	{
		//printf("%d\n", (sign == 1)? 1 : faktorijel(gfstart+1));
		return (sign == 1)? 1 : faktorijel(gfstart+1);
	}
		
	
	if (sign)
	{
		//printf("%d * %d - %d! / suma\n", n, n, gfstart);
		return n * n - faktorijel(gfstart) / rek(n-1, 0, fstart, gfstart+2);
	} else
	{
		//printf("%d! + sqrt(%d * %d / suma)\n", fstart, n, n);
		return faktorijel(fstart) + sqrt(n*n / rek(n-1, 1, fstart+2, gfstart));
	}
}

void prvi()
{
	int n;
	scanf("%d", &n);
	printf("%lf\n", iter(n));
	printf("%lf\n", rek(n, 0, 1, 2));
}

void ubaci_i_izmeni(char s1[100], char s2[100], char temp2[100], int s1i, int s2i)
{
	for (int i = 0; i < strlen(temp2); i++)
		s1[s1i++] = temp2[i];
	for (int j = 0; j < strlen(temp2); j++)
		s2[s2i++] = '0';
}

void rotiraj_k_puta(char s1[100], int n, int k, int s1i)
{
	//printf("N: %d, s1i: %d, k: %d\n", n, s1i, k);
	while (k--)
	{
		char last = s1[n-1];
		for (int i = n-1; i > s1i; i--)
			s1[i] = s1[i-1];
		s1[s1i] = last;
	}
}

void pronadji_i_zameni(char s1[100], char s2[100], char temp[100], int n, int m, int s1i)
{
	char temp2[100];
	int temp2i = 0;
	for (int i = 0; i < m; i++)
	{
		if (s2[i] == '0')
			continue;
		if (s2[i] != ' ')
			temp2[temp2i++] = s2[i];
		else
		{
			temp2[temp2i] = '\0';
			//printf("TEMP2: %s\n", temp2);
			if (strlen(temp) == strlen(temp2))
			{
				//printf("USAO ZA TEMP2: %s\n", temp2);
				ubaci_i_izmeni(s1, s2, temp2, s1i, i - temp2i);
				return;
			}
			temp2i = 0;	
		}
	}
	temp2[temp2i] = '\0';
	//printf("TEMP2: %s\n", temp2);
	if (strlen(temp) == strlen(temp2))
	{
		//printf("USAO ZA TEMP2: %s\n", temp2);
		ubaci_i_izmeni(s1, s2, temp2, s1i, m - temp2i);
		return;
	}
	//printf("LEN(TEMP): %d\n", strlen(temp));
	rotiraj_k_puta(s1, s1i+strlen(temp), strlen(temp)/2, s1i);
}

void drugi()
{
	char s1[100], s2[100];
	fgets(s1, 100, stdin);
	fgets(s2, 100, stdin);
	s1[strlen(s1)-1] = '\0';
	s2[strlen(s2)-1] = '\0';
	int n = strlen(s1), m = strlen(s2);
	char temp[100];
	int tempi = 0;
	for (int i = 0; i < n; i++)
	{
		if (s1[i] != ' ')
			temp[tempi++] = s1[i];
		else
		{
			temp[tempi] = '\0';
			//printf("TEMP: %s\n", temp);
			pronadji_i_zameni(s1, s2, temp, n, m, i - tempi);
			//printf("S1: %s\n", s1);
			//printf("S2: %s\n", s2);
			tempi = 0;
		}
	}
	temp[tempi] = '\0';
	//printf("TEMP: %s\n", temp);
	pronadji_i_zameni(s1, s2, temp, n, m, n - tempi);
	//printf("S1: %s\n", s1);
	//printf("S2: %s\n", s2);
	tempi = 0;
	puts(s1);
}

int mx_cifra(int x)
{
	int sol = 0;
	while(x)
	{
		if (x%10 > sol)
			sol = x%10;
		x/=10;
	}
	return sol;
}

void obelezi_slobodno(int mat[100][100], int n, int k)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = k;
}

void popuni(int mat[100][100], int i, int j, int n, int k)
{
	//printf("Usao za i: %d, j: %d, k: %d\n", i, j, k);
	for (int b1 = 0; b1 < k-1; b1++)
		mat[i][j++] = k;
	//printf("I: %d, J: %d\n", i, j);
	for (int b1 = 0; b1 < k-1; b1++)
		mat[i++][j] = k;
	for (int b1 = 0; b1 < k-1; b1++)
		mat[i][j--] = k;
	for (int b1 = 0; b1 < k-1; b1++)
		mat[i--][j] = k;
}

void ukloni_mx_iz_br(int *x, int k)
{
	int ost = 0;
	int ostlen = 0;
	int temp = *x;
	while (temp)
	{
		if (temp%10 == k)
		{
			//printf("TEMP: %d, ost: %d, ostlen: %d\n", temp, ost, ostlen);
			temp /= 10;
			temp *= pow(10, ostlen);
			temp += ost;
			*x = temp;
			//printf("ZAKRAJ: %d\n", temp);
			return;
		} else
		{
			ost = (temp%10) * pow(10, ostlen) + ost;
			ostlen++;
		}
		temp /= 10;
	}
}

bool proveri_jel_smes(int mat[100][100], int i, int j, int n, int k)
{
	for (int b1 = 0; b1 < k-1; b1++)
	{
		if (mat[i][j] != 10)
			return false;
		j++;
	}
	for (int b1 = 0; b1 < k-1; b1++)
	{
		if (mat[i][j] != 10)
			return false;
		i++;
	}
	for (int b1 = 0; b1 < k-1; b1++)
	{
		if (mat[i][j] != 10)
			return false;
		j--;
	}
	for (int b1 = 0; b1 < k-1; b1++)
	{
		if (mat[i][j] != 10)
			return false;
		i--;
	}
	return true;
}

void stampaj_mat(int mat[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", mat[i][j]);
		puts("");
	}
}

void popuni_nulama_umesto_10(int mat[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (mat[i][j] == 10)
				mat[i][j] = 0;
	}
}

void treci()
{
	int x;
	scanf("%d", &x);
	int n = mx_cifra(x);
	ukloni_mx_iz_br(&x, n);
	//printf("%d\n", x);
	int mat[100][100];
	obelezi_slobodno(mat, n, 10);
	
	while (x)
	{
		int k = mx_cifra(x);
		//printf("TRAZI SE ZA K: %d\n", k);
		for (int i = 0; i < n - k + 1; i++)
		{
			for (int j = 0; j < n - k + 1; j++)
			{
				if (mat[i][j] == 10 && proveri_jel_smes(mat, i, j, n, k))
				{
					popuni(mat, i, j, n, k);
					//stampaj_mat(mat, n);
				}
			}
		}
		ukloni_mx_iz_br(&x, k);
	}
	popuni_nulama_umesto_10(mat, n);
	stampaj_mat(mat, n);
}

int main()
{
	//prvi();
	//drugi();
	//treci();
}
