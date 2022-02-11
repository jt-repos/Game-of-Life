#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "logic.h"
#include "variables.h"
#include "file_operations.h"

//Input numOfEvos to then calculate consecutive evolutions. Exit in case of error.
void SetupLogic()
{
	while(true)
	{
		int evos;
		printf("\nEnter number of evolutions: ");
		scanf("%d", &evos);
		numOfEvos = evos;
		if(numOfEvos) { break; }
	}
	char fileName[MAXSIZE] = "in.txt";
	int error = SetupArray(fileName);
	if(error == 0)
	{
		CalculateEvolutions();
	}
	else
	{
		exit(0);
	}
}

//Goes through each cell to calculate next iteration state
void CalculateEvolutions()
{
	int evo = 1;
	for(; evo <= numOfEvos; evo++)
	{
		CheckEachCell(evo);
		//ShowGrid(evo);
	}
	SaveData("out.txt", grid[evo-1]);
}

//Sets next cell state depending on conditions given
void CheckEachCell(int evo)
{
	for (int i = 1; i < iSize + 1; i++)
	{
		for (int j = 1; j < jSize + 1; j++)
		{
			int neighbours = CountNeighbours(evo-1, i, j);
			if(neighbours <= 1 || neighbours > 3)
			{
				grid[evo][i][j] = 0;
			}
			else if(neighbours == 3)
			{
				grid[evo][i][j] = 1;
			}
			else
			{
				grid[evo][i][j] = grid[evo-1][i][j];
			}
		}
	}
}

//Counts alive cells adjacent to the one passed
int CountNeighbours(int evo, int i, int j)
{
	int neighbours =
				grid[evo][i-1][j-1] + grid[evo][i-1][j] + grid[evo][i-1][j+1] +
				grid[evo][i][j-1] 					+ grid[evo][i][j+1] +
				grid[evo][i+1][j-1] + grid[evo][i+1][j] + grid[evo][i+1][j+1];
	return neighbours;
}

//returns a row of grid
int* GetGrid(int evo, int i)
{
	return grid[evo][i];
}

//getters used in testing and other modules
int GetISize()
{
	return iSize;
}

int GetJSize()
{
	return jSize;
}

int GetNumOfEvos()
{
	return numOfEvos;
}

int GetArrayElem(int evo, int i, int j)
{
	return grid[evo][i][j];
}

//setters used in testing and other modules
void SetArrayElem(int elem, int i, int j)
{
	grid[0][i][j] = elem;
	if(i > iSize)
	{
		iSize = i;
	}
	if(j > jSize)
	{
		jSize = j;
	}
}

int SetEvos(int evos)
{
	if(evos > 0 && evos <= MAXSIZE - 2)
	{
		numOfEvos = evos;
		return evos;
	}
	printf("Invalid number of evolutions (should be 1-64).\n");
	return 0;
}

void ShowGrid(int evo)
{
	printf("\n\t");
	for (int k = 0; k < jSize; k++)
	{
		printf("%i ", k);
	}
	printf("\n\n");
	for (int i = 0; i < iSize; i++)
	{
		printf("%i", i);
		printf("\t");
		for (int j = 0; j < jSize; j++)
		{
			printf("%d ", grid[evo][i+1][j+1]);
		}
		printf("\n");
	}
	printf("\n");
}

//used in testing
void ResetArray()
{
	memset(grid, 0, sizeof(grid));
}
