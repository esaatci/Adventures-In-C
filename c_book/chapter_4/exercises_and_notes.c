/* Chapter 4 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
Exercise 4-1. Write the function strindex(s,t)
which returns the position of the rightmost occurrence of t in s, or -1 if there is none.
*/
int exercise_four_one(char s[],  char t[])
{
    int s_len, t_len, i, j, cur;
    char first;
    s_len = strlen(s);
    t_len = strlen(t);

    if(!s_len || !t_len)
    {
        return -1;
    }

    first = t[0];
    for(i = s_len-1; i >= 0; i--)
    {
        if(s[i] == first)
        {
            cur = i;
            for(j=0; j <t_len && cur < s_len && t[j] == s[cur]; j++, cur++);
            if(j == t_len)
            {
                return i;
            }
        }
    }

    return -1;
}

/*
Exercise 4-2. Extend atof to handle scientific notation of the form 123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

   /* atof:  convert string s to double */
double my_atof(char s[])
{
    double val, power, sc_val;
    int i, sign, sc_sign;


    /* skip white space */
    for (i = 0; isspace(s[i]); i++);

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.')
    {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    // add check for e or E
    if(s[i] == 'e' || s[i] == 'E')
    {
        printf("found e\n");
        i++;
    }
    // check for exponent sign
    sc_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    printf("the sign is %d\n", sc_sign);
    // add the exp to the power
    for (sc_val = 0.0; isdigit(s[i]); i++)
    {
        sc_val = 10.0 * sc_val + (s[i] - '0');
    }
    printf("the sc val is %f\n", sc_val);
    sc_val *= sc_sign;
    // multiply the res with pow
    return (sign * val / power) * pow(10, sc_val);
}



double my_fun(void)
{
    return 1.2345;
}


/* Chapter 4.10 */
/*
When a function calls itself recursively, each invocation gets a fresh set of all the automatic variables, independent of the previous set
*/


/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine.
*/
void exercise_four_thirteen(char s[]);
void helper(char buf[], long n, int i)
{
    if(n < 0)
    {
        n = -n;
        buf[i++] = '-';
    }

    if(n < 10)
    {
        buf[i++] = n + '0';
        buf[i] = '\0';
        return;
    }

    int digit = n % 10;
    buf[i] = digit + '0';
    helper(buf, n / 10, i+1);
    return;

}
void exercise_four_twelve(char buf[], int n)
{
    helper(buf, (long) n, 0);
    exercise_four_thirteen(buf);

}


void reverse_swap(char s[], int i, int j)
{
    char temp;

    temp =  s[i];
    s[i] = s[j];
    s[j] = temp;
}
void reverse_helper(char s[], int first, int last)
{
    if(first > last)
    {
        return;
    }
    reverse_swap(s, first, last);
    reverse_helper(s, first+1, last-1);
}

void exercise_four_thirteen(char s[])
{
    int len = strlen(s);
    reverse_helper(s, 0, len-1);
}

#define my_swap(t, x, y) \
    t temp = x; \
    x = y; \
    y = temp; \

int main()
{
    /* exercise four one tests */
    // char s[] = "Hello WorldsssW";
    // char t[] = "World";
    // int found = exercise_four_one(s, t);
    // printf("I found %d\n", found);
    // int su = my_fun();
    // printf("I rxed %d\n", su);

    /* exercise four two tests */
    char c_num[] = "123.45";
    double num = my_atof(c_num);
    printf("the number is %f\n", num);
    char x[] = "-5";
    printf("atof is %f\n", atof(x));

    /* exercise four twelve tests */
    printf("=================\n");
    printf("exercise four twelve tests\n");
    char buf[100];
    num = 1256;
    exercise_four_twelve(buf, num);
    printf("the buf after the operation is %s\n", buf);
    /* exercise four thirteen tests */
    char word[] = "";
    exercise_four_thirteen(word);
    printf("the reversed string is %s\n", word);

    int t = 5;
    int q = 4;
    my_swap(int, t , q);
    printf("the result of the swap is %d\n", q);
    return 0;
}