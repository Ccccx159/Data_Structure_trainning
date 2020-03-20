#include "02_LinearTable/02_SinglyLinkedList/SinglyLinkedList.h"

#define check_param(L)                                               \
  {                                                                  \
    if (!L) {                                                        \
      std::cout << "linkedList L is NULL!...pls check" << std::endl; \
      return ERROR;                                                  \
    }                                                                \
  }

// 初始化单链表（带头节点）
Status init_linked_list(plinked_list_node *L) {
  *L = (plinked_list_node)calloc(1, sizeof(linked_list_node));
  if (*L) {
    return OK;
  } else {
    std::cout << "memory calloc failed!..." << std::endl;
    return OVERFLOW;
  }
}

// 清空单链表（保留头节点）
Status clear_linked_list(plinked_list_node L) {
  check_param(L);

  plinked_list_node p = L->next;
  plinked_list_node q = NULL;
  while (p) {
    q = p;
    p = p->next;
    free(q);
  }

  return OK;
}

// 销毁单链表（不保留头节点）
Status destroy_linked_list(plinked_list_node *L) {
  check_param(*L);

  plinked_list_node p = *L;
  plinked_list_node q = NULL;

  while (p) {
    q = p;
    p = p->next;
    free(q);
    q = NULL;
  }

  return OK;
}

// 判断单链表是否为空
Status empty_linked_list(plinked_list_node L) {
  return NULL == L->next ? TRUE : FALSE;
}

// 获取链表长度
int get_length_linked_list(plinked_list_node L) {
  check_param(L);

  plinked_list_node p = L->next;
  int len = 0;

  while (p) {
    ++len;
    p = p->next;
  }

  return len;
}

// 获取单链表中位置为i的元素值
Status get_elem_linked_list(plinked_list_node L, int i, ElemType_int *e) {
  check_param(L);

  int len = get_length_linked_list(L);
  if (i > len) {
    printf("param i[%d] is larged than L's length[%d], pls check!...", i, len);
    return ERROR;
  }
  plinked_list_node p = L->next;
  int cnt = 0;
  while (p && cnt < i - 1) {
    ++cnt;
    p = p->next;
  }
  *e = p->data;
  return OK;
}

// 获取满足条件的元素的位置
int get_local_linked_list(plinked_list_node L, ElemType_int e, compare func) {
  check_param(L);

  plinked_list_node p = L->next;
  int pos = 0;
  while (p) {
    ++pos;
    if (TRUE == func(p->data, e)) {
      return pos;
    } else {
      p = p->next;
    }
  }
  if (!p) {
    std::cout << "no elem satisfying condition!..." << std::endl;
  }
  return -1;
}

// 获取元素cur_e的前驱节点
Status get_prior_linked_list(plinked_list_node L, ElemType_int cur_e,
                             ElemType_int *pre_e) {
  check_param(L);

  plinked_list_node p = L->next;
  while (p->next) {
    if (p->next->data == cur_e) {
      *pre_e = p->data;
      return OK;
    } else {
      p = p->next;
    }
  }
  if (!p->next) {
    printf("no cur_e[%d] in the LinkedList L, pls check!...\n", cur_e);
  }
  return ERROR;
}

// 获取元素cur_e的后继节点
Status get_next_linked_list(plinked_list_node L, ElemType_int cur_e,
                            ElemType_int *next_e) {
  check_param(L);

  plinked_list_node p = L->next;
  while (p) {
    if (p->data == cur_e) {
      if (p->next) {
        *next_e = p->next->data;
        return OK;
      } else {
        printf("cur_e[%d] has no next_link!..\n", cur_e);
        return ERROR;
      }
    } else {
      p = p->next;
    }
  }

  printf("LinkedList has no cur_e[%d] elem!...\n", cur_e);
  return ERROR;
}

// 在单链表的第i个位置插入元素e
Status insert_linked_list(plinked_list_node L, int pos, ElemType_int e) {
  check_param(L);

  int len = get_length_linked_list(L);
  if (pos > len + 1) {
    printf("pos[%d] exceed the table's length[%d]...\n", pos, len);
    return ERROR;
  }

  plinked_list_node p = L;
  int cnt = 0;
  while (p->next && cnt < pos - 1) {
    p = p->next;
    cnt++;
  }

  plinked_list_node new_node =
      (plinked_list_node)calloc(1, sizeof(linked_list_node));
  if (!new_node) {
    std::cout << "memory calloc failed!..." << std::endl;
    return OVERFLOW;
  }
  new_node->data = e;
  new_node->next = p->next;
  p->next = new_node;
  return OK;
}

// 删除第i个位置的元素
Status delete_linked_list(plinked_list_node L, int pos, ElemType_int *e) {
  check_param(L);

  int len = get_length_linked_list(L);
  if (pos > len) {
    printf("pos[%d] exceed the table's length[%d]...\n", pos, len);
    return ERROR;
  }

  plinked_list_node p = L;
  int cnt = 0;
  while (p->next && cnt < pos - 1) {
    p = p->next;
    cnt++;
  }

  plinked_list_node q = p->next;
  p->next = q->next;
  *e = q->data;
  free(q);
  return OK;
}

// 遍历访问单链表
Status traverse_linked_list(plinked_list_node L) {
  check_param(L);

  plinked_list_node p = L->next;
  while (p) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
  return OK;
}

// 头插法创建单链表
Status create_linked_list_h(plinked_list_node *L,
                            std::vector<ElemType_int> list) {
  *L = (plinked_list_node)calloc(1, sizeof(linked_list_node));
  if (!(*L)) {
    std::cout << "memory calloc failed!..." << std::endl;
    return ERROR;
  }
  for (int i = 0; i < list.size(); i++) {
    plinked_list_node p =
        (plinked_list_node)calloc(1, sizeof(linked_list_node));
    if (!p) {
      std::cout << "memory calloc failed!..." << std::endl;
      return ERROR;
    }
    p->data = list[i];
    p->next = (*L)->next;
    (*L)->next = p;
  }

  return OK;
}

// 尾插法创建单链表
Status create_linked_list_t(plinked_list_node *L,
                            std::vector<ElemType_int> list) {
  *L = (plinked_list_node)calloc(1, sizeof(linked_list_node));
  if (!(*L)) {
    std::cout << "memory calloc failed!..." << std::endl;
    return ERROR;
  }
  plinked_list_node tail = *L;
  for (int i = 0; i < list.size(); i++) {
    plinked_list_node p =
        (plinked_list_node)calloc(1, sizeof(linked_list_node));
    if (!p) {
      std::cout << "memory calloc failed!..." << std::endl;
      return ERROR;
    }
    p->data = list[i];
    p->next = NULL;
    tail->next = p;
    tail = p;
  }

  return OK;
}