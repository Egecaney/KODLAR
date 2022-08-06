#include<stdio.h>
#include<math.h>
#include<string.h>
#include <ctype.h>

// Session1_Q1
void sumNumbers(char * numbers);
int main(){
	
	char numbers[999];
	printf("Please enter the numbers with comma in-between: ");
	gets(numbers);
	sumNumbers(numbers);
	return(0);
}

void sumNumbers(char *numbers){
		
	int temp1=0;
	int temp2;
    int temp3;
	int i=0;
	int total=0;
	int power=0;
	 	
	while(numbers[i]!= NULL){
	 	temp1++;
	 	i++;
	}
		
	for(i=temp1-1; i>=0 ; i--){
		if(numbers[i]==','){
		power=0;
		}
	    else{
			temp2=numbers[i]-48;
			temp3=temp2*pow(10,power);
			total=total+temp3;
			power=power+1;
		}
	}
	printf("Here is the total of the given numbers: %d",total);
}
//

/* Session1_Q2
void convertToSentenceCase(char *sentence);
int main(){

    char sentence[200];
   	printf("Please enter your sentence: ");
    gets(sentence);
   	convertToSentenceCase(sentence);
	return(0);
}
void convertToSentenceCase(char *sentence){
	
	int i;
	printf("Here is the result: ");
    printf("%c", toupper(sentence[0]));

  	for(i=1;i<strlen(sentence);i++){
     	if(sentence[i] == '.'){
    	printf(".%c", toupper(sentence[i+1])); 
    	i++;
    	} 
		else{
    	printf("%c", sentence[i]);
    	}
    }
}
*/
