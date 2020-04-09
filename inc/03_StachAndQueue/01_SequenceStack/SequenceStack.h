#ifndef _SEQUENCESTACK_H_
#define _SEQUENCESTACK_H_

#include "status.h"

#define STACK_INIT_SIZE 100 //顺序栈初始化存储空间大小
#define STACK_INCREMENT 10  //顺序栈存储空间的分配增量

// 顺序栈定义
// 在“迷宫”、“表达式”、“11二叉树二叉链表”、“孩子兄弟树”等算法中重定义该类型
typedef int elemType_sq_stack;

typedef struct sequence_stack_tag{
  elemType_sq_stack *base;  //栈底指针
  elemType_sq_stack *top;   //栈顶指针
  int stackSize;            //栈空间大小
}sq_stack_t, *p_sq_stack_t;





#endif // !_SEQUENCESTACK_H_
