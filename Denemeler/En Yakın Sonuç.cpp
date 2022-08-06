#include<stdio.h>
#include<math.h>

int main(){
	
	int stnumber;
	int grade;
	int number;
	int closest;
	int i;
	int k;
	int finalid;
	int finalgrade;
	int j;
	int p;
	int t=0;
	
	printf("How many student you have:");
	scanf("%d",&number);
	
	printf("Enter the exact grade:");
	scanf("%d",&closest);
	
	printf("Enter the 1. ID and grade:");
	scanf("%d",&stnumber);
	scanf("%d",&grade);
	
	j= stnumber;
	p= grade;
	k=abs(closest-grade);
	
	for(i=1;i<number;i++){
		
	printf("Enter the %d. ID and grade:",i+1);
	scanf("%d",&stnumber);
	scanf("%d",&grade);
		
		if(k>abs(closest-grade)){
			finalid=stnumber;
			finalgrade=grade;
			k=abs(closest-finalgrade);
			t = t+1;
		}
	}
	
	if(t==0){
		finalid = j;
		finalgrade = p;
	}
	
	printf("The closest number is %d and its grade is %d",finalid,finalgrade);
	
	
	return(0);
}
