#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <math.h>

typedef char * Char_Ptr;
typedef Char_Ptr* Char_Ptr_To_Ptr;
#define GREEN "[0;32m" 
#define RED "[0;31m" 
#define BLUE "[0;34m" 
#define BOLD_CYAN "[0;36m" 
#define RESET "[0m" 
#define READ  0
#define WRITE 1

enum commands_code
{
 BUILT_IN,
 SIMPLE_COMMAND,
 PIPE,
 MULTIPLE_COMMAND 
};

void set_color(Char_Ptr);
void print_dir();
int execute_basic_commands(Char_Ptr_To_Ptr);
int execute_built_in_commands(Char_Ptr_To_Ptr);
void handle_ctrl_c(int);
int parse(Char_Ptr, Char_Ptr_To_Ptr, Char_Ptr);
Char_Ptr_To_Ptr parse_space(Char_Ptr);
void execute_pipes(Char_Ptr_To_Ptr* , int);

#endif