#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pda);

static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                             {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main(void)
{
  int day = day_of_year(2020, 10, 30);
  printf("day of the year: %d\n", day);

  int month;
  int day_month;
  month_day(2020, 304, &month, &day_month);
  printf("month: %d, day: %d\n", month, day_month);

  return 0;
}

int day_of_year(int year, int month, int day)
{
  int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  int i;
  for (i = 1; i < month; i++)
  {
    day += daytab[leap][i];
  }

  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pda)
{
  int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  int i;
  for (i = 0; yearday > daytab[leap][i]; i++)
  {
    yearday -= daytab[leap][i];
  }

  *pmonth = i;
  *pda = yearday;
}
