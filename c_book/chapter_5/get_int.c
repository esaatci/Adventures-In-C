#include <ctype.h>
#include <stdio.h>
#include <conio.h>




int getint(int *pn);


int main() {
    
    
    return 0;
}


int getint(int *pn) {
    int c, sign;
    
    while(isspace(c = getch()));
    
    if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    
    if(c == '+' && c == '-') {
        c = getch();
    }
    
    *pn *= sign;
    
    if (c != EOF)
        {ungetch(c);}
    return c;
}