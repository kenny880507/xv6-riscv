#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(){
    int p[2];
    pipe(p);

    close(1);
    dup(p[1]);

    

    exit(0);
}