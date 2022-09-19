#include "./include/oppgave4.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _MYHTTP { 
    int iHttpCode; 
    int iContentLength;
    bool bIsSuccess; 
    char szServer[16]; 
    char szContentType[16]; 
    int lastModified;
} MYHTTP;


MYHTTP* ProcessHttpHeader(char* pszHttp); // Moved down this part, cannot use struct before initializing it.

MYHTTP* ProcessHttpHeaderFixed(char* pszHttp);


void printHeader(MYHTTP* header); //Function that prints the HTTP attributes.

int main(void)
{
    unsigned char HTTP_REPLY[] ="Server: Apache\nContent-Type: text/html\nContent-Length: 80\nLast-Modified: 2021";
   
    MYHTTP* http = ProcessHttpHeader(HTTP_REPLY);
    MYHTTP* httpFixed = ProcessHttpHeaderFixed(HTTP_REPLY);

    printf("\nFAULTY HTTP:\n\n");
    printHeader(http);
    
    printf("\nFIXED HTTP:\n\n");
    printHeader(httpFixed);

    free(http);
    free(httpFixed);

    return 0;
}

void printHeader(MYHTTP* header)
{
    printf("Server: %s\n", header->szServer);
    printf("Content-Type: %s\n", header->szContentType);
    printf("Content-Length: %d\n", header->iContentLength);
    printf("Last-Modified: %d\n", header->lastModified);
    printf("Http-Code: %d\n", header->iHttpCode);
    printf("Success-Response: %s\n", header->bIsSuccess ? "true" : "false");
}


MYHTTP* ProcessHttpHeader(char *pszHttp) {
    
    char* pszPtr;

    MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP)); 
    
    if (!pHttp) return NULL;
    memset(pHttp, 0, sizeof(MYHTTP));

    pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x ")); 
    
    if (pHttp->iHttpCode = 200) {
        pHttp->bIsSuccess = true;
    }

    pszPtr = strstr(pszHttp, "Server");

    if (pszPtr) {
    pszPtr += 6; 
    while (!isalpha(pszPtr[0]))pszPtr++; 

    strchr(pszPtr, '\n')[0] = 0; 
    strcpy(pHttp->szServer, pszPtr); 
    pszPtr[strlen(pHttp->szServer)] = '\n';

    }

    pszPtr = strstr(pszHttp, "Content-Type"); 
    if (pszPtr) {

    pszPtr += 12; 
    while (!isalpha(pszPtr[0]))pszPtr++; 
   
    strchr(pszPtr, '\n')[0] = 0; 
    strncpy(pHttp->szContentType, pszPtr, 15); 
    pszPtr[strlen(pHttp->szContentType)] = '\n';
    
    }
    
    pszPtr = strstr(pszHttp, "Content-Length");
    
    if (pszPtr) {
    pszPtr += 14; 
    while (!isdigit(pszPtr[0])) pszPtr++; 
    
    pHttp->iContentLength = atoi(pszHttp);
    
    }
   return pHttp;
}


MYHTTP* ProcessHttpHeaderFixed(char *pszHttp) {
    
    char* pszPtr;
    pszPtr = NULL;
    
    MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP)); 
    
    if (!pHttp) return NULL;

    memset(pHttp, 0, sizeof(MYHTTP)); 
    
    pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x ")); 

        if (pHttp->iHttpCode = 200) { 
            pHttp->bIsSuccess = true;
        }
    
    pszPtr = strstr(pszHttp, "Server");
    
    if (pszPtr) {
        pszPtr += 6; 
        while (!isalpha(pszPtr[0])) pszPtr++;

        strchr(pszPtr, '\n')[0] = 0; 
        strcpy(pHttp->szServer, pszPtr); 
        
        pszPtr[strlen(pHttp->szServer)] = '\n'; 
    }

    pszPtr = strstr(pszHttp, "Content-Type"); 

    if (pszPtr) { 
       
        pszPtr += 12; 
        while (!isalpha(pszPtr[0])) pszPtr++; 

        strchr(pszPtr, '\n')[0] = 0; 
        strncpy(pHttp->szContentType, pszPtr, 15); 
        pszPtr[strlen(pHttp->szContentType)] = '\n'; 
    }
    pszPtr = strstr(pszHttp, "Content-Length"); 

    if (pszPtr) {
       
        pszPtr += 14; 
        while (!isdigit(pszPtr[0])) pszPtr++; 
        
        pHttp->iContentLength = atoi(pszPtr); 
    } 
    
    pszPtr = strstr(pszHttp,"Last-Modified");

    if (pszPtr)
    {
    
        while (!isdigit(pszPtr[0])) 
        pszPtr++; 
        pHttp->lastModified = atoi(pszPtr);

    }

    return pHttp;
}