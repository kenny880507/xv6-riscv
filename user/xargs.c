#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char* argv[]){

    int p[2];
    pipe(p);

    close(1);
    dup(p[1]);
    char buff[512], *p_buff;
    p_buff = buff;
    char* new_argv[MAXARG];
    int new_argc = 1;

    int i;
    new_argv[0] = argv[1];
    for(i = new_argc; i<argc ; i++){
        new_argv[i] = argv[i+1];
        new_argc++;
    }

    if(fork() == 0){
        close(p[1]);
        while(1){
            if(read(p[0],&buff,1) == 0){
                exec(argv[1], new_argv);
                break;
            } else {
                
            }
        }
        close(p[0]);
    } else {
        wait(0);
    }
    close(p[1]);
    close(p[2]);
    exit(0);
}