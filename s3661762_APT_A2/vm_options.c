/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_options.h"

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem *system) {
    /*initialising the size and the head of linked list*/
    system->itemList->head = NULL;
    system->itemList->size = 0;
    return FALSE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem *system) {}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
        VmSystem *system, const char *stockFileName, const char *coinsFileName) {
    loadStock(system, stockFileName);
    loadCoins(system, coinsFileName);
    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem *system, const char *fileName) {

    Stock *stock;
    Price *price;
    char *singleLine = NULL;
    char *token = NULL;
    FILE *stockFile = NULL;
    char *endPtr = NULL;
    price = malloc(sizeof(Price));
    singleLine = malloc(sizeof(Stock));
    stockFile = fopen("stock.dat", "r");
    /*loop through all the lines in the stock file until the line is NULL and tokenises accordingly*/
    while (fgets(singleLine, sizeof(Stock), stockFile) != NULL) {
        stock = malloc(sizeof(Stock));

        token = strtok(singleLine, VERTICAL_DELIM);
        strcpy(stock->id, token);

        token = strtok(NULL, VERTICAL_DELIM);
        strcpy(stock->name, token);

        token = strtok(NULL, VERTICAL_DELIM);
        strcpy(stock->desc, token);

        token = strtok(NULL, DOT_DELIM);
        price->dollars = (unsigned) strtol(token, &endPtr, BASE);


        token = strtok(NULL, VERTICAL_DELIM);
        price->cents = (unsigned) strtol(token, &endPtr, BASE);
        stock->price = *price;

        token = strtok(NULL, VERTICAL_DELIM);
        stock->onHand = (unsigned) strtol(token, &endPtr, BASE);
/*calling the listAdd function in stock.c to add the items in the stock file to the linked list*/
        listAdd(stock, system);
    }

    fclose(stockFile);

    return FALSE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem *system, const char *fileName) {
    Coin *coins;
    char *singleLine = NULL;
    char *token = NULL;
    FILE *coinsFile = NULL;
    char *endPtr = NULL;
    int i;
    i = 0;
    singleLine = malloc(sizeof(Coin));
    coinsFile = fopen("coins.dat", "r");
    /*looping through all the lines in the coins file until the line is NULL and tokenises the coins accordingly*/
    while (fgets(singleLine, sizeof(Coin), coinsFile) != NULL) {
        coins = malloc(sizeof(Coin));
        token = strtok(singleLine, COMMA_DELIM);
        system->cashRegister[i].denom = (Denomination) strtol(token, &endPtr, BASE);
        token = strtok(NULL, COMMA_DELIM);
        system->cashRegister[i].count = (Denomination) strtol(token, &endPtr, BASE);
        i++;
    }
    fclose(coinsFile);

    return FALSE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem *system) {


    FILE *stockFile = NULL;
    Node *previousNode, *currentNode;
    currentNode = system->itemList->head;
    previousNode = NULL;
    stockFile = fopen("stock.dat", "w");
    if (stockFile == NULL) {
        fprintf(stderr, "Failed to Write to StockFile\n");
        return FALSE;
    }
    /*loops through the linked list while currentNode is not NULL and writes to the file*/
    while (currentNode != NULL) {
        fprintf(stockFile, "%s|%s|%s|%d.%0.2d|%d\n", currentNode->data->id, currentNode->data->name,
                currentNode->data->desc, currentNode->data->price.dollars, currentNode->data->price.cents,
                currentNode->data->onHand);
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    fclose(stockFile);
    return TRUE;


    /*freeList(system);*/


}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem *system) {
    FILE *coinsFile = NULL;
    int i;
    coinsFile = fopen("coins.dat", "w");
    if (coinsFile == NULL) {
        fprintf(stderr, "Failed to Write to CoinsFile\n");
        return FALSE;
    }
    for (i = 0; i < NUM_DENOMS; i++) {
        fprintf(coinsFile, "%d,%d\n", system->cashRegister[i].denom, system->cashRegister[i].count);
    }
    fclose(coinsFile);
    return TRUE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem *system) {
    printf("\nItems Menu\n");
    printf("\nID   | Name                | Available | Price\n");
    printf("-----------------------------------------------\n");
    printMenuList(system);
    printf("\n");

}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem *system) {

    char userInput[INPUTSIZE];
    long amtToGive = 0;
    long input = 0;
    int price = 0;
    Boolean valid = FALSE;
    char *endPtr = NULL;
    Node *previousNode, *currentNode;
    currentNode = system->itemList->head;
    previousNode = NULL;
    while (valid == FALSE) {
        printf("\nPurchase Item\n");
        printf("-----------------\n");
        printf("Please enter the ID of the item you wish to purchase: ");
        fgets(userInput, INPUTSIZE, stdin);
        if (userInput[0] == '\n') {
            printf("Returning to Menu...\n");
            return;
        }
        if (userInput[0] != 'I') {
            printf("Invalid ID of item enetered. Please try again\n");
            continue;
        }
        if (userInput[strlen(userInput) - 1] != '\n') {
            readRestOfLine();
        } else {
            userInput[strlen(userInput) - 1] = '\0';
            while (currentNode != NULL) {
                if (strcmp(userInput, currentNode->data->id) == 0 && currentNode->data->onHand > 0) {
                    printf("You have selected %s %s . This will cost you $%d.%0.2d \n", currentNode->data->name,
                           currentNode->data->desc, currentNode->data->price.dollars, currentNode->data->price.cents);
                    price = (currentNode->data->price.dollars * DOLLAR_IN_CENTS) + currentNode->data->price.cents;
                    printf("Please hand over the money - type in the value of each note/coins in cents.\n");
                    printf("Press enter on a new and empty line to cancel this purchase: \n");
                    printf("You still need to give us: $%d.%0.2d:", currentNode->data->price.dollars,
                           currentNode->data->price.cents);
                    userInput[strlen(userInput) - 1] = '\0';
                    amtToGive = price;
                    while (amtToGive > 0) {
                        fgets(userInput, INPUTSIZE, stdin);
                        if (userInput[0] == '\n') {
                            printf("Failed to purchase item successfully.Returning to Menu...\n");
                            return;
                        }
                        if (userInput[strlen(userInput) - 1] != '\n') {
                            readRestOfLine();
                        } else {
                            userInput[strlen(userInput) - 1] = '\0';
                            if (strcmp(userInput, "5") == 0 || strcmp(userInput, "10") == 0 ||
                                strcmp(userInput, "20") == 0 || strcmp(userInput, "50") == 0 ||
                                strcmp(userInput, "100") == 0 || strcmp(userInput, "200") == 0 ||
                                strcmp(userInput, "500") == 0 || strcmp(userInput, "1000") == 0) {
                                input = strtol(userInput, &endPtr, BASE);
                                amtToGive = amtToGive - input;
                                if (amtToGive > 0) {
                                    printf("You still need to give us:$%0.2f:", (double) amtToGive / DOLLAR_IN_CENTS);
                                }
                            } else {
                                input = strtol(userInput, &endPtr, BASE);
                                printf("Error: $%0.2f is not a valid denomination of money.\n",
                                       (double) input / DOLLAR_IN_CENTS);
                                printf("You still need to give us: $%0.2f:", (double) amtToGive / DOLLAR_IN_CENTS);
                            }
                        }
                    }
                    if (amtToGive < 0) {
                        long change = amtToGive * -1;
                        printf("Thank you. Here is your %s, and your change is $%0.2f\n",
                               currentNode->data->name, (double) change / DOLLAR_IN_CENTS);
                        printf("Please come back soon.\n");
                        currentNode->data->onHand--;
                        return;
                    } else if (amtToGive == 0) {
                        printf("Thank you. Here is your %s\n", currentNode->data->name);
                        printf("Please come back soon.\n");
                        currentNode->data->onHand--;
                        valid = TRUE;
                    }
                    previousNode = currentNode;
                }
                currentNode = currentNode->next;
            }
        }
    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem *system) {
    printf("goodbye\n");
    saveStock(system);
    saveCoins(system);
    freeList(system);
    exit(0);

}

void validatingPrice(Stock *stock) {
    char new_Item_Price[INPUTSIZE];
    char *endPtr = NULL;
    char *dollars = NULL;
    char *cents = NULL;
    int dollar;
    int cent;

    Boolean valid = FALSE;

    while (valid == FALSE) {
        fgets(new_Item_Price, INPUTSIZE, stdin);
        if (new_Item_Price[0] == '\n') {
            printf("Returning to Menu...\n");
            return;
        }

        if (new_Item_Price[strlen(new_Item_Price) - 1] != '\n') {
            readRestOfLine();
        } else {

            dollars = strtok(new_Item_Price, ".");
            dollar = (unsigned) strtol(dollars, &endPtr, BASE);
            if (dollar < MIN_AMT_DOLLARS || dollar > MAX_AMT_DOLLARS) {
                printf("Invalid price entered. Please try again.\n");
                continue;

            } else if (dollar == (int) endPtr || *endPtr != '\0') {
                printf("Invalid price entered. Please try again.\n");
                continue;
            } else {
                cents = strtok(NULL, ".");
                cent = (unsigned) strtol(cents, &endPtr, BASE);
                if (strlen(cents) != MAX_LENGTH_CENTS) {
                    printf("Invalid price entered. Please try again.\n");
                    continue;
                } else if (cent % DIVISIBLE_BY_FIVE != 0) {
                    printf("Invalid price entered. Please try again.\n");
                    continue;
                } else {
                    stock->price.dollars = (unsigned) dollar;
                    stock->price.cents = (unsigned) cent;
                    valid = TRUE;
                }
            }
        }
    }
}


/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem *system) {
    Stock *stock;
    Boolean valid;
    Node *previousNode, *currentNode;
    char new_Item_ID[INPUTSIZE];
    char new_Item_Name[INPUTSIZE];
    char new_Item_Descrip[INPUTSIZE];
    char *endPtr;
    endPtr = NULL;
    valid = FALSE;
    stock = malloc(sizeof(Stock));
    previousNode = NULL;
    currentNode = system->itemList->head;

    printf("\nAdd Item\n");
    printf("----------\n");
    printf("Please enter the ID of the new Item:\n");
    fgets(new_Item_ID, INPUTSIZE, stdin);
    if (new_Item_ID[0] == '\n') {
        printf("Returning to Menu...\n");
        return;
    }
    if (new_Item_ID[strlen(new_Item_ID) - 1] != '\n') {
        readRestOfLine();
    } else {
        new_Item_ID[strlen(new_Item_ID) - 1] = '\0';


        while (currentNode != NULL) {
            if (strcmp(new_Item_ID, currentNode->data->id) == 0) {
                printf("ID already exists in the vm system.\n");
                return;

            } else if (new_Item_ID[0] != 'I') {
                printf("Invalid ID entered.\n");
                return;

            } else if (strlen(new_Item_ID) != 5) {
                printf("Invalid ID entered.\n");
                return;

            } else {
                strcpy(stock->id, new_Item_ID);


            }
            currentNode = currentNode->next;
        }
    }

    do {
        printf("Enter the Item name: \n");
        fgets(new_Item_Name, INPUTSIZE, stdin);
    } while (strlen(new_Item_Name) > NAME_LEN);

    if (new_Item_Name[0] == '\n') {
        printf("Returning to Menu...\n");
        return;
    }
    if (new_Item_Name[strlen(new_Item_Name) - 1] != '\n') {
        readRestOfLine();
    } else {
        new_Item_Name[strlen(new_Item_Name) - 1] = '\0';
        strcpy(stock->name, new_Item_Name);
    }
    do {
        printf("Enter the Item description: \n");
        fgets(new_Item_Descrip, INPUTSIZE, stdin);
    } while (strlen(new_Item_Descrip) > DESC_LEN);
    if (new_Item_Descrip[0] == '\n') {
        printf("Returning to Menu...\n");
        return;
    }
    if (new_Item_Descrip[strlen(new_Item_Descrip) - 1] != '\n') {
        readRestOfLine();
    } else {
        new_Item_Descrip[strlen(new_Item_Descrip) - 1] = '\0';
        strcpy(stock->desc, new_Item_Descrip);
    }
    printf("Enter the price for this item:\n");
    validatingPrice(stock);
    stock->onHand = DEFAULT_STOCK_LEVEL;
    printf("This Item: %s - %s has now been added to the menu.\n", new_Item_Name, new_Item_Descrip);
    listAdd(stock, system);
    return;

}


