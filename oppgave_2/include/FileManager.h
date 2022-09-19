#ifndef __FileManager__H__
#define __FileManager__H__

extern int decodeFile(unsigned char* msg,const unsigned char* fileToRead); // Decodes the given file.
extern int writeToFile(const unsigned char* msg,const unsigned char* fileToWrite ); // Writes the decoded message to a new file.


#endif //__FileManager__H__


