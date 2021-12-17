#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
/*
int main(int argc, char** argv) {
    int fd[2];
    if (pipe(fd) != 0) {
       printf ("Error creating pipe. %s", strerror(errno));
       exit(errno);
    }

    int pid = fork();
    if (pid == -1) {
       printf ("Error creating pipe. %s", strerror(errno));
       exit(errno);
    } else if (pid == 0) {
       //child
       * Replace standard output of child process with read end of the pipe *
        dup2(fd[0], 0);

        * Close the write end of the pipe in child process.It is not used *
         close(fd[1]);         * Close the read end of the pipe in child process. We have a copy o it in file descriptor 0*
         close(fd[0]);
		 execlp("wc", "wc", "-c", NULL);
     } else {
        //parent
        * Replace standard output of parent process with write end of the pipe *
        dup2(fd[1], 1);

        * Close the read end of the pipe in parent process.It is not used *
         close(fd[0]);

         * Close the write end of the pipe in child process.We have a copy of it in file descriptor 1*
          close(fd[1]);

          execlp("cat", "cat" , "/tmp/file1" , NULL);
     }
}
*/



#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

void execute_command(char* command) {
    int i = 0;
    int argument_count = 0;

    /* Strip white spaces */
    while (command[i] == ' ') {
        i++;
    }
    command = command + i;

    i = 0;

    /* Count the number of arguments to the command */
    while (command[i] != '\0') {
         if (command[i] == ' ')
             argument_count++;
         i++;
     }

    char** argv = calloc(argument_count + 2, sizeof(char*));
    char* argument = NULL;
    i = 0;
    while ((argument = strsep(&command, " ")) != NULL) {
       if (strlen(argument) != 0) {
           argv[i] = calloc(strlen(argument) + 1, sizeof(char));
           strncpy(argv[i], argument, strlen(argument));
       }
       i++;
    }    /* Need to set the last argument as NULL */
    argv[i] = NULL;

    if (execvp(argv[0], argv) != 0) {
        fprintf(stderr, "Error creating pipe. %s",         strerror(errno));
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf ("Usage pipe <commands to execute>");
        exit(-1);
    }

    int* fd = calloc(2, sizeof(int));
    if (pipe(fd) != 0) {
        printf ("Error creating pipe. %s", strerror(errno));
        exit(errno);
    }
    const char* command = argv[1];
    int prev_commands_length = 0;
    int i = 0;
    int quote_begin = 0;
    while (1) {
        if (command[i] == '|') {
            /*  End of a command */
            int pid = fork();
            if (pid == -1) {
                printf("Error creating pipe. %s", strerror(errno));
                    exit(errno);
             } else if (pid > 0) {
                 /*
                     Parent will take care of command seen.
                     And send its output to child.
                  */
                  dup2(fd[1], 1);
                  close(fd[0]);
                  close(fd[1]);
                  char* current_command = calloc(i + 1 - prev_commands_length, sizeof(char));
                  strncpy(current_command, command + prev_commands_length, i - prev_commands_length);
                  execute_command(current_command);
              } else {
                  dup2(fd[0], 0);
                  close(fd[1]);
                  close(fd[0]);                  /* Create new pipe for chaining the next two commands */
                   fd = calloc(2, sizeof(int));
                   pipe(fd);
              }
                    prev_commands_length = i + 1;
          } else if (command[i] == '\0') {
              char* current_command = calloc(i + 1 - prev_commands_length, sizeof(char));
              strncpy(current_command, command + prev_commands_length, i - prev_commands_length);
              execute_command(current_command);
          }          i++;
     }
 }
