//find min and max in a array

#include<stdio.h>
#include<stdlib.h>

//naive version
int minimum(int* a,int a_size){
        int min=a[0];
        for(int i=1;i<a_size;i++){
                if(min>a[i])
                        min=a[i];
        }
        return min;
}

//naive version
int maximum(int* a,int a_size){
        int max=a[0];
        for(int i=1;i<a_size;i++){
                if(max<a[i])
                        max=a[i];
        }
        return max;
}

//simple version
//using Theta(n) times comparisons
int* simultaneous_min_and_max(int* a,int a_size){
        int min,max;     
        if(a_size&1){
                min=a[0];
                max=a[0];
        }
        if(~a_size&1){
                if(a[0]>a[1]){
                        min=a[1];
                        max=a[0];
                }
                else{
                        min=a[0];
                        max=a[1];
                }
        }     //initialization
        for(int i=1;i<a_size;i+=2){
                if(a[i]>a[i+1]){
                        if(a[i]>max)
                                max=a[i];
                        if(a[i+1]<min)
                                min=a[i+1];
                }
                else{
                        if(a[i]<min)
                                min=a[i];
                        if(a[i+1]>max)
                                max=a[i+1];
                }
        }
        int* res=(int*)malloc(sizeof(int)*2);
        res[0]=min;
        res[1]=max;
        return res;
}
