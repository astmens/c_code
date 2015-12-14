#include <stdio.h>

int main(int argc, char *argv[]){
	int numbers[5] = {0};
	char name[5] = {'a'};
	
	// first, print them out raw:
	printf("numbers: %d %d %d %d %d\n", 
		numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	printf("name each: %c %c %c %c %c\n", 
		name[0], name[1], name[2], name[3], name[4]);
	printf("name: %s\n", name);
	
	// setup numbers:
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;
	numbers[4] = 5;
	//setup name:
	name[0] = 'T';
	name[1] = 'o';
	name[2] = 'm';
	name[3] = 's';
	name[4] = '\0';
	
	// print out initialized:
	printf("numbers: %d %d %d %d %d\n", 
		numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	printf("name each: %c %c %c %c %c\n", 
		name[0], name[1], name[2], name[3], name[4]);
	printf("name: %s\n", name);
	
	char *another = "Toms";
	//printf("another: %s\n"); // segmentation fault, core dump!
	printf("another: %s\n", another);
	printf("another each: %c %c %c %c %c\n", 
		another[0], another[1], another[2], another[3], another[4]);
	
	// Ways to break the program:
	// *) when char[] is used ar string and not Null terminated.
	// *) string expected but not given for printf output.
 
 	// Extra credit:
 	printf("Extra credit\n");
	// setup numbers:
	name[0] = 1;
	name[1] = 2;
	name[2] = 3;
	name[3] = 4;
	name[4] = 5;
	//setup name:
	numbers[0] = 'T';
	numbers[1] = 'o';
	numbers[2] = 'm';
	numbers[3] = 's';
	numbers[4] = '\0';
	
	// print out initialized:
	printf("numbers: %d %d %d %d %d\n", 
		numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
	printf("name each: %c %c %c %c %c\n", 
		name[0], name[1], name[2], name[3], name[4]);
	//printf("name: %s\n", name); // NOT Null terminated!
	// encoding & decoding 4*char's as 1*int
	int msk = 0x000000ff;
	// 0x04000000 + 0x00030000 + 0x00000200 + 0x00000001 = 
	// 0x04030201 = 67305985
	int chars = (name[0] << (8*0)) + (name[1] << (8*1)) + 
		(name[2] << (8*2)) + (name[3] << (8*3));
	printf("chars: %d, (%d, %d, %d, %d)\n", 
		chars, 
		((chars & (msk<< (8*0))) >> (8*0)), 
		((chars & (msk<< (8*1))) >> (8*1)),
		((chars & (msk<< (8*2))) >> (8*2)),
		((chars & (msk<< (8*3))) >> (8*3)) );
	
	// Segmentation fault:
	/*	
	char *name2;
	name2[0] = 'T';
	name2[1] = 'o';
	name2[2] = 'm';
	name2[3] = 's';
	name2[4] = '\0';
	
	printf("name2: %s\n", name2);
	*/
	
	return 0;
}
