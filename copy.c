#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: ./cpy filename1 filename2 filename3 .... directory");
        return 0;
    }
    FILE *fd, *dest;
    char buf[257], name[256], dir[256];;
    int len;
    struct stat st;
    
    strcpy(dir, argv[argc-1]);
    if(stat(dir, &st)){
        printf("Usage: ./cpy filename1 filename2 filename3 .... directory");
        return 0;
    }
    if(!S_ISDIR(st.st_mode)){
        printf("Usage: ./cpy filename1 filename2 filename3 .... directory");
        return 0;
    }

    if(strlen(dir) > 200) return 0;
    if(dir[strlen(dir) - 1] != '/') strcat(dir, "/");
    for(int i = 0; i < argc-2; i++){
        fd = fopen(argv[i+1], "r");
        strcpy(name, dir);
        strcat(name, argv[i+1]);
        printf("%d = %s\n", i, name);
        dest = fopen(name, "w");
        while((len = fread(buf, 1, 256, fd)))
        {
            fwrite(buf, 1, len, dest);         
        }
        fclose(dest);
        fclose(fd);
    }
}
