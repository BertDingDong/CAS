#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000
char input[MAXLEN];
char pu[MAXLEN];
char compare[MAXLEN];
char *possible[MAXLEN];
char regist[MAXLEN];
int pre = 0;
char simu[MAXLEN];
int psi = 0;
char sta[MAXLEN];
int psta = 0;
int simulate(char s[], int num);
int size;
int re[MAXLEN];
int prem = 0;
void push(char s[], char c, int p);
void pop(char s[], int p);
char top(char s[], int p);
int empty(char s[], int p);
int main()
{
    char c, type;
    int num, i = 0, j = 0, k = 0, l = 0, result, time, bre = 0;
    char *p;
    pu[0] = '\0';
    num = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (c >= 'A' && c <= 'G')
        {
            type = c;
            while ((c = getchar()) <= '9' && c >= '0')
            {
                input[i++] = c;
                input[i] = '\0';
            }
            if (c == '-' || c == ' ')
            {
                num = atoi(input);
                if (num == 0)
                {
                    printf("-1\n");
                    return 0;
                }
                i = 0;
                for (j = 0; j < num; j++)
                {
                    pu[k++] = type;
                    pu[k] = '\0';
                }
                if (c == ' ')
                {
                    num = 0;
                    input[i] = '\0';
                    while ((c = getchar()) <= '9' && c >= '0')
                    {
                        input[i++] = c;
                        input[i] = '\0';
                    }
                    num = atoi(input);
                    break;
                }
            }
            else
            {
                printf("-1\n");
                return 0;
            }
        }
        else
        {
            printf("-1\n");
            return 0;
        }
    }
    size = k;
    if (pu[0] == '\0')
    {
        printf("-1\n");
        return 0;
    }
    if (num == 0)
    {
        printf("-1\n");
        return 0;
    }
    while (1)
    {
        i = 0, result = 0;
        compare[i] = '\0';
        if ((c = getchar()) == EOF)
        {
            break;
        }
        else
        {
            ungetc(c, stdin);
        }
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (c >= 'A' && c <= 'G')
            {
                compare[i++] = c;
                compare[i] = '\0';
            }
        }
        if (compare[0] == '\0' || i != k)
        {
            re[prem++] = 2;
            continue;
        }
        result = simulate(compare, num);
        if (c == EOF)
        {
            if (result == 1)
            {
                re[prem++] = 1;
            }
            else
            {
                re[prem++] = 0;
            }
            break;
        }
        if (result == 1)
        {
            re[prem++] = 1;
        }
        else
        {
            re[prem++] = 0;
        }
    }
    if (prem == 0)
    {
        printf("-1\n");
        return 0;
    }
    for (i = 0; i < prem; i++)
    {
        if (re[i] == 2)
        {
            printf("-1\n");
            return 0;
        }
    }
    for (i = 0; i < prem; i++)
    {
        if (re[i] == 1)
        {
            printf("true\n");
        }
        else
        {
            printf("false\n");
        }
    }
    return 0;
}

int simulate(char s[], int num)
{
    int i, j, k, result = 1;
    pre = psi = psta = 0;
    for (i = 0; i < size; i++)
    {
        push(sta, pu[size - i - 1], 3);
    }
    i = 0;
    push(simu, top(sta, 3), 2);
    pop(sta, 3);
    while (!empty(sta, 3))
    {
        if (!empty(simu, 2) && top(simu, 2) == s[i])
        {
            for (; !empty(regist, 1);)
            {
                pop(regist, 1);
            }
            for (j = 0; j < num; j++)
            {
                if (empty(simu, 2))
                {
                    break;
                }
                else
                {
                    if (top(simu, 2) != s[i])
                    {
                        for (; !empty(regist, 1);)
                        {
                            i--;
                            push(simu, top(regist, 1), 2);
                            pop(regist, 1);
                        }
                        push(simu, top(sta, 3), 2);
                        pop(sta, 3);
                    }
                    else
                    {
                        push(regist, top(simu, 2), 1);
                        pop(simu, 2);
                        i++;
                    }
                }
            }
        }
        else
        {
            push(simu, top(sta, 3), 2);
            pop(sta, 3);
        }
    }
    for (; !empty(simu, 2);)
    {
        if (top(simu, 2) != s[i])
        {
            result = 0;
            return result;
        }
        else
        {
            pop(simu, 2);
            i++;
        }
    }
    if (i != size)
    {
        result = 0;
        return result;
    }
    return result;
}

void push(char s[], char c, int p)
{
    if (p == 1)
    {
        regist[pre] = c;
        pre++;
    }
    else if (p == 2)
    {
        simu[psi] = c;
        psi++;
    }
    else if (p == 3)
    {
        sta[psta] = c;
        psta++;
    }
}

void pop(char s[], int p)
{
    if (p == 1)
    {
        pre--;
    }
    else if (p == 2)
    {
        psi--;
    }
    else if (p == 3)
    {
        psta--;
    }
}

char top(char s[], int p)
{
    if (p == 1)
    {
        return regist[pre - 1];
    }
    else if (p == 2)
    {
        return simu[psi - 1];
    }
    else if (p == 3)
    {
        return sta[psta - 1];
    }
    else
    {
        return '\0';
    }
}

int empty(char s[], int p)
{
    if (p == 1)
    {
        if (pre == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (p == 2)
    {
        if (psi == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (p == 3)
    {
        if (psta == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}