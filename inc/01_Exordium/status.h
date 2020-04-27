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

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

/* 状态码 */
#define TRUE 0         //真
#define FALSE 1        //假
#define YES 0          //是
#define NO 1           //否
#define OK 0           //通过
#define ERROR -1       //错误
#define SUCCESS 0      //成功
#define UNSUCCESS -1   //失败
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

/* 日志颜色宏定义 */
/*
\033[:表示转义序列开始
0    :特殊属性，0表示默认关闭，1表示高亮等
30   :字体前景色
47   :字体背景色
字色              背景              颜色
---------------------------------------
30                40              黑色
31                41              紅色
32                42              綠色
33                43              黃色
34                44              藍色
35                45              紫紅色
36                46              青藍色
37                47              白色
*/
#define black "\033[0;30m"
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;34m"
#define purple "\033[0;35m"
#define cyan "\033[0;36m"
#define white "\033[0;37m"
#define defaultclr "\033[0m"

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
    std::cout << std::endl;   \
  }

#define LOG_WARN(format, ...)                                                 \
  do {                                                                        \
    printf(yellow "[%s][line: %d]" format defaultclr, __FUNCTION__, __LINE__, \
           ##__VA_ARGS__);                                                    \
  } while (0)

#define LOG_INFO(format, ...)                                                \
  do {                                                                       \
    printf(green "[%s][line: %d]" format defaultclr, __FUNCTION__, __LINE__, \
           ##__VA_ARGS__);                                                   \
  } while (0)

#define LOG_ERROR(format, ...)                                             \
  do {                                                                     \
    printf(red "[%s][line: %d]" format defaultclr, __FUNCTION__, __LINE__, \
           ##__VA_ARGS__);                                                 \
  } while (0)

#define ASSERT(x)                                                    \
  if ((x) == 0) {                                                    \
    printf(red "assert!::[%s][line: %d]\n" defaultclr, __FUNCTION__, \
           __LINE__);                                                \
    while (1)                                                        \
      ;                                                              \
  }

#define check_ptr(ptr)                                      \
  {                                                         \
    if (!ptr) {                                             \
      std::cout << "ptr is NULL, pls chk!..." << std::endl; \
      return ERROR;                                         \
    }                                                       \
  }

// 定义一个函数指针，用于注册比较函数
typedef Status (*compare)(int a, int b);

// 定义一个函数指针，用于注册遍历函数
typedef void (*visit)(void *elem);

// 自定义输入函数声明
int scanf_priv(FILE *fp, char *format, ...);

/*****************************************************************************
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 参数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
 *
 * 注意:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
                            int outSize);

#ifdef __cplusplus
}
#endif

#endif
