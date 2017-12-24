#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#define filtro "<li class=\"b_algo\"><h2><a href=\""
#define wf fprintf
enum{MAX=900*900};

void * error(char *string, size_t erro) {    
    wf(stderr, "%s", string);
    exit(erro);
    exit(-1);
}

char *filter(char *url, char *domain, char *search){
   if (!*url) return NULL; 
   int c = 0; static int i;
   char *z = NULL;
  
  for(;*url;++url){
  z = search;
  for(; *z != 0x0 && *url == *z; ){
  ++url;++z;
  }
  if(!*z)
  strcpy(domain, url);}
  for(i=10;domain[i];++i){
    if(domain[i]=='/'){
      domain[i]=0x0;}
  }
  return domain;
}

typedef struct {
    unsigned char *ptr;
    size_t len;
}dim;

size_t writefunc(void *ptr, size_t size, size_t numbmemb, dim *dinam) {
    size_t nlen = dinam->len + size*numbmemb;
    
    if ( (dinam->ptr = realloc(dinam->ptr, nlen+1)) == NULL) {
        error("erro realloc.\n", -1);
    }
    
    memcpy(dinam->ptr+dinam->len, ptr, size*numbmemb);
    dinam->ptr[nlen] = '\0';
    dinam->len = nlen;
    
    return size*numbmemb;
}

void * banner(void) {
    wf(stdout, "\n\t[ bing dorker ]\n");
    wf(stdout, "\t[ coded by vold ]\n"); 
    wf(stdout, "\t[ greetz: all my friends ;) ]\n");
 
    return 0;
}

void * help(char *name) {
    wf(stderr, "\ndomain or flag not found...\n" \
               "example: %s <option> <domain> <verbose>\n" \
               "search: -s domain -v\n\n",name);
    return 0;
}

unsigned char request(char **argv, int argc) {
    banner();
    FILE *file = NULL;
    char domain[MAX], teste[MAX];
    
    int opt, verbose = 0;
    char *search=NULL;
    
    if(argc!=4) {
        wf(stderr,"Fault...\n");
    }
    
     while((opt = getopt(argc, argv, "s:v")) != -1) 
         switch(opt) {
             case 's':
              search = optarg;
              break;
              
              case 'v':
              verbose=1;
              break;
              
             case '?':
              if(optopt=='s') 
               wf(stderr,"option -s requires argument.\n");
               
             default:
              wf(stderr,"unknow option: `-%c'.\n",optopt);
              return -1;
         }
    
    if (search==NULL || verbose==0) {
        help(argv[0]);
        exit(-1);
    }
    
    dim dinamic;
    CURL *session;
    CURLcode res;
    
    unsigned const char bing[MAX] = "www.bing.com";
    unsigned const char path[MAX] = "/search?q=site:";
    
    printf("\nPesquisando por '%s'...\n", argv[2]);
    
    strcat( (char*)path, argv[2]);
    putchar('\n');
    strcat( (char*)bing, (char*)path);
    
    int i;
    for(i = 0; i<=9; ++i){
    
    session = curl_easy_init();
    curl_easy_setopt(session, CURLOPT_URL, bing);
    curl_easy_setopt(session, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:29.0) Gecko/20100101 Firefox/29.0");
    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(session, CURLOPT_WRITEDATA, &dinamic);
    curl_easy_perform(session);
    
    filter(dinamic.ptr, domain, filtro);
    puts(domain);
    }
    
    curl_easy_cleanup(session);  
    return 0;
}

int main(int argc, char *argv[]) {
    request(argv, argc);
    return 0;
}
