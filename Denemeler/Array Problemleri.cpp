#include<stdio.h>
#include<math.h>

/* HARF BULMA
int main(){
	
	char name[100];
	int i;
	int k=0;
	int e=0;
	int m=0;
	int size=0;
	
	printf("Enter your name and surname:");
	for(i=0;i<100;i++){
		
	    scanf("%c",&name[i]);
	    
	    if(name[i]=='.'){
			break;	
		}
		 size++;	
	}
	for(i=0;i<size;i++){
		
		if(name[i]>='A'&&name[i]<='Z')
		k++;
		if(name[i]=='E')
		e++;
		if(name[i]=='M')
		m++;
	}
	for(i=0;i<size;i++){
		printf("%c",name[i]);
	}
	
	printf("\nYour name has %d letter, has %d E letter and has %d M letter ",k,e,m);
	return(0);
}
*/

/* Sayýlarý Büyükten Küçüðe Doðru Sýralama 
int main()
{
 int sayilar[5];
 int sayac = 0;
 int buyuk = 0; 
 int kucuk = 0;
 int temp = 0;
 
 
 printf("5 Sayi giriniz\n");
 for(sayac=0;sayac<5;sayac++)
 {
  printf("%d. Sayi : ",sayac+1);
  scanf("%d",&sayilar[sayac]);
 }
 
 printf("\nSiralama Oncesi");
 for(sayac=0;sayac<5;sayac++)
 {
  printf("\n%d",sayilar[sayac]);
 }
 
 for(buyuk=0;buyuk<4;buyuk++)
 {
  for(kucuk=buyuk+1;kucuk<5;kucuk++)
  {
   if(sayilar[buyuk]>sayilar[kucuk])
   {
    temp = sayilar[buyuk];
    sayilar[buyuk] = sayilar[kucuk];
    sayilar[kucuk] = temp;
   }
  }
 }
 
 printf("\nSiralama Sonrasi");
 for(sayac=4;sayac>=0;sayac--)
 {
  printf("\n%d",sayilar[sayac]);
 }
 
 return(0);
}
*/

/* Binary Çevirme
int main(){
	
	int number;
	int number2;
	int i;
	int b[10];
	int k=0;
	
	
	printf("Bir sayi giriniz : ");
	scanf("%d",&number);
	
	number2=number;

	for(i=10;i>0;i--){
		
		b[i] = number%2;
		number = number/2;
		k++;
		if(number==1){
			b[i-1]=1;
			break;
		}
		
	}
	printf("(%d)D is equal to Binary :",number2);
	for(i=10-k;i<11;i++){
		printf("%d",b[i]);
	}
	return 0;
}
*/

/* Armstrong Number
int main(){
	
	int number;
	int i=0;
	int temp;
	int temp2=0;
    int digit[4];
    int t=0;
	
	
	
	printf("Enter a number: ");
	scanf("%d",&number);
	
	temp=number;
	
	while(number>=1){
		
		digit[i]=number%10;
		number = number/10;
		i++;
	}	
	for(t=0;t<i;t++){
		
		temp2 += pow(digit[t],i);
		
	}
	    if(temp==temp2)
	    puts("This is Armstrong number.");
	
	return(0);
}
*/

/* Sayý kadar yýldýz yapma 
int main(){
	
    int num[13] = {7,3,5,6,1,2,3,3,3,4,5,5,9};
    int freq[10]={0};
    int i;
    int j;
    
    for(i=0;i<13;i++){
    	freq[num[i]-1]++;
	}
    for(i=0;i<10;i++){
    	printf("The frequency of the number %d:",i+1);
    	for(j=0;j<freq[i];j++){
    		printf("*");
		}
		puts(" ");
	}

	return(0);
}
*/

/* Sayýdan kaç tane var bulma
int arryserach(int numbers[], int size, int target);

int main (){
    int numbers[13] = {1,3,5,6,1,2,3,3,3,4,5,5,7};
    int target;
    printf("Please enter the target number\n");
    scanf("%d", &target);
    int result = arryserach(numbers,13, target);
     printf("The target number %d is occurs in the array %d times\n", target,result);
}

int arryserach(int numbers[], int size, int target){
      int frequency = 0;
	  	int i;
		  for (i=0;i<size;i++){
	  		if(target == numbers[i]){
	  			frequency++;
			  }
		  }
return frequency;
}
*/

