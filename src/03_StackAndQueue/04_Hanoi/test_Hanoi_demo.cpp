#include "03_StackAndQueue/04_Hanoi/Hanoi.h"
#include "demo_func.h"
using namespace std;

void test_Hanoi_demo() {
  int scale = 0;
  cout << "pls input Hanoi's scale:";
  cin >> scale;

  sq_stack_t x = {0};
  sq_stack_t y = {0};
  sq_stack_t z = {0};
  init_stack_sq(&x);
  x.stack_name[0] = 'x';
  init_stack_sq(&y);
  y.stack_name[0] = 'y';
  init_stack_sq(&z);
  z.stack_name[0] = 'z';

  for (int i = scale; i > 0; --i) {
    push_stack_sq(&x, i);
  }

  hanoi(scale, &x, &y, &z);
  traverse_stack_sq(z);

  destroy_stack_sq(&x);
  destroy_stack_sq(&y);
  destroy_stack_sq(&z);

  return;
}