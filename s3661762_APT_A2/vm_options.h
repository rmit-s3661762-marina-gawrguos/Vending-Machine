/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H
#define BUFFER_SIZE 200
#define VERTICAL_DELIM "|"
#define DOT_DELIM "."
#define COMMA_DELIM ","
#define INPUTSIZE 50
#define BASE 10
#define DOLLAR_IN_CENTS 100
#define DIVISIBLE_BY_FIVE 5
#define MIN_AMT_DOLLARS 0
#define MAX_AMT_DOLLARS 99
#define MAX_LENGTH_CENTS 3
#include "vm_stock.h"

Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
void removeItem(VmSystem * system);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);
void validatingPrice(Stock *stock);
#endif
