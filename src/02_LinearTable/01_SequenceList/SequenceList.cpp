#include "02_LinearTable/01_SequenceList/SequenceList.h"

//初始化顺序表
Status init_list_seq(pSqlist L) {
  L->elem = (ElemType_Sql *)calloc(LIST_INIT_SIZE, sizeof(ElemType_Sql));
  if (NULL == L->elem) {
    return OVERFLOW;
  }
  L->length = 0;
  L->list_size = LIST_INIT_SIZE * sizeof(ElemType_Sql);
  return OK;
}

//清空顺序表
Status clear_list_seq(pSqlist L) {
  memset(L->elem, 0, LIST_INIT_SIZE * sizeof(ElemType_Sql));
  L->length = 0;
  L->list_size = LIST_INIT_SIZE;
  return OK;
}

//销毁顺序表
Status destroy_list_seq(pSqlist L) {
  memset(L->elem, 0, LIST_INIT_SIZE * sizeof(ElemType_Sql));
  free(L->elem);
  L->elem = NULL;
  L->length = 0;
  L->list_size = 0;
  free(L);
  if (NULL != L) {
    return UNSUCCESS;
  }
  return SUCCESS;
}

//判断顺序表是否为空，空则返回true，否则返回false
Status empty_list_seq(Sqlist L) { return L.length > 0 ? FALSE : TRUE; }

//获得顺序表长度
int get_length_list_seq(Sqlist L) { return L.length; }

//查：获取第i个元素内容
Status get_elem_list_seq(Sqlist L, int i, ElemType_Sql *e) {
  if (i > L.length) {
    std::cout << "list L's length is [" << L.length << "], i[" << i << "] > "
              << "length" << std::endl;
  }
  *e = L.elem[i - 1];
  return OK;
}

//查：获取元素e在顺序表中第一次出现的位置
int get_local_list_seq(Sqlist L, ElemType_Sql e, compare func) {
  for (int idx = 0; idx < L.length; idx++) {
    if (!func(e, L.elem[idx])) {
      return idx + 1;
    }
  }
  std::cout << "No elem [" << e << "] in this list!" << std::endl;
  return -1;
}

//查：获取元素e的前驱
Status get_prior_list_seq(Sqlist L, ElemType_Sql e, ElemType_Sql *pre) {
  for (int idx = 0; idx < L.length; idx++) {
    if (e == L.elem[idx] && idx != 0) {
      *pre = L.elem[idx - 1];
      return OK;
    }
  }
  std::cout << "elem e[" << e << "] doesn't have prior node!" << std::endl;
  return ERROR;
}

//查：获取元素e的后继
Status get_next_list_seq(Sqlist L, ElemType_Sql e, ElemType_Sql *next) {
  for (int idx = 0; idx < L.length; idx++) {
    if (e == L.elem[idx] && idx != (L.length - 1)) {
      *next = L.elem[idx + 1];
      return OK;
    }
  }
  std::cout << "elem e[" << e << "] doesn't have next node!" << std::endl;
  return ERROR;
}

//插入：在位置i处插入元素e
Status insert_list_seq(pSqlist L, int i, ElemType_Sql e) {
  if (i <= 0) {
    printf("i[%d] invalid!\n", i);
    return ERROR;
  }
  if (LIST_INIT_SIZE <= L->length) {
    std::cout << "list need to expand" << std::endl;
    std::cout << "insert beging: ..." << std::endl;
    L->elem = (ElemType_Sql *)realloc(
        L->elem, (LIST_INIT_SIZE + LIST_INIT_SIZE) * sizeof(ElemType_Sql));
    if (NULL == L->elem) {
      std::cout << "List realloc failed!" << std::endl;
      return OVERFLOW;
    } else {
      L->list_size = (LIST_INIT_SIZE + LIST_INIT_SIZE) * sizeof(ElemType_Sql);
    }
  }
  for (int idx = L->length; idx >= 0 && idx > i; idx--) {
    L->elem[idx] = L->elem[idx - 1];
  }
  L->elem[i - 1] = e;
  L->length++;
  return OK;
}

//删：删除顺序表中的第i个数据，用e接收原第i个元素
Status del_list_seq(pSqlist L, int i, ElemType_Sql *e) {
  if (i <= 0 || i > L->length) {
    printf("i[%d] invalid\n", i);
    return ERROR;
  }
  *e = L->elem[i - 1];
  for (int idx = i - 1; idx < L->length - 1; idx++) {
    L->elem[idx] = L->elem[idx + 1];
  }
  L->elem[L->length - 1] = 0;
  L->length--;
  return OK;
}

//遍历顺序表
Status traversal_list_seq(Sqlist L) {
  for (int idx = 0; idx < L.length; idx++) {
    if (idx != 0) {
      std::cout << " ";
    }
    std::cout << L.elem[idx];
    if (idx == L.length - 1) {
      std::cout << std::endl;
    }
  }
  return OK;
}

extern Status equal(int a, int b);

//求两个顺序表的并集
void union_list_seq(Sqlist *La, Sqlist Lb) {
  for (int idx = 0; idx < Lb.length; idx++) {
    int pos = get_local_list_seq(*La, Lb.elem[idx], equal);
    if (pos > 0) {
      continue;
    } else {
      insert_list_seq(La, La->length + 1, Lb.elem[idx]);
    }
  }
}

//顺序表的合并
Status merge_list_seq(Sqlist La, Sqlist Lb, pSqlist Lc) {
  Lc->elem =
      (ElemType_Sql *)calloc(La.length + Lb.length, sizeof(ElemType_Sql));
  Lc->length = La.length + Lb.length;
  Lc->list_size = (La.length + Lb.length) * sizeof(ElemType_Sql);

  ElemType_Sql *pc = Lc->elem;
  ElemType_Sql *pa = La.elem;
  ElemType_Sql *pb = Lb.elem;

  while (pa <= La.elem + La.length - 1 && pb <= Lb.elem + Lb.length - 1) {
    if (*pa <= *pb) {
      *pc++ = *pa++;
    } else {
      *pc++ = *pb++;
    }
  }

  while (pa <= La.elem + La.length - 1) {
    *pc++ = *pa++;
  }
  while (pb <= Lb.elem + Lb.length - 1) {
    *pc++ = *pb++;
  }

  return OK;
}