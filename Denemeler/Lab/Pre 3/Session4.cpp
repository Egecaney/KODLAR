#include<stdio.h>

//Q1_Session4
int main(){

 int size;
 int i=0;
 int j=0;
 int k=1;
 int temp1=0;
 
 printf("Please enter of size of table: ");
 scanf("%d",&size);
 
 int matrix[size][size];
 
 if(size%2==0){
	
 	for(i=0;i<size;i++){
 		
 	    k=i+1;
		 for(j=0;j<size/2;j++){

			matrix[i][j] =j+k;
		}
		temp1=0;
	    for(j=size-1;j>=size/2;j--){
	    	
			matrix[i][j] = matrix[i][temp1];
	    	temp1++;
		}	
	    }		
	 }
	 
 else{
 	for(i=0;i<size;i++){
 		
 	    k=i+1;
		 for(j=0;j<=size/2;j++){

			matrix[i][j] =j+k;
		}
	
		temp1=0;
	    for(j=size-1;j>=size/2;j--){
	    	
			matrix[i][j] = matrix[i][temp1];
	    	temp1++;
		}	
	    }		
	 }
	 
	 
 	for(i=0;i<size;i++){
	 	for(j=0;j<size;j++){
	 		printf("%d ",matrix[i][j]);
		 }
		 puts(" ");	
 }	
	 
	 return(0);
} 
// 

/*Q2_Session4
int main(){
	
	int matrix[10][5];
	int add[5];
	int command;
	int com1;
	int com2;
	int i;
	int j;
	
	for(i=0;i<10;i++){
			for(j=0;j<5;j++){
			matrix[i][j] =0 ;
			}			
    }
    
	while(1){
	command=0;
	com1=0;	
	printf("Enter command: ");
	scanf("%d",&command);
	com1= command-10;
	
	if(com1>=0 && com1<10){
		printf("\n--Add process for %d\n",com1);
		
		for(i=0;i<5;i++){
			printf("Enter data %d: ",i+1);
			scanf("%d",&add[i]);
		}
		
		for(j=0;j<5;j++){
			matrix[com1][j] = add[j];
		}
		printf("\nUpdated Data: \n");
		for(i=0;i<10;i++){
			for(j=0;j<5;j++){
				printf("%d ",matrix[i][j]);
			}
			puts("");
		}
	}
	
	else if(com1>=10 && com1<20){
		com1 = com1-10;
		printf("\n--Clear process for %d\n",com1);
		
		for(j=0;j<5;j++){
			matrix[com1][j] = 0;
		}
		printf("\nUpdated Data: \n");
		for(i=0;i<10;i++){
			for(j=0;j<5;j++){
				printf("%d ",matrix[i][j]);
			}
			puts("");
		}
	}
	
	puts("");	
	}
	return(0);
}
*/
