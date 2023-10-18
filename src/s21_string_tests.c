#include "s21_tests.h"

// memchr – поиск первого вхождения указанного символа в массиве.
START_TEST(s21_memchr_test) {
    // 1. Находим существующее вхождение символа.
    char src[18] = "Jilted Generation\0";
    char *sym1, *sym2;
    sym1 = s21_memchr(src, 'G', 18);
    sym2 = memchr(src, 'G', 18);
    ck_assert_str_eq(sym1, sym2);

    // 2. Пробуем найти несуществующий символ.
    sym1 = s21_memchr(src, '@', 18);
    sym2 = memchr(src, '@', 18);
    ck_assert_pstr_eq(sym1, sym2);

    // 3. Пробуем выйти за рамки массива.
    sym1 = s21_memchr(src, '@', 35);
    sym2 = memchr(src, '@', 35);
    ck_assert_pstr_eq(sym1, sym2);
}
END_TEST

// memcmp – сравнение массивов.
START_TEST(s21_memcmp_test) {
    // 1. Сравниваем одинаковые массивы.
    char src1[] = "1234567890";
    char src2[] = "1234567890";
    int res1, res2;
    res1 = s21_memcmp(src1, src2, 10);
    res2 = memcmp(src1, src2, 10);
    ck_assert_int_eq(res1, res2);

    // 2. Пробуем зацепить символ окончания строки.
    res1 = s21_memcmp(src1, src2, 11);
    res2 = memcmp(src1, src2, 11);
    ck_assert_int_eq(res1, res2);

    // 3. Пробуем выйти за рамки массива.
    res1 = s21_memcmp(src1, src2, 35);
    res2 = memcmp(src1, src2, 35);
    ck_assert_int_eq(res1, res2);

    // 4. Сравниваем разные массивы.
    char src3[] = "0987654321";
    res1 = s21_memcmp(src1, src3, 10);
    res2 = memcmp(src1, src3, 10);
    ck_assert_int_eq(res1, res2);

    res1 = s21_memcmp(src3, src2, 10);
    res2 = memcmp(src3, src2, 10);
    ck_assert_int_eq(res1, res2);
}
END_TEST

// memcpy – копирование непересекающихся массивов.
START_TEST(s21_memcpy_test) {
    // 1. Копируем массив символов.
    char src[19] = "Weather Experience";
    char dst1[19] = "...";
    s21_memcpy(dst1, src, s21_strlen(src));
    char dst2[19] = "...";
    memcpy(dst2, src, strlen(src));
    ck_assert_str_eq(dst1, dst2);

    // 2. Копируем массив значений типа int.
    int src_int_1[5] = {1, 2, 3, 4, 5};
    int dst_int_1[5] = {0};
    s21_memcpy(dst_int_1, src_int_1, sizeof(src_int_1));
    int dst_int_2[5] = {0};
    memcpy(dst_int_2, src_int_1, sizeof(src_int_1));
    ck_assert_int_eq(dst_int_1[3], dst_int_2[3]);

    // 3. Копируем три байта.
    char dst3[10] = "";
    s21_memcpy(dst3, src, 3);
    char dst4[10] = "";
    memcpy(dst4, src, 3);
    ck_assert_str_eq(dst1, dst2);
}
END_TEST

// memmove – копирование массивов (в том числе пересекающихся).
START_TEST(s21_memmove_test) {
    // 1. Копируем перекрывающийся массив символов.
    char src1[11] = "0123456789";
    s21_memmove(&src1[4], &src1[3], 3);
    char src2[11] = "0123456789";
    memmove(&src2[4], &src2[3], 3);
    ck_assert_str_eq(src1, src2);

    // 2. Копируем массив символов.
    char src[19] = "Weather Experience";
    char dst1[19] = "...";
    s21_memmove(dst1, src, s21_strlen(src));
    char dst2[19] = "...";
    memmove(dst2, src, strlen(src));
    ck_assert_str_eq(dst1, dst2);

    // 3. Копируем массив значений типа int.
    int src_int_1[5] = {1, 2, 3, 4, 5};
    int dst_int_1[5] = {0};
    s21_memmove(dst_int_1, src_int_1, sizeof(src_int_1));
    int dst_int_2[5] = {0};
    memmove(dst_int_2, src_int_1, sizeof(src_int_1));
    ck_assert_int_eq(dst_int_1[3], dst_int_2[3]);

    // 4. Копируем три байта.
    char dst3[10] = "";
    s21_memmove(dst3, src, 3);
    char dst4[10] = "";
    memmove(dst4, src, 3);
    ck_assert_str_eq(dst1, dst2);
}
END_TEST

