#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
	
	int a = 0;
	a++;
	printf("Sizes:\n\tint %ld\n\tlong %ld\n\tdouble %ld\n\tfloat %ld\n\tchar %ld\n\tshort int %ld\n", 
		sizeof(int), sizeof(long), sizeof(double), sizeof(float), sizeof(char),
		sizeof(short int)); // int 4bytes = 32bits
	printf("\tint8_t %ld \t(%d..%d)\n", 
		sizeof(int8_t), INT8_MIN, INT8_MAX);
	printf("Max possible int on this system: %llx\n", INTMAX_MAX);
	return 0;
}
