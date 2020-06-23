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
  printf("%d\n", exit_code);
    printf("Command not found: ");
    set_color(RED);
    printf("%s\n", error);
    exit(0);
  }
}

int __execute_first_command(int * pipefd, Char_Ptr_To_Ptr command){
  int exit_code = 0;
  close(pipefd[READ]); 
  dup2(pipefd[WRITE], STDOUT_FILENO); 
  close(pipefd[WRITE]); 
  exit_code = execvp(command[0], command);
  __check_error(exit_code, command[0]);
  return exit_code;
}

int __execute_second_command(int * pipefd, Char_Ptr_To_Ptr command){
  int exit_code = 0;
  close(pipefd[WRITE]); 
  dup2(pipefd[READ], STDIN_FILENO); 
  close(pipefd[READ]); 
  exit_code = execvp(command[0], command);
  __check_error(exit_code, command[0]);
  return exit_code;
}

int execute_pipe(Char_Ptr_To_Ptr command, Char_Ptr_To_Ptr pipe_args){
  int exit_code = 0;
  int pipefd[2];  
  int pid_1, pid_2; 
  Char_Ptr_To_Ptr dummy_command1 = malloc(sizeof(Char_Ptr)* 3);
  dummy_command1[0] = malloc(sizeof(Char_Ptr));
  dummy_command1[0] = "cat";
  dummy_command1[1] = malloc(sizeof(Char_Ptr));
  dummy_command1[1] = "shell.c";
  dummy_command1[2] = malloc(sizeof(Char_Ptr));
  dummy_command1[2] = NULL;
  Char_Ptr_To_Ptr dummy_command2 = malloc(sizeof(Char_Ptr)* 2);
  dummy_command2[0] = malloc(sizeof(Char_Ptr));
  dummy_command2[0] = "grep";
  dummy_command2[1] = malloc(sizeof(Char_Ptr));
  dummy_command2[1] = "execute";
  dummy_command2[2] = malloc(sizeof(Char_Ptr));
  dummy_command2[2] = NULL;
  if (pipe(pipefd) < 0) { 
    printf("\nPipe could not be initialized"); 
    return 1; 
  } 
  pid_1 = fork(); 
  if(pid_1 < 0){
    printf("Something went wrong in initializing fork...\n");
    return 1;
  }

  if (pid_1 == 0) { 
    __execute_first_command(pipefd, dummy_command1);
  } else { 
      pid_2 = fork(); 
      if(pid_2 < 0 ){
        printf("Something went wrong in initializing fork...\n");
        return 1;
      }
      if (pid_2 == 0) { 
        __execute_second_command(pipefd, dummy_command2);
      } else { 
        wait(&pid_2); 
        wait(&pid_1); 
      } 
  }
  return exit_code; 
}

