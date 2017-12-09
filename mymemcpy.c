#include <stdio.h>
#include <stdlib.h>
void * my_memcpy(void *str, const void *p, size_t h){
  
  unsigned long i;
  char *str1 = (char *)str;
  const char *cst = (const char *)p;
  
  for(i = 0; i <= h; i++){
    str1[i] = cst[i];
  }
  
  str1[i] = 0x0;
  return (void *)0; 
}


int main(int argc, char **argv){
  char *var = malloc(40);
  
  my_memcpy(var, "v0ld pointer", 4);
  printf("ret: %s\n", var);
  
  free(var);
  return 0;
}

