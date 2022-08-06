#include<stdio.h>
#include<math.h>
#define pi 3.14


/*Temel1
int main (){
	
	int i=5;
	int *p = &i;
	
	printf("Address: %u\n",p);  // & deðiþkenin adres bilgilerini veriyor.
	printf("Value  : %d",*p);   // * adresdeki deðeri verir.
	
	return 0;

}
*/

/* Temel2
int main(){
	
	int i,j=1;         // i nin deðeri belli deðil ama j nin deðeri 1.
	int *jp1,*jp2= &j; // jp2 ye j nin baþlangýç adresini atmýþ.
	
	jp1 = jp2;         // jp1 de jp2 gibi jnin baþlangýç adresine gidiyor.
	
	i = ++(*jp2);      // jp2 1 idi , i 2 oldu. ve j nin deðer de 2 oldu.
	
	*jp2=*jp1+i;       // jp2 4 oldu , jp2 jp1 ve j ayný deðeri göstereceði için 4 oluyorlar.
	
	printf("i=%d j=%d *jp1=%d *jp2=%d \n",i,j,*jp1,*jp2);
	printf("i=%u j=%u *jp1=%u *jp2=%u",i,j,jp1,jp2);
	

	return 0;
}
*/

/* Alan-Çevre Fonksiyonsuz
int main(){
	
	int x1;
	int x2;
	int *ed1=&x1;
	int *ed2=&x2;
	
	printf("Enter two values separeted by space: ");
	scanf("%d",&x1);
	scanf("%d",&x2);
	
	printf("Area: %d   ---  Perimeter: %d",(*ed1)*(*ed2),(2*((*ed1)+(*ed2))));
	return(0);
}

/*Alan-Çevre Fonksiyonlu
void area_peri(float, float*, float*);  
int main()  
{  
    float radius, area, perimeter;  
  
    printf("Enter radius of Circle\n");  
    scanf("%f", &radius);  
  
    area_peri(radius, &area, &perimeter);  
  
    printf("\nArea of Circle = %0.2f\n", area);  
    printf("Perimeter of Circle = %0.2f\n", perimeter);  
  
    return 0;  
}  
  
void area_peri(float r, float *a, float *p)  
{  
    *a = 3.14 * r * r;  
    *p = 2 * 3.14 * r;  
} 
*/

/* Sayý Deðiþtirme
int swap(int* , int*);

int main(){
	
	int number1;
	int number2;
	
	printf("Enter the number1(N1):");
	scanf("%d",&number1);
	
	printf("Enter the number2(N2):");
	scanf("%d",&number2);
	
	puts("--Swapping Operation--");
	
	swap(&number1,&number2);
	
	printf("N1: %d , N2: %d",number1,number2);
	
	return(0);
}

int swap(int *n1, int *n2){
	
	int temp;
	
	temp=*n1;          // Pointer sayesinde Return yapmaya gerek kalmýyor.
	*n1=*n2;
	*n2=temp;
	
}
*/

/* Kelime Sayýsý (Quiz3)
int sizeOf(char *p);
int main() {
	
    char name[] = "EgemenCanAydugan";
    int d = sizeOf(name);
    printf("%d %s\n", d, name);
    return 0;
}

int sizeOf(char *name){
    char ind = *name; 
    int leng = 0;  

    while (ind != '\0'){ 
        leng++;
        ind = *(name + leng);
    }
    return leng;
}
*/

/*Hacim
double volumerect(double *r1,double *r2,double *r3);
double volumesph(double *rad);
int main(){
	
	int selection;
	double redges[3];
	double radius;
	int i;
	while(1){
		
		printf("1.Rectangular\n2.Sphere\n3.Finish\n");
		printf("Please, enter your selection: ");
		scanf("%d",&selection);
		
		if(selection==1){
			printf("Please, enter the edges of rectangular: ");
			for(i=0;i<3;i++){
				scanf("%lf",&redges[i]);
			}
			printf("The volume of rectangular: %lf\n",volumerect(&redges[0],&redges[1],&redges[2]));
			puts("");
		}
		if(selection==2){
			printf("Please, enter the radius of sphere: ");
			scanf("%lf",&radius);
			printf("The volume of sphere: %lf\n",volumesph(&radius));
			puts("");
		}
		if(selection==3){
			break;
		}
    }
	return(0);
}
double volumerect(double *r1,double *r2,double *r3){
	return (*r1)*(*r2)*(*r3);	
}
double volumesph(double *rad){
	return (4*pi*(*rad)*(*rad)*(*rad))/3;
}
*/

