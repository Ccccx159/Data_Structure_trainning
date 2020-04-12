#include "demo_func.h"
#include "03_StackAndQueue/02_LinkedListStack/LinkedListStack.h"
using namespace std;

void test_LinkedListStack_demo() {
  linkedList_stack_t stk = {0};
  int ret = OK;

  cout << "function [init_stack_linkedList] test begin..." << endl;
  {
    printf("init LinkedList_Stack[stk] ...\n");
    ret = init_stack_linkedList(&stk);
    assert(ret == OK);
    cout << "init SUCCESS!..." << endl;
  }
  PressEnter;

  cout << "function [empty_stack_linkedList] test begin..." << endl;
  {
    TRUE == empty_stack_linkedList(stk) ? cout << "stack is EMPTY!" << endl
                                        : cout << "stack is NOT empty" << endl;
  }
  PressEnter;

  cout << "function [push_stack_linkedList] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: push [%d] in the position ^%d^", 2 * i, i);
      ret = push_stack_linkedList(&stk, 2 * i);
      assert(OK == ret);
      cout << endl;
    }
  }
  PressEnter;

  cout << "function [traverse_stack_linkedList] test begin..." << endl;
  {
    cout << "stack [stk]'s element is: " << endl;
    ret = traverse_stack_linkedList(stk);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_length_stack_linkedList] test begin..." << endl;
  {
    int length = get_length_stack_linkedList(stk);
    cout << "stack [stk]'s length is: [" << length << "]" << endl;
  }
  PressEnter;

  cout << "function [get_top_stack_linkedList] test begin..." << endl;
  {
    elemType_linkedStack e = 0;
    ret = get_top_stack_linkedList(stk, &e);
    assert(OK == ret);
    printf("the elem in top of stack is: [%d]\n", e);
  }
  PressEnter;

  cout << "function [pop_stack_sq] test begin..." << endl;
  {
    elemType_linkedStack e = 0;
    for (int i = 2; i > 0; i--) {
      ret = pop_stack_linkedList(&stk, &e);
      assert(OK == ret);
      cout << "pop elem" << e << endl;
    }
    ret = traverse_stack_linkedList(stk);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [destroy_stack_linkedList] test begin..." << endl;
  {
    ret = destroy_stack_linkedList(&stk);
    assert(OK == ret);
    printf("destroy sequenceStack SUCCESS!..\n");
  }
  PressEnter;
}