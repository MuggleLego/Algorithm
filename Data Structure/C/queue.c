//funtion:initialize,enqueue,dequeue

#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
        int item;
        struct _node* next;
}node;

typedef struct _queue{
        node* head;
        node* tail;
}queue;


void enqueue(queue* q,int item){
        node* new=(node*)malloc(sizeof(node));
        new->item=item;
        new->next=NULL;
        if(!q->head){
                q->head=q->tail=new;
                return;
        }
        q->tail->next=new;
        q->tail=new;
}


void dequeue(queue* q){
        if(!q->head)
                return;
        node* tmp=q->head;
        printf("%d dequeue\n",tmp->item);
        q->head=tmp->next;
        free(tmp);
}

int main(){
        queue* q=(queue*)malloc(sizeof(queue));
        q->head=q->tail=NULL;
        for(int i=1;i<=5;i++)
                enqueue(q,i);
        for(int j=1;j<=5;j++)
                dequeue(q);
        return 0;
}
