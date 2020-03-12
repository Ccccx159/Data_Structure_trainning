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


}
