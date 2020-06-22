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

int main(void){
  int exit_code = 0;

  while (1)
  {
    __print_prompt(exit_code);
    char line[255];
    gets(line);
    Char_Ptr_To_Ptr command = parse_command(line);
    if(!handle_built_in(command)){
      exit_code = execute_command(command) || 0;
    }
  }
  return 0;
}

