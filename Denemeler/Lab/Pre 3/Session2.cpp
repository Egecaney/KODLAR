#include<stdio.h>
#include<math.h>

//Session2_Q1
int main(){
	
	int size;
	int i=0;
	int j=0;
	int tracA=0;
	int tractrasA=0;
	
	printf("Enter the size of matrix A: ");
	scanf("%d",&size);
	
	int A[size][size];
	
	printf("Enter the elements of A:\n");
	puts("------------------------");
	
	for(i=0;i<size;i++){
		
		printf("Enter the row %d of A: ",i+1);
		for(j=0;j<size;j++){
		scanf("%d",&A[i][j]);		
	    }
	}
	
	int At[size][size];
	printf ("The matrix A: \n");
	for(i=0;i<size;i++){
		
		for(j=0;j<size;j++){	
		At[i][j]=A[i][j];
		printf("%d ",At[i][j]);		
	    }
	    
	    puts(" ");
	}
	puts(" ");
	printf("The transponse of Matrix A: \n");
	for(i=0;i<size;i++){
		
		for(j=0;j<size;j++){
		printf("%d ",A[j][i]);		
	    }
	    puts(" ");
	}
	puts(" ");
	i=0;
	while(i<size){
		tracA += A[i][i];
		i++;	
	}
	
	i=0;
	while(i<size){
		tractrasA += At[i][i];
		i++;	
	}
	
	printf("The trace of A: %d ",tracA);
	printf("\nThe trace of transpose A: %d ",tractrasA);
	if(tracA==tractrasA){
		printf("\nThe property is verified!");
		
	}
	return(0);
}

/* Session2_Q2
float computeArea(float length, float width);
float computePerimeter(float length, float width);

int main(){
	
	float length;
	float width;
	char AorP;
	char enter;
	
	printf("Enter the lenght of rectangle: ");
	scanf("%f",&length);
	printf("Enter the width of rectangle: ");
	scanf("%f",&width);
	
	scanf("%c",&enter);
	printf("Choose the operation(A/a or P/p): ");
	scanf("%c",&AorP);
	
	switch(AorP){
		
		case 'a':
		case 'A':	
		computeArea(length,width);
		break;
		
		case 'p':
	    case 'P':
		computePerimeter(length,width);
		break;	
	}
	return(0);
}
float computeArea(float length, float width){
	float area;
	area =length*width;
	printf("Area is %f",area);
	
}
float computePerimeter(float length, float width){
	float perimeter;
	perimeter= (length+width)*2;
	printf("Perimeter is %f",perimeter);
}
*/
