#include <string.h>
#include <stdio.h>
int foo(void) {
  char  bar[128];
  char  *baz = &bar[0];
  
  baz[127] = 0;

  return strlen(baz);
}

int main(int argc, char** argv){
	char blah[] = "fizzbuzz";
	printf("%s\n", blah+4);
	
	if (sizeof(int*) == sizeof(int)) {
		printf("eq\n");
	}
	
	int c[]  = {1, 2, 3, 4};
	printf("%d\n", *(c+2));
	
	printf("foo: %d\n", foo());
	
	
	return 0;
}

