#ifndef _HANOI_H_
#define _HANOI_H_

#include "status.h"
#include "03_StackAndQueue/01_SequenceStack/SequenceStack.h"

#ifdef __cplusplus
extern "C" {
#endif


// 汉诺塔递归实现
void hanoi(int scale, sq_stack_t *x, sq_stack_t *y, sq_stack_t *z);

#ifdef __cplusplus
}
#endif

#endif // _HANOI_H_