// memset – заполнения массива указанными символами.
START_TEST(s21_memset_test) {
    // 1. Копируем символ в первые 5 байт.
    char src1[14] = "tupity unity";
    s21_memset(src1, '!', 5);
    char src2[14] = "tupity unity";
    memset(src2, '!', 5);
    ck_assert_str_eq(src1, src2);

    // 2. Копируем символ в первые 1 байт.
    s21_memset(src1, '+', 1);
    memset(src2, '+', 1);
    ck_assert_str_eq(src1, src2);

    // 3. Копируем символ во все байты строки.
    s21_memset(src1, '~', s21_strlen(src1));
    memset(src2, '~', strlen(src2));
    ck_assert_str_eq(src1, src2);
}
END_TEST

// strcat – объединение строк.
START_TEST(s21_strcat_test) {
    // 1. Присоединяем обычную строку к обычной строке.
    char dont_worry[35] = "Don't worry,";
    char* be_happy = " be happy";
    s21_strcat(dont_worry, be_happy);
    char dont_worry_2[35] = "Don't worry,";
    strcat(dont_worry_2, be_happy);
    ck_assert_str_eq(dont_worry, dont_worry_2);

    // 2. Присоединяем пустую строку к обычной строке.
    char teenage_riot[13] = "Teenage Riot";
    char empty[1] = "\0";
    s21_strcat(teenage_riot, empty);
    char teenage_riot_2[13] = "Teenage Riot";
    strcat(teenage_riot_2, empty);
    ck_assert_str_eq(teenage_riot, teenage_riot_2);

    // 3. Присоединяем пустую строку к пустой строке.
    s21_strcat(empty, "");
    char empty_2[1] = "\0";
    strcat(empty_2, "");
    ck_assert_str_eq(empty, empty_2);

    // 4. Сравниваем непосредственно возвращаемые значения функций.
    char destination[40] = "Here w0 are123\0";
    char origin[40] = "Here w0 are123\0";
    char test1[20] = "Hell0 world\0";
    ck_assert_str_eq(s21_strcat(destination, test1), strcat(origin, test1));
}
END_TEST

// strncat – объединение строк c ограничением длины добавляемой строки.
START_TEST(s21_strncat_test) {
    // 1. Присоединяем к строке три символа.
    char str1[20] = "Dylan ";
    char app[3] = "Bob";
    s21_strncat(str1, app, 3);
    char str2[20] = "Dylan ";
    strncat(str2, app, 3);
    ck_assert_str_eq(str1, str2);

    // 2. Присоединяем символ окончания строки.
    s21_strncat(str1, "\0", 1);
    strncat(str2, "\0", 1);
    ck_assert_str_eq(str1, str2);

    // 3. Присоединяем несколько символов к пустой строке.
    char empty1[10] = "";
    s21_strncat(empty1, app, 3);
    char empty2[10] = "";
    strncat(empty2, app, 3);
    ck_assert_str_eq(empty1, empty2);
}
END_TEST

// strchr – поиск первого вхождения символа в строку.
START_TEST(s21_strchr_test) {
    // 1. Ищем обычный символ в обычной строке.
    char* a_elbereth = "A Elbereth Gilthoniel";
    int c = 'e';
    char* res1 = s21_strchr(a_elbereth, c);
    char* res2 = strchr(a_elbereth, c);
    ck_assert_str_eq(res1, res2);

    // 2. Ищем символ окончания строки.
    c = '\0';
    res1 = s21_strchr(a_elbereth, c);
    res2 = strchr(a_elbereth, c);
    ck_assert_str_eq(res1, res2);

    // 3. Ищем несуществующий символ.
    c = 'd';
    res1 = s21_strchr(a_elbereth, c);
    res2 = strchr(a_elbereth, c);
    ck_assert_pstr_eq(res1, res2);

    // 4. Находим первый символ.
    c = 'A';
    res1 = s21_strchr(a_elbereth, c);
    res2 = strchr(a_elbereth, c);
    ck_assert_pstr_eq(res1, res2);
}
END_TEST

