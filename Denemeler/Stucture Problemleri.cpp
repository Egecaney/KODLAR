#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* P(x,y) ; y=mx+c Kontrol
struct line{
	int m;
	int c;	
};
struct point{
	int x;
	int y;
	char YoN;
};
int main(){
	struct line lines;
	struct point points[100];
	int i=0;
	char select;
	char enter;
	
	printf("\n                y=mx+c\n");
	printf("Enter the m and c coordinates for %d. point: ",i+1);
	scanf("%d%d",&lines.m,&lines.c);
	
	do{
		printf("Enter the x and y coordinates for %d. point: ",i+1);
		scanf("%d%d",&points[i].x,&points[i].y);
		
		if(points[i].y==(lines.m)*(points[i].x)+lines.c){
			points[i].YoN='Y';
		}
		else{
			points[i].YoN='N';
		}
		
		if(points[i].YoN=='Y'){
			printf("This points is on this equation.\n");
		}
		else{
			printf("This points is not on this equation.\n");
		}
		
		printf("Do you want to check another points? (Y/N): ");
		scanf("%c",&enter);
		scanf("%c",&select);
		i++;
	}while(select=='Y');
	
	return(0);
}
*/

/*  Karmaþýk Sayý Toplama Çýkarma (Fonksiyonlu)
struct complex{
	double reel;
	double imaginary; 
};
struct complex operation(struct complex,struct complex,char ope);
int main(){
	
	struct complex Z[3];
	char enter,ope;
	
	printf("Enter the first complex number: ");
	scanf("%lf%lf",&Z[0].reel,&Z[0].imaginary);
	
	printf("Enter the second complex number: ");
	scanf("%lf%lf",&Z[1].reel,&Z[1].imaginary);
	
	printf("Enter the operator: ");
	scanf("%c",&enter);
	scanf("%c",&ope);
	
	Z[2]=operation(Z[0],Z[1],ope);
	
	if(Z[2].imaginary>0){
		printf("Final Result: %.2lf+%.2lfi",Z[2].reel,Z[2].imaginary);
	}
	else{
		printf("Final Result: %.2lf%.2lfi",Z[2].reel,Z[2].imaginary);
	}
	
	return(0);
}

struct complex operation(struct complex z1,struct complex z2,char ope){
	struct complex final;
	
	if(ope=='+'){
		final.reel = z1.reel+z2.reel;
		final.imaginary = z1.imaginary+z2.imaginary;
	}
	else{
		final.reel = z1.reel-z2.reel;
		final.imaginary = z1.imaginary-z2.imaginary;
	}
	return(final);
}
*/

/* Yarýþma (Puan Hesaplama)
struct player{
	char name[100];
	char surname[100];
	double points[5];
	double perform;
};
double calcu(struct player);
int main(){
	struct player first[2];
	int i=0;
	int j=0;
	char enter;
	
	for(j=0;j<2;j++){
		
	printf("Player %d:\n",j+1);
	printf("Name: ");
	gets(first[j].name);
	printf("Surname: ");
	gets(first[j].surname);
	
	printf("Judge points: ");
	for(i=0;i<5;i++){
		scanf("%lf",&first[j].points[i]);
	}
	
	first[j].perform = calcu(first[j]);
	scanf("%c",&enter);	
	}
	
	for(i=0;i<2;i++){
	printf("The performance points of %s %s: %lf\n",first[i].name,first[i].surname,first[i].perform);	
	}
	
	printf("Winner: ");
	if(first[0].perform>first[1].perform){
		printf("%s %s with performance point %lf",first[0].name,first[0].surname,first[0].perform);
	}
	if(first[1].perform>first[0].perform){
		printf("%s %s with performance point %lf",first[1].name,first[1].surname,first[1].perform);
	}
	else{
		printf(" TWO CHAMP! ");
	}
		
	return(0);
}
double calcu(struct player first){
	double result=0;
	int i;
	double max = first.points[0];
	double min = first.points[0];
	
	for(i=1;i<5;i++){
		if(max<first.points[i]){
			max = first.points[i];
		}
		if(min>first.points[i]){
			min = first.points[i];
		}
	}
	
	for(i=0;i<5;i++){
		result+=first.points[i];
	}
	
	result = (result-max-min)/3;
	return(result);
}
*/

