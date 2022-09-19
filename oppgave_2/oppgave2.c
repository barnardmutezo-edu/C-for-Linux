// Headers containing function prototypes.
#include "./include/FileManager.h" 
#include "./include/wordProcessor.h" 

#include<stdio.h>
#include <stdlib.h>


int main(void){

    // Container for the decoded message.
    unsigned char msg [250] = {0};
    
    // Hardcoded file names.
   const unsigned char encodedFile[] = "encoded.txt"; // the HEX file.
   const unsigned char decodedFile[] = "decoded.txt"; // the decoded file.

    //PART A OF THE TASK: ALL FUNCTIONS IN FileManager.h FileManager.c
    if (decodeFile(msg,encodedFile) != 1) 
    {
        printf("ERROR DECODING FILE!\n");
        exit(1);
    }
    
    if (writeToFile(msg,decodedFile) != 1) 
    {
        printf("ERROR WRITING TO FILE!\n");
        exit(1);
    }
       

    //PART B OF THE TASK: ALL FUNCTIONS IN WordHandler.h WordHandler.c
    printOccurrences(msg); 

    return 0;
}
