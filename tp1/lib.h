
#ifndef LIB_H
#define LIB_H

typedef int (*pCallback) (char*,char*,void*);

typedef struct{ /// parametro u opcion
    int type;
    char *key;
    char *value;
}t_action;

int parseCmdLine(int argc,char *argv[], pCallback p,void *userData);

static void init_action(int type,t_action* action , char *key, char *value);


#endif /* LIB_H */

