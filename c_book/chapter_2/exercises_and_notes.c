#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
/*
    arbitrary byte sized bit pattern can be specified
*/
#define VTAB ’\xb’  /* ASCII vertical tab */
#define BELL ’\x7’  /* ASCII bell character */

/* enumearation is a list of constant integer values */

/* Don't apply % to floats or doubles */

void auto_variable_val_test(void) 
{
    int x;
    printf("the value of x is %d\n", x);
}

const int lim = 5;
char s[lim];

/*
    converts a string of hexadecimal digit into its equivalent integer value
    allowable digits 0 -- 9 a through f and A through F
    optional 0x 0X
*/
int my_htoi(char s[])
{
    int val, len, i, offset, exp, temp;
    /* determine the length of the string */
    len = strlen(s);
    val = exp = 0;
    printf("the len of the string is %d\n", len);
    /* iterate through the string and convert chars to lower case */
    for(i=0; i<len; i++)
    {
        
        if(!isdigit(s[i]) && isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
        
    }
    printf("the modified sting is %s\n", s);
    /* check if it has 0x */
    if(s[0] == '0' && s[1] == 'x')
        offset = 2;
    else
        offset = 0;

    

    
    /* iterate through the string producing the val */
    for(i=len-1; i>=offset; i--)
    {
        if(isdigit(s[i]))
        {
            temp = s[i] - '0';
        }
        else
        {
            temp = s[i] -'f' + 15;
        }
        printf("temp is %d\n", temp);
        val += pow(16, exp++) * temp;

    }

    return val;
}

/*
    write the loop in comments in without using && ||
*/
void exercise_two_two(void)
{

    int i, c;
    /*
    for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    printf("I rxed %s", s);
    */
    int j,k,q;
    for(j=0; j<lim-1; j++)
    {
        c = getchar();
        if(c == EOF)
            break;
        else if(c == '\n') 
            break;
        else
            s[j] = c;
            
            
    }
    printf("I rxed %s\n", s); 
    
}
/* Chapter 2.8 Notes */
/*
Increment and decrement operators can only be applied to variables (i+j)++ is illegal
*/


void shift_helper(char *s1, int i)
{
    printf("the string is %s\n", s1);
    while(s1[i] != '\0') 
    {
        s1[i] = s1[i+1];
        i++;
    }    

}


/* @brief
    deletes each character in s1 that mathces any character in string s2
*/
void exercise_two_four(char *s1, char *s2) 
{
    int i, j, shifted;
    i = 0;
    shifted = 0;
    while(s1[i] != '\0')
    {    
        for(j=0; s2[j] != '\0'; j++) 
        {
            if(s1[i] == s2[j])
            {
                shift_helper(s1, i);
                shifted = 1;
            }
        }
        if(shifted)
        {
            shifted = 0;
        }
        else
        {
            i++;
        }
    }
    
    
}
/* @brief

returns the first location in a string s1 
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.

*/

int exercise_two_five(char *s1, char *s2)
{
    int i, j;
    
    for(i=0; s1[i] != '\0'; i++)
    {
        for(j=0; s2[j] != '\0'; j++)
        {
            if(s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}

int exercise_two_six(uint32_t x, uint32_t p, uint32_t n, uint32_t y)
{
    uint32_t mask;
    // the mask
    mask = 0xFFFFFFFF >> (32-n);
    // clear the leftmost 32-n bits
    y &= mask;
    // position it at p
    y <<= p;
    // set the bits of x
    x |= y;
    
    return x; 
    
}
/*
    that returns x with the n bits that begin at position p inverted 
    (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/

uint32_t exercise_two_seven(uint32_t x, uint32_t p, uint32_t n)
{
    
    uint32_t mask;
    
    //get n bits that are set starting at position 0
    mask = 0xFFFFFFFF >> (32-n);
    // move the mask to position p
    mask <<= p;
    // apply the mask to x
    x ^= mask;
    
    return x;
}
uint32_t exercise_two_eight(uint32_t x, uint32_t n)
{
    int i, bit;
    for(i=0; i<n; i++)
    {
        bit = x & 1;
        x >>= 1;
        bit <<= 31;
        x |= bit;

    }
    return x;
}
/* 2.10 */
/*
    The operator += is called an assignment operator.

*/


uint32_t slow_bitcount(uint32_t num);


/*
    Faster bit count
    In a two’s complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this
    observation to write a faster version of bitcount.
*/
uint32_t exercise_two_nine(uint32_t num)
{
    int b;
    for(b=0; num != 0; num &= num-1)
    {
        b++;
    }
    return b;
}


uint32_t slow_bitcount(uint32_t num)
{
    int b;
    
    for(b=0; num != 0; num >>= 1)
    {
        if(num & 0x1)
        {
            b++;
        }
    }
    return b;
}


/* 2.11 */
/*
    expr1 ? expr2 : expr3

*/

/*
    Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression
    instead of if-else.
*/
int exercise_two_ten(int c)
{
    int dif = 'a' - 'A';

    
    return (c >= 'A' && c <= 'Z') ? (c+dif) : (c);
}

void check_case(int c)
{
    if(c >= 'A' && c <= 'Z')
    {
        printf("this character is upper case\n");
    }
    else
    {
        printf("this character is not upper case\n");
    }
    
}

/*
    2.12
    x = f() + g();
    f may be evaluated before g or vice versa; 
    thus if either f or g alters a variable on which the other depends, x can depend on the order of evaluation. 
    Intermediate results can be stored in temporary variables to ensure a particular sequence.

    printf("%d %d\n", ++n, pow(2,n)); WRONG order of arguments are not specified
    Don't write code that depends on the order of evaluation

*/
int main()
{
    int result, b;
    char test[] = "AAAAAAAAA";
    result = my_htoi(test); 
    printf("result is %d\n", result);
    char h[] = "AAAA World";
    char d[] = "H";
    result = exercise_two_five(h, d);
    printf("the modified result is %d\n", result);
    
    uint32_t test_num = 0x8;
    uint32_t res = exercise_two_eight(test_num, 4);
    printf("the result is %x\n", res);

    printf("number of bits in testnum is %d\n", slow_bitcount(test_num));
    printf("the number of bits with fast bitcount %d\n", exercise_two_nine(test_num));

    for(b = 'A'; b <= 'Z'; b++)
    {
        printf("the char is %c\n", exercise_two_ten(b));
    }
    
    return 0;
}