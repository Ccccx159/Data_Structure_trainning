#ifndef _LINKEDQUEQUE_H_
#define _LINKEDQUEQUE_H_

#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int elemType_que_lq;

typedef struct linkedque_node_tag {
  elemType_que_lq data;
  struct linkedque_node_tag *next;
} linkedque_node_t, *p_linkedque_node_t;

typedef struct linkedque_tag {
  int que_len;
  linkedque_node_t *front;
  linkedque_node_t *rear;
} linkedque_t, *p_linkedque_t;

// 初始化链队列
Status linkedQue_init(linkedque_t *que_l);

// 销毁队列
Status linkedQue_destroy(linkedque_t *que_l);

// 判断队列是否为空
Status linkedQue_get_empty(linkedque_t que_l);

// 获取队列长度
int linkedQue_get_length(linkedque_t que_l);

// 获取队列头部元素
Status linkedQue_get_head(linkedque_t que_l, elemType_que_lq *e);

// 队尾插入元素
Status linkedQue_push_tail(linkedque_t *que_l, elemType_que_lq e);

// 队头弹出元素
Status linkedQue_pop_head(linkedque_t *que_l, elemType_que_lq *e);

// 遍历队列元素
Status linkedQue_traverse(linkedque_t que_l, visit vfunc);

#ifdef __cplusplus
}
#endif

#endif