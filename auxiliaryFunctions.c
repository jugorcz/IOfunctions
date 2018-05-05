/* Created by Justyna Gorczyca on 18.03.18. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "auxiliaryFunctions.h"

#include <time.h>
#include <sys/times.h>


int operation;
char* fileName1;
char* fileName2;
int recordsNumber;
int recordLength;
int usedLib;

/*---------------------------------------------------------------------------------*/
void displayInfo()
{
    printf("\nWrong arguments amount, should be at least two: \n"
                   "[1] file name \n"
                   "[2] operation name: \n"
                   "      - generate \n"
                   "      - sort \n"
                   "      - copy \n"
                   "and optional: \n"
                   "[3] file name to generate or sort data \n"
                   "[4] number of records \n"
                   "[5] length of record \n"
                   "[6] used library \n"
                   "      - sys \n"
                   "      - lib \n"
                   "[7] second file name to copy data from first file \n"
                   "if above arguments won't be added, operation will be run with default parameters. \n");
}

int setOperation(char* argv[])
{
    if(strcmp(argv[1],"generate") == 0) return  1;
    else if(strcmp(argv[1],"sort") == 0) return  2;
    else if(strcmp(argv[1],"copy") == 0) return  3;
    else
        printf("\nWrong operation name, should be generate, sort or copy.");
    return 1;
}

char* setFileName1(int argc, char* argv[])
{
    if(argc > 2)
        return argv[2];
    else
        return "file1.txt";
}

int setRecordsNumber(int argc, char* argv[])
{
    if(argc > 3)
    {
        int tmp = atoi(argv[3]);
        if(tmp == 0)
            printf("\nWrong number of records. Will be set default number.");
        else
            return tmp;
    }
    return  100;
}

int setRecordLength(int argc, char* argv[])
{
    if(argc > 4)
    {
        int tmp = atoi(argv[4]);
        if(tmp == 0)
            printf("\nWrong length of record. Will be set default number.");
        else
            return tmp;
    }
    return 512;
}

int setUsedLib(int argc, char* argv[])
{
    if(argc > 5)
    {
        if(strcmp(argv[5],"sys") == 0) return 0;
        else if(strcmp(argv[5],"lib") == 0) return 1;
        else
            printf("\nWrong name of used library, will be set default library.");
    }
    return  0;
}

char* setFileName2(int argc, char* argv[])
{
    if(argc > 6)
        return argv[6];
    else
        return "file2.txt";
}

void displayArguments(int argc, char* argv[],int operation, char* fileName1, char* fileName2, int recordsNumber, int recordLength, int usedLib)
{
    printf("\n\nPodane argumenty:");
    int i;
    for(i = 0; i < argc; i++)
    {
        printf("\n%d:%s",i,argv[i]);
    }

    printf("\n\nUstawione argumenty:"
                   "\noperacja: ");
    if(operation == 1) printf("generate");
    if(operation == 2) printf("sort");
    if(operation == 3) printf("copy");
    printf("\nnazwa pliku: %s",fileName1);
    printf("\nliczba rekordów: %d",recordsNumber);
    printf("\nwielkość rekordu: %d",recordLength);
    printf("\nużyte funkcje: %s", usedLib == 0 ? "systemowe" : "biblioteczne");
    printf("\nnazwa pliku: %s\n",fileName2);
}

/*---------------------------------------------------------------------------------*/

void generate(char* fileName1,int recordsNumber, int recordLength)
{
    /*printf("\nGenerate data.\n");*/
    FILE * data = fopen(fileName1, "w");
    if(data == NULL)
        return;
    FILE * random = fopen("/dev/urandom", "r");
    int i;
    for(i = 0; i < recordsNumber * recordLength; i++)
    {
        putc(getc(random), data);
    }
    fclose(data);
    fclose(random);
}

