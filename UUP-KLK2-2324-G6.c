#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double iterativno(int n)
{
    double sum = 0;
    int startodd = 'A' + n - 1;
    startodd += (n/2 - (n%2==0)) * 2;
    char oddletter = 'A' + ((startodd - 'A') % 26);
    char starteven = 'A' + ( (('A' + n - 2 - 2*(n/2 - 1)) - 'A' + 26) % 26 );
    //putchar(oddletter);
    //putchar(starteven);
    char evenletter = starteven;
    int koji; //1 - odd, 0 - even
    if (n % 2 == 0)
    {
        sum = evenletter + n*n;
        evenletter += 2;
        if (evenletter > 'Z')
            evenletter -= 26;
        koji = 1;
    }
    else
    {
        sum = oddletter + n*n;
        oddletter -= 2;
        if (oddletter < 'A')
            oddletter += 26;
        koji = 0;
    }
    for (int i = 1; i < n; i++)
    {
        if (koji)
        {
            //printf("%c + %d %d / %lf\n", oddletter, (n-i), n-i, sum);
            sum = oddletter + (n-i) * (n-i) / sum;
            oddletter -= 2;
            if (oddletter < 'A')
                oddletter += 26;
        } else
        {
            //printf("%c + %d %d / %lf\n", evenletter, (n-i), n-i, sum);
            sum = evenletter + (n-i) * (n-i) / sum;
            evenletter += 2;
            if (evenletter > 'Z')
                evenletter -= 26;
        }
        koji ^= 1;
    }
    return sum;
}

double rekurzivno(int n, char oddletter, char evenletter, int i)
{
    if (i == n)
        return (n % 2 == 0? evenletter : oddletter) + n*n;
    if (i % 2 == 1)
        return oddletter + i * i / rekurzivno(n, oddletter + 2 - 26 * (oddletter > 'z') , evenletter, i+1);
    else
        return evenletter + i * i / rekurzivno(n, oddletter, evenletter - 2 + 26 * (evenletter < 'a'), i+1);
}

void prvi()
{
    int n;
    scanf("%d", &n);
    printf("%lf\n", iterativno(n));
    printf("%lf\n", rekurzivno(n, 'A' + n - 1, 'A' + n - 2, 1));
}

int prost(int n)
{
    for (int i = 2; i <= n/2; i++)
        if (n%i == 0)
            return 0;
    return 1;
}

int sledeciprost(int n)
{
    n++;
    while (1)
    {
        if (prost(n))
            return n;
        n++;
    }
    return 0;
}

void stampaj_matricu(int mat[100][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        puts("");
    }
}

void drugi()
{
    int n;
    scanf("%d", &n);
    int mat[100][100];
    int currprost = 1;
    for (int i = n-1, j = 0; j <= n/2 - (n%2 == 0); j++)
    {
        int tempi = i, tempj = j;
        while (tempi > j)
        {
            mat[tempi][tempj] = (currprost = sledeciprost(currprost)) % 10;
            tempi--;
        }
        while (tempj < n-1-j)
        {
            mat[tempi][tempj] = (currprost = sledeciprost(currprost)) % 10;
            tempj++;
        }
        if (n % 2 == 1 && j == n/2 - (n%2 == 0))
        {
            mat[tempi][tempj] = (currprost = sledeciprost(currprost)) % 10;
            break;
        }
        while (tempi < n)
        {
            mat[tempi][tempj] = (currprost = sledeciprost(currprost)) % 10;
            tempi++;
        }
        //stampaj_matricu(mat, n);
        //puts("");
    }
    stampaj_matricu(mat, n);
}

int palindrom(char *s)
{
    char *e = s;
    while (*e != '\0')
        e++;
    e--;
    while (s <= e)
    {
        if (*s != *e)
            return 0;
        s++, e--;
    }
    return 1;
}

void resi(char *s)
{
    char tren[100];
    int treni = 0;
    int br = 0;
    while (*s != '\0')
    {
       if (*s >= '0' && *s <= '9')
            br = br * 10 + (*s - '0');
        else if (*s == '-')
        {
            br %= 26;
            tren[treni++] = 'A' + br;
            br = 0;
        } else if (*s == ' ')
        {
            br %= 26;
            tren[treni++] = 'A' + br;
            br = 0;
            tren[treni] = '\0';
            //puts(tren);
            if (palindrom(tren))
                printf("%s ", tren);
            treni = 0;
        }
        s++;
    }
    br %= 26;
    tren[treni++] = 'A' + br;
    br = 0;
    tren[treni] = '\0';
    if (palindrom(tren))
        puts(tren);
}

void treci()
{
    char s[100];
    fgets(s, 100, stdin);
    s[strlen(s) - 1] = '\0';
    resi(s);
}

int main()
{
    //prvi();
    //drugi();
    //treci();
}
