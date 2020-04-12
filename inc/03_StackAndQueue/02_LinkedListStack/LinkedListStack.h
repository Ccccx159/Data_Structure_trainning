#ifndef _LINKEDLISTSTACK_H_
#define _LINKEDLISTSTACK_H_

#include "status.h"

typedef int elemType_linkedStack;  // 定义链栈存储数据类型

typedef struct linkedList_stack_node_tag{
  elemType_linkedStack data;
  linkedList_stack_node_tag *next;
}linkedList_stack_node_t, *p_linkedList_stack_node_t;

typedef struct linkedList_stack_tag{
  p_linkedList_stack_node_t head;
  int stack_len;
}linkedList_stack_t, *p_linkedList_stack_t;

#ifdef __cplusplus
extern "C" {
#endif

// 初始化顺序栈
Status init_stack_linkedList(p_linkedList_stack_t stk_l);

// 销毁顺序栈
Status destroy_stack_linkedList(p_linkedList_stack_t stk_l);

// 清空
Status clear_stack_linkedList(p_linkedList_stack_t stk_l);

// 判断是否为空
Status empty_stack_linkedList(linkedList_stack_t stk_l);

// 获取栈长
int get_length_stack_linkedList(linkedList_stack_t stk_l);

// 用e获取栈顶元素
Status get_top_stack_linkedList(linkedList_stack_t stk_l, elemType_linkedStack *e);

// 元素e进栈
Status push_stack_linkedList(p_linkedList_stack_t stk_l, elemType_linkedStack e);

// 元素e出栈
Status pop_stack_linkedList(p_linkedList_stack_t stk_l, elemType_linkedStack *e);

// 遍历
Status traverse_stack_linkedList(linkedList_stack_t stk_l);

#ifdef __cplusplus
}
#endif

#endif