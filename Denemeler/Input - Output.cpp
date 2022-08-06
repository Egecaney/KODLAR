#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int main(){
	
printf("----PART1(Decimal)----\n");
	printf("%d\n",455);    // Signed decimal integer
	printf("%i\n",455);    // Signed decimal integer
	printf("%d\n",+455);   
	printf("%d\n",-455);
	
	printf("%hd\n",32000U);              // U-F-L-LL
	printf("%ld\n",2000000000L);         // Lenght Modifiers
	
	printf("%o\n",455);      // Unsigned octal integer
	
	printf("%u\n",455);      // Unsigned decimal integer
	printf("%u\n",-455);
	
	printf("%x\n",455);      // Unsigned hexadecimal integer
	printf("%X\n",455);        // x->Lowercase , X->Uppercase
	
printf("\n----PART2(Float)----\n");
	printf("%e\n",12.234);     //12.234 = 1.2234e+001
	printf("%e\n",+12.234);    //+12.234 = 1.2234e+001
	printf("%e\n",-12.234);    //-12.234 = -1.2234e+001
	printf("%E\n",12.234);     //12.234 = 1.2234E+001
	
	printf("%f\n",12.234);     //12.234 -> 12.234000 , Noktadan sonra 6 basamak yapana kadar 0 basar.
	
	printf("%g\n",123456.89);         //1.23457
	printf("%g\n",12345678.89);       //1.23457e+007
	printf("%G\n",1234567.89);        //1.23457E+006        , Decimal k�sm� en az 7 basamakl� olmal�, Output 6 basamak bas�yor(Noktadan sonra 5)
	
printf("\n----PART3(String)----\n");
	char ch1 = 'A';
	printf("%c\n",ch1);
	printf("%s\n","This is string.");
	char st1[] = "This is string.";
	printf("%s\n",st1);
	const char *st2 = "This is also a string.";
	printf("%s\n",st2);
	
printf("\n----PART4(Address-Value)----\n");
	int x=12345;
	int *ptr=&x;
	printf("The value of ptr is %p\n",ptr);    //Display a pointer value in an implemantation-defined manner.
	printf("The address of x is %p\n",&x);
	
printf("\n----PART5(Field Widths)----\n");
	int dec=873;
	printf("\t%.4d \n\t%.9d\n",dec,dec);     // /t say�dan �nce 8 bo�luk b�rak�r.
	
	double flo=123.456;
	printf("\t%.3lf \n\t%.4e \n\t%.4g\n",flo,flo,flo);  // lf ve e ->noktadan sonra sayar , g-> ba�tan ba�lar.
	
	char hps[]="Happy Birthday";
	printf("\t%.11s\n",hps);   // (8 Bo�luk)Happy Birth
	printf("\t%.14s\n",hps);   // (8 Bo�luk)Happy Birthday
	
printf("\n----PART6(Scanf)----\n");
    int mon,day,year;
    printf("%s","Enter a date in the form mm-dd-yyyy: ");
    //scanf("%d-%d-%d",&mon,&day,&year);            // Sadece - kabul eder.
    scanf("%d%*c%d%*c%d", &mon, &day, &year);       // Her�ey kabul eder.
    printf("Month=%d Day=%d Year=%d\n",mon,day,year);
	
return(0);	
}


