#include<stdio.h>
#include<math.h>
#define tam 150

/*
int main(){
	
	int n;
	int counter;
	double x;
	double number=0;
	double total;
	char ok;
	char enter;

	do{
		
	printf("Enter the positive number:");
	scanf("%d",&n);
	
	printf("Enter the reel number:");
	scanf("%lf",&x);
	scanf("%c",&enter);                                  // Enter tuþunu da veri olarak alýyor //
	
	for(counter=1;counter<=n;counter++){
		
		total = (2*counter-1)/pow(x,2*counter);
		number = number+total;
		
	}
	printf("Series: %.2lf",number);
	number=0;
	
	printf("\nWill you continue? ");
	scanf("%c",&ok);
	
	}while((ok =='Y') || (ok =='y'));
	
	return(0);
}
*/

/*EN YAKIN DEÐER BULMA
int main(){
	
    int no;
    int boy;
    int minboy;
    int minno;
    int fark;
    
    printf("Student number:");
    	scanf("%d",&no);
    	
    	printf("Student Height:");
    	scanf("%d",&boy);
    
    fark= abs(boy-tam);
    
    while(1){
    	
    	printf("Student number:");
    	scanf("%d",&no);
    	
    	printf("Student Height:");
    	scanf("%d",&boy);
    	
    	if(no<0||boy<0){
    		break;
		}
		
		else if(abs(boy-tam)<fark){
			fark = abs(boy-tam);
			minboy= boy;
			minno = no;
		}
	}
    
    printf("\n%d numarali ogrenci %dcm. Boyuyla %dcm ye en yakýndýr.",minno,minboy,tam);
    
	return(0);
}
*/

/* BASAMAK ÇARPMAK
int main(){
	
    int number;
    int cross=1;
    int i=1;
    
    printf("Enter the positive number:");
    scanf("%d",&number);
    
   do{
   	
   	while(number>0){
   		cross *= (number%10);
   		number /=10 ;
	   }
   	
   	printf("%d. Number: %d\n",i++,cross);
   	number = cross;
   	cross = 1;
   	
   }while(number>9);
    
	return(0);
}
*/

/* BASAMAK BULMA
int main(){
	
    int number;
    int digit = 0;
    int i=1;
    
    printf("Enter the positive number:");
    scanf("%d",&number);
    
   while(1){
   	
   		digit = (number%10);
   		printf("%d. Digit: %d\n",i++,digit);
   		number /=10 ;
   		
   		 if(number<1){
   		 	break;
			}
	   }
	   printf("This number has %d digit number.",i-1);
	return(0);
}
*/

/* BOÞLUKLU EÞKENAR DÖRTGEN YAPMA
int main(){
	
	int k;
	int i;
	
	for(i=1;i<5;i++){
		
		for(k=4;k>i;k--){
			
			printf(" ");
		}
		for(k=1;k<=i;k++){
			
			printf("* ");
		}
		printf("\n");
	}
	for(i=4;i>0;i--){
		
		for(k=5;k>i;k--){
			
			printf(" ");
		}
		for(k=1;k<i;k++){
			
			printf("* ");
		}
		printf("\n");
	}
	return(0);
}
*/

// EÞKENAR DÖRTGEN
int main(){
	
	char op;
	int kenar;
	int satir;
	int i;
	
	printf("Enter the characteristic:");
	scanf("%c",&op);
	
	printf("Enter the lenght of side:");
	scanf("%d",&kenar);
	
	for(satir=1;satir<=kenar;satir++){
		
		for(i=1;i<=kenar-satir;i++)
		printf(" ");
		
		for(i=1;i<=2*satir-1;i++)
		printf("%c",op);
		
		printf("\n");
	}
	
	for(satir=kenar-1;satir>0;satir--){
		
		for(i=0;i<kenar-satir;i++)
		printf(" ");
		
		for(i=1;i<=2*satir-1;i++)
		printf("%c",op);
		
		printf("\n");
	}
	
	return(0);
}
//

/* Sayýlarla Kare Yapma
int main(){
	
	int number;
	int i;
	int k;
	
	printf("Enter the number:");
	scanf("%d",&number);
	
	for(i=1;i<=number;i++){
		
		for(k=i;k<number+i;k++)
		printf(" %d ",number*k);
		
		printf("\n");
	}

	return(0);
}
*/

/* Faktöriyel
int main(){
	
	int number;
	int total=1;
	int i;
	
	printf("Enter the number:");
	scanf("%d",&number);
	
	for(i=1;i<=number;i++){
		
		if(number==0)
			total=1;
			
		else
		   total = total*i;  
	
	}
	
   printf("%d! = %d",number,total);
   
	return(0);
}
*/

/* Geçme Problemi
int main(){
	
	double bird = 2272;
	double rabbit = 1042;
	int year=0;
	
	
	do{
		
		rabbit = rabbit*103.8/100;
		bird = bird*101.2/100;
		year++;
		
		printf("%d. Year Rabbit:%d            Bird:%d\n",year,int(rabbit),int(bird));
		
	}while(bird>=rabbit);
	
	printf("Year:%d",year);
	return(0);
}
*/

/* Büyük ve Küçük Harf Bulma
int main(){
	
	char name;
	int big=0;
	int small=0;
	
	puts("Enter a word.(Finish the word with dot)");
	
	do{
		scanf("%c",&name);
		
		if(name>='A'&&name<='Z')
		big++;
		
		if(name>='a'&&name<='z')
		small++;
		
	}while(name!='.');
	
	printf("Big Letter: %d , Small Letter: %d",big,small);
	
	return(0);
}
*/

/* PÝSAGOR
int main(){
	
	int n;
	int a;
	int b;
	int c;
	
	printf("Enter a positive number:");
	scanf("%d",&n);
	puts("   A    B    C ");
	
	for(a=1;a<=n;a++){
		for(b=1;b<=n;b++){
			for(c=1;c<=n;c++){
			if(pow(a,2)+pow(b,2)==pow(c,2)){
				printf("   %d    %d    %d\n",a,b,c);
			}
			
		}
		}
	
	}
	return(0);
}
*/

/* BÝLYE SAYISI
int main(){
	
	int bilye;
	for(bilye=1;bilye<1000;bilye++){
		if(bilye%2==1 && bilye%3==1 && bilye%4==1 && bilye%5==1 && bilye%6==1 && bilye%7==0){
			printf("%d",bilye);
		    break;
		}
		
	}
	return(0);
}
*/


