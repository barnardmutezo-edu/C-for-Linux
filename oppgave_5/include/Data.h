#include <pthread.h>
#include <stdio.h>

#ifndef __Data_H__
#define __Data_H__
typedef struct DATA
{
   pthread_mutex_t mutex; // Synchronization lock.
   pthread_cond_t cond; // Condition variable.
   FILE* file; // File handler.

   char buff[11]; // The buffer for the string.
   unsigned int currentChar; // Keeps track of which char to read/write. 
   unsigned int buffSize; // Amount of words inn buff.

  
   unsigned int shouldStart;  // Flag for signaling when a thread should start.
} DATA;
#endif //__Data_H
