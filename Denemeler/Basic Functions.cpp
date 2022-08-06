#include<stdio.h>
#include<math.h>
/*
int fonk(int p , int s);

int main(){
	
	int popularity;
	int size;
	int p1;
	int p2;
	int u1;
	int u2;
	int home;
	
	puts("It is an exponential finding operation.(N1)^N2 ");
	printf("Popularity is: ");
	scanf("%d",&popularity);
	
	printf("Size is: ");
	scanf("%d",&size);
	
	
	p1 = fonk(popularity,3);
	p2 = fonk(size,2);
	
	home = ((p1+p2)*1000);
	printf("Home is: %d",home);
	
	return(0);
}

int fonk(int p , int s){
	
	int number1;
	int number2;
	int counter=1;
	
	number1=p;
	number2=p;
	printf("%d and %d\n",number1,number2);
	
	while(counter<s){
		
		number1 = number1*p;
		counter++;
	}
	printf("%d and %d\n",number1,number2);
	return(number1);
	}
*/

/*
int fonk(int p , int s);

int main(){
	
	int popularity;
	int size;
	int p1;
	
	puts("It is an exponential finding operation.(N1)^N2 ");
	printf("Popularity is: ");
	scanf("%d",&popularity);
	
	printf("Size is: ");
	scanf("%d",&size);
	
	
	p1 = fonk(popularity,size);
	printf("Home is: %d",p1);
	
	return(0);
}

int fonk(int p , int s){
	
	int number1;
	int number2;
	int counter=1;
	
	number1=p;
	number2=p;
	printf("%d and %d\n",number1,number2);
	
	while(counter<s){
		
		number1 = number1*p;
		counter++;
	}
	printf("%d and %d\n",number1,number2);
	return(number1);
	}
*/
	
/* RMSE DEÐERÝ BULMA
	double fonk(int x1, int x2, int y1, int y2);
int main(){
	
	int a1,a2;
	int b1,b2;
	double c;
	printf("Please write Set1 Number1: ");
	scanf("%d/n",&a1);
	
	printf("Please write Set1 Number2: ");
	scanf("%d/n",&a2);
	
	printf("Please write Set2 Number1: ");
	scanf("%d/n",&b1);
	
	printf("Please write Set2 Number2: ");
	scanf("%d/n",&b2);
	
	c = fonk(a1,a2,b1,b2);
	printf("RMSE is :%lf",c);
	return(0);
	}
	double fonk(int x1, int x2, int y1, int y2){
		double k4;
		double k1;
		k1 = pow(x1-y1,2);
		double k2;
		k2 = pow(x2-y2,2);
		double k3;
		k3 = (k1+k2)/2;
		k4 = sqrt(k3);
		return(k4);
	}
*/

/* Karakter Bulma
char find(char ch){
	
	if((ch>='A'&&ch<='Z') || (ch>='a'&&ch<='z'))
	  printf("%c is a alphabetic character.\n",ch);
	  
	else if( ch>='0' && ch<='9' )
	printf("%C is a number.\n",ch);
	
	else
	printf("%c is a special character.\n",ch);
	
}
int main(){
	
	int number;
	char character;
	char enter;
	int i;
	
	printf("Enter a positive number:");
	scanf("%d",&number);
	
	for(i=1;i<=number;i++){
		
		scanf("%c",&enter);
		printf("Enter a character:");
		scanf("%c",&character);
		
		find(character);
		
	}
	return(0);
}
*/

/* Ýki Fonksiyonla Birim Çevirme
double findclc(double fah){
	double clc;
	clc = (5*(fah-32))/9;
	printf("Celcius Degree: %lf",clc);
}

double findfah(double clc1){
	double fah1;
	fah1 = (9*clc1+160)/5;
	printf("Fahrenheit Degree: %lf",fah1);
}
int main(){
	
	char op;
	double degree;
	
	puts("Fahrenheit(F/f) --- Celcius(C/c) ");
	
	printf("Enter your choice:");
	scanf("%c",&op);
	
	if(op=='F'||op=='f'){
		printf("Enter the celcius degree:");
		scanf("%lf",&degree);
		findfah(degree);
	}
	
	else if(op=='C'||op=='c'){
		printf("Enter the fahrenheit degree:");
		scanf("%lf",&degree);
		findclc(degree);
	}
	return(0);
}
*/

/* Tek Fonksiyonla Birim Çevirme
char find(char op){
	
	double fah;
	double clc;
	if(op=='F'||op=='f'){
		printf("Enter the celcius degree:");
		scanf("%lf",&clc);
		fah=(9*clc+160)/5;
		printf("Fahrenheit Degree: %lf",fah);
		
	}
	
	else if(op=='C'||op=='c'){
		printf("Enter the fahrenheit degree:");
		scanf("%lf",&fah);
		clc=(5*(fah-32))/9;
		printf("Celcius Degree: %lf",clc);
	}

}
int main(){
	
	char op;
	double degree;
	
	puts("Fahrenheit(F/f) --- Celcius(C/c) ");
	
	printf("Enter your choice:");
	scanf("%c",&op);
	find(op);
	
	if(op!='F' && op!='f' && op!='c' && op!='C')
	puts("Wrong character.");
	
	return(0);
}
*/

/* Basamak Sayýsý
int basamak(int bas){
	
	int k=1;
	while(1){
	
	
	if(bas>9)
		k++;
	else
	    break;
	    
	    bas=bas/10;
	}
	return(k);
}

int main(){
	
	int number;
	int i;
	int ba;
	
	printf("Enter a positive number:");
	scanf("%d",&number);
	
	while(number>0){
		
	ba = basamak(number);
	printf("Number of digits: %d\n",ba);
	
		printf("Enter a positive number:");
		scanf("%d",&number);
	}
	
	return(0);
}
*/

/* Basamak Ekleme
double basamak(double bas){
	
	int k=1;
	while(1){
	
	
	if(bas>10)
		k++;
	else
	    break;
	    
	    bas=bas/10;
	}
	return(k);
}

int main(){
	
	double number1;
	double number2;
	double temp;
	double reel;
	double ba2;
	
	printf("Enter two positive number:");
	scanf("%lf",&number1);
	scanf("%lf",&number2);
	
	while(number1>=0&&number2>=0){
		
	ba2 = basamak(number2);
	
	reel = number1+(number2/pow(10,ba2));
	printf("Reel Number: %lf\n",reel);
	
	printf("Enter two positive number:");
	scanf("%lf",&number1);
	scanf("%lf",&number2);
	}
	
	return(0);
}
*/

// Faktörüyel Serisi (1!/1 + 2!/2 + ...)
int series(int n1);
int main(){
	
	int number;
	int k;
	int p;
	int total=0;
	
	printf("Enter a positive number:");
	scanf("%d",&number);
	
	for(p=number;p>0;p--){
		
		k= series(p);
		total +=k;
	}
	
	
	printf("Series: %d",total);
	
	return(0);
}
int series(int n1){
	
	int i;
	int cross=1;
	
	for(i=n1;i>0;i--){
		
		cross= cross*i;
	}
	
	cross=cross/n1;
	
	return(cross);
}

