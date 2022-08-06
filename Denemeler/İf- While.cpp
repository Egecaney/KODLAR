#include<stdio.h>


int main(){
	
	int a;
	int b;
	
	printf("Enter the number: ");
	scanf("%d",&a);
	
	
	if(a>=5 && a<=10){
		while(a>=5){
		
	b += a;
	a= a-1;
			
	}
	}
	
	else if(a>10 && a<=20){
		b=100;
	while(a>10 && a<=15){
	b -= a;
	a= a-1;
	}
	}
	
	else{
		printf("Unmateched \n");
	}
	
	printf("A is %d, B is %d ",a,b);
	
	return(0);
}
