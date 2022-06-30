#include <stdio.h>


char *getln(char *line);

int main() {
    char line[100];
    
    getln(line);
    printf("%s", line);
    
    return 0;
}

char *getln(char *line) {
    while ((*line++ = getchar()) != 10);
    *--line = 0;
    return line;
}
