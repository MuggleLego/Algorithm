//function:random_build_heap,l_child_index,r_child_index,max_heapify,build_max_heap,heap_sort;

#include<stdio.h>
#include<stdlib.h>

typedef struct _heap{
        int size;
        int* heap;
}heap;

//randomly build a heap
heap* build_random_heap(int size){
        heap* h=(heap*)malloc(sizeof(heap));
        h->size=size;
        h->heap=(int*)malloc(sizeof(int)*size);
        for(int i=0;i<size;i++)
                h->heap[i]=(rand()%size);
        return h;
}

//calculate the index of the left child of a node
int left(int i){
        return ((i+1)<<1)-1;
}

//calculate the index of the right child of a node
int right(int i){
        return (i+1)<<1;
}

void exchange(int* a,int* b){
        int tmp;
        tmp=*a;
        *a=*b;
        *b=tmp;
}

//build a max_heap in recursion way
void max_heapify(heap* h,int i){
        int l=left(i);
        int r=right(i);
        int largest=i;
        if(l<h->size && h->heap[i]<h->heap[l])
                largest=l;
        if(r<h->size && h->heap[r]>h->heap[largest])
                largest=r;
        if(largest-i){
                exchange(&(h->heap[i]),&(h->heap[largest]));
                max_heapify(h,largest);
        }
}

void build_max_heap(heap* h){
        for(int i=(h->size-1)/2;i>=0;i--)
                max_heapify(h,i);
}

void heap_sort(heap* h){
        build_max_heap(h);
        for(int i=h->size-1;i>0;i--){
                exchange(&(h->heap[0]),&(h->heap[i]));
                h->size--;
                max_heapify(h,0);
        }
}

//input the size of the heap
//the entry in the heap will be in range(0,size-1)
int main(){
        int n;
        scanf("%d",&n);
        heap* h=build_random_heap(n);
        heap_sort(h);
        for(int i=0;i<n;i++)
                printf("%d ",h->heap[i]);
        printf("\n");
        return 0;
}

