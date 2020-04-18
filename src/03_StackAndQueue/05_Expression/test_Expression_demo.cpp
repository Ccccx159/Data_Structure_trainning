#include "demo_func.h"
#include "03_StackAndQueue/05_Expression/Expression.h"
using namespace std;

void test_Expression_demo() {
  string src;
  cout << "plz Input the Expression:";
  cin >> src;

  int ret = OK;

  sq_stack_t suffix = {0};
  init_stack_sq(&suffix);

  // 将中缀表达式转换成后缀表达式
  ret = infixConvertSuffix(src, &suffix);
  traverse_stack_sq(suffix);
  cout << endl;
  
  // 借用栈计算表达式的值
  int val = 0;
  ret = calculateValue(&suffix, &val);

  cout << "expression's value is:[" << val << "]" << endl;

  destroy_stack_sq(&suffix);
  return;
}