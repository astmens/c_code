#include <stdio.h>

int main(int argc, char* argv[]){
	int bugs = 100;
	double bug_rate = 1.2;
	
	printf("You have %d bugs at the imaginary rate of %f. \n",
		bugs, bug_rate);
		
	long universe_of_defects = 1L * 1024L * 1024L * 1024L;
	printf("The intire universe has %ld bugs. \n", 
		universe_of_defects);
		
	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", 
		expected_bugs);
		
	//double part_of_universe = expected_bugs / universe_of_defects; // conversion warning: 'double' from 'long int'
	double part_of_universe = expected_bugs / (double)(universe_of_defects); // cast gets rid of warning message.
	printf("That is only a %e portion of the universe. \n",
		part_of_universe);
		
	// this is just a demo...
	char nul_byte = '\0';
	int care_percentage = bugs * nul_byte;
	printf("Which means you should care %d%%.\n",
		care_percentage);
		
	//extra credit, try and break it:
	//printf("%s\n", nul_byte);
	printf("%c\n", nul_byte);
	long limits_of_long = (2 << 31) - 1 + 7; // +1 = zero, +7 = six
	printf("Value of long: %li\n", limits_of_long);
	
		
	return 0;
}
