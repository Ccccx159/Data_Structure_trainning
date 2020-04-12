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
    // cout << "init SUCCESS!..." << endl;
    LOG_INFO("init SUCCESS!...\n");
  }
  PressEnter;

  cout << "function [empty_stack_linkedList] test begin..." << endl;
  {
    if (TRUE == empty_stack_linkedList(stk)) {
      LOG_WARN("stack is EMPTY!\n");
    } else {
      LOG_WARN("stack is NOT empty\n");
    }
  }
  PressEnter;

  cout << "function [push_stack_linkedList] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      LOG_WARN("for example: push [%d] in the position ^%d^", 2 * i, i);
      ret = push_stack_linkedList(&stk, 2 * i);
      assert(OK == ret);
      cout << endl;
    }
  }
  PressEnter;

  cout << "function [traverse_stack_linkedList] test begin..." << endl;
  {
    LOG_INFO("stack [stk]'s element is: \n");
    ret = traverse_stack_linkedList(stk);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [get_length_stack_linkedList] test begin..." << endl;
  {
    int length = get_length_stack_linkedList(stk);
    LOG_INFO("stack [stk]'s length is: [%d]\n", length);
  }
  PressEnter;

  cout << "function [get_top_stack_linkedList] test begin..." << endl;
  {
    elemType_linkedStack e = 0;
    ret = get_top_stack_linkedList(stk, &e);
    assert(OK == ret);
    LOG_INFO("the elem in top of stack is: [%d]\n", e);
  }
  PressEnter;

  cout << "function [pop_stack_sq] test begin..." << endl;
  {
    elemType_linkedStack e = 0;
    for (int i = 2; i > 0; i--) {
      ret = pop_stack_linkedList(&stk, &e);
      assert(OK == ret);
      LOG_WARN("pop elem %d\n", e);
    }
    ret = traverse_stack_linkedList(stk);
    assert(OK == ret);
  }
  PressEnter;

  cout << "function [destroy_stack_linkedList] test begin..." << endl;
  {
    ret = destroy_stack_linkedList(&stk);
    assert(OK == ret);
    LOG_INFO("destroy sequenceStack SUCCESS!..\n");
  }
  PressEnter;
}