#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXLEN 1000
#define max(x,y) (((x)>(y))?(x):(y))
struct treenode
{
    int num;
    struct treenode *parent;
    struct treenode *left;
    struct treenode *right;
};

void visit(struct treenode *proot,int level);

struct treenode *find(int num, int time);
struct treenode *pfind;

bool ispre(struct treenode *parent, struct treenode *son, struct treenode *proot);
struct treenode *re[MAXLEN];
struct treenode *points[MAXLEN];

int exam(struct treenode *proot);
void examlevel(struct treenode *proot,int level);
int number = 0;
bool first = true;
int maxnum;
int maxlevel=0;
int main()
{
    int num, i=0, j=0, sonnum, time = 0,level;
    int record[MAXLEN];
    struct treenode *p;
    struct treenode *proot = NULL;
    struct treenode *parent;
    struct treenode *son;
    char c, direct;
    char input[MAXLEN];
    bool success;
    input[0]='\0';
    while((c=getchar())>='0'&&c<='9'){
        input[i++]=c;
        input[i]='\0';
    }
    if(c!='\n'){
        printf("false\n");
        return 0;
    }
    level=atoi(input);
    if(level<0){
        printf("false\n");
        return 0;
    }
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
                printf("false\n");
                break;
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
                while ((c = getchar()) != '\n'&&c!=EOF)
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
    examlevel(proot,0);
    if(level>maxlevel){
        printf("false\n");
        return 0;
    }
    first=true;
    visit(proot,level);
    printf("%d\n",maxnum);
    return 0;
}

void visit(struct treenode *proot,int level)
{
    if (proot == NULL)
    {
        return;
    }
    if(level==0){
        if(first){
            maxnum=proot->num;
            first=false;
        }else{
            maxnum=max(maxnum,proot->num);
        }
    }
    visit(proot->left,level-1);
    visit(proot->right,level-1);
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

void examlevel(struct treenode *proot,int level)
{
    if (proot == NULL)
    {
        maxlevel=max(maxlevel,level-1);
        return ;
    }
    examlevel(proot->left,level+1);
    examlevel(proot->right,level+1);
}