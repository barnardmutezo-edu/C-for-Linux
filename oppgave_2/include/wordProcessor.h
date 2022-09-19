#ifndef __WordProcessor__H__
#define __WordProcessor__H__

// Using const to let caller know that im not going to modify the parameter varibales.
extern void printOccurrences(const unsigned char* msg); // Prints how many times each letter appears.
extern void find(const unsigned char * msg, const unsigned char* letter, unsigned char* count); // Finds how many time a letter occours in a message.
extern void convert(unsigned char* msg, const unsigned char* temp); // Converts the HEX to a char.

#endif //__WordProcessor__H__
