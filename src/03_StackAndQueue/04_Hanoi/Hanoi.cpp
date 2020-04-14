#include "03_StackAndQueue/04_Hanoi/Hanoi.h"

static void moveN_xToz(sq_stack_t *x, sq_stack_t *z) {
  elemType_sq_stack tmp = 0;
  int ret = OK;
  ret = pop_stack_sq(x, &tmp);
  if (OK != ret) {
    LOG_ERROR("pop failed!..pls check...\n");
    return;
  }
  ret = push_stack_sq(z, tmp);
  if (OK != ret) {
    LOG_ERROR("push failed!..pls check...\n");
  }

  LOG_WARN("move [%d] from [%s] to [%s]\n", tmp, x->stack_name, z->stack_name);
  return;
}

void hanoi(int scale, sq_stack_t *x, sq_stack_t *y, sq_stack_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    LOG_ERROR("param Error! x[%p], y[%p], z[%p]\n", x, y, z);
    return;
  }

  if (scale == 1) {
    moveN_xToz(x, z);
  } else {
    hanoi(scale - 1, x, z, y);
    moveN_xToz(x, z);
    hanoi(scale - 1, y, x, z);
  }
}