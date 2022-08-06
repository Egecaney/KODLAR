#include<stdio.h>
#include<math.h>

// Experiment3_Session3_Q1
double computeTotalCharge(double KHU);

int main(){
	
	double number;
	int costnumber;
	double total;
	
	while(1){
		
	printf("Please, enter customerNo: ");
	scanf("%d",&costnumber);
	
	if(costnumber==0){
		break;
	}
	
	if(costnumber>0){
	printf("Please, enter Kilowatt-Hour Used (KHU): ");
	scanf("%lf",&number);
	}	
	total = computeTotalCharge(number);
	printf("The customerNo: %d --- The Kilowatt-Hour Used (KHU): %lf --- The total charge: %lf \n",costnumber,number,total);
    total = 0;
    puts("");
	}
	return(0);
}
double computeTotalCharge(double KHU){
	
	double total=0;
	
	if(KHU > 300) {
      total += 300 * 9;
      KHU -= 300;
    }
	else{
      total += KHU * 9;
      KHU = 0;
    }
    
    if(KHU > 300) {   
      total += 300 * 8;
      KHU -= 300;
    }
	else {
      total += KHU * 8;
      KHU = 0;
    }
    
    if(KHU > 400) {   
      total += 400 * 6;
      KHU -= 400;
    }
	else {
      total += KHU * 6;
      KHU = 0;
    }
    
    if(KHU > 1000) {
      total += KHU * 5;
    }
         
    return total;
}
//

/* Experiment3_Session3_Q2
int main(){
	
	int number[20];
	int numberint;
	double numberdouble;
	int i;
	int k;
	int rootplace=0;
	int roots[20];
	puts("Welcome to square number puzzle solver");
	
	for(i=0;i<20;i++){
		
		printf("Please, enter the next number:" );
		scanf("%d",&number[i]);
		if(number[i]==0){
			break;
		}
		numberint = sqrt(number[i]);
		numberdouble = sqrt(number[i]); 
		
		if(numberint==numberdouble){
			roots[rootplace] = number[i];
			rootplace++;
		}
    }
    if(rootplace>0){
        printf("Here the answers: ");
	    for(i=0;i<rootplace;i++){
		printf(" %d ",roots[i]);
	}	
	}
	else{
		printf("No answers found.");
	}
	
	return(0);
}
*/
