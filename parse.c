#include "shell.h"

Char_Ptr_To_Ptr parse_space(Char_Ptr line){
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
int parse(Char_Ptr line, Char_Ptr_To_Ptr commands, Char_Ptr parse_by) 
{   
  int count;
  for (count = 0; count < 10; count++) { 
    commands[count] = strsep(&line, parse_by); 
    if (commands[count] == NULL) 
        break;
  } 
  return count;  
} 


