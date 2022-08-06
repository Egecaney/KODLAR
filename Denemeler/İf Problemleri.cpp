#include<stdio.h>
#include<math.h>
/*
int main(){
	
	int number;
	
	printf("Enter a number: ");
	scanf("%d",&number);
	
	if(number%13 == 0 && number%17 != 0)
		printf("It can divided by 13");
		
	else if(number%13 != 0 && number%17 == 0)
		printf("It can divided by 17");

	else if(number%13 == 0 && number%17 == 0)
		printf("It can divided into both 13 and 17");
		
	else if(number%13 != 0 && number%17 != 0)
		printf("It cannot divided into both 13 and 17");
		
	return(0);
	
}
*/
/*
int main(){
	
	char kod;
	double mkare;
	double para;
	
	printf("Hali Tipi(T/B/S) :");
	scanf("%c",&kod);
	
	printf("Metrekare: ");
	scanf("%lf",&mkare);
	
	if(kod =='T' && mkare>= 10){
		para=mkare*18.80;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(kod =='B' && mkare>= 10){
		para=mkare*17.80;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(kod =='S' && mkare>= 10){
		para=mkare*19.20;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(mkare < 10 || kod != 'T'|| kod != 'B'|| kod != 'S'){
		printf("Uza!");
	}
	
	return(0);
}
*/

/*
int main(){
	
	char kod;
	int dos;
	double mkare;
	double para;
	
	printf("Hali Tipi(T/B/S) :");
	scanf("%c",&kod);
	
	printf("Metrekare: ");
	scanf("%lf",&mkare);
	
	if(kod =='T' && mkare>= 10){
		para=mkare*18.80;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(kod =='B' && mkare>= 10){
		para=mkare*17.80;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(kod =='S' && mkare>= 10){
		para=mkare*19.20;
		printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(mkare < 10 || kod != 'T'|| kod != 'B'|| kod != 'S'){
		printf("Uza!");
	}
	
	printf("\nDoseme(Evet=1/Hayir=0): ");
	scanf("%d",&dos);
	
	if(dos == 1 && mkare>=10){
		
		if(mkare>=10 && mkare<25)
		para = para + 35;
		else if(mkare>=25 && mkare<100)
		para = para + 60;
		else if(mkare>=100)
		para = para + 75;
	
	printf("Odenmesi gereken ucret: %lf ",para);
	}
	else if(dos == 0)
	printf("Odenmesi gereken yeni ucret: %lf ",para);
	
	return(0);
}
*/

/* ÜÇGEN TÜRÜ BULMA
int main(){
	
	double angle1;
	double angle2;
	double angle3;
	
	puts("Enter the all angles");
	scanf("%lf",&angle1);
	scanf("%lf",&angle2);
	scanf("%lf",&angle3);
	
	if(angle1+angle2+angle3==180 && angle1!=0 && angle2!=0 && angle3!=0 ){
		
		if(angle1==90||angle2==90||angle3==90){
			puts("This is right-angled triangular.");
			if(angle1==angle2||angle1==angle3||angle2==angle3)
			puts("This is isosceles triangular.");
			else if(angle1!=angle2&&angle1!=angle3&&angle2!=angle3)
			puts("This is scalene triangular.");
		}
		else if(angle1>90||angle2>90||angle3>90){
			puts("This is obtuse-angled triangular.");
			if(angle1==angle2||angle1==angle3||angle2==angle3)
			puts("This is isosceles triangular.");
			else if(angle1!=angle2&&angle1!=angle3&&angle2!=angle3)
			puts("This is scalene triangular.");
		}
		else if(angle1<90||angle2<90||angle3<90){
			puts("This is acute-angled triangular.");
			if(angle1==60&&angle2==60&&angle3==60)
			puts("This is equilateral triangular.");
			else if(angle1==angle2||angle1==angle3||angle2==angle3)
			puts("This is isosceles triangular.");
			else if(angle1!=angle2&&angle1!=angle3&&angle2!=angle3)
			puts("This is scalene triangular.");
		}
	}
	else
	puts("This is not triangular.");
	
	return(0);
}
*/

// ARALIK TEKRARI
int main(){
	
	double number;
	int i=0;
	
	printf("Enter a number:");
	scanf("%lf",&number);
	
	puts("Go on when it is not in the interval ");
	while(i==0){
		
		if(number>=10 && number<20){
			puts("This is in first interval.");
			printf("Enter a number:");
	        scanf("%lf",&number);
		}
		else if(number>=20 && number<30){
			puts("This is in second interval.");
			printf("Enter a number:");
	        scanf("%lf",&number);
		}
		
		else{
			puts("This is not in the interval.");
			i=1;
		}
		
	}
	
	return(0);
}




