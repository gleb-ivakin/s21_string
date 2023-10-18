#include "s21_tests.h"

#define BUFF_SIZE 512

START_TEST(test_sprintf_d) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "h%%el%dlo!%d", 50, -60);
  char output1[100] = "";
  sprintf(output1, "h%%el%dlo!%d", 50, -60);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%drld!", 50);
  char output2[100] = "";
  sprintf(output2, "hel%drld!", 50);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%dlo!", -50000);
  char output3[100] = "";
  sprintf(output3, "hel%dlo!", -50000);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%dlo!", 000000);
  char output4[100] = "";
  sprintf(output4, "hel%dlo!", 000000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%dlo!", 5);
  char output5[100] = "";
  sprintf(output5, "hel%dlo!", 5);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);

  // if(sum5 != -4)
  //    ck_abort_msg("Test failed: -1+-3 != %d\n",sum5);
}
END_TEST

START_TEST(s21_sprintf_test) {
    char str1[150] = "";
    char str2[150] = "";
    char buf1[60] = "";
    char buf2[60] = "";
    char s1[150] = "";
    char s2[150] = "";
    char buff1[50] = "";
    char buff2[50] = "";
     char st1[100] = "";
     char st2[100] = "";
    int l1 = s21_sprintf(str1, "%+*d", 6, 534);
    int l2 = sprintf(str2, "%+*d", 6, 534);
    ck_assert_int_eq(l1, l2);
    ck_assert_str_eq(str1, str2);
    int l3 = s21_sprintf(buf1, "%.*d %d % f %+-*d %% ", 6, 2888, -286, 4.0, 6, 100);
    int l4 = sprintf(buf2, "%.*d %d % f %+-*d %% ", 6, 2888, -286, 4.0, 6, 100);
    ck_assert_int_eq(l3, l4);
    ck_assert_str_eq(buf1, buf2);
    int l5 = sprintf(s1, "%*.*d %d % f %+-*d %% %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 7, 45674, 8,
                     'Q', 7, 5555555555);
    int l6 = s21_sprintf(s2, "%*.*d %d % f %+-*d %% %.*i %*c %-*lu\n", 9, 6, 2888, -286, 4.0, 6, 100, 7,
                         45674, 8, 'Q', 7, 5555555555);
    ck_assert_int_eq(l5, l6);
    ck_assert_str_eq(s1, s2);
    int l7 = s21_sprintf(buff1, "%s", "Hello world Hello world Hello world");
    int l8 = sprintf(buff2, "%s", "Hello world Hello world Hello world");
    ck_assert_int_eq(l7, l8);
    ck_assert_str_eq(buff1, buff2);
    int l9 = s21_sprintf(st1, "%-*.*f %d %-*c", 10, 0, -123.2345, 0, 5, 'S');
    int l10 = sprintf(st2, "%-*.*f %d %-*c", 10, 0, -123.2345, 0, 5, 'S');
    ck_assert_int_eq(l9, l10);
    ck_assert_str_eq(st1, st2);
}
END_TEST

START_TEST(test_sprintf_s) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%-10.2slo!%10.2s", "qqq", "x\0x");
  char output1[100] = "";
  sprintf(output1, "hel%-10.2slo!%10.2s", "qqq", "x\0x");

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%srld!", "lo wo");
  char output2[100] = "";
  sprintf(output2, "hel%srld!", "lo wo");

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%slo!", "");
  char output3[100] = "";
  sprintf(output3, "hel%slo!", "");

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%slo%%!", "\n");
  char output4[100] = "";
  sprintf(output4, "hel%slo%%!", "\n");

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%slo!", "EOF");
  char output5[100] = "";
  sprintf(output5, "hel%slo!", "EOF");

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_random) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "%+f%+1.1f%- 71.10fq\n", 0., 123.4567, 8.9);
  char output1[100] = "";
  sprintf(output1, "%+f%+1.1f%- 71.10fq\n", 0., 123.4567, 8.9);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "%+9.7f% 1.9f\n", 9.1234567891011, 8.999999999);
  char output3[100] = "";
  sprintf(output3, "%+9.7f% 1.9f\n", 9.1234567891011, 8.999999999);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "%*.*d %d % f %+-*d %% %*.*s %.*i %*c %-*lu\n", 9, 6, 2888,
  -286, 4.0, 6, 100, 8, 3, "Hello", 7, 45674, 8, 'Q', 7, 5555555555);
  char output4[100] = "";
  sprintf(output4, "%*.*d %d % f %+-*d %% %*.*s %.*i %*c %-*lu\n", 9, 6, 2888,
  -286, 4.0, 6, 100, 8, 3, "Hello", 7, 45674, 8, 'Q', 7, 5555555555);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "ll:%lld l:%ld s:%hd int:%d\n",
  9223372036854775807LL, -9223372036854775807, (short)231, 2022);
  char output5[100] = "";
  sprintf(output5, "ll:%lld l:%ld s:%hd int:%d\n", 9223372036854775807LL,
  -9223372036854775807, (short)231, 2022);

  char s21_output6[100] = "";
  sprintf(s21_output6, "%.2d", 1);
  sprintf(s21_output6, "%.2d", 1);
  s21_sprintf(s21_output6, "%.2d", 1);
  char output6[100] = "";
  sprintf(output6, "%.2d", 1);
  sprintf(output6, "%.2d", 1);
  sprintf(output6, "%.2d", 1);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  // ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
    ck_assert_str_eq(s21_output4, output4);  // FIXME: still not work
  ck_assert_str_eq(s21_output5, output5);
  ck_assert_str_eq(s21_output6, output6);
}
END_TEST