// strcmp – сравнение строк.
START_TEST(s21_strcmp_test) {
    // 1. Tест для пустых строк.
    int res1 = s21_strcmp("\0", "\0");
    int res2 = strcmp("\0", "\0");
    ck_assert_int_eq(res1, res2);

    // 2. Tест для одинаковых строк.
    res1 = s21_strcmp("PURGEN", "PURGEN");
    res2 = strcmp("PURGEN", "PURGEN");
    ck_assert_int_eq(res1, res2);

    // 3. Tест для разных строк.
    res1 = s21_strcmp("123", "1");
    res2 = strcmp("123", "1");
    ck_assert_int_eq(res1 >= 0, res2 >= 0);

    // 4. Tест для разных строк.
    res1 = s21_strcmp("1", "123");
    res2 = strcmp("1", "123");
    ck_assert_int_eq(res1 <= 0, res2 <= 0);
}
END_TEST

// strncmp – сравнение строк с ограничением количества сравниваемых символов.
START_TEST(s21_strncmp_test) {
    // 1. Сравниваем первые четыре символа.
    char src1[14] = "half empty";
    char src2[14] = "half full";
    int res1 = s21_strncmp(src1, src2, 5);
    int res2 = strncmp(src1, src2, 5);
    ck_assert_int_eq(res1, res2);

    // 2. Сравниваем строки целиком.
    res1 = s21_strncmp(src1, src2, s21_strlen(src1));
    res2 = strncmp(src1, src2, strlen(src2));
    ck_assert_int_eq(res1, res2);

    // 3. Выходим за границы массива.
    res1 = s21_strncmp(src1, src2, 20);
    res2 = strncmp(src1, src2, 20);
    ck_assert_int_eq(res1, res2);

    // 4. Сравниваем меньшую по длине строку с большей по длине.
    char src3[] = "sex";
    char src4[] = "sex&violence";
    res1 = s21_strncmp(src3, src4, 10);
    res2 = strncmp(src3, src4, 10);
    ck_assert_int_eq(res1, res2);

    // 5. Сравниваем ноль символов.
    res1 = s21_strncmp(src3, src4, 0);
    res2 = strncmp(src3, src4, 0);
    ck_assert_int_eq(res1, res2);
}
END_TEST

// strcpy – копирование строк.
START_TEST(s21_strcpy_test) {
    // 1. Kопируем в строку большего размера.
    char str1a[] = "пыщ-пыщ";
    char* str1b = "DXM";
    s21_strcpy(str1a, str1b);
    char str1c[] = "пыщ-пыщ";
    strcpy(str1c, str1b);
    ck_assert_str_eq(str1a, str1c);

    // 2. Kопируем пустую строку в непустую.
    char str2a[] = "не унывайте пацаны";
    char* str2b = "\0";
    s21_strcpy(str2a, str2b);
    char str2c[] = "не унывайте пацаны";
    strcpy(str2c, str2b);
    ck_assert_str_eq(str2a, str2c);

    // 3. Копируем пустую строку в пустую.
    char str3a[] = "";
    char* str3b = "";
    s21_strcpy(str3a, str3b);
    char str3c[] = "";
    strcpy(str3c, str3b);
    ck_assert_str_eq(str3a, str3c);

    // 4. Сравниваем непосредственно возвращаемые значения функций.
    char destination[] = "Here w0 are\0";
    char origin[] = "Here w0 are\0";
    char test1[20] = "Hell0 world\0";
    ck_assert_str_eq(s21_strcpy(destination, test1), strcpy(origin, test1));
}
END_TEST

