#include<stdio.h>
#include<math.h>

/* SWÝTCH-CASE 
int main(){
	
	int number1;
	int number2;
	char op;
	
	printf("Enter the operation(+-):");
	scanf("%c",&op);
	
	printf("Enter the Number1:");
	scanf("%d",&number1);
	
	printf("Enter the Number2:");
	scanf("%d",&number2);
	
	if(number1 ==0 || number2==0){
		printf("The denominator cannot be 0.");
	}
	else{
		switch(op){
			
		case '+':
		printf("Result is %d/%d",number1+number2,number1*number2);
		break;
		case '-' :
		printf("Result is %d/%d",number2-number1,number1*number2);
		break;
		default :
		printf("Wrong Operation.");
	}
	}
	return(0);
}
*/

/* Fibonacci Sayýlarý
int main(){
	
	int temp;
	int number1;
	int number2;
	int i;
	
	number1=0;
	number2=1;
	
	for(i=0;i<10;i++){
		
		temp = number2;
		number2 += number1;
		printf(" %d ",number1);
		number1 = temp;
	}
	return(0);
	
}
*/

/* TAM BÖLEN SAYILAR
int main(){
	
	int number;
	int i;
	int k=0;
	
    printf("Enter a Number:");
    scanf("%d",&number);
    
    for(i=number-1;i>=2;i--){
    	if(number%i == 0){
    		printf("%d \n",i);
    		k++;
		}
	}
	if(k==0){
	printf("This is a prime number.");
	}
	else
    printf("Divisor numbers: %d",k);
	return(0);
	
}
*/

/*ARALIKTA ASAL SAYI BULMA PROGRAMI 
int checkPrimeNumber(int n);
int main()
{
    int number1, number2;
	int i;
	int flag;

    printf("Enter two positive number:(N1<N2)\n");
    scanf("%d %d",&number1,&number2);
    printf("%d ve %d arasindaki asal sayilar: ",number1,number2);

    for(i=number1;i<number2;i++)
    {
        flag = checkPrimeNumber(i);
        if(flag == 1 && i !=0 && i!=1)
            printf("%d ",i);
    }
    return 0;
}

int checkPrimeNumber(int n)
{
    int j;
	int flag = 1;

    for(j=2;j<=n/2;++j)
    {
        if (n%j == 0)
        {
            flag =0;
            break;
        }
    }
    return flag;
}
*/

/* GPA Hesaplama
int main(){
	
	int credit;
	char letter;
	char cont;
	char enter;
	int total1=0;
	int total2=0;
	int i=1;
	
	do{
		
		printf("Lesson %d\n",i);
		i++;
		
		printf("Enter the credit of lesson:");
		scanf("%d",&credit);
		total2 += credit;
		
		scanf("%c",&enter);
		printf("Enter the your letter grade:");
		scanf("%c",&letter);
		
		switch(letter){
		
			case 'A':
			total1 += 4*credit;
			break;
			
			case 'B':
			total1 += 3*credit;
			break;
			
			case 'C':
			total1 += 2*credit;
			break;
			
			case 'D':
			total1 += 1*credit;
			break;
			
			case 'F':
			total1 += 0*credit;
			break;
		}
		
		scanf("%c",&enter);
		printf("Do you continue(Y):");
		scanf("%c",&cont);
	}while(cont =='Y');
	
	printf("Total Not: %d\n",total1);
	printf("Total Credit: %d\n",total2);
	printf("GPA: %.2lf\n",(double)total1/total2);
	
	return(0);
}
*/

/* Uzun Yoldan Asal Çarpan ve Asal Kontrol 
int asalsorgu(int as){
	
	int i;
	int k=0;
	int t;
	
	if(as>0){
		for(i=as-1;i>1;i--){
			if(as%i==0){
				k++;
			}
		}
		if(k!=0){
			printf("%d is not prime number.",as);
		    t=0;
		}
		    
		else{
			printf("%d is a prime number.",as);
			t=1;
		}
	}
	else{
		puts("This is not positive number.");
	}
	
	return(t);
}

int asalbulma(int asal){
	
	int j;
	int p;
	int prime=0;
	
	for(j=2;j<=asal;j++)
    {
        if(asal%j==0)
        {
            prime = 1;
            
            for(p=2;p<=j/2;p++)
            {
                if(j%p==0)
                {
                    prime = 0;
                    break;
                }
            }

            if(prime==1)
            {
                printf(" %d ", j);
            }
        }
    }
	
}
int main(){
	
	int number;
	int p;
	int sorgu;
	int flag;
	
	printf("Enter a positive number:");
	scanf("%d",&number);
	
	sorgu = asalsorgu(number);
	
	if(sorgu==0){
		
		printf("\nPrime Factors:");
		asalbulma(number);
		
	}
	
	return(0);
}
*/

//Kýsa Yoldan Asal Çarpan ve Asal Kontrol
int asal(int);
int asalbul(int , int);

int main(){
	
	int number;
	int i;
	
	printf("Enter a positive number:");
	scanf("%d",&number);
	printf("Prime Factors of Number %d:",number);
	
	for(i=2;number>0;++i){
		
		if(asal(i)==1 && asalbul(number,i)==1){
			printf(" %d ",i);
			number = number/i;
			--i;
		}
	}
	
	return(0);
}

int asal(int sayi){
	
	int i;
	for(i=sayi-1;i>1;--i){
		
		if(sayi%i==0){
			return(0);
		}
	}
	return(1);
}

int asalbul(int sayi,int i){
	
	if(sayi%i==0)
	return(1);
	
	else
	return(0);
	
}

/*
int main(){
	
	return(0);
}
*/
