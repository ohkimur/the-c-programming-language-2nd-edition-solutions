#include <stdio.h>

#define MAXLEN 1000
#define BUFFSIZE 1000

int getstr(char line[], int limit);
void ungetstr(char line[]);

int main(void)
{
    char line[MAXLEN];
    char temp[MAXLEN];

    getstr(line, MAXLEN);
    printf("%s", line);

    ungetstr(line);

    getstr(temp, MAXLEN);
    printf("buf: %s--", temp);

    return 0;
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }
}

int getstr(char line[], int limit)
{
    int i = 0, c;

    printf("%d\n", bufp);
    printf("%c\n", buf[0]);
    printf("exec\n");

    while(limit - 1 > 0 && (c = getch()) != EOF && c != '\n')
    {

        printf("entered\n");
        line[i++] = c;
    }

    if(c == '\n')
    {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}

void ungetstr(char line[])
{
    int i = 0;

    while(line[i] != '\0')
    {
        ungetch(line[i++]);
    }
}

// Exercise page: 93

// OBS: Silence is golden.