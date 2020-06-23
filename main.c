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

int handle_input(Char_Ptr line, Char_Ptr_To_Ptr* commands){
    Char_Ptr strpiped[2]; 
    int piped = 0; 
    commands[0] = malloc(sizeof(Char_Ptr_To_Ptr));

    if (parse_pipe(line, strpiped)) { 
      commands[1] = malloc(sizeof(Char_Ptr_To_Ptr));
      parse_space(strpiped[0], commands[0]); 
      parse_space(strpiped[1], commands[1]); 
      return PIPE;
    }
    parse_space(line, commands[0]);

    if (execute_built_in_commands(commands[0])) 
    {
      return BUILT_IN; 
    }
    return SIMPLE_COMMAND;
}

int main(void){
  int exit_code = 0;
  Char_Ptr_To_Ptr commands[10];
  while (1)
  {
    __print_prompt(exit_code);
    char line[255];
    gets(line);
    int command_code = handle_input(line, commands);

    if(command_code == SIMPLE_COMMAND){
      exit_code = execute_basic_commands(commands[0]);
    }

    if(command_code == PIPE){
      exit_code = execute_pipe(commands[0], commands[1]);
    }
  }
  return 0;
}

 