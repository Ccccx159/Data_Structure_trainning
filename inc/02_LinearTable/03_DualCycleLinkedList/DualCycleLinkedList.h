#ifndef _DUALCYCLELINKEDLIST_H_
#define _DUALCYCLELINKEDLIST_H_

#include "status.h"

typedef int ElemType_dcl;
typedef struct dual_cycle_linked_list_node_tag {
  ElemType_dcl data;
  struct dual_cycle_linked_list_node_tag *prior;
  struct dual_cycle_linked_list_node_tag *next;
} dual_cycle_linked_list_node_t, *p_dual_cycle_linked_list_node_t;

#ifdef __cplusplus
extern "C" {
#endif

// 初始化双向循环链表
Status init_list_dcl(p_dual_cycle_linked_list_node_t *L);

// 清空链表
Status clear_list_dcl(p_dual_cycle_linked_list_node_t L);

// 销毁双向循环链表
Status destroy_list_dcl(p_dual_cycle_linked_list_node_t *L);

// 判断链表是否为空
Status empty_list_dcl(p_dual_cycle_linked_list_node_t L);

// 获取链表长度
int get_length_list_dcl(p_dual_cycle_linked_list_node_t L);

// 获取第pos个节点内容，pos>0
Status get_elem_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                         ElemType_dcl *e);

// 获取首次符合条件的元素
Status locate_elem_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl e,
                            compare func);

// 获取元素的前驱节点
Status get_prior_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl cur_e,
                          ElemType_dcl *prior_e);

// 获取元素的后继节点
Status get_next_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl cur_e,
                         ElemType_dcl *next_e);

// 在位置pos处插入元素e，pos>0
Status insert_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                       ElemType_dcl e);

// 删除pos处的元素，pos>0
Status delete_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                       ElemType_dcl *e);

// 遍历双向循环链表
Status traverse_list_dcl(p_dual_cycle_linked_list_node_t L);

#ifdef __cplusplus
}
#endif

#endif