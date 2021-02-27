#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include<sys/wait.h> 

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main()
{
	printf("WELCOME TO RADMAN'S SHELL \n");
	pid_t pid;
	int lop = 0;
 	char command[20];
 	char temp[20]; 
 	char temp1[20];
 	char content;
 	char *cmd = malloc(20*sizeof(char));
	char *argv[20];
	for (int i = 0 ; i<20; i++){
		argv[i]= malloc(20*sizeof(char));
	}
	int argSize;
	int fd[2];
	int fd1[2];
	bool check = false;
	bool twoPart;
	int mood = 2;
	int N;
	int len;
	/*while (lop == 0){
		check = false;
		twoPart = false;
		argSize = 0;
		printf("\n isp$ ");
		bzero(command, 20);
    		scanf("%[^\n]%*c", command); 
    		if (pipe(fd) == -1) { fprintf(stderr,"Pipe failed"); return 1;}
    		for (int i = 0; command[i] != '\0' && twoPart == false; i++){
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
 			else if (command[i] == '|'){
 				twoPart = true;
				pid = fork();
				if (pid < 0) { fprintf(stderr, "Fork failed"); return 1; }
				if (pid == 0){ 
					argv[argSize] = NULL;
					dup2(fd[WRITE_END], STDOUT_FILENO);
    					close(fd[WRITE_END]);
    					close(fd[READ_END]);
    					execvp(cmd, argv);
    					fprintf(stderr, "Failed to execute first '%s'\n", cmd);
					exit(1);
				}
				else {
					wait(NULL);
					pid = fork();
					if (pid < 0) { fprintf(stderr, "Fork failed"); return 1; }
					if (pid == 0){
						bzero(cmd, 20);
						argSize = 0;
						for (int j = ++i; command[j] != '\0'; j++){
							if (command[j] == ' ' || command[j] != ' ' ){
    								if (command[j] != ' '){
    									while (command[j] != '\0' && command[j] != ' '){
    										strncat(cmd, &command[j], 1); 
    										j++;
    									}
    								}
    								else{
    									while (command[j] == ' ')
    										j++;
    									while (command[j] != '\0' && command[j] != ' '){
    										strncat(cmd, &command[j], 1); 
    										j++;
    									}
    								}
    								strcpy(*(argv + argSize), cmd);
    								argSize++;
    							}
    							else if (command[i] != ' '){
								strncat(temp, &command[i], 1); 
								strcpy(*(argv + argSize), temp);
								check = true;
							}
							else{
								argSize++;
								bzero(temp, 20);
							}				
						}
						if (check){
							argSize++;
							argv[argSize] = NULL;
						}
						else
	    						argv[argSize] = NULL;
    						dup2(fd[READ_END], STDIN_FILENO);
						close(fd[READ_END]);
						close(fd[WRITE_END]);
	    					execvp(cmd, argv);
	    					fprintf(stderr, "Failed to execute second '%s'\n", cmd);
	    					exit(1);
    					}
    					else{
    						int status;
       					close(fd[READ_END]);
						close(fd[WRITE_END]);
       					waitpid(pid, &status, 0);
       					bzero(cmd, 20);
       				}
    				}
    			}
			else if (command[i] != ' ' && command[i] != '|'){
				strncat(temp, &command[i], 1); 
				strcpy(*(argv + argSize), temp);
			}
			else{
				argSize++;
				bzero(temp, 20);
			}
		}
		bzero(temp, 20);
		if (twoPart == false){
			argSize++;
			argv[argSize] = NULL;
			pid = fork();
			if (pid  == 0){
				if (execvp(cmd, argv) == -1) {
		    			// Print error if command not found
		    			printf("comment does not find \n");
		    		}
		    	}
		    	wait(NULL);
		}
		bzero(cmd, 20);
	}*/
	/*
		tapping mood 
	*/
	while (lop == 0){
		len = -1;
		check = false;
		twoPart = false;
		argSize = 0;
		printf("\n isp$ ");
		bzero(command, 20);
    		scanf("%[^\n]%*c", command);
		for (int i = 0; command[i] != '\0' && twoPart == false; i++){
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
    			else if (command[i] == '|'){
    				if (pipe(fd) == -1) { fprintf(stderr,"Pipe failed"); return 1;}
    				if (pipe(fd1) == -1) { fprintf(stderr,"Pipe failed"); return 1;}
    				twoPart = true;
				pid = fork();
				if (pid < 0) { fprintf(stderr, "Fork failed"); return 1; }
				if (pid == 0){ 
					argv[argSize] = NULL;
					len = dup2(fd[WRITE_END], STDOUT_FILENO);
    					close(fd[WRITE_END]);
    					close(fd[READ_END]);
					close(fd1[WRITE_END]);
    					close(fd1[READ_END]);
					if (len < 0) {
    						perror("read error");
					}
    					execvp(cmd, argv);
    					fprintf(stderr, "Failed to execute first '%s'\n", cmd);
					exit(1);
				}
				else {
					wait(NULL);
					len = read(fd[READ_END], temp, 1024);
					close(fd[WRITE_END]);
					if (len < 0) {
						perror("read error");
					}
					printf("temp: %s \n", temp);
					len = write(fd1[WRITE_END], temp, 1024);
					if (len < 0) {
						perror("read error");
					}
					close(fd1[WRITE_END]);
					printf("write: %s \n", fd1);
					pid = fork();
					if (pid < 0) { fprintf(stderr, "Fork failed"); return 1; }
					if (pid == 0){
						len = read(fd1[READ_END], temp1, 1024);
						close(fd1[WRITE_END]);
	    					close(fd1[READ_END]);
	    					if (len < 0) {
							perror("read error");
						}
						printf("temp1: %s \n", temp1);*/
						bzero(cmd, 20);
						argSize = 0;
						for (int j = ++i; command[j] != '\0'; j++){
							if (command[j] == ' ' || command[j] != ' ' ){
    								if (command[j] != ' '){
    									while (command[j] != '\0' && command[j] != ' '){
    										strncat(cmd, &command[j], 1); 
    										j++;
    									}
    								}
    								else{
    									while (command[j] == ' ')
    										j++;
    									while (command[j] != '\0' && command[j] != ' '){
    										strncat(cmd, &command[j], 1); 
    										j++;
    									}
    								}
    								strcpy(*(argv + argSize), cmd);
    								argSize++;
    							}
    							else if (command[i] != ' '){
								strncat(temp, &command[i], 1); 
								strcpy(*(argv + argSize), temp);
								check = true;
							}
							else{
								argSize++;
								bzero(temp, 20);
							}				
						}
						if (check){
							argSize++;
							argv[argSize] = NULL;
						}
						else
	    						argv[argSize] = NULL;
						printf("cmd: %s \n", cmd);
						for (int i = 0; i <= argSize; i++){
				    			printf("argv: %s \n", argv[i]);
				    			printf("size: %d \n", strlen(argv[i]));
				    		}
    						//len = dup2(fd1[READ_END], STDIN_FILENO);
						//close(fd1[READ_END]);
						//close(fd1[WRITE_END]);
    						/*if (len < 0) {
	    						perror("read error");
						}*/
	    					execvp(cmd, argv);
	    					fprintf(stderr, "Failed to execute second '%s'\n", cmd);
	    					exit(1);
    					}
    					else{
    						int status;
       					close(fd[READ_END]);
						close(fd[WRITE_END]);
						close(fd1[READ_END]);
						close(fd1[WRITE_END]);
       					waitpid(pid, &status, 0);
       					bzero(cmd, 20);
       				}
				}
    			}
    			else if (command[i] != ' ' && command[i] != '|'){
				strncat(temp, &command[i], 1); 
				strcpy(*(argv + argSize), temp);
			}
			else{
				argSize++;
				bzero(temp, 20);
			}
		}
		bzero(temp, 20);
		if (twoPart == false){
			argSize++;
			argv[argSize] = NULL;
			pid = fork();
			if (pid  == 0){
				if (execvp(cmd, argv) == -1) {
		    			// Print error if command not found
		    			printf("comment does not find \n");
		    		}
		    	}
		    	wait(NULL);
		}
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
