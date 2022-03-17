#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFSIZE 256
int parse_line(char* str){
    printf("%s", str);
    return 0;
}
// int simple_cmd(char *argv[]){

// }
void removeComments(char * buffer, int index){
    for(int i = index; i<strlen(buffer); i++){
        buffer[i] = '\0';
    }
}
void cleanArgs(char ** args){
    for(int i=0; i<BUFSIZE; i++){
        args[i] = NULL;
    }
}
void cleanBufferInput(char *buffer){
    for(int i=0; i<strlen(buffer); i++){
         buffer[i] = '\0';
    }
}
void displayArgs(char ** args,int nbArgs){
    printf("=== [displayArgs: start] ====\n");
    for(int i = 0; i<nbArgs; i++){
        printf("value : %s", args[i]);
        printf("\n");
    }
    printf("=== [displayArgs: end] ====\n");
}
int main(){
    char buffer[BUFSIZE];
    char * strOutput = NULL;
    while(1){
        printf("$%s", buffer);
        strOutput = fgets(buffer,sizeof buffer,stdin);
        unsigned int bufLen = strlen(buffer);
        buffer[bufLen-1] = '\0';
        if(strcmp(buffer, "exit") == 0){
            exit(0);
        }
        char * commentFoundInBuffer =strpbrk(buffer,"#");
        if(commentFoundInBuffer!=NULL){
            int indexComment = commentFoundInBuffer - buffer;
            removeComments(buffer,indexComment);
            printf(" ==== comments removed ====");
            printf("\n");
        }
        char * mArgs[BUFSIZE];
        int nbArgs = 0;
        char * equalSignFound = strpbrk(buffer, "=");
        char bufferCpy [strlen(buffer)];
        strcpy(bufferCpy, buffer);
        if(equalSignFound!=NULL){
            // printf(" equal sign => %s", equalSignFound);
            // printf("\n");
            // printf("bufferCpy => %s", bufferCpy);
            // printf("\n");
            // printf(" value : %s ", buffer);
            // printf("\n");
            // printf("nb of args : %d", nbArgs);
            // printf("\n");
            char * token = strtok(bufferCpy, "=");
            while(token!=NULL){
                printf("\n");
                mArgs[nbArgs] = token;
                token = strtok(NULL, "=");
                nbArgs++;
            }
            displayArgs(mArgs,nbArgs);
            if(setEnv(mArgs[0], mArgs[1], 0)==-1){
                // printf("%s ")
            }
        }else{
            printf("\nok je suis en dehors");
            // char bufferCpy [strlen(buffer)];
            // strcpy(bufferCpy, buffer);

            char * token = strtok(bufferCpy, " ");
            while(token!=NULL){
                mArgs[nbArgs] = token;
                token = strtok(NULL, " ");
                nbArgs++;
            }

            printf("nb of args : %d", nbArgs);
            printf("\n");

            displayArgs(mArgs,nbArgs);

            printf("bufferCpy after strtok : %s ", bufferCpy);
            printf("\n");
            printf("buffer befor cleaning : %s", buffer);
            printf("\n");

        }
        cleanArgs(mArgs);
        cleanBufferInput(buffer);
    }
    if(strOutput == NULL){
        printf("ok problème de lecture de l'entrée : je quitte le programme");
        exit(0);
    }
    return 0;
}