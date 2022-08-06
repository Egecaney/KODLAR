#include<stdio.h>
#include <stdlib.h>
#include<math.h>

/* Experiment2_Session4_Q1
int main(){
	
	int number;
	int i;
	int temp1;
	int temp2;
	
	printf("Integer square root of ");
	scanf("%d",&number);
	
	for(i=1;i<=100;i++){
		
		temp1 = (i+1)*(i+1);
		temp2 = i*i ;
		
		if(temp1>number && temp2<=number){
			printf("Answer: %d",i);
		}
		
	}
	
	return(0);
}
*/

// Experiment2_Session4_Q1
int main(){
	float x, y;
	float distance = 0;
	long int inside = 0;
	long int total = 10000000;
	
	for(int i = 0; i < total; i++){
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		distance = sqrt(x*x+y*y);
		
		if(distance <= 1){
			inside++;
		}
	
	}
	
	printf("Approximate value of pi is : %.5f\n", 4*(float)inside/total );
	
	return 0;
}
//
