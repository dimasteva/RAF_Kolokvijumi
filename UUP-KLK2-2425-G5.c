#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    else return b;
}

int swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fibonaci_swap(int *prvi, int *drugi)
{
    int temp = *prvi;
    *prvi = *drugi - *prvi;
    *drugi = temp;
}

int nti_fibonaci(int *prvi, int *drugi, int n)
{
    if (n == 1 || n == 2)
        return 1;
    
    n-=3;
    while (n--)
    {
        int temp = *drugi;
        *drugi += *prvi;
        *prvi = temp;
    }
    return *prvi + *drugi;
}

float iterativno(int n)
{
    int oduzeti = n/2;
    //printf("%d\n", oduzeti);
    int prvi = (n-1) * oduzeti;
    int prvifib = 1, drugifib = 1;
    int donji = nti_fibonaci(&prvifib, &drugifib, n);
    //printf("prvifib: %d, drugifib: %d\n", prvifib, drugifib);
    //printf("DONJI je: %d\n", donji);
    //printf("%d * %d / %f", prvi, n, pow(donji, 3));
    float sum = sqrt(prvi * n / pow(donji, oduzeti));
    donji -= prvifib;
    prvi = max(1, prvi - oduzeti);
    fibonaci_swap(&prvifib, &drugifib);
    n--;
    for (int i = n; i > 0; i--)
    {
        //printf("prvifib: %d, drugifib: %d\n", prvifib, drugifib);
        //printf("%f\n", sum);
        //printf("%d * %d / %f + %f", prvi, i, pow(donji, oduzeti), sum);
        sum = sqrt(prvi * i/pow(donji, oduzeti) + sum);
        donji -= prvifib;
        //printf("DONJI je: %d\n", donji);
        prvi = max(1, prvi - oduzeti);
        fibonaci_swap(&prvifib, &drugifib);
    }
    return sum;
}

float rekurzivno(int i, int n, int prvifib, int drugifib)
{
    if (i == n)
        return sqrt(max(1, (i-1)*(n/2)) * i / pow((prvifib + drugifib), n/2));
    //printf("%d * %d / %f\n", max(1, (i-1)*(n/2)), i, pow(prvifib+drugifib, n/2));
    //printf("Prvi fibo: %d, Drugi: %d\n", prvifib, drugifib);
    return sqrt(max(1, (i-1)*(n/2)) * i / pow((prvifib + drugifib), n/2) +
    rekurzivno(i+1, n, i==1? 0 : drugifib, i==1? drugifib: prvifib+drugifib));
}

void prvi()
{
    int n;
    scanf("%d", &n);
    printf("%f\n", iterativno(n));
    int prvifib = 0, drugifib = 1;
    int stepen = n/2;
    printf("%f\n", rekurzivno(1, n, prvifib, drugifib));
}

void ucitaj_matricu(int mat[][100], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &mat[i][j]);
}

void sort(int niz[], int n, int neparan)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if ((!neparan && niz[i] > niz[j])
            || (neparan && niz[i] < niz[j]))
                swap(&niz[i], &niz[j]);
        }
    }
}

void stampaj_matricu(int niz[][100], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", niz[i][j]);
        printf("\n");
    }
}

void drugi()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int mat[100][100];
    ucitaj_matricu(mat, n, m);
    
    for (int i = 0; i < n; i++)
    {
        int parnost[m];
        for (int j = 0; j < m; j++)
            parnost[j] = mat[i][j]%2;
        int parni[m], neparni[m];
        int psize = 0, nsize = 0;
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] % 2)
                neparni[nsize++] = mat[i][j];
            else
                parni[psize++] = mat[i][j];
        }
        sort(parni, psize, 0);
        sort(neparni, nsize, 1);
        psize = 0, nsize = 0;
        for (int j = 0; j < m; j++)
            mat[i][j] = parnost[j]? neparni[nsize++] : parni[psize++];
    }
    stampaj_matricu(mat, n, m);
}

void dodeli(char podstringovi[][100], int *i, char trenutni[])
{
    for (int j = 0; j < strlen(trenutni); j++)
        podstringovi[*i][j] = trenutni[j];
    (*i)++;
    //printf("%d\n", *i);
}

void siftuj_string(char str[])
{
    for (int i = 0; i < strlen(str)-1; i++)
        str[i] = str[i+1];
    str[strlen(str)-1] = '\0';
}

void treci()
{
    char ulaz[100];
    fgets(ulaz, 100, stdin);
    ulaz[strlen(ulaz)-1] = '\0';
    
    int k;
    char k1[100];
    fgets(k1, 100, stdin);
    k1[strlen(k1)-1] = '\0';
    k = atoi(k1);
    
    char podstringovi[100][100];
    int psi = 0;
    char trenutni[100] = "";
    //puts(str);
    //printf("%d\n", k);
    int i = 0;
    while (i < k && ulaz[i] != '\0')
    {
        //putchar(str[i]);
        trenutni[i] = ulaz[i];
        i++;
    }
    trenutni[i] = '\0';
    dodeli(podstringovi, &psi, trenutni);
    //printf("%d\n", psi);
    for (; i < strlen(ulaz); i++)
    {
        //puts(podstringovi[0]);
        siftuj_string(trenutni);
        int trlen = strlen(trenutni);
        trenutni[trlen] = ulaz[i];
        trenutni[trlen+1] = '\0';
        dodeli(podstringovi, &psi, trenutni);
        //printf("%d\n", psi);
    }
    for (int j = 0; j < psi; j++)
    {
        int cnt = 1;
        if (podstringovi[j][0] == '\0') continue;
        for (int k = j+1; k < psi; k++)
        {
            if (strcmp(podstringovi[j], podstringovi[k]) == 0)
            {
                cnt++;
                podstringovi[k][0] = '\0';
            }
        }
        printf("%s %d\n", podstringovi[j], cnt);
    }
}

int main()
{
    //prvi();
    //drugi();
    //treci();
}