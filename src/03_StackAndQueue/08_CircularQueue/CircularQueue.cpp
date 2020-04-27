#include "03_StackAndQueue/08_CircularQueue/CircularQueue.h"

// 初始化队列
Status que_cir_init(ds_circular_que_t *que) {
  // 入参校验
  check_ptr(que);

  // 分配队列空间
  que->base = (elemType_que *)calloc(MAXSIZE_QUE, sizeof(elemType_que));
  check_ptr(que->base);
  que->que_size = MAXSIZE_QUE;
  que->front = 0;
  que->rear = 0;
  return OK;
}

// 销毁队列
Status que_cir_destroy(ds_circular_que_t *que) {
  check_ptr(que);

  if (que->base) {
    free(que->base);
    que->base = NULL;
    que->front = -1;
    que->rear = -1;
  } else {
    LOG_WARN("que already don't exist!...");
  }
  return OK;
}

// 清空队列
Status que_cir_clear(ds_circular_que_t *que) {
  check_ptr(que);
  check_ptr(que->base);
  memset(que->base, 0, que->que_size * sizeof(elemType_que));
  que->front = 0;
  que->rear = 0;
  return OK;
}

// 判断循环队列是否为空
Status que_cir_get_empty(ds_circular_que_t que) {
  return que.front == que.rear ? TRUE : FALSE;
}

// 获取队列长度
int que_cir_get_length(ds_circular_que_t que) {
  return (que.rear - que.front + que.que_size) % que.que_size;
}

// 获取队头元素
Status que_cir_get_head(ds_circular_que_t que, elemType_que *e) {
  check_ptr(e);
  elemType_que *tmp = que.base + que.front;
  memcpy(e, tmp, sizeof(elemType_que));
  return OK;
}

// 弹出队头元素
Status que_cir_pop_head(ds_circular_que_t *que, elemType_que *e) {
  check_ptr(que);
  if (que->base && que->front != que->rear) {
    memcpy(e, que->base + que->front, sizeof(elemType_que));
    que->front = (que->front + 1) % que->que_size;
    return OK;
  } else {
    LOG_ERROR("que is NULL or que is EMPTY!...plz check...\n");
    return ERROR;
  }
}

// 队尾压入新元素
Status que_cir_push_tail(ds_circular_que_t *que, elemType_que e) {
  check_ptr(que);
  if (que->base && (que->rear + 1) % que->que_size != que->front) {
    memcpy(que->base + que->rear, &e, sizeof(elemType_que));
    que->rear = (que->rear + 1) % que->que_size;
    return OK;
  } else {
    LOG_ERROR("que is NULL or que is FULL...plz check...\n");
    return ERROR;
  }
}

// 遍历访问队列元素
Status que_cir_traverse(ds_circular_que_t que, visit vfunc) {
  if (que.base && que.front != que.rear) {
    int len = que_cir_get_length(que);
    elemType_que *tmp = que.base + que.front;
    for (int i = 0; i < len; i++) {
      vfunc(tmp);
      tmp++;
    }
  } else {
    LOG_WARN("que is NULL or EMPTY!...plz check...\n");
    return ERROR;
  }

  return OK;
}
