#ifndef LOGIC_GUARD__H
#define LOGIC_GUARD__H

#include <stdio.h>

void SetupLogic();
void ShowGrid();
void CalculateEvolutions();
void CheckEachCell(int evo);
int CountNeighbours(int evo, int i, int j);
int GetISize();
int GetJSize();
int GetNumOfEvos();
int* GetGrid(int evo, int i);
void SetArrayElem(int elem, int i, int j);
int GetArrayElem(int evo, int i, int j);
int SetEvos(int evos);
void ResetArray();

#endif
