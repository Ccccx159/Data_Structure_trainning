/*******************************************************************
Attention:                                                         /
    This function is just used to Compute within 10 positive       /
    integer expressions.                                           /
                                                                   /
    Follow-up to optimize                                          /
*******************************************************************/


#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "status.h"

typedef char elemType_sq_stack;
#include "../src/03_StackAndQueue/01_SequenceStack/SequenceStack.cpp"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// infix expression convert to suffix expression
Status infixConvertSuffix(const std::string& src, sq_stack_t* dst);

// calculate the value of expression
Status calculateValue(sq_stack_t* exp, int* val);

#ifdef __cplusplus
}
#endif

#endif