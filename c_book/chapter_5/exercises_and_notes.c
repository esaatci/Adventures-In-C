#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/* Chapter 5.1 */
/*

pointers cannot be applied to expressions constants or register variables

*/

/* Chapter 5.2 */
/*


*/

/* Chapter 5.3 */
/*

There is one difference between an array name and a pointer that must be kept in mind.
A pointer is a variable, so pa=a and pa++ are legal.
But an array name is not a variable; constructions like a=pa and a++ are illegal.

Passing a sub array
    f(&a[2])
*/
#define BUFSIZE 100
/* buffer for ungetch */
char buf[BUFSIZE];
/* next free position in buf */
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

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

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))   /* skip white space */
    ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    printf("sign is %d\n", sign);
    if (c == '+' || c == '-')
    {
        printf("we are here\n");
        c = getch();
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}
/* exercise 5-1 */
int exercise_five_one(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))   /* skip white space */
    ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    printf("sign is %d\n", sign);
    if (c == '+' || c == '-')
    {
        printf("we are here\n");
        c = getch();
        if(!isdigit(c))
        {
            printf("the\n");
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}


/* Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? */
int exercise_five_two(double *pn)
{
    int c, sign, power;
    double t;
    power = 0;
    while (isspace(c = getch()))   /* skip white space */
    ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        c = getch();
        if(!isdigit(c))
        {
            ungetch(c);
            return 0;
        }
    }
    for (t = 0.0; isdigit(c); c = getch())
    {
        t = 10 * t + (c - '0');
    }
    if(c == '.')
    {
        c = getch();
       for (; isdigit(c); c = getch())
        {
            t = 10 * t + (c - '0');
            power++;
        }
    }
    *pn = t;
    printf("power is %d\n", power);
    *pn = (sign * t) / pow(10, power);
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

void exercise_five_one_tests(void)
{
    printf("running 5-1\n");
    int x, res;
    if(!(res = exercise_five_one(&x)))
    {
        printf("the value is not a num\n");
    }
    else
    {
        printf("the number rxed is %d\n", x);
    }

}

void exercise_five_two_tests(void)
{
    printf("runnig 5-2\n");
    double k;
    exercise_five_two(&k);
    printf("the number is %f\n", k);

}

/* Chapter 5-4 */
/*
It is not legal to add two pointers, or to multiply or divide or shift or mask them, or to add float or double to them, or even, except for void *, to assign a pointer of one type to a pointer of another type without a cast.
*/
/*
Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/

void exercise_five_three(char *s, char *t)
{
    int i, j;


    for(; *s != '\0'; s++);
    while((*s++ = *t++) != '\0');


}

void exercise_five_three_tests(void)
{
    char s[] = "Hello";
    char t[] = "W";
    exercise_five_three(s, t);
    printf("the concat is %s\n", s);
}

int my_strcomp(char *s, char *t)
{
    for(; *s == *t; s++, t++)
    {
        if(*s == '\0')
        {
            return 0;
        }
    }
    return *s - *t;
}
/*
Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.

assume |t| > |s|
*/
int exercise_five_four(char *s, char *t)
{
    int s_len, t_len, i, j;
    if(!s || !t)
    {
        /* strings are empty */
        printf("here\n");
        return 0;
    }
    s_len = strlen(s);
    t_len = strlen(t);

    for(i=s_len ,j=t_len; i >= 0 && j >= 0 && s[i] == t[j]; i--, j--);
    return (j == -1) ? 1 : 0;
}

void exercise_five_four_tests(void)
{
    int result;
    /* finds the word */
    char *s = "Hello World";
    char *t = "World";
    result = exercise_five_four(s, t);
    printf("the first result is %d\n", result);
    
    char *s2 = "Hello WOrld";
    char *t2 = "World";
    result = exercise_five_four(s2, t2);
    printf("the second result is %d\n", result);
    
    char *s3 = "Hello World";
    char *t4 = "world";
    result = exercise_five_four(s2, t2);
    printf("the second result is %d\n", result);

}


/* 
Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. 
For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/
void my_strncpy(char *s, const char *t, int n) 
{
    for(; n > 0 && *t != '\0'; n--)
    {
        *s++ = *t++;
    }
    *s = '\0';
    
}
/*
concatenate at most n characters of string ct to string s, terminate s with ’\0’; return s.
*/
char *my_strncat(char *s, char *ct, int n)
{
    char *temp = s;
    /* find the end of the string s */
    for(; *temp != '\0'; temp++);
    /* copy ct to the end */
    for(; n > 0 && (*temp++ = *ct++) != '\0'; n--)
    {
    }
    *temp = '\0';
    
    return s;
}

int my_strncmp(const char *cs, const char *ct, int n)
{
    for(; (n > 0) && (*ct == *cs) && (*cs != '\0') && (*ct != '\0'); n--, ct++, cs++);
    
    if(*cs == *ct)
    {
        return 0;
    }
    else if(*cs > *ct)
    {
        return 1;
    }
    else {
        return -1;
    }
}

void exercise_five_five_tests(void)
{
    int result;
    char buf[100];
    char *t = "Hello";
    my_strncpy(buf, t, 2);
    printf("the string is %s\n", buf);

    char buf_two[100] = "Hello";
    char *k = " World";
    my_strncat(buf_two, k, 6);
    printf("the second is %s\n", buf_two);

    char cs[] = "H";
    char ct[] = "Howdy";
    result = my_strncmp(cs, ct, 5);
    printf("the result is %d\n", result);

}

void exercise_five_six(void);
/* Chapter 5.6 */

int main()
{


    /* exercise 5-1 tests */
    // exercise_five_one_tests();

    /* exercise 5-2 tests */
    // exercise_five_two_tests();

    /* exercise 5-3 tests */
    // exercise_five_three_tests();
    
    /* exercise 5-4 tests */
    // exercise_five_four_tests();

    /* exercise 5-5 tests */
    exercise_five_five_tests();
    return 0;
}