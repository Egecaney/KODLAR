#include<stdio.h>

//Experiment2_Session1_Q1
 int main(){
	
	int N;
	int i;
	int total=0;
 
    printf("How many shots entered: ");
    scanf("%d",&N);
    
    for(i=1;i<=N;i++){
    	
    	total += 2;
    	
    	if(i%3==0){
    		total +=5;
		}
    	
	}
 
	printf("Total Score: %d",total);
	
	return(0);
}


/*Experiment2_Session1_Q2
int main()
{
    int number;
	int i;
	int j;
	int temp=1;
	int largest=0;

    printf("Enter a number: ");
    scanf("%d",&number);

    for(i=0;i<=number;i++){
    	
        temp=1;
		for(j=2;j<=i/2;++j){
			
        if (i%j==0){
            temp =0;
        }
    }
        if(temp == 1 && i !=0 && i!=1){
             largest=i;
		}      
    }
    
    printf("The largest prime number is: %d",largest);
    return (0);
}
*/

