#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

typedef char * Char_Ptr;
typedef Char_Ptr* Char_Ptr_To_Ptr;
#define GREEN "[0;32m" 
#define RED "[0;31m" 
#define BLUE "[0;34m" 
#define BOLD_CYAN "[0;36m" 
#define RESET "[0m" 

void set_color(Char_Ptr);
void print_dir();
int execute_command(Char_Ptr_To_Ptr);
Char_Ptr_To_Ptr parse_command(Char_Ptr);
int handle_built_in(Char_Ptr_To_Ptr);
void handle_ctrl_c(int);
int parse_pipe(Char_Ptr, Char_Ptr_To_Ptr);
void parse_space(Char_Ptr, Char_Ptr_To_Ptr);
int execute_pipe(Char_Ptr_To_Ptr, Char_Ptr_To_Ptr);

#endif