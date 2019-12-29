#include<stdio.h>

void insert(int arr[ ],int len){
        int key,j;
        for(int i=1;i<len;i++){
                key=arr[i];//the entry to be inserted
                j=i-1;//
                while (j>=0 && arr[j]>key){
                        arr[j+1]=arr[j];//move
                        j=j-1;
                }
                arr[j+1]=key;//arr[j] is less or equal to key
        }
}