/* Karakter - Sayý Tanýmý
void find(char ch, int *result);
int main(){
	
	char enter,ch;
	int i;
	int result;
	
	for(i=0;i<10;i++){
		
		printf("%d. Character: ",i+1);
		scanf("%c",&ch);
		scanf("%c",&enter);
		find(ch,&result);
		switch(result){
			case 1:
				puts("This is an alphabetic character.");
			break;
			case 2:
				puts("This is a number.");
			break;
			case 3:
				puts("This is a special character.");
			break;
		}
	}	
	return(0);
}
void find(char ch, int *result){
	
	if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')){
		*result = 1;
	}
	else if(ch>='0' && ch<='9'){
		*result = 2;
	}
	else{
		*result = 3;
	}
}
*/

/* Max-Min
void find(int number[],int *max,int *min);
int main(){
	
	int i;
	int number[5];
	int max;
    int min;
	
	printf("Please, enter numbers: ");
	for(i=0;i<5;i++){
		scanf("%d",&number[i]);
	}
	
	max=number[0];
	min=number[0];	
	for(i=0;i<5;i++){
		find(number,&max,&min);
	}
	
	printf("Max: %d --- Min: %d",max,min);
	return(0);
}

void find(int number[],int *max,int *min){
	int i;
	for(i=0;i<5;i++){
		
	if(number[i]>*max){
   		*max= number[i];
	   }
	if(number[i]<*min){
   	   *min= number[i];
	}	
	}	
}
*/

/* Reverse Input
int main(){
	
	int size;
	int i;
	int tmp;
	printf("The lenght of input array: ");
	scanf("%d",&size);
	puts("************     ************");
	
	int number1[size];
	int temp[size];
	int *left;                          
	int *right;
	
	for(i=0;i<size;i++){
		printf("Please, enter the value %d: ",i+1);
		scanf("%d",&number1[i]);
		temp[i]=number1[i];
	}
	
	left = &number1[0];                                 //*left = number1[0] , left = address of number1[0]
	right = &number1[size-1];                           //*right = number1[size-1] , right = address of number1[size-1]
	
	while(left < right) 
    {
        tmp=*left;          
	    *left=*right;
	    *right=tmp;
	    
        left++;                                        // Increment Address 
        right--;                                       // Decrement Address  
    }
	
	puts("The input array --- The output array");
	for(i=0;i<size;i++){
	printf("      %d                   %d\n",temp[i],number1[i]);
	}	
return(0);	
}
*/

/* Integer-Decimal
double funct(double number, double *integerpart, double *decimalpart);
int main(){
	
	double number;
	double integerpart;
	double decimalpart;
	
	while(1){
		printf("Enter the reel number: ");
		scanf("%lf",&number);
		if(number>=0){
		    funct(number,&integerpart,&decimalpart);
			printf("Integer part: %lf\n",integerpart);
			printf("Decimal part: %lf\n",decimalpart);	
		}
		else{
		    break;
		}	
	}
	return(0);
}
double funct(double number, double *integerpart, double *decimalpart){
	
	*decimalpart = number - (int)number;
	*integerpart = (int)number;
}
*/

