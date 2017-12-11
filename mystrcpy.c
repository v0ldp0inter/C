#include <stdio.h>

char *my_strcpy(char *str, const char *dest){
  if(!*str) return NULL;
  long i = 0;
  
  while(dest[i] != 0x0){
  str[i] = dest[i]; ++i;
  }
    
  str[i] = 0x0;
  return str;
}

int main(int argc, char **argv){
  char cst[55];
  my_strcpy(cst, "teste teste");
  
  puts(cst);
  return 0;
}
