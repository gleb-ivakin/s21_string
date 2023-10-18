#include "s21_string.h"

int collectCHAR(struct flags *f, struct params *par, va_list input) {
    int isERR = 0;
    if (par->width == 0)
        par->width = 1;
    if (f->isSUPPRESS) {
        int n;
        s21_size_t sum = 0;
        if ((n = par->inr) < (int)par->width) {
            sum += n;
            par->width -= n;
            par->str += n;
        } else {
            sum += par->width;
            par->inr -= par->width;
            par->str += par->width;
        }
        par->nread += sum;
    } else {
        if (f->isLONG) {
            wchar_t *sp = va_arg(input, wchar_t*);
            for (s21_size_t i = 0; i < par->width; i++) {
                sp[i] = par->str[i];
            }
        } else {
            s21_memcpy(va_arg(input, char *), par->str, par->width);
        }
        par->inr -= par->width;
        par->str += par->width;
        par->nread += par->width;
        par->nassigned++;
    }
    par->nconversions++;
    return isERR;
}
void collectSTR(struct flags *f, struct params *par, va_list input) {
    int exit = 0;
    if (par->width == 0)
        par->width = (s21_size_t)~0;
    while (par->inr > 0 && isspace(*par->str))
        par->nread++, par->inr--, par->str++;
    if (f->isSUPPRESS) {
        int n = 0;
        while (!isspace(*par->str) && !exit) {
            n++, par->inr--, par->str++;
            if (par->inr <= 0)
                exit = 1;
        }
        par->nread += n;
    } else {
        char *p, *p0;
        p0 = p = va_arg(input, char *);
        while (!isspace(*par->str) && !exit) {
            par->inr--;
            *p++ = *par->str++;
            if (--par->width == 0)
                exit = 1;
            if (par->inr <= 0)
                exit = 1;
        }
        *p = 0;
        par->nread += p - p0;
        par->nassigned++;
    }
    par->nconversions++;
    return;
}
int collectINT(struct flags *f, struct params *par, va_list input) {
    int isERR = 0;
    int wasSIGN = 0;
    if (!par->base) {
        par->base = 10;
    }
    while (par->inr > 0 && isspace(*par->str))
        par->nread++, par->inr--, par->str++;
    while (par->inr > 0 && (*par->str == '-' || *par->str == '+')) {
        par->nread++, par->inr--, par->str++;
        wasSIGN++;
    }
    if (wasSIGN) {
        if (par->width)
            par->width++;
        else
            par->width = s21_strcspn(par->str, " \0")+1;
        if (wasSIGN > 1) {
            f->isALLERR = 1;
        }
        par->nread--; par->inr++;
        par->str--;
    }
    s21_size_t tmpWIDTH = s21_strcspn(par->str, " \f\n\r\t\v\0");
    s21_memset(par->buf, '\0', MAXDIGLEN);
    if (par->width > tmpWIDTH) {
        par->width = tmpWIDTH;
    }
    if (par->width) {
        s21_strncpy(par->buf, par->str, par->width);
    } else {
        s21_strncpy(par->buf, par->str, tmpWIDTH);
    }
    char * t = (char *)par->buf;
    if (s21_strpbrk(par->buf, "ABCDEFabcdefxX")) {
        if (s21_strlen(par->buf) > 2) {
            int i = 0;
            if (*par->buf == '-') {
                i = 1;
            }
            if (par->buf[i] == '0' && par->buf[i+1] == 'x') {
                if (!f->isDEC) par->base = 16;
            }
        }
    } else if (*par->buf == '-' || *par->buf == '+') {
        if (*(par->buf+1) == '0')
            if (!f->isPOINT)
                par->base = 8;
    } else if (*par->buf == '0') {
            if (!f->isPOINT)
                par->base = 8;
    }
    int countBeforeRead = s21_strlen(par->buf);
    if ((f->isSUPPRESS) == 0) {
        long long int res;
        if (!f->isALLERR) {
            if ((f->isUnsigned) == 0) {
                res = strtoll(par->buf, &t, par->base);
                if (t == par->buf) isERR = 1;
            } else {
                res = strtoull(par->buf, &t, par->base);
                if (t == par->buf) isERR = 1;
            }
        } else {
            res = 0;
            isERR = 1;
        }
        if (f->isPOINT)
            *va_arg(input, void **) =
                (void *)(s21_size_t)res;
        else if (f->isSS)
            *va_arg(input, char *) = res;
        else if (f->isSHORT)
            *va_arg(input, short *) = res;
        else if (f->isLONG)
            *va_arg(input, long *) = res;
        else if (f->isLL)
            *va_arg(input, long long *) = res;
        else
            *va_arg(input, int *) = res;
        if (!isERR) {
            par->nassigned++;
            par->nconversions++;
        }
        par->width = (countBeforeRead - s21_strlen(t));
    }  else {
        par->width = countBeforeRead;
    }
    par->inr -= par->width;
    par->nread += par->width;
    par->str += par->width;
    return isERR;
}
int collectFLOAT(struct flags *f, struct params *par, va_list input) {
    int isERR = 0;
    while (par->inr > 0 && isspace(*par->str))
        par->nread++, par->inr--, par->str++;
    s21_size_t tmpWIDTH = s21_strcspn(par->str, " \f\n\r\t\v\0");
    s21_memset(par->buf, '\0', MAXDIGLEN);
    if (par->width > tmpWIDTH) {
        par->width = tmpWIDTH;
    }
    if (par->width) {
        s21_strncpy(par->buf, par->str, par->width);
    } else {
        s21_strncpy(par->buf, par->str, tmpWIDTH);
    }
    char * t = (char *)par->buf;
    if ((f->isSUPPRESS) == 0) {
        if (f->isLONGDBL) {
            long double res = strtold(par->buf, &t);
            if (t == par->buf) isERR = 1;
            *va_arg(input, long double *) = res;
        } else if (f->isLONG) {
            double res = strtod(par->buf, &t);
            if (t == par->buf) isERR = 1;
            *va_arg(input, double *) = res;
        } else {
            float res = strtof(par->buf, &t);
            if (t == par->buf) isERR = 1;
            *va_arg(input, float *) = res;
        }
        if (!isERR) par->nassigned++;
    }
    par->width = s21_strlen(par->buf);
    par->nread += par->width;
    par->inr -= par->width;
    par->str += par->width;
    par->nconversions++;
    return isERR;
}
int s21_sscanf(const char * str, const char * format, ...) {
    struct params par;
    struct flags f;
    par.inr = s21_strlen(str);
    par.fmt = (const char *)format;
    par.str = (const char *)str;
    par.nassigned = 0;
    par.nconversions = 0;
    par.nread = 0;
    par.base = 0;
    f.isALLERR = 0;
    va_list(input);
    va_start(input, format);
    int exitStatus = 0;
    int isNewInput = 1;
    for (; !exitStatus ;) {
        int c = *par.fmt++;
        if (isNewInput) {
            if (isspace(c)) {
                while (par.inr > 0 && isspace(*par.str))
                    par.nread++, par.inr--, par.str++;
                continue;
            }
            if (c != '%') {
                if (par.inr <= 0) {
                    f.isERR = 1; exitStatus = 1;
                }
                if (*par.str != c) {
                    f.isERR = 2; exitStatus = 1;
                }
                par.inr--, par.str++;
                par.nread++;
                continue;
            }
            par.width = 0;
            c = *par.fmt++;
            f.isDEC = 0; f.isERR = 0; f.isEXP = 0; f.isHEX = 0; f.isLL = 0;
            f.isLONG = 0; f.isPERC = 0; f.isLONGDBL = 0;
            f.isPOINT = 0; f.isSHORT = 0; f.isSIGN = 0; f.isSKIP = 0;
            f.isSS = 0; f.isSUPPRESS = 0; f.isUnsigned = 0;
        }
        switch (c) {
        case '%':
            if (*par.str != c) {
                f.isERR = 2; exitStatus = 1;
            }
            par.inr--, par.str++;
            par.nread++;
            isNewInput = 1;
            continue;
        case '*':
            f.isSUPPRESS = 1;
            isNewInput = 0;
            continue;
        case 'l':
            if (f.isLONG) {
                f.isLONG = 0;
                f.isLL = 1;
            } else {
                f.isLONG = 1;
            }
            isNewInput = 0;
            continue;
        case 'L':
            f.isLONGDBL = 1;
            isNewInput = 0;
            continue;
        case 'h':
            if (f.isSHORT) {
                f.isSHORT = 0;
                f.isSS = 1;
            } else {
                f.isSHORT = 1;
            }
            isNewInput = 0;
            continue;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            par.width = par.width * 10 + c - '0';
            isNewInput = 0;
            continue;
        case 'd':
            par.base = 10;
            f.isDEC = 1;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'i':
            par.base = 0;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'o':
            f.isUnsigned = 1;
            par.base = 8;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'u':
            par.base = 10;
            f.isUnsigned = 1;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'X':
        case 'x':
            f.isHEX = 1;
            f.isUnsigned = 1;
            par.base = 16;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'A': case 'E': case 'F': case 'G':
        case 'a': case 'e': case 'f': case 'g':
            f.isERR = collectFLOAT(&f, &par, input);
            isNewInput = 1;
            break;
        case 's':
            collectSTR(&f, &par, input);
            isNewInput = 1;
            break;
        case 'c':
            f.isERR = collectCHAR(&f, &par, input);
            isNewInput = 1;
            break;
        case 'p':
            f.isPOINT = 1;
            f.isHEX = 1;
            f.isUnsigned = 1;
            par.base = 16;
            f.isERR = collectINT(&f, &par, input);
            isNewInput = 1;
            break;
        case 'n':
            par.nconversions++;
            *va_arg(input, int *) = par.nread;
            continue;
        }
    }
    if (f.isERR != 2) {
        return (par.nconversions != 0 ? par.nassigned : -1);
    } else {
        return par.nassigned;
    }
}

