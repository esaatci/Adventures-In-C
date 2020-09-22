#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void swap(void);
void print_top(void);
void clear(void);
void duplicate(void);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
            {
                push(atof(s));
                break;
            }
            case '+':
            {
                push(pop() + pop());
                break;
            }
            case '*':
            {
                push(pop() * pop());
                break;
            }
            case '-':
            {   op2 = pop();
                push(pop() - op2);
                break;
            }
            case '/':
            {
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            }
            case '%':
            {
                op2 = pop();
                if(op2 != floor(op2) || op2 < 0)
                {
                    printf("error invalid operand");
                }
                else
                {
                    push(abs((int) pop()) % (int) op2);
                }
                break;

            }
            case 'c':
            {
                clear();
                break;
            }
            case 'p':
            {
                print_top();
                break;
            }
            case 's':
            {
                swap();
                break;
            }
            case 'd':
            {
                duplicate();
                break;
            }

            case '\n':
                printf("\t%.8g\n", pop());
                break;

            default:
            {
                printf("error: unknown command %s\n", s);
                break;
            }
        }
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */
int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can’t push %g\n", f);
    }
}
/* duplicates the top element of the stack */
void duplicate(void)
{
    double temp = pop();
    push(temp);
    push(temp);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
/* swaps two top elements of the stack */
void swap(void)
{
    double temp;
    if(sp -1 == 0)
    {
        printf("error: cannot perform swap");
        return;
    }
    temp = val[sp-1];
    val[sp-1] = val[sp -2];
    val[sp -2] = temp;
}

/* prints the two top elements of the stack */
void print_top(void)
{
    printf("sp is %d\n", sp);
    if(sp -1 == 0)
    {
        printf("stack has only one element in it\n");
        return;
    }
    printf("the top is %f\n", val[sp-1]);
}
/* clears the stack */
void clear(void)
{
    sp = 0;
}

int getch(void);
int ungetch(int);

int getop(char s[])
{
    int i, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
    {
        /* not a number */
        return c;
    }
    i = 0;
    /* check if a negative number */
    if(c == '-')
    {
        next = getch();
        if(!isdigit(next))
        {
            ungetch(next);
            return c;
        }
        ungetch(next);
        s[++i] = c = getch();
    }
    /* collect integer part */
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
        ;
    }
    /* collect fraction part */
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
        ;
    }
    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100
/* buffer for ungetch */
char buf[BUFSIZE];
/* next free position in buf */
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
int ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
        return 1;
    }
    buf[bufp++] = c;
    return 0;
}
/*
Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?
this will work unless there there is enough room on the buf
*/
void ungets(char s[]) {

    int i;
    while(s[i] != '\0' && s[i] != EOF)
    {
        if(!ungetch(s[i++]))
        {
            printf("Cannot ungets the string\n");
            break;
        }
    }
    ungetch(s[i]);
}

/*
Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
*/
int temp = -1;

int mod_getch(void)
{
    int copy;
    if(temp) 
    {
        copy = temp;
        temp = -1;
        return copy;
    }
    return getch();
}

void mod_ungetch(int c)
{
    temp = c;
}