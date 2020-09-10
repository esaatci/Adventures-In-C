#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 200


int get_line(char *buf);
char *init_buf(char *buf, int size, int new_size);

/*
    Without variable buffer and assuming that buffer will not overflow
    
    get characters until we see EOF
        if c == '\n'
            insert c to buf
            break
    
    insert '\0' to buf

    ======


    get chars until we see EOF
        
        if i == k*MAXLINE:
            allocate a new buffer
            copy the contents of the old buffer
            set old buffer to point to new
        if c == '\n':
            insert it to buf
            i++
            if i == k*MAXLINE:
                allocate a new buffer
                copy the contents of the old buffer
                set old buffer to point to new
            i++
            insert '\0'
            break
                
*/

int get_line(char * buf) {

    int i,c, new_size, size;
    static int k;
    i = 0;
    k = 1;
    while((c = getchar()) != EOF) {
        if (i == k*MAXLINE) {
            printf("Creating a larger buffer\n");
            size = k*MAXLINE;
            k++;
            new_size = k*MAXLINE;
            buf = init_buf(buf, size, new_size);
            if(buf == NULL)
                return -1; 
        }
        if (c == '\n') {
            printf("here");
            printf("i is %d %d\n", i, k);
            buf[i] = c;
            i++;
            if(i == k*MAXLINE) {
                size = k*MAXLINE;
                k++;
                new_size = k*MAXLINE;
                buf = init_buf(buf, size, new_size);
                if (buf == NULL) 
                    return -1;
            }
            buf[i] = '\0';
            i++;
            printf("came all the way here\n");
            break;
        }
        else {
            buf[i] = c;
            i++;
        }
    }
    return i;

}

char *init_buf(char *buf, int size, int new_size) {
    int i;
    char * new_buff = (char *)malloc(new_size*sizeof(char));
    if(new_buff == NULL) 
        return NULL;
    
    for(i = 0; i < size; i++)
        new_buff[i] = buf[i];
    
    return new_buff;
}



int main() {
    int c; 
    char *buf = (char *)malloc(MAXLINE*sizeof(char));
    while((c = get_line(buf)) > 0) {
        printf("%s", buf);
    }
    return 0;
}
