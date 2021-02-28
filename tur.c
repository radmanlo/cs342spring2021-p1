#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * Turan Mert Duran
 * 21601418
 * CS 342 Project 1
 * This program is a new designed shell
 * It supports two command executions
 * This code demonstrates how pipes
 * work and how data flow can be accessed
 * by main process in tapped mode
 */
int main(int argc, char *argv[]) {
    printf("Welcome to Turan Mert's shell >>");
    int mode = 2; // NORMAL MODE, 1 FOR TAPPED MODE
    int byteCnt = 4096; // READ & WRITE BYTE COUNT AT A TIME
    int chckPr = 0;
    char str[1000]; // INPUT STR
    char filePath[100]; // FILE PATH 1
    char filePathT[100]; // FILE PATH 2
    char* path[20]; // ARGUMENTS 1
    char* pathT[20]; // ARGUMENTS 2
    char* token; // FOR READ AND WRITE IN TAPPED MODE
    int writeC; // HOW MANY WRITE OCCUR COUNTER
    int readC; // HOW MANY READ OCCUR COUNTER
    int charC; // HOW MANY CHAR PASSED DURING TAPPED MODE PROCESS

    //GET MODE AND BYTES
    if(argc > 2){
        byteCnt = atoi(argv[1]);
        mode = atoi(argv[2]);
    }
    while(1){
        writeC = 0;
        readC = 0;
        charC = 0;

        //GETTING USER INPUT
        fgets(str, 1000, stdin);

        //STARTING TIME AFTER GETTIN USER INPUT
        struct timeval start, end;
        gettimeofday(&start, NULL);

        //CHECKİNG FOR ISP IF IT COMES CHANGING MODE
        char subStr[6];
        memcpy( subStr, &str[0], 5);
        subStr[5] = '\0';
        //CHECKİNG FOR ISP IF IT COMES CHANGING MODE
        if(strcmp(subStr, "./isp") == 0){
            token = strtok(str, " "); //isp
            token = strtok(NULL, " "); // byte count
            byteCnt = atoi(token);
            token = strtok(NULL, " "); //mode
            mode = atoi(token);
            printf("Byte count: %d, mode: %d\n>>", byteCnt, mode);
            continue;
        }
        //EXIT FOR QUIT LOOP END TERMINAL
        if( strcmp(str, "exit") == 0)
        {
            printf("Exit");
            break;
        }
        // DIVIDING USER INPUT INTO CHAR ARRAYS
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
            //REMOVING NEW LINES
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
            // IF TAPPED MODE IS ON
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
                        chckPr = 1;
                    }
                    close(fd[1]);
                    exit(1);
                }else {
                    //PARENT PROCESS
                    int fdT[2];
                    pipe(fdT);
                    pid_t childT = fork();
                    if(childT == 0){
                        //SECOND CHILD PROCESS
                        close(fd[0]);
                        close(fd[1]);
                        close(fdT[1]);
                        dup2(fdT[0], STDIN_FILENO);
                        close(fdT[0]);
                        if(execvp(filePathT, pathT)<0){
                            memmove (filePathT, filePathT+5, strlen (filePathT+5) + 5);
                            execvp(filePathT, pathT);
                        }
                        exit(1);
                    }else{
                        //PARENT
                        close(fd[1]);
                        close(fdT[0]);
                        int hmB = 0;
                        while(read(fd[0], &buffer, byteCnt) > 0){
                            writeC++;
                            readC++;
                            write(fdT[1], &buffer, byteCnt);
                            charC = charC + byteCnt;
                        }
                        close(fd[0]);
                        close(fdT[1]);
                        wait(NULL);
                        printf(">>");
                    }
                    //CLOSING PIPES
                    close(fd[0]);
                    close(fdT[1]);
                    close(fd[1]);
                    close(fdT[0]);
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
                        //PARENT PROCESS
                        close(fd[1]);
                        close(fd[0]);

                        wait(NULL);
                        printf(">>");
                    }
                }
            }
        }else{
            //ONE COMMAND SUPPORT
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
                //CHILD PROCESS
                if(execvp(filePath, path)<0){
                    memmove (filePath, filePath+5, strlen (filePath+5) + 5);
                    execvp(filePath, path);
                }
                exit(1);

            }else{
                //PARENT MAIN PROCESS
                wait(NULL);
                printf(">>");

            }
        }
        //RETURN HOW MANY SECONDS PASSED AFTER STARTING EXECUTION
        gettimeofday(&end, NULL);
        double time_taken = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
        printf("Passed time for execution: %f sec\n>>", time_taken);
    }
}