// strncpy – копирование строк c ограничением длины.
START_TEST(s21_strncpy_test) {
    // 1. Копируем 12 символов.
    char src[] = "pop will eat itself";
    char res1[30], res2[30];
    s21_strncpy(res1, src, 12);
    strncpy(res2, src, 12);
    res2[12] = '\0';
    res1[12] = '\0';
    ck_assert_str_eq(res1, res2);

    // 2. Копируем строку целиком.
    s21_strncpy(res1, src, s21_strlen(src));
    strncpy(res2, src, strlen(src));
    res1[19] = '\0';
    res2[19] = '\0';
    ck_assert_str_eq(res1, res2);

    // 3. Копируем в существующую строку и сравниваем непосредственно возвращаемые значения функций.
    char destination3[] = "Here w0 are\0";
    char result3[] = "Here w0 are\0";
    char test1[20] = "Hell0 world\0";
    ck_assert_str_eq(s21_strncpy(destination3, test1, 4), strncpy(result3, test1, 4));
}
END_TEST

// strcspn – определение длины участка строки, не содержащего указанные символы.
START_TEST(s21_strcspn_test) {
    // 1. Находим длину отрезка, в который не входят указанные символы.
    char src[] = "gallons of rubbing alcohol flow through the strip";
    char sym1[] = "zwdf";
    ck_assert_int_eq(s21_strcspn(src, sym1), strcspn(src, sym1));

    // 2. Случай, когда искомый символ встречается сразу.
    char sym2[] = "g";
    ck_assert_int_eq(s21_strcspn(src, sym2), strcspn(src, sym2));

    // 3. Случай, когда символы вообще не встречаются.
    char sym3[] = "#@!$";
    ck_assert_int_eq(s21_strcspn(src, sym3), strcspn(src, sym3));

    // 4. Случай, когда конец строки не определён.
    char str[10] = "0123456789";
    char sym4[10] = "98765";
    ck_assert_int_eq(s21_strcspn(str, sym4), strcspn(str, sym4));
}
END_TEST

// strerror – формирование сообщения об ошибке по коду ошибки.
START_TEST(s21_strerror_test) {
    // 1. Сравним возвращаемые значения функций для ошибки номер 14.
    char* str1 = s21_strerror(14);
    char* str2 = strerror(14);
    ck_assert_str_eq(str1, str2);

    // 2. Сравним вывод для несуществующей ошибки.
    str1 = s21_strerror(350);
    str2 = strerror(350);
    ck_assert_str_eq(str1, str2);

    // 3. Сравним вывод для числа, следующего за номером последней ошибки (macOS).
    str1 = s21_strerror(107);
    str2 = strerror(107);
    ck_assert_str_eq(str1, str2);

    // 4. Сравним вывод для несуществующей ошибки c отрицательным номером.
    str1 = s21_strerror(-350);
    str2 = strerror(-350);
    ck_assert_str_eq(str1, str2);
}
END_TEST

// strlen – определение длины строки.
START_TEST(s21_strlen_test) {
    // 1. Тесты для пустых строк.
    ck_assert_int_eq(s21_strlen(""), strlen(""));
    ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));

    // 2. Тест для обычной строки.
    char* str1 = "NEVERMIND THE BOLLOCKS, HERE'S THE SEX PISTOLS";
    ck_assert_int_eq(s21_strlen(str1), strlen(str1));

    // 3. Тест на EOF.
    char str2[5];
    s21_sprintf(str2, "%d", EOF);
    ck_assert_int_eq(s21_strlen(str2), strlen(str2));
}
END_TEST

// strpbrk – поиск первого вхождения в строку символа из указанного множества.
START_TEST(s21_strpbrk_test) {
    // 1. Ищем вхождение одного из существующих символов.
    char* a_elbereth = "A Elbereth Gilthoniel";
    char* gilth = "Goni";
    char* res1 = s21_strpbrk(a_elbereth, gilth);
    char* res2 = strpbrk(a_elbereth, gilth);
    ck_assert_str_eq(res1, res2);

    // 2. Ищем вхождение несуществующих символов.
    char* svirel = "SVIREL";
    res1 = s21_strpbrk(a_elbereth, svirel);
    res2 = strpbrk(a_elbereth, svirel);
    ck_assert_pstr_eq(res1, res2);

    // 3. Ищем вхождение нулевого символа.
    res1 = s21_strpbrk(a_elbereth, "\0");
    res2 = strpbrk(a_elbereth, "\0");
    ck_assert_pstr_eq(res1, res2);
}
END_TEST