/**
 *Определяет количество чаров, необходимых для записи числа
 */
int int_len(long long int n) {
  int len = 0;
  if (n < 0) n = n *(-1);
  if (n != 0) {
    for (; n > 0; len++) {
      n /= 10;
    }
  } else {
    len = 1;
  }
  return len;
}
/**
 *Убирает незначащие нули с правой стороны числа, которые после запятой
 */
int trim_int(long double trim_val, int accur) {
  if (accur == -1) accur = 6;
  char arr[500] = {
    0
  };
  for (int i = 0; i < accur; i++) {
    trim_val *= 10;
    arr[i] = (int) round(trim_val) % 10 + '0';
    trim_val = trim_val - (long long int) trim_val;
  }

  int ret = accur;
  for (; arr[ret - 1] == '0' && ret > 0; ret--) {}

  return ret;
}

char *s21_wcharcat(char *dest,
  wchar_t *src) {
  s21_size_t size = s21_strlen(dest);
  s21_size_t i;
  for (i = 0; src[i]; i++) {
    dest[i + size] = src[i];
  }
  dest[i + size] = '\0';
  return dest;
}

/**
 *Переводит строку в строку с форматированием
 */
void str_to_str(char *buffer,
  char
  const *val, int flag, int width, int accur) {
  if (width == -1 && accur == -1) {
    s21_strcpy(buffer, val);
  } else {
    if (accur == -1) accur = (int) s21_strlen(val);
    if ((int) s21_strlen(val) < accur) accur = (int) s21_strlen(val);
    if (flag % 2 == 0) {  // флаг '-'
      int i = 0;
      for (int j = 0; j < accur; j++) {
        buffer[i] = val[j];
        i++;
      }
      for (; i < width; i++)
        buffer[i] = ' ';
    } else {
      int i;
      for (i = 0; i < width - accur; i++)
        buffer[i] = ' ';
      for (int j = 0; j < accur; j++) {
        buffer[i] = val[j];
        i++;
      }
    }
  }
}

