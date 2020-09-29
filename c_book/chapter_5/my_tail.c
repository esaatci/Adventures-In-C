#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it
can be changed by an optional argument so that
tail -n prints the last n lines.

*/
#define ARGSIZE 2
#define MAXSIZE 5096

int main(int argc, char **argv) {
    int i, line, c, j;
    char *arg, **lines;
    /* Parse the input line arguments */

    // check argument number
    if (argc != ARGSIZE) {
        printf("invalid number of arguments\n");
        return 1;
    }

    // convert the input to integer
    arg = *(argv + 1);
    line = atoi(arg+1);

    if (line <= 0) {
        printf("invalid number of lines recieved!\n");
    }
    /* read the lines */

    // allocate space for lines
    lines = (char **) malloc(sizeof(char *) * line);
    for (i = 0; i < line; i++) {
        lines[i] = (char *) malloc(sizeof(char) * MAXSIZE);
        // reduces the time complexity of the last loop
        lines[i][0] = '\0';
    }

    i = j =  0;
    while ((c=getchar()) != EOF && j < MAXSIZE) {
        lines[i][j] = c;

        if (c == '\n') {
            lines[i][j] = '\0';
            j = 0;
            i++;
        } else {
            j++;
        }
        if (i == line) {
            i = 0;
        }
    }
    /* print the last n lines */
    for (j = i; j >= 0; j--) {
        printf("%s\n", lines[j]);
    }
    for (j = line-1; j != i; j--) {
        if (strlen(lines[j])) {
            printf("%s\n", lines[j]);
        }
    }
    return 0;
}
