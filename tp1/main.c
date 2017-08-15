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
    
    char *test1[] = {"NAME","-a","b","c","-e","f","-hf","a"};
    
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
    check(ans,5,2);
    
    char *test6[]={"NAME","-Hola", "mundo","-hola", "mundo","test","-hola","hola","-hola","test","test"}; // Sucess
    ans = parseCmdLine( sz(test6), test6, parseCallback,NULL);
    check(ans,6,6);
    
    char *test7[]={"NAME","parser","--aw","34gy5","ahchehv3","---54d","hu687","hjgdyt"};
    ans = parseCmdLine( sz(test7), test7, parseCallback,NULL);
    check(ans,7,5);
    
    char *test8[]={"NAME","parser","-f","34gy5","-rt"};
    ans = parseCmdLine( sz(test8), test8, parseCallback,NULL);
    check(ans,8,-1);
    
    
    
    /****** 
    SALIDA DE ARIEL
    
    called [a]=[b]
    called [c]=[(null)]
    called [e]=[f]
    called [hf]=[a]
    Sucess on test 1
    Sucess on test 2
    Sucess on test 3
    Sucess on test 4
    called [key]=[-key]
    called [param]=[(null)]
    Sucess on test 5
    called [Hola]=[mundo]
    called [hola]=[mundo]
    called [test]=[(null)]
    called [hola]=[hola]
    called [hola]=[test]
    called [test]=[(null)]
    Sucess on test 6
    called [parser]=[(null)]
    called [-aw]=[34gy5]
    called [ahchehv3]=[(null)]
    called [--54d]=[hu687]
    called [hjgdyt]=[(null)]
    Sucess on test 7
    Sucess on test 8


     */
    
}

int parseCallback(char *key, char *value, void *userData){
    printf("called [%s]=[%s]\n",key,value);
    return 1;
}