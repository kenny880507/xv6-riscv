#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    if(fork() == 0){
        int pid = getpid();
        char buff[512];
        read(p1[0], buff, sizeof buff);
        printf("%d: received %s\n",pid, buff);
        write(p2[1], "pong", 5);
        exit(0);
    } else {
        int pid = getpid();
        char buff[512];
        write(p1[1], "ping", 5);
        read(p2[0],buff,sizeof buff);
        printf("%d: received %s\n",pid,buff);
        exit(0);
    }
}