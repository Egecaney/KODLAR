#include<stdio.h>
#include<math.h>

/* Mod & Tekrar
int main(){
	
	int s;
	int s2;
	int u=0;
	
	printf("1. Sayi: ");
	scanf("%d",&s);
	
	printf("2.Sayi: ");
	scanf("%d",&s2);
	
	if(s>=s2){
		while(s>=s2){
			u++;
			s = s-s2;
		}
	}
	else{
		printf("Fuck OFF!\n");
	}
	
	printf("Mod: %d \n",s);
	printf("Tekrar: %d",u);
	
	return(0);
}
*/

// Fibonacci Sayýlarý( 0 1 1 2 3 5 8 13 21 )
int main(){
	
	int number1=0;
	int number2=1;
	int i;
	int temp;
	
	printf(" %d  %d ",number1,number2);
	
	for(i=0;i<10;i++){
		
		temp=number2;
		number2+=number1;
		number1=temp;
		
		printf(" %d ",number2);
		
		
	}
	
	return 0;
}	
