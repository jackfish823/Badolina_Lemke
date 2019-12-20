#include "header.h"

int main()
{
  //VARIABLE DECLERATION
  Menu_Item selection;
  time_t t = time(NULL); //for date
  struct tm tm = *localtime(&t); //for date

  //HEADER
  printf("$$ Welecome to badolina salary maneger $$\n\n");

  //MENU
  printf("Menu:\n---------\n1. New shift\n2. View shifts\n0. Exit\n---------\n");
  printf("Choose -> ");

  //SELECT
  scanf("%d", &selection);

  while (selection != EXIT)
  {
    switch (selection)
    {
      case NEW: //new shift
        New_Shift(tm);
      break;

      case VIEW: //view shifts
        View_Shifts();
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
