#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0
#define BUF_SIZE 1024

int buf[BUF_SIZE];

int main() {
	
	int c, nl, nw, nc, state;
	int buf_idx = 0;
	state = OUT;
	nl = nw = nc = 0;
	while((c = getchar()) != EOF) {
		++nc;
		if(c  == '\n')
			++nl;
		if(c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			// print the word
			int i = 0;
			while(i <= buf_idx) {
				putchar(buf[i]);
				++i;
			}
			putchar('\n');
			// clear the buf
			memset(&buf, 0, BUF_SIZE*sizeof(int));
			buf_idx = 0;
		}
		else if(state == OUT) {	
			state = IN;
			++nw;
		}

		if(state == IN) {
			if(buf_idx == BUF_SIZE) {
				printf("BUF size reached!\n");
				continue;
			}
			buf[buf_idx] = c;
			++buf_idx;
			
		}
	}

	printf("%d %d %d\n", nl, nw, nc);

}


