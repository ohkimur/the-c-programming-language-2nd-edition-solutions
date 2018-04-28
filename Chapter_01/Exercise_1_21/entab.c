#include <stdio.h>

#define MAXLINE 1000
#define TABWIDTH 8

int getln(char line[], int limit);
void entab(char line[], char etline[]);

int main()
{
    char line[MAXLINE];
    char etline[MAXLINE];

    getln(line, MAXLINE);
    
    entab(line, etline);

    printf("%s", etline);

    return 0;
}

int getln(char line[], int limit)
{
    int c, i = 0;

    while(i < limit - 1 && (c = getchar()) != EOF && c != '\n')
    {
        line[i++] = c;
    }

    if(c == '\n')
    {
        line[i++] = c;
    }

    line[i] = '\0';

    return i;
}

void entab(char line[], char etline[])
{
    int i = 0, j = 0;
    int spacew = 0;

    while(line[i] != '\0')
    {
        while(line[i] == ' ' || line[i] == '\t')
        {
            if(line[i] == ' ')
            {
                ++spacew;
            }
            else
            {
                spacew += TABWIDTH;
            }
            
            ++i;
        }

        int tabs = spacew / TABWIDTH;
        int spaces = spacew % TABWIDTH;

        while(tabs-- > 0)
        {
            etline[j++] = '-';
            spacew -= TABWIDTH;
        }

        while(spaces-- > 0)
        {
            etline[j++] = '+';
            --spacew;
        }

        etline[j++] = line[i++];
    }

    if(line[i] == '\n')
    {
        etline[j++] = line[i];
    }

    printf("spacew: %d\n", spacew);

    etline[j] = '\0';
}

// Exercise page: 48

// OBS: This solution is simple and very obvious. Count the number of
// spaces and that determine how many tabs and spaces can fit in that
// number. After this just add the tabs and spaces to the new array.