#ifndef GRID_NODE_H
#define GRID_NODE_H
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef int Grid_node_type;
#define ENTER 1
#define EXIT 2
#define WALL 0
#define ROAD 3 
#define OK 1
#define ERROR 0
#define BE_WALK 0
#define NO_WALK 1
#define CAN_NOT_PASS 0
#define CAN_PASS 1
#define NO_DIRECTION 0
#define HAS_DIRECTION 1
#define EAST 2
#define SOUTH 3
#define WEST 4
#define NORTH 5
typedef int Statue;
typedef struct{
    Grid_node_type data;
    int property;
    int be_walk;//表示该路径块被走过；
    int direction;
    int pos_i;
    int pos_j;
}Grid_node;
int rand_new()
{
    extern int sq[100];
    extern int k;
    int answer;
    while(1)
    {
        answer=rand()%(99-10+1)+10;
        int i=0;
        while(sq[i])
        {
            if(answer==sq[i])
            break;
            else
            ++i;
        }
        if(!sq[i])
        {
            sq[k]=answer;
            ++k;
            return answer;
        }
        else
        continue;
    }
}
Statue InitGridNode(Grid_node *node,int arg)
{
    node->property=arg;
    if(arg==ENTER||arg==EXIT||arg==WALL)
    {
        node->data=arg;
        if(arg==WALL)
        {
            node->be_walk=BE_WALK;
            node->direction=NO_DIRECTION;
        }
        else
        {
            node->be_walk=NO_WALK;
            node->direction=EAST;
        }
    }
    else
    {
        node->data=rand_new();
        node->be_walk=NO_WALK;
        node->direction=EAST;
    }
}
Statue Pass(Grid_node *node)
{
    if(node->be_walk==BE_WALK)
    return CAN_NOT_PASS;
    else
    {
        return CAN_PASS;
    }
}
Statue Footprint(Grid_node *node)
{
    node->be_walk=CAN_NOT_PASS;
}
Statue if_end(Grid_node *node)
{
    if(node->property==EXIT)
    return 1;
    else
    return 0;
}
void change_direc(Grid_node *node)
{
    ++node->direction;
}
#endif