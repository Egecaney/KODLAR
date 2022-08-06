#include<stdio.h>
#include<math.h>

// Session1_Q1
int absolutenorm(int number[],int size);
double euclideannorm(int number[],int size);
int maximumnorm(int number[],int size);
int main(){
	
	int absnorm;
	double eucnorm;
	int maxnorm;
	int i;
	
	int size;
	printf("Enter the size of vector x:" );
	scanf("%d",&size);

	int number[size];
	printf("Enter the elements of x: ");
	for(i=0;i<size;i++){
		scanf("%d",&number[i]);
	}
	
	printf("\nThe vector x : ");
	for(i=0;i<size;i++){
		printf("%d ",number[i]);
	}
	puts("\n-------------------------------");
	
	absnorm = absolutenorm(number,size);
	eucnorm = euclideannorm(number,size);
	maxnorm= maximumnorm(number,size);
	printf("\nThe Absolute-value norm of x: %d",absnorm);
	printf("\nThe Euclidean norm of x: %lf",eucnorm);
	printf("\nThe Maximum norm of x: %d",maxnorm);
	return(0);
}
int absolutenorm(int number[],int size){
	
	int absnorm=0;
	int i;
	for(i=0;i<size;i++){
		absnorm += abs(number[i]);	
	}
	return absnorm;
}
double euclideannorm(int number[],int size){
	
	double eucnorm;
	int temp=0;
	int i;
	for(i=0;i<size;i++){
		temp += pow(number[i],2);
	}
	eucnorm = (double)temp;
	printf("%lf",eucnorm);
	eucnorm = sqrt(eucnorm);
	return eucnorm;
	
}
int maximumnorm(int number[],int size){
	
	int maxnorm;
	int i;
	maxnorm = abs(number[0]);
	for(i=1;i<size;i++){
		if(maxnorm<abs(number[i])){
			maxnorm = abs(number[i]);
		}
	}
	return maxnorm;
}
//

/* Session1_Q2
int main(){
	
	int size;
	int *left;                          
	int *right;
	int i;
	int tmp;
	printf("The lenght of input array: ");
	scanf("%d",&size);
	puts("************     ************");
	
	int number1[size];
	int temp[size];
	
	
	for(i=0;i<size;i++){
		printf("Please, enter the value %d: ",i+1);
		scanf("%d",&number1[i]);
		temp[i]=number1[i];
	}
	
	left = &number1[0];                                 
	right = &number1[size-1];                           
	
	while(left < right) 
    {
        tmp=*left;          
	    *left=*right;
	    *right=tmp;
	    
        left++;                                         
        right--;                                        
    }
	printf("\n");
	puts("The input array --- The output array");
	for(i=0;i<size;i++){
	printf("      %d         ---        %d\n",temp[i],number1[i]);
	}	
return(0);	
}
*/