/**
 *Переводит целое число в строку
 */
void int_to_str(char *buffer, long long int val, int flag, int width, int accur, char specifier) {
  if (val == 0 && accur == 0) {
    buffer[0] = '\0';
  } else {
    int tag = 0;  // дополнительный параметр,
  // отвечающий за наличие дополнительного символа
  // перед числом('-', '+', ' ')
    int len = int_len(val);
    int minus = 0;  // дополнительный параметр, отвечающий за выравнивание по левому краю
    if (flag % 2 == 0) {
      minus = width;
      width = -1;
    }
    int count = 0;
    if (val < 0 || accur == -2) {  // accur = -2 используется в f если целая
  // часть равна нулю, для определения знака
      buffer[0] = '-';
      val *= -1;
      count++;
      len++;
      tag++;
    } else {
      if (flag % 3 == 0) {  // флаг '+'
        buffer[0] = '+';
        count++;
        len++;
        tag++;
      } else if (flag % 5 == 0 && specifier != 'u') {  // флаг ' '
        buffer[0] = ' ';
        count++;
        len++;
        tag++;
      }
    }
    for (int i = len - 1; i >= count; i--) {
      buffer[i] = val % 10 + '0';
      val /= 10;
    }

    if (accur != -1) {
      char c = buffer[0];
      if (tag != 0) {
        len--;
        buffer[0] = '0';
      }
      for (int i = accur - len; i > 0; i--) {
        for (int j = len; j >= 0; j--) {
          buffer[j + 1] = buffer[j];
        }
        buffer[0] = '0';
        len++;
      }
      if (tag != 0) {
        buffer[0] = c;
        len++;
      }
    }
    if (width >= 0) {
      char c = '*';
      if ((flag % 3 == 0 || flag % 5 == 0 || accur == -2) && flag % 7 == 0) {
        c = buffer[0];
        buffer[0] = '0';
      }
      char fill = flag % 7 ? ' ' : '0';
      for (int i = width - len; i > 0; i--) {
        for (int j = len; j >= 0; j--) {
          buffer[j + 1] = buffer[j];
        }
        buffer[0] = fill;
        len++;
      }
      if (c != '*') buffer[0] = c;
    }
    if (flag % 2 == 0) {  // Выравнивание по левому краю в пределах заданной ширины поля
      for (int i = minus - len; i > 0; i--) {
        buffer[len] = ' ';
        len++;
      }
    }

    buffer[len] = '\0';
  }
}

