/******************************************************************************
** Student name: 	Marina Gawrguos
** Student number: 	s3661762
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */
int listAdd(Stock* stock, VmSystem* system)
{

    Node* previousNode, *currentNode, *newNode;
    currentNode=system->itemList->head;
    previousNode=NULL;
    newNode=malloc(sizeof(Node));
    if(newNode==NULL)
    {
        printf("Error:Failed to allocate Memory.\n");
        return FALSE;
    }
    newNode->data=stock;
    newNode->next=NULL;
    if (currentNode==NULL)
    {
        system->itemList->head=newNode;
        system->itemList->size++;
        return TRUE;
    }

    while(currentNode!=NULL&&strcmp(currentNode->data->name,stock->name)<0)
    {
        previousNode=currentNode;
        currentNode=currentNode->next;
    }

    /*if currentNode is null, add the node to the end of the list*/
    if(currentNode==NULL)
    {
        previousNode->next=newNode;

    }
        /*if the previous node is null, this node becomes the head*/
    else if(previousNode==NULL)
    {
        newNode->next=system->itemList->head;
        system->itemList->head=newNode;
    }
    /*if the node is node is neither the head or tail, it is inserted in the middle of the list*/
    else
    {
        previousNode->next=newNode;
        newNode->next=currentNode;
    }
    system->itemList->size++;
    return TRUE;
}
/*printNode and printList functions used for debugging purposes*/
void printNode(Stock* stock)
{
    printf("%s,%s,%s,%d,%d,%d\n",stock->id,stock->name,stock->desc,stock->price.dollars,stock->price.cents,stock->onHand);
}

void printList(VmSystem* system)
{

    Node* currentNode=NULL;
   currentNode=system->itemList->head;

    while(currentNode!=NULL)
    {
        printNode(currentNode->data);
        currentNode=currentNode->next;
    }

}

/*printSpecifDataInNode and printMenuList are methods used for displaying the items*/
void printSpecifDataInNode(Stock* stock)
{
    printf("%s|%-21s|%-11d|$%d.%0.2d\n",stock->id,stock->name,stock->onHand,stock->price.dollars,stock->price.cents);
}

void printMenuList(VmSystem* system)
{

    Node* currentNode=NULL;
    currentNode=system->itemList->head;

    while(currentNode!=NULL)
    {
        printSpecifDataInNode(currentNode->data);
        currentNode=currentNode->next;
    }

}
/*loops the linked list and frees the nodes and stock*/
void freeList(VmSystem* system)
{
    Node* currentNode, *removeNode;
    Stock* stock;
    currentNode=system->itemList->head;

    while(currentNode!=NULL)
    {
        removeNode=currentNode;
        stock=removeNode->data;
        currentNode=currentNode->next;
        free(stock);
        free(removeNode);
    }
}
