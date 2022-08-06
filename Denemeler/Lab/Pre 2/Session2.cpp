#include<stdio.h>

// Experiment2_Q1
int main(){
	
	int number;
	int temp;
	int count=1;
	int i=2;
	int prime=0;
	int finish=0;
	
	
	printf("Please,enter the number to check: ");
	scanf("%d",&number);
	temp= number;
	
	
	do{
		if(i<=number/2){
			if(number%i==0){
				printf("Count: %d, Number: %d\n",count,number/i);
				prime=1;
				count++;
				if(count==4){
					finish =1;
				}	
		}
		i++;
		}
		if(i>temp/2){
				finish =1;
		}
	}while(finish!=1);
	
	if(prime==0){
		printf("The number is entered a prime number.");
	}
	
	return(0);
}


/* Experiment2_Section2_Q2
int main(){
	
	double n;
	double e = 2.71828182;
	double number=1;
	int i;
	
	printf("Please choose the accuracy for the estimate of e: ");
	scanf("%lf",&n);
	
	printf("You have chosen %.0lf",n);
	
	for(i=1;i<=n;i++){
		number *= (1+(1/n));
	}
	
	printf("\nEstimate of the constant e is: %lf",number);
	printf("\nActual e constant is equal to: %lf",e);
    printf("\nError between the estimate of e and actual e constant is: %lf",e-number);
    
	return(0);
}
*/
