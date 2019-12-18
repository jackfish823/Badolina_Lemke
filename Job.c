#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TIMESTRING 6
#define PERHOUR 35

typedef enum {EXIT, NEW, VIEW} Menu_Item;

typedef struct date
{
  int year;
  int month;
  int day;
}date;

typedef struct shift
{
  float salary;
  float time;
  int tip;
  char from[TIMESTRING];
  char to[TIMESTRING];
  date date;
}shiftStruct;

void timediff (char *start, char *end, int *hourLength, int *minutesLength)
{
  int hs, he, ms, me, hd, md, seconds1, seconds2, totalSeconds;

  sscanf(start, "%d:%d", &hs, &ms);
  sscanf(end, "%d:%d", &he, &me);

  if (he < hs) he = 24 + he;

  seconds1 = hs*60*60 + ms*60;
  seconds2 = he*60*60 + me*60;

  totalSeconds = seconds2-seconds1;

  md = totalSeconds/60;
  hd = md/60;
  md = md%60;

  *hourLength = hd;
  *minutesLength = md;
}

void New_Shift(struct tm time)
{
  int hourLength, minutesLength, tip, perh = PERHOUR, inputChoose;
  float hoursWork, sal;
  char startString[TIMESTRING], endString[TIMESTRING];
  shiftStruct currShift;
  FILE *f;

  printf("\n#New Shift#\n--------\n");

  printf("Date: %d-%d-%d\n\n", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);

  printf("Insert start time -> ");
  scanf("%s", startString);
  printf("Insert end time -> ");
  scanf("%s", endString);
  printf("Inset tip -> ");
  scanf("%d", &tip);

  timediff(startString, endString, &hourLength, &minutesLength);

  hoursWork = hourLength + (float)minutesLength / 100;

  sal = hoursWork * perh + tip;

  printf("\n\nThis shift got you: %0.2f ils\n\nExplenation:\n------------\n1. Worked %0.2fhrs for %d ils each hour\n\n2. Earned %d ils in tips\n", sal, hoursWork, perh, tip);
  printf("\nPress 1 to save shift or 0 to discard -> ");

  while (inputChoose != 1 || inputChoose != 0)
  {
    scanf("%d", &inputChoose);

    if (inputChoose == 1)
    {
      currShift.salary = sal;
      currShift.time = hoursWork;
      currShift.tip = tip;
      strcpy(currShift.from, startString);
      strcpy(currShift.to, endString);
      currShift.date.year = time.tm_year + 1900;
      currShift.date.month = time.tm_mon + 1;
      currShift.date.day = time.tm_mday;

      f = fopen ("SHIFTS.DAT", "ab");

      if(f == NULL)
        {
          printf("\n\nError!\n\n");
          exit(1);
        }

      fwrite(&currShift, sizeof(shiftStruct), 1, f);

      fclose(f);

      printf("\nSaved, back to main menu...\n\n");

      return;
    }

    else
          if (!inputChoose)
          {
            printf("\nDiscard, back to main menu...\n\n");
            return;
          }
  }
}

void View_Shifts()
{
  int count = 0, tips = 0;
  char key;
  shiftStruct currShift;
  float sal = 0;
  FILE *f;

  f = fopen ("SHIFTS.DAT", "rb");

  if(f == NULL)
    {
      printf("\n\nError!\n\n");
      exit(1);
    }

  printf("\n  $$$$$$$$$$$$$$$$$$$$$$$$$$\n  $ ALL OF THE SHIFTS LIST $\n  $$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");

  fread(&currShift, sizeof(shiftStruct), 1, f);
  while (!feof(f))
  {
    sal += currShift.salary - currShift.tip;
    tips += currShift.tip;
    count++;

    printf(" Date: %d-%d-%d        #%d\n From: %s TO %s\n Time: %0.2f\n Tip: %0d ils\n Salary: %0.2f ils\n Total %0.2f ils\n----------------------------\n", currShift.date.year, currShift.date.month, currShift.date.day, count, currShift.from, currShift.to, currShift.time, currShift.tip, currShift.salary-currShift.tip, currShift.salary);
    fread(&currShift, sizeof(shiftStruct), 1, f);
  }
  fclose(f);

    printf("\n# Salary check will be %0.2f ils! #\n# and %d in tips (total of %0.2f) #\n", sal, tips, sal+tips);

    key = getchar();
    key = getchar();
    return;
}

int main()
{
  //VARIABLE DECLERATION
  Menu_Item selection;
  time_t t = time(NULL); //for date
  struct tm tm = *localtime(&t); //for date

  //HEADER
  printf("$$Welecome to badolina salary maneger$$\n\n");

  //MENU
  printf("Menu:\n---------\n1. New shift\n2. View shifts\n0. Exit\n---------\n");
  printf("Choose -> ");

  //SELECT
  scanf("%d", &selection);

  while (selection != EXIT)
  {
    switch (selection)
    {
      case NEW:
        New_Shift(tm);
      break;

      case VIEW:
        View_Shifts();
      break;

      case EXIT:

      break;

      deafult:

      break;
    }
    //MENU
    printf("\nMenu:\n---------\n1. New shift\n2. View shifts\n0. Exit\n---------\n");
    printf("Choose -> ");

    //SELECT
    scanf("%d", &selection);
  }
}
