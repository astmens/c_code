/*
	ex16np.c - "no pointer version"
*/
#define _GNU_SOURCE 1	// "hides a warning" about strdup

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};
struct Person Person_create(char *name, int age, int height, int weight);
void Person_destroy(struct Person who);
void Person_print(struct Person who);

struct Person Person_create(char *name, int age, int height, int weight){
	struct Person who;
	
	who.name = strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;
	
	return who;
}
void Person_destroy(struct Person who){
	// how does this "freeing" work, when "pass-by-value" is used?
	free(who.name); 
}

void Person_print(struct Person who){
	printf("Who is at memory location %p:\n", (void*)&who);
	//printf("Who.name is at memory location %p:\n", (void*)&who.name); //address of who.name is same as who
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);	
}

int main(int argc, char *argv[]) {
	// make struct on stack:
	struct Person stack = {"Stack Person", 25, 67, 60};
	Person_print(stack);
	
	// make two people structures
	struct Person joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person frank = Person_create("Frank Blank", 20, 72, 180);
	
	//print them out:
	printf("Joe.name is at memory location %p:\n", (void*)&joe.name); // cast to void* hides warning
	Person_print(joe);
	
	printf("Frank is at memory location %p:\n", (void*)&frank);
	Person_print(frank);
	
	printf("After 20 years...\n");
	joe.age += 20;
	joe.height -= 2;
	joe.weight += 40;
	Person_print(joe);
	
	frank.age += 20;
	frank.weight += 20;
	Person_print(frank);
	
	// destroy, clean up;
	Person_destroy(joe);
	Person_destroy(frank);
	
	
	return 0 ;
}


