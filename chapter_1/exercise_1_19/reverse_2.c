#include <stdio.h>

int getline(char[]);
void reverse(char[]);

int main() {
    int res;
    char line[1000]; 
    while (res = getline(line)) {
        reverse(line);
        printf("%s", line);
        if (res != EOF) printf("\n", line);
        else break;
    }
}

int getline(char s[]) {
    int c, i = -1;
    while ((c = getchar()) != EOF && c != '\n') {
        s[++i] = c;
    }
    s[i == -1 ? 0 : i + 1] = '\0';
    return c;
}

void reverse(char s[]) {
    int len = 0;
    char buffer;
    while (s[len] != '\0')
        len += 1;
    for (int i = 0; i < len / 2; i++) {
        buffer = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = buffer;
    }
}
