#include<stdio.h>

/* Session4_Q1
void letter_grade(int points, char *gradepLetter, char *gradepNumber, char *just_missedp);
int main(){
	
	int points;
	char gradepLetter;
	char gradepNumber;
	char just_missedp;
	
	printf("Please enter the points for grading: ");
	scanf("%d",&points);
	
	letter_grade(points,&gradepLetter,&gradepNumber,&just_missedp);
	if(gradepLetter!='D'&& gradepLetter!='F'){
	printf("Letter grade is: %c%c",gradepLetter,gradepNumber);	
	}
	else{
	printf("Letter grade is: %c",gradepLetter);
	}
	
	printf("\nStudent missed the next grade a single point? %c",just_missedp);

	return(0);
}
void letter_grade(int points, char *gradepLetter, char *gradepNumber, char *just_missedp){
	
	if(points>=95&&points<=100){
		*gradepLetter = 'A';
		*gradepNumber = '1';
	}
	else if(points>=90&&points<=94){
		*gradepLetter = 'A';
		*gradepNumber = '2';
	}
	else if(points>=85&&points<=89){
		*gradepLetter = 'A';
		*gradepNumber = '3';
	}
	else if(points>=80&&points<=84){
		*gradepLetter = 'B';
		*gradepNumber = '1';
	}
	else if(points>=75&&points<=79){
		*gradepLetter = 'B';
		*gradepNumber = '2';
	}
	else if(points>=70&&points<=74){
		*gradepLetter = 'B';
		*gradepNumber = '3';
	}
	else if(points>=65&&points<=69){
		*gradepLetter = 'C';
		*gradepNumber = '1';
	}
	else if(points>=60&&points<=64){
		*gradepLetter = 'C';
		*gradepNumber = '2';
	}
	else if(points>=55&&points<=59){
		*gradepLetter = 'C';
		*gradepNumber = '3';
	}
	else if(points>=50&&points<=54){
		*gradepLetter = 'D';
		*gradepNumber = '0';
	}
	else{
		*gradepLetter = 'F';
		*gradepNumber = '0';
	}
	
	
	if(points==94 && *gradepLetter =='A' && *gradepNumber== '2'){
		*just_missedp = 'Y';
	}
	if(points==89 && *gradepLetter =='A' && *gradepNumber== '3'){
		*just_missedp = 'Y';
	}
	if(points==84 && *gradepLetter =='B' && *gradepNumber== '1'){
		*just_missedp = 'Y';
	}
	if(points==79 && *gradepLetter =='B' && *gradepNumber== '2'){
		*just_missedp = 'Y';
	}
	if(points==74 && *gradepLetter =='B' && *gradepNumber== '3'){
		*just_missedp = 'Y';
	}
	if(points==69 && *gradepLetter =='C' && *gradepNumber== '1'){
		*just_missedp = 'Y';
	}
	if(points==64 && *gradepLetter =='C' && *gradepNumber== '2'){
		*just_missedp = 'Y';
	}
	if(points==59 && *gradepLetter =='C' && *gradepNumber== '3'){
		*just_missedp = 'Y';
	}
	if(points==54 && *gradepLetter =='D' && *gradepNumber== '0'){
		*just_missedp = 'Y';
	}
	if(points==49 && *gradepLetter =='F' && *gradepNumber== '0'){
		*just_missedp = 'Y';
	}
	else if(points!=94&&points!=89&&points!=84&&points!=79&&points!=74&&points!=69&&points!=64&&points!=59&&points!=54&&points!=49){
		*just_missedp = 'N';
	}
}
*/

// Session4_Q2
void scan_data(char *a, double *b);
void do_next_op(char *a, double *b, double *result);

int main()
	{
		double result=0;
		char a;
		double b;
				
		while(1!=0){
			scan_data(&a,&b);
			do_next_op(&a,&b,&result);
			if(a=='q'){
				break;
			}
		}
		return(0);
	}

void scan_data(char *a, double *b){
		char x;
		int y;
		char enter;
		scanf("%c",&x);
		scanf("%d",&y);
		*a = x;
		*b = y;
		scanf("%c",&enter);
	}

void do_next_op(char *a, double *b, double *result){
		if(*a=='+'){
			*result = *result + *b;
			printf("Result so far is %.1f\n", *result);
		}
		
		if(*a=='-'){
			*result = *result - *b;
			printf("Result so far is %.1f\n", *result);
		}
		
		if(*a=='*'){
			*result = *result * *b;
			printf("Result so far is %.1f\n", *result);
		}
		
		if(*a=='/'){
			*result = *result / *b;
			printf("Result so far is %.1f\n", *result);
		}
		
		if(*a=='^'){
			if(*b==0){
			*result = 1;
			printf("Result so far is %.1f\n", *result);
				}
			else{
			int x= *result;
			{
			for(int i=1; i<*b; i++){
			*result=(*result)*x;	
			}
			printf("Result so far is %.1f\n", *result);
			}
			}
		}
		
		if(*a=='q'){
		    printf("Final result is %.1f\n", *result);		
		}
}	
//

