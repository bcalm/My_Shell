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
      printf("Command not found: %s\n", command[0]);
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

void set_color(Char_Ptr color_code){
  printf("\033%s", color_code);
}

int main(void){
  int exit_code = 0;
  Char_Ptr green = "[0;32m";
  Char_Ptr red = "[0;31m";
  Char_Ptr reset = "[0m";
  while (1)
  {
    Char_Ptr color = green;
    char line[255];
    set_color(color);
    printf("my-shell ");
    if(exit_code) {
      color = red;
    }
    set_color(color);
    printf("$  ");
    set_color(reset);
    gets(line);
    Char_Ptr_To_Ptr command = parse_command(line);
    if(!handle_built_in(command)){
      exit_code = execute_command(command) || 0;
    }
  }
  return 0;
}

