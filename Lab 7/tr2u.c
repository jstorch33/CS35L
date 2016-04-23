#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  int i=0;
  while(argv[1][i] !='\0')
    {
      if(argv[2][i] == '\0')
	{
	  fprintf(stderr, "Error: Arguments are Different length");
	  return 1;
	}
      i++;
    }
  if(argv[2][i] != '\0')
    {
      fprintf(stderr, "Error: Arguments are Different length");
      return 1;
    }

  int argLength = i;
  int x;
  int z;
  for(x=0; x < argLength-1; x++)
    {
      for(z=x+1; z < argLength; z++)
	{
	  if(argv[1][x] == argv[1][z])
	    {
	      fprintf(stderr, "Error: Arguments Repeat Character");
	      return 1;
	    }
	}
    }

  int c;
  int y;
  int a;
  while(1)
    {
      a = read(0,&c,1);
      if(a == 0)
	break;
      if(a < 0)
	{
	  fprintf(stderr, "Error: Read failed");
	  return 1;
	}
      for(y=0; y < argLength; y++)
	{
	  if(argv[1][y] == c)
	    c = argv[2][y];
	}
      write(1,&c,1);
    }
}
