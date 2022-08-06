#include<stdio.h>

//Experiment2_Session3_Q1
int main(){
	
	int code;
	int score;
	int score1=0;
	int score2=0;
	int score3=0;
	int i;
	
	for(i=0;i<3;i++){
		
	printf("\nEnter score code: ");
	scanf("%d",&code);
	printf("Enter score: ");
	scanf("%d",&score);
	
	switch(code){
		
		case 1:
			score1 +=score;
		break;
		case 2:
			score2 +=score;
		break;
		case 3:
			score3 +=score;
		break;
		default:
			printf("There is no such code.\n");
		break;	
	}
	
	printf("\nScore1: %d",score1);
	printf("\nScore2: %d",score2);
	printf("\nScore3: %d\n",score3);

	}
	
	return(0);
}


/* Experiment2_Session3_Q1
int main(){
	
	
	int strmonth;
	int strday;
	int start;
	int endmonth;
	int endday;
	int end;
	
	
	printf("Enter start day: ");
	scanf("%d",&strday);
	printf("Enter start month: ");
	scanf("%d",&strmonth);
	puts(" ");
	printf("Enter end day: ");
	scanf("%d",&endday);
	printf("Enter end month: ");
	scanf("%d",&endmonth);
	puts(" ");
	
	
	switch(strmonth){
		
		case 1:
			start= strday;
		break;
		case 2:
			start= 31+strday;
		break;
		case 3:
			start= 59+strday;
		break;
		case 4:
			start= 90+strday;
		break;
		case 5:
			start= 120+strday;
		break;
		case 6:
			start= 151+strday;
		break;
		case 7:
			start= 181+strday;
		break;
		case 8:
			start= 212+strday;
		break;
		case 9:
			start= 243+strday;
		break;
		case 10:
			start= 273+strday;
		break;
		case 11:
			start= 304+strday;
		break;
		case 12:
			start= 334+strday;
		break;	
	}
	
	switch(endmonth){
		
		case 1:
			end= endday;
		break;
		case 2:
			end= 31+endday;
		break;
		case 3:
			end= 59+endday;
		break;
		case 4:
			end= 90+endday;
		break;
		case 5:
			end= 120+endday;
		break;
		case 6:
			end= 151+endday;
		break;
		case 7:
			end= 181+endday;
		break;
		case 8:
			end= 212+endday;
		break;
		case 9:
			end= 243+endday;
		break;
		case 10:
			end= 273+endday;
		break;
		case 11:
			end= 304+endday;
		break;
		case 12:
			end= 334+endday;
		break;	
	}
	
	printf("Total Days: %d",end-start);
	
	
	return(0);
}
*/