START_TEST(test_sprintf_u) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%ulo!%u", 50u, -60u);
  char output1[100] = "";
  sprintf(output1, "hel%ulo!%u", 50u, -60u);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%urld!", 50u);
  char output2[100] = "";
  sprintf(output2, "hel%urld!", 50u);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%ulo!", -50000u);
  char output3[100] = "";
  sprintf(output3, "hel%ulo!", -50000u);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%ulo%%!", 000000u);
  char output4[100] = "";
  sprintf(output4, "hel%ulo%%!", 000000u);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%ulo!", 5u);
  char output5[100] = "";
  sprintf(output5, "hel%ulo!", 5u);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_i) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%ilo!%i", 50, -60);
  char output1[100] = "";
  sprintf(output1, "hel%ilo!%i", 50, -60);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%irld!", 50);
  char output2[100] = "";
  sprintf(output2, "hel%irld!", 50);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "h%%el%ilo!", -50000);
  char output3[100] = "";
  sprintf(output3, "h%%el%ilo!", -50000);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%ilo!", 000000);
  char output4[100] = "";
  sprintf(output4, "hel%ilo!", 000000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%ilo!", 5);
  char output5[100] = "";
  sprintf(output5, "hel%ilo!", 5);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_accur) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%.7flo!%.8f", 50.123, -60.123);
  char output1[100] = "";
  sprintf(output1, "hel%.7flo!%.8f", 50.123, -60.123);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%.0flo!", 50.543);
  char output2[100] = "";
  sprintf(output2, "hel%.0flo!", 50.543);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%1.10flo!", -50000.);
  char output3[100] = "";
  sprintf(output3, "hel%1.10flo!", -50000.);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%10.1flo!", 0.00000);
  char output4[100] = "";
  sprintf(output4, "hel%10.1flo!", 0.00000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%0.0flo!%%%%%%", 5.);
  char output5[100] = "";
  sprintf(output5, "hel%0.0flo!%%%%%%", 5.);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_width) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%5flo!%6f", 50.123, -60.123);
  char output1[100] = "";
  sprintf(output1, "hel%5flo!%6f", 50.123, -60.123);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%0flo!", 50.);
  char output2[100] = "";
  sprintf(output2, "hel%0flo!", 50.);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%20flo!", -50000.);
  char output3[100] = "";
  sprintf(output3, "hel%20flo!", -50000.);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%1flo!", 0.00000);
  char output4[100] = "";
  sprintf(output4, "hel%1flo!", 0.00000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%2flo!%%%%%%", 5.);
  char output5[100] = "";
  sprintf(output5, "hel%2flo!%%%%%%", 5.);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_p) {
char str1[1000];
    char str2[1000];
    void *p1 = (void*)0x123456789;
    void *p2 = (void*)456123;
    void *p3 = (void*)0xabcdef00;
    void *p4 = (void*)987654;
    int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p",
                     p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);
    int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p",
                         p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sprintf_flag) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%+flo!%+f", 50.123, -60.123);
  char output1[100] = "";
  sprintf(output1, "hel%+flo!%+f", 50.123, -60.123);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel% flo!", 50.);
  char output2[100] = "";
  sprintf(output2, "hel% flo!", 50.);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%0flo!", -50000.);
  char output3[100] = "";
  sprintf(output3, "hel%0flo!", -50000.);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%-flo!", 0.00000);
  char output4[100] = "";
  sprintf(output4, "hel%-flo!", 0.00000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%0 flo!%%%%%%", 5.);
  char output5[100] = "";
  sprintf(output5, "hel%0 flo!%%%%%%", 5.);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_f) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%flo!%f", 50.123, -60.123);
  char output1[100] = "";
  sprintf(output1, "hel%flo!%f", 50.123, -60.123);

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%flo!", 50.);
  char output2[100] = "";
  sprintf(output2, "hel%flo!", 50.);

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%flo!", -50000.);
  char output3[100] = "";
  sprintf(output3, "hel%flo!", -50000.);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%flo!", 0.00000);
  char output4[100] = "";
  sprintf(output4, "hel%flo!", 0.00000);

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%flo!%%%%%%", 5.);
  char output5[100] = "";
  sprintf(output5, "hel%flo!%%%%%%", 5.);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_e) {
  //  function under test
    char s21_output1[100] = "";
    s21_sprintf(s21_output1, "!%e!%E!", 50.123, -60.123);
    char output1[100] = "";
    sprintf(output1, "!%e!%E!", 50.123, -60.123);

    char s21_output2[100] = "";
    s21_sprintf(s21_output2, "!%20e!", -0.50);
    char output2[100] = "";
    sprintf(output2, "!%20e!", -0.50);

    char s21_output3[100] = "";
    s21_sprintf(s21_output3, "!%-20.10E!", -50000.);
    char output3[100] = "";
    sprintf(output3, "!%-20.10E!", -50000.);

    char s21_output4[100] = "";
    s21_sprintf(s21_output4, "!%020.15e!", 0.00000);
    char output4[100] = "";
    sprintf(output4, "!%020.15e!", 0.00000);

    char s21_output5[100] = "";
    s21_sprintf(s21_output5, "!%E!", 5.);
    char output5[100] = "";
    sprintf(output5, "!%E!", 5.);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_g) {
  //  function under test
    char s21_output1[100] = "";
    s21_sprintf(s21_output1, "!%g!%g!", 50.123, -60.123);
    char output1[100] = "";
    sprintf(output1, "!%g!%g!", 50.123, -60.123);

    char s21_output2[100] = "";
    s21_sprintf(s21_output2, "!%20g!", -0.50);
    char output2[100] = "";
    sprintf(output2, "!%20g!", -0.5);

    char s21_output3[100] = "";
    s21_sprintf(s21_output3, "!%-20.10g!", -50000.);
    char output3[100] = "";
    sprintf(output3, "!%-20.10g!", -50000.);

    char s21_output4[100] = "";
    s21_sprintf(s21_output4, "!%020.15g!", 0.00000);
    char output4[100] = "";
    sprintf(output4, "!%020.15g!", 0.00000);

    char s21_output5[100] = "";
    s21_sprintf(s21_output5, "!%g!", 5.);
    char output5[100] = "";
    sprintf(output5, "!%g!", 5.);

    char s21_output6[100] = "";
      s21_sprintf(s21_output6, "!%g!", 0.000050);
      char output6[100] = "";
      sprintf(output6, "!%g!", 0.000050);

      char s21_output7[100] = "";
      s21_sprintf(s21_output7, "!%g!", 0.50);
      char output7[100] = "";
      sprintf(output7, "!%g!", 0.50);

      char s21_output8[100] = "";
      s21_sprintf(s21_output8, "!%20.15g!", 0.50);
      char output8[100] = "";
      sprintf(output8, "!%20.15g!", 0.50);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
  ck_assert_str_eq(s21_output6, output6);
  ck_assert_str_eq(s21_output7, output7);
  ck_assert_str_eq(s21_output8, output8);
}
END_TEST

