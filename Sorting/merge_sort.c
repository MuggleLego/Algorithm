#include<stdio.h>
#include<stdlib.h>

//input:two ordered arrays
//output:an ordered array
int* merge(int* a,int* b,int len_a,int len_b){
        int* res=(int*)malloc(sizeof(int)*(len_a+len_b)); //malloc the new array
        int* p_a=a;  //head pointers
        int* p_b=b;
        int i=0;  //index of new array
        while(p_a != a+len_a && p_b != b+len_b){  //pick the smaller one into new array
                if(*p_a<*p_b){
                        res[i++]=*(p_a++);
                }
                else{
                        res[i++]=*(p_b++);
                }
        }
        if(p_a == a+len_a){   //put the rest of array b in the new array 
                while(p_b!=b+len_b){
                        res[i++]=*(p_b++);
                }
        }
        else{
                while(p_a!=a+len_a){   //put the rest of array a in the new array
                        res[i++]=*(p_a++);
                }
        }
        return res;
}

//input:a random array
//output:an ordered array by divide array into subarray recursively.
int* merge_sort(int* a,int size){
        if(size==1)
                return a;    //base case
        int mid=size>>1;  //divide-and-conquer
        int* tmp1=merge_sort(a,mid);
        int* tmp2=merge_sort(a+mid,size-mid);
        a=merge(tmp1,tmp2,mid,size-mid);
        return a;
}

int main(){
        int n;
        scanf("%d",&n);
        int a[n];
        for(int i=0;i<n;i++){
                scanf("%d",a+i);
        }
        int* tmp=merge_sort((int*)a,n);
        for(int j=0;j<n;j++)
                printf("%d ",tmp[j]);
        printf("\n");
        return 0;
}
