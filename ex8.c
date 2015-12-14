#include <stdio.h>

int main(int argc, char *argv[]){
	int areas[] = {10, 12, 13, 14, 20};
	char name[] = "Toms";
	char full_name[] = {'T', 'o', 'm', 's', 
		' ', 'A', '.', ' ', 
		'A', 's', 't', 'a', 'h', 'o', 'v', 's', 'k', 'i', 's', '\0'
	};
	// warning: on some systems you may have to 
	// change the %ld int this code to %u
	printf("The size of an int %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
	printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);
	printf("The size of char: %ld\n", sizeof(char));
	printf("The size of name(char[]): %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));
	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));
	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);
	
	// Extra credit, break it:
	areas[9] = 42;
	printf("areas[] out of bounds: %d\n", areas[10]);
	printf("name[] out of bounds: %d\n", name[10]);
	return 0;
}
