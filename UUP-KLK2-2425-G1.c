#include <stdio.h>
#include <math.h>

long long iterativno(long long n, long long min, long long max)
{
    long long broj = 0;
    int stepen = 0;
    int cnt = 2;
    while (n)
    {
        if (n % 10 >= min && n % 10 <= max)
        {
            broj = (n%10) * pow(10, stepen) + broj;
            stepen += cnt++;
        }
        n/=10;
    }
    return broj;
}

long long rekurzivno(long long n, long long min, long long max, int stepen, int cnt)
{
    if (n == 0)
        return 0;

    if (n%10 >= min && n%10 <= max)
        return (n%10) * pow(10, stepen) + rekurzivno(n/10, min, max, stepen+cnt, cnt+1);
    else
        return rekurzivno(n/10, min, max, stepen, cnt);
}

void prvi()
{
    long long n, min, max;
    scanf("%lld %lld %lld", &n, &min, &max);
    printf("%lld\n", iterativno(n, min, max));
    printf("%lld\n", rekurzivno(n, min, max, 0, 2));
}

void drugi()
{
    int n, dim;
    scanf("%d %d", &n, &dim);
    int res[100][100];

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            scanf("%d", &res[i][j]);
    puts("");
    for (int k = 1; k < n; k++)
    {
        int A[100][100];
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                scanf("%d", &A[i][j]);

        int tmp[100][100];

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                tmp[i][j] = 0;
                for (int l = 0; l < dim; l++)
                {
                    tmp[i][j] += res[i][l] * A[l][j];
                }
            }
        }
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                res[i][j] = tmp[i][j];
        puts("");

    }
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            printf("%d ", res[i][j]);
        puts("");
    }
}

void treci()
{
    char lastc = '\n';
    char c;
    int mapa[26] = {0};
    while (1)
    {
        c = getc(stdin);
        if (lastc == '\n' && c == '\n')
            break;

        if (c >= 'a' && c <= 'z')
            mapa[c-'a']++;
        lastc = c;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!mapa[i])
            putchar('a' + i);
    }
}

int main()
{
    //prvi();
    //drugi();
    //treci();
}