/*Cümledeki Büyük-Küçük Harfleri Bulma
int funct(char name[], int *big, int *small,int size);
int main(){
	
	char name[100];
	int big;
	int small;
	int i;
	int size=0;
	
	printf("Enter your name and surname: ");
	for(i=0;i<100;i++){
		
	    scanf("%c",&name[i]);
	    
	    if(name[i]=='.'){
			break;	
		}
		 size++;	
	}
	
	funct(name,&big,&small,size);
	printf("Number of big letter: %d\n",big);
	printf("Number of small letter: %d\n",small);		
	return(0);
}

int funct(char name[], int *big, int *small,int size){
	int i;
	
	for(i=0;i<size;i++){
		
		if(name[i]>='A'&&name[i]<='Z'){
		(*big)++;	
		}
		if(name[i]>='a'&&name[i]<='z'){
		(*small)++;
		}
	}
}
*/

/*Paralarý Ayýrma
int funct(int money,int *ahunderd,int *fifty,int *twenty,int *ten,int *five,int *one);
int main(){
	
	int money;
	int ahunderd=0;
	int fifty=0;
	int twenty=0;
	int ten=0;
	int five=0;
	int one=0;
	
	printf("Enter your money: ");
	scanf("%d",&money);
	funct(money,&ahunderd,&fifty,&twenty,&ten,&five,&one);
	printf("A hundred: %d\n",ahunderd);
	printf("Fifty:     %d\n",fifty);
	printf("Twenty:    %d\n",twenty);
	printf("Ten:       %d\n",ten);
	printf("Five:      %d\n",five);
	printf("One:       %d",one);
	return(0);
}
int funct(int money,int *ahunderd,int *fifty,int *twenty,int *ten,int *five,int *one){
	
	while(money>=100){
		(*ahunderd)++;
		money = money-100;
	}
	while(money>=50&&money<100){
		(*fifty)++;
		money = money-50;
	}
	while(money>=20&&money<50){
		(*twenty)++;
		money = money-20;
	}
	while(money>=10&&money<20){
		(*ten)++;
		money = money-10;
	}
	while(money>=5&&money<10){
		(*five)++;
		money = money-5;
	}
	 *one=money;
}
*/

// Series(1/1! + (1+2)/2! + ...)
int funct(int number,double *series);
int main(){
	
	int number;
	double series=0;
	
	printf("Enter a positive number: ");
	scanf("%d",&number);
	
	funct(number, &series);
	printf("Series: %lf",series);
	
	return(0);
}
int funct(int number,double *series){
	
	double fak=1;
	double total=0;
	int i=1;
	int j=1;
	int temp = number;
	
	
	for(i=1;i<=temp;i++){
		for(j=1;j<=number;j++){
		total +=j;
		fak *=j;	
		}
		number--;
		*series += total/fak;
		total=0;
		fak=1;
	}
}
//

/* Kontrol Hanesi 
int funct(int number[],int *finaldigit);
int main(){
	
	int number[9];
	int i;
	int finaldigit;
	
	for(i=0;i<9;i++){
		printf("%d. digit: ",i+1);
		scanf("%d",&number[i]);
	}
	funct(number,&finaldigit);
	printf("Control Digit(10. Digit): %d",finaldigit);
	return(0);
}
int funct(int number[],int *finaldigit){
	
	int total=0;
	int i=0;
	for(i=0;i<9;i++){
		total += number[i]*(i+1);
	}
	*finaldigit = total%11;
}
*/

/* Matrix Tek Sayý Tutma
int funct(int number[][10],int oddar[],int size,int *nofodd);
int main(){
	
	int i;
	int j;
	int size;
	int nofodd=0;
	printf("Enter a size of matrix: ");
	scanf("%d",&size);
	
	int number[10][10];
	int oddar[100];
	
	for(i=0;i<size;i++){
		printf("Enter the %d. row:  ",i+1);
		for(j=0;j<size;j++){
			scanf("%d",&number[i][j]);
			}
	}
	
	funct(number,oddar,size,&nofodd);
	printf("New array: ");
	for(i=0;i<nofodd;i++){
		printf ("%d ",oddar[i]);
	}
	return(0);
}
int funct(int number[][10],int oddar[],int size,int *nofodd){
	
	int i,j;
	int temp=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(number[i][j]%2 == 1){
				oddar[temp]=number[i][j];
				temp++;
			}
		}
	}
	*nofodd = temp;
}
*/
