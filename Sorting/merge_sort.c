//merge:input two ordered arrays.
//      output an ordered array.
//merge_sort:input a random array.
//           output an ordered array by divide array into subarray recursively.

int* merge(int* a,int* b,int len_a,int len_b){
        int* res=(int*)malloc(sizeof(int)*(len_a+len_b)); //malloc the new array
        int* end_b=b+len_b;  //tail pointers
        int* end_a=a+len_a;
        int* p_a=a;  //head pointers
        int* p_b=b;
        int i=0;  //counter
        while(p_a != end_a && p_b != end_b){  //pick the smaller one into new array
                if(*p_a<*p_b){
                        res[i++]=*p_a;
                        p_a++;
                }
                else{
                        res[i++]=*p_b;
                        p_b++;
                }
        }
        if(p_a == end_a){   //put the rest of array b in the new array 
                while(p_b!=end_b){
                        res[i++]=*p_b;
                        p_b++;
                }
        }
        else{
                while(p_a!=end_a){   //put the rest of array a in the new array
                        res[i++]=*p_a;
                        p_a++;
                }
        }
        return res;
}

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
