#include "./include/ListManager.h" // Import requred prototypes and structs.
#include "./include/FileManager.h" // File management prototypes.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include  <ctype.h> 
#include <time.h>
//#define OK 1
//#define ERROR 0

enum flags{
    PROCEED = 1,
    RETREAT = 0
};

// EXAM REQUIRED FUNCTIONS: Details found in ListManager.h

void addToList(NODE** headP,unsigned char* changeMade)
{

    NODE* duplicate = NULL;
    char choice;

    unsigned char productName[50];
    int quantity;
    char priceString[5];
    float price;

    printf("Enter product name: ");

    if (scanf("%s",productName) != 1) return;
    // We do not want to end up multiplying by zero...
    do
    {
        printf("Enter quantity, number > 0: ");
        
        if(scanf("%d", &quantity) != 1) return;

    } while (quantity <= 0);


    do
    {
        printf("Enter price, number > 0.0: ");

        if(scanf("%s", priceString) != 1) return; // Allow user to enter a string.

        price = atof(priceString); // Convert the string to a float.
      
    } while (price <= 0.0);
    

    duplicate = allreadyInList(headP,productName); // Check if element already in list.

    if (duplicate != NULL)
    {
        do
        {
            printf("\n%s is already in the list, woud you like to update the attributes? y/n: ", productName);
            if (scanf(" %c",&choice) != 1);

        } while (choice != 'y' && choice != 'n');
        
        if (choice == 'y')
        {
            updateNode(duplicate, &quantity,&price);
            printf("Successfully updated %s's attrinutes", productName);          
        } 
        else if (choice == 'n')
        {
            duplicate = NULL;
        }
    }
    
    if (duplicate == NULL) enqueue(headP,productName,&quantity,&price,0);
    (*changeMade)++;
   
}

NODE* allreadyInList(NODE** headP,const unsigned char* name)
{
    NODE* current = (*headP);

    while (current != NULL)
    {
        if (strcmp(current->data->productName,name) == 0) return current;
        
        current = current->next;
    }
    
    return NULL;
}

void updateNode(NODE* nodeP, const int* quanty, const float* price)
{
    nodeP->data->quantity = (*quanty);
    nodeP->data->pricePerUnit = (*price);
}


int enqueue(NODE** headP, const unsigned char* name, const int* quantity, const float* price, const unsigned char fromFile)
{

    NODE* newNode = createNode(); 
    newNode->data = createData(name,quantity,price);

    if ((*headP) == NULL) // List is empty.
    {
        (*headP) = newNode; // Point the head directly to the new node
        (*headP)->next = NULL; 
        (*headP)->prev = NULL;
    }
    else
    {
        // List >= 1
        NODE* current = (*headP); //Store the first node.
        while (current->next != NULL) // Find the node before the last node.
        {
            current = current->next; 
        }
        
        // Allign the nodes.
        current->next = newNode; 
        newNode->prev = current;
        newNode->next = NULL;
    }

    if (fromFile) return 0;

    printf("\n");
    printf("Successfully added: %s",newNode->data->productName);
    printf("\n");

    return 1;
    

}


void removeLastNode(NODE** headP,unsigned char* changeMade)
{ 
   NODE* toDelete = NULL;
  
   if ((*headP) == NULL) // If head is NULL the list is empty, so just return back to caller.
   {
        printf("List is empty could not delete.\n");
        return;
   }


   if ((*headP)->next == NULL) //Removing the last element, set head to NULL.
   {
        toDelete = (*headP);
        (*headP) = NULL;
   } 

   else
   {
        toDelete = (*headP); // List is > 1, find the last element.

        while (toDelete->next != NULL) 
        {
            toDelete = toDelete->next;
        }

        toDelete->prev->next = NULL; // Remove from list.
   }


   printf("Sucessfully deleted: %s\n", toDelete->data->productName);

   if (freeNode(toDelete))((*changeMade)++); // Remove from heap.

}


void getNameToDelete(NODE** headP,unsigned char* changeMade)
{
    if ((*headP) == NULL) // Return to caller if the list is empty.
    {
        printf("List is empty could not delete.\n");
        return;
    }
    unsigned char productToDelete[50]; // Store the product name.
    unsigned char found = 0; // Check wether a name is found or not.

    printf("Enter the product name you wish to delete: ");
    
    if (scanf("%s",productToDelete)); // Get the name to delete provided by user.
    
    deleteName(headP, productToDelete,&found); // Send the name to the delete function.


    printf("\n");
    if (found){
        printf("Successfully deleted %s from the list\n",productToDelete);
        ((*changeMade)++); 

    } else {
        printf("Sorry could not find %s from the list\n", productToDelete);
    }
}

void deleteName(NODE** headP, unsigned char* nameP, unsigned char* found)
{
    NODE* current = (*headP);
    DATA* data = NULL;
    NODE* toDelete = NULL;
    
    unsigned char shouldFree = RETREAT; // Varible to keep track when a node is to be deleted

    while (current != NULL)
    {
        data = current->data;
        
        if (strcmp(data->productName,nameP)==0) // Check if the productName matches the given name.
        {
            toDelete = current;
            shouldFree = PROCEED;    
            (*found)++;    
        } 

        current = current->next;

        if (shouldFree) 
        {
            deleteNode(headP,toDelete);
            shouldFree = RETREAT;
        }
        
    }

}

