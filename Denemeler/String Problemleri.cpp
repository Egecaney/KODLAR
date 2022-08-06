#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// strlen()	computes string's length
// strcpy()	copies a string to another
// strcat()	concatenates(joins) two strings
// strcmp()	compares two strings
// strlwr()	converts string to lowercase
// strupr()	converts string to uppercase

// scanf("%s",a) komutu boþluk olunca \0 koyar ve biter.
// gets(a) Hepsini yazdýrýr, bitince \0 koyar.

// sscanf() , sprintf() 

 /* Temel1
int main(){
	
	char s[] = "EgemenCan";
	char *t=&s[6];
	printf("%s\n",s);                   // s = EgemenCan
	printf("%s\n",t);                   // t = Can
	printf("%d\n",strlen(s));           // strlen(s) = 9
	printf("%d\n",strlen(t));           // strlen(t) = 3
	printf("%c %c\n",s[6],t[0]);        // s[6]=C, t[0]=C	
	return(0);
}
*/

/* Temel2
int main(){
	
	char s[25];
	int k=0;
	
    printf("Enter a string: ");
    gets(s);
    
    for(int i=0;i<strlen(s);i++){
    	
    	if(s[i]!=' '){
    		k++;
		}
	}
	
	if(k==0){
		puts("No sentences.");
	}
	else{
		printf("%s",s);
	}
	
}
*/

/* Temel3 ( sscanf() , sprintf() )
int main(){
	
	char s1[25] = "Computer Programming";
	char s2[25];
	char s3[25];
	
	sscanf(s1,"%s %s",s2,s3);
	printf("%s\n%s\n%s\n",s1,s2,s3);
	
	sprintf(s2,"***%s***",s1);
	printf("%s\n%s\n%s",s1,s2,s3);
	return(0);
	
}
*/

/* Temel4 ( strcpy(), strncpy(), strcat() )
int main(){
	
	printf("----PART1----\n");
	int number1;
	int number2;
	char yon[6];
	
	printf("Enter a two positive number: ");
	scanf("%d%d",&number1,&number2);
	
	if(number1==number2){
		strcpy(yon,"Yes");
	}
	else{
		strcpy(yon,"No");
	}
	printf("Are there equal?: %s",yon);
	
	printf("\n\n----PART2----\n");
	char string[10] = "Egemen";
	printf("%s\n",string);
	strcat(string," Can");
	printf("%s\n",string);
	strncpy(string,"ABC",2);
	printf("Character: %s\nC.Number: %d",string,strlen(string));

	return(0);
}
*/

/* Temel 5
int main(){
	
	char a[50]="C Dersi:Cozumlu Problem Kitabi";
	char b[50]="";
	char c[5]="***";
	char d[50]="";
	
	printf("----PART1----\n");
	printf("Char. Number: %d\n",strlen(a));
	
	printf("\n----PART2----\n");
	strcpy(b,&a[8]);
	printf("%s\n",b);
	
	printf("\n----PART3----\n");
	strncpy(b,&a[8],7);
	b[7]='\0';
	printf("%s\n",b);
	
	printf("\n----PART4----\n");
	strcat(d,c);
	strncat(d,a,7);
	strcat(d,c);
	printf("%s\n",d);
	
	printf("\n----PART5----\n");
	strcpy(b,&a[8]);
	strcat(b," ");
	strncat(b,a,7);
	b[strlen(a)+1]='\0';
	printf("%s\n",b);
	
	return(0);
}
*/

/* Temel6 (Strncpy)
int main(){
	
	char string[100];
	char st[100];
	int position;
	int length;
	
	printf("Test Data:\n");
	printf("Input the string: ");
	gets(string);
	
	printf("Input the position to start extraction: ");
	scanf("%d",&position);
	printf("Input the length of substring: ");
	scanf("%d",&length);
	
	printf("Expected Data:\n");
	printf("The substring retrieve from the string is: '%s' ",strncpy(st,&string[position-1],length));
	return(0);
}
*/

/* Tekil-Çoðul 
int main(){
	
	char string[10];
	int i=0;
	int j;
	
	for(i=0;i<100;i++){
		printf("%d. Nonplural: ",i+1);
		gets(string);
		
		if(string[0]=='.'){
			break;
		}
		
		if(string[strlen(string)-1] == 'y'){
			string[strlen(string)-1] = 'i';
			strcat(string,"es");
		}
		else if(string[strlen(string)-1] == 'x'||string[strlen(string)-1] == 's'){
			strcat(string,"es");
		}
		else{
			strcat(string,"s");
		}
		
		printf("%d. Plural: %s\n\n",i+1,string);
	}
	return(0);
}
*/

