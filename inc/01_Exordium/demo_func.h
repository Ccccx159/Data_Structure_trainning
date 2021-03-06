#ifndef _DEMO_FUNC_H
#define _DEMO_FUNC_H_

#include "01_Exordium/status.h"


#ifdef __cplusplus
extern "C" {
#endif

//顺序表的测试接口函数
void test_SequenceList_demo();

//单链表测试接口函数
void test_SinglyLinkedList_demo();

//双向循环链表测试接口函数
void test_DualCycleLinkedList_demo();

// 顺序栈测试接口函数
void test_SequenceStack_demo();

// 链栈测试接口函数
void test_LinkedListStack_demo();

// 行编辑程序测试接口函数
void test_LineEditor_demo();

// 汉诺塔测试接口函数
void test_Hanoi_demo();

// 表达式求值测试接口
void test_Expression_demo();

// 利用栈实现迷宫寻路测试接口
void test_Maze_demo();

// 链式队列实现测试接口
void test_LinkedQueue_demo();

// 循环队列实现测试接口
void test_CircularQueue_demo();

#ifdef __cplusplus
}
#endif

#endif // !1
