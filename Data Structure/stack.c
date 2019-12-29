//function:push,pop,print;

#include<stdio.h>
#include<stdlib.h>

struct stack{
        int item;
        struct stack* next;
};


void push(struct stack* stack,int item){
        struct stack* s=(struct stack*)malloc(sizeof(struct stack));
        s->item=item;
        s->next=stack->next;
        stack->next=s;
}

struct stack* pop(struct stack* s){
        struct stack* tmp=s->next;
        if(!tmp)
                return 0;
        //printf("%d popped\n",tmp->item);
        s->next=tmp->next;
        return tmp;
}

void print_stack(struct stack* s){
        struct stack* tmp=s->next;
        while(tmp){
                printf("%d ",tmp->item);
                tmp=tmp->next;
        }
        printf("\n");
}

int main(){
        struct stack* s=(struct stack*)malloc(sizeof(struct stack));
        s->next=NULL;
        for(int i=1;i<=5;i++)
                push(s,i);
        print_stack(s);
        for(int j=1;j<=3;j++)
                printf("%d ",pop(s)->item);
        printf("\n");
        return 0;
}
