#include "shell.h"

void handle_ctrl_c(int signum){
  exit(0);
}

int execute_basic_commands(Char_Ptr_To_Ptr command){
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

int execute_built_in_commands(Char_Ptr_To_Ptr command){
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

void __check_error(int exit_code, Char_Ptr error){
  if(exit_code < 0){
    printf("Command not found: ");
    set_color(RED);
    printf("%s\n", error);
    exit(0);
  }
}

int __execute_first_command(int * pipefd, Char_Ptr_To_Ptr command){
  int exit_code = 0;
  close(pipefd[READ]); 
  dup2(pipefd[WRITE], 1); 
  close(pipefd[WRITE]); 
  exit_code = execvp(command[0], command);
  __check_error(exit_code, command[0]);
  return exit_code;
}

int __execute_second_command(int * pipefd, Char_Ptr_To_Ptr command){
  int exit_code = 0;
  close(pipefd[WRITE]); 
  dup2(pipefd[READ], 0); 
  close(pipefd[READ]); 
  exit_code = execvp(command[0], command);
  __check_error(exit_code, command[0]);
  return exit_code;
}

void __execute_pipe(Char_Ptr_To_Ptr* commands, int  command_count){
  if (command_count == 0)
  {
    return;
  }    
  int fd[2];
  if (pipe(fd) == -1) {
    fprintf(stderr, "error creating pipe\n");
  }
  int pid_2 = fork();
  if (pid_2 == -1) {
    fprintf(stderr, "error forking process\n");
  }
  if (!pid_2) {
    close(fd[0]);
    dup2(fd[1], 1);
    __execute_pipe(commands, command_count - 1);
    int exit_code = execvp(commands[command_count -1][0], commands[command_count -1]);
    __check_error(exit_code, commands[command_count -1][0]);
  }
  close(fd[1]);
  dup2(fd[0], 0);
  wait(&pid_2);
  int exit_code = execvp(commands[command_count][0], commands[command_count]);
  __check_error(exit_code, commands[command_count][0]);
}

void execute_pipes(Char_Ptr_To_Ptr* commands, int command_count) 
{
  int pid_1 = fork(); 
  if(!pid_1) {
    __execute_pipe(commands, command_count)    ;
  } else {
    wait(&pid_1);
  }
}
