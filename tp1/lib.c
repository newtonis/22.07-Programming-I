#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

#define OPCION_CNT 2
#define PARAMETRO_CNT 1

enum { BUSCAR_INICIAL , LEER_STRING };
enum { PARAMETRO, OPCION };



void init_action(int type,t_action* action , char *key, char *value){
    action->type = type;
    switch (type){
        case PARAMETRO:
            action->key   = key;
            action->value = NULL;
        break;
        case OPCION:
            action->key = key;
            action->value = value;
        break;
    }
}

int parseCmdLine(int argc,char *argv[], pCallback p,void *userData){
    
   
    int estado = BUSCAR_INICIAL; // buscamos el primer guion o letra
    
    int error = 0; 
    int cnt_actions = 0;
    
    t_action** actions = malloc(sizeof(t_action*)*argc); // nunca tendremos mas de argc acciones 
    
    char *buffer;
    
    for (int i = 0;i < argc;i++){
        switch (estado){
            case BUSCAR_INICIAL:
                if (argv[i][0] == '-'){
                    buffer = &(argv[i][1]);
                    if (strlen(buffer) == 0){
                        error = 1; // type 2
                    }
                    estado = LEER_STRING;
                }else{
                    actions[cnt_actions] = malloc(sizeof(t_action));
                    init_action(PARAMETRO,actions[cnt_actions],argv[i],NULL);
                    cnt_actions ++;
                }
            break;
            case LEER_STRING:
                actions[cnt_actions] = malloc(sizeof(t_action));
                init_action(OPCION,actions[cnt_actions],buffer,argv[i]);
                cnt_actions++;
                estado = BUSCAR_INICIAL;
            break;
        }
        
        if (error) break; /// no tiene ningun sentido seguir
    }
    if (estado == LEER_STRING){
        error = 1; // type 1
    }
    
    if (error == 0){ // if success
        for (int i = 0;i < cnt_actions;i++){
            int success;
            switch(actions[i]->type){
                case OPCION:
                    success = p(actions[i]->key,actions[i]->value,userData);
                break;
                case PARAMETRO:
                    success = p(actions[i]->key,NULL,userData);
                break;
            }
            if (!success){
                error = 1; 
                break;
            }
        }
    }
    
    for (int i = 0;i < cnt_actions;i++){
        free(actions[i]);
    }
    free(actions);
    
    if (error == 0){
        return cnt_actions;
    }else{
        return -1;   
    }
}