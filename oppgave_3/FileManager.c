#include "./include/FileManager.h"
#include "./include/ListManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define OK 1
#define ERROR 0
#define FILE_DELETED 2

int saveToFile(NODE** headP, const unsigned char* fileName)
{
    
    if ((*headP) == NULL) 
    {
        remove(fileName);
        return FILE_DELETED;
    }
    

    FILE* file;
    NODE* current = (*headP);
    DATA* data = NULL;

    file = fopen(fileName,"w");

    if (file == NULL) return ERROR;

    while (current != NULL)
    {        
        data = current->data;    
        
        fprintf(file, "%s,%d,%.2f",
        data->productName,
        data->quantity,
        data->pricePerUnit);

        current = current->next;
        
        fprintf(file,"%c", '\n');
    }


    fclose(file);

    return OK;

}


int loadFromFile(NODE** headP,const unsigned char* fileName)
{
    FILE* file;
    file = fopen(fileName,"r");
    unsigned char buff[100];
    
    if (file == NULL) return ERROR;
    if (access(fileName,F_OK != 0))
    {
        printf("Not present");
    }
    

    while (fgets(buff,100,file)) parseToList(headP,buff);
    

    fclose(file);
    return OK;
}

void parseToList(NODE** headP, unsigned char* string)
{
    unsigned char * productName;
    int quantity;
    float pricePerUnit;

    productName = strtok(string, ","); 
   
    string+= (1 + (strlen(productName)));

    quantity = atoi(strtok(string, ","));

    string+= (1 + strlen(string));

    pricePerUnit = atof(strtok(string, ","));
    enqueue(headP,productName,&quantity,&pricePerUnit,1);
    

}
