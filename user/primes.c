#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(){
    
    int p[2];
    int i;
    pipe(p);
    for(i=2;i<36;++i) write(p[1],&i,sizeof i);
    close(p[1]);
    int prime, received_num;
    prime = 0;

    int right_pipe[2];
    int has_child = 0;
    
    while(1){
        int read_state = read(p[0], &received_num, sizeof(int));
        if(read_state == 0){
            close(p[0]);
            if(has_child){
                close(right_pipe[1]);
                wait(0);
            }
            exit(0);
        } else if(prime == 0){
            prime = received_num;
            printf("prime %d\n",prime);
        } else if(received_num % prime == 0){
            continue;
        } else {
            if(has_child == 0){
                pipe(right_pipe);
                
                if(fork() == 0){
                    p[0] = right_pipe[0];
                    close(right_pipe[1]);

                    prime = has_child = 0;
                    continue;
                }
                close(right_pipe[0]);
                has_child = 1;
            }

            write(right_pipe[1],&received_num, sizeof(int));
        }
        
    }
}