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
  int stack_len;
}sq_stack_t, *p_sq_stack_t;

#ifdef __cplusplus
extern "C" {
#endif

// 初始化顺序栈
Status init_stack_sq(p_sq_stack_t stk);

// 销毁顺序栈
Status destroy_stack_sq(p_sq_stack_t stk);

// 清空
Status clear_stack_sq(p_sq_stack_t stk);

// 判断是否为空
Status empty_stack_sq(sq_stack_t stk);

// 获取栈长
int get_length_stack_sq(sq_stack_t stk);

// 用e获取栈顶元素
Status get_top_stack_sq(sq_stack_t stk, elemType_sq_stack *e);

// 元素e进栈
Status push_stack_sq(p_sq_stack_t stk, elemType_sq_stack e);

// 元素e出栈
Status pop_stack_sq(p_sq_stack_t stk, elemType_sq_stack *e);

// 遍历
Status traverse_stack_sq(sq_stack_t stk);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !_SEQUENCESTACK_H_
