#include "01_Exordium/demo_func.h"
#include "02_LinearTable/02_SinglyLinkedList/SinglyLinkedList.h"
using namespace std;

void test_SinglyLinkedList_demo() {
  plinked_list_node L = NULL;
  int ret = OK;

  cout << "function [init_linked_list] test begin..." << endl;
  {
    printf("init SinglyLinkedList [L] ...\n");
    ret = init_linked_list(&L);
    assert(ret == OK);
    cout << "init SUCCESS!..." << endl;
  }
  PressEnter;

  cout << "function [empty_linked_list] test begin..." << endl;
  {
    TRUE == empty_linked_list(L) ? cout << "list is EMPTY!" << endl
                                 : cout << "list is NOT empty" << endl;
  }
  PressEnter;

  cout << "function [insert_linked_list] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: insert [%d] in the position ^%d^", 2 * i, i);
      ret = insert_linked_list(L, i, 2 * i);
      assert(OK == ret);
      cout << endl;
    }
  }
  PressEnter;

  cout << "function [traverse_linked_list] test begin..." << endl;
  {
    cout << "list L's element is: ";
    ret = traverse_linked_list(L);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_length_linked_list] test begin..." << endl;
  {
    int length = get_length_linked_list(L);
    cout << "list L's length is: [" << length << "]" << endl;
  }
  PressEnter;

  extern Status bigger(int a, int b);

  cout << "function [get_local_linked_list] test begin..." << endl;
  {
    int e = 5;
    int pos = get_local_linked_list(L, e, bigger);
    int len = get_length_linked_list(L);
    if (pos <= len) {
      printf("the first elem, which is bigger than e[%d], is in the pos^%d^\n",
             e, pos);
    } else {
      cout << "NO elem in the List SATISFYING CONDITION!" << endl;
    }
  }
  PressEnter;

  cout << "function [delete_linked_list] test begin..." << endl;
  {
    ElemType_int e = 0;
    int pos = 3;
    ret = delete_linked_list(L, pos, &e);
    assert(OK == ret);
    printf("deleted elem in position ^%d^ is [%d]\n", pos, e);
    cout << "now L's element is: ";
    ret = traverse_linked_list(L);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_elem_linked_list] test begin..." << endl;
  {
    int pos = 4;
    ElemType_int e = 0;
    ret = get_elem_linked_list(L, pos, &e);
    assert(OK == ret);
    printf("the elem in position ^%d^ is: [%d]\n", pos, e);
  }
  PressEnter;

  cout << "function [create_linked_list_h] test begin..." << endl;
  {
    plinked_list_node H = NULL;
    vector<ElemType_int> data;
    for (int i=0; i<10; i++) {
      data.push_back(i);
    }
    ret = create_linked_list_h(&H, data);
    assert(OK == ret);
    printf("create linked_list from HEAD SUCCESS!\n");
    cout << "now head_linked_list is: ";
    ret = traverse_linked_list(H);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [create_linked_list_t] test begin..." << endl;
  {
    plinked_list_node T = NULL;
    vector<ElemType_int> data;
    for (int i=0; i<10; i++) {
      data.push_back(i);
    }
    ret = create_linked_list_t(&T, data);
    assert(OK == ret);
    printf("create linked_list from TAIL SUCCESS!\n");
    cout << "now tail_linked_list is: ";
    ret = traverse_linked_list(T);
    assert(OK == ret);
  }
  PressEnter;
}