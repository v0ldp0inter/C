#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *filter(char *url, char *domain, char *search){
   if (!*url) return NULL; 
   static int jmp; int i = 9;
   char *z = NULL;
  
   while(*url){
       z = search;
       while(*z != 0x0 && *url == *z){
         ++url;
         ++z;
       }
     if(!*z){break;}
     ++url;
   }
   
   strcpy(domain, &url[i]);
   for(jmp = 10;domain[jmp];++jmp){
     if(domain[jmp] == '/')
        domain[jmp] = 0x0;
   }
  
  return domain;
}

int main(int argc, char **argv){
  char *domain = malloc(400), \
  *url = "<li class=\"b_algo\"><h2><a href=\"http://teste.com.br/domain\" h=\"ID=SERP,5089.1\">";
  
  puts(filter(url, domain,  "<li class=\"b_algo\"><h2>")); 
  free(domain);
  return 0;
}
