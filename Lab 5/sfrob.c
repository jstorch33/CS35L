//
//  main.c
//  sfrob
//
//  Created by Jack Storch on 10/30/15.
//  Copyright © 2015 Jack Storch. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>


int frobcmp(const char *a, const char *b)
{
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
  int c;
  int count = 0;
  int arrSize = 51;
  char* arr = (char*) malloc (51); //50 characters and the '/0'
  if (arr == NULL)
    {
      fprintf(stderr,"Memory Error: No memory could be allocated");
      exit(1);
    }
  
  int isEmpty = 1;
  while(1)
    {
      c = getchar();
      if(c == EOF) //check for end of file
	break;
      isEmpty=0;
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
  
  if(isEmpty == 1)
    return 0;

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
  //  for(a=0;a<pos;a++)
  // free(arr2[a]);
  free(arr2);
}

