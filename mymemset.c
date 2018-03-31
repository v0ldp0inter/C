#include <stdio.h>
void *_mymemset(void *st, char rew, size_t len){
     char *aux = (char *)st;
     size_t i;
    
     for(i = 0; i <= len; ++i)
         aux[i] = rew;
  
  return aux;
}

int main(int argc, char **argv){
  char aux[] = "teste";
  puts(aux);
  
  _mymemset(aux, 0x0, sizeof(aux));
  puts(aux);
  return 0;
}
