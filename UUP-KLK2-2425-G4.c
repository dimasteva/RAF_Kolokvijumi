#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define FLT_MAX 3.402823466e+38F

int zbircifara(int n)
{
    int sum = 0;
    while (n)
    {
        sum += n%10;
        n/=10;
    }
    return sum;
}

int iterativno(int a, int n)
{
    while (--n)
        a = 2 * a + zbircifara(a);
    return a;
}

int rekurzivno(int a, int n)
{
    if (n == 1)
        return a;
    
    return rekurzivno(2 * a + zbircifara(a), n-1);
}

void prvi()
{
    int n, a;
    scanf("%d%d", &a, &n);
    printf("%d\n", iterativno(a, n));
    printf("%d\n", rekurzivno(a, n));
}

int issamoglasnik(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
    || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void obrisi_interval(char s[], int i, int j)
{
    while (j < strlen(s))
    {
        s[i] = s[j];
        i++, j++;
    }
    s[i] = '\0';
}

int pretoga(char s[], int i, int trazimo)
{
    if (i < 0)
        return 1;
    if (trazimo == 1 && isdigit(s[i]))
        return 1;
    if (trazimo == 0 && isalpha(s[i]))
        return 1;
    return 0;
}

void drugi()
{
    char ulaz[100];
    fgets(ulaz, 100, stdin);
    ulaz[strlen(ulaz)-1] = '\0';
    int trazimo = isalpha(ulaz[0])? 1 : 0; //1 - slovo, 0 - broj
    int brsamog = issamoglasnik(ulaz[0]);
    int lasti = 0;
    int sumacifara = 0;
    for (int i = 1; i < strlen(ulaz); i++)
    {
        brsamog += issamoglasnik(ulaz[i]);
        sumacifara += (isdigit(ulaz[i])? ulaz[i] - '0' : 0);
        if (isalpha(ulaz[i]) && trazimo == 0)
        {
            //printf("USAO ZA I: %d i lasti:%d \n", i, lasti);
            if (sumacifara % 3 == 0 && pretoga(ulaz, lasti-1, trazimo))
            {
                obrisi_interval(ulaz, lasti, i);
                i = lasti;
            } else lasti = i;
            sumacifara = 0;
            trazimo = 1;
        } else if (isdigit(ulaz[i]) && trazimo == 1)
        {
            //printf("USAO ZA II: %d i lasti:%d \n", i, lasti);
            if (brsamog % 2 != 0 && pretoga(ulaz, lasti-1, trazimo))
            {
                obrisi_interval(ulaz, lasti, i);
                i = lasti;
            } else lasti = i;
            brsamog = 0;
            trazimo = 0;
        }
        //puts(ulaz);
    }
    //printf("%d %d\n", lasti, trazimo);
    //printf("%d", brsamog);
    //putchar(ulaz[lasti-1]);
    if (trazimo == 1 && brsamog % 2 != 0 && pretoga(ulaz, lasti-1, trazimo))
        obrisi_interval(ulaz, lasti, strlen(ulaz));
    else if (trazimo == 0 && sumacifara % 3 == 0 && pretoga(ulaz, lasti-1, trazimo))
        obrisi_interval(ulaz, lasti, strlen(ulaz));
        
    puts(ulaz);
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

float avg(int mat[][100], int gornji_cosak_i, int gornji_cosak_j, int k)
{
    float sum = 0;
    for (int i = gornji_cosak_i; i < gornji_cosak_i+k; i++)
    {
        for (int j = gornji_cosak_j; j < gornji_cosak_j+k; j++)
        {
            //printf("%d ", mat[i][j]);
            //printf("%d, %d ", i, j);
            sum += mat[i][j];
        }
    }
    //puts("");
    return sum / (k*k);
}

void stampajod(int mat[][100], int i, int j, int k)
{
    for (int i1 = i; i1 < i+k; i1++)
    {
        for (int j1 = j; j1 < j+k; j1++)
            printf("%d ", mat[i1][j1]);
        printf("\n");
    }
}

void treci()
{
   int m, n;
   scanf("%d%d", &m, &n);
   int mat[100][100];
   for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
   }
   float mn = FLT_MAX;
   int bestk = -1, gi = -1, gj = -1;
   for (int k = 2; k <= min(m, n); k++)
   {
       for (int i = 0; i+k <= m; i++)
       {
           for (int j = 0; j+k <= n; j++)
           {
                float prosek = avg(mat, i, j, k);
                //printf("PROSEK: %f ZA i: %d, j: %d\n", prosek, i, j);
                if (prosek < mn)
                {
                   bestk = k;
                   gi = i;
                   gj = j;
                   mn = prosek;
                }
           }
       }
       //printf("KKK: %d\n", k);
   }
   printf("k = %d, (%d,%d)\n", bestk, gi, gj);
   stampajod(mat, gi, gj, bestk);
}

int main()
{
    //prvi();
    //drugi();
    //treci();
}