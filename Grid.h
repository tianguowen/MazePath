#ifndef GRID_H
#define GRID_H
#include"Grid_node.h"
#include<stdio.h>
typedef int Statue;
#define GRID_WIDE 10
#define GRID_HEIGTH 10
typedef struct{
    Grid_node **node;
}Grid;

Statue InitGrid(Grid *s)
{
    int index;
    s->node=(Grid_node**)malloc(sizeof(Grid_node*)*GRID_WIDE);
    for(index=0;index<GRID_WIDE;++index)
    {
        s->node[index]=(Grid_node*)malloc(sizeof(Grid_node)*GRID_HEIGTH);
    }
    //节点中内容初始化
    int i,j;
    srand((unsigned)time(NULL));
    for(i=0;i<GRID_WIDE;++i)
    {
        for(j=0;j<GRID_HEIGTH;++j)
        {
            if(i==0||i==9)
            {
                InitGridNode(&(s->node)[i][j],WALL);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
            else if(j==0||j==9)
            {
                InitGridNode(&(s->node)[i][j],WALL);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
            else if((i==1&&(j==3||j==7))||(i==2&&(j==3||j==7))||(i==3&&(j==5||j==6))||(i==4&&(j==2||j==3||j==4))||(i==5&&j==4)||(i==6&&(j==2||j==6))||(i==7&&(j==2||j==3||j==4||j==6||j==7))||(i==8&&j==1))
            {
                InitGridNode(&(s->node)[i][j],WALL);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
            else if(i==1&&j==1)
            {
                InitGridNode(&(s->node)[i][j],ENTER);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
            else if(i==8&&j==8)
            {
                InitGridNode(&(s->node)[i][j],EXIT);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
            else
            {
                InitGridNode(&(s->node[i][j]),ROAD);
                (s->node)[i][j].pos_i=i;
                (s->node)[i][j].pos_j=j;
            }
        }
    }
}
Statue PrintGrid(Grid *s)
{
    int i,j;
    for(i=0;i<GRID_WIDE;++i)
    {
        for(j=0;j<GRID_HEIGTH;++j)
        {
            if ((s->node)[i][j].data==1||(s->node)[i][j].data==2)
            {
                printf("O  ");
            }
            else if ((s->node[i][j]).data<10)
            {
                printf("** ");
            }
            else
            printf("%d ",(s->node)[i][j].data);
        }
        printf("\n");
    }
}
Grid_node* Next_pos(Grid *s,Grid_node e)//s参数关联地图，而e参数代表当前位置信息节点
{
    if(e.direction==EAST)
    return &(s->node)[e.pos_i][e.pos_j+1];
    else if (e.direction==SOUTH)
    {
        return &(s->node)[e.pos_i+1][e.pos_j];
    }
    else if(e.direction==WEST)
    {
        return &(s->node)[e.pos_i][e.pos_j-1];
    }
    else
    {
        return &(s->node)[e.pos_i-1][e.pos_j];
    }
}
Grid_node* Get_ENTER(Grid *s)
{
    return &(s->node)[1][1];
}
Statue MazePath(Grid *s)
{
    SqStack road_line;//堆栈用于存储路径；
    int step=1;//用于统计走了多少步；
    InitStack(&road_line);
    Grid_node e;//临时变量
    Grid_node* mouse=Get_ENTER(s);
    do{
        if(Pass(mouse))//检查当前块是否可以走
        {
            Footprint(mouse);//在此留下足迹保证该块不能被通过
            e=*mouse;
            Push(&road_line,e);//将当前块压入我们的路径条中去
            if(if_end(mouse))
            break;
            mouse=Next_pos(s,*mouse);
            ++step;
        }
        else//这是当前块无法通过的情况
        {
            if(!StackEmpty(&road_line))
            {
                Pop(&road_line,mouse);
                if(mouse->direction<=5)//表示当前位置四周尚未探查
                {
                    ++mouse->direction;//换下一个方向
                    Push(&road_line,*mouse);
                    mouse=Next_pos(s,*mouse);
                }
                while(mouse->direction>5&&!StackEmpty(&road_line))
                {
                    Footprint(mouse);
                    Pop(&road_line,mouse);
                }
            }
        }
    }
    while(!StackEmpty(&road_line));
    PrintStack(road_line);
    printf("\n");
    printf("%d",step);
}
#endif