#include<stdio.h>

int main(){
	
	
	int M1,M2,F,B;
	double G,A,C;
	
	printf("Please, enter your first midterm:");
	scanf("%d",&M1);
	
	printf("Please, enter your second midterm:");
	scanf("%d",&M2);
	
	printf("Please, enter your final:");
	scanf("%d",&F);
	
	printf("Please, enter your general average:");
	scanf("%lf",&A);
	
	printf("Please, enter your AKTS:");
	scanf("%d",&B);
	
	
	G= M1*0.3+M2*0.3+F*0.4;
	printf("Your Grade is : %f \n",G);
	
	if(G>=95){
		printf("Your Letter Grade is A1");
		G=4.0;
	}
		else if (G>=90 && G<95){
			printf("Your Letter Grade is A2");
			G=3.75;
		}
		else if (G>=85&&G<90){
			printf("Your Letter Grade is A3");
			G=3.50;
		}
		else if(G>=80&&G<85){
			printf("Your Letter Grade is B1");
			G=3.25;
		}
		else if(G>=75&&G<80){
			printf("Your Letter Grade is B2");
			G=3.0;
		}
		else if(G>=70&&G<75){
			printf("Your Letter Grade is B3");
			G=2.75;
		}
		else if(G>=65&&G<70){
			printf("Your Letter Grade is C1");
			G=2.5;
			if(A<=2.50){
				printf("\nYou should take this course again!");
			}
		}
		else if(G>=60&&G<65){
			printf("Your Letter Grade is C2");
			G=2.25;
			if(A<=2.50){
				printf("\nYou should take this course again!");
			}
		}
		else if(G>=55&&G<60){
			printf("Your Letter Grade is C3");
			G=2.0;
			if(A<=2.50){
				printf("\nYou should take this course again!");
			}
		}
		else if(G>=50&&G<55){
			printf("Your Letter Grade is D");
			G=1.75;
			if(A<=2.50){
				printf("\nYou should take this course again!");
			}
		}
		else if(G<50){
			printf("Your Letter Grade is F3");
			G=0.0;
		}
		
		A = (A*B+0.75+G*7-14)/B;
		
		printf("\nYour average is : %lf",A);
		
	return(0);
}
