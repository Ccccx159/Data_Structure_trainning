#include "03_StackAndQueue/01_SequenceStack/SequenceStack.h"

#define check_ptr(ptr)                                      \
  {                                                         \
    if (!ptr) {                                             \
      std::cout << "ptr is NULL, pls chk!..." << std::endl; \
      return ERROR;                                         \
    }                                                       \
  }

// 初始化顺序栈
Status init_stack_sq(p_sq_stack_t stk) {
  stk->base =
      (elemType_sq_stack *)calloc(STACK_INIT_SIZE + 1, sizeof(elemType_sq_stack));
  if (!stk->base) {
    std::cout << "memory calloc failed!" << std::endl;
    return OVERFLOW;
  }
  stk->top = stk->base;
  stk->stackSize = STACK_INIT_SIZE;
  stk->stack_len = 0;

  return OK;
}

// 销毁顺序栈
Status destroy_stack_sq(p_sq_stack_t stk) {
  check_ptr(stk->base);
  free(stk->base);
  stk->base = NULL;
  stk->top = NULL;
  stk->stackSize = 0;
  stk->stack_len = 0;

  return OK;
}

// 清空
Status clear_stack_sq(p_sq_stack_t stk) {
  check_ptr(stk->base);
  if (stk->top == stk->base) {
    std::cout << "stack is already Clear!..." << std::endl;
    return OK;
  }
  memset(stk->base, 0, stk->stackSize * sizeof(elemType_sq_stack));
  stk->top = stk->base;
  stk->stack_len = 0;

  return OK;
}

// 判断是否为空
Status empty_stack_sq(sq_stack_t stk) {
  return 0 == stk.stack_len ? TRUE : FALSE;
}

// 获取栈长
int get_length_stack_sq(sq_stack_t stk) { return stk.stack_len; }

// 用e获取栈顶元素
Status get_top_stack_sq(sq_stack_t stk, elemType_sq_stack *e) {
  if (TRUE == empty_stack_sq) {
    std::cout << "stack is empty!..." << std::endl;
    return ERROR;
  }
  (*e) = *(stk.top - 1);
  return OK;
}

// 元素e进栈
Status push_stack_sq(p_sq_stack_t stk, elemType_sq_stack e) {
  if (stk->stack_len == stk->stackSize) {
    stk->base = (elemType_sq_stack *)realloc(
        stk->base,
        (STACK_INIT_SIZE + 1 + STACK_INCREMENT) * sizeof(elemType_sq_stack));
    check_ptr(stk->base);
    stk->stackSize = STACK_INIT_SIZE + STACK_INCREMENT;
  }
  *(stk->top) = e;
  stk->top++;
  stk->stack_len++;

  return OK;
}

// 元素e出栈
Status pop_stack_sq(p_sq_stack_t stk, elemType_sq_stack *e) {
  if (0 == stk->stack_len) {
    std::cout << "stack is Empty!..." << std::endl;
    return ERROR;
  }
  (*e) = *(--stk->top);
  (*stk->top) = 0;
  stk->stack_len--;

  return OK;
}

// 遍历
Status traverse_stack_sq(sq_stack_t stk) {
  check_ptr(stk.base);
  if (0 == stk.stack_len) {
    std::cout << "stack is Empty!..." << std::endl;
    return ERROR;
  }
  
  for (elemType_sq_stack *tmp = stk.top - 1; tmp >= stk.base;) {
    std::cout << *tmp << " ";
    tmp--;
  }

  return OK;
}