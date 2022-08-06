#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
int main(){
	
	char a[]="EGEMEN";;
	int number=1;
	int i=0;
	
	for(i=0;i<sizeof(a)-1;i++){
		printf("\nYour %d.letter is: %c",i+1,a[i]);
	}
	
	return(0);
}
*/
/*
int main(){
	
	int i;
	int j;
	
	i=4;
	
	while(i>=1){
		j=1;
		while(j<=3){
			printf("%3d",j);
			j++;
		}
		printf("\n%3d\n",i);
		i--;
	}
	
	return(0);
}
*/


int main(){
	
	int i;
	int j;
	int temp;
	
	
	for(i=4;i>=-7;i--){
		
		if(i%4==0)
			temp=i;
		
		for(j=1;j<=3;j++){
			printf("  %d",j);
		}
		printf("\n%3d\n",temp);
	}
	return(0);
}


/* Random Variable
int main(){
	
	unsigned int i;
	
	for(i=1;i<=20;++i){
		
		printf("%10d",1+(rand()%7));
		
		printf(" %d ",i%5);
		puts(" X");
		
		if(i%5==0){
			puts("");
		}
	}
	
	return(0);
}
*/
