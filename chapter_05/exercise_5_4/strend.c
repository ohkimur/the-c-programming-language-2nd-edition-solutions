#include <stdio.h>

unsigned int strlen(char *s);
int strend(char *s, char *t);

int main(void)
{
  char *s = "This si a simple string";
  char *t1 = "string";
  char *t2 = "random string";

  // Test if the string t1 occurs at the end of string s.
  if (strend(s, t1))
    puts("The string t1 orrurs at the end of the string s.");
  else
    puts("The string t1 doesn't orrur at the end of the string s.");

  // Test if the string t2 occurs at the end of string s.
  if (strend(s, t2))
    puts("The string t2 orrurs at the end of the string s.");
  else
    puts("The string t2 doesn't orrur at the end of the string s.");

  return 0;
}

// Returns the length of the string.
unsigned int strlen(char *s)
{
  unsigned int str_length = 0;

  while ((*++s) != '\0')
    ++str_length;

  return str_length;
}

//  Returns 1 if the string t occurs at the end of the string s, and zero otherwise.
int strend(char *s, char *t)
{
  // Determine the lengths of the strings.
  unsigned int s_length = strlen(s);
  unsigned int t_length = strlen(t);

  // Move the s & t pointer to the end of the corresponding strings.
  s += s_length;
  t += t_length;

  // Check backwards if each character from string t occurs in the corresonding
  // location from the string s.
  while (t_length && (*s-- == *t--))
    --t_length;

  if (t_length)
    return 0;

  return 1;
}

// Exercise page: 121

// NOTE: Silence is golden.
