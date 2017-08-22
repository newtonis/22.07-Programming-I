
#include "common_structs.h"
#include <stdio.h>
#include "lib_parser.h"
#include "utils.h"


int parseCallback(char* key,char* data,void* userdata){
    lowerize(key);
    lowerize(data);
    
    printf("[%s] = %s ",key,data);
    
}
 

int main(int argv , char *argc[]){
    parameter_data data;
    int parser_success = parseCmdLine(argv,argc,parseCallback,(void*)&data);
    
    
}