// strrchr – поиск последнего вхождения символа в строку.
START_TEST(s21_strrchr_test) {
    // 1. Ищем обычный символ в обычной строке.
    char* a_elbereth = "A Elbereth Gilthoniel";
    int c = 'e';
    char* res1 = s21_strrchr(a_elbereth, c);
    char* res2 = strrchr(a_elbereth, c);
    ck_assert_str_eq(res1, res2);

    // 2. Ищем символ окончания строки.
    c = '\0';
    res1 = s21_strrchr(a_elbereth, c);
    res2 = strrchr(a_elbereth, c);
    ck_assert_str_eq(res1, res2);

    // 3. Ищем несуществующий символ.
    c = 'd';
    res1 = s21_strrchr(a_elbereth, c);
    res2 = strrchr(a_elbereth, c);
    ck_assert_pstr_eq(res1, res2);

    char str[] = "\0\0\\0\0";
    res1 = s21_strrchr(str, '\0');
    res2 = strrchr(str, '\0');
    ck_assert_pstr_eq(res1, res2);
}
END_TEST

// strspn – определение максимальной длины участка строки, содержащего только указанные символы.
START_TEST(s21_strspn_test) {
    // 1. Находим длину отрезка, в который входят указанные символы.
    char src[] = "gallons of rubbing alcohol flow through the strip";
    char sym1[] = "galons frubich";
    ck_assert_int_eq(s21_strspn(src, sym1), strspn(src, sym1));

    // 2. Случай, когда искомый символ встречается сразу.
    char sym2[] = "g";
    ck_assert_int_eq(s21_strspn(src, sym2), strspn(src, sym2));

    // 3. Случай, когда символы вообще не встречаются.
    char sym3[] = "#@!$";
    ck_assert_int_eq(s21_strspn(src, sym3), strspn(src, sym3));

    // 4. Случай, когда конец строки не определён.
    char str[10] = "0123456789";
    char sym4[10] = "98765";
    ck_assert_int_eq(s21_strspn(str, sym4), strspn(str, sym4));
}
END_TEST

// strstr – поиск первого вхождения строки А в строку В.
START_TEST(s21_strstr_test) {
    // 1. Ищем существующее вхождение в обычной строке.
    char* a_elbereth = "A Elbereth Gilthoniel";
    char* gilth = "Gilthoniel";
    char* res1 = s21_strstr(a_elbereth, gilth);
    char* res2 = strstr(a_elbereth, gilth);
    ck_assert_str_eq(res1, res2);

    // 2. Ищем несуществующее вхождение в обычной строке.
    char* svirel = "Svirel";
    res1 = s21_strstr(a_elbereth, svirel);
    res2 = strstr(a_elbereth, svirel);
    ck_assert_pstr_eq(res1, res2);

    // 3. Ищем вхождение нулевого символа.
    res1 = s21_strstr(a_elbereth, "\0");
    res2 = strstr(a_elbereth, "\0");
    ck_assert_pstr_eq(res1, res2);
}
END_TEST

