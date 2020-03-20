#ifndef _SINGLYLINKEDLIST_H_
#define _SINGLYLINKEDLIST_H_

#include "01_Exordium/status.h"

// 单链表结构定义
typedef int ElemType_int;

typedef struct linked_list_node_tag {
  ElemType_int data;
  struct linked_list_node_tag *next;
} linked_list_node, *plinked_list_node;

#ifdef __cplusplus
extern "C" {
#endif

// 初始化单链表（带头节点）
Status init_linked_list(plinked_list_node *L);

// 清空单链表（保留头节点）
Status clear_linked_list(plinked_list_node L);

// 销毁单链表（不保留头节点）
Status destroy_linked_list(plinked_list_node *L);

// 判断单链表是否为空
Status empty_linked_list(plinked_list_node L);

// 获取链表长度
int get_length_linked_list(plinked_list_node L);

// 获取单链表中位置为i的元素值
Status get_elem_linked_list(plinked_list_node L, int i, ElemType_int *e);

// 获取满足条件的元素的位置
int get_local_linked_list(plinked_list_node L, ElemType_int e, compare func);

// 获取元素cur_e的前驱节点
Status get_prior_linked_list(plinked_list_node L, ElemType_int cur_e,
                             ElemType_int *pre_e);

// 获取元素cur_e的后继节点
Status get_next_linked_list(plinked_list_node L, ElemType_int cur_e,
                             ElemType_int *next_e);

// 在单链表的第i个位置插入元素e
Status insert_linked_list(plinked_list_node L, int local, ElemType_int e);

// 删除第i个位置的元素
Status delete_linked_list(plinked_list_node L, int local, ElemType_int *e);

// 遍历访问单链表
Status traverse_linked_list(plinked_list_node L);

// 头插法创建单链表
Status create_linked_list_h(plinked_list_node *L,
                            std::vector<ElemType_int> list);

// 尾插法创建单链表
Status create_linked_list_t(plinked_list_node *L,
                            std::vector<ElemType_int> list);

#ifdef __cplusplus
}
#endif
#endif
