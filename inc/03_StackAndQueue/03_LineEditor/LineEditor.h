#ifndef _LINEEDITOR_H_
#define _LINEEDITOR_H_

#include "status.h"
#include "03_StackAndQueue/01_SequenceStack/SequenceStack.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//行编辑函数
Status lineEditor_sq_stack(std::string &dst, const std::string& src);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _LINEEDITOR_H_
