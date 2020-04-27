#ifndef _CIRCULARQUEUE_H_
#define _CIRCULARQUEUE_H_

#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXSIZE_QUE 100
#define INCREMENT_QUE 10

/*******************************************************************************
 * 此处约定：初始化创建空队列时，令front = rear = 0，每当插入新的队尾元素时，“尾指
 * 针rear加1”；每当删除队头元素时，“头指针front加1”。头指针始终指向队列头元素，尾
 * 指针始终指向队尾元素的下一个位置
 * ****************************************************************************/
typedef int elemType_que;
typedef struct ds_circular_queue_tag {
  elemType_que *base;     //初始化动态分配线性存储空间的基址
  int que_size;           //队列空间容量
  int front;              //头指针。若队列不空，指向队头元素
  int rear;               //尾指针，若队列不空，指向队尾元素的下一个位置
}ds_circular_que_t, *p_ds_circular_que_t;

// 初始化队列
Status que_cir_init(ds_circular_que_t *que);

// 销毁队列
Status que_cir_destroy(ds_circular_que_t *que);

// 清空队列
Status que_cir_clear(ds_circular_que_t *que);

// 判断循环队列是否为空
Status que_cir_get_empty(ds_circular_que_t que);

// 获取队列长度
int que_cir_get_length(ds_circular_que_t que);

// 获取队头元素
Status que_cir_get_head(ds_circular_que_t que, elemType_que *e);

// 弹出队头元素
Status que_cir_pop_head(ds_circular_que_t *que, elemType_que *e);

// 队尾压入新元素
Status que_cir_push_tail(ds_circular_que_t *que, elemType_que e);

// 遍历访问队列元素
Status que_cir_traverse(ds_circular_que_t que, visit vfunc);

#ifdef __cplusplus
}
#endif

#endif