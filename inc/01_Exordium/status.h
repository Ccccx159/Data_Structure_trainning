/**********************************
 *                                *
 * 文件夹: 01_Exordium              *
 *                                *
 * 文件名: Status.h               *
 *                                *
 * 内  容: 相关状态码及宏函数列表 *
 *                                *
 **********************************/

#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* 状态码 */
#define TRUE 0         //真
#define FALSE 1        //假
#define YES 0          //是
#define NO 1           //否
#define OK 0           //通过
#define ERROR -1        //错误
#define SUCCESS 0      //成功
#define UNSUCCESS -1    //失败
#define INFEASIBLE -2  //不可行

#ifndef _MATH_H_      //系统中已有此状态码定义，要避免冲突
#define OVERFLOW -5   //堆栈上溢
#define UNDERFLOW -6  //堆栈下溢
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/* 状态码识别类型 */
typedef int Status;

/*宏函数*/
//函数暂停一段时间
#define Wait(x)                                                             \
  {                                                                         \
    double _Loop_Num_;                                                      \
    for (_Loop_Num_ = 0.01; _Loop_Num_ <= 100000.0 * x; _Loop_Num_ += 0.01) \
      ;                                                                     \
  }  //设立一个空循环

//摁Enter键继续
#define PressEnter            \
  {                           \
    fflush(stdin);            \
    printf("Press Enter..."); \
    getchar();                \
    fflush(stdin);            \
  }

#ifdef __cplusplus
extern "C" {
#endif

typedef Status (*compare)(int a, int b);
  
//自定义输入函数声明
int scanf_priv(FILE *fp, char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
