#include <stdio.h>
#include <stdlib.h>
char *my_strtok(void *z, char *out, char delim){
  char *ret = (char *)z;
  unsigned long k, p = 0;
  
  for(k = 0; ret[k]; ++k, ++p){
    
    if(ret[k] == delim){
      k++;
      out[p] = ret[k];
      continue;
    }
    out[p] = ret[k];
  }
    out[p] = 0x0;
    return out;
}

int main(int argc, char **argv){
  char *var = malloc(30);
  puts(my_strtok(" 'www.url.com.br' ", var, '.'));
  free(var);
  return 0;
}
