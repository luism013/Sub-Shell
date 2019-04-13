#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN_DELIMETERS " \t\r\n\a"
#define DEFAULT_SIZE 1024

char *history[DEFAULT_SIZE];
char *argv[DEFAULT_SIZE];
int hist_count = 0;
int hist_num = 0;
int position = 0;
short isHistNum = 0;
pid_t pid;

void read_line(char *line){
    if(isHistNum){
        line = memcpy(line,history[hist_num-1],DEFAULT_SIZE);
                printf("\n");
        }
        else{
                gets(line);
        }
        isHistNum = 0;
        memcpy(history[hist_count],line,DEFAULT_SIZE);
        hist_count++;
}

void parse_line(char *line,char *argv[]){
    char *token;
    position = 0;
        token = strtok(line,TOKEN_DELIMETERS);
        while(token!=NULL){
            argv[position] = token;
        position++;
            token =strtok(NULL,TOKEN_DELIMETERS);
        }
}

int nat_history(char *argv[]){
    if(position==2){
                hist_num = atoi(argv[1]);
                for(int k = 1; k<=hist_count;k++){
                    if(hist_num == k){
                        isHistNum = 1;
            }
        }
        }        
        if(isHistNum==0){
                for(int i =0; i <hist_count;i++)
                        printf(" %d %s\n",(i+1),history[i]);
    }
    return 1;
}

void nat_ls(char *argv[]){
    system("ls");
    //system("echo *");
}

void nat_help(char *argv[]){
    printf("Welcome to the Sub-Shell Command Line Interface.\n");
    printf("These are the possible commands: ls, help, cd[dir], exit\n");
}

void nat_cd(char *argv[]){
    chdir(argv[1]);
}

void execute(char *argv[]){
    pid = fork();
    if(pid < 0){
        printf("Child process creation failed!");
        exit(1);
    }
    else if (pid == 0) //child
        printf("Suppose to execute a file or something else but I could not get it to work\n");
        //don't know if this creates a zombie process.
    else //parent
        wait(&pid);        
}

int main(int argc, char *argv[]){
    char hist[10];    strcpy(hist, "history");
    char ls[10];    strcpy(ls, "ls");
    char cd[10];    strcpy(cd, "cd");
    char help[10];    strcpy(help, "help");
    int valid = 0;
        char *line = (char*)malloc(DEFAULT_SIZE);
        for(int i = 0;i<DEFAULT_SIZE;i++)
            history[i] = (char*)malloc(DEFAULT_SIZE);
        long size;
        char *buf;
        char *ptr;

    while(1){
        printf("Sub-Shell ->");

        read_line(line);
        parse_line(line,argv);
    if(strcmp(argv[0], "exit") == 0)
            exit(0);
    else if(strcmp(argv[0], hist) == 0){
        nat_history(argv);
    }
    else if(strcmp(argv[0], ls) == 0){
        nat_ls(argv);
    }
    else if(strcmp(argv[0], cd) == 0){
        nat_cd(argv);
    }
    else if(strcmp(argv[0], help) == 0){
        nat_help(argv);
    }
    else{    
        execute(argv);
    }
        for(int j = 0; j< DEFAULT_SIZE;j++){
                argv[j] = NULL;
        }    
    }
}