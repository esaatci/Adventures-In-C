#include <stdio.h>
#include <string.h>
int get_line(char buf[]) {
    int i, c;
    i = 0;
    while((c= getchar()) != EOF && c != '\n') {
        buf[i] = c;
        i++;
    }
    if(c == '\n') {
        buf[i++] = c;
    }
    buf[i] = '\0';
    return i;
}

void reverse_word_in_line(char str[], int start, int end) {
    int i, len;
    len = (end - start) + 1;
    // printf("len is %d\n", len);
    for(i = start; i < (len/2) + end; i++) {
        char temp = str[i];
        str[i] = str[end];
        str[end] = temp;
        end--;
    }
}

void parse_line(char str[]) {
    int i, first,start, end;
    first = 1;
    i =0;
    while(str[i] != '\n') {
        
        if(str[i] == '#') {
            return;
        }
        
        else if(str[i] != ' ') {
            if(first) {
                first = 0;
                start = i;
                // printf("start %d %d\n", start, i);
            }
        }
        
        else {
            if(!first) {
                end = i-1;
                //printf("Here\n");
                //printf("start: %d, end: %d\n", start, end);
                reverse_word_in_line(str, start, end);
                first = 1;
            }
        }
        i++;
    }
    if(!first) {
        end = i-1;
        reverse_word_in_line(str, start, end);
    }
}

int main() {
    int i;
    i = 0;
    char buf[1024];
    while((i=get_line(buf)) > 0) {
        parse_line(buf);
        printf("%s", buf);
        memset(&buf, 0, 1024);
    }
    return 0;
}