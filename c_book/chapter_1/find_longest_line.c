/*
while (there’s another line)
    if (it’s longer than the previous longest)
        (save it)
        (save its length) 
print longest line
*/

#include <stdio.h>
#define MAXLINE 1000

int efe_getline(char s[], int maxline);
void copy(char to[], char from[]);




int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    max = 0;
    while((len = efe_getline(line, MAXLINE)) > 0)
        if(len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);
    return 0;
}


int efe_getline(char s[], int maxline) {

    int c, i;
    
    for(i=0; i<maxline && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    printf("%d\n", i);
    return i;
}

void copy(char to[], char from[]) {
    
    int i;
    i = 0;
    while((to[i] = from[i]) != '\0') {
        ++i;
    }
        
}