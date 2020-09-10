#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#define MIN(x,y) (((x) > (y)) ? (y) : (x))

char *find_common_letters(char *arr, int size) {
    
    int count[256] = {0};
    int global_letter_count[256] = {INT_MAX};
    int i, j, k, out_count;
    char *output = NULL;

    for(i = 0; i < size; i++) {
        int str_size = strlen(arr[i]);
        for(j = 0; j < str_size; j++) {
            // count[arr[i][j]]++;
        }
        for(k = 0; k < 256; k++) {
            global_letter_count[k] = MIN(count[k], global_letter_count[k]);
        }
        memset(&count,0, sizeof(int)*256);
    }
    
    out_count = 0;
    for(i = 0; i < 256; i++) {
        if(global_letter_count[i] != 0)
            out_count++;     
    }
    output = (char *)malloc(sizeof(char) * out_count);
    j = 0;
    for(i = 0; i < 256; i++) {
        if(global_letter_count[i] != 0) {
            output[j] = i; 
            j++;
        }

    }
    return output;
}






int main(void) {
    
    char* test_1 = "Hello";
    char* test_2 = "Hol";
    char* test[2];
    test[0] = test_1;
    test[1] = test_2;
    return 0;

}

