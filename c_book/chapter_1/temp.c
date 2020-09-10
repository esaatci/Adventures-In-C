#include <stdio.h>

#define TO_CELSIUS(x) ((5 * ((x) - 32)) / 9)
#define TO_F(C) (((9 * (C)) / 5) + 32)

int main() {
	
	int fahr = 40;
	int cels = 100;
	printf("%d\t%d\n", fahr ,cels);

	float t;
	printf("Please enter a temp in F\n");
	scanf("%f", &t);
	t = TO_CELSIUS(t); 
	printf("howdy: %f\n", t);
	printf("to F is %2.2f\n", TO_F(35.1));
	return 0;
}
