void swap(int* a,int* b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
			
void select(int arr[ ],int len){
        int mark;
        for(int i=0;i<len-1;i++){//choose the i^th smallest number
                mark=i;
                for(int j=i+1;j<len;j++){
                        if (arr[j]<arr[mark])
                                mark=j;//mark the i^th smallest
                }
                swap(arr+mark,arr+i);
        }
}
