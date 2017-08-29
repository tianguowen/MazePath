#include "Grid_node.h"
#include "stack.h"
#include "Grid.h"
int sq[100];
int k=0;
int main()
{
    Grid grid;
    InitGrid(&grid);
    printf("迷宫如下图所示:\n");
    PrintGrid(&grid);
    printf("\n");
    MazePath(&grid);
}