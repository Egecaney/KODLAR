#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX_SIZE 1000 

/* Average Bulmak
int main(){
	
	double t=0;
	int grade;
	int counter=0;
	double average;
	
	printf("%d.grade is: ",counter+1);
	scanf("%d",&grade);
	
	while(grade != -1){
		counter = counter+1;
		t = t+grade;
		printf("Total: %lf\n",t);
		
		printf("%d.grade is: ",counter+1);
		scanf("%d",&grade);
		
	}
	
	average = t/counter;
	printf("Average is %lf",average);
	
	return(0);
}
*/

/* Max ve Min Bulmak
int main(){
	
	int number;
	int max;
	int min;
	int counter=1;
	int i;
	
	printf("Enter the i: ");
	scanf("%d",&i);
	
	while(counter<=i){
		printf("Enter the number:");
		scanf("%d",&number);
		if(counter == 1){
			min= number;
			max= number;
		}
		else{
			if(min>number)
			min= number;
			if(max<number)
			max= number;
		}
		
		
		counter++;
	}
	
	printf("Min: %d \nMax : %d",min,max);
	
	return(0);
}
*/

/* Max1 ve Max2 Bulmak
int main(){
	
	int max1=0;
	int max2=0;
	int number;
	int N;
	int sum;
	int counter=0;
	
	printf("How many numbers will you enter?");
	scanf("%d",&N);
	
	while(counter<N){
		printf("Please Enter a Number: ");
		scanf("%d",&number);
		if  (number>max1)
        {
            max2=max1;
            max1=number;
        }
        else if (number>max2)
            max2=number;
		
		counter++;
	}
	 sum = max1+ max2;
	 printf("The sum of largest two numbers: %d",sum);
	
	return(0);
}
*/

/* ARRAY KULLANARAK BULMAK
int main()
{
    int arr[MAX_SIZE];
	int size;
	int i;
    int max1=0 , max2=0 , max3=0;
    int k , p;

    printf("Enter size of the array (1-1000): ");
    scanf("%d", &size);

    
    for(i=0; i<size; i++)
    {
    	printf("Enter %d. Number: ",i+1);
        scanf("%d", &arr[i]);
    }

    for(i=0; i<size; i++)
    {
        if(arr[i] > max1)
        {
            max3 = max2;
			max2 = max1;
            max1 = arr[i];
        }
        else if(arr[i] > max2 && arr[i] < max1)
        {
            max3 = max2;
			max2 = arr[i]; 
        }
        else if(arr[i] > max3 && arr[i] < max2)
        {
			max3 = arr[i]; 
        }
    }
    
    printf("\nFirst Maximum: %d\n", max1);
    printf("\nSecond Maximum: %d\n", max2);
    printf("\nThird Maximum: %d\n", max3);

    return 0;
}
*/

// Ýyi ve Kötü Film 
int main()
{
	double f[5];
	double max=0;
	double min=0;
	double count;
	int i;
	
	puts("How many people watched 'Nice Time'?");
	scanf("%lf",&f[0]);
	puts("How many people watched 'Emine Holmes'?");
	scanf("%lf",&f[1]);
	puts("How many people watched 'The Return of the Zoom'?");
	scanf("%lf",&f[2]);
	puts("How many people watched '21st Century Cats'?");
	scanf("%lf",&f[3]);
	puts("How many people watched 'The Turkishman'?");
	scanf("%lf",&f[4]);
	
	count = f[0]+f[1]+f[2]+f[3]+f[4];
	
	printf("Nice Time : %lf%",f[0]*100/count);
	printf("\nEmine Holmes : %lf%",f[1]*100/count);
	printf("\nThe Return of the Zoom': %lf%",f[2]*100/count);
	printf("\n21st Century Cats' : %lf%",f[3]*100/count);
	printf("\nThe Turkishman : %lf%",f[4]*100/count);
	
	
	min = f[0];
    max = f[0];
    
 for(i=1; i<5; i++)
    {
        if(f[i]>max)
        {
			max = f[i];
        }
        else{
         	if(min>f[i])
         	min =  f[i];
		 }
        
    }
		puts(" ");
		
		if(max==f[0])
		printf("The best movie of this season is Nice Time with percentage %lf%",f[0]*100/count);
		else if(max==f[1])
		printf("The best movie of this season is Emine Holmes with percentage %lf%",f[1]*100/count);
		else if(max==f[2])
		printf("The best movie of this season is The Return of the Zoom with percentage %lf%",f[2]*100/count);
		else if(max==f[3])
		printf("The best movie of this season is 21st Century Cats with percentage %lf%",f[3]*100/count);
		else if(max==f[4])
		printf("The best movie of this season is The Turkishman with percentage %lf%",f[4]*100/count);
		
		puts(" ");
		
		if(min==f[0])
		printf("The worst movie of this season is Nice Time with percentage %lf%",f[0]*100/count);
		else if(min==f[1])
		printf("The worst movie of this season is Emine Holmes with percentage %lf%",f[1]*100/count);
		else if(min==f[2])
		printf("The worst movie of this season is The Return of the Zoom with percentage %lf%",f[2]*100/count);
		else if(min==f[3])
		printf("The worst movie of this season is 21st Century Cats with percentage %lf%",f[3]*100/count);
		else if(min==f[4])
		printf("The worst movie of this season is The Turkishman with percentage %lf%",f[4]*100/count);
		
	return 0;
}
