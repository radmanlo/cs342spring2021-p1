#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
	char* characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    	int M = atoi(argv[1]);
   	int index;
    	char charac;
    	for (int i = 0; i < M; i++){
		index = rand() % 40 ;
		charac = characters[index];
		printf("%c \n", charac);
    	}

}
