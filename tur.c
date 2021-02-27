#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main (){
    printf("Welcome to Turan's shell >>");
    int mode = 2; // NORMAL MODE, 1 FOR TAPPED MODE
    int byteCnt = 2;
    char str[1000];
    char filePath[100];
    char filePathT[100];
    char* path[20];
    char* pathT[20];
    char* token;
    int writeC;
    int readC;
    int charC;
    if(argc > 2){
        byteCnt = atoi(argv[1]);
        mode = atoi(argv[2]);
    }
    while(1){
        writeC = 0;
        readC = 0;
        charC = 0;
        fgets(str, 1000, stdin);
        struct timeval start, end;

        gettimeofday(&start, NULL);

        char subStr[6];
        memcpy( subStr, &str[0], 5);
        subStr[5] = '\0';

        if(strcmp(subStr, "./isp") == 0){
            token = strtok(str, " "); //isp
            token = strtok(NULL, " "); // byte count
            byteCnt = atoi(token);
            token = strtok(NULL, " "); //mode
            mode = atoi(token);
            printf("Byte count: %d, mode: %d\n>>", byteCnt, mode);
            continue;
        }
        if( strcmp(str, "exit") == 0)
        {
            printf("Exit");
            break;
        }

        token = strtok(str, " ");
        int ctr = 0;
        int ctrT = 0;
        int divisionIndex = 0;
        while (token != NULL)  {
            if(divisionIndex != 0){
                pathT[ctrT] = token;
                token = strtok(NULL, " ");
                ctrT++;
            }else{
                if(strcmp(token, "|") == 0){
                    divisionIndex = ctr;
                    token = strtok(NULL, " ");
                }else{
                    path[ctr] = token;
                    ctr++;
                    token = strtok (NULL, " ");
                }
            }
        }
        path[ctr] = NULL;
        pathT[ctrT] = NULL;

        //  TWO COMMANDS SUPPORT
        if(divisionIndex != 0){

            strcpy(filePath,"/bin/");
            strcat(filePath, path[0]);
            strcpy(filePathT,"/bin/");
            strcat(filePathT, pathT[0]);
            for(int i = 0; i < ctrT; i++){
                for(int j = 0; j < strlen(pathT[i]); j++){
                    if(pathT[i][j] =='\n'){
                        pathT[i][j] ='\0';
                    }
                }
            }
            for( int i=0; i < strlen(filePathT); i++){
                if( filePathT[i] =='\n'){
                    filePathT[i] ='\0';
                }
            }
            for(int i = 0; i < ctr; i++){
                for(int j = 0; j < strlen(path[i]); j++){
                    if(path[i][j] =='\n'){
                        path[i][j] ='\0';
                    }
                }
            }
            for( int i=0; i < strlen(filePath); i++){
                if( filePath[i] =='\n'){
                    filePath[i] ='\0';
                }
            }
            if(mode == 2){
                int fd[2];
                pipe(fd);

                //TAPPED MODE
                char buffer[byteCnt];
                pid_t child = fork();
                if( child == 0) {
                    // FIRST CHILD
                    close(fd[0]);
                    dup2(fd[1], STDOUT_FILENO);
                    if(execvp(filePath, path)<0){
                        memmove (filePath, filePath+5, strlen (filePath+5) + 5);
                        execvp(filePath, path);
                    }
                    exit(1);
                }else {
                    //wait(NULL);
                    int fdT[2];
                    pipe(fdT);
                    pid_t childT = fork();
                    if(childT == 0){
                        //SECOND CHILD

                        close(fdT[1]);
                        dup2(fdT[0], STDIN_FILENO);
                        close(fdT[0]);

                        if(execvp(filePathT, pathT)<0){
                            memmove (filePathT, filePathT+5, strlen (filePathT+5) + 5);
                            execvp(filePathT, pathT);
                        }
                        exit(1);

                    }else{byteCnt
                        //PARENT
                        close(fd[1]);
                        //printf("Naber");
                        while(read(fd[0], buffer, byteCnt)> 0){
                            //printf("Selam");
                            charC = charC + byteCnt;
                            writeC++;
                            readC++;
                            write(fdT[1], buffer, byteCnt   );
                        }
                        close(fd[0]);
                        close(fdT[1]);
                        //wait(NULL);
                        printf(">>");
                    }
                    wait(NULL);
                }
                printf("\ncharacter-count: %d\nread-call-count: %d\nwrite-call-count: %d\n",charC, readC, writeC);
            }else{
                // NORMAL MODE
                //CREATING PIPES
                int fd[2];
                pipe(fd);

                pid_t child = fork();
                if( child == 0) {
                    // FIRST CHILD
                    close(fd[0]);
                    dup2(fd[1], STDOUT_FILENO);
                    if(execvp(filePath, path)<0){
                        memmove (filePath, filePath+5, strlen (filePath+5) + 5);
                        execvp(filePath, path);
                    }
                    exit(1);
                }else {
                    //wait(NULL);
                    pid_t childT = fork();
                    if (childT == 0) {
                        //SECOND CHILD

                        close(fd[1]);
                        dup2(fd[0], STDIN_FILENO);

                        if(execvp(filePathT, pathT)<0){
                            memmove (filePathT, filePathT+5, strlen (filePathT+5) + 5);
                            execvp(filePathT, pathT);
                        }
                        exit(1);
                    } else{
                        //PARENT
                        close(fd[1]);
                        close(fd[0]);

                        wait(NULL);
                        printf(">>");
                    }
                    wait(NULL);
                }
            }



        }else{

            strcpy(filePath,"/bin/");
            strcat(filePath, path[0]);
            for(int i = 0; i < ctr; i++){
                for(int j = 0; j < strlen(path[i]); j++){
                    if(path[i][j] =='\n'){
                        path[i][j] ='\0';
                    }
                }
            }
            for( int i=0; i < strlen(filePath); i++){
                if( filePath[i] =='\n'){
                    filePath[i] ='\0';
                }
            }
            pid_t child = fork();
            if( child == 0){
                //wait(NULL);
                //puts(filePath);
                //puts(path);
                //puts(filePath);
                if(execvp(filePath, path)<0){
                    memmove (filePath, filePath+5, strlen (filePath+5) + 5);
                    execvp(filePath, path);
                }
                exit(1);

            }else{
                wait(NULL);
                printf(">>");

            }
        }

        gettimeofday(&end, NULL);

        double time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;

        printf("Passed time for execution: %f sec\n>>", time_taken);
    }
}
