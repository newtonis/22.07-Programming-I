#include "utils.h"

void lowerize(char * str){
    for (int pnt = 0;str[pnt] != 0;pnt++){
        if (str[pnt] >= 'A' && str[pnt] <= 'Z'){
            str[pnt] = str[pnt] - 'A' + 'a';
        }
    }
}
