/*
 * Write a function escape(s,t) that converts characters like newline
 * and tab into visible escape sequences like \n and \t as it copies
 * the string t to s.Use a switch.Write a function for the other dire
 * ction as well,converting escape sequences into the real characters.
 */

#include<stdio.h>
#define ON 1
#define OFF 0

void real()
{
        char c;
        int ESCAPE = OFF;
        while((c=getchar())!= '0')
        {
                if(ESCAPE) 
                {

                switch(c)

                {
                default: putchar(c);break;
                case 'a': printf("\a"); break;
                case 'b': printf("\b"); break;
                case 'f': printf("\f"); break;
                case 'n': printf("\n"); break;
                case 'r': printf("\r"); break;
                case 't': printf("\t"); break;
                case 'v': printf("\v"); break;
                case '\\':printf("\\"); break;
                }

                ESCAPE = OFF;

                }

                else 

                {
                if(c == '\\') ESCAPE = ON;
                else
                        putchar(c);
                }
        }

}
void escape()
{
        char c;
        while((c=getchar())!= '0')
        {

        switch(c)
 
        {
        default  : putchar(c)   ;break;
        case '\a': printf("\\a");break;
        case '\b': printf("\\b");break;            
        case '\f': printf("\\f");break;
        case '\n': printf("\\n\n");break;
        case '\r': printf("\\r");break;
        case '\t': printf("\\t");break;
        case '\v': printf("\\v");break;
        }
        }
}

int main(void)
{
        puts("Enter zero(0) to quit");
        puts("escape : converts escape characters to visible escape sequences\n"); escape();
        puts("Enter zero(0) to quit");
        puts("\nreal : converts visible escape sequences to escape characters\n"); real();
}
