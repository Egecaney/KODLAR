#include<stdio.h>
#include<math.h>

// Q1_Session1
int dectobinary(int number);
int main(){
	
	int number;

	printf("Enter a decimal number: ");
	scanf("%d",&number);
	dectobinary(number);
	return (0);
}

int dectobinary(int number){
    
	int number2;
	int i;
	int b[10];
	int k=0;
	number2=number; 

	for(i=10;i>0;i--){
		
		b[i] = number%2;
		number = number/2;
		k++;
		if(number==1){
			b[i-1]=1;
			break;
		}
		
	}
	printf("%d in decimal = ",number2);
	for(i=10-k;i<11;i++){
		printf("%d",b[i]);
	}
	printf(" in binary");
}
//

/*Q2_Session2
int main(){
	
	int lenght;
	int number[100];
	int search;
	int position=0;
	int i;
	int t=0;
	
	printf("Enter the number of element is array: ");
	scanf("%d",&lenght);
	
	printf("Enter %d integer(s): ",lenght);
	for(i=0;i<lenght;i++){
	scanf("%d",&number[i]);	
	}
	
    printf("Enter a number to search: ");
    scanf("%d",&search);
    
    for(i=0;i<lenght;i++){
    	
    	if(search==number[i]){
    		position++;
    		t++;
    		break;
		}
    	position++;
	}
    if(t==1){
    	printf("%d is present at location %d",search,position);
	}
    else{
    	printf("%d is not defined.",search);
	}
    
	return(0);
}
*/
