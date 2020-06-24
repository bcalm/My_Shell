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

void __assign_commands(Char_Ptr_To_Ptr * commands,int length, Char_Ptr_To_Ptr temp){
  for (size_t i = 0; i < length; i++)
    {
      commands[i] = malloc(sizeof(Char_Ptr_To_Ptr));
      commands[i] = parse_space(temp[i]); 
    }
}

int __handle_input(Char_Ptr line, Char_Ptr_To_Ptr* commands){
  Char_Ptr temp[10]; 
  
  int piped = parse(line, temp, "|");
  if (piped > 1) { 
    __assign_commands(commands, piped, temp);
    return PIPE;
  }
  commands[0] = malloc(sizeof(Char_Ptr_To_Ptr));
  commands[0] = parse_space(line);
  if (execute_built_in_commands(commands[0])) 
  {
    return BUILT_IN; 
  }
  return SIMPLE_COMMAND;
}

int __run(Char_Ptr line, Char_Ptr_To_Ptr * commands){
  int exit_code = 0;
  int command_code = __handle_input(line, commands);
  if(command_code == SIMPLE_COMMAND){
    exit_code = execute_basic_commands(commands[0]);
  }
  if(command_code == PIPE){
    exit_code = execute_pipe(commands[0], commands[1]);
  }
  return exit_code;
}

int __handle_multiple_commands(Char_Ptr line, Char_Ptr_To_Ptr* commands, int* exit_code){
  Char_Ptr temp[10];
  int multiple_commands  = parse(line, temp, ";");
  if(multiple_commands > 1){
    for (size_t i = 0; i < multiple_commands; i++)
    {
      *exit_code = __run(temp[i], commands);
    }
  }
  return multiple_commands - 1;
}

int main(void){
  int exit_code = 0;

  Char_Ptr_To_Ptr commands[10];
  while (1)
  {
    __print_prompt(exit_code);
    char line[255];
    gets(line);

    if(!__handle_multiple_commands(line, commands, &exit_code)){
      exit_code = __run(line, commands);
    }
  }
  return 0;
}

 