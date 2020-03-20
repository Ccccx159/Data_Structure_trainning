/*线性表相关学习*/

#ifndef _SEQUENCELIST_H_
#define _SEQUENCELIST_H_

#include "01_Exordium/status.h"

#define LIST_INIT_SIZE 100  //初始化顺序表预留空间
#define LIST_INCREMENT 10   //顺序表单次扩容大小

//顺序表数据类型定义
#ifndef ELEMENT_TYPE_SQL
#define ELEMENT_TYPE_SQL
typedef int ElemType_Sql;
#endif

typedef struct {
  ElemType_Sql *elem;  //顺序表存储空间基址
  int length;          //顺序表长度
  int list_size;       //顺序表当前空间大小
} Sqlist, *pSqlist;

#ifdef __cplusplus
extern "C" {
#endif

//初始化顺序表
Status init_list_seq(pSqlist L);

//清空顺序表
Status clear_list_seq(pSqlist L);

//销毁顺序表
Status destroy_list_seq(pSqlist L);

//判断顺序表是否为空，空则返回true，否则返回false
Status empty_list_seq(Sqlist L);

//获得顺序表长度
int get_length_list_seq(Sqlist L);

//查：获取第i个元素内容
Status get_elem_list_seq(Sqlist L, int i, ElemType_Sql *e);

//查：获取元素e在顺序表中的位置
int get_local_list_seq(Sqlist L, ElemType_Sql e, compare func);

//查：获取元素e的前驱
Status get_prior_list_seq(Sqlist L, ElemType_Sql e, ElemType_Sql *pre);

//查：获取元素e的后继
Status get_next_list_seq(Sqlist L, ElemType_Sql e, ElemType_Sql *next);

//插入：在位置i处插入元素e
Status insert_list_seq(pSqlist L, int i, ElemType_Sql e);

//删：删除顺序表中的第i个数据，用e接收原第i个元素
Status del_list_seq(pSqlist L, int i, ElemType_Sql *e);

//遍历顺序表
Status traversal_list_seq(Sqlist L);
  
/******************************************************************************/

//求两个顺序表的并集
void union_list_seq(Sqlist *La, Sqlist Lb);

//顺序表的合并
Status merge_list_seq(Sqlist La, Sqlist Lb, pSqlist Lc);

#ifdef __cplusplus
}
#endif

#endif