void sortSys(char* fileName1, int recordsNumber, size_t recordLength)
{
    /*printf("\nSort data using operating system functions\n"); */
    int data = open(fileName1, O_RDWR);
    if(data < 0)
        return;
    char* buffer1 = (char*)malloc(recordLength);
    char* buffer2 = (char*)malloc(recordLength);
    int changed = 1;
    int count;
    for(count = 0; count < recordsNumber && changed; count++)
    {
        /* printf("\nrecord: %d",count); */
        changed = 0;
        int record;
        for(record = 0; record < recordsNumber-1; record++)
        {
            lseek(data, record * recordLength, SEEK_SET);
            read(data, buffer1, recordLength);

            lseek(data, (record + 1) * recordLength, SEEK_SET);
            read(data, buffer2, recordLength);
            if(buffer1[0] > buffer2[0])
            {
                changed = 1;
                lseek(data, record * recordLength, SEEK_SET);
                write(data, buffer2, recordLength);

                lseek(data, (record + 1) * recordLength, SEEK_SET);
                write(data, buffer1, recordLength);
            }
        }
    }
    close(data);
    free(buffer1);
    free(buffer2);
}

void copySys(char* fileName1, int recordsNumber, size_t recordLength, char* fileName2)
{
    /*printf("\nCopy data using operating system functions");*/
    int in = open(fileName1, O_RDONLY);
    if(in < 0)
        return;

    int out = open(fileName2,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    if(out < 0)
        return;
    char* buffer = (char*)malloc(recordLength);

    int i;
    for(i = 0; i < recordsNumber; i++)
    {
        read(in, buffer, recordLength);
        write(out, buffer, recordLength);
    }
    close(in);
    close(out);
    free(buffer);
}

void sortLib(char* fileName1,int recordsNumber, size_t recordLength)
{
    /*printf("\nSort data using library functions");*/
    FILE * data = fopen(fileName1, "r+");

    if(data == NULL)
        return;

    char* buffer1 = (char*)malloc(recordLength);
    char* buffer2 = (char*)malloc(recordLength);

    int change = 1;
    int i;
    for(i = 0; i < recordsNumber && change; i++)
    {

        /* printf("\nrecord: %d",i); */
        change = 0;
        int record;
        for(record = 0; record < recordsNumber-1; record++)
        {
            fseek(data, record * recordLength, SEEK_SET);
            fread(buffer1, recordLength, 1, data);

            fseek(data, (record + 1) * recordLength, SEEK_SET);
            fread(buffer2, recordLength, 1, data);

            if(buffer1[0] > buffer2[0])
            {
                change = 1;
                fseek(data, record * recordLength, SEEK_SET);
                fwrite(buffer2, recordLength, 1, data);

                fseek(data, (record + 1) * recordLength, SEEK_SET);
                fwrite(buffer1, recordLength, 1, data);
            }
        }
    }
    fclose(data);
    free(buffer1);
    free(buffer2);
}


void copyLib(char* fileName1, int recordsNumber, size_t recordLength, char* fileName2)
{
    /*printf("\nCopy data using library functions");*/
    FILE* in = fopen(fileName1, "r");
    if(in == NULL)
        return;

    FILE* out = fopen(fileName2,"w");
    if(out == NULL)
        return;

    char* buffer = (char*)malloc(recordLength);

    int i;
    for(i = 0; i < recordsNumber; i++)
    {
        fread(buffer, recordLength, 1, in);
        fwrite(buffer,recordLength,1,out);
    }
    fclose(in);
    fclose(out);
    free(buffer);
}


void saveResults(FILE* out, clock_t clk,struct tms startTime,struct tms endTime, char* operationName)
{
    fprintf(out,"%s\nreal\t%f us\nuser\t%f us\nsys\t%f us\n...................\n",
            operationName,
            ((double)clk*1000000)/(CLOCKS_PER_SEC),
            ((double)(endTime.tms_utime - startTime.tms_utime)*1000000)/CLOCKS_PER_SEC,
            ((double)(endTime.tms_stime - startTime.tms_stime)*1000000)/CLOCKS_PER_SEC);
}
