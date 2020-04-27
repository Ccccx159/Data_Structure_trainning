#include "03_StackAndQueue/08_CircularQueue/CircularQueue.h"
#include "demo_func.h"
using namespace std;

void print_cir_que(void *e) {
  cout << *((elemType_que*)e) << " ";  
}

void test_CircularQueue_demo() {
  ds_circular_que_t que = {0};
  int ret = OK;

  cout << "function [que_cir_init] test begin..." << endl;
  {
    printf("init CircularQueue[que] ...\n");
    ret = que_cir_init(&que);
    ASSERT(ret == OK);
    LOG_INFO("init SUCCESS!...\n");
  }
  PressEnter;

  cout << "function [que_cir_get_empty] test begin..." << endl;
  {
    if (TRUE == que_cir_get_empty(que)) {
      LOG_WARN("QUE is EMPTY!\n");
    } else {
      LOG_ERROR("QUE is NOT empty\n");
    }
  }
  PressEnter;

  cout << "function [que_cir_push_tail] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: insert [%d] from TAIL\n", 2 * i, i);
      ret = que_cir_push_tail(&que, 2 * i);
      ASSERT(OK == ret);
    }
  }
  PressEnter;

  cout << "function [que_cir_traverse] test begin..." << endl;
  {
    LOG_INFO("CircularQueue [que]'s element is: \n");
    visit vfunc = print_cir_que;
    ret = que_cir_traverse(que, vfunc);
    ASSERT(OK == ret);
    cout << endl;
  }
  PressEnter;

  cout << "function [que_cir_get_length] test begin..." << endl;
  {
    int length = que_cir_get_length(que);
    cout << "CircularQueue [que]'s length is: [" << length << "]" << endl;
  }
  PressEnter;

  cout << "function [get_top_stack_sq] test begin..." << endl;
  {
    elemType_que e = 0;
    ret = que_cir_get_head(que, &e);
    ASSERT(OK == ret);
    LOG_WARN("the elem in Head of que is: [%d]\n", e);
  }
  PressEnter;

  cout << "function [que_cir_pop_head] test begin..." << endl;
  {
    elemType_que e = 0;
    for (int i = 2; i > 0; i--) {
      ret = que_cir_pop_head(&que, &e);
      ASSERT(OK == ret);
      LOG_ERROR("pop elem [%d] from HEAD success!\n", e);
    }
  }
  PressEnter;

  cout << "function [que_cir_destroy] test begin..." << endl;
  {
    ret = que_cir_destroy(&que);
    ASSERT(OK == ret);
    LOG_WARN("destroy CircularQueue SUCCESS!..\n");
  }
  PressEnter;

}