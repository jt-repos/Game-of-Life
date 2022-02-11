#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_operations.h"
#include "logic.h"

//reads the values from text files into grid[0]
int SetupArray(char* fileName)//, int (*array)[MAXSIZE])
{
    int row = 0, col = 0; //column, row and character counters to keep track of which field will be appended
  	int prevCol = 0;
    FILE *filePointer = fopen(fileName, "r"); //file pointer as specified by the name passed.
    char c; //the character read from the file
    if(filePointer == NULL)
    {
        printf("\nERROR. Could not open the file.\n");
        return 1;
    }
    while(!feof(filePointer))
  	{
        c = fgetc(filePointer);
		if(c == '\n')
		{
            int isGrid = (prevCol == col || prevCol == 0) && col != 0;
			if(!isGrid)
			{
				printf("\nInvalid contents of the file.\n");
				fclose(filePointer);
				return 1;
			}
			prevCol = col;
			row++;
			col = 0;
		}
        else if(c != EOF)
        {
            int value = c == 48 ? 0 : 1;
            if(col + 1 < MAXSIZE && row + 1 < MAXSIZE)
            {
                SetArrayElem(value, row + 1, col + 1);
            }
            else
            {
                printf("\nInvalid size of the input grid (max 64).\n");
				fclose(filePointer);
				return 1;
            }
            col++;
        }
  	}
    fclose(filePointer);
    return 0;
}

//saves the last state of grid into a text file
int SaveData(char* fileName, int (*array)[MAXSIZE])
{
    int iSize = GetISize();
    int jSize = GetJSize();
    FILE *filePointer = fopen(fileName, "w"); //file pointer as specified by the name passed.
    if(filePointer == NULL)
    {
        printf("ERROR. Could not open the file provided.\n");
        return 1;
    }
    for(int i = 1; i < iSize + 1; i++)
    {
		for(int j = 1; j < jSize + 1; j++)
		{
			char c[MAXSIZE];
        	snprintf(c, sizeof(c), "%d", array[i][j]); //on linux
			fwrite(c, 1, strlen(c), filePointer);
		}
		fwrite("\n", 1, strlen("\n"), filePointer);
    }
    fclose(filePointer);
  	printf("Successfully saved to %s!", fileName);
    return 0;
}
