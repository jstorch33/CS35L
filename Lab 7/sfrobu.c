//
//  main.c
//  sfrob
//
//  Created by Jack Storch on 10/30/15.
//  Copyright © 2015 Jack Storch. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int numOfComps = 0;

int frobcmp(const char *a, const char *b)
{
    numOfComps+=1;
    
    const char *first = *(const char **)a;
    const char *second = *(const char **)b;
    int i =0;
    for(i =0;;i++)
    {
        int f = (int)*first;
        int s = (int)*second;
        f^=42;
        s^=42;
        first++;
        second++;
        if(s == f)
            continue;
        else
            return f - s;
    }
    return 0;
}


int main()
{
    char c;       //character to be found with read
    char c2;
    int count = 0;
    int currentSize;
    int arrSize = 100;
    char* arr;
    
    //Give information about the file
    struct stat filename;
    fstat(0, &filename);
    int sizeOfFile = filename.st_size;
    
    
    int readStatus;
    if(S_ISREG(filename.st_mode))
    {
        arr = (char*) malloc(sizeof(char) * sizeOfFile);
        currentSize = sizeOfFile;
        if(arr == NULL)
        {
            fprintf(stderr, "Error: dynamic memory not allocated");
            exit(1);
        }
        
        int i;
        for(i=0; i<sizeOfFile; i++ )
        {
            readStatus = read(0,&c, 1);
	    arr[count] = c;
            count++;
            
            if(count == currentSize)
            {
                arr = (char*) realloc(arr,  arrSize + currentSize);
                if(arr == NULL)
                {
                    fprintf(stderr, "Error: dynamic memory not allocated");
                    exit(1);
                }
                currentSize += arrSize;
            }
            
            //Recheck length of file
            fstat(0, &filename);
            sizeOfFile = filename.st_size;
        }
    }
    else   //written input instead of a file
    {
        arr = (char*) malloc(arrSize);
        
        while(1)
        {
            readStatus = read(0,&c,1);
            if(readStatus == 0)
                break;
            
            arr[count] = c;
            count++;
            
            if(count == arrSize)    //add more to the arr if too big
            {
                arr = (char*) realloc (arr, count*2);
                if (arr == NULL)
                {
                    fprintf(stderr,"Memory Error: No memory could be allocated");
                    exit(1);
                }
                arrSize = (arrSize * 2);
            }
        }
    }
    
    
    
    
    int loc;
    int numSpaces =0;
    
    if(arr[count-1] != ' ')
    {
        arr[count] = ' ';
        count++;
    }
    
    for(loc = 0; loc < count; loc++)
    {
        if(arr[loc] == ' ')
            numSpaces++;
    }
    
    
    char** arr2 =(char**) malloc(sizeof(char*) * numSpaces);
    if (arr == NULL)
    {
        fprintf(stderr,"Memory Error: No memory could be allocated");
        exit(1);
    }
    
    char * arrCopy =arr;
    int w;
    int arr2Pos =0;
    for(w =0;w<numSpaces;w++)
    {
        if(w == 0 && *arrCopy == ' ' )
        {
            arr2[arr2Pos] = arrCopy;
            arr2Pos++;
            arrCopy++;
            w++;
        }
        
        arr2[arr2Pos] = arrCopy;
        arr2Pos++;
        while(*arrCopy != ' ')
            arrCopy++;
        
        arrCopy++;
    }
    
    qsort(arr2, arr2Pos, sizeof(char*), frobcmp);
    
    int b;
    for(b=0;b<numSpaces;b++)
    {
        char * position = arr2[b];
        char * print = arr2[b];
        int lengthOfEntry =1;
        int g;
        while(*position != ' ')
        {
            position++;
            lengthOfEntry++;
        }
        for(g=0;g <lengthOfEntry;g++)
        {
            printf("%c", *print);
            print++;
        }
    }
    
    free (arr);
    free (arr2);
    
    fprintf(stderr, "Comparisons: %d\n", numOfComps);
    return 0;
}

