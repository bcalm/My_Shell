#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

typedef char * Char_Ptr;
typedef Char_Ptr* Char_Ptr_To_Ptr;

Char_Ptr_To_Ptr parse_command(Char_Ptr line){
  Char_Ptr_To_Ptr command = malloc(sizeof(Char_Ptr) * 10);
  int command_count = 0;
  char arg[10];
  int arg_count = 0;
  for (int i = 0; i < 255; i++)
  {
    char character = line[i];
    if (character == ' ' || character == '\0')
    {
      command[command_count] = malloc(sizeof(char)* arg_count);
      strncpy(command[command_count++], arg, arg_count);
      arg_count = 0;
    }
    else arg[arg_count++] = character;
    if(character == '\0') break;
  }
  command[command_count] = NULL;
  return command;
}

void handle_ctrl_c(int signum){
  exit(0);
}

void execute_command(Char_Ptr_To_Ptr command){
  int pid = fork();
  signal(SIGINT, SIG_IGN);
  if(pid < 0)
  {
    printf("Something went wrong system brake...\n");
  }
  else if (pid == 0)
  {
    signal(SIGINT, handle_ctrl_c);
    if(execvp(command[0], command) < 0){
      printf("Command not found: %s\n", command[0]);
    }
  }
  else
  {
    wait(&pid);
  }
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

int main(void){
  while (1)
  {
    char line[255];
    printf("my-shell $ ");
    gets(line);
    Char_Ptr_To_Ptr command = parse_command(line);
    if(!handle_built_in(command)){
      execute_command(command);
    }
  }
  return 0;
}

