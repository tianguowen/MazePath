#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include "stack.h"
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
        printf("%d",(s.base)->data);
        ++s.base;
    }
    printf("\n");
}
