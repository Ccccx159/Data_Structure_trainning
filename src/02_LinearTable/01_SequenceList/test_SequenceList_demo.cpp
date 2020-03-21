#include "01_Exordium/demo_func.h"
#include "02_LinearTable/01_SequenceList/SequenceList.h"
using namespace std;

//顺序表的测试接口函数
void test_SequenceList_demo() {
  Sqlist L = {0};
  int ret = OK;

  cout << "function [init_list_seq] test begin..." << endl;
  {
    printf("init SequenceList [L] ...\n");
    ret = init_list_seq(&L);
    assert(ret == OK);
    cout << endl;
  }
  PressEnter;

  cout << "function [empty_list_seq] test begin..." << endl;
  {
    TRUE == empty_list_seq(L) ? cout << "list is EMPTY!" << endl
                              : cout << "list is NOT empty" << endl;
    cout << endl;
  }
  PressEnter;

  cout << "function [insert_list_seq] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: insert [%d] in the position ^%d^", 2 * i, i);
      ret = insert_list_seq(&L, i, 2 * i);
      assert(OK == ret);
      cout << endl;
    }
    cout << endl;
  }
  PressEnter;

  cout << "function [traversal_list_seq] test begin..." << endl;
  {
    cout << "list L's element is: ";
    ret = traversal_list_seq(L);
    assert(OK == ret);
    cout << endl;
  }
  PressEnter;

  cout << "function [get_length_list_seq] test begin..." << endl;
  {
    int length = get_length_list_seq(L);
    cout << "list L's length is: [" << length << "]" << endl;
    cout << endl;
  }
  PressEnter;

    extern Status bigger(int a, int b);

  cout << "function [get_local_list_seq] test begin..." << endl;
  {
    int e = 5;
    int pos = get_local_list_seq(L, e, bigger);
    if (pos <= L.length) {
      printf("the first elem, which is bigger than e[%d], is in the pos^%d^\n",
             e, pos);
    } else {
      cout << "NO elem in the List SATISFYING CONDITION!" << endl;
    }
    cout << endl;
  }
  PressEnter;
  
  cout << "function [del_list_seq] test begin..." << endl;
  {
    ElemType_Sql e = 0;
    int pos = 3;
    ret = del_list_seq(&L, pos, &e);
    assert(OK == ret);
    printf("deleted elem in position ^%d^ is [%d]\n", pos, e);
    cout << "now L's element is: ";
    ret = traversal_list_seq(L);
    assert(OK == ret);
    cout << endl;
  }
  PressEnter;

  cout << "function [get_elem_list_seq] test begin..." << endl;
  {
    int pos = 4;
    ElemType_Sql e = 0;
    ret = get_elem_list_seq(L, pos, &e);
    assert(OK == ret);
    printf("the elem in position ^%d^ is: [%d]\n", pos, e);
    cout << endl;
  }
  PressEnter;

    cout << "function [union_list_seq] test begin..." << endl;
  {
    Sqlist La, Lb;
    int a[5] = {5, 2, 1, 3, 9};
    int b[7] = {7, 2, 6, 9, 11, 3, 10};

    init_list_seq(&La);
    for (int i=0; i<5; i++) {
      insert_list_seq(&La, i+1, a[i]);
    }
    cout << "La: ";
    traversal_list_seq(La);

    init_list_seq(&Lb);
    for (int i=0; i<7; i++) {
      insert_list_seq(&Lb, i+1, b[i]);
    }
    cout << "Lb: ";
    traversal_list_seq(Lb);

    union_list_seq(&La, Lb);
    cout << "after union, La: ";
    traversal_list_seq(La);
    destroy_list_seq(&La);
    destroy_list_seq(&Lb);
    cout << endl;
  }

  cout << "function [merge_list_seq] test begin..." << endl;
  {
    Sqlist La, Lb, Lc;

    init_list_seq(&La);
    for (int i=0; i<5; i++) {
      insert_list_seq(&La, i+1, 2*i);
    }
    cout << "La: ";
    traversal_list_seq(La);

    init_list_seq(&Lb);
    for (int i=0; i<7; i++) {
      insert_list_seq(&Lb, i+1, 2*i+1);
    }
    cout << "Lb: ";
    traversal_list_seq(Lb);

    merge_list_seq(La, Lb, &Lc);
    cout << "after merge, Lc: ";
    traversal_list_seq(Lc);
    destroy_list_seq(&La);
    destroy_list_seq(&Lb);
    destroy_list_seq(&Lc);
    cout << endl;
  }

  destroy_list_seq(&L);

}
