#include <stdio.h>

int main(int argc, char* argv[])
{
    int i=0;
    while(argv[1][i] !='\0')
    {
        if(argv[2][i] == '\0')
        {
            fprintf(stderr, "Error: Arguments are Different length");
            return 0;
        }
        i++;
    }
    if(argv[2][i] != '\0')
    {
        fprintf(stderr, "Error: Arguments are Different length");
        return 0;
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
                return 0;
            }
        }
    }
    
    int c;
    int y;
    while(1)
    {
        c = getchar();
        if(c == EOF)
            break;
        for(y=0; y < argLength; y++)
        {
            if(argv[1][y] == c)
                c = argv[2][y];
        }
        putchar(c);
    }
}
