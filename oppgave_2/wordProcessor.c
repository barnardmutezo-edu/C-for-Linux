#include "./include/wordProcessor.h" // import the function prototypes
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void printOccurrences(const unsigned char* msg){
    
    //No need for integers..
    unsigned char ch,count;

    // loop that goes through the whole alphabet
    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        count = 0;  
        // loop to check the number of times a letter appears in the string 
        find(msg,&ch,&count);
        printf("The letter %c occured: %d times\n",ch,count);
    }

}

// Increments the count in printOccurences if words match
void find(const unsigned char* msg, const unsigned char* letter, unsigned char* count)
{
    // Some pointer arithmetics for you, no need for braces..
    while (*msg++) if (toupper(*msg) == (*letter)) (*count)++;
}


void convert(unsigned char* msg, const unsigned char* temp) {
    // stores the letter and the "\0" terminator
    unsigned char letter[2];

    // convert the HEX to a single char AKA a letter
    letter[0] = (char) strtol(temp, 0, 16);
    
    // add a null terminator
    letter[1] = '\0';
    
    // add the letter to the back of the array
    strcat(msg,letter);
}