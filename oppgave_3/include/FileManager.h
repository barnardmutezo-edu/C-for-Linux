#include "./Node.h"
#ifndef __FileManager_H__
#define __FileManager_H__

// A nodes attributes contained in a struct to keep code clean and scalable
extern int saveToFile(NODE** headP, const unsigned char* fileName);
extern int loadFromFile(NODE** headP,const unsigned char* fileName);
extern void parseToList(NODE** headP, unsigned char* string);
#endif //__Data_H
