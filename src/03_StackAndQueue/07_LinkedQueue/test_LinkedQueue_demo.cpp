#include "03_StackAndQueue/07_LinkedQueue/LinkedQueue.h"
#include "demo_func.h"
using namespace std;

void print_linked_sq(void *e) { cout << *((elemType_que_lq *)e) << " "; }

void test_LinkedQueue_demo() {
  int ret = OK;
  linkedque_t que_l_sq = {0};

  cout << "function [linkedQue_init] test begin..." << endl;
  {
    printf("init linkedQue_init[que_l_sq] ...\n");
    ret = linkedQue_init(&que_l_sq);
    ASSERT(ret == OK);
    LOG_INFO("init SUCCESS!...\n");
  }
  PressEnter;

  cout << "function [linkedQue_get_empty] test begin..." << endl;
  {
    if (TRUE == linkedQue_get_empty(que_l_sq)) {
      LOG_WARN("QUE is EMPTY!\n");
    } else {
      LOG_ERROR("QUE is NOT empty\n");
    }
  }
  PressEnter;

  cout << "function [linkedQue_push_tail] test begin..." << endl;
  {
    for (int i = 1; i < 6; i++) {
      printf("for example: insert [%d] from TAIL\n", 2 * i, i);
      ret = linkedQue_push_tail(&que_l_sq, 2 * i);
      ASSERT(OK == ret);
    }
  }
  PressEnter;

  cout << "function [linkedQue_traverse] test begin..." << endl;
  {
    LOG_INFO("linkedQueueue [que]'s element is: \n");
    visit vfunc = print_linked_sq;
    ret = linkedQue_traverse(que_l_sq, vfunc);
    ASSERT(OK == ret);
    cout << endl;
  }
  PressEnter;

  cout << "function [linkedQue_get_length] test begin..." << endl;
  {
    int length = linkedQue_get_length(que_l_sq);
    cout << "LinkedQueue [que]'s length is: [" << length << "]" << endl;
  }
  PressEnter;

  cout << "function [linkedQue_get_head] test begin..." << endl;
  {
    elemType_que_lq e = 0;
    ret = linkedQue_get_head(que_l_sq, &e);
    ASSERT(OK == ret);
    LOG_WARN("the elem in Head of que is: [%d]\n", e);
  }
  PressEnter;

  cout << "function [que_cir_pop_head] test begin..." << endl;
  {
    elemType_que_lq e = 0;
    for (int i = 2; i > 0; i--) {
      ret = linkedQue_pop_head(&que_l_sq, &e);
      ASSERT(OK == ret);
      LOG_ERROR("pop elem [%d] from HEAD success!\n", e);
    }
  }
  PressEnter;

  cout << "function [linkedQue_destroy] test begin..." << endl;
  {
    ret = linkedQue_destroy(&que_l_sq);
    ASSERT(OK == ret);
    LOG_WARN("destroy CircularQueue SUCCESS!..\n");
  }
  PressEnter;
}