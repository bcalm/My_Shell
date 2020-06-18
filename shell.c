#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int main(void){
  while (1)
  {
    char line[255];
    printf("my-shell $ ");
    gets(line);
    Char_Ptr_To_Ptr command = parse_command(line);
    printf("a is located at %s\n",command[0]);
    printf("a is located at %s\n",command[1]);
  }
  return 0;
}