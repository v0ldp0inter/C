#include <stdio.h>
#include <stdlib.h>
void *_mymemset(void *st, char rew, size_t len){
     size_t i;
     char *aux = (char *)st;
    
     for(i = 0; aux[i]; ++i)
         aux[i] = rew;
  
  return aux;
}

int main(int argc, char **argv){
  char aux[] = "teste";
  puts(aux);
  
  puts(_mymemset(aux, 0x0, sizeof(aux)));
  puts(aux);
  return 0;
}
