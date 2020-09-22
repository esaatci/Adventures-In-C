/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s. 
Use it to write a program that reverses its input a line at a time.

*/
#include <stdio.h>
#define BUF_SIZE 1024

void reverse(char str[]) {
    int i, len;
    i = 0;
    len = 0;
    
    for(i=0; str[i] != '\0'; i++) {
        len++;
    }
    for(i=0; i < len/2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

void clear_buf(char buf[]) {
    int i;

    i = 0;
    for(i=0; i< BUF_SIZE; i++) {
        buf[i] = 0;
    }
}

int get_line_and_reverse(char buf[]) {
    int i, c;
    i = 0;
    while((c = getchar()) != EOF && c != '\n') {
        buf[i] = c;
        i++;
    }
    if(c == '\n') {
        buf[i] = '\0';
        reverse(buf);
        buf[i] = '\n';
        buf[++i] = '\0';
    }
    else {

        buf[i] = '\0';
        reverse(buf);
    }

    return i;
}


int main() {
    int i;
    char buf[BUF_SIZE];
    while((i = get_line_and_reverse(buf)) > 0) {
        printf("%s", buf);
    }

    
    return 0;
}