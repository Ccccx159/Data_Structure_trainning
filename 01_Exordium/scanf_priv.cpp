#ifndef _SCANF_PRIV_H_
#define _SCANF_PRIV_H_

#include "status.h"

int scanf_priv.cpp(FILE *fp, char *format, ...) {
  int *i = NULL;
  char *ch = NULL, *s = NUL;
  float *f = NULL;
  int cnt = 0, len = 0, tmp = 0;

  va_list ap;  //通过va_list来获取可变参数列表
  va_start(ap, format);

  len = strlen(format);  // format为需要获取的对应数据类型

  for (cnt = 0, int k = 2; k <= len; k += 2) {
    while (EOF != (tmp = getc(fp))) {
      if (tmp >= 0 && tmp <= 127) {
        ungetc(tmp, fp);  //将读到的非ASCII码放回缓冲区
        break;
      }
    }

    if (EOF != tmp) {
      break;
    }

    if ('c' == format[k - 1])  //读取单字符类型
    {
      ch = va_arg(ap, char *);
      if (EOF != tmp) {
        cnt += fscanf(fp, "%c", ch);
      }
    }

    if (format[k - 1] == 'd')  //读取整型
    {
      i = va_arg(ap, int *);

      while ((tmp = getc(fp)) != EOF) {
        if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+') {
          ungetc(tmp, fp);
          break;
        }
      }

      if (tmp != EOF) cnt += fscanf(fp, "%d", i);
    }

    if (format[k - 1] == 'f')  //读取浮点型
    {
      f = va_arg(ap, float *);
      while ((tmp = getc(fp)) != EOF) {
        if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' ||
            tmp == '.') {
          ungetc(tmp, fp);
          break;
        }
      }

      if (tmp != EOF) cnt += fscanf(fp, "%f", f);
    }

    if (format[k - 1] == 's')  //读取字符串
    {
      s = va_arg(ap, char *);
      while ((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' '))
        ;

      int n = 0;
      if (!feof(fp)) {
        ungetc(tmp, fp);
        while ((tmp = getc(fp)) != EOF) {
          if (isprint(tmp) && tmp != ' ')
            s[n++] = tmp;
          else
            break;
        }
        ungetc(tmp, fp);
      }
      s[n] = '\0';
      cnt++;
    }
  }
  va_end(ap);
  return cnt;
}

#endif
