#include<stdio.h>
#include<stdlib.h>

void exchange(int* a,int* b){
        int tmp=*a;
        *a=*b;
        *b=tmp;
}

int partition(int* a,int left,int right){
        int* pivot = a+right;
        int* i = a;
        int* j=a;
        int count=0;
        while(j<pivot){
                if(*j<*pivot){
                        exchange(j,i++);
                        count++;
                }
                j++;
        }
        exchange(i,pivot);
        return count;
}

int* quick_sort(int* a,int left,int right){
        if(left<right){
                int pivot=partition(a,left,right);
                quick_sort(a,left,pivot-1);
                quick_sort(a,pivot+1,right);
        }
        return a;
}

int main(){
        srand(2);
        int n;
        scanf("%d",&n);
        int* a=(int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++)
                a[j]=(rand()%n);
        int* tmp;
        tmp=quick_sort(a,0,n-1);
        for(int i=0;i<n;i++)
                printf("%d ",tmp[i]);
        printf("\n");
        free(a);
        return 0;
}

