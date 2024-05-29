#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
using namespace std;
#define MAXSIZE 100
struct edge
{
    int from;
    int to;
};
int pointsize = 0;
int egdesize = 0;
int point[MAXSIZE];
bool visited[MAXSIZE];
edge e[MAXSIZE];
stack<int> s;
stack<int> scc;
int searchpoint(int num, int size);
void dfs1(int num);
void dfs2(int num);
void reverse();
int sum(int s[], int size);
int main()
{
    int num1, num2, i = 0, j = 0, k = 0, m;
    int graph[MAXSIZE][MAXSIZE];
    int graphsize[MAXSIZE];
    char input[MAXSIZE];
    char c;
    while (true)
    {
        i = 0;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            input[i++] = c;
            input[i] = '\0';
            if (c == ' ')
            {
                num1 = atoi(input);
                i = 0;
            }
        }
        num2 = atoi(input);
        if (searchpoint(num1, pointsize) == -1)
        {
            point[pointsize++] = num1;
        }
        if (searchpoint(num2, pointsize) == -1)
        {
            point[pointsize++] = num2;
        }
        e[egdesize].from = num1;
        e[egdesize++].to = num2;
        if (c == EOF)
        {
            break;
        }
    }
    for (i = 0; i < pointsize; i++)
    {
        visited[i] = false;
    }
    for (i = 0; i < pointsize; i++)
    {
        if (visited[i] == false)
        {
            dfs1(point[i]);
        }
    }
    reverse();
    for (i = 0; i < pointsize; i++)
    {
        visited[i] = false;
    }
    j = 0;
    while (!s.empty())
    {
        i = 0;
        if (!visited[searchpoint(s.top(), pointsize)])
        {
            dfs2(s.top());
            s.pop();
            while (!scc.empty())
            {
                graph[j][i++] = scc.top();
                scc.pop();
            }
            graphsize[j++] = i;
        }
        else
        {
            s.pop();
        }
    }
    for (i = 0; i < j; i++)
    {
        for (m = 0; m < graphsize[i]; m++)
        {
            for (k = 1; k < graphsize[i]; k++)
            {
                if (graph[i][k - 1] > graph[i][k])
                {
                    swap(graph[i][k - 1], graph[i][k]);
                }
            }
        }
    }
    for (i = 0; i < j; i++)
    {
        for (k = 1; k < j; k++)
        {
            if (graphsize[k - 1] < graphsize[k])
            {
                swap(graph[k - 1], graph[k]);
                swap(graphsize[k - 1], graphsize[k]);
            }
            else if (graphsize[k - 1] == graphsize[k])
            {
                if (sum(graph[k - 1], graphsize[k - 1]) < sum(graph[k], graphsize[k]))
                {
                    swap(graph[k - 1], graph[k]);
                    swap(graphsize[k - 1], graphsize[k]);
                }
            }
        }
    }
    for (i = 0; i < j; i++)
    {
        cout << graph[i][0];
        for (k = 1; k < graphsize[i]; k++)
        {
            cout  << " "<< graph[i][k];
        }
        cout << endl;
    }
}

int searchpoint(int num, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (point[i] == num)
        {
            return i;
        }
    }
    return -1;
}

void dfs1(int num)
{
    visited[searchpoint(num, pointsize)] = true;
    int i;
    for (i = 0; i < egdesize; i++)
    {
        if (e[i].from == num)
        {
            if (visited[searchpoint(e[i].to, pointsize)] == false)
            {
                dfs1(e[i].to);
            }
        }
    }
    s.push(num);
}

void dfs2(int num)
{
    visited[searchpoint(num, pointsize)] = true;
    scc.push(num);
    int i;
    for (i = 0; i < egdesize; i++)
    {
        if (e[i].from == num)
        {
            if (visited[searchpoint(e[i].to, pointsize)] == false)
            {
                dfs2(e[i].to);
            }
        }
    }
}

void reverse()
{
    int i;
    int temp;
    for (i = 0; i < egdesize; i++)
    {
        temp = e[i].from;
        e[i].from = e[i].to;
        e[i].to = temp;
    }
}

int sum(int s[], int size)
{
    int i;
    int sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += s[i];
    }
    return sum;
}