/* PALINDROME
int main(){
	
	char string1[15] = "NeveroddoreveN";
	char string2[12] = "Fundemental";
	int i;
	int k1=0;
	int k2=0;
	
	for(i=0;i<strlen(string1)/2;i++){
		
		if(string1[i]!=string1[strlen(string1)-i-1]){
			k1++;
		}
	}
	
	for(i=0;i<strlen(string2)/2;i++){
		
		if(string2[i]!=string2[strlen(string2)-i-1]){
			k2++;
		}
	}
	
	if(k1==0){
		printf("%s is palindrome.\n",string1);
	}
	else{
		printf("%s is not palindrome.\n",string1);
	}
	if(k2==0){
		printf("%s is palindrome.\n",string2);
	}
	else{
		printf("%s is not palindrome.\n",string2);
	}
	
	return(0);
}
*/

/* Cümleden Kelime Çýkarma
int main()
{
    char str[100]; 
	char word[20];
    int i, j;
	int lens, lenw;
	int temp, chk=0;
	
    printf("Enter the String: ");
    gets(str);
    lens = strlen(str);
    
    printf("Enter a Word: ");
    gets(word);
    lenw = strlen(word);
    
    for(i=0;i<lens;i++){
    	
        temp = i;
        for(j=0;j<lenw;j++){
            if(str[i]==word[j]){
            	i++;
			}
        }
        
        chk = i-temp;
        if(chk==lenw){
        	
            i = temp;
            for(j=i; j<(lens-lenw); j++)
                str[j] = str[j+lenw];
            lens = lens-lenw;
            str[j]='\0';
        }
    }
    
    printf("\nNew String = %s", str);
    return(0);
}
*/

/* Kýsaltma
void func(char s1[],char s2[]);
int main(){
	
	char s1[25];
	char s2[10];
	int i;
	
	while(1){
		
		printf("Enter a string: ");
	    gets(s1);
	    
	    if(s1[0]=='.'){
	    	break;
		}
		else{
			func(s1,s2);
			printf("Shortening: %s\n",strupr(s2));
		}
	}
	return(0);
}
void func(char s1[],char s2[]){
	
	int lens= strlen(s1);
	int i;
	int next=1;
	s2[0]=s1[0];
	for(i=1;i<lens;i++){
		
		if(s1[i]==' '){
			s2[next]=s1[i+1];
			next++;
		}
		
	}
	s2[next]='\0';
}
*/

/*En Uzun ve En Kýsa Kelime Bulma
void find(char sentence[],char bigword[],char smallword[]);
int main(){
	
	char sentence[100];
	char bigword[30];
	char smallword[30];
	
	printf("Enter a sentence: ");
	gets(sentence);
	
	find(sentence,bigword,smallword);
	printf("Biggest Word: %s\nSmallest Word: %s",bigword,smallword);
	return(0);
}
void find(char sentence[],char bigword[],char smallword[]){
	
	int len,d=0;
	int final;
	int first;
	int small=100;
	int big=0;
	char word[30];
	
	while(sentence[d]!='\0'){
		
		first=d;
		while(sentence[d]!=' '&&sentence[d]!='\0'){
			d++;
		}
		final=d;
		
		strncpy(word,&sentence[first],final-first);
		word[final-first]='\0';
		len= strlen(word);
		
		if(sentence[d]!='\0'){
			d++;
		}
		if(len<small){
			strcpy(smallword,word);
			small=len;
		}
		if(len>big){
			strcpy(bigword,word);
			big=len;
		}
		
	}
}
*/

/* Büyük Harfler ile Maxtrix
int main(){
	
	char sent[100];
	char matr[5][10];
	int bigword=0;
	int lens;
	int i,j;
	int sat=0,sut=0;
	
	for(i=0;i<5;i++){
		for(j=0;j<10;j++){
			matr[i][j]='*';
		}
	}
	
	printf("Please, enter a sentence: ");
	gets(sent);
	lens= strlen(sent);
	
	for(i=0;i<lens;i++){
		if(sent[i]>='A'&&sent[i]<='Z'){
			matr[sut][sat] = sent[i];
			sut++;
			bigword++;
			if(sut==5){
				sut=0;
				sat++;
			} 
		}
	}
	printf("Number of bigword: %d\n",bigword);
	puts("Matrix:");
	for(i=0;i<5;i++){
		for(j=0;j<10;j++){
			printf("%c ",matr[i][j]);
		}
		puts("");
	}
	
	return(0);
}
*/

/* Notlara Ayýrma
int main(){
	
	char names[100];
	char div[15];
	int lens;
	int i=0;
	int first=0;
	int temp=0;
	int even=0;
	
	printf("Please, enter names nad notes: ");
	gets(names);
	lens=strlen(names);
	
	printf("List:\n");
	while(i<lens){
		
		if(names[i]==' '||names[i+1]=='\0'){
			even++;
			temp=1;
		}
		if(even%2==0&&temp==1){
			strncpy(div,&names[first],i-first+1);
			div[i-first+1]='\0';
			first= i+1;
			puts(div);
			temp=0;
		}
		i++;
	}
	return(0);
}
*/

