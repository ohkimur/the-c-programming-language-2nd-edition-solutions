#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFFSIZE 100
#define NUMBER '0'

#define VARSET '_'
#define VARGET 'a'
#define VARNUM 26
char var = '0';

enum boolean { FALSE, TRUE };

int getop(char[]);

void push(double f);
double pop(void);
int is_empty(void);
void view_head(void);
void duplicate(void);
void swap(void);
void clear(void);

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    int varindex = 0;
    double var_buff[VARNUM];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;

        case '+':
            push(pop() + pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '*':
            push(pop() * pop());
            break;

        case '/':
            op2 = pop();

            if (op2 != 0.0) {
                push(pop() / op2);
            } else {
                printf("Error: zero divisor.\n");
            }

            break;

        case '%':
            op2 = pop();

            if (op2 != 0.0) {
                push((int)pop() % (int)op2);
            } else {
                printf("Error: zero divisor.\n");
            }
            break;

        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;

        case '~':
            push(sin(pop()));
            break;

        case 'E':
            push(exp(pop()));
            break;

        case 'H':
            view_head();
            break;

        case 'D':
            duplicate();
            break;

        case 'S':
            swap();
            break;

        case 'C':
            clear();
            break;

        case VARSET:
            var_buff[varindex++] = pop();
            printf("variable %c: %.3f\n", 'a' + varindex - 1,
                   var_buff[varindex - 1]);
            break;

        case VARGET:
            // Check if the variable has been assigned previously
            if (var - 'a' <= (varindex - 1)) {
                push(var_buff[var - 'a']);
            } else {
                printf("Error: undefined variable.\n");
            }
            break;

        case '\n':
            if (!is_empty()) {
                printf("result: %.8g\n", pop());
            }
            break;

        default:
            printf("Error: unknown command %s.\n", s);
            break;
        }
    }

    return 0;
}

int sp = 0;
double stack[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) {
        stack[sp++] = f;
    } else {
        printf("Error: stack full.\n");
    }
}

double pop(void) {
    if (sp > 0) {
        return stack[--sp];
    } else {
        printf("Error: stack empty.\n");
    }

    return 0.0;
}

int is_empty(void) {
    if (sp > 0) {
        return FALSE;
    }

    return TRUE;
}

void view_head(void) {
    if (sp) {
        printf("stack_head: %g\n", stack[sp - 1]);
    } else {
        printf("Error: stack empty.\n");
    }
}

void duplicate(void) {
    double temp = pop();
    push(temp);
    push(temp);
}

void swap(void) {
    double temp1 = pop();
    double temp2 = pop();

    push(temp1);
    push(temp2);
}

void clear(void) {
    do {
        stack[sp] = 0.0;
    } while (sp--);
}

int bufp = 0;
char buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

int getop(char s[]) {
    int i = 0;
    int c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (islower(c)) {
        var = c;
        return VARGET;
    }

    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    if (c == '-') {
        int next = getch();
        if (next == '\n' || next == ' ' || next == '\t') {
            ungetch(next);
            return c; // return '-' as operator
        } else if (!isdigit(next) && next != '.') {
            return next; // not a number
        } else           // number like "-5", "-.6" etc, next is digit or '.'
        {
            s[++i] = c = next;
        }
    } else {
        c = getch();
    }

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}
