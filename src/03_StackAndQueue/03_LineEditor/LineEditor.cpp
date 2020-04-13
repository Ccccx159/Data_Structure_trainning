#include "03_StackAndQueue/03_LineEditor/LineEditor.h"

Status lineEditor_sq_stack(std::string& dst, const std::string& src) {
  sq_stack_t stk = {0};
  int ret = OK;
  ret = init_stack_sq(&stk);
  if (OK != ret) {
    LOG_ERROR("stack init failed!...pls check and try again...\n");
    return ret;
  }

  int len = src.length();
  elemType_sq_stack tmp;
  for (int i = 0; i < len; i++) {
    switch (src[i]) {
      case '#':
        ret = pop_stack_sq(&stk, &tmp);
        if (OK != ret) {
          LOG_ERROR("pop elem failed!... pls try debug...\n");
          return ret;
        }
        break;
      case '@':
        ret = clear_stack_sq(&stk);
        if (OK != ret) {
          LOG_ERROR("clear stack failed!... pls try debug...\n");
          return ret;
        }
        break;
      default:
        ret = push_stack_sq(&stk, src[i]);
        if (OK != ret) {
          LOG_ERROR("push elem failed!... pls try debug...\n");
          return ret;
        }
        break;
    }
  }

  while (0 != stk.stack_len) {
    ret = pop_stack_sq(&stk, &tmp);
    if (OK != ret) {
      LOG_ERROR("pop elem failed!... pls try debug...\n");
      return ret;
    }
    char ch[1] = {0};
    ch[0] = tmp;
    dst.insert(0, ch);
  }

  ret = destroy_stack_sq(&stk);
  if (OK != ret) {
    LOG_ERROR("destroy stack_sq failed!... pls try debug...\n");
    return ret;
  }

  LOG_INFO("final resualt is %s\n", dst.c_str());
  return ret;
}