/* Alfabetik Sýralama
void func(char name[][10]);
int main(){
	
	char name[10][10];
	int i;
	
	printf("Enter a word: ");
	for(i=0;i<10;i++){
		scanf("%c",&name[i]);
	}
	func(name);
	printf("Ordered Word: ");
	for(i=0;i<10;i++){
		printf("%s ",name[i]);
	}
	return(0);
}
void func(char name[][10]){
	
	char temp[10];
	int i;
	int j;
	
	for(i=0;i<9;i++){
		for(j=0;j<9-i;j++){
			if(strcmp(name[j],name[j+1])>0){
				strcpy(temp,name[j]);
				strcpy(name[j],name[j+1]);
				strcpy(name[j+1],temp);
			}
		}
	}
	
}
*/

/* Ortak Kelime
int hmcopy(char *str1,char *str2);
int main(){
	
	char str1[100];
	char str2[100];
	int copy;
	
	printf("The first string is: ");
	gets(str1);
	printf("The second string is: ");
	gets(str2);
	copy = hmcopy(str1,str2);
	printf("Number of characters copied: %d",copy);
	
	return(0);
}
int hmcopy(char *str1,char *str2){
	
	int i=0;
	int temp=0;
	int lenght;
	
	if(strlen(str1)>=strlen(str2)){
		lenght = strlen(str1);
	}
	else{
		lenght = strlen(str2);
	}
	
	for(i=0;i<lenght;i++){
		if(str1[i]==str2[i]){
			temp++;
		}
	}
	return temp;
}
*/

/* Ünlü-Ünsüz Harfler
void WowelorConsonant(char *string,int *wovel,int *consonant);
int main(){
	
	char string[100];
	int wovel=0;
	int consonant=0;
	
	printf("Test Data:\n");
	printf("Input the string: ");
	gets(string);
	
	
	printf("\nExpected Data:\n");
	WowelorConsonant(string,&wovel,&consonant);
	printf("The total number of wovel in the string is: %d\n",wovel);
	printf("The total number of consonant in the string is: %d",consonant);
	return(0);
}
void WowelorConsonant(char *string,int *wovel,int *consonant){
	
	int i=0;
	int lenght = strlen(string);
	
	printf("Output the string: %s\n",string);
	for(i=0;i<lenght;i++){
		
		if(string[i]=='A'||string[i]=='a'||string[i]=='E'||string[i]=='e'||string[i]=='U'||string[i]=='u'||string[i]=='O'||string[i]=='o'||string[i]=='I'||string[i]=='i'){
			(*wovel)++;
		}
		else{
			(*consonant)++;
		}	
	}
}
*/

/* Stringdeki Harfleri ASC2 Tablosuna Göre Büyükten Küçüðe Sýralama
void order(char *string1);
int main(){
	
	char string1[100];
	char string2[100];
	
	printf("Test Data:\n");
	printf("Input the string: ");
	gets(string1);
	
	
	printf("\nExpected Data:\n");
	order(string1);
	printf("Input the string: %s",string1);
	return(0);
}
void order(char *string1){
	
	int i;
	int j;
	int lenght = strlen(string1);
    char temp;
      
    for(i=0;i<lenght;i++){
        for(j=0;j<lenght;j++){
            if(string1[j]<=string1[i]){  // < ise Büyükten ---> Küçüðe , > ise Küçükten --->  Büyüðe
                temp=string1[i];  
                string1[i]=string1[j];
                string1[j]=temp;
            }
        }
    }    
}
*/

/*
int main(){
	
    char name[25][50];
    char temp[25];
    int n,i,j;
  
    printf("Input number of strings :");
    scanf("%d",&n);

    printf("\nInput string %d :\n",n);
    for(i=0;i<=n;i++){
       gets(name[i]);
    }
     
    for(i=1;i<=n;i++){
    	for(j=0;j<=n-i;j++){
		
		if(strcmp(name[j],name[j+1])>0){ 
            strcpy(temp,name[j]);
	        strcpy(name[j],name[j+1]);
	        strcpy(name[j+1],temp);
	    }
	    }
	}
		  
   printf("\nThe strings appears after sorting :");
	for(i=0;i<=n;i++){
	printf("%s\n",name[i]);	
	}
    return(0);
} 
*/

//
int main(){
	
	char input[100];
	char search[100];
	int length;
	int i;
	int k=0;
	
	printf("Test Data :\n");
	printf("Input the string: ");
	gets(input);
	printf("Input the substring to be search: ");
	gets(search);
	length=strlen(search);
	
	printf("\nExpected Data: \n");
	for(i=0;i<strlen(input);i++){
		
		if(input[i]==search[k]){
			k++;
			if(k==length){
	        break;
	}	
		}
		else{
			k=0;
		}
	}
	if(k==length){
	printf("The substring is exists in the string.");
	}
	if(k!=length){
	printf("The substring is not exists in the string.");	
	}

	return(0);
}
//