/* Fonksiyonsuz Not Hesaplama
struct info{
	int schnumber;
	char answer[10];
	double trueans[3];
	double falseans[3];
	double points[3];
};
int main(){
	struct info student[3];
	char realansw[10];
	char enter;
	int i,j;
	
	printf("Enter the correct answers: ");
	gets(realansw);
	printf("\n\n");
	for(i=0;i<3;i++){
		
		student[i].trueans[i]=0;
		student[i].falseans[i]=0;
		
		printf("Student %d\n",i+1);
		printf("School Number: ");
		scanf("%d",&student[i].schnumber);
		scanf("%c",&enter);
		printf("Enter the student answers: ");
		gets(student[i].answer);
		
		for(j=0;j<10;j++){
			if(student[i].answer[j]== realansw[j]){
				student[i].trueans[i] ++;
			}
			else{
				student[i].falseans[i] ++;
			}
		}
		
		printf("Number of true: %.0lf\n",student[i].trueans[i]);
		printf("Number of false: %.0lf\n\n\n",student[i].falseans[i]);
		student[i].points[i]= 10-student[i].falseans[i]-((student[i].falseans[i])/4);
	}
		for(i=0;i<3;i++){
			printf("Point of %d. student: %.2lf\n",i+1,student[i].points[i]);
		}
		
	return(0);
}
*/

/* Union Örneði
struct input{
	int number;
	union{
		char ch[20];
	    double reel[20];
	}subcover;
};
int main(){
	struct input value[20];
	int i=0;
	int numberofreel=0;
	double avg=0;
	char enter;
	
	printf("1-> Character\n0-> Reel Number\nOther Numbers-> Exit\n");
	
	for(i=0;i<20;i++){
		printf("Enter a number: ");
		scanf("%d",&value[i].number);
		if(value[i].number==1){
			printf("Enter a character: ");
			scanf("%c",&enter);
			scanf("%c",&value[i].subcover.ch[i]);
		}
		else if(value[i].number==0){
			printf("Enter a reel number: ");
			scanf("%lf",&value[i].subcover.reel[i]);
			numberofreel++;
			avg += value[i].subcover.reel[i];
		}
		else{
			break;
		}
	}
	
	avg=(avg)/numberofreel;
	printf("The average of reel number: %.2lf",avg);
	return(0);
}
*/

// Hastahane Kaydý
struct people{
	char name[20];
	char surname[20];
	char blood_type[2];
	int age;
};
int main(){
	struct people information[20];
	int i=0;
	int j=0;
	int numberofpeople=0;
	int selection;
	char enter;
	
	do{
		printf("Hospital Information System\n");
		printf("(1)  Add New Patient\n(2)  Display the Information\n(3)  Exit the Menu\nSelect option 1, option 2 or option 3: ");
		scanf("%d",&selection);
		
		if(selection==1){
			printf("First Name: ");
			scanf("%s",information[i].name);
			printf("Last Name: ");
			scanf("%s",information[i].surname);
			printf("Blood Type (A-B-AB-0): ");
			scanf("%s",information[i].blood_type);
			printf("Age: ");
			scanf("%d",&information[i].age);
			i++;
		}
		else if(selection==2){
			printf("---Informations---\n");
			for(j=0;j<i;j++){
				printf("%s   %s    %s   %d\n",information[j].name,information[j].surname,information[j].blood_type,information[j].age);
			}
		}
		else{
			break;
		}
		printf("\n\n");
	}while(selection == 1||selection ==2);
	
	return(0);
}
//


