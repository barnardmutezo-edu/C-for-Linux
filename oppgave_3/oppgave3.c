#include "./include/ConsoleManager.h"
#include "./include/ListManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ACTIVE 1;

int main(void)
{
    unsigned char isActive = ACTIVE; // Keeps track when to quit the program.
    unsigned char choice; // Keeps track of users choice.
    unsigned char changeMade = 0;
    

    NODE* head = NULL; // Pointer to the first element of the list. Found in Node.h

    greetUser(&head); // Found in ConsoleManager.h and ConsoleManager.c

    while (isActive)
    {
        printMenu(&choice); // Found in ConsoleManager.h and ConsoleManager.c
        switch (choice)
        {
        case 0:
            askToSave(&head,&changeMade);
            freeHeap(&head); // Found in Listmanager.h and ListManager.c
            isActive = !ACTIVE;
            break;
        case 1:
            addToList(&head,&changeMade); // Found in Listmanager.h and ListManager.c
            break;
        case 2:
            removeLastNode(&head,&changeMade); // Found in Listmanager.h and ListManager.c
            break;    
        case 3:
            getNameToDelete(&head,&changeMade); // Found in Listmanager.h and ListManager.c
            break;    
        case 4:
            calculateSum(&head); // Found in Listmanager.h and ListManager.c
            break;
        case 5:
            printReceipt(&head); // Found in Listmanager.h and ListManager.c
            break;
        case 6:
            deleteAll(&head, &changeMade); // Found in Listmanager.h and ListManager.c
            break;
        default:
            break;
        }
    }
    return 0;
}