#include <stdio.h>
#include <stdlib.h>
int frobcmp (char const * a, char const * b)
 {
    for (;; a++, b++) {
        if(*a == ' ' && *b == ' ') return 0; //@end of argument or arg is empty
        else if (*a == ' ' || (*a ^ 42) < (*b ^ 42)) return -1; //a < b
        else if (*b == ' ' || (*b ^ 42) < (*a ^ 42)) return 1; //a > b
	}
 }

int compare(const void* a, const void* b){
	return frobcmp(*(char const**)a, *(char const**)b);
}

void checkError(){
	if(ferror(stdin)){
		fprintf(stderr, "cannot read file properly.");
		exit(1);
	}
}

int main(void){
    int letter_count = 0;
    int word_count = 0;
	char* word;
	char** word_list;
	
	word = (char*)malloc(sizeof(char));
	word_list = (char**)malloc(sizeof(char*));

	char curr = getchar();
	checkError();
	
	while(curr != EOF){
		word[letter_count] = curr;
		char* tmp = realloc(word, (letter_count + 2)*sizeof(char));
		if(tmp == NULL){
			free(word);
			fprintf(stderr, "cannot allocate memory properly.");
			exit(1);
		}
		else word = tmp;
		letter_count++;
		
		if(curr == EOF) exit(0);	
		if(curr == ' '){
			word_list[word_count] = word;
			char** tmp_list = realloc(word_list, sizeof(char*)*(word_count + 2));
			if(tmp_list == NULL){
				free(word_list);
				fprintf(stderr, "cannot allocate memory properly.");
				exit(1);
			}	 
			else {
				word_list = tmp_list;
				word = NULL;
				word = (char*)malloc(sizeof(char));
				word_count++;
				letter_count = 0;
			}
		}	
		char next = getchar();
		checkError();
		if(next == EOF && curr == ' ') break;
        else if (next == EOF)
            curr = ' ';
        else if (next == ' ' && curr == ' '){
			while(curr == ' '){
				curr = getchar();
				checkError();
			}
		}
		else curr = next;
	}
	
	qsort(word_list, word_count, sizeof(char*), compare);

	for(int i = 0; i < word_count; i++){
	    for(int j = 0;; j++){
			if(putchar(word_list[i][j]) == EOF) {
				fprintf(stderr, "cannot write output properly.");
				exit(1);
			}			
			if(word_list[i][j] == ' ') break;
		}
	}

	for(int i = 0; i < word_count; i++){
		free(word_list[i]);
	}
	free(word_list);

	exit(0);
}
