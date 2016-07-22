#include <stdio.h>

//#define func(t,a,b)
int main(int argc, char *argv[]){
	printf("Output %s:\n", argv[0]);
	int num = 425;
	printf("%d", printf("%d\n", num));
	//int i,j,k;
	//i=4;
	//j=30;
	//k=0;
	//k=j++/i++;
	//++k;
	//printf("%d %d %d\n", i,j,k);
	
	//char arr[]={'R', 'A', 'M'};
	//printf("%d\n",strlen(arr));
	printf("%d\n", -1L < 1U);
	printf("%d\n", -1L < 1U);
	//signed char i = 1;
	//for(; i<=255; i++) printf("%d ", i);
	char arr1[]="REGALINT";
	printf("%d,",strlen(arr1));
	printf("%d\n",sizeof(arr1));
	//unsigned char a=255;
	//a = a+1;
	//printf("%d\n", a);
	
	/*
	int arr[10];
	int a = sizeof(arr);
	printf("%d\n", a);
	
	int arr[][2]= {1,2,3,4,5,6};
	printf("%d", arr[2][1]);
	
	int n = 5, x; 
	x=++n++;
	printf("%d", x);
	*/
	enum{red, green, blue = 0, white};
	printf("%d %d, %d, %d\n", red, green, blue, white);
	printf("\n");
	
	return 0;
}
