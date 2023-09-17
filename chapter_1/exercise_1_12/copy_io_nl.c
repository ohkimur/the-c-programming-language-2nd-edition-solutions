#include <stdio.h>

int main()
{
  char c;
  char last_char = -1;
  while ((c = getchar()) != EOF) {
    if(c==' ' || c=='\t' ||  c=='\n'){
      if(last_char!=' ' &&  last_char!='\t' && last_char!='\n'){
        putchar('\n');
      }
    }
    else {
      putchar(c);
    }
    last_char=c;
  }
}
