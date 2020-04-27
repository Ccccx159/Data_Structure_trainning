#include "03_StackAndQueue/07_LinkedQueue/LinkedQueue.h"

Status linkedQue_init(linkedque_t *que_l) {
  check_ptr(que_l);
  que_l->front = (linkedque_node_t *)calloc(1, sizeof(linkedque_node_t));
  check_ptr(que_l->front);
  que_l->rear = que_l->front;
  que_l->que_len = 0;

  return OK;
}

Status linkedQue_destroy(linkedque_t *que_l) {
  check_ptr(que_l);
  while (que_l->front) {
    que_l->rear = que_l->front->next;
    free(que_l->front);
    que_l->front = que_l->rear;
  }
  que_l->que_len = 0;

  return OK;
}

Status linkedQue_get_empty(linkedque_t que_l) {
  return (que_l.que_len == 0) ? TRUE : FALSE;
}

int linkedQue_get_length(linkedque_t que_l) { return que_l.que_len; }

Status linkedQue_get_head(linkedque_t que_l, elemType_que_lq *e) {
  check_ptr(que_l.front);
  memcpy(e, &que_l.front->data, sizeof(elemType_que_lq));
  return OK;
}

Status linkedQue_push_tail(linkedque_t *que_l, elemType_que_lq e) {
  check_ptr(que_l);
  memcpy(&que_l->rear->data, &e, sizeof(elemType_que_lq));
  linkedque_node_t *tmp =
      (linkedque_node_t *)calloc(1, sizeof(linkedque_node_t));
  check_ptr(tmp);
  que_l->rear->next = tmp;
  que_l->rear = tmp;
  que_l->que_len++;
  return OK;
}

Status linkedQue_pop_head(linkedque_t *que_l, elemType_que_lq *e) {
  check_ptr(que_l);

  if (que_l->que_len > 0) {
    memcpy(e, &que_l->front->data, sizeof(elemType_que_lq));
    linkedque_node_t *tmp = que_l->front;
    que_l->front = que_l->front->next;
    free(tmp);
    que_l->que_len--;
    return OK;
  } else {
    LOG_ERROR("linked queue is MEPTY");
    return ERROR;
  }
}

Status linkedQue_traverse(linkedque_t que_l, visit vfunc) {
  linkedque_node_t *tmp = que_l.front;
  while (tmp && tmp != que_l.rear)
  {
    vfunc(&tmp->data);
    tmp = tmp->next;
  }
  return OK;
}