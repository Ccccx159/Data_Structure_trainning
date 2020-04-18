#include "03_StackAndQueue/05_Expression/Expression.h"

// infix expression convert to suffix expression
Status infixConvertSuffix(const std::string &src, sq_stack_t *dst) {
  check_ptr(dst->base);

  sq_stack_t tmp = {0};
  init_stack_sq(&tmp);

  int ret = OK;
  int flag = 0;

  for (int i = 0; i < src.length(); i++) {
    if ('0' <= src[i] && src[i] <= '9') {
      push_stack_sq(dst, src[i]);
    } else if (src[i] == '+' || src[i] == '-') {
      while (1 && tmp.stack_len != 0) {
        elemType_sq_stack ch;
        ret = get_top_stack_sq(tmp, &ch);
        if (ch != '(') {
          pop_stack_sq(&tmp, &ch);
          push_stack_sq(dst, ch);
        } else {
          break;
        }
      }
      push_stack_sq(&tmp, src[i]);
    } else if (src[i] == '*' || src[i] == '/') {
      while (1 && tmp.stack_len != 0) {
        elemType_sq_stack ch;
        ret = get_top_stack_sq(tmp, &ch);
        if (ch == '*' || ch == '/') {
          pop_stack_sq(&tmp, &ch);
          push_stack_sq(dst, ch);
        } else {
          break;
        }
      }
      push_stack_sq(&tmp, src[i]);
    } else if (src[i] == '(') {
      push_stack_sq(&tmp, src[i]);
      flag++;
    } else {
      while (1 && tmp.stack_len != 0) {
        elemType_sq_stack ch;
        ret = get_top_stack_sq(tmp, &ch);
        if (ch != '(') {
          pop_stack_sq(&tmp, &ch);
          push_stack_sq(dst, ch);
        } else {
          pop_stack_sq(&tmp, &ch);
          flag--;
          break;
        }
      }
    }
  }
  if (flag != 0) {
    LOG_ERROR("brackets not paired!...Expression invaild!...\n");
    destroy_stack_sq(&tmp);
    return ERROR;
  }
  while (tmp.stack_len) {
    elemType_sq_stack ch;
    pop_stack_sq(&tmp, &ch);
    push_stack_sq(dst, ch);
  }

  destroy_stack_sq(&tmp);
  return OK;
}

// calculate the value of expression
Status calculateValue(sq_stack_t *exp, int *val) {
  sq_stack_t tmp_stk = {0};
  init_stack_sq(&tmp_stk);
  sq_stack_t tmp_cal = {0};
  init_stack_sq(&tmp_cal);

  while (exp->stack_len) {
    elemType_sq_stack tmp_elem;
    pop_stack_sq(exp, &tmp_elem);
    push_stack_sq(&tmp_stk, tmp_elem);
  }

  while (tmp_stk.stack_len) {
    elemType_sq_stack tmp_elem;
    pop_stack_sq(&tmp_stk, &tmp_elem);
    if ('0' <= tmp_elem && tmp_elem <= '9') {
      push_stack_sq(&tmp_cal, tmp_elem - '0');
    } else {
      int x = 0, y = 0;
      pop_stack_sq(&tmp_cal, (elemType_sq_stack *)&y);
      pop_stack_sq(&tmp_cal, (elemType_sq_stack *)&x);
      switch (tmp_elem) {
        case '+':
          (*val) = x + y;
          push_stack_sq(&tmp_cal, (*val));
          break;
        case '-':
          (*val) = x - y;
          push_stack_sq(&tmp_cal, (*val));
          break;
        case '*':
          (*val) = x * y;
          push_stack_sq(&tmp_cal, (*val));
          break;
        case '/':
          (*val) = x / y;
          push_stack_sq(&tmp_cal, (*val));
          break;
        default:
          break;
      }
    }
  }
  pop_stack_sq(&tmp_cal, (elemType_sq_stack *)val);

  destroy_stack_sq(&tmp_stk);
  destroy_stack_sq(&tmp_cal);
  return OK;
}