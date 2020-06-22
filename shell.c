#include "shell.h"

void handle_ctrl_c(int signum){
  exit(0);
}

int execute_command(Char_Ptr_To_Ptr command){
  int pid = fork();
  int exit_code = 0;
  signal(SIGINT, SIG_IGN);
  if(pid < 0)
  {
    printf("Something went wrong system brake...\n");
  }
  else if (pid == 0)
  {
    signal(SIGINT, handle_ctrl_c);
    exit_code = execvp(command[0], command);
    if(exit_code < 0){
      printf("Command not found: ");
      set_color(RED);
      printf("%s\n", command[0]);
      set_color(RESET);
    }

  }
  else
  {
    wait(&pid);
   }
  return exit_code;
}

int handle_built_in(Char_Ptr_To_Ptr command){
  if (strcmp(command[0], "exit") == 0)
  {
    exit(0);
  }
  if (strcmp(command[0], "cd") == 0)
  {
    chdir(command[1]);
    return 1;
  }
  return 0;
}

int execute_pipe(Char_Ptr_To_Ptr command, Char_Ptr_To_Ptr pipe_args){
  int exit_code = 0;
  int pipefd[2];  
  pid_t pid_1, pid_2; 
  
  if (pipe(pipefd) < 0) { 
    printf("\nPipe could not be initialized"); 
    return 1; 
  } 

  pid_1 = fork(); 
  if (pid_1 == 0) { 
    close(pipefd[0]); 
    dup2(pipefd[1], STDOUT_FILENO); 
    close(pipefd[1]); 

    exit_code = execvp(command[0], command);
    if (exit_code < 0) { 
      printf("Command not found: ");
      set_color(RED);
      printf("%s\n", command[0]);
      exit(0);
    } 
  } else { 
      pid_2 = fork(); 
      if (pid_2 == 0) { 
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO); 
        close(pipefd[0]); 
        exit_code = execvp(pipe_args[0], pipe_args);
        if (exit_code < 0) { 
          printf("Command not found: ");
          set_color(RED);
          printf("%s\n", pipe_args[0]);
          exit(0);
        } 
      } else { 
        wait(&pid_1); 
      } 
    }
  return exit_code; 
}