#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
    node *before;
};
int main()
{
    struct node *pfirst = NULL;
    struct node *pend = NULL;
    struct node n;
    struct node *p;
    struct node *p2;
    p = (struct node *)malloc(sizeof(struct node));
    int i, num;
    char c;
    char str[100];
    for (i = 0;; i++)
    {
        c = getchar();
        str[i] = c;
        str[i + 1] = '\0';
        if (c == ' ' || c == '\n')
        {
            if(str[0]=='\n'){
                break;
            }
            if(str[0]==' '){
                i=-1;
                continue;
            }
            str[i] = '\0';
            num = atoi(str);
            if (pfirst == NULL)
            {
                n.data = num;
                pfirst = &n;
                pend = &n;
                n.next = &n;
                n.before = &n;
                i = -1;
                if (c == '\n')
                {
                    break;
                }
            }
            else
            {
                p = (struct node *)malloc(sizeof(struct node));
                p->data = num;
                p->next = pfirst;
                pfirst->before = p;
                pend->next = p;
                p->before = pend;
                pend = p;
                i = -1;
                if (c == '\n')
                {
                    break;
                }
            }
        }
    }
    cin >> num;
    cout << '[';
    if (num > 0)
    {
        for (i = 0; i < num; i++)
        {
            pfirst = pfirst->before;
        }
    }
    else if (num < 0)
    {
        for (; num < 0; num++)
        {
            pfirst = pfirst->next;
        }
    }
    p2 = pfirst;
    cout << pfirst->data;
    pfirst = pfirst->next;
    for (; pfirst != p2; pfirst = pfirst->next)
    {
        cout << ',' << pfirst->data;
    }
    cout << ']';
    return 0;
}