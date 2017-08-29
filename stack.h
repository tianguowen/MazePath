#ifndef _STACK_H
#define _STACK_H
#define STACK_INIT_SIZE 100 /*存储空间初始分配量*/
#define STACKINCREMENT 10/*存储空间增加量*/
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#include "Grid_node.h"
#include <stdio.h>
typedef int Statue; 
typedef Grid_node SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
Statue InitStack(SqStack *s);//构造一个空的栈列表
Statue DestoryStack(SqStack *s);//销毁一个栈列表
Statue ClearStack(SqStack *s);//将栈置空
int StackEmpty(SqStack *s);//判断栈是否为空
int StackLength(SqStack *s);//返回栈的长度
Statue Gettop(SqStack *s,SElemType *e);//获取栈yu元素的值，通过e返回
Statue Push(SqStack *s,SElemType e);/*压入元素*/
Statue Pop(SqStack *s,SElemType *e);/*头顶元素出栈，并通过e返回*/
Statue StackTraverse(SqStack *s,Statue(*visit)());
Statue PrintStack(SqStack s);
#endif

Statue InitStack(SqStack *s)
{
    s->base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!s->base)
       exit(OVERFLOW);
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
    return OK;
}
Statue DestoryStack(SqStack *s)
{
    free(s->base);
    if(s->base)
    return ERROR;
    s->base=s->top=NULL;
    s->stacksize=0;
}
Statue ClearStack(SqStack *s)
{
    while(s->base!=s->top)
    {
        memset(s->top,0,sizeof(SElemType));
        --s->top;
    }
    memset(s->base,0,sizeof(SElemType));
}
Statue StackEmpty(SqStack *s)
{
    if(s->top==s->base)
    return TRUE;
    return FALSE;
}
int StackLength(SqStack *s)
{
    return (s->top-s->base)+1;
}
Statue GetTop(SqStack *s,SElemType *e)
{
    *e=*(--s->top);
    ++s->top;
    if(e)
    return OK;
    else
    {
        return ERROR;
    }
}
Statue Push(SqStack *s,SElemType e)
{
    if(StackLength(s)>=s->stacksize)
    {
        s->base=(SElemType *)realloc(s->base,(STACKINCREMENT+STACK_INIT_SIZE)*sizeof(SElemType));
    }
    if(!s->base)
    exit(OVERFLOW);
    else
    s->stacksize=STACK_INIT_SIZE+STACKINCREMENT;
    *(s->top)=e;
    ++s->top;
    return OK;
}
Statue Pop(SqStack *s,SElemType *e)
{
    if(!StackEmpty(s))
    {
        GetTop(s,e);
        --s->top;
        memset(s->top,0,sizeof(SElemType));
    }
    else
    return ERROR;
}
Statue PrintStack(SqStack s)
{
    while(s.base!=s.top)
    {
        printf("%d  ",(s.base)->data);
        ++s.base;
    }
    printf("\n");
}

