#include "03_StackAndQueue/02_LinkedListStack/LinkedListStack.h"

#define check_ptr(ptr)                                                         \
  {                                                                            \
    if (!ptr) {                                                                \
      std::cout << __FUNCTION__ << __LINE__ << "ptr is NULL!..." << std::endl; \
      return ERROR;                                                            \
    }                                                                          \
  }

// 初始化顺序栈
Status init_stack_linkedList(p_linkedList_stack_t stk_l) {
  stk_l->head =
      (linkedList_stack_node_t *)calloc(1, sizeof(linkedList_stack_node_t));
  check_ptr(stk_l->head);
  stk_l->stack_len = 0;

  return OK;
}

// 销毁顺序栈
Status destroy_stack_linkedList(p_linkedList_stack_t stk_l) {
  check_ptr(stk_l->head);
  p_linkedList_stack_node_t tmp = stk_l->head;
  p_linkedList_stack_node_t n_f = NULL;
  while (tmp) {
    n_f = tmp;
    tmp = tmp->next;
    free(n_f);
  }
  stk_l->stack_len = 0;

  return OK;
}

// 清空
Status clear_stack_linkedList(p_linkedList_stack_t stk_l) {
  check_ptr(stk_l->head);
  p_linkedList_stack_node_t tmp = stk_l->head->next;
  p_linkedList_stack_node_t n_f = NULL;
  while (tmp) {
    n_f = tmp;
    tmp = tmp->next;
    free(n_f);
  }
  stk_l->stack_len = 0;

  return OK;
}

// 判断是否为空
Status empty_stack_linkedList(linkedList_stack_t stk_l) {
  return stk_l.stack_len == 0 ? TRUE : FALSE;
}

// 获取栈长
int get_length_stack_linkedList(linkedList_stack_t stk_l) {
  return stk_l.stack_len;
}

// 用e获取栈顶元素
Status get_top_stack_linkedList(linkedList_stack_t stk_l,
                                elemType_linkedStack *e) {
  check_ptr(stk_l.head);
  (*e) = stk_l.head->next->data;
  return OK;
}

// 元素e进栈
Status push_stack_linkedList(p_linkedList_stack_t stk_l,
                             elemType_linkedStack e) {
  check_ptr(stk_l->head);
  p_linkedList_stack_node_t new_node =
      (p_linkedList_stack_node_t)calloc(1, sizeof(linkedList_stack_node_t));
  check_ptr(new_node);
  new_node->data = e;
  new_node->next = stk_l->head->next;
  stk_l->head->next = new_node;
  stk_l->stack_len++;
  return OK;
}

// 元素e出栈
Status pop_stack_linkedList(p_linkedList_stack_t stk_l,
                            elemType_linkedStack *e) {
  check_ptr(stk_l->head);
  if (stk_l->stack_len > 0) {
    (*e) = stk_l->head->next->data;
    p_linkedList_stack_node_t tmp = NULL;
    tmp = stk_l->head->next;
    stk_l->head->next = tmp->next;
    free(tmp);
  } else {
    LOG_ERROR("stack_linked is empty!!!\n");
    return ERROR;
  }

  return OK;
}

// 遍历
Status traverse_stack_linkedList(linkedList_stack_t stk_l) {
  check_ptr(stk_l.head);
  p_linkedList_stack_node_t tmp = stk_l.head->next;
  while (tmp)
  {
    std::cout << tmp->data << " ";
    tmp = tmp->next;
  }
  std::cout << std::endl;
  return OK;
}