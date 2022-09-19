#include "./Data.h" // Import the DATA struct containing attributes

#ifndef __Node_H__
#define __Node_H__

//The NODE structure
typedef struct NODE
{
    struct NODE* next; // Pointer to the next element.
    struct NODE* prev; // Pointer to the previous element.
    struct DATA* data; // Pointer to the nodes attributes.
  
} NODE;

#endif //__Node_H
