void swap(int* a,int* b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void bubble(int arr[ ],int len){
        for(int i=0;i<len-1;i++){  //i marks the bubbled position
                for(int j=0;j<len-i-1;j++){
                        if(arr[j]>arr[j+1]){   //bubbling
                               swap(arr+j,arr+j+1);
                        }
                }
        }
}
