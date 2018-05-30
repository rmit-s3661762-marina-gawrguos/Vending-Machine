/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{
    strcpy(menu[0].text,"Display Items");
    menu[0].function=displayItems;

    strcpy(menu[1].text,"Purchase Items");
    menu[1].function=purchaseItem;

    strcpy(menu[2].text,"Save and Exit");
    menu[2].function=saveAndExit;

    strcpy(menu[3].text,"Add Item");
    menu[3].function=addItem;

    strcpy(menu[4].text,"Remove Item");
    menu[4].function=removeItem;

    strcpy(menu[5].text,"Display Coins");
    menu[5].function=displayCoins;

    strcpy(menu[6].text,"Reset Stock");
    menu[6].function=resetStock;

    strcpy(menu[7].text,"Reset Coins");
    menu[7].function=resetCoins;

    strcpy(menu[8].text,"Abort Program");
    menu[8].function=abortProgram;
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{

    char userInput[INPUT_SIZE];
    displayMenu(menu);

        fgets(userInput, sizeof(userInput), stdin);
        if (userInput[strlen(userInput) - 1] != '\n') {
            printf("Buffer Overflow detected\n");
            readRestOfLine();
        } else {
            userInput[strlen(userInput) - 1] = '\0';
            if (strlen(userInput) != INPUT_LENGTH) {

            }
            else if (strcmp(userInput, "1") == 0) {

                return menu[0].function;


            }
            else if (strcmp(userInput, "2") == 0) {

                return menu[1].function;

            }
            else if (strcmp(userInput, "3") == 0) {

                return menu[2].function;

            }
            else if (strcmp(userInput, "4") == 0) {

                return menu[3].function;

            }
            else if (strcmp(userInput, "5") == 0) {

                return menu[4].function;

            }
            else if (strcmp(userInput, "6") == 0) {

                return menu[5].function;

            }
            else if (strcmp(userInput, "7") == 0) {

                return menu[6].function;

            }
            else if (strcmp(userInput, "8") == 0) {

                return menu[7].function;

            }
            else if (strcmp(userInput, "9") == 0) {

                return menu[8].function;

            } else{
                getMenuChoice(menu);
            }
        }

    return NULL;
}

/*method that prints out the menu by looping through the menu items array*/
void displayMenu(MenuItem * menu) {
    int i;
    printf("\nMain Menu:\n");
    for (i = 0; i < NO_OF_MENU_ITEMS; i++) {
        printf("%d.""%s\n", i + 1, menu[i].text);
        if(i==NUM)
        {
            printf("Adminstrator-only Menu:\n");
        }
    }
    printf("Select your option(1-9):\n");
}
