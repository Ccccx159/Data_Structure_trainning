#ifndef _SCANF_PRIV_H_
#define _SCANF_PRIV_H_

#include "status.h"

Status bigger(int a, int b) { return a > b ? TRUE : FALSE; }
Status equal(int a, int b) { return a == b ? TRUE : FALSE; }
Status smaller(int a, int b) { return a < b ? TRUE : FALSE; }

int scanf_priv(FILE *fp, char *format, ...) {
  int *i = NULL;
  char *ch = NULL, *s = NULL;
  float *f = NULL;
  int cnt = 0, len = 0, tmp = 0, k = 0;

  va_list ap;  //通过va_list来获取可变参数列表
  va_start(ap, format);

  len = strlen(format);  // format为需要获取的对应数据类型

  for (cnt = 0, k = 2; k <= len; k += 2) {
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

/*****************************************************************************
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 参数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
 *
 * 注意:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
 ****************************************************************************/
int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,
                            int outSize) {
  assert(pOutput != NULL);
  assert(outSize >= 6);

  if (unic <= 0x0000007F) {
    // * U-00000000 - U-0000007F:  0xxxxxxx
    *pOutput = (unic & 0x7F);
    return 1;
  } else if (unic >= 0x00000080 && unic <= 0x000007FF) {
    // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
    *(pOutput + 1) = (unic & 0x3F) | 0x80;
    *pOutput = ((unic >> 6) & 0x1F) | 0xC0;
    return 2;
  } else if (unic >= 0x00000800 && unic <= 0x0000FFFF) {
    // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
    *(pOutput + 2) = (unic & 0x3F) | 0x80;
    *(pOutput + 1) = ((unic >> 6) & 0x3F) | 0x80;
    *pOutput = ((unic >> 12) & 0x0F) | 0xE0;
    return 3;
  } else if (unic >= 0x00010000 && unic <= 0x001FFFFF) {
    // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    *(pOutput + 3) = (unic & 0x3F) | 0x80;
    *(pOutput + 2) = ((unic >> 6) & 0x3F) | 0x80;
    *(pOutput + 1) = ((unic >> 12) & 0x3F) | 0x80;
    *pOutput = ((unic >> 18) & 0x07) | 0xF0;
    return 4;
  } else if (unic >= 0x00200000 && unic <= 0x03FFFFFF) {
    // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    *(pOutput + 4) = (unic & 0x3F) | 0x80;
    *(pOutput + 3) = ((unic >> 6) & 0x3F) | 0x80;
    *(pOutput + 2) = ((unic >> 12) & 0x3F) | 0x80;
    *(pOutput + 1) = ((unic >> 18) & 0x3F) | 0x80;
    *pOutput = ((unic >> 24) & 0x03) | 0xF8;
    return 5;
  } else if (unic >= 0x04000000 && unic <= 0x7FFFFFFF) {
    // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    // 10xxxxxx
    *(pOutput + 5) = (unic & 0x3F) | 0x80;
    *(pOutput + 4) = ((unic >> 6) & 0x3F) | 0x80;
    *(pOutput + 3) = ((unic >> 12) & 0x3F) | 0x80;
    *(pOutput + 2) = ((unic >> 18) & 0x3F) | 0x80;
    *(pOutput + 1) = ((unic >> 24) & 0x3F) | 0x80;
    *pOutput = ((unic >> 30) & 0x01) | 0xFC;
    return 6;
  }

  return 0;
}

#endif
