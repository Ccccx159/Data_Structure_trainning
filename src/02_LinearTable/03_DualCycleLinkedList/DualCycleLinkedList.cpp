#include "02_LinearTable/03_DualCycleLinkedList/DualCycleLinkedList.h"

#define check_list_head(L)                                                    \
  {                                                                           \
    if (!L) {                                                                 \
      std::cout << "dualCycleLinkedList L is NULL!...pls check" << std::endl; \
      return ERROR;                                                           \
    }                                                                         \
  }

// 初始化双向循环链表
Status init_list_dcl(p_dual_cycle_linked_list_node_t *L) {
  (*L) = (p_dual_cycle_linked_list_node_t)calloc(
      1, sizeof(dual_cycle_linked_list_node_t));
  if (!(*L)) {
    std::cout << "memory calloc failed!..." << std::endl;
    return OVERFLOW;
  }
  (*L)->next = (*L);
  (*L)->prior = (*L);
  return OK;
}

// 清空链表
Status clear_list_dcl(p_dual_cycle_linked_list_node_t L) {
  check_list_head(L);
  p_dual_cycle_linked_list_node_t p = L->next;
  p_dual_cycle_linked_list_node_t q = NULL;
  while (p != L) {
    q = p;
    p = p->next;
    free(q);
  }
  L->next = L;
  L->prior = L;

  return OK;
}

// 销毁双向循环链表
Status destroy_list_dcl(p_dual_cycle_linked_list_node_t *L) {
  check_list_head((*L));
  p_dual_cycle_linked_list_node_t p = (*L)->next;
  p_dual_cycle_linked_list_node_t q = NULL;
  while (p != (*L)) {
    q = p;
    p = p->next;
    free(q);
  }

  free((*L));
  (*L) = NULL;
  return OK;
}

// 判断链表是否为空
Status empty_list_dcl(p_dual_cycle_linked_list_node_t L) {
  check_list_head(L);

  return L->next == L && L->prior == L ? TRUE : FALSE;
}

// 获取链表长度
int get_length_list_dcl(p_dual_cycle_linked_list_node_t L) {
  check_list_head(L);

  int cnt = 0;
  p_dual_cycle_linked_list_node_t p = L->next;
  while (p != L) {
    cnt++;
    p = p->next;
  }

  return cnt;
}

// 获取第pos个节点内容，pos>0
Status get_elem_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                         ElemType_dcl *e) {
  check_list_head(L);

  int len = get_length_list_dcl(L);
  if (pos > len) {
    std::cout << "pos [" << pos << "] exceed the table's length[" << len << "]"
              << std::endl;
    return ERROR;
  }

  p_dual_cycle_linked_list_node_t p = L->next;
  for (int i = 1; i < pos; ++i) {
    p = p->next;
  }
  (*e) = p->data;
  return OK;
}

// 获取首次符合条件的元素
int locate_elem_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl e,
                         compare func) {
  check_list_head(L);

  p_dual_cycle_linked_list_node_t p = L->next;
  int cnt = 1;
  while (p != L && func(p->data, e)) {
    p = p->next;
    cnt++;
  }
  if (p == L) {
    std::cout << "No elem in the List satify the condition!..." << std::endl;
    return ERROR;
  }
  return cnt;
}

// 获取元素的前驱节点
Status get_prior_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl cur_e,
                          ElemType_dcl *prior_e) {
  check_list_head(L);

  p_dual_cycle_linked_list_node_t p = L->next;
  while (p != L && p->data != cur_e) {
    p = p->next;
  }
  if (p == L) {
    std::cout << "No elem[" << cur_e << "] in this list, pls check!..."
              << std::endl;
    return ERROR;
  }

  if (p->prior == L) {
    std::cout << "elem[" << cur_e << "] does NOT have Prior!..." << std::endl;
    return ERROR;
  }

  (*prior_e) = p->prior->data;
  return OK;
}

// 获取元素的后继节点
Status get_next_list_dcl(p_dual_cycle_linked_list_node_t L, ElemType_dcl cur_e,
                         ElemType_dcl *next_e) {
  check_list_head(L);

  p_dual_cycle_linked_list_node_t p = L->next;
  while (p != L && p->data != cur_e) {
    p = p->next;
  }

  if (p == L) {
    std::cout << "No elem[" << cur_e << "] in this list, pls check!..."
              << std::endl;
    return ERROR;
  }

  if (p->next == L) {
    std::cout << "elem[" << cur_e << "] does NOT have Next!..." << std::endl;
    return ERROR;
  }

  (*next_e) = p->next->data;
  return OK;
}

// 在位置pos处插入元素e，pos>0
Status insert_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                       ElemType_dcl e) {
  check_list_head(L);

  int len = get_length_list_dcl(L);
  if (pos > len + 1) {
    printf("pos[%d] exceed this list's length[%d]! pls check!...\n", pos, len);
    return ERROR;
  }

  p_dual_cycle_linked_list_node_t p = L->next;
  for (int i = 1; i < pos; i++) {
    p = p->next;
  }

  p_dual_cycle_linked_list_node_t new_node =
      (p_dual_cycle_linked_list_node_t)calloc(
          1, sizeof(dual_cycle_linked_list_node_t));
  if (!new_node) {
    std::cout << "memory calloc failed!..." << std::endl;
    return ERROR;
  }

  new_node->data = e;
  new_node->next = p;
  new_node->prior = p->prior;
  p->prior->next = new_node;
  p->prior = new_node;

  return OK;
}

// 删除pos处的元素，pos>0
Status delete_list_dcl(p_dual_cycle_linked_list_node_t L, int pos,
                       ElemType_dcl *e) {
  check_list_head(L);

  int len = get_length_list_dcl(L);
  if (pos > len) {
    printf("pos[%d] exceed this list's length[%d]! pls check!...\n", pos, len);
    return ERROR;
  }

  p_dual_cycle_linked_list_node_t p = L->next;
  for (int i = 1; i < pos; i++) {
    p = p->next;
  }
  p->prior->next = p->next;
  p->next->prior = p->prior;
  free(p);
  p = NULL;

  return OK;
}

// 遍历双向循环链表
Status traverse_list_dcl(p_dual_cycle_linked_list_node_t L) {
  check_list_head(L);

  p_dual_cycle_linked_list_node_t p = L->next;
  std::cout << "sequence list: ";
  while (p != L) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;

  p = L->prior;
  std::cout << "inverse sequence list: ";
  while (p != L) {
    std::cout << p->data << " ";
    p = p->prior;
  }
  std::cout << std::endl;

  return OK;
}