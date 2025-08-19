#include <stdio.h>

#define TABSIZE 8

int main() {
    	int c, next, pos;
	
	pos = 0;
	while((c = getchar()) != EOF) {
		if(c == '\\') {
			next = getchar();
			if(next == 't') {
				int spaces = TABSIZE - (pos % TABSIZE);

				for(int i = 0; i < spaces; ++i)
					putchar(' ');
				pos += spaces;	
			}
			else {
				putchar(c);
				++pos;
				putchar(next);
				++pos;
			}
		}
		else {
			if(c == '\n')
				pos = 0;
			else
				++pos;
			putchar(c);
		}
	}
	return 0;
}

// NOTE: In UNIX like systems you can execute commands like this:
// ./detab < file_in.txt > file_out.txt that takes the input from a
// file and after the program processed its content puts it to another file.
