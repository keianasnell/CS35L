#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <ctype.h>

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

int frobcmp_flag (char const * a, char const * b)
 {
    for (;; a++, b++) {
		char u_a = *a ^ 42;
		char u_b = *b ^ 42;
		if(isalpha(u_a)) u_a = toupper((unsigned char) u_a);
		if(isalpha(u_b)) u_b = toupper((unsigned char) u_b);
		
        if(*a == ' ' && *b == ' ') return 0; //@end of argument or arg is empty
        else if (*a == ' ' || u_a < u_b) return -1; //a < b
        else if (*b == ' ' || u_b < u_a) return 1; //a > b
    }
 }

int compare_flag(const void* a, const void* b){
    return frobcmp_flag(*(char const**)a, *(char const**)b);
}

void checkError(int v){
	if(v < 0){
		write(2, "Error: cannot read input correctly", v);
		exit(1);
	}
}
////////////

int main(int argc, char* const argv[]){

	struct stat file_stat;
 	if(fstat(0,&file_stat) < 0){
    	write(2, "Error: cannot retrieve file information properly", argc);
    	exit(1);
  	}

	char* file;
	char** words;
	char* word;
	
	int return_val = 0;
    size_t buffersize = 0;
	int reg = 0;
	//is file is a regular file
	if(S_ISREG(file_stat.st_mode)){
		buffersize = file_stat.st_size + 2;
		file = (char*) malloc(buffersize*sizeof(char));
		words = (char**) malloc(buffersize*sizeof(char*));
		words[0] = file;
		word = words[0];
	}
	//else, file must be read byte-wise
	else {
		word = (char*) malloc(sizeof(char));
        words = (char**) malloc(sizeof(char*));
		if(word == NULL || words == NULL){
			write(2, "Error: cannot allocate memory properly.",return_val);
			exit(1);
		}
		reg = 1; 
	} 
	
	int char_count = 0;
	char curr[2];
	return_val = read(0, curr,1);
	checkError(return_val);

	int word_index = 0;
	int arr_index = 0;
	
	while(return_val > 0){
		word[word_index++] = curr[0];
		char_count++;
	
		if(char_count > buffersize-2 || reg){
			char* tmp = realloc(word, sizeof(char)*(word_index+2));
			if(tmp != NULL) word = tmp;
			else{
                free(word);
                write(2, "Error: cannot allocate memory properly.", char_count);
                exit(1);
			}
		}

		if(curr[0] == ' '){
			words[arr_index++] = word;
			
			if(char_count > buffersize-2 || reg){
				char** tmp = realloc(words, sizeof(char*)*(arr_index+2));
            	if(tmp != NULL){
                    words = tmp;
                    word = NULL;
                    word = (char*)malloc(sizeof(char));
                    if(word == NULL){
                        write(2, "Error: cannot allocate memory properly.", char_count);
                        exit(1);
					}
           		}
				else {
                    free(words);
                    write(2, "Error: cannot allocate memory properly.", char_count);
                    exit(1);	
					}
			}
			else word = &file[char_count];
			
			word_index = 0;
		}
		return_val = read(0, curr+1, 1);
		checkError(return_val);

		if(return_val == 0 && curr[0] == ' ') break;
		else if (return_val == 0){
			curr[0] = ' ';
			return_val = 1;
		}
		else if(curr[1] == ' ' && curr[0] == ' '){
			while(curr[0] == ' '){
				return_val = read(0, curr, 1);
				checkError(return_val);
			}
		}else curr[0] = curr[1];
	}

//////////////////	
	if(argc == 2 && argv[1][1] == 'f') qsort(words, arr_index, sizeof(char*), compare_flag);
	else qsort(words, arr_index, sizeof(char*), compare);


	for(int i = 0; i < arr_index; i++){
		for(int j = 0;;j++){
			if(write(1, words[i]+j, 1) <=0){
				write(2, "Error: cannot write to output.", arr_index);
				exit(1);
			}			
			if(words[i][j] == ' ') break;
		}
	}

	for(int i = 0; i < arr_index; i++){
		free(words[i]);
	}
	free(words);
	exit(0);
}
