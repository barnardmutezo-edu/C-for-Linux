#include "./Node.h"
#ifndef __ListManager_H__
#define __ListManager_H__


// EXAM REQUIRED FUNCTIONS
extern void addToList(NODE**headP, unsigned char* changeMade);
extern int enqueue(NODE** headP, const unsigned char* name, const int* quantity, const float* price, const unsigned char fromFile); // Legge til et element i slutten av listen 

extern void removeLastNode(NODE** headP,unsigned char* changeMade); // Slette siste element i listen (en «angreknapp»)

/*These two work as one function*/
extern void getNameToDelete(NODE** headP,unsigned char* changeMade); // Sletter alle elementer i listen som har et gitt VARENAVN-
extern void deleteName(NODE** headP, unsigned char* nameP, unsigned char* found); // (sendes som parameter til funksjonen)

extern float getSum(NODE** headP); // Summerer sammen total pris for varene i listen (husk å ta hensyn til antall)

extern void printReceipt(NODE** headP); //Printer ut en kvittering (i konsoll vinduet)


// HELPER FUNCTIONS

// Creation functions
extern NODE* createNode(); // Creates and returns a new NODE pointer.
extern void buildNode(const unsigned char* name, const unsigned int* price, const float* pricePerUnit );
extern DATA* createData(const unsigned char* name, const int* quantity, const float* price); // Creates a new DATA pointer witch is then put in the new NODE pointer, recieved as a parameter.

extern NODE* allreadyInList(NODE** headP, const unsigned char* name);
extern void updateNode(NODE* nodeP, const int* price, const float* quantity);

// Calculation functions
extern void calculateSum(NODE** headP); // Calculates the price for all the elements in the Queue.
extern void updatePrice(const DATA* dataP, float* priceP); // A helper function that updates the price in calculateSum.
extern int countElements(NODE** headP); // EKSTRA: counts the total amount of elements in the Queue.


// Deletion functions
extern void deleteNode(NODE** headP, NODE* nodeP); // Deletes a NODE from the Queue, recieved as a parameter.
extern int freeNode(NODE* nodeP); // Frees the NODE and DATA pointer received as parm and sets them to NULL.
extern void freeHeap(NODE** headP); // Called upon each exit to make sure the heap is cleared.
extern void deleteAll(NODE** headP, unsigned char* changeMade);

extern void insertStamp(void); // Adds a purchused time to the bottom of the receipt.

#endif //_ListManager_H_
