#include "shell.h"

void parse_space(Char_Ptr line, Char_Ptr_To_Ptr command) 
{ 
  int i; 
  for (i = 0; i < 10; i++) { 
    command[i] = strsep(&line, " "); 
    if (command[i] == NULL) 
      break; 
    if (strlen(command[i]) == 0) 
      i--; 
  } 
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


