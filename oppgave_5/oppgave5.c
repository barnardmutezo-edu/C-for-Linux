#include "./include/Data.h" // Include the struct to be passed between threads.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define ACTIVE 1;

void* writeToFile(void* arg); // Worker thread.
void processStringInput(char* string);

int main(void) // Main thread
{
   DATA* data = malloc(sizeof(DATA)); // Allocate room for the struct.

   pthread_t thread; // Worker thread handle

   unsigned char isActive = ACTIVE;
   unsigned char i;
   char word[11];
 

   // Add default values to the struct
   data->shouldStart = 0; // Make sure we start in the main thread.
   data->buffSize = 0;
   data->file = NULL;

   // Init mutex and synchronization mechanisms.
   pthread_mutex_init(&data->mutex,NULL);
   pthread_cond_init(&data->cond,NULL);

   while (isActive)
   {
         processStringInput(word);

         if (strcmp(word,"quit") == 0) break;

         //Let worker know the amount of chars to expect, before sending.    
         data->buffSize = strlen(word); 

         //Start thread only after we have validated the string.
         pthread_create(&thread,NULL,writeToFile,(void*)data); 

         // Send one char at a time through loop cycles, the only logical way i figured..
         for (i = 0; i < data->buffSize; i++)
         {
               // Allowing only the main thread to access the shared memo.
               pthread_mutex_lock(&data->mutex);
         
               // Incase worker is reading, wait for signal
               while (data->shouldStart) pthread_cond_wait(&data->cond,&data->mutex);

               // Write to the shared memo      
               data->buff[i] = word[i];
               data->currentChar = i;         

               printf("Main sending: %c\n", data->buff[data->currentChar]);
         
               // Suspend main/wake worker
               data->shouldStart = 1;
               
               // Signal to worker that a char has been send
               pthread_cond_signal(&data->cond);
      
               pthread_mutex_unlock(&data->mutex);
         
         }
      
      // Wait for worker to finnish processing before restarting loop.
      pthread_join(thread,NULL);

      fclose(data->file);
      data->file = NULL;
      printf("\n");
   }
   
   // Clean up
   pthread_cond_destroy(&data->cond);
   pthread_mutex_destroy(&data->mutex);
  
   
   //So we do not get error if first word is "quit"
   if (data->file != NULL){
      fclose(data->file);
      data->file = NULL;
   }

   free(data);
   printf("Done\n");
   data = NULL;
   return 0;
}

void* writeToFile(void* arg)
{

   DATA* data = (DATA*) arg; // Cast the recieved parameter.

   const unsigned char fileName[] = "output.txt";
   unsigned char i;
   
   data->file = fopen(fileName,"a");

   // Get one char at a time
   if (data->file != NULL)
   {  
      // Reading one char at a time while the buffer is filling   
      for (i = 0; i < data->buffSize; i++)
      {
  
         // Allowing only worker to access the shared memo.
         pthread_mutex_lock(&data->mutex);
         
         // Incase main is still writing, wait for signal.
         while (!data->shouldStart) pthread_cond_wait(&data->cond,&data->mutex);
         
         // Read from shared memo.
         printf("Worker recieving: %c\n", data->buff[data->currentChar]);

         // Write to the file.
         fprintf(data->file, "%c", data->buff[data->currentChar]);


         // Last char appended, add a new line
         if (i == (data->buffSize-1)) fprintf(data->file, "%c", '\n');
        
         // Suspend worker/wake main
         data->shouldStart = 0;
         
         pthread_cond_signal(&data->cond);        
         pthread_mutex_unlock(&data->mutex);
     
      }

   }
}

void processStringInput(char* string)
{
      unsigned char length;

      printf("Enter string: ");
      if (scanf("%s", string));

      length  = strlen(string);

      while (length > 10)
      {
            printf("String is too long try again: ");
            if (scanf("%s", string));

            length = strlen(string);
            string[length] = '\0';

      }

      string[length] = '\0';
}