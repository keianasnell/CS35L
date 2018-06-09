#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Error: incorrect number of arguments in %s", argv[0]);
		exit(1); 
	}	
	
	char* from = argv[1];
	char*to = argv[2];
	if(strlen(from) != strlen(to)){
		fprintf(stderr, "Error: arguments be the same length\n");
        exit(1);
	}

	for(int i = 0; i < strlen(from); i++){
		for(int j = i + 1; j < strlen(from); j++){
			if(from[i] == from[j]){
				fprintf(stderr, "Error: cannot have duplicate byte in argument\n");
        		exit(1);
			}
		}
	}	
	
	char ascii[127];
	for(int i = 0; i < 127; i++){
		ascii[i] = i;
	}
	for(int j = 0; j < strlen(from); j++){
		ascii[from[j]] = to[j];
	}

	char c = getchar();
	while(c != EOF){
		putchar(ascii[c]);
		c = getchar();
	}
}
