#include<stdio.h>

// Session3_Q1
int main(){
	
	int number[10][10];
	int row;
	int col;
	int i,j;
	
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
		    number[i][j]=0;
		    printf("%d ",number[i][j]);
		}
		printf("\n");
	}
	while(1){
		printf("Enter the coordinates (row,col): ");
		scanf("%d",&row);
		scanf("%d",&col);
		
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
		    	if((row-1)+i>=0&&(row-1)+i<=9&&(col-1)+j>=0&&(col-1)+j<=9){
		    		number[(row-1)+i][(col-1)+j] += 1;
				}
	    	}	
		}
		
		for(i=0;i<10;i++){
		for(j=0;j<10;j++){
		    printf("%d ",number[i][j]);
		}
		printf("\n");
	}
    }
	return(0);
}
//

/* Session3_Q2
void sortIntegers(int *nums, int len);
int main(){
	
	int nums;
	int len;
	
	printf("Enter the size of input: ");
	scanf("%d",&len);
	
	sortIntegers(&nums,len);
	return(0);
}
void sortIntegers(int *nums, int len){

	int i,j;
	int order[len];
	int temp;
	
	for(i=0;i<len;i++){
		printf("Please, enter the value %d: ",i+1);
		scanf("%d",nums);
		nums += 1;
	}
	
	nums = nums-len;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			if(*(nums+j)>=*(nums+i)){
				temp=*(nums+i);  
                *(nums+i)=*(nums+j);
                *(nums+j)=temp;
			}	
        }
		}
		
	printf("The stored array are: ");
	for(i=0;i<len;i++){
		printf("%d ",*nums);
		nums++;
	}
}
*/
