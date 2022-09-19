#include "./include/ConsoleManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMenu(unsigned char *choice)
{
    printf("\n******Receipt Manager******\n\n");
    
    printf("0: Exit\n");
    printf("1: Add to the back of the Queueue (enqueue).\n");
    printf("2: Remove from back of the Queueue.\n");
    printf("3: Delete given name.\n");
    printf("4: Sum total price.\n");
    printf("5: Print receipt.\n");
    printf("6: Delete all.\n");

    printf("-> ");
    
    if (scanf("%hhd",choice)); // Get rid of compiler warnings

    printf("\n");
}

void greetUser(NODE** headP) // This function welcomes the user based on the time of the day
{
    printf("\n");
    unsigned char t;
    unsigned char* greeting = NULL;
    
    setTime(&t);

    // Here i use ternary condition to set the message to display to user
    greeting = (t >= 0 && t<6)? "Good Night!" : 
               (t>=6 && t<=11) ? "Good Morning!" : 
               (t>=12 && t<18) ? "Good Afternoon!" : 
               "Good Evening!";

    printf("%s ", greeting); 

    if (loadFromFile(headP,"database.csv"))
    {
        printf("The previous session is available.\n");
    } else 
    {
        printf("The database is empty, start adding stuff!\n");  
    }


}


void setTime(unsigned char* t)
{

    time_t currTime;
    struct tm * timeDetails; 
    time (&currTime);
    
    timeDetails = localtime (&currTime); // set current time to localtime

    *t = timeDetails->tm_hour; // get the hour
}

// Små snacks
void askToSave(NODE** headP, unsigned char* changeMade)
{

    if ((*headP) == NULL && !(changeMade) || !(*changeMade)) return;
    
    char choice;
    unsigned char n;
    const unsigned char fileName[20] = "database.csv";

    do
    {
        printf("Do you wish to save file changes y/n: ");

        if (scanf(" %c", &choice) != 1);

    } while (choice != 'y' && choice != 'n');
    


    if (choice == 'y')
    {
        n = saveToFile(headP,fileName);    
        if (n == 1)
        {
            printf("Successfully saved to: %s\n", fileName);
        } 
        
        else if(n == 2)
        {
            printf("Successfully deleted: %s\n", fileName);
        }
        
        else 
        {
            printf("Failed to load: %s", fileName);   
        }
        
    } else if(choice == 'n') return;

    return;

}
