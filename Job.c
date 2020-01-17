#include "header.h"

int main()
{
  //VARIABLE DECLERATION
  Menu_Item selection;
  time_t t = time(NULL); //for date
  struct tm tm = *localtime(&t); //for date

  //HEADER
  printf(" ____            _       _ _             \n|  _ \\          | |     | (_)            \n| |_) | __ _  __| | ___ | |_ _ __   __ _ \n|  _ < / _` |/ _` |/ _ \\| | | '_ \\ / _` |\n| |_) | (_| | (_| | (_) | | | | | | (_| |\n|____/ \\__,_|\\__,_|\\___/|_|_|_| |_|\\__,_|\n\n");

  selection = Menu();

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

    selection = Menu();
  }
}
