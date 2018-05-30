/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"
int listAdd(Stock* stock,VmSystem* system);
void printNode(Stock* stock);
void printList(VmSystem* system);
void printSpecifDataInNode(Stock* stock);
void printMenuList(VmSystem* system);
void freeList(VmSystem* system);
#endif