float getSum(NODE** headP)
{

    NODE* current = (*headP);
    DATA* data = NULL;
    float totalPrice = 0.0;

    while (current != NULL)
    {
        data = current->data;
        updatePrice(data,&totalPrice);    
        current = current->next;
    }

    return totalPrice;

}


void printReceipt(NODE** headP)
{

    if ((*headP) == NULL) //nothing to print, return to caller
    { 
           printf("List is empty\n");
           return;
    }
 
    NODE* current = *headP;
    DATA* data = NULL;    
    
    printf("Here is your reseipt: \n\n");

    while (current != NULL)
    {
        data = current->data;
        printf("Product name: %s\n", data->productName);
        printf("Quantity: %d\n", data->quantity);
        printf("Price: %.2f\n", data->pricePerUnit); // Use a .2 precission to make the format cleaner.

        current = current->next;
        printf("\n");
    }

    printf("Total price: %.2f\n", getSum(headP));
    printf("Total elemnts: %d\n", countElements(headP));
    
    //Add time stamp
    insertStamp();
    printf("\n");
}


 
// HELPER FUNCTIONS: Details found in ListManager.h

// Creation functions
NODE* createNode()
{
    
    NODE *newNode = malloc(sizeof(NODE)); // Allocate room for pointer.
    memset(newNode,0,sizeof(NODE)); // Initialize it to zero.
   
    if (newNode == NULL)
    {
        printf("COULD NOT CREATE NODE!!\n");
        exit(1);
    }
   
    return newNode;
}


DATA* createData(const unsigned char* name, const int* quantity, const float* price)
{
    DATA* data = NULL;
    data = malloc(sizeof(DATA));
    memset(data,0,sizeof(DATA));

    if (data == NULL)
    {
        printf("COULD NOT CREATE DATA!!\n");
        exit(1);
    }

    strcpy(data->productName, name);
    data->quantity = *quantity;
    data->pricePerUnit = *price;

    return data;
}

// Calculation functions

void calculateSum(NODE** headP)
{
    if ((*headP) == NULL)
    {
        printf("List is empty could not calculate\n");        
        return;
    }

    printf("The total price is: %.2f\n", getSum(headP)); // Again precission to reduce cluster.
}

void updatePrice(const DATA* dataP, float* priceP)
{
    *priceP += (dataP->pricePerUnit)*(dataP->quantity);
}

int countElements(NODE** headP)
{
    int count = 0;
    NODE* current = (*headP);
    DATA* data = NULL;

    while (current != NULL)
    {
        data = current->data;
        count+= (data->quantity);
        current = current->next;
    }

    return count;
}

// Deletion functions

void deleteNode(NODE** headP,NODE* nodeP)
{
    NODE* nodeToDeleteP = nodeP;

    //THE HEAD...
    if (nodeToDeleteP == (*headP))
    {
        // LIST > 1 UPDATE HEAD
        if (nodeToDeleteP->next != NULL)
        {
            nodeToDeleteP->next->prev = NULL;
            (*headP)= nodeToDeleteP->next;
        } 
        
        // LIST = 1 
        else
        { 
            nodeToDeleteP = (*headP);
            (*headP) = NULL;
            
        }

    } else
    {
        //TAIL
        if (nodeToDeleteP->next == NULL)
        {
            nodeToDeleteP->prev->next = NULL;
        }
        
        //MIDDLE
        else
        {
            nodeToDeleteP->next->prev = nodeToDeleteP->prev;
            nodeToDeleteP->prev->next = nodeToDeleteP->next;
        }
        
    }          
    freeNode(nodeToDeleteP); 
}

void deleteAll(NODE** headP, unsigned char* changeMade)
{
    NODE* current = NULL;
    NODE* temp = NULL;

    if ((*headP) == NULL)
    {
       printf("List is empty\n");
       return;     
    }

    current = (*headP);

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        deleteNode(headP, temp);
    }
    
    (*changeMade)++;
    printf("Successfully deleted all elements.\n");    

}

int freeNode(NODE* nodeP) // Frees both the node and attributes.
{
    DATA* dataP = nodeP->data;

    free(dataP);
    free(nodeP);

    //Set pointers to NULL.
    dataP = NULL;
    nodeP = NULL;

    if (dataP==NULL && nodeP == NULL) return PROCEED;
    

}

void freeHeap(NODE** headP) // Call this function at every exit.
{
    if ((*headP) == NULL) return;
    
    NODE* current =(*headP);
    NODE* toDelete = NULL; 

    while(current != NULL)
    {
        toDelete = current;    
        current = current->next;
        deleteNode(headP,toDelete);
    }
}


void insertStamp(void)
{
    time_t currTime;
    char* timeString;
    currTime = time(NULL);
    timeString = ctime(&currTime); // Get the time provided by the system.
    
    if (timeString == NULL)
    {
        printf("Failed to pass time\n");
    } else
    {
        printf("Purchased: %s", timeString);
    }

}

