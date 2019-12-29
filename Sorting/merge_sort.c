//merge:input two ordered arrays.
//      output an ordered array.
//merge_sort:input a random array.
//           output an ordered array by divide array into subarray recursively.

int* merge(int* a,int* b,int len_a,int len_b){
        int* res=(int*)malloc(sizeof(int)*(len_a+len_b));
        int* end_b=b+len_b;
        int* end_a=a+len_a;
        int* p_a=a;
        int* p_b=b;
        int i=0;
        while(p_a != end_a && p_b != end_b){
                if(*p_a<*p_b){
                        res[i++]=*p_a;
                        p_a++;
                }
                else{
                        res[i++]=*p_b;
                        p_b++;
                }
        }
        if(p_a == end_a){
                while(p_b!=end_b){
                        res[i++]=*p_b;
                        p_b++;
                }
        }
        else{
                while(p_a!=end_a){
                        res[i++]=*p_a;
                        p_a++;
                }
        }
        return res;
}

int* merge_sort(int* a,int len){
        if(len==1)
                return a;
        int mid=len/2;
        int* tmp1=merge_sort(a,mid);
        int* tmp2=merge_sort(a+mid,len-mid);
        a=merge(tmp1,tmp2,mid,len-mid);
        return a;
}
