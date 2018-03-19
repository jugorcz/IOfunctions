/* Created by Justyna Gorczyca on 18.03.18. */


#ifndef UNTITLED_AUXILIARYFUNCTIONS_H
#define UNTITLED_AUXILIARYFUNCTIONS_H

#include <time.h>
#include <sys/times.h>

void displayInfo();
int setOperation(char* argv[]);
char* setFileName1(int argc, char* argv[]);
int setRecordsNumber(int argc, char* argv[]);
int setRecordLength(int argc, char* argv[]);
int setUsedLib(int argc, char* argv[]);
char* setFileName2(int argc, char* argv[]);
void displayArguments(int argc, char* argv[],int operation, char* fileName1, char* fileName2, int recordsNumber, int recordLength, int usedLib);

void generate(char* fileName1,int recordsNumber, int recordLength);

void sortSys(char* fileName1,int recordsNumber, size_t recordLength);
void copySys(char* fileName1, int recordsNumber, size_t recordLength, char* fileName2);
void sortLib(char* fileName1,int recordsNumber, size_t recordLength);
void copyLib(char* fileName1, int recordsNumber, size_t recordLength, char* fileName2);

void saveResults(FILE* out, clock_t clk,struct tms startTime,struct tms endTime, char* operationName);

#endif /* UNTITLED_AUXILIARYFUNCTIONS_H */
