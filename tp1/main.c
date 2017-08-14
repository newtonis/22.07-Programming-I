/**** TP1 EDA ****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

#define sz(i) (sizeof(i)/sizeof(char*))

struct data_t{
    int x,y;
};

int parseCallback(char *key, char *value, void *userData); 

void check(int ans,int id,int expected){
    if (ans != expected){
        printf("Failure on test %d\n",id);
        exit(1);
    }else{
        printf("Sucess on test %d\n",id);
    }
}

int main(char argc, char *argv[]){
    
    
    int ans;
    
    char *test1[] = {"-a","b","c","-e","f","-hf","a"};
    
    ans = parseCmdLine(sz(test1), test1, parseCallback,NULL);
    check(ans,1,4);
    
    char *test2[] = {"NAME", "-","val", "param"};
    
    ans = parseCmdLine(sz(test2), test2, parseCallback,NULL);
    check(ans,2,-1);
    
    char *test3[]={"NAME", "-key","val", "-key"}; // Error
    
    ans = parseCmdLine(sz(test3), test3, parseCallback,NULL);
    check(ans,3,-1);
    
    char *test4[]={"NAME", "-key","val", "-"};
    ans = parseCmdLine( sz(test4), test4, parseCallback,NULL);
    check(ans,4,-1);
    
    char *test5[]={"NAME", "-key","-key", "param"}; // Error
    ans = parseCmdLine( sz(test5), test5, parseCallback,NULL);
    check(ans,5,3);
    
    char *test6[]={"-Hola", "mundo","-hola", "mundo","test","-hola","hola","-hola","test","test"}; // Sucess
    ans = parseCmdLine( sz(test5), test5, parseCallback,NULL);
    check(ans,6,6);
    
}

int parseCallback(char *key, char *value, void *userData){
    printf("called [%s]=[%s]\n",key,value);
    return 1;
}