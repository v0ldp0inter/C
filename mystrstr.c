#include <stdio.h>
#include <string.h>
char *my_strstr(char *st, char *p){
   if (!*st) return NULL; 
   char *j = NULL;
   long c = 0;
   
    while(*st){
        j = p;
        while(*j != 0x0 && *st == *j){
          ++j;
          ++c;
          ++st;
        }
          if(*j == 0x0){
            return st - c;
          }
        
      ++st;
    }
  
  return NULL;
}

int main(int argc, char **argv){
  puts(my_strstr("atheist", "ist"));
  return 0;
}
