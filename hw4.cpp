#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXLEN 1000
struct treenode
{
    int num;
    struct treenode *parent;
    struct treenode *left;
    struct treenode *right;
};

void previsit(struct treenode *proot);
void midvisit(struct treenode *proot);
void latvisit(struct treenode *proot);

struct treenode *pfind;
struct treenode *possible;
struct treenode *find(int num, int time);

void transfom(int s[], int len, struct treenode *proot, int time);

bool ispre(struct treenode *parent, struct treenode *son, struct treenode *proot);
struct treenode *re[MAXLEN];
struct treenode *points[MAXLEN];

int exam(struct treenode *proot);
int number = 0;
bool first = true;

int main()
{
    int num, i, j, sonnum, time = 0;
    int record[MAXLEN];
    struct treenode *p;
    struct treenode *proot = NULL;
    struct treenode *parent;
    struct treenode *son;
    char c, direct;
    char input[MAXLEN];
    bool success;
    while (1)
    {
        if ((c = getchar()) == EOF)
        {
            number = 0;
            exam(proot);
            if (number != time || time == 0)
            {
                printf("false\n");
                return 1;
            }
            break;
        }
        else if (c == 'A')
        {
            number = 0;
            exam(proot);
            if (number != time)
            {
                printf("false\n");
                return 1;
            }
            first = true;
            previsit(proot);
            printf("\n");
        }
        else if (c == 'B')
        {
            number = 0;
            exam(proot);
            if (number != time)
            {
                printf("false\n");
                return 1;
            }
            first = true;
            midvisit(proot);
            printf("\n");
        }
        else if (c == 'C')
        {
            number = 0;
            exam(proot);
            if (number != time)
            {
                printf("false\n");
                return 1;
            }
            first = true;
            latvisit(proot);
            printf("\n");
        }
        else if (c >= '0' && c <= '9')
        {
            input[0] = c;
            input[1] = '\0';
            i = 1;
            while ((c = getchar()) != ' ' && c != EOF&&c!='\n')
            {
                input[i++] = c;
                input[i] = '\0';
            }
            num = atoi(input);
            if ((c = getchar()) != 'R' && c != 'L')
            {
                number = 0;
                exam(proot);
                if (number != time)
                {
                    printf("false\n");
                    return 1;
                }
                i = j = 0;
                record[j++] = num;
                input[i++] = c;
                input[i] = '\0';
                while ((c = getchar()) != '\n' && c != EOF)
                {
                    if (c >= '0' && c <= '9')
                    {
                        input[i++] = c;
                        input[i] = '\0';
                    }
                    else if (c == ' ')
                    {
                        record[j++] = atoi(input);
                        i = 0;
                    }
                }
                if (i != 0&&input[0]>='0'&&input[0]<='9')
                {
                    record[j++] = atoi(input);
                    i = 0;
                }
                transfom(record, j, proot, time);
                possible = re[0]->parent;
                while (1)
                {
                    success = true;
                    for (i = 0; i < j; i++)
                    {
                        if (!ispre(possible, re[i], proot))
                        {
                            possible = possible->parent;
                            success = false;
                            break;
                        }
                    }
                    if (success == true)
                    {
                        printf("%d\n", possible->num);
                        break;
                    }
                }
            }
            else if (c == 'R' || c == 'L')
            {
                direct = c;
                if (time == 0)
                {
                    proot = (struct treenode *)malloc(sizeof(struct treenode));
                    proot->left = NULL;
                    proot->right = NULL;
                    proot->num = num;
                    proot->parent = NULL;
                    parent = proot;
                    points[time] = proot;
                    time += 1;
                }
                pfind = NULL;
                parent = find(num, time);
                if (parent == NULL)
                {
                    parent = (struct treenode *)malloc(sizeof(struct treenode));
                    parent->left = NULL;
                    parent->right = NULL;
                    parent->num = num;
                    parent->parent = NULL;
                    points[time] = parent;
                    time += 1;
                }
                c = getchar();
                i = 0;
                while ((c = getchar()) != '\n')
                {
                    input[i++] = c;
                    input[i] = '\0';
                }
                sonnum = atoi(input);
                pfind = NULL;
                son = find(sonnum, time);
                if (son == NULL)
                {
                    son = (struct treenode *)malloc(sizeof(struct treenode));
                    son->left = NULL;
                    son->right = NULL;
                    son->num = sonnum;
                    son->parent = NULL;
                    points[time] = son;
                    time += 1;
                }
                if (direct == 'R')
                {
                    if (son->parent != NULL || parent->right != NULL)
                    {
                        printf("false\n");
                        return 1;
                    }
                    son->parent = parent;
                    parent->right = son;
                    if (ispre(son, parent, proot))
                    {
                        printf("false\n");
                        return 1;
                    }
                    while (proot->parent != NULL)
                    {
                        proot = proot->parent;
                    }
                }
                else
                {
                    if (son->parent != NULL || parent->left != NULL)
                    {
                        printf("false\n");
                        return 1;
                    }
                    son->parent = parent;
                    parent->left = son;
                    if (ispre(son, parent, proot))
                    {
                        printf("false\n");
                        return 1;
                    }
                    while (proot->parent != NULL)
                    {
                        proot = proot->parent;
                    }
                }
            }
            else
            {
                printf("false\n");
                return 1;
            }
        }
        else if (c == '\n')
        {
            continue;
        }
        else
        {
            printf("false\n");
            return 1;
        }
    }
}

void previsit(struct treenode *proot)
{
    if (proot == NULL)
    {
        return;
    }
    if (first == true)
    {
        printf("%d", proot->num);
        first = false;
    }
    else
    {
        printf(" %d", proot->num);
    }
    previsit(proot->left);
    previsit(proot->right);
}

void midvisit(struct treenode *proot)
{
    if (proot == NULL)
    {
        return;
    }
    midvisit(proot->left);
    if (first == true)
    {
        printf("%d", proot->num);
        first = false;
    }
    else
    {
        printf(" %d", proot->num);
    }
    midvisit(proot->right);
}

void latvisit(struct treenode *proot)
{
    if (proot == NULL)
    {
        return;
    }
    latvisit(proot->left);
    latvisit(proot->right);
    if (first == true)
    {
        printf("%d", proot->num);
        first = false;
    }
    else
    {
        printf(" %d", proot->num);
    }
}

struct treenode *find(int num, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        if (points[i]->num == num)
        {
            return points[i];
        }
    }
    return NULL;
}

void transfom(int s[], int len, struct treenode *proot, int time)
{
    int i;
    struct treenode *p;
    for (i = 0; i < len; i++)
    {
        re[i] = find(s[i], time);
    }
}

bool ispre(struct treenode *parent, struct treenode *son, struct treenode *proot)
{
    struct treenode *p = son;
    if (p->parent == NULL)
    {
        return false;
    }
    while ((p = p->parent) != parent && p != proot && p->parent != NULL)
        ;
    if (p == parent)
    {
        return true;
    }
    else if (parent == proot)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int exam(struct treenode *proot)
{
    if (proot == NULL)
    {
        return 0;
    }
    exam(proot->left);
    exam(proot->right);
    number += 1;
    return number;
}