/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem *system) {
    char userInput[INPUTSIZE];
    Boolean valid = FALSE;
    Node *previousNode, *currentNode, *deleteNode;
    currentNode = system->itemList->head;
    previousNode = NULL;
    deleteNode = NULL;
    while (valid == FALSE) {
        printf("Enter the Item ID of the item to remove from menu: ");
        fgets(userInput, INPUTSIZE, stdin);
        if (userInput[0] == '\n') {
            printf("Returning to Menu...\n");
            return;
        }
        if (userInput[strlen(userInput) - 1] != '\n') {
            readRestOfLine();
        } else {
            userInput[strlen(userInput) - 1] = '\0';

            while (currentNode != NULL) {
                if (strcmp(userInput, currentNode->data->id) == 0) {
                    /*deleting head Node*/
                    if (previousNode == NULL) {
                        deleteNode = system->itemList->head;
                        system->itemList->head = system->itemList->head->next;
                    } else {
                        deleteNode = currentNode;
                        previousNode->next = currentNode->next;
                    }
                    printf("%s - %s has been removed.\n", userInput, currentNode->data->desc);
                    free(deleteNode);
                    system->itemList->size--;
                    valid = TRUE;
                    return;
                } else {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                    continue;
                }
            }
        }
        printf("ID entered does not exist.\n");
        return;
    }

}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem *system) {

    printf("Coins Summary\n");
    printf("-------------\n");
    printf("Denomination | Count\n\n");

    printf("5 cents      |%d\n", system->cashRegister[0].count);
    printf("10 cents     |%d\n", system->cashRegister[1].count);
    printf("20 cents     |%d\n", system->cashRegister[2].count);
    printf("50 cents     |%d\n", system->cashRegister[3].count);
    printf("1 dollar     |%d\n", system->cashRegister[4].count);
    printf("2 dollar     |%d\n", system->cashRegister[5].count);
    printf("5 dollar     |%d\n", system->cashRegister[6].count);
    printf("10 dollar    |%d\n", system->cashRegister[7].count);
}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem *system) {
    Node *previousNode, *currentNode;
    currentNode = system->itemList->head;
    previousNode = NULL;

    while (currentNode != NULL) {
        currentNode->data->onHand = DEFAULT_STOCK_LEVEL;
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    printf("All stock has been reset to the default level of %d\n", DEFAULT_STOCK_LEVEL);
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem *system) {
    int i;
    for (i = 0; i < NUM_DENOMS; i++) {
        system->cashRegister->count = DEFAULT_COIN_COUNT;
    }
    printf("All coins have been reset to the default level of %d\n", DEFAULT_COIN_COUNT);
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem *system) {
    printf("Goodbye\n");
    freeList(system);
    exit(0);

}

void convertDenomination(VmSystem *system, Denomination denom) {

}
