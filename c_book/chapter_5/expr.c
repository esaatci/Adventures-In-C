#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Exercise 5-10. Write the program expr, 
which evaluates a reverse Polish expression from the command line, 
where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).
*/

/*

for(c in argv)
{
    if(c == value)
    {
        push(c)
    }
    if(c == op)
    {
        v1 = pop();
        v2 = pop();
        switch(c) 
        {

        } 
    }
}

*/
#define MAXSIZE 1024
int s[MAXSIZE];
int sp = 0;

void my_push(int num)
{
    if(sp == MAXSIZE)
    {
        printf("not enough space on the stack\n");
    }
    s[sp++] = num;
}
int my_pop(void)
{
    if(!sp)
    {
        printf("no elements on the stack\n");
    }    
    return s[--sp];
}

int main(int argc, char **argv) 
{
    int i, arg_len, num, v1, v2, res, sign;
    char *arg, c;
    for(i = 1; i < argc; i++)
    {
        printf("here\n");
        arg = *(argv + i);
        arg_len = strlen(arg);
        if(arg_len > 1)
        {
            sign = (arg[0] == '-') ? -1 : 1;
            num = (arg[0] == '-' || arg[0] == '+') ?  atoi(arg+1) : atoi(arg);
            num *= sign;
            my_push(num);
        } 
        else
        {
            c = *arg;
            if(c == '-' || c == '+' || c == 'x' || c == '/') 
            {
                v2 = my_pop();
                v1 = my_pop();
                switch (c)
                {
                case '-':
                {
                    res = v1 - v2;
                    my_push(res);
                    break;
                }
                case '+':
                {
                    res = v1 + v2;
                    my_push(res);
                    break;
                }
                case 'x':
                {
                    res = v1 * v2;
                    my_push(res);
                    break;
                }
                case '/':
                {
                    res = v1 / v2;
                    my_push(res);
                    break;
                }
                default:
                {
                    printf("unknown operation\n");
                    break;
                }
                }
            }
            else if(c >= '0' && c <= '9')
            {
                my_push(atoi(arg));
            }
            else
            {
                printf("unknown symbol\n");
            }
            
        }
    }
    printf("the result of the operation is %d\n", s[0]);
    return 0;
}