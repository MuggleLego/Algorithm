//date:2020.11.06
//path:~/Code/DS
#include <iostream>
#include <stdlib.h>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

//循环链表
struct Cyclist
{
    node *dummy;
    node *rear;
};

//创建循环链表中的结点
node *create(int c)
{
    node *_node = (node *)malloc(sizeof(node));
    _node->data = c;
    _node->next = NULL;
    return _node;
}

//创建循环链表
Cyclist *create_Cyclist()
{
    Cyclist *list = (Cyclist *)malloc(sizeof(Cyclist));
    list->dummy = create(0);
    list->rear = create(0);
    return list;
}

//向循环链表添加结点
void append(Cyclist *list, int x)
{
    node *_node = create(x);
    if (list->dummy->next == NULL)
    {
        list->dummy->next = _node;
        list->rear = _node;
        _node->next = _node;
        return;
    }
    list->rear->next = _node;
    _node->next = list->dummy->next;
    list->rear = _node;
}

//删除循环链表中dummy后的第一个节点
void delete_front(Cyclist *list)
{
    if (list->dummy->next == NULL)
        return; //empty list
    node *tmp = list->dummy->next->next;
    free(list->dummy->next);
    if (list->rear == NULL)
        return; //empty list
    list->dummy->next = tmp;
    list->rear->next = list->dummy->next;
}

Cyclist *order_of_dequeue(Cyclist *list)
{
    Cyclist *res = create_Cyclist();
    int i = 0;
    while (list->dummy->next != list->rear)//more than one element in the queue
    {
        if (!(i & 1))
        {                                         //i is even
            append(res, list->dummy->next->data); //move the front to a new queue
            delete_front(list);
        }
        else
        {
            append(list, list->dummy->next->data); //move the front to the end of a queue
            delete_front(list);
        }
        i++;
    }
    append(res,list->rear->data);//put the last element into the new queue
    return res;
}

//打印循环链表
void pri_Cyclist(Cyclist *list)
{
    node *first = list->dummy->next;
    if (first == NULL)
    {
        printf("\n");
        return;
    }
    printf("%d ", first->data);
    node *walker = first->next;
    while (walker != first)
    {
        printf("%d ", walker->data);
        walker = walker->next;
    }
    printf("\n");
}

int main()
{
    int n;
    cin >> n;
    Cyclist *list = create_Cyclist();
    for (int i = 1; i <= n; i++)
    {
        append(list, i);
    }
    Cyclist *res = order_of_dequeue(list);
    pri_Cyclist(res);
    return 0;
}
