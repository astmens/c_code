#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc !=2){
		printf("Error: Your need one argument.\n");
		return 1;
	}
	int i = 0;
	char letter = '\0';
	for(i = 0, letter = argv[1][i]; argv[1][i] != '\0'; i++, letter = argv[1][i]){
		
		if (letter >= 'A' && letter <= 'Z'){
			// convert to lower-case:
			letter = (char)(letter + ('a'-'A'));
		}
		switch(letter){
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				printf("%d: '%c'\n", i, letter);
				break;
			case 'y':
				if(i > 2) {
					// its only sometimes Y
					printf("%d: 'y'\n", i);
					break;
				}
			default:
				printf("%d %c is not a vowel\n", i, letter);
		}
		
		/*		
		switch(letter){
			case 'a':
			case 'A':
				printf("%d: 'A'\n", i);
				break;
			case 'e':
			case 'E':
				printf("%d: 'E'\n", i);
				break;
			case 'i':
			case 'I':
				printf("%d: 'O'\n", i);
				break;
			case 'o':
			case 'O':
				printf("%d: 'O'\n", i);
				break;
			case 'u':
			case 'U':
				printf("%d: 'U'\n", i);
				break;
			case 'y':
			case 'Y':
				if(i > 2) {
					// its only sometimes Y
					printf("%d: 'Y'\n", i);
				}
				break;
			default:
				printf("%d %c is not a vowel\n", i, letter);
		}
		*/
	}
	return 0;
}