int double_to_str(char *buffer, long double val, int flag, int width, int accur, char specifier) {
  if (accur == -1) accur = 6;
  s21_strcpy(buffer, "");
  int minus = 0, nul = 1;
  // minus - дополнительный параметр, отвечающий за
  // выравнивание по левому краю, t - количество значимых
  // символов после запятой, nul - если точность = 0, нам не нужно
  // резервировать символ на точку
  // если не указана точность,
  // поумолчанию выводится 6 символов после запятой(точки)

  if (flag % 2 == 0) minus = width + 1;  // выравнивание по левому краю
  // если есть флаги '+' или ' '

  // считаем множитель е
  int count_e = 0;
  if (s21_strchr("eEbB", specifier)) {
    for (;
      (fabsl(val) >= 10 || fabsl(val) < 1) && fabsl(val) != 0;) {
      if (fabsl(val) > 0 && fabsl(val) < 1) {
        val *= 10;
        count_e--;
      } else if (fabsl(val) >= 10) {
        val /= 10;
        count_e++;
      }
    }
    if (int_len(count_e) == 3) width -= 5;
    else
      width -= 4;  // 4 символа на е-00
  }
  int neg = -1;
  int int_lenght = 0;  // если есть флаг '#' то из точности нужно вычесть количество символов целой части
  if (val < 0) neg = -2;
  if (accur == 0) {
    if (flag % 11 == 0) nul = 1;
    else
        nul = 0;

    if ((int) val == 0) {
      if ((int)(val *10) != 0) {
        accur = 1;
      } else if ((int)(val *100) != 0) {
        accur = 2;
      } else if ((int)(val *1000) != 0) {
        accur = 3;
      } else if ((int)(val *10000) != 0) {
        accur = 4;
      }
    }
    int_to_str(buffer, (double) round(val), flag, width - accur - nul - minus, neg, specifier);
  } else {
    int_to_str(buffer, (double)(val), flag, width - accur - nul - minus, neg, specifier);
  }

  if (flag % 11 == 0 && (specifier == 'b' || specifier == 'B')) int_lenght = 1;
  if (flag % 11 == 0 && specifier == 'a') int_lenght = int_len((long long int)(val));
  // для всего что до точки вызываем инт_то_стринг, учитывая все предыдущие параметры -1 это для точки

  int count = s21_strlen(buffer);
  char c = buffer[0];
  if (accur != 0 || specifier == 'a') {  // если нет .0
    long double trim_val = val - (long long int) val;
    if (trim_val < 0) trim_val *= -1;
    int t = trim_int(trim_val, accur - int_lenght);

    if (!s21_strchr("abB", specifier) || t > 0) {  // сюда заходим если используется 'g'
      buffer[count] = '.';
      count++;
    }

    if (val < 0) {
      val = val *(-1);
    }

    val = val - (long long int) val;
  // берм количество символов, которое мы уже записали в строку
    for (int i = 0; i < t - 1; i++) {  // печатаем все значимые
  // символы после запятой(точки)

      val *= 10.;  // число 0.х умножаем на 10 чтобы получить х
      buffer[count] = (int) fmod(val, 10) + '0';

      val = val - (int) val;
      accur--;
      count++;
    }

    val *= 10.;  // для последнего числа используется округдение по правилам математики
    if (s21_strchr(buffer, '.')) {
      val *= 10;
      if ((int) val % 10 > 4) buffer[count] = ((int) val / 10 + 1) % 10 + '0';
      else
          buffer[count] = (int)(val / 10) % 10 + '0';
      accur--;
      count++;
    }

    for (int i = 0; i < accur - int_lenght; i++) {  // печатаем нули т.к. значимых символов больше нет
      if (s21_strchr("abB", specifier)) {
        if (flag % 11 == 0) {
          buffer[count] = '0';
          count++;
        }
      } else {
        buffer[count] = '0';
        count++;
      }
    }
    buffer[0] = c;
  } else {
    if (flag % 11 == 0) {
      buffer[count] = '.';
      count++;
    }
  }

  if (s21_strchr("eEbB", specifier)) {  // сюда заходим при e и g
    if (specifier == 'E' || specifier == 'B') buffer[count] = 'E';
    else
      buffer[count] = 'e';
    count++;
    if (count_e < 0) {
      buffer[count] = '-';
    } else {
      buffer[count] = '+';
    }
    count++;
    if (abs(count_e) < 10) {
      buffer[count] = '0';
      count++;
      buffer[count] = abs(count_e) + '0';
      count++;
    } else if (abs(count_e) < 100) {
      buffer[count] = abs(count_e) / 10 + '0';
      count++;
      buffer[count] = abs(count_e) % 10 + '0';
      count++;
    } else {
      buffer[count] = abs(count_e) / 100 + '0';
      count++;
      buffer[count] = (abs(count_e) / 10) % 10 + '0';
      count++;
      buffer[count] = abs(count_e) % 10 + '0';
      count++;
      width++;
    }
    width += 4;
  }
  buffer[count] = '\0';
  char fill = flag % 7 ? ' ' : '0';  // то чем будем заполнять пустоту,
  // поумолчанию пробелами, если флаг '0', то нулями
  if (flag % 2 == 0) {  // если используется флаг '-' печатаем пробелы
    for (int i = width - count; i > 0; i--) {
      buffer[count] = ' ';
      count++;
    }
  } else if (s21_strchr("abB", specifier)) {
    if ((neg == -2 || flag % 3 == 0 || flag % 5 == 0) && (flag % 7 == 0)) {
      buffer[0] = fill;
    }

    for (int i = count; count < width; i++) {
      for (int j = i - 1; j >= 0; j--) {
        buffer[j + 1] = buffer[j];
      }
      buffer[0] = fill;
      count++;
    }
    buffer[0] = c;
  }

  buffer[count] = '\0';

  int ret;
  if (specifier == 'e' || specifier == 'E') {
    ret = count_e;
  } else {
    ret = -1;
  }
  return ret;
}
/**
 *Подготавливает функцию при использовании g,  вычисляет что будет короче математическая нотация или запись
 *с плавающей точкой, меняет значение точности поумолчанию с 6 до 4
 */
