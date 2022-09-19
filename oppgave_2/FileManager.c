#include "./include/FileManager.h" 
#include "./include/wordProcessor.h" 
#include <stdio.h>

//#define OK  1
//#define ERROR 0

enum flags{
    OK = 1,
    ERROR = 0
};

int decodeFile(unsigned char* msg, const unsigned char* fileToRead)
{

    // Array to store two chars each HEX included '\0'.
    unsigned char temp[3] = {0};
    
    // Simple file reading.
    FILE* file = NULL;

    // Open file in read mode. 
    file = fopen(fileToRead,"r");

    if (file == NULL) return ERROR;

    // Read two chars at a time. Braces omitted..
    while (fgets(temp,sizeof(temp),file) != NULL) convert(msg,temp); // Found in WordProcessor.h and WordProcessor.c

    //Clean up
    fclose(file);
    return OK;
}

int writeToFile(const unsigned char* msg,const unsigned char* fileToWrite)
{
    // Simple file writing.
    FILE* file = NULL;

    // Open file in write mode.
    file = fopen(fileToWrite, "w");
    
    if (file == NULL) return ERROR;
     
    // write to file 
    fprintf(file,"%s",msg);
    
    // close file
    fclose(file);      
    return OK;
}


