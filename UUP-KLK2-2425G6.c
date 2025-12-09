/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

long long faktorijel(int n)
{
    if (n == 1)
        return n;
    return n * faktorijel(n-1);
}

float iter(int n)
{
    int i = n%2;
    int sred = n/2 + (n%2);
    int duplasred = n%2;
    int poc = n;
    int stanje = -1;
    double sum = 0;
    if (i == 0)
        sum = faktorijel(n);
    else
        sum = (n+1)*n;
    
    n--;
    while (n >= 1)
    {
        //printf("%d ", poc);
        poc += stanje;
        //printf("%lf\n", sum);
        if (n%2 == 0)
        {
            //printf("%d! + %d/%lf\n", n, poc, sum);
            sum = faktorijel(n) + poc/sum;
        } else
        {
            //printf("%d * %d + %d/%lf\n", n, n+1, poc, sum);
            sum = (n)*(n+1) + poc/sum;
        }
        n--;
        if (poc == sred)
        {
            if (duplasred)
            {
                duplasred = 0;
                poc++;
            }
            else
                stanje = 1;
        }
    }
    return sum;
}

float rek(int n, int iter, int poc, int stanje, int duplo)
{
    if (iter == n)
    {
        if (iter % 2 == 0)
            return iter * (iter-1);
        else
            return faktorijel(iter-1);
    }
    if (n/2 + (n%2) == iter)
    {
        if (duplo)
        {
            duplo = 0;
            stanje = 0;
        } else
            stanje = 1;
    }
    if (iter % 2 == 0)
    {
        //printf("%d * %d + %d/%lf\n", iter, iter-1, poc);
        return iter * (iter-1) + poc/rek(n, iter+1, poc+stanje, stanje, duplo);
    } else
    {
        //printf("%d! + %d/%lf\n", n, poc);
        return faktorijel(iter-1) + poc/rek(n, iter+1, poc+stanje, stanje, duplo);
    }
}

void prvi()
{
    int n;
    scanf("%d", &n);
    printf("%.4lf\n", iter(n));
    printf("%.4f\n", rek(n, 2, n-1, -1, n%2));
}

void kreiraj_mapu(char mapa[], char s[])
{
    for (int i = 0; i < 26; i++)
        mapa[i] = 0;
    for (int i = 0; i < strlen(s); i++)
        mapa[s[i]-'a']++;
}

int min(int a, int b)
{
    if (a <= b)
        return a;
    else return b;
}

int uporedimape(char mapa1[], char mapa2[])
{
    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (mapa2[i])
            cnt += mapa1[i];
        
    return cnt;
}

void ukloni_slovo_pozicija(char temp[], int i)
{
    while (i < strlen(temp)-1)
    {
        temp[i] = temp[i+1];
        i++;
    }
    temp[strlen(temp)-1] = '\0';
}

void siftuj_string(char temp[], char a, int cnt)
{
    //printf("Za uklanjanje: %c, koliko puta: %d\n", a, cnt);
    while (cnt)
    {
        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] == a)
            {
                //printf("Nasao slovo na: %d\n", i);
                ukloni_slovo_pozicija(temp, i);
                cnt--;
                break;
            }
        }
    }
}

void ukloni_slova(char temp[], char mapatemp[], char mapa2[])
{
    for (int i = 0; i < 26; i++)
    {
        if (min(mapatemp[i], mapa2[i]) > 0)
        {
            siftuj_string(temp, 'a'+i, min(mapatemp[i], mapa2[i]));
        }
    }
}

void rotiraj(char temp[])
{
    char prvi = temp[0];
    for (int i = 0; i < strlen(temp)-1; i++)
        temp[i] = temp[i+1];
    temp[strlen(temp)-1] = prvi;
}

void drugi()
{
    char s1[100], s2[100];
    char sol[100] = "";
    fgets(s1, 100, stdin);
    fgets(s2, 100, stdin);
    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';
    int n1 = strlen(s1), n2 = strlen(s2);
    char mapa2[26];
    kreiraj_mapu(mapa2, s2);
    char temp[100];
    for (int i = 0; i < n1; i++)
    {
        temp[i%n2] = s1[i];
        //printf("ZA I: %d i n2: %d\n", i, n2);
        //puts(temp);
        if ((i+1) % n2 == 0)
        {
            temp[i+1] = '\0';
            //puts("USAOO");
            char mapatemp[26];
            kreiraj_mapu(mapatemp, temp);
            //printf("%d\n", mapatemp['s'-'a']);
            int pojavljivanja = uporedimape(mapatemp, mapa2);
            //printf("Pojavlj: %d\n", pojavljivanja);
            if (pojavljivanja % 2 == 0)
            {
                ukloni_slova(temp, mapatemp, mapa2);
            } else
            {
                while (pojavljivanja--)
                    rotiraj(temp);
            }
            //puts(temp);
            strcat(sol, temp);
        }
    }
    //printf("N1: %d, N2: %d\n", n1, n2);
    temp[n1%n2] = '\0';
    char mapatemp[26];
    kreiraj_mapu(mapatemp, temp);
    //printf("%d\n", mapatemp['s'-'a']);
    int pojavljivanja = uporedimape(mapatemp, mapa2);
    //printf("Pojavlj: %d\n", pojavljivanja);
    if (pojavljivanja % 2 == 0)
    {
        ukloni_slova(temp, mapatemp, mapa2);
    } else
    {
        while (pojavljivanja--)
            rotiraj(temp);
    }
    strcat(sol, temp);
    puts(sol);
    
}

void sort(int niz[], int n, int i1)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i1 % 2 == 0)
            {
                if (niz[i] < niz[j])
                {
                    int temp = niz[i];
                    niz[i] = niz[j];
                    niz[j] = temp;
                }
            } else
            {
                if (niz[i] > niz[j])
                {
                    int temp = niz[i];
                    niz[i] = niz[j];
                    niz[j] = temp;
                }
            }
            
        }
    }
}

void treci()
{
    int n;
    scanf("%d", &n);
    int mat[100][100];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    //printf("1");
    int i = 0, j = 0;
    int niz[100];
    int nizi = 0;
    while (i <= n/2-1)
    {
        int tempi = i, tempj = j;
        while (tempj < n - j)
            niz[nizi++] = mat[tempi][tempj++];
        tempi++;
        tempj--;
        
        while (tempi < n - i)
            niz[nizi++] = mat[tempi++][tempj];
        tempj--;
        tempi--;
        
        while (tempj >= j)
            niz[nizi++] = mat[tempi][tempj--];
        tempi--;
        tempj++;
        
        while (tempi > i)
            niz[nizi++] = mat[tempi--][tempj];
            
        //puts("\n");
        //for (int i = 0; i < nizi; i++)
        //    printf("%d ", niz[i]);
            
        sort(niz, nizi, i);
        
        //puts("\n");
        //for (int i = 0; i < nizi; i++)
        //    printf("%d ", niz[i]);
        
        tempi = i, tempj = j;
        nizi = 0;
        while (tempj < n - j)
             mat[tempi][tempj++] = niz[nizi++];
        tempi++;
        tempj--;
        
        while (tempi < n - i)
            mat[tempi++][tempj] = niz[nizi++];
        tempj--;
        tempi--;
        
        while (tempj >= j)
            mat[tempi][tempj--] = niz[nizi++];
        tempi--;
        tempj++;
        
        while (tempi > i)
            mat[tempi--][tempj] = niz[nizi++];
        
        i++, j++;
        nizi = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        puts("");
    }
    
}

int main()
{
    //prvi();
    //drugi();
    //treci();
}