START_TEST(test_sprintf_c) {
  //  function under test
  char s21_output1[100] = "";
  s21_sprintf(s21_output1, "hel%-5clo!%6c", 'a', 's');
  char output1[100] = "";
  sprintf(output1, "hel%-5clo!%6c", 'a', 's');

  char s21_output2[100] = "";
  s21_sprintf(s21_output2, "hel%clo!", '\0');
  char output2[100] = "";
  sprintf(output2, "hel%clo!", '\0');

  char s21_output3[100] = "";
  s21_sprintf(s21_output3, "hel%clo!", EOF);
  char output3[100] = "";
  sprintf(output3, "hel%clo!", EOF);

  char s21_output4[100] = "";
  s21_sprintf(s21_output4, "hel%clo!", '\n');
  char output4[100] = "";
  sprintf(output4, "hel%clo!", '\n');

  char s21_output5[100] = "";
  s21_sprintf(s21_output5, "hel%clo!", 'Q');
  char output5[100] = "";
  sprintf(output5, "hel%clo!", 'Q');

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_x) {
  //  function under test
    char s21_output1[100] = "";
    s21_sprintf(s21_output1, "!%X!%x!", 50123, 60123);
    char output1[100] = "";
    sprintf(output1, "!%X!%x!", 50123, 60123);

    char s21_output2[100] = "";
    s21_sprintf(s21_output2, "!%20x!", 50);
    char output2[100] = "";
    sprintf(output2, "!%20x!", 50);

    char s21_output3[100] = "";
    s21_sprintf(s21_output3, "!%20.10x!", -123456);
    char output3[100] = "";
    sprintf(output3, "!%20.10x!", -123456);

    char s21_output4[100] = "";
    s21_sprintf(s21_output4, "!%20.15x!", 0);
    char output4[100] = "";
    sprintf(output4, "!%20.15x!", 0);

    char s21_output5[100] = "";
    s21_sprintf(s21_output5, "!%X!", 5);
    char output5[100] = "";
    sprintf(output5, "!%X!", 5);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(test_sprintf_o) {
  //  function under test
    char s21_output1[100] = "";
    s21_sprintf(s21_output1, "!%o!%o!", 50123, 60123);
    char output1[100] = "";
    sprintf(output1, "!%o!%o!", 50123, 60123);

    char s21_output2[100] = "";
    s21_sprintf(s21_output2, "!%20o!", 50);
    char output2[100] = "";
    sprintf(output2, "!%20o!", 50);

    char s21_output3[100] = "";
    s21_sprintf(s21_output3, "!%20.10o!", -123456);
    char output3[100] = "";
    sprintf(output3, "!%20.10o!", -123456);

    char s21_output4[100] = "";
    s21_sprintf(s21_output4, "!%20.15o!", 0);
    char output4[100] = "";
    sprintf(output4, "!%20.15o!", 0);

    char s21_output5[100] = "";
    s21_sprintf(s21_output5, "!%o!", 5);
    char output5[100] = "";
    sprintf(output5, "!%o!", 5);

  // verify results are as expected
  ck_assert_str_eq(s21_output1, output1);
  ck_assert_str_eq(s21_output2, output2);
  ck_assert_str_eq(s21_output3, output3);
  ck_assert_str_eq(s21_output4, output4);
  ck_assert_str_eq(s21_output5, output5);
}
END_TEST

START_TEST(s21_chars_f) {
    char test1[20] = "Hell0 world\0";
    char test2[20] = "Hell0 world\n\0";
    char test3[10] = "a\n\0";
    char test4[10] = " \n\0";
    char test5[10] = " \0";
    char test6[10] = "\n\0";
    char test7[10] = "\0";
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer, "%%%% %c %s %c%s %c %s %s %s %s %s", 'a', test1, '\n',
              test2, '-', test3, test4, test5, test6, test7);
  sprintf(buffer, "%%%% %c %s %c%s %c %s %s %s %s %s", 'a', test1, '\n', test2,
          '-', test3, test4, test5, test6, test7);
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer,
              "%-2i %+5i % 4i %2i %4d %d %15d %-+15d %22u %5u %4u %3u", 101,
              -210, -0, '0', 101, -210, -0, '0', (unsigned int)101,
              (unsigned int)210, (unsigned int)-0, (unsigned int)'0');
  sprintf(buffer, "%-2i %+5i % 4i %2i %4d %d %15d %-+15d %22u %5u %4u %3u", 101,
          -210, -0, '0', 101, -210, -0, '0', (unsigned int)101,
          (unsigned int)210, (unsigned int)-0, (unsigned int)'0');
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums2_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};

  s21_sprintf(s21_buffer, "%- 5li %-5hi %12hu %-4lu %hi %li %hi %li",
              (long int)125123123123, (short int)160, (unsigned short)101,
              (unsigned long)210, (short int)0, (long int)0, (short int)-25, (long int)-51);
  sprintf(buffer, "%- 5li %-5hi %12hu %-4lu %hi %li %hi %li", (long int)125123123123,
          (short int)160, (unsigned short)101, (unsigned long)210, (short int)0, (long int)0,
          (short int)-25, (long int)-51);
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums3_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer, "%-+6.4f %-2.2f %5.5f %f %f", 100.0, 0.01, 0.10,
              -12.0, 0.00001);
  sprintf(buffer, "%-+6.4f %-2.2f %5.5f %f %f", 100.0, 0.01, 0.10, -12.0,
          0.00001);
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_sprintf_test1) {
  char str1[100]="______";
  char str2[100]="______";
  void *p = (void*)0x3456;
  int n1, n2;
  int r1 = sprintf(str1, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba", 'a', 123, 25.34, 4325.23434,
  0.0000000123, 2.12345, 12345u, 8342, 0.0000456, 1235, &n1, p, "hello my friend");
  int r2 = s21_sprintf(str2, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba", 'a',
  123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u, 8342, 0.0000456, 1235, &n2, p, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char str1[100];
  char str2[100];
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  int r2 = s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char str1[100];
  char str2[100];
  int r1 = sprintf(str1, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567, "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char str1[100];
  char str2[100];
  void *p = (void*)43252342;
  int r1 = sprintf(str1, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p, 43252342u);
  int r2 = s21_sprintf(str2, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[50];
  char str4[100];
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  int r1 = sprintf(str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd",
  253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd",
  253, 335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
  char str1[1000];
  char str2[1000];
  short h = 34;
  long l = 2353423523424;
  int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
  34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  int r2 = s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
  34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
  char str1[1000];
  char str2[1000];
  wchar_t c1 = 'T', c2 = 'Z';
  int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc",
  'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc",
  'a', 'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
  2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
  11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int r2 = s21_sprintf(str2, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
  2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
  11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
  3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2, 53242.4242,
  10, 456789.43242, 25, 1111122222.34567899, 2345678.23453242);
  int r2 = s21_sprintf(str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
  3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2, 53242.4242,
  10, 456789.43242, 25, 1111122222.34567899, 2345678.23453242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
  2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245, 2, 12345.6788,
  1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2, 34567.43244);
  int r2 = s21_sprintf(str2, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
  2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245, 2, 12345.6788,
  1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2, 34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 = s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 =
  sprintf(str1,
  "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*x%#10.*x%*.5hx%10.25lx",
  235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 =
  s21_sprintf(str2,
  "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*x%#10.*x%*.5hx%10.25lx",
  235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 =
  sprintf(str1, "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%#12.*X%*.8hx%14.12lX",
  235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 =
  s21_sprintf
  (str2, "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%#12.*X%*.8hx%14.12lX",
  235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  char str1[1000];
  char str2[1000];
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 = sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
  4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l, h);
  int r2 = s21_sprintf(str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
  4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  char str1[1000];
  char str2[1000];
  wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
  int r1 = sprintf(str1,
  "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10, "QWERTY",
  15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  int r2 = s21_sprintf(str2,
  "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10, "QWERTY",
  15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
  char str1[1000];
  char str2[1000];
  void *p1 = (void*)0x123456789;
  void *p2 = (void*)4325234;
  void *p3 = (void*)0x123f324b;
  void *p4 = (void*)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p",
  p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p",
  p1, p2, p3, p4, p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(test_sprintf_n) {
    char s1[1500];
    char s2[1500];

    int i1 = 0, i2 = 0, r1 = 0;
    int s21_i1 = 0, s21_i2 = 0, s21_r1 = 0;
    r1 = sprintf(s1, "123456%n%d%n", &i1, 123, &i2);
    s21_r1 = s21_sprintf(s2, "123456%n%d%n", &s21_i1, 123, &s21_i2);
    ck_assert_int_eq(i1, s21_i1);
    ck_assert_int_eq(i2, s21_i2);
    ck_assert_int_eq(r1, s21_r1);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  char str1[1000];
  char str2[1000];
  int r1 = sprintf(str1, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
  2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234, 2345.4234,
  5, 23456.4324, 9, 234567.43242, 0.0000034);
  int r2 = s21_sprintf(str2, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
  2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234, 2345.4234,
  5, 23456.4324, 9, 234567.43242, 0.0000034);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
  char str1[1000];
  char str2[1000];
  int r1 =
  sprintf(str1, "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
  43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5 , 111.432534243243242, 4324.43242,
  25, -3213.43242, 16, -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
  int r2 =
  s21_sprintf(str2, "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
  43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5 , 111.432534243243242, 4324.43242,
  25, -3213.43242, 16, -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

//!!!
START_TEST(sprintf_simple_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "This is a simple value %d";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_precise_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.5i";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_width_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%5d";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_minus_width_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-5i";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_plus_width_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%+12d";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_padding_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%012i";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_star_width_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%0*d";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, 5, val), sprintf(str2, format, 5, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_star_precision_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%0.*i";
    int val = 69;
    ck_assert_int_eq(s21_sprintf(str1, format, 5, val), sprintf(str2, format, 5, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_many_flags_many_ints) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char format[] = "%0.*i %d %4.*i %013d %d";
    int val = 69;
    ck_assert_int_eq(
        s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
        sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_flags_long_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%+5.31li";
    long int val = 698518581899;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_flags_short_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-16.9hi";
    short int val = 6958;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_flags_another_long_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%0.*ld";
    long val = 8581385185;
    ck_assert_int_eq(s21_sprintf(str1, format, 5, val), sprintf(str2, format, 5, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_zero_precision_zero_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.0d";
    int val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_space_flag_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "% d";
    int val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%15u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-16u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.51u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_many_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "% 5.51u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_short) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%hu";
    unsigned short int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_long) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%lu";
    unsigned long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_val_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%lu, %u, %hu, %.5u, %5.u";
    unsigned long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
    sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
    (unsigned)14414, (unsigned)9681));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%15o";
    int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-16o";
    int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.51o";
    int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_many_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-5.51o";
    int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%o";
    ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_hash) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#o";
    int val = 57175;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_short) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%hd";
    short int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_long) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%lo";
    long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%lo, %o, %ho, %.5o, %5.o";
    long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
    sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
    (unsigned)14414, (unsigned)9681));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_octal) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%lo";
    long int val = 84518;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_unsigned_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%u";
    ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, (unsigned)0));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%5x";
    unsigned val = 858158158;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#-10x";
    unsigned val = 858158158;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.15x";
    unsigned val = 858158158;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#-10x%x%X%#x%#X%5.5x";
    unsigned val = 858158158;
    ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
    sprintf(str2, format, val, val, val, val, val, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_many_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#-5.10x";
    unsigned val = 858158158;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#x";
    unsigned val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#x";
    unsigned val = 18571;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_short) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#hx";
    unsigned short val = 12352;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_long) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#lx";
    unsigned long val = 18571757371571;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_one_longer_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#2x";
    unsigned val = 1;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_hex_two_longer_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%#30x";
    unsigned val = 1;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_one_char) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%c";
    char val = 'X';
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST
START_TEST(sprintf_one_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.5c";
    char val = 'c';
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_one_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "% -5c";
    char val = 'c';
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_one_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%15c";
    char val = 'c';
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_one_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
    char val = 'c';
    ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
    sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_one_many_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-5.3c";
    char val = 'c';
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%s";
    char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%.15s";
    char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%15s";
    char *val = "69 IS MY FAVORITE NUMBER";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%-15.9s";
    char *val = "69 IS MY FAVORITE NUMBER";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string_long) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%s";
    char *val =
        "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_ptr) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%p";
    ck_assert_int_eq(s21_sprintf(str1, format, format), sprintf(str2, format, format));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_ptr_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "%15p";
    ck_assert_int_eq(s21_sprintf(str1, format, format), sprintf(str2, format, format));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_string_width_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *val = "kjafdiuhfjahfjdahf";
    char *format = "%120s";
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_n_specifier) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    int ret = 0;
    char *format = "Hello, my sexy little aboba abobushka abobina %n";
    ck_assert_int_eq(s21_sprintf(str1, format, &ret), sprintf(str2, format, &ret));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%Lf";
    long double val = 513515.131513515151351;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%10Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.0Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_empty) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_huge_negative) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Lf";
    long double val = -15.35581134;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%Lf";
    long double val = 72537572375.1431341;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "% f";
    float val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "% .0f %.lf %Lf %f %lf %Lf";
    float val = 0;
    double val1 = 0;
    long double val2 = 3515315.153151;
    float val3 = 5.5;
    double val4 = 9851.51351;
    long double val5 = 95919539159.53151351131;
    ck_assert_int_eq(
        s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
        sprintf(str2, format, val, val1, val2, val3, val4, val5));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.17Le";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_precision_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.0Le";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_precision_empty) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.Le";
    long double val = 15.000009121;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST
START_TEST(sprintf_e_precision_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Le";
    long double val = 0.000000000000000123;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_precision_huge_negative) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Le";
    long double val = -15.35581134;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%Le";
    long double val = 72537572375.1431341;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%015E";
    float val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%15e";
    float val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_e_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "% .0e %.le %Le %e %le %Le";
    float val = 0;
    double val1 = 0;
    long double val2 = 3515315.153151;
    float val3 = 5.5;
    double val4 = 0.094913941;
    long double val5 = 95919539159.53151351131;
    ck_assert_int_eq(
        s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
        sprintf(str2, format, val, val1, val2, val3, val4, val5));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_all_empty) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_empty_format_and_parameters) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_char) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_char) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
    sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_string) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"), sprintf(str2,
    "%s", "Drop Sega PLS"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_string) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
        sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_dec) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_dec) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
    sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_int) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
    sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_float) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001), sprintf(str2, "%f", 0.0001));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_float) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(
        s21_sprintf(str1, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
        sprintf(str2, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_unsigned_dec) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, "%u", 100), sprintf(str2, "%u", (unsigned)100));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_unsigned_dec) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100), sprintf(str2,
    "%u%u%u%u", (unsigned)999, (unsigned)0, (unsigned)666, (unsigned)100));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_char_with_alignment_left) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_char_with_alignment_right) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'), sprintf(str2, "%-8c", '\t'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_char_with_alignment) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
        sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

    ck_assert_str_eq(str1, str2);
} END_TEST

// START HEX TEST
START_TEST(sprintf_test_one_hex_lower) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN), sprintf(str2, "%x", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%x", 0), sprintf(str2, "%x", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX), sprintf(str2, "%x", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN), sprintf(str2, "%X", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%X", 0), sprintf(str2, "%x", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX), sprintf(str2, "%X", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_lower) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123),
        sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_upper) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123),
        sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123));
    ck_assert_str_eq(str1, str2);
} END_TEST
// END HEX TEST

// START HEX WITH ALIGNMENT
START_TEST(sprintf_test_one_hex_lower_with_alignment_left) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN), sprintf(str2,
    "%-3x", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0), sprintf(str2, "%-3x", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX), sprintf(str2, "%-3x", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_lower_with_alignment_right) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN), sprintf(str2,
    "%13x", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%13x", 0), sprintf(str2, "%13x", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX), sprintf(str2, "%13x", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_alignment_left) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN), sprintf(str2, "%-60X",
    (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0), sprintf(str2, "%-60X", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX), sprintf(str2, "%-60X",
    INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_alignment_right) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
    sprintf(str2, "%7X", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%7X", 0), sprintf(str2, "%7X", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX), sprintf(str2,
    "%7X", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_lower_with_alignment) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999),
        sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_upper_with_alignment) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    ck_assert_int_eq(
        s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999),
        sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999));
    ck_assert_str_eq(str1, str2);
} END_TEST
// START HEX WITH ALIGNMENT

// START HEX TEST WITH #
START_TEST(sprintf_test_one_hex_with_hashtag) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN), sprintf(str2, "%#x", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%#x", 0), sprintf(str2, "%#x", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX), sprintf(str2, "%#x", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_hashtag) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN), sprintf(str2, "%#X", (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%#X", 0), sprintf(str2, "%#X", 0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX), sprintf(str2, "%#X", INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_lower_with_hashtag_and_alignm) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535,
    -13, -0, 123213123), sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13,
    -0, 123213123));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_upper_with_hashtag_and_alignm) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535,
    -13, -0, 123213123), sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13,
    -0, 123213123));
    ck_assert_str_eq(str1, str2);
} END_TEST
// END HEX TEST WITH #

// START HEX TEST with width *
START_TEST(sprintf_test_one_hex_lower_with_width_star) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN), sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);

    ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0), sprintf(str2, "%*x", 11, 0));
    ck_assert_str_eq(str1, str2);

    ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX), sprintf(str2, "%*x", 11, INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_width_star) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN), sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
    ck_assert_str_eq(str1, str2);

    ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0), sprintf(str2, "%*X", 11, 0));
    ck_assert_str_eq(str1, str2);

    ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX), sprintf(str2, "%*X", 11, INT32_MAX));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_lower_with_width_star_and_align_and_hashtag) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0,
    -1, 199, -123978, 3, -1251), sprintf(str2, "%#*x%*x%-12x%3x%*x", 9,
    127312897, -0, -1, 199, -123978, 3, -1251));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_upper_with_width_star) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0,
    -1, 199, -123978, 3, -1251), sprintf(str2, "%#*X%*X%-12X%3X%*X", 9,
    127312897, 0, -1, 199, -123978, 3, -1251));
    ck_assert_str_eq(str1, str2);
} END_TEST
// END HEX TEST WITH Width *

// START HEX TEST WITH precision
START_TEST(sprintf_test_one_hex_lower_with_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    int a = s21_sprintf(str1, "%*.6x", 11, 0);
    int b = sprintf(str2, "%*.6x", 11, 0);
    ck_assert_int_eq(a, b);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
    int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
    ck_assert_int_eq(a, b);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_lower_with_precision_and_other) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    int a = s21_sprintf(
        str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
        4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
    int b = sprintf(
        str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
        4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
    ck_assert_int_eq(a, b);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_many_hex_upper_with_precision_and_other) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(
        s21_sprintf(str1,
                    "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
                    -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                    41, -41, 33),
        sprintf(str2, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
                -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
                -41, 33));
    ck_assert_str_eq(str1, str2);
} END_TEST
// END HEX TEST WITH precision

// START HEX TEST WITH Length
START_TEST(sprintf_test_one_hex_lower_with_length) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%hx", (unsigned short)11), sprintf(str2, "%hx", (unsigned short)11));
    ck_assert_str_eq(str1, str2);
    long unsigned int val = INT32_MAX;
    ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
    ck_assert_str_eq(str1, str2);
    long unsigned int v = 0;
    ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_one_hex_upper_with_length) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    ck_assert_int_eq(s21_sprintf(str1, "%hx", (unsigned short)-11),
    sprintf(str2, "%hx", (unsigned short)-11));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%hx", (unsigned short)0), sprintf(str2, "%hx", (unsigned short)0));
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(s21_sprintf(str1, "%hx", (unsigned short)11), sprintf(str2, "%hx", (unsigned short)11));
    ck_assert_str_eq(str1, str2);
    long unsigned int val = INT32_MAX;
    ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
    ck_assert_str_eq(str1, str2);
    long unsigned int v = 0;
    ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf1) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%10ld";

    ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf2) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%1.1f";

    ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf3) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%8.3c";

    ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf4) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%+5.5d aboba";

    int val = 10000;
    int a = s21_sprintf(str1, format, val);
    int b = sprintf(str2, format, val);
    ck_assert_int_eq(a, b);

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf6) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%7.7f";

    ck_assert_int_eq(s21_sprintf(str1, format, 11.123456), sprintf(str2, format, 11.123456));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf7) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%7.4s";

    ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"), sprintf(str2, format, "aboba floppa"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf8) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%6.6u";

    ck_assert_int_eq(s21_sprintf(str1, format, 12341151), sprintf(str2, format, 12341151));
    ck_assert_str_eq(str1, str2);

    long long unsigned int val = 12341151;
    ck_assert_int_eq(s21_sprintf(str1, "%6.6llu", val), sprintf(str2, "%6.6llu", val));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf9) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%li%ld%lu";

    ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
    sprintf(str2, format, 666666666666, 777, 111));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf10) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%hi%hd%hu";

    ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111), sprintf(str2, format,
    666, -777, 111));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf12) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%-11.11li%-35.5lu%-3.5ld%33.19Lf";
    long double k = 333.33213;

    ck_assert_int_eq(
        s21_sprintf(str1, format, 66666666666, 5555555555, 44444444444, k),
        sprintf(str2, format, 66666666666, 5555555555, 44444444444, k));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf14) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";

    ck_assert_int_eq(
        s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
        sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf16) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "% c";

    ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf18) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "% s% c";

    ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'), sprintf(str2, format, "", 'f'));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf19) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%210s";

    ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
    sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf20) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%-115s";

    ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"), sprintf(str2, format, "Nick her"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf25) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.f";

    ck_assert_int_eq(s21_sprintf(str1, format, 121.123), sprintf(str2, format, 121.123));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf26) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%%";

    ck_assert_int_eq(s21_sprintf(str1, format), sprintf(str2, format));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf27) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%%%%%%%%";

    ck_assert_int_eq(s21_sprintf(str1, format), sprintf(str2, format));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf28) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    int n1;
    int n2;
    int a = s21_sprintf(str1, "%d%n", 123, &n1);
    int b = sprintf(str2, "%d%n", 123, &n2);

    ck_assert_int_eq(a, b);
    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf29) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%-.f";

    ck_assert_int_eq(s21_sprintf(str1, format, 111.111), sprintf(str2, format, 111.111));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf30) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%-.1d";

    ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf31) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%e";
    double x = 111;
    ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf32) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%e%e%e%e";

    ck_assert_int_eq(
        s21_sprintf(str1, format, 11.111, 222.2222, 666., -555.125),
        sprintf(str2, format, 11.111, 222.2222, 666., -555.125));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf33) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%Le";
    long double x = 122.1231;

    ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf35) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.10e";

    ck_assert_int_eq(s21_sprintf(str1, format, 111.184314818), sprintf(str2, format, 111.184314818));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf36) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%5.3e%3.2e%lf";

    ck_assert_int_eq(s21_sprintf(str1, format, 0.000111, 111.555, 1.999),
    sprintf(str2, format, 0.000111, 111.555, 1.999));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf37) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%E";

    ck_assert_int_eq(s21_sprintf(str1, format, 0.666666), sprintf(str2, format, 0.666666));
    ck_assert_str_eq(str1, str2);

    ck_assert_int_eq(s21_sprintf(str1, format, 1.1e+123), sprintf(str2, format, 1.1e+123));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf38) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%E%E%E";

    ck_assert_int_eq(s21_sprintf(str1, format, 0.0000999, 111.9999, 6.666),
    sprintf(str2, format, 0.0000999, 111.9999, 6.666));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf39) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%e ABOBA %Lf %Lf %Le";
    long double c = 848181;
    long double a = 0.00000001;
    long double b = 1111111.11;
    ck_assert_int_eq(s21_sprintf(str1, format, 123.123, a, b, c),
    sprintf(str2, format, 123.123, a, b, c));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf40) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%#e Floppa %#E%#f";

    ck_assert_int_eq(s21_sprintf(str1, format, 123.111, 0.0000999, 0.555),
    sprintf(str2, format, 123.111, 0.0000999, 0.555));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf41) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.Lf";
    long double a = 7.9418438184;

    ck_assert_int_eq(s21_sprintf(str1, format, a), sprintf(str2, format, a));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf42) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%#5p";
    int a = 5;
    ck_assert_int_eq(s21_sprintf(str1, format, &a), sprintf(str2, format, &a));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf43) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.5o";

    ck_assert_int_eq(s21_sprintf(str1, format, 12345), sprintf(str2, format, 12345));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_test_sprintf44) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%#5lX";
    long hex = 314818438141;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_trailing_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 0.50300;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_large) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 5131.43141;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_small) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 0.123000;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.5g";
    double hex = 0.123000;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_precision_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.0g";
    double hex = 0.123000;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_precision_missing) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.g";
    double hex = 0.123000;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_many_zeroes_in_front) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.g";
    double hex = 0.0004;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);

    hex = 0.004;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);

    hex = 0.04;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_one_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%.5g";
    double hex = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_mantiss) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 0.0000005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_mantiss_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%5.8g";
    double hex = 0.0000005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_short_no_mantiss) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%g";
    double hex = 0.005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_LG) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%LG";
    long double hex = 0.000005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);

    hex = 0.00005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);

    hex = 0.0005;
    ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_g_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char format[] = "%LG %g %G %Lg %.5g";
    long double hex = 0.000005;
    double hex1 = 41.1341;
    double hex2 = 848.9000;
    long double hex3 = 0.0843;
    double hex4 = 0.0005;
    double hex5 = 0.8481481;
    ck_assert_int_eq(
        s21_sprintf(str1, format, hex, hex1, hex2, hex3, hex4, hex5),
        sprintf(str2, format, hex, hex1, hex2, hex3, hex4, hex5));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_width_char) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    char *format = "This is a simple wide char %5c";
    char w = 'c';
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}

Suite* s21_sprintf_suite(void) {
    Suite* s = suite_create("s21_sprintf Unit Tests");
    TCase* tc_s21_sprintf = tcase_create("s21_sprintf");

    tcase_add_test(tc_s21_sprintf, test_sprintf_d);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test);
    tcase_add_test(tc_s21_sprintf, test_sprintf_s);
    tcase_add_test(tc_s21_sprintf, test_sprintf_random);
    tcase_add_test(tc_s21_sprintf, test_sprintf_u);
    tcase_add_test(tc_s21_sprintf, test_sprintf_i);
    tcase_add_test(tc_s21_sprintf, test_sprintf_accur);
    tcase_add_test(tc_s21_sprintf, test_sprintf_width);
    tcase_add_test(tc_s21_sprintf, test_sprintf_p);
    tcase_add_test(tc_s21_sprintf, test_sprintf_flag);
    tcase_add_test(tc_s21_sprintf, test_sprintf_f);
    tcase_add_test(tc_s21_sprintf, test_sprintf_e);
    tcase_add_test(tc_s21_sprintf, test_sprintf_g);
    tcase_add_test(tc_s21_sprintf, test_sprintf_c);
    tcase_add_test(tc_s21_sprintf, test_sprintf_x);
    tcase_add_test(tc_s21_sprintf, test_sprintf_o);
    tcase_add_test(tc_s21_sprintf, s21_chars_f);
    tcase_add_test(tc_s21_sprintf, s21_nums_f);
    tcase_add_test(tc_s21_sprintf, s21_nums2_f);
    tcase_add_test(tc_s21_sprintf, s21_nums3_f);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test1);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test2);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test3);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test4);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_d);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_i);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_c);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_e);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_E);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_f);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_o);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_x);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_X);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_u);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_s);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_p);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_percent);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_g);
    tcase_add_test(tc_s21_sprintf, s21_sprintf_test_G);
    tcase_add_test(tc_s21_sprintf, test_sprintf_n);
    tcase_add_test(tc_s21_sprintf, sprintf_simple_int);
    tcase_add_test(tc_s21_sprintf, sprintf_precise_int);
    tcase_add_test(tc_s21_sprintf, sprintf_width_int);
    tcase_add_test(tc_s21_sprintf, sprintf_minus_width_int);
    tcase_add_test(tc_s21_sprintf, sprintf_plus_width_int);
    tcase_add_test(tc_s21_sprintf, sprintf_padding_int);
    tcase_add_test(tc_s21_sprintf, sprintf_star_width_int);
    tcase_add_test(tc_s21_sprintf, sprintf_star_precision_int);
    tcase_add_test(tc_s21_sprintf, sprintf_many_flags_many_ints);
    tcase_add_test(tc_s21_sprintf, sprintf_flags_long_int);
    tcase_add_test(tc_s21_sprintf, sprintf_flags_short_int);
    tcase_add_test(tc_s21_sprintf, sprintf_flags_another_long_int);
    tcase_add_test(tc_s21_sprintf, sprintf_zero_precision_zero_int);
    tcase_add_test(tc_s21_sprintf, sprintf_space_flag_int);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_width);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_many_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_short);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_long);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_val_many);

    tcase_add_test(tc_s21_sprintf, sprintf_octal_width);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_many_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_short);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_long);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_many);
    tcase_add_test(tc_s21_sprintf, sprintf_octal);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_octal_hash);
    tcase_add_test(tc_s21_sprintf, sprintf_unsigned_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_width);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_many);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_many_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_short);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_long);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_one_longer_width);
    tcase_add_test(tc_s21_sprintf, sprintf_hex_two_longer_width);
    tcase_add_test(tc_s21_sprintf, sprintf_one_char);
    tcase_add_test(tc_s21_sprintf, sprintf_one_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_one_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_one_width);
    tcase_add_test(tc_s21_sprintf, sprintf_one_many);
    tcase_add_test(tc_s21_sprintf, sprintf_one_many_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_string);
    tcase_add_test(tc_s21_sprintf, sprintf_string_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_string_width);
    tcase_add_test(tc_s21_sprintf, sprintf_string_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_string_long);
    tcase_add_test(tc_s21_sprintf, sprintf_ptr);
    tcase_add_test(tc_s21_sprintf, sprintf_ptr_width);
    tcase_add_test(tc_s21_sprintf, sprintf_n_specifier);
    tcase_add_test(tc_s21_sprintf, sprintf_string_width_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_float_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_float_width);
    tcase_add_test(tc_s21_sprintf, sprintf_float_precision_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_float_precision_empty);
    tcase_add_test(tc_s21_sprintf, sprintf_float_precision_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_float_precision_huge_negative);
    tcase_add_test(tc_s21_sprintf, sprintf_float_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_float_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_float_many);
    tcase_add_test(tc_s21_sprintf, sprintf_e_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_e_precision_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_e_precision_empty);
    tcase_add_test(tc_s21_sprintf, sprintf_e_precision_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_e_precision_huge_negative);
    tcase_add_test(tc_s21_sprintf, sprintf_e_huge);
    tcase_add_test(tc_s21_sprintf, sprintf_e_many);
    tcase_add_test(tc_s21_sprintf, sprintf_e_width);
    tcase_add_test(tc_s21_sprintf, sprintf_e_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_all_empty);
    tcase_add_test(tc_s21_sprintf, sprintf_empty_format_and_parameters);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_char);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_char);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_string);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_string);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_dec);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_dec);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_int);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_int);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_float);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_float);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_unsigned_dec);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_unsigned_dec);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_char_with_alignment_left);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_char_with_alignment_right);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_char_with_alignment);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_lower);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_upper);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower_with_alignment_left);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower_with_alignment_right);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_alignment_left);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_alignment_right);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_lower_with_alignment);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_upper_with_alignment);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_with_hashtag);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_hashtag);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_lower_with_hashtag_and_alignm);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_upper_with_hashtag_and_alignm);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower_with_width_star);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_width_star);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_lower_with_width_star_and_align_and_hashtag);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_upper_with_width_star);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower_with_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_lower_with_precision_and_other);
    tcase_add_test(tc_s21_sprintf, sprintf_test_many_hex_upper_with_precision_and_other);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_lower_with_length);
    tcase_add_test(tc_s21_sprintf, sprintf_test_one_hex_upper_with_length);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf1);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf2);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf3);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf4);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf6);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf7);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf8);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf9);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf10);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf12);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf14);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf16);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf18);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf19);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf20);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf25);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf28);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf29);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf30);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf31);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf32);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf33);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf35);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf36);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf37);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf38);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf39);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf40);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf41);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf42);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf43);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf44);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf26);
    tcase_add_test(tc_s21_sprintf, sprintf_test_sprintf27);
    tcase_add_test(tc_s21_sprintf, sprintf_g_trailing_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_g_large);
    tcase_add_test(tc_s21_sprintf, sprintf_g_small);
    tcase_add_test(tc_s21_sprintf, sprintf_g_precision);
    tcase_add_test(tc_s21_sprintf, sprintf_g_precision_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_g_precision_missing);
    tcase_add_test(tc_s21_sprintf, sprintf_g_many_zeroes_in_front);
    tcase_add_test(tc_s21_sprintf, sprintf_g_one_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_g_mantiss);
    tcase_add_test(tc_s21_sprintf, sprintf_g_mantiss_flags);
    tcase_add_test(tc_s21_sprintf, sprintf_g_short_no_mantiss);
    tcase_add_test(tc_s21_sprintf, sprintf_LG);
    tcase_add_test(tc_s21_sprintf, sprintf_g_many);
    tcase_add_test(tc_s21_sprintf, sprintf_g_zero);
    tcase_add_test(tc_s21_sprintf, sprintf_width_char);
    suite_add_tcase(s, tc_s21_sprintf);

    return s;
}
