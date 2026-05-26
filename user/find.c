#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char* path, char* target){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
    case T_FILE:
        
        break;

    case T_DIR:
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0) continue;
            if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0) continue;

            if(strcmp(target, de.name) == 0) printf("%s/%s\n",path,de.name);

            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            int sub_fd = open(buf,0);
            if(sub_fd >= 0){
                struct stat sub_st;
                if(fstat(sub_fd,&sub_st)>=0 && sub_st.type == T_DIR){
                    find(buf,target);
                }
                close(sub_fd);
            }           
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[]){

    find(argv[1],argv[2]);
    exit(0);
}