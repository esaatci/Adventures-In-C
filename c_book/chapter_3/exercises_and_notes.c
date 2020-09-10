#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    
    while (low <= high) 
    {
        mid = (low+high)/2;
        if (x < v[mid])
            {high = mid + 1;}
        else if (x  > v[mid])
            {low = mid + 1;}
        else    /* found match */
            {return mid;}
    }
    return -1;   /* no match */
}
/*

Exercise 3-1. Our binary search makes two tests inside the loop, 
when one would suffice (at the price of more tests outside.) 
Write a version with only one test inside the loop and measure the difference in run-time.

*/
int exercise_three_one(int *arr, int key, int size)
{
    int high, low, mid;
    
    high = size-1;
    low = 0;
    mid = (high + low) / 2;
    printf("initial mid is %d\n", mid);
    while(low < high && arr[mid] != key)
    {
        if(arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }    
        mid = (high + low) / 2;
        printf("low is %d high is %d and mid is %d\n", low, high, mid);


    }
    return (arr[mid] == key) ? mid : -1;
}

/*

Chapter 3.4 switches
A default is optional; 
if it isn’t there and if none of the cases match, 
no action at all takes place. Cases and the default clause can occur in any order.
always add a break statement at the end of swithc cases
otherwise the code will fall through and execute the other switch cases

*/
/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. 
Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.

\n, \t, \r, \b 
I'm assuming that t has enough space to hold the copied string
*/
void exercise_three_two(char s[], char t[])
{
    /* Copy the string */
    int i, j, c;
    
    j = 0;
    
    for(i=0; (c = s[i]) != '\0'; ++i)
    {
        switch (c)
        {
            case '\n':
            {
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            }
            case '\t':
            {
                t[j++] = '\\';
                t[j++] = 't';
                break;
            }
            case '\r':
            {
                t[j++] = '\\';
                t[j++] = 'r';
                break;
            }
            case '\b':
            {
                t[j++] = '\\';
                t[j++] = 'b';
                break;
            }
                
            default:
            {
                /* just copy  */
                t[j++] = c; 
                break;
            }
        }
    }
    /* copy the null char */
    t[j] = '\0';
    
}

typedef enum state {
    S1,
    S2,
    S3,
    S4,
    S5
} state;


void exercise_three_three(char *s1, char *s2)
{
    int i =0;
    state cur = S1;
    state next;
    
    while(s1[i] != ' ')
    {
        switch (cur)
        {
        case S1:
        {
            if(s1[i] == '-')
            {
                next = S1;
            }
            else
            {
                next = S2;
            }
            break;
        }
        case S2:
        {
            if(s1[i] == '-')
            {
                next = S3;
            }
            else
            {
                next = S2;
            }
            break;
        }
        case S4:
        {
            if(s1[i] == '-')
            {
                next = S5;
                
            }
        }
        default:
            break;
        }
    }
}
void reverse(char s[]);
char hex_conv(char c);

/*
Exercise 3-4. In a two’s complement number representation, our version of itoa does not handle the largest negative number, 
that is, the value of n equal to -(2wordsize-1). 
Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.

*/
void my_itoa(int n, char s[])
{

    int i, sign;
    long num;
    num = n;
    if ((sign = n) < 0)  /* record sign */
    {
        num = n;
        num *= -1;
    }
    i = 0;
    do {/* generate digits in reverse order */
        s[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. 
In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/


void itob(int n, char s[], int b) 
{
    int i, sign;
    long expanded_num;
    char digit;
    
    expanded_num = n;
    i = sign = 0;
    if(expanded_num < 0) {
        expanded_num *= -1;
        sign = 1;
    }
    do {
        digit = expanded_num % b;
        printf("digit is %c\n", 55);
        
        if(b == 16 && digit > 9) 
        {
            s[i++] = hex_conv(digit);
        }
        else
        {
            s[i++] = digit + '0';
        }
        
        expanded_num /= b;
        // printf("num is %ld\n", expanded_num);
    } while(expanded_num > 0);
    
    if(sign) 
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
    
    
}

void exercise_three_six(int n, char s[], int min_width) 
{

    int i, sign, len;
    long num;
    num = n;
    
    len = 0;
    
    if ((sign = n) < 0)  /* record sign */
    {
        num = n;
        num *= -1;
    }
    i = 0;
    do {/* generate digits in reverse order */
        s[i++] = num % 10 + '0';
        len++;
    } while ((num /= 10) > 0);

    if (sign < 0)
    {
        s[i++] = '-';
    }
    
    while(len++ < min_width)
    {
        s[i++] = 'A';
    }
    
    s[i] = '\0';
    reverse(s);
}

int main()
{
    /*
    int num, i;
    int my_test[] = {1,2,3,4,5,6,10,13,20};
    num = 10000;
    i = exercise_three_one(my_test, num, 9);
    printf("the index is %d\n", i);
    char s[] = "Hello World\n";
    */
    
    char t[256];
    int test_num = -548;
    // itob(test_num, t, 16);
    my_itoa(test_num, t);
    
   exercise_three_six(-548, t, 100);
   printf("%s\n", t);
    
    
    return 0;
}
void reverse(char s[])
{
    int len, i, mid;
    char temp;
    
    len = strlen(s);
    i = 0;
    mid = len / 2;
    
    for(i=0; i<mid; i++)
    {
        temp = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = temp;
    }
    
    return;
}


char hex_conv(char c)
{
    char add = c % 10;
    return 'A' + add;
}