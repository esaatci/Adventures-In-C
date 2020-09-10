/*
Write a program to remove all comments from a C program. 
Don’t forget to handle quoted strings and character constants properly. 
C comments don’t nest.
*/
#include <stdio.h>

#define BUF_SIZE 2048

typedef enum {
    INIT,
    SLASH,
    ONE_STAR,
    TWO_STAR,
    BACKSLASH,
} state;

typedef enum {
    NIL,
    COMMENT,
    DONE,
} output;

void remove_comment(char buf[], int start, int end) {
    int i;
    for(i =start; i <= end; i++) {
        buf[i] = ' ';
    }
}


int main() {
    char buf[BUF_SIZE];
    int i, c, start, end;
    i = 0;
    state cur_state = INIT;
    state next_state;
    output o;
    
    while((c=getchar()) != EOF) {
        switch (cur_state)
        {
        case INIT:
            if(c == '/') {
                next_state = SLASH;
                o = NIL;
            }
            else {
                next_state = INIT;
                o = NIL;
            }
            break;
        
        case SLASH:
            if(c == '*') {
                next_state = ONE_STAR;
                o = COMMENT;
            }
            else {
                next_state = INIT;
                o = NIL;
            }
            break;
        case ONE_STAR:
            if(c == '*') {
                next_state = TWO_STAR;
                o = NIL;
            }
            else {
                next_state = ONE_STAR;
                o = NIL;
            }
            break;
        case TWO_STAR:
            if(c == '/') {
                next_state = BACKSLASH;
                o = DONE;
            }
            else {
                next_state = ONE_STAR;
                o = NIL;
            }
            break;
        case BACKSLASH:
            if(c == '/') {
                next_state = SLASH;
                o = NIL;
            }
            else {
                next_state = INIT;
                o = NIL;
            }
            break;
        default:
            break;
        }
        
        buf[i] = c;
        // printf("cur is %d\n", cur_state);
        if(o == COMMENT) {
            start = i-1;
        }
        if(o == DONE) {
            end = i;
            remove_comment(buf, start, end);
        }
        cur_state = next_state;
        i++;
    }
    buf[i] = '\0';
    printf("%s", buf);
    // for(i = start; i <= end; i++) {
    //     printf("%c", buf[i]);
    // }
    

}
