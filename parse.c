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

int parse_pipe(Char_Ptr line, Char_Ptr_To_Ptr commands) 
{ 
    int i; 
    for (i = 0; i < 2; i++) { 
        commands[i] = strsep(&line, "|"); 
        if (commands[i] == NULL) 
            break; 
    } 
  
    if (commands[1] == NULL) 
        return 0;  
    else { 
        return 1; 
    } 
} 

