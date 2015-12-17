#include <stdio.h>

void firstprint(int *age, char **name, int count);
void secondprint(int *age, char **name, int count);
void thirdprint(int *age, char **name, int count);
void fourthprint(int *age, char **name, int count);

int main(int argc, char *argv[]){
	// create two arrays:
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = { 
		"Alan", "Frank", "Mary", "John", "Lisa"
	};
	// safely get the size of ages
	int count = sizeof(ages)/ sizeof(int);
	int i = 0 ;
	
	// first way of using indexing
	for(i = 0; i < count; i++){
		printf("%s has %d years alive\n", names[i], ages[i]);
	}
	printf("---\n");
	
	// setup the pointers to the start of the arrays
	int *cur_age = ages;
	char **cur_name = names;
	
	// second way using pointers
	for(i = 0; i < count; i++){
		printf("%s is %d years old.\n", *(cur_name+i), *(cur_age+i));
	}
	printf("---\n");
	
	// third way, pointers are just arrays
	for(i = 0; i < count; i++){
		printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
	}
	printf("---\n");
	
	// fourth way with pointers
	for(cur_name = names, cur_age = ages; 
			(cur_age - ages) < count; 
			cur_name++, cur_age++){
		printf("%s is %d years old.\n", *(cur_name), *(cur_age));
	}
	
	printf("Extra:\n");
	firstprint(ages, names, count);
	secondprint(ages, names, count);
	thirdprint(ages, names, count);
	fourthprint(ages, names, count);
	
	return 0;
}



void firstprint(int *age, char **name, int count){
	// first way of using indexing
	int i = 0;
	for(i = 0; i < count; i++){
		printf("%s has %d years alive\n", name[i], age[i]);
	}
	printf("---\n");
	return;
}

void secondprint(int *age, char **name, int count){
	// second way using pointers
	int i = 0;
	for(i = 0; i < count; i++){
		printf("%s is %d years old.\n", *(name+i), *(age+i));
	}
	printf("---\n");
}

void thirdprint(int *age, char **name, int count){
	// third way, pointers are just arrays
	int i = 0;
	for(i = 0; i < count; i++){
		printf("%s is %d years old.\n", name[i], age[i]);
	}
	printf("---\n");
}

void fourthprint(int *age, char **name, int count){
	int *cur_age = age;
	char **cur_name = name;
	// fourth way with pointers
	for(cur_name = name, cur_age = age; 
			(cur_age - age) < count; 
			cur_name++, cur_age++){
		printf("%s is %d years old.\n", *(cur_name), *(cur_age));
	}
}


