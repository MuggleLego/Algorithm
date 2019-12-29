//input:given a price array p in size n
//output:the maximum revenue r_n
//solution:maximum revenue r_n=max(p_n,r_1+r_{n-1},...,r_{n-1}+r_1}
//function:naive_rod_cutting,memoized_rod_cutting,bottom_up_rod_cutting,ex_bottom_up_rod_cutting;

#include<stdio.h>
#include<stdlib.h>
#define MIN -2147483648

//counting calculations
static int k=0;
static int x=0;

int cut_rod(int* p,int n){//the naive way:grows explosively.
        if(n==0)
                return 0;
        int q=0;
        for(int i=0;i<n;i++)
                q = q>*(p+i)+cut_rod(p,n-i-1) ? q :*(p+i)+cut_rod(p,n-i-1);
        k++;
        return q;//q is used to save the optimal of every length i.
}

int memoized_cut_rod_aux(int* p,int n,int* r){
        if(*(r+n)>0)
                return *(r+n);
        int q;
        if(!n)
                q=0;
        else{
                q=MIN;//Question:why min instead of 0?I think the revenue won't be a negative.
                for(int i=0;i<n;i++)
                        q=q>*(p+i)+memoized_cut_rod_aux(p,n-i-1,r)?q:*(p+i)+memoized_cut_rod_aux(p,n-i-1,r);
        }
        x++;
        *(r+n)=q;//save the maximum revenue into a new array r
        return q;
}

int memoized_cut_rod(int* p,int n){
        int r[n];
        for(int i=0;i<n;i++)
                r[i]=MIN;
        return memoized_cut_rod_aux(p,n,r);
}

int bottom_up_cut_rod(int* p,int n){
        int* r=(int*)malloc(sizeof(int)*(n+1));
        *r=0;
        int q;
        for(int j=1;j<=n;j++){
                q=MIN;//reflesh the initialization every time.
                for(int i=1;i<=j;i++)
                        q= q>*(p+i-1)+*(r+j-i)?q:*(p+i-1)+*(r+j-i);
                *(r+j)=q;
        }
        return *(r+n);
}

/*
int* ex_bottom_up_cut_rod(int* p,int n){
        int* r=(int*)malloc(sizeof(int)*(n+1));
        int* s=(int*)malloc(sizeof(int)*(n+1));
        *r=0;
        for(int j=1;j<=n;j++){
                int q=MIN;
                for(int i=1;i<=j;i++){
                        if(q<*(p+i)+*(r+j-i))
                                *(s+j)=i;
                }
                *(r+j)=q;
        }
        return (s,r);
}

void print_cut_rod_solution(int* p,int n){
        (r,s)=ex_bottom_up_cut_rod(p,n);
        while(n>0){
                printf("%d ",*(s+n));
                n-=*(s+n);
        }
}
*/

int main(){
        int p[]={1,5,8,9,10,17,17,20,24,30};
        printf("%d\n",bottom_up_cut_rod(p,10));
        cut_rod(p,10);
        printf("%d\n",memoized_cut_rod(p,10));
        printf("recursion times of cut_rod:%d\n",k);
        printf("recursion times of memoized_cut_rod:%d\n",x);
        return 0;
}
