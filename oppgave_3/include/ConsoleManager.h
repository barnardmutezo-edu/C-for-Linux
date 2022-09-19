#include "./FileManager.h"

#ifndef __ConsoleManager_H__
#define __ConsoleManager_H__

extern void printMenu(unsigned char* choice);
extern void greetUser(NODE** headP);
extern void setTime(unsigned char* t);
extern void askToSave(NODE** headP, unsigned char* changesMade);

#endif //_ConsoleManager_H_
 