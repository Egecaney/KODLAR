#include<stdio.h>
#include<math.h>

/*
int main(){
	
	int s;
	int n;
	int s1;
	int u=1;
	
	printf("1. Sayi: ");
	scanf("%d",&s);
	
	printf("2.Sayi: ");
	scanf("%d",&n);
	
	s1 = s;
	
	while(n>u){
	    u++;
	    s= s*s1;
	    printf("Sonuc: %d , %d \n",s, u);
	        
	}
	printf("Final Sonuc: %d",s);
	
	return(0);
}
*/

 int main(){
 
	int number1;
	int number2;
	int number3;
	int counter=1;
	
	puts("It is an exponential finding operation.(N1)^N2 ");
	printf("Enter the N1: ");
	scanf("%d",&number1);
	
	printf("Enter the N2: ");
	scanf("%d",&number2);
	
	number3=number1;
	
	while(counter<number2){
		
		number1 = number1*number3;
		counter++;
	}
	
	printf("Result: %d",number1);
	return(0);
}