void g_to_str(char *buffer, long double val, int flag, int width, int accur, char specifier) {
  int hash = 0;
  int tmp_accur = accur == -1 ? 7 : accur;
  if (flag % 11 == 0) hash = 1;
  int st = double_to_str(buffer, val, flag, width, accur, specifier == 'g' ? 'e' : 'E');
  if (accur == -1) {
    accur = 6;
  } else if (accur == 0) {
    accur = 1;
  }
  if (accur > st && st >= -4) {
    accur -= (st + 1);
    specifier = 'a';
  } else {
    accur -= 1;
    specifier = specifier == 'g' ? 'b' : 'B';
  }
  if (hash || tmp_accur == 0) accur = tmp_accur;
  double_to_str(buffer, val, flag, width, accur, specifier);
}
/**
 *Переводит запись в 8(o) или 16(xX) ричную систему, также используется при p
 */
void oct_hex_to_str(char *buffer, unsigned long int val, int flag, int width, int accur, char specifier) {
  s21_strcpy(buffer, "");

  int val_n = 1;
  if (val == 0) val_n = 0;
  char *temp_str = (char *) calloc((width + accur + 50), sizeof(char));

  int n = specifier == 'o' ? 8 : 16;  // если о то 8, в остальных случаях 16
  int temp_count = 0;

  if (val == 0) {
    temp_str[0] = '0';
    temp_count++;
  } else {
    for (; val != 0; val /= n, temp_count++) {
      if (n == 16) {
        switch (val % n) {
        case 10: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'a' : 'A';
          break;
        }
        case 11: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'b' : 'B';
          break;
        }
        case 12: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'c' : 'C';
          break;
        }
        case 13: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'd' : 'D';
          break;
        }
        case 14: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'e' : 'E';
          break;
        }
        case 15: {
          temp_str[temp_count] = specifier == 'x' || specifier == 'p' ? 'f' : 'F';
          break;
        }
        default: {
          temp_str[temp_count] = (val % n) + '0';
          break;
        }
        }
      } else {
        temp_str[temp_count] = (val % n) + '0';
      }
    }
  }
  temp_str[temp_count] = '\0';
  // запись в temp_str сделана задом наперед
  int count = 0;
  char empty = ' ';

  if (specifier == 'p') {
    s21_strcat(temp_str, "x0");
    temp_count += 2;
  }

  int size = temp_count > accur ? temp_count : accur;

  int hash = 0;
  if (flag % 11 == 0) {
    if (specifier == 'o') hash = 1;
  }
  if ((int) s21_strlen(temp_str) < accur) {
    for (; temp_count < accur - hash; temp_count++) {
      temp_str[temp_count] = '0';
    }
    temp_str[temp_count] = '\0';
  }

  if ((flag % 11 == 0)) {
    switch (specifier) {
    case 'o': {
      if (val_n) {
        s21_strcat(temp_str, "0");
        temp_count += 1;
        hash = 1;
      }
      break;
    }
    case 'x': {
      if (val_n) {
        s21_strcat(temp_str, "x0");
        temp_count += 2;
        hash = 2;
      }
      break;
    }
    case 'X': {
      if (val_n) {
        s21_strcat(temp_str, "X0");
        temp_count += 2;
        hash = 2;
      }
      break;
    }
    default:
      hash = 0;
      break;
    }
  }

  if (width > size && !(flag % 2 == 0)) {
    for (int j = 0; j < width - size - hash; j++) {
      buffer[count] = empty;
      count++;
    }
  }

  for (temp_count -= 1; temp_count >= 0; temp_count--) {
    buffer[count] = temp_str[temp_count];
    count++;
  }
  if (width > size && flag % 2 == 0) {
    for (int i = 0; i < width - size - hash; i++) {
      buffer[count] = empty;
      count++;
    }
    buffer[count] = '\0';
  }
  free(temp_str);
}

/**
 *Разбиваем на подстроку, которая начинается на % и заканчивается одним из значимых символов "cdieEfgGosuxXpn%"
 */
void parcer(int *flag, int *width, int *accur, int *lenght, char *specifier, int *strlen,
  const char *tmp) {
  int i, sw = 0, fsw = 0;  // sw - отвечает за переключение
  // значений от ширины к точности, fsw - отвечает за конец
  // чтения флагов (-, +, ' ', 0, #)
  for (i = 0; !s21_strchr("cdieEfgGosuxXpn%", tmp[i]); i++) {
    if (s21_strchr("-+ 0#", tmp[i]) && fsw == 0) {
      if (*flag == -1) *flag = 1;
      if (tmp[i] == '-') *flag *= 2;
      if (tmp[i] == '+') *flag *= 3;
      if (tmp[i] == ' ') *flag *= 5;
      if (tmp[i] == '0') *flag *= 7;
      if (tmp[i] == '#') {
        *flag *= 11;
      }
      *flag %= 2310;  // чтобы предотвратить переполнение
  // берем по модулю от максимального частного
    } else {
      fsw = 1;
      if (tmp[i] == '*') {
        if (sw == 0) *width = -2;
        else
          *accur = -2;
      } else if (s21_strchr("1234567890", tmp[i])) {
        if (sw == 0) {
          if (*width == -1) {
            *width = 0;
          }
          *width = *width *10 + tmp[i] - '0';
        } else {
          *accur = *accur *10 + tmp[i] - '0';
        }
      } else if (tmp[i] == '.') {
        sw++;
        *accur = 0;
      } else if (s21_strchr("hlL", tmp[i])) {
        if (tmp[i] == 'h') {
          *lenght = 0;
        } else if (tmp[i] == 'l') {
          if (*lenght == 1) *lenght = 3;
          else
            *lenght = 1;
        } else {
          *lenght = 2;
        }
      }
    }
  }
  *strlen = i + 1;
  *specifier = tmp[i];
}

