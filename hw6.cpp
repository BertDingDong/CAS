#include <stdio.h>
#include <string.h>
#include <iostream>
#include <limits.h>
#define MAXSIZE 1000
using namespace std;
struct edge
{
    int one;
    int other;
    int distance;
};

int searchcity(int city[], int num, int citysize);
int distance(int from, int to, edge e[], int edgesize);
bool hasedge(int from, int to, edge e[], int edgesize);

int main()
{
    int num1, num2, num3, i = 0, j = 0, k = 0, citynum, edgenum;
    int from, to;
    char input[MAXSIZE];
    char c;
    bool first;
    bool second;
    while ((c = getchar()) != '\n')
    {
        input[i++] = c;
        input[i] = '\0';
        if (c == ' ')
        {
            num1 = atoi(input);
            i = 0;
        }
    }
    citynum = num1;
    num2 = atoi(input);
    edgenum = num2;
    edge e[num2];
    int city[num1];
    for (i = 0; i < num1; i++)
    {
        city[i] = -1;
    }
    int citydistance[num1];
    while (true)
    {
        i = 0;
        first = true;
        second = true;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            input[i++] = c;
            input[i] = '\0';
            if (c == ' ' && first == true)
            {
                num1 = atoi(input);
                i = 0;
                first = false;
            }
            else if (c == ' ' && first == false && second == true)
            {
                num2 = atoi(input);
                i = 0;
                second = false;
            }
        }
        input[i] = '\0';
        num3 = atoi(input);
        if (second == true)
        {
            break;
        }
        if (searchcity(city, num1, citynum) == -1)
        {
            city[k++] = num1;
        }
        if (searchcity(city, num2, citynum) == -1)
        {
            city[k++] = num2;
        }
        e[j].one = num1;
        e[j].other = num2;
        e[j++].distance = num3;
    }
    from = searchcity(city, num1, citynum);
    to = searchcity(city, num3, citynum);
    for (i = 0; i < citynum; i++)
    {
        if (i == from)
            citydistance[i] = 0;
        else
            citydistance[i] = INT_MAX;
    }
    int includecity[citynum];
    for (i = 0; i < citynum; i++)
    {
        includecity[i] = -1;
    }
    int nearestcity, nearestlocal;
    int min;
    for (i = 0; i < citynum; i++)
    {
        min = INT_MAX;
        for (j = 0; j < citynum; j++)
        {
            if (includecity[j] != -1)
            {
                continue;
            }
            if (citydistance[j] < min)
            {
                min = citydistance[j];
                nearestcity = city[j];
                nearestlocal = j;
            }
        }
        includecity[nearestlocal] = 1;
        nearestcity = searchcity(city, nearestcity, citynum);
        for (j = 0; j < citynum; j++)
        {
            if (includecity[j] != -1)
            {
                continue;
            }
            if (!hasedge(city[nearestcity], city[j], e, edgenum))
            {
                continue;
            }
            if (citydistance[nearestcity] + distance(city[nearestcity], city[j], e, edgenum) < citydistance[j])
            {
                citydistance[j] = citydistance[nearestcity] + distance(city[nearestcity], city[j], e, edgenum);
            }
        }
    }
    if (citydistance[to] == INT_MAX)
    {
        printf("-1\n");
        return 0;
    }
    else
    {
        printf("%d\n", citydistance[to]);
    }
    return 0;
}

int searchcity(int city[], int num, int citysize)
{
    for (int i = 0; i < citysize; i++)
    {
        if (city[i] == num)
        {
            return i;
        }
    }
    return -1;
}

int distance(int from, int to, edge e[], int edgesize)
{
    int i;
    for (i = 0; i < edgesize; i++)
    {
        if (e[i].one == from && e[i].other == to)
        {
            return e[i].distance;
        }
        else if (e[i].one == to && e[i].other == from)
        {
            return e[i].distance;
        }
    }
    return INT_MAX;
}

bool hasedge(int from, int to, edge e[], int edgesize)
{
    int i;
    for (i = 0; i < edgesize; i++)
    {
        if (e[i].one == from && e[i].other == to)
        {
            return true;
        }
        else if (e[i].one == to && e[i].other == from)
        {
            return true;
        }
    }
    return false;
}