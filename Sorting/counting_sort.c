#include<stdio.h>
#include<stdlib.h>

int* counting(int* a,int a_size,int k){
        int b[k+1]; //k is the biggest key in array a
        int* res=(int*)malloc(sizeof(int)*a_size);
        for(int i=0;i<k+1;i++)
                b[i]=0;
        for(int j=0;j<a_size;j++)
                b[a[j]]+=1;//the number in b[i] is the number of i in array a
        for(int h=1;h<k+1;h++)
                b[h]+=b[h-1];//b[i] now contains the number of elements less than or equal to i
        for(int j=a_size-1;j>=0;j--){
                res[b[a[j]]-1]=a[j];  //by the value in array b to see how many elements are less
                b[a[j]]-=1;        //than or equal to a[j],to find a[j]'s postition
        }
        return res;
}

int main(){
        int a[]={2,5,3,0,3,2,0,3};
        int* b=counting(a,8,5);
        for(int i=0;i<8;i++)
                printf("%d ",b[i]);
        printf("\n");
        free(b);
        return 0;
}