int s21_sprintf(char *str,
  const char *format, ...) {
  va_list(input);
  va_start(input, format);  // инициализация вараргов
  int count = 0;
  for (int i = 0; format[i]; i++) {
    if (format[i] == '%') {  // дошли до % обуляем все параметры и запускаем парсер
      int flag = -1, width = -1, accur = -1, lenght = -1, strlen = -1;
      char specifier = ' ';
      const char *tmp = format + i + 1;  // временная подстрока, которая начинается с символа следующим за %
      parcer(& flag, & width, & accur, & lenght, & specifier, & strlen, tmp);
      if (width == -2) width = (int) va_arg(input, int);  // если были использованы '*'
      if (accur == -2) accur = (int) va_arg(input, int);
      char *buffer = (char *) calloc((width + accur + 50), sizeof(char));
      s21_strcpy(buffer, "");  // создаем массив под фотматирование строки
      if (s21_strchr("di", specifier)) {  // знаковое десятичное число
        str[count] = '\0';
        if (lenght == 3) {
          long long int val = (long long int) va_arg(input, long long int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else if (lenght == 1) {
          long int val = (long int) va_arg(input, long int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else if (lenght == 0) {
          short val = (short) va_arg(input, int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else {
          int val = (int) va_arg(input, int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        }
      } else if (specifier == 'c') {  // символ
        str[count] = '\0';
        char val;
        if (lenght == 1) {
          val = (char) va_arg(input, wchar_t);
        } else {
          val = (char) va_arg(input, int);
        }
        if (width == -1) {
          str[count] = val;
          count++;
        } else {
          int tmp_c = count;
          for (int j = 0; j < width; j++) {
            str[count] = ' ';
            count++;
          }
          if (flag % 2 == 0) str[tmp_c] = val;
          else
            str[count - 1] = val;
        }
      } else if (s21_strchr("feE", specifier)) {  // десятичное число с плавающей
  // точкой или научная нотация (мантисса/экспонента)
        str[count] = '\0';
        long double val;
        if (lenght == 2) {
          val = (long double) va_arg(input, long double);
        } else {
          val = (long double) va_arg(input, double);
        }
        double_to_str(buffer, val, flag, width, accur, specifier);
      } else if (s21_strchr("gG", specifier)) {  // укороченная запись
        str[count] = '\0';
        long double val;
        if (lenght == 2) {
          val = (long double) va_arg(input, long double);
        } else {
          val = va_arg(input, double);
        }
        g_to_str(buffer, val, flag, width, accur, specifier);
      } else if (specifier == 's') {  // строка
        char val[10000]="";
        if (lenght == 1) {
          wchar_t *tmpc = (wchar_t *) va_arg(input, wchar_t *);
          s21_wcharcat(val, tmpc);
        } else {
          char *tmpc = (char *) va_arg(input, char *);
    s21_strcat(val, tmpc);
        }
        char *buffer_s = (char *) calloc((accur + width + (int) s21_strlen(val) + 40), sizeof(char));
        str_to_str(buffer_s, val, flag, width, accur);
        str[count] = '\0';
        s21_strcat(str, buffer_s);
        count += s21_strlen(buffer_s);
        free(buffer_s);
      } else if (specifier == 'u') {  // беззнаковое десятичное число
        if (lenght == 3) {
          unsigned long long int val = va_arg(input, unsigned long long int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else if (lenght == 1) {
          unsigned long int val = va_arg(input, unsigned long int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else if (lenght == 0) {
          unsigned short val = (unsigned short) va_arg(input, unsigned int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        } else {
          unsigned int val = va_arg(input, unsigned int);
          int_to_str(buffer, val, flag, width, accur, specifier);
        }

      } else if (specifier == '%') {  // процент
        str[count] = '%';
        count++;
      } else if (specifier == 'n') {  // передаем число уже напечатанных символов
        int *d = va_arg(input, int *);

        *d = count;
      } else if (s21_strchr("xXop", specifier)) {  // 8 или 16 или указатель
        unsigned long int val;
        if (lenght == 1 || specifier == 'p') {
          val = (unsigned long int) va_arg(input, unsigned long int);
        } else {
          val = va_arg(input, unsigned int);
        }

        oct_hex_to_str(buffer, val, flag, width, accur, specifier);
      }

      str[count] = '\0';  // если нам дали не пустую строку,
  // задаем символ конца строки для конкотенации
      s21_strcat(str, buffer);
      count += s21_strlen(buffer);
      free(buffer);
      i += strlen;
    } else {  // все остальное переписываем сразу в выходную строку
      str[count] = format[i];
      count++;
    }
  }
  str[count] = '\0';
  va_end(input);
  return count;
}

// memchr – поиск первого вхождения указанного символа в массиве.
void* s21_memchr(const void* str, int c, s21_size_t n) {
    unsigned char* ret = s21_NULL;
    unsigned char* temp = (unsigned char*) str;

    for (; n && ret == s21_NULL; temp++, n--)
        if (*temp == c)
            ret = temp;

    return ret;
}

// memcmp – сравнение массивов.
int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
    const unsigned char *p1 = str1;
    const unsigned char *p2 = str2;
    int res = 0;
    for (s21_size_t i = 0; i < n && res == 0; i++) {
        if (p1[i] != p2[i]) {
            res = p1[i] - p2[i];
        }
    }
    return res;
}

// memcpy – копирование непересекающихся массивов.
void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
    unsigned char* p_dest = (unsigned char*) dest;
    const unsigned char* p_src = (const unsigned char*) src;

    for (; n; n--)
        *p_dest++ = *p_src++;

    return dest;
}

// memmove – копирование массивов (в том числе пересекающихся).
void* s21_memmove(void* dest, const void* src, s21_size_t n) {
    unsigned char* p_dest = (unsigned char*) dest;
    const unsigned char* p_src = (const unsigned char*) src;
    unsigned char* temp = malloc(sizeof(unsigned char) * n);

    s21_size_t i;
    for (i = 0; i < n; i++)
        temp[i] = p_src[i];
    for (i = 0; i < n; i++)
        p_dest[i] = temp[i];

    free(temp);

    return dest;
}

// memset – заполнения массива указанными символами.
void* s21_memset(void* str, int c, s21_size_t n) {
    unsigned char* p_str = (unsigned char*) str;
    for (; n; n--)
        *p_str++ = c;

    return str;
}

// strcat – объединение строк.
char* s21_strcat(char* dest, const char* src) {
    char* res = dest;
    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';

    return res;
}

// strncat – объединение строк c ограничением длины добавляемой строки.
char* s21_strncat(char* dest, const char* src, s21_size_t n) {
    char* res = dest;
    while (*dest)
        dest++;
    for (; n; n--)
        *dest++ = *src++;
    *dest = '\0';

    return res;
}

// strchr – поиск первого вхождения символа в строку.
char* s21_strchr(const char* str, int c) {
    char* ret = s21_NULL;
    int no_return = 1;
    for (; *str && no_return; str++)
        if (*str == c) {
            ret = (char*)str;
            no_return = 0;
        } else if (*(str+1) == c) {
            ret = (char*)str+1;
            no_return = 0;
        }

    return ret;
}

// strcmp – сравнение строк.
int s21_strcmp(const char* str1, const char* str2) {
    for (; *str1 && (*str1 == *str2); str1++, str2++) {}

    return (*str1 - *str2);
}

// strncmp – сравнение строк с ограничением количества сравниваемых символов.
int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
    for (; n > 1 && *str1 && (*str1 == *str2); n--, str1++, str2++) {}

    return (n < 1) ? 0 : (*str1 - *str2);
}

// strcpy – копирование строк.
char* s21_strcpy(char* dest, const char* src) {
    char* res = dest;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';

    return res;
}

// strncpy – копирование строк c ограничением длины.
char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
    char* res = dest;
    for (; n; n--) {
      if (*src == '\0')
          *dest++ = '\0';
      else
          *dest++ = *src++;
    }
    return res;
}

// strcspn – определение длины участка строки, не содержащего указанные символы.
s21_size_t s21_strcspn(const char* str, const char* sym) {
    s21_size_t count = 0;
    int no_return = 1;
    char* sym_copy = (char*)sym;

    for (; *str && no_return; str++) {
        for (sym = sym_copy; *sym; sym++)
            if (*str == *sym)
                no_return = 0;
        if (no_return)
            count++;
    }

    return count;
}

// strerror – формирование сообщения об ошибке по коду ошибки.
char* s21_strerror(int num) {
    char* errors[ERR_AMOUNT] = ERROR_LIST;
    static char returned_str[100] = {0};
    if (num >= 0 && num < ERR_AMOUNT)
        s21_strcpy(returned_str, errors[num]);
    else
    #if defined(__APPLE__)
        s21_sprintf(returned_str, ERRORMSG, num);
    #elif defined(__linux) || defined(__linux__)
        s21_sprintf(returned_str, ERRORMSG);
    #endif
    return returned_str;
}

// strlen – определение длины строки.
s21_size_t s21_strlen(const char* str) {
    s21_size_t len = 0;
    for (; *str != '\0'; str++)
        len++;

    return len;
}

// strpbrk – поиск первого вхождения в строку символа из указанного множества.
char* s21_strpbrk(const char* str, const char* sym) {
    int no_return = 1;
    for (; *str != '\0' && no_return; str++) {
        char *sym_copy = (char*)sym;
        for (; *sym_copy != '\0'; sym_copy++) {
            if (*sym_copy == *str) {
                no_return = 0;
                str--;
            }
        }
    }

    return no_return ? s21_NULL : (char*)str;
}

// strrchr – поиск последнего вхождения символа в строку.
char* s21_strrchr(const char* str, int c) {
    char * ret = s21_NULL;
    for (int i = s21_strlen(str); i >= 0; i--)
        if (str[i] == c) {
            ret = (char *)str + i;
            break;
        }
    return ret;
}

// strspn – определение максимальной длины участка строки, содержащего только указанные символы.
s21_size_t s21_strspn(const char* str, const char* sym) {
    s21_size_t count = 0;
    int no_return = 1;
    char* sym_copy = (char*)sym;

    for (; *str && no_return; str++) {
        int no_break = 1;

        for (sym = sym_copy; *sym && no_break; sym++)
            if (*str == *sym) {
                no_break = 0;
                sym--;
            }

        if (*sym == '\0')
            no_return = 0;
        else
            count++;
    }

    return count;
}

// strstr – поиск первого вхождения строки А в строку В.
char* s21_strstr(const char* str1, const char* str2) {
    char* res = s21_NULL;

    for (int i = 0; (i < (int)s21_strlen(str1) - (int)s21_strlen(str2) + 1) && (res == s21_NULL); i++) {
        s21_size_t k = 0;
        for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
            if (str1[i + j] == str2[j])
                k++;
        }
        if (k == s21_strlen(str2))
            res = (char*)str1 + i;
    }

    return res;
}

// strtok – разбиение строки на части по указанному разделителю.
char* s21_strtok(char* str, const char* sep) {
    static char *oldstr;
    char *entry;

    if (oldstr == s21_NULL && str == s21_NULL) {
        entry = s21_NULL;
    } else {
        if (str == s21_NULL)
            str = oldstr;

        int count = s21_strspn(str, sep);

        str += count;
        if (*str == '\0') {
            oldstr = str;
            entry = s21_NULL;
        } else if (count == 0 && s21_strpbrk(str, sep) == s21_NULL) {
            oldstr = "\0";
            entry = str;
        } else {
            entry = str;
            str = s21_strpbrk(str, sep);
            if (str != s21_NULL) {
                *str = '\0';
                oldstr = str + 1;
            } else {
                oldstr = s21_NULL;
            }
        }
    }

    return entry;
}

// to_upper - возвращает копию строки, преобразованной в верхний регистр.
void* s21_to_upper(const char* str) {
    char* temp;

    if (str == s21_NULL) {
        temp = s21_NULL;
    } else {
        s21_size_t i;
        temp = malloc(sizeof(char) * (s21_strlen(str)+1));
        for (i = 0; str[i]; i++) {
            if (str[i] >= 'a' && str[i] <= 'z')
                temp[i] = str[i] - 32;
            else
                temp[i] = str[i];
        }
        temp[i] = '\0';
    }


    return temp;
}

// to_lower - возвращает копию строки, преобразованной в нижний регистр.
void* s21_to_lower(const char* str) {
    char* temp;

    if (str == s21_NULL) {
        temp = s21_NULL;
    } else {
        s21_size_t i;
        temp = malloc(sizeof(char) * (s21_strlen(str)+1));
        for (i = 0; str[i]; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z')
                temp[i] = str[i] + 32;
            else
                temp[i] = str[i];
        }
        temp[i] = '\0';
    }

    return temp;
}

// insert - возвращает новую строку, в которой указанная строка (str)
// вставлена в указанную позицию (start_index) в данной строке (src).
void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
    char* temp;

    if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
        temp = s21_NULL;
    } else {
        s21_size_t i, j;
        temp = malloc(sizeof(char) * (s21_strlen(src)+s21_strlen(str)+1));
        for (i = 0; i < start_index; i++)
            temp[i] = src[i];
        for (j = 0; j < s21_strlen(str); j++, i++)
            temp[i] = str[j];
        for (j = start_index; src[j]; j++, i++)
            temp[i] = src[j];
        temp[i] = '\0';
    }

    return temp;
}

// trim - возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src).
void* s21_trim(const char* src, const char* trim_chars) {
    char* temp;

    if (src == s21_NULL) {
        temp = s21_NULL;
    } else if (trim_chars == s21_NULL) {
        temp = s21_trim(src, " ");
    } else if (s21_strspn(src, trim_chars) == s21_strlen(src)) {
        temp = malloc(sizeof(char));
        temp[0] = '\0';
    } else {
        // i - начало вхождения trim_chars в конце src.
        s21_size_t i;

        int no_return = 1;
        for (i = s21_strlen(src)-1; src[i] && no_return; i--) {
            char* trim = (char*)trim_chars;
            int no_break = 1;

            for (; *trim && no_break; trim++)
                if (src[i] == *trim) {
                    no_break = 0;
                    trim--;
                }

            if (*trim == '\0') {
                no_return = 0;
                i += 2;
            }
        }

        // k - конец вхождения trim_chars в начале src.
        s21_size_t k = s21_strspn(src, trim_chars);

        temp = malloc(sizeof(char) * (i-k+1));

        s21_size_t j;
        for (j = 0; k < i; k++, j++)
            temp[j] = src[k];

        temp[j] = '\0';
    }

    return temp;
}
