/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

int main(int argc, char *argv[]) {
    char *fileName = NULL;
    char *coinsFileName = NULL;
    VmSystem *system;
    /*creating list in the main*/
    List *list;
    system = malloc(sizeof(VmSystem));
    list = malloc(sizeof(List));

    /*initialising itemList to list*/
    system->itemList = list;
    if (argc < NO_OF_ARGS) {
        printf("Please provide more command line arguments.\n");
        exit(0);
    } else if (argc > NO_OF_ARGS) {
        printf("Too many command line arguments entered.\n");
        exit(0);
    } else if (argc == NO_OF_ARGS) {
        fileName = argv[COMMAND_ARGS_ONE];
        coinsFileName = argv[COMMAND_ARGS_TWO];
    }

    /*Initialising the system and loading the stock and coins into the system*/
    systemInit(system);
    loadData(system, fileName, coinsFileName);

    printMenu(system);
    return EXIT_SUCCESS;
}

void printMenu(VmSystem *system) {
    while (1) {
        char userInput[INPUTSIZE];
        printf("\nMain Menu\n");
        printf("1.Display Items\n");
        printf("2.Purchase Items\n");
        printf("3.Save and Exit\n");
        printf("Adminstrator-only Menu\n");
        printf("4.Add Item\n");
        printf("5.Remove Item\n");
        printf("6.Display Coins\n");
        printf("7.Reset Stock\n");
        printf("8.Reset Coins\n");
        printf("9.Abort Program\n");
        printf("Select your option(1-9):\n");

        fgets(userInput, INPUTSIZE, stdin);
        if (userInput[strlen(userInput) - 1] != '\n') {
            readRestOfLine();
        } else {
            userInput[strlen(userInput) - 1] = '\0';
            if (strcmp(userInput, "1") == 0) {
                displayItems(system);
            } else if (strcmp(userInput, "2") == 0) {
                purchaseItem(system);
            } else if (strcmp(userInput, "3") == 0) {
                saveAndExit(system);
            } else if (strcmp(userInput, "4") == 0) {
                addItem(system);
            } else if (strcmp(userInput, "5") == 0) {
                removeItem(system);
            } else if (strcmp(userInput, "6") == 0) {
                displayCoins(system);
            } else if (strcmp(userInput, "7") == 0) {
                resetStock(system);
            } else if (strcmp(userInput, "8") == 0) {
                resetCoins(system);
            } else if (strcmp(userInput, "9") == 0) {
                abortProgram(system);
            } else {
                printMenu(system);
            }
        }
    }
}
