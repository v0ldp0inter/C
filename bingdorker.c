#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#define wf fprintf
enum{MAX=900*900};

void * error(void *string, size_t erro) {
    unsigned char *ptr = (unsigned char *)string;
    
    wf(stderr, "%s", ptr);
    exit(erro);
    
    exit(-1);
}

void * mstrstr(char *needle, char * haystack) {
    unsigned int b, k, flag, u = strlen(haystack);
    k=b=flag=0;
    
     for ( b = 0; needle[b] != '\0'; b++ ) {
          for (k = 0; haystack[k] != '\0'; k++ ) 
         if (needle[b+k] == haystack[k]) {
           flag++;
         }
        if (flag == u) {
             needle[b] = '\0';
             break;
                  
          } else
           flag = 0;
     }
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
    FILE *file=NULL;
    char domain[MAX];
    
    int opt, verbose=0;
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
    
    unsigned char *exc[] = {
      "kstrong",
      "67000093.r.bat",
      "estrong",
      "wstrong",
      "cid",
      "www.microsofttranslate.com",
      "www.zimbra.com",
      "bingj.com",
      "go.microsoft.com",
      "cc.var",
      "cc.d.domain",
      "www.w3.org",
      "schemas.live.com",
      "www.bing.com",
      "login.live.com",
      "cc.",
      "strong",
      "microsoft.com",
      "bing.com",
      "www.microsofttranslator.com",
      NULL  
    };
    
    dim dinamic;
    CURL *session;
    CURLcode res;
    
    unsigned int percorre;
    unsigned const char bing[MAX] = "www.bing.com";
    unsigned const char path[MAX] = "/search?q=site:";
    
    printf("\nPesquisando por '%s'...\n", argv[2]);
    
    strcat( (char*)path, argv[2]);
    putchar('\n');
    strcat( (char*)bing, (char*)path);
    
    session = curl_easy_init();
    
    curl_easy_setopt(session, CURLOPT_CONNECTTIMEOUT, 10);
    curl_easy_setopt(session, CURLOPT_URL, bing);
    curl_easy_setopt(session, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64; rv:29.0) Gecko/20100101 Firefox/29.0");
    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(session, CURLOPT_WRITEDATA, &dinamic);
    
    curl_easy_perform(session);
    
    unsigned int var, deletesite, cxc, count, blank;
    for(cxc = 0; cxc <= 30; ++cxc) {
        
        dinamic.ptr = strstr(dinamic.ptr, "://");
        dinamic.ptr += strlen("://");
        
        for(var = 0; dinamic.ptr[var] != '\0'; ++var) {
            
            if(dinamic.ptr[var] == '/') {
                domain[var] = '\0';
                break;
            }
            
            sscanf(&dinamic.ptr[var], "%[0-9a-zA-Z.^\n]", &domain[var]);
            
           }
           
                for(deletesite=0;exc[deletesite]!=NULL;++deletesite) {
                   mstrstr(domain,exc[deletesite]);
                 }
                 
                  for(blank=0;domain[blank] != '\0';blank++) {
                      printf("[%d] - %s\n",count++, domain);
                      break;
                  }
                  
    }
    
    curl_easy_cleanup(session);
    return 0;
}

int main(int argc, char *argv[]) {
    request(argv, argc);
    return 0;
}