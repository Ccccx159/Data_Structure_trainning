#include "03_StackAndQueue/03_LineEditor/LineEditor.h"
#include "demo_func.h"
using namespace std;

void test_LineEditor_demo() {
  string src;
  cout << "plz input your line_text:";
  cin >> src;

  string dst;
  int ret = OK;

  LOG_WARN("now, your line_text is: %s\n", src.c_str());

  ret = lineEditor_sq_stack(dst, src);
  if (OK != ret) {
    LOG_ERROR("lineEditor process failed!...return [%d], plz debug to chk...\n",
              ret);
  }

  return;
}
