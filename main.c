/* Created by Justyna Gorczyca on 18.03.18. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/times.h>

#include "auxiliaryFunctions.h"

int operation;
char* fileName1;
char* fileName2;
int recordsNumber;
int recordLength;
int usedLib;

int properArguments(int argc, char* argv[])
{
    if(argc < 2)
    {
        displayInfo();
        return 0;
    }
    operation = setOperation(argv);
    fileName1 = setFileName1(argc,argv);
    recordsNumber = setRecordsNumber(argc,argv);
    recordLength = setRecordLength(argc,argv);
    usedLib = setUsedLib(argc,argv);
    fileName2 = setFileName2(argc,argv);
    displayArguments(argc,argv,operation,fileName1,fileName2,recordsNumber,recordLength,usedLib);

    return 1;
}

void callFunction()
{
    if(usedLib == 0) /* systemowe */
    {
        switch(operation)
        {
            case 1: generate(fileName1,recordsNumber,recordLength);
                break;
            case 2: sortSys(fileName1,recordsNumber, (size_t )recordLength);
                break;
            case 3: copySys(fileName1, recordsNumber, (size_t )recordLength, fileName2);
                break;
            default:
                break;
        }
    }

    if(usedLib == 1) /* biblioteczne */
    {
        switch(operation)
        {
            case 1: generate(fileName1,recordsNumber,recordLength);
                break;
            case 2: sortLib(fileName1,recordsNumber, (size_t )recordLength);
                break;
            case 3: copyLib(fileName1, recordsNumber, (size_t )recordLength, fileName2);
                break;
            default:
                break;
        }
    }
}


int main(int argc, char* argv[])
{
    /*if(properArguments(argc, argv) == 0)
        return 0;

    callFunction();*/

    FILE* file  = fopen("wyniki.txt","w");
    if(file == NULL)
        return 0;


    fileName1 = "file1.txt";
    fileName2 = "file2.txt";
    char* fileName3 = "file3.txt";

    clock_t clk;
    struct tms startTime, endTime;

    /* ------------------------------------------------------długość rekordu: 4*/
    fprintf(file,"\n------------------------------RECORD SIZE: 4\n");
    recordsNumber = 1000;
    recordLength = 4;

    generate(fileName1,recordsNumber,recordLength);

    times(&startTime);
    clk = clock();
    copySys(fileName1, recordsNumber, (size_t )recordLength, fileName2);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy sys");

    times(&startTime);
    clk = clock();
    copyLib(fileName2, recordsNumber, (size_t )recordLength, fileName3);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy lib");

    times(&startTime);
    clk = clock();
    sortSys(fileName1,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort sys");

    times(&startTime);
    clk = clock();
    sortLib(fileName2,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort lib");



    /* ------------------------------------------------------długość rekordu: 512*/
    fprintf(file,"\n------------------------------RECORD SIZE: 512\n");
    recordsNumber = 1000;
    recordLength = 512;

    generate(fileName1,recordsNumber,recordLength);

    times(&startTime);
    clk = clock();
    copySys(fileName1, recordsNumber, (size_t )recordLength, fileName2);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy sys");

    times(&startTime);
    clk = clock();
    copyLib(fileName2, recordsNumber, (size_t )recordLength, fileName3);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy lib");

    times(&startTime);
    clk = clock();
    sortSys(fileName1,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort sys");

    times(&startTime);
    clk = clock();
    sortLib(fileName2,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort lib");



    /* ------------------------------------------------------długość rekordu: 4096*/
    fprintf(file,"\n------------------------------RECORD SIZE: 4096\n");
    recordsNumber = 500;
    recordLength = 4096;

    generate(fileName1,recordsNumber,recordLength);

    times(&startTime);
    clk = clock();
    copySys(fileName1, recordsNumber, (size_t )recordLength, fileName2);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy sys");

    times(&startTime);
    clk = clock();
    copyLib(fileName2, recordsNumber, (size_t )recordLength, fileName3);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy lib");

    times(&startTime);
    clk = clock();
    sortSys(fileName1,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort sys");

    times(&startTime);
    clk = clock();
    sortLib(fileName2,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort lib");



    /* ------------------------------------------------------długość rekordu: 8192*/
    fprintf(file,"\n------------------------------RECORD SIZE: 8192\n");
    recordsNumber = 100;
    recordLength = 8192;

    generate(fileName1,recordsNumber,recordLength);

    times(&startTime);
    clk = clock();
    copySys(fileName1, recordsNumber, (size_t )recordLength, fileName2);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy sys");

    times(&startTime);
    clk = clock();
    copyLib(fileName2, recordsNumber, (size_t )recordLength, fileName3);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"copy lib");

    times(&startTime);
    clk = clock();
    sortSys(fileName1,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort sys");

    times(&startTime);
    clk = clock();
    sortLib(fileName2,recordsNumber, (size_t )recordLength);
    clk = clock() - clk;
    times(&endTime);
    saveResults(file,clk,startTime,endTime,"sort lib");


    return 0;
}
