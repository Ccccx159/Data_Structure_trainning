#include "Expression.cpp"
#include "demo_func.h"
using namespace std;

void print_exp(void* e) { cout << *((elemType_sq_stack*)e) << " "; }

void test_Expression_demo() {
  string src;
  cout << "plz Input the Expression:";
  cin >> src;

  int ret = OK;

  sq_stack_t suffix = {0};
  init_stack_sq(&suffix);

  // 将中缀表达式转换成后缀表达式
  ret = infixConvertSuffix(src, &suffix);
  visit vfunc = print_exp;
  traverse_stack_sq(suffix, print_exp);
  cout << endl;

  // 借用栈计算表达式的值
  int val = 0;
  ret = calculateValue(&suffix, &val);

  cout << "expression's value is:[" << val << "]" << endl;

  destroy_stack_sq(&suffix);
  return;
}