// strtok – разбиение строки на части по указанному разделителю.
START_TEST(s21_strtok_test) {
    // 1. Разбиваем строку по одному разделителю.
    char dancer_1[] = "you.never.gonna.stop.the.space.dancer";
    char* sep1 = ".";
    char* res1 = s21_strtok(dancer_1, sep1);
    char dancer_2[] = "you.never.gonna.stop.the.space.dancer";
    char* res2 = strtok(dancer_2, sep1);
    ck_assert_str_eq(res1, res2);

    // 2. Вызываем функцию с параметром NULL для продолжения обработки предыдущей строки.
    res1 = s21_strtok(s21_NULL, sep1);
    res2 = strtok(NULL, sep1);
    ck_assert_str_eq(res1, res2);

    // 3. Разбиваем строку по нескольким разделителям.
    char p1[] = "So, I've decided to take my work back underground to stop it falling into the wrong hands.";
    char* sep2 = ",'-wtf";
    res1 = s21_strtok(p1, sep2);
    char p2[] = "So, I've decided to take my work back underground to stop it falling into the wrong hands.";
    res2 = strtok(p2, sep2);
    ck_assert_str_eq(res1, res2);

    // 4. Разбиваем строку по нескольким разделителям до тех пор, пока функция не вернёт NULL.
    while (res1 != s21_NULL)
        res1 = s21_strtok(s21_NULL, sep2);
    while (res2 != NULL)
        res2 = strtok(NULL, sep2);
    ck_assert_pstr_eq(res1, res2);

    // 5. Пробуем разбить строку по разделителям, которых в ней нет.
    res1 = s21_strtok(dancer_1, "/");
    res2 = strtok(dancer_2, "/");
    ck_assert_str_eq(res1, res2);

    // 6. Разбиваем строку, которая начинается с разделителей.
    char str1[] = "...350...";
    char str2[] = "...350...";
    res1 = s21_strtok(str1, ".3");
    res2 = strtok(str2, ".3");
    ck_assert_str_eq(res1, res2);

    // 7. Разбиваем строку, которая начинается с разделителей, но ими не заканчивается.
    char dest4[] = ".swe\0";
    char orig4[] = ".swe\0";
    ck_assert_str_eq(s21_strtok(dest4, "."), strtok(orig4, "."));
}
END_TEST

// to_upper - возвращает копию строки, преобразованной в верхний регистр.
START_TEST(s21_to_upper_test) {
    // 1. Преобразуем строку в верхний регистр.
    char src[] = "abcdefghijklmnopqrstuvwxyz 1234567890,.!@#$%^&*()-+= <>?~";
    char* to_up = s21_to_upper(src);
    ck_assert_str_eq(to_up, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890,.!@#$%^&*()-+= <>?~");

    // 2. Преобразуем NULL.
    char* null = s21_NULL;
    to_up = s21_to_upper(null);
    ck_assert_pstr_eq(to_up, s21_NULL);

    free(to_up);
}
END_TEST

// to_lower - возвращает копию строки, преобразованной в нижний регистр.
START_TEST(s21_to_lower_test) {
    // 1. Преобразуем строку в нижний регистр.
    char src[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890,.!@#$%^&*()-+= <>?~";
    char* to_low = s21_to_lower(src);
    ck_assert_str_eq(to_low, "abcdefghijklmnopqrstuvwxyz 1234567890,.!@#$%^&*()-+= <>?~");

    // 2. Преобразуем NULL.
    char* null = s21_NULL;
    to_low = s21_to_lower(null);
    ck_assert_pstr_eq(to_low, s21_NULL);

    free(to_low);
}
END_TEST

// insert - возвращает новую строку, в которой указанная строка (str)
// вставлена в указанную позицию (start_index) в данной строке (src).
START_TEST(s21_insert_test) {
    // 1. Вставляем строку в середину.
    char* str  = "Tupity Unity";
    char* res = s21_insert(str, " -===3.50===-", 6);
    ck_assert_str_eq(res, "Tupity -===3.50===- Unity");

    // 2. Пробуем вставить что-либо в строку, равную NULL.
    char* null = s21_NULL;
    res = s21_insert(null, "???", 48);
    ck_assert_pstr_eq(res, s21_NULL);

    // 3. Пробуем вставить NULL в строку.
    res = s21_insert(str, null, 48);
    ck_assert_pstr_eq(res, s21_NULL);

    // 4. Пробуем вставить что-то в место, выходящее за рамки заданной строки.
    res = s21_insert(str, "3.50", 777);
    ck_assert_pstr_eq(res, s21_NULL);

    // 5. Пробуем вызвать функцию с отрицательным параметром start_index.
    res = s21_insert(str, "3.50", -777);
    ck_assert_pstr_eq(res, s21_NULL);

    // 6. Вставляем строку в конец другой строки.
    res = s21_insert(str, " Forever", s21_strlen(str));
    ck_assert_str_eq(res, "Tupity Unity Forever");

    // 7. Вставляем строку в начало другой строки.
    res = s21_insert(str, "Forever ", 0);
    ck_assert_str_eq(res, "Forever Tupity Unity");

    free(res);
}
END_TEST

// trim - возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src).
START_TEST(s21_trim_test) {
    // 1. Обрезаем символы с обоих краёв строки.
    char* banner = "*** 'Much @do @bout Nothing' ***";
    char* charsToTrim = "* \'.@#";
    char* result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "Much @do @bout Nothing");

    // 2. Обрезаем сивмолы в начале строки.
    banner = "^__^ Well_done!";
    charsToTrim = "^_ ";
    result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "Well_done!");

    // 3. Обрезаем символы в конце строки.
    banner = "Well_done! (^__^)";
    charsToTrim = "^_ ()";
    result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "Well_done!");

    // 4. Пробуем обрезать несуществуюшие символы.
    banner = "Well, get off the TV!";
    charsToTrim = "#%:,.;()$^&*";
    result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "Well, get off the TV!");

    // 5. Пробуем обработать строку, целиком состоящую из trim_chars.
    banner = "..;;;;-)))";
    charsToTrim = "#%:,-.;()$^&*";
    result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "");

    // 6. Отправляем на обработку NULL-строку. Возвращаемое значение - NULL.
    char* null = s21_NULL;
    result = s21_trim(null, charsToTrim);
    ck_assert_pstr_eq(result, s21_NULL);

    // 7. Используем NULL-строку в качестве разделителей. Из результата обрезаются пробелы.
    banner = "   School 21   ";
    result = s21_trim(banner, null);
    ck_assert_pstr_eq(result, "School 21");

    // 8. Обрезаем все символы из строки.
    banner = "School-21";
    charsToTrim = "School-21";
    result = s21_trim(banner, charsToTrim);
    ck_assert_str_eq(result, "");

    free(result);
}
END_TEST

