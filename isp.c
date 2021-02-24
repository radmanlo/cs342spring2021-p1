#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	printf("WELCOME TO RADMAN'S SHELL \n");
	int lop = 0;
 	char command[20] = "";
 	char cmd[] = "";
	char argv[20][20];
	int argSize;
	while (lop == 0){
		//argSize = 0;
		printf("isp$ ");
    		scanf("%[^\n]%*c", command); 
    		printf("Your command: ");
    		printf("%s \n", command);
    		printf("cmd: %s \n", cmd);
    		strncat(argv[0], &command, 1); 
    		printf("%s \n", argv[0]);
    		for (int i = 0; command[i] != 0; i++){
    			if (i == 0 && (command[i] == ' ' || command[i] != ' ' )){
    				if (command[i] != ' '){
    					while (command[i] != ' '){
    						strncat(cmd, &command[i], 1); 
    						i++;
    					}
    				}
    				else{
    					while (command[i] == ' ')
    						i++;
    					while (command[i] != 0){
    						strncat(cmd, &command[i], 1); 
    						i++;
    					}
    				}
    			}
    			else if (command[i] == ' '){
    				argSize++;
    			}
    			else{
    				strncat(argv[argSize], &command[i], 1); 
    			}
    		}
    		printf("cmd: %s \n", cmd);
    		for (int i = 0; argv[i] != 0; i++)
    			printf("argv: %s \n", argv[i]);
    		printf("\n");
    		//execvp(cmd, argv);*/
	}
}
