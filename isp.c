#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	printf("WELCOME TO RADMAN'S SHELL \n");
	int lop = 0;
 	char command[20];
 	char temp[20]; 
 	char *cmd = malloc(20*sizeof(char));
	char *argv[20];
	for (int i = 0 ; i<20; i++){
		argv[i]= malloc(20*sizeof(char));
	}
	int argSize;
	while (lop == 0){
		argSize = 0;
		printf("isp$ ");
    		scanf("%[^\n]%*c", command); 
    		for (int i = 0; command[i] != '\0'; i++){
    			if (i == 0 && (command[i] == ' ' || command[i] != ' ' )){
    				if (command[i] != ' '){
    					while (command[i] != '\0' && command[i] != ' '){
    						strncat(cmd, &command[i], 1); 
    						i++;
    					}
    				}
    				else{
    					while (command[i] == ' ')
    						i++;
    					while (command[i] != '\0' && command[i] != ' '){
    						strncat(cmd, &command[i], 1); 
    						i++;
    					}
    				}
    				strcpy(*(argv + argSize), cmd);
    				argSize++;
    			}
    			else if (command[i] != ' '){
    				strncat(temp, &command[i], 1); 
    				strcpy(*(argv + argSize), temp);
    			}
    			else{
    				argSize++;
    				bzero(temp, 20);
    			}
    		}
    		bzero(temp, 20);
    		argSize++;
		argv[argSize] = NULL;
		pid_t pid = fork();
		if (pid  == 0){
			if (execvp(cmd, argv) == -1) {
	    			// Print error if command not found
	    			printf("comment does not find \n");
	    		}
	    	}
	    	wait(NULL);
	    	bzero(cmd, 20);
	}
}





/*printf("cmd: %s \n", cmd);
    		for (int i = 0; i <= argSize; i++){
    			printf("argv: %s \n", argv[i]);
    			printf("size: %d \n", strlen(argv[i]));	
    		
    		}*/
    		
    				
    				//printf("argv: %s \n", argv[argSize]);
    		
    		//printf("Your command: ");
    		//printf("%s \n", command);
    		//argv[0] = command;
    		//printf("cmd: %s \n", cmd);
    		//strcpy(*(argv + 0), command);
    		//strncat(*(argv, command, 1); 
    		//printf("%s \n", argv[0]);
