#include "shell.h"

void set_color(Char_Ptr color_code){
  printf("\033%s", color_code);
}

void __print_dir(){
  char cwd[1024]; 
  getcwd(cwd, sizeof(cwd)); 
  printf("\nDir: %s\n", cwd); 
}

void __print_prompt(int exit_code){
    Char_Ptr color = BOLD_CYAN;
    set_color(color);
    __print_dir();
    color = GREEN;
    set_color(color);
    printf("  my-shell ");
    if(exit_code) {
      color = RED;
    }
    set_color(color);
    printf("$  ");
    set_color(RESET);
}

int handle_input(Char_Ptr line, Char_Ptr_To_Ptr command, Char_Ptr_To_Ptr pipe_args){
    Char_Ptr strpiped[2]; 
    int piped = 0; 
  
    piped = parse_pipe(line, strpiped); 
  
    if (piped) { 
      parse_space(strpiped[0], command); 
      parse_space(strpiped[1], pipe_args); 
  
    } else { 
      parse_space(line, command); 
    } 

    if (handle_built_in(command)) 
        return 0; 
    else
        return 1 + piped; 
}

int main(void){
  int exit_code = 0;
  Char_Ptr pipe_args[2];
  Char_Ptr command[10];

  while (1)
  {
    __print_prompt(exit_code);
    char line[255];
    gets(line);
    int process_code = handle_input(line, command, pipe_args);
    if(process_code == 1){
      exit_code = execute_command(command);
    }
    if(process_code == 2){
      exit_code = execute_pipe(command, pipe_args);
    }
  }
  return 0;
}

 