// Функция создания набора тестов.
    Suite* s21_string_suite(void) {
    Suite* s = suite_create("s21_string Unit Tests");

    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase* tc_s21_string = tcase_create("s21_string");

    // Добавление тестов в группу.
    tcase_add_test(tc_s21_string, s21_memchr_test);
    tcase_add_test(tc_s21_string, s21_memcmp_test);
    tcase_add_test(tc_s21_string, s21_memcpy_test);
    tcase_add_test(tc_s21_string, s21_memmove_test);
    tcase_add_test(tc_s21_string, s21_memset_test);
    tcase_add_test(tc_s21_string, s21_strcat_test);
    tcase_add_test(tc_s21_string, s21_strncat_test);
    tcase_add_test(tc_s21_string, s21_strchr_test);
    tcase_add_test(tc_s21_string, s21_strcmp_test);
    tcase_add_test(tc_s21_string, s21_strncmp_test);
    tcase_add_test(tc_s21_string, s21_strcpy_test);
    tcase_add_test(tc_s21_string, s21_strncpy_test);
    tcase_add_test(tc_s21_string, s21_strcspn_test);
    tcase_add_test(tc_s21_string, s21_strerror_test);
    tcase_add_test(tc_s21_string, s21_strlen_test);
    tcase_add_test(tc_s21_string, s21_strpbrk_test);
    tcase_add_test(tc_s21_string, s21_strrchr_test);
    tcase_add_test(tc_s21_string, s21_strspn_test);
    tcase_add_test(tc_s21_string, s21_strstr_test);
    tcase_add_test(tc_s21_string, s21_strtok_test);

    tcase_add_test(tc_s21_string, s21_to_upper_test);
    tcase_add_test(tc_s21_string, s21_to_lower_test);
    tcase_add_test(tc_s21_string, s21_insert_test);
    tcase_add_test(tc_s21_string, s21_trim_test);

    // Добавление группы в тестовый набор.
    suite_add_tcase(s, tc_s21_string);

    return s;
}
