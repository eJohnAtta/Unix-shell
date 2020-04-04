#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define cmd_number 4

char* username;
char cmd[1024];
char cwd[1024];
char p_cmd1[1024];
char p_cmd2[110];

char* my_commands[] = { "exit",
                        "cd",
                        "help",
                        "pwd"
                        };

char* argv[];
int BG=0,space=0;


void intialize_shell(){
    printf("Shell Intialization\n");
    username = getenv ("USER");
    if (username!=NULL)
        printf ("User   ##%s##  is Ready",username);
    printf("\nStart your commands..\n");
    sleep(1);
}

char* direc(){
    getcwd(cwd, sizeof(cwd));
    return (cwd);
}

void line_setup(){
    printf("\n%s @ %s\t>> ",username,direc());
}


void command_get(){
    FILE* fptr = fopen("log.txt","a");
    line_setup();
    //scanf("%s", cmd);
    gets(cmd);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fptr, "%d-%02d-%02d %02d:%02d:%02d >> %10s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,cmd);
    fclose(fptr);
}

int command_text(){
    int i=0 , x=0 , y=0;
    *p_cmd1="";*p_cmd2="";
    for(i=0;i<strlen(cmd);i++){
        if( cmd[i]!=' ' && cmd[i]!='/'){
            p_cmd1[x]=cmd[i];
            ++x;
        }

         if ((cmd[i]==' ') || (cmd[i]=='/')){
            space=1;
            if(i==0) continue;
            for(int j=i+1; j<strlen(cmd);j++){
                p_cmd2[y] =cmd[j];
                ++y;
            }
            i=0;
            break;

        }}
    for(i=0;i<cmd_number;i++){
        char tmp[10];
        strcpy(tmp,my_commands[i]);
        if(strcmp(p_cmd1,tmp)==0)   {return (i+1);}
        else if (i == cmd_number-1) {return 0;}
        }}

void reset(){
    memset(p_cmd1, 0, sizeof(p_cmd1));
    memset(p_cmd2, 0, sizeof(p_cmd2));
    space=0;
}

void ex_cmd(){
    argv[0]=p_cmd1;
    if (!strcmp(p_cmd2,"&")){   //Background
        BG=1;
        argv[1]=NULL;
    }
    else if (space==0)argv[1]=NULL;
    else {argv[1]=p_cmd2;argv[2]=NULL;}

}

void help_cmd(){
    printf("\n\tHere we are introducing the supported commands\n"
            "\tthe shell can implement executable commands and set of\n"
            "\tbuiltin functions:\n"
            "\tbuiltin functions: 1.cd to change the shell working directory\n"
            "\t                   2.pwd to determine the current directory\n"
            "\t                   3.exit to terminate the shell\n"
            "\texecutable functions: 1.ls to list the current directory components\n"
            "\t                       it can take arguments like -l , -t , -X & etc\n"
            "\t                      2.run any program like firefox or gedit\n"
            "\t                      3.Background execution using % operand\n"
            "\t Note: the shell can implement ALL the executable commands!\n"
            "\t we are looking forward to develope it more and more\n\n \t\t\t\tThanks for using it\n"

                                                                );
}

void command_process(int sel){
    switch (sel){
    case 1 : //exit
        exit(0);
        break;
    case 2 : //cd
        chdir(p_cmd2);
        break;
    case 3 : //help
        help_cmd();
        break;
    case 4 :
        printf("%s\n",direc());
        break;
    case 0 :
        ex_cmd();   //check if its exc
        t_fork();
        break;
    default: break;
    }
    reset();}

void s_hand(){
    FILE* fptr = fopen("log.txt","a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fptr, "%d-%02d-%02d %02d:%02d:%02d >> CHILD PROCESS IS TERMINATED!!!!\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(fptr);
}

void t_fork(){
  pid_t pid, wpid;
  signal(SIGCHLD, s_hand);
  int status=0;
  pid = fork();
  if (pid == 0 ) {   // Child process
        if (execvp(argv[0], argv) == -1) {
            printf("Error in child Execution: Check Syntax\n");
            }}
  else if (pid < 0) {printf("Error in Forking");} // Error forking

  else if(pid > 0) {        // Parent process
          do {
            if (BG){continue;}
            else wpid=waitpid(pid, &status, WUNTRACED);}
            while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
 }



void main() {
    intialize_shell();
    while(1){
    command_get();
    command_process(command_text());
}}
