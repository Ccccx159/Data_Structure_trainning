#include "02_LinearTable/03_DualCycleLinkedList/DualCycleLinkedList.h"
#include "demo_func.h"
using namespace std;

void test_DualCycleLinkedList_demo() {
  p_dual_cycle_linked_list_node_t L = NULL;
  int ret = OK;

  cout << "function [init_list_dcl] test begin..." << endl;
  {
    printf("init dualCycleLinkedList [L] ...\n");
    ret = init_list_dcl(&L);
    assert(ret == OK);
    cout << "init SUCCESS!..." << endl;
  }
  PressEnter;

  cout << "function [empty_list_dcl] test begin..." << endl;
  {
    TRUE == empty_list_dcl(L) ? cout << "list is EMPTY!" << endl
                              : cout << "list is NOT empty" << endl;
  }
  PressEnter;

  cout << "function [insert_list_dcl] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: insert [%d] in the position ^%d^", 2 * i, i);
      ret = insert_list_dcl(L, i, 2 * i);
      assert(OK == ret);
      cout << endl;
    }
  }
  PressEnter;

  cout << "function [traverse_list_dcl] test begin..." << endl;
  {
    cout << "list L's element is: " << endl;
    ret = traverse_list_dcl(L);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_length_list_dcl] test begin..." << endl;
  {
    int length = get_length_list_dcl(L);
    cout << "list L's length is: [" << length << "]" << endl;
  }
  PressEnter;

  extern Status bigger(int a, int b);

  cout << "function [get_local_linked_list] test begin..." << endl;
  {
    ElemType_dcl e = 5;
    int pos = locate_elem_list_dcl(L, e, bigger);
    if (pos == ERROR) {
      cout << "NO elem in the List SATISFYING CONDITION!" << endl;
    } else {
      printf("the first elem, which is bigger than e[%d], is in the pos^%d^\n",
             e, pos);
    }
  }
  PressEnter;

  cout << "function [delete_list_dcl] test begin..." << endl;
  {
    ElemType_dcl e = 0;
    int pos = 3;
    ret = delete_list_dcl(L, pos, &e);
    assert(OK == ret);
    printf("deleted elem in position ^%d^ is [%d]\n", pos, e);
    cout << "now L's element is: ";
    ret = traverse_list_dcl(L);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_elem_list_dcl] test begin..." << endl;
  {
    int pos = 4;
    ElemType_dcl e = 0;
    ret = get_elem_list_dcl(L, pos, &e);
    assert(OK == ret);
    printf("the elem in position ^%d^ is: [%d]\n", pos, e);
  }
  PressEnter;

  cout << "function [get_prior_list_dcl] test begin..." << endl;
  {
    ElemType_dcl cur_e = 8;
    ElemType_dcl prior_e = 0;
    ret = get_prior_list_dcl(L, cur_e, &prior_e);
    assert(OK == ret);
    printf("the elem[%d]'s PRIOR node is: [%d]\n", cur_e, prior_e);
  }
  PressEnter;

  cout << "function [get_next_list_dcl] test begin..." << endl;
  {
    ElemType_dcl cur_e = 8;
    ElemType_dcl next_e = 0;
    ret = get_next_list_dcl(L, cur_e, &next_e);
    assert(OK == ret);
    printf("the elem[%d]'s NEXT node is: [%d]\n", cur_e, next_e);
  }
  PressEnter;

  cout << "function [destroy_list_dcl] test begin..." << endl;
  {
    ret = destroy_list_dcl(&L);
    assert(OK == ret);
    printf("destroy dualCycleLinkedList SUCCESS!..\n");
  }
  PressEnter;
}