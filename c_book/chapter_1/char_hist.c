// Exercise 1-14. Write a program to print a histogram of the frequencies of different characters in its input.
#include <stdio.h>


#define CHAR_COUNT 256
#define PRINT_LINE(x) for(j = (x); j > 0; --j) \
                        printf("-");
// get characters until its EOF

// increment the correspoding index

// print the resulting histogram

int main() {

    char input_chars[256];
    int c, i, j;

    for(i = 0; i < CHAR_COUNT; ++i)
        input_chars[i] = 0;
    
    while ((c = getchar()) != EOF) {
        ++input_chars[c];
    }

    printf("Starting to print the histogram\n");
    
    for(i = 33; i < 127; ++i) {
        int count = input_chars[i];
        printf("character %c =>  ", i);
        PRINT_LINE(count);
        // for(j = count; j > 0; --j)
        //     printf("-");
        printf("\n");
    }


    return 0;

}