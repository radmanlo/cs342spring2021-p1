#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    	int M = atoi(argv[1]);
    	char character;
    	for (int i = 0; i < M; i++){
        	scanf("%c", &character);
        	printf("characters: %c \n", character);
    }
}
