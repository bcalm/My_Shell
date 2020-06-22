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
  return 1;
}