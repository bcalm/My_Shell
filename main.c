#include "shell.h"

void set_color(Char_Ptr color_code){
  printf("\033%s", color_code);
}

int main(void){
  int exit_code = 0;

  while (1)
  {
    Char_Ptr color = GREEN;
    char line[255];
    set_color(color);
    printf("my-shell ");
    if(exit_code) {
      color = RED;
    }
    set_color(color);
    printf("$  ");
    set_color(RESET);
    gets(line);
    Char_Ptr_To_Ptr command = parse_command(line);
    if(!handle_built_in(command)){
      exit_code = execute_command(command) || 0;
    }
  }
  return 0;
}