/* 5 Sayý Tekrar
int main(){
	
	int userinput;
	int i;
	int k=1;
	int number[9];
	
	printf("Please, enter the number(1-9), enter -1 to stop\n");
	scanf("%d",&userinput);
	
	while(userinput!=-1){
		
		k=1;
		if(userinput<=4){
		number[0]=5+userinput;
	   }
	   else if(userinput>=5){
		number[0]=userinput-4;
	   }
		
		for(i=0;i<5;i++){
			number[i+1]=number[i]+1;
			if(number[i+1]>=10){
				number[i+1]=k;
				k++;
			}
		}
		
		for(i=0;i<5;i++){
	    printf("%d ",number[i]);
		}
		
		puts("");
	    printf("Please, enter the next number(1-9), enter -1 to stop\n");
	    scanf("%d",&userinput);
	}
	   	
	return(0);
}
*/

/* Reverse Input
int main(){
	
	int size;
	int i;
	printf("The lenght of input array: ");
	scanf("%d",&size);
	puts("************     ************");
	
	int number1[size];
	int number2[size];
	for(i=0;i<size;i++){
		printf("Please, enter the value %d: ",i+1);
		scanf("%d",&number1[i]);
	}
	
	for(i=0;i<size;i++){
		number2[size-1-i]=number1[i];
	}
	puts("The input array --- The output array");
	for(i=0;i<size;i++){
	printf("      %d                   %d\n",number1[i],number2[i]);
	}	
return(0);	
}
*/

// Büyükten ---> Küçüðe
int main(){
	
      int dizi[8],i,j,t,fark,min,max;
      
      for(i=1;i<9;i++){
            printf("%d. sayiyi giriniz: ",i);
            scanf("%d",&dizi[i]);
      }
      
      for(i=1;i<9;i++){
            for(j=1;j<9;j++){
                  if(dizi[j]<=dizi[i]){  // < ise Büyükten ---> Küçüðe , > ise Küçükten --->  Büyüðe
                        t=dizi[i];  
                        dizi[i]=dizi[j];
                        dizi[j]=t;
                        }
                  }
            }
      
      printf("\nsiralama: ");
      
      for(i = 1;i < 9; i++){
            printf("%d ",dizi[i]);
      }
      
      return(0);
}
//

/* Matrixteki Tek Sayýlarla Array Yapma
int main(){
	
	int i;
	int j;
	int nofodd=0;
	int size;
	printf("Enter a size of matrix: ");
	scanf("%d",&size);
	
	int number[size][size];
	int oddar[size*size];
	
	for(i=0;i<size;i++){
		
		printf("Enter the %d. row:  ",i+1);
		
		for(j=0;j<size;j++){
			scanf("%d",&number[i][j]);
			
			if(number[i][j]%2 == 1){
				oddar[nofodd]=number[i][j];
				nofodd++;
			}
		}
	}
	printf("New array: ");
	for(i=0;i<nofodd;i++){
		printf ("%d ",oddar[i]);
	}
	return(0);
}
*/

/* Matrix BÜYÜK-KÜÇÜK
int funct(int number[][10],int input[],int size,int integer);
int main(){
	
	int number[2][10] ;
	int size;
	int i;
	int j;
	int integer;
	
	printf("Enter the size of array(<=10): ");
	scanf("%d",&size);
	int input[size];
	
	printf("Enter the values of array: ");
	for(i=0;i<size;i++){
		scanf("%d",&input[i]);
	}
	
	printf("Enter a integer: ");
	scanf("%d",&integer);
	
	funct(number,input,size,integer);
	printf("Output Array: \n");
	for(i=0;i<2;i++){
		for(j=0;j<10;j++){
			printf("%2d ",number[i][j]);
		}
		puts("");
	}
	return(0);
}
int funct(int number[][10],int input[],int size,int integer){
	
	int i;
	int j;
	int b=0;
	int s=0;
	for(i=0;i<10;i++){
		number[0][i] = 0;
		number[1][i] = 0;
	}
	for(i=0;i<size;i++){
		if(input[i]>= integer){
			number[0][b] = input[i];
			b++;
		}
		else{
			number[1][s] = input[i];
			s++;
		}
	}
}
*/
