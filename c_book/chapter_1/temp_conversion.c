#include <stdio.h>

/* Functions that converts temperature values Centigrade and F */

float from_c_to_f(float c);
float from_f_to_c(float f);
float convert_temp(float temp, int f_to_c);

/*
(F - 32) * (5 / 9) = C
F = (9 / 5 * c) + 32
*/

float from_c_to_f(float c) {
    
    return (1.8 * c) + 32;

}

float from_f_to_c(float f) {
    
    return 5 * (f-32) / 9;
}

float convert_temp(float temp, int f_to_c) {
    
    if(f_to_c)
        return from_f_to_c(temp);
    else
        return from_c_to_f(temp);

}


int main() {
    
    float temp; 
    int f_to_c;
    float result;
    printf("=============================================\n");
    printf("Welcome to the Temperature Conversion Program!\n");
    printf("please enter the temperature: ");
    scanf("%f", &temp);
    printf("please enter the direction: ");
    scanf("%d", &f_to_c);
    result = convert_temp(temp, f_to_c);
    printf("the converted temperature is %2.2f\n", result);


    
    return 0;

}