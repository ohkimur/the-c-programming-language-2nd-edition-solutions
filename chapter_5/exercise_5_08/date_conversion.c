#include <stdio.h>

static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                             {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pda);

int main(void)
{
  int day = day_of_year(2020, 10, 30);
  printf("day of the year: %d\n", day);

  int month_invalid = day_of_year(2020, 13, 1);
  if (month_invalid == -1)
  {
    printf("Warning: invalid month detected.\n");
  }

  int day_invalid = day_of_year(202, 12, 32);
  if (day_invalid == -2)
  {
    printf("Warning: invalid day detected.\n");
  }

  int month;
  int day_month;

  month_day(2020, 304, &month, &day_month);
  printf("month: %d, day: %d\n", month, day_month);

  month_day(2020, 366, &month, &day_month);
  printf("month: %d, day: %d\n", month, day_month);

  month_day(2020, 367, &month, &day_month);
  printf("month: %d, day: %d\n", month, day_month);

  return 0;
}

int day_of_year(int year, int month, int day)
{
  int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

  // Additional checks for month.
  if (month > 12)
  {
    printf("Error: a year has 12 months, so please choose a number betweeen 1 and 12.\n");
    return -1;
  }

  // Additional checks for day.
  if (day > daytab[leap][month])
  {
    printf("Error: the %d month has a maximum of %d days.\n", month, daytab[leap][month]);
    return -2;
  }

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

  // Additional check for yearday.
  if ((!leap && yearday > 365) || (leap && yearday > 366))
  {
    // Reset the provided month and day.
    *pmonth = 0;
    *pda = 0;
    printf("Error: year %d has %d days.\n", year, leap ? 366 : 365);

    return;
  }

  int i;
  for (i = 0; yearday > daytab[leap][i]; i++)
  {
    yearday -= daytab[leap][i];
  }

  *pmonth = i;
  *pda = yearday;
}
