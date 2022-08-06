#include<stdio.h>

//Session2_Q1
int main(){
	
	int number[6][6];
	int i;
	int j;
	int direction;
	int placex[4]={2,3,2,3};
	int placey[4]={2,2,3,3};
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
		number[i][j]=0;
	}
	}
	number[2][2]=1;
	number[3][2]=1;
	number[2][3]=1;
	number[3][3]=1;
	
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
		printf(" %d ",number[i][j]);
	}
	printf("\n");
	}
	while(1){
		puts("-----------------");
		printf("Please, enter the direction: ");
		scanf("%d",&direction);
		
	if(direction==4){
			for(i=0;i<4;i++){
				placex[i]--;
				if(placex[i]==-1){
					placex[i]=5;
				}
			}
			
		for(i=0;i<6;i++){
		    for(j=0;j<6;j++){
		    number[i][j]=0;
	    }	
		}
		for(i=0;i<4;i++){
			number[placey[i]][placex[i]]=1;
		}
	}
	if(direction==6){
			for(i=0;i<4;i++){
				placex[i]++;
				if(placex[i]==6){
					placex[i]=0;
				}
			}
			
		for(i=0;i<6;i++){
		    for(j=0;j<6;j++){
		    number[i][j]=0;
	    }	
		}
		for(i=0;i<4;i++){
			number[placey[i]][placex[i]]=1;
		}
	}
	if(direction==8){
			for(i=0;i<4;i++){
				placey[i]--;
				if(placey[i]==-1){
					placey[i]=5;
				}
			}
			
		for(i=0;i<6;i++){
		    for(j=0;j<6;j++){
		    number[i][j]=0;
	    }	
		}
		for(i=0;i<4;i++){
			number[placey[i]][placex[i]]=1;
		}
	}
	if(direction==2){
			for(i=0;i<4;i++){
				placey[i]++;
				if(placey[i]==6){
					placey[i]=0;
				}
			}
			
		for(i=0;i<6;i++){
		    for(j=0;j<6;j++){
		    number[i][j]=0;
	    }	
		}
		for(i=0;i<4;i++){
			number[placey[i]][placex[i]]=1;
		}
	}
	if(direction==2||direction==4||direction==6||direction==8){
	    for(i=0;i<6;i++){
		    for(j=0;j<6;j++){
		    printf(" %d ",number[i][j]);
	}
	    printf("\n");
    }		
	}
	else{
		printf("Not Exists.");
		break;
	}
   }
	return(0);
}
//

/* Session2_Q2
void getNumbers(int *numbers1, int *numbers2, int *count);
void checkSimilarity(int *numbers1, int *numbers2, int *count);
int main(){
	
	int count;
	printf("How many questions are there in the text: ");
	scanf("%d",&count);
	
	int numbers1;
	int numbers2;
	getNumbers(&numbers1,&numbers2,&count);
	checkSimilarity(&numbers1,&numbers2,&count);
	return(0);
}
void getNumbers(int *numbers1, int *numbers2, int *count){
	
	    numbers1= numbers1+2;
		int s1;
		int s2;
		int i;
		//printf("%d\n",numbers1);
		for(i=0;i<*count;i++){
			printf("Please enter the answer of First student for question %d: ",i+1);
			scanf("%d",&s1);
			*numbers1 = s1;
			numbers1++;
			//printf("%d\n",numbers1);
		}
		numbers2=numbers1+2;
		//printf("%d\n",numbers2);
		for(i=0;i<*count;i++){
			printf("Please enter the answer of Second student for question %d: ",i+1);
			scanf("%d",&s2);
			*numbers2 = s2;
			numbers2++;
			//printf("%d\n",numbers2);
		}
	}
void checkSimilarity(int *numbers1, int *numbers2, int *count){
	
	int k=0;
	int i;
	numbers1= numbers1+2;
	numbers2= numbers1+*count+2;
	///printf("%d %d\n",numbers1,numbers2);
	
	for(i=0;i<*count;i++){
		if(*numbers1==*numbers2){
			k++;
		}
		numbers1++;
		numbers2++;
	}
	printf("Similarity between two student' answers: ");
	printf("%d",k*100/(*count));
}
*/
