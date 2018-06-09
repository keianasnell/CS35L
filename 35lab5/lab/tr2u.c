#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        write(2, "Error: incorrect number of arguments in %s", strlen(argv[0]));
        exit(1);
    }

    char* from = argv[1];
    char*to = argv[2];
    if(strlen(from) != strlen(to)){
        write(2, "Error: arguments be the same length", strlen(argv[2]));
        exit(1);
    }

	for(int i = 0; i < strlen(from); i++){
        for(int j = i + 1; j < strlen(from); j++){
            if(from[i] == from[j]){
                write(2, "Error: cannot have duplicate byte in argument", from[i]);
                exit(1);
            }
        }
    }

	int x = 0;
	char curr;
	while(read(0, &curr, 1) != 0){
		for(int i = 0; i < strlen(from); i++){
			if(curr == from[i]){
				write(1, to+i, 1);
				x = 1;
				break;
			}
			else x = 0;
		}
		if(!x) write(1, &curr, 1);
	}

	
}
