CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    CHECK=-lcheck -L.
	#LEAK=leaks -atExit -- ./a.out
	HTML_CREATE=lcov -t a.out -o report.info -c -d .; genhtml -o report report.info
else
    CHECK=-lcheck -lm -lsubunit -lrt -lpthread -L. #-L/usr/lib -L/usr/local/lib 
	#LEAK=valgrind -q --track-origins=yes ./a.out
	HTML_CREATE=gcov -b -l -p -c s21_string.gcno; gcovr -g -k -r . --html --html-details -o report.html; mv report.s21_string.c.html report.html
	
endif

all: clean s21_string.a test gcov_report

rebuild: clean all

test: clean s21_string.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o s21_string_test_new.o
	$(CC) $(CFLAGS) main.c s21_string.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o s21_string_test_new.o $(CHECK)
	./a.out

clean:
	rm -rf *.g* report.* *.out *.o ./report s21_string.a *.txt *.cfg

s21_string.o:
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_sscanf_tests.o:
	$(CC) $(CFLAGS) -c s21_sscanf_tests.c -o s21_sscanf_tests.o

s21_sprintf_tests.o:
	$(CC) $(CFLAGS) -c s21_sprintf_tests.c -o s21_sprintf_tests.o

s21_string_tests.o:
	$(CC) $(CFLAGS) -c s21_string_tests.c -o s21_string_tests.o

s21_string_test_new.o:
	$(CC) $(CFLAGS) -c s21_string_test_new.c -o s21_string_test_new.o

s21_string.a: clean 
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o
	ar rc s21_string.a s21_string.o
	ranlib s21_string.a

valgrind: rebuild
	$(CC) $(CFLAGS) -g main.c s21_string.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o s21_string_test_new.o $(CHECK)
	valgrind -q --log-file=RESULT_VALGRIND.txt ./a.out
	cat RESULT_VALGRIND.txt

gcov_report: clean
	gcc $(CFLAGS) --coverage -c s21_string.c -o s21_string.o
	gcc $(CFLAGS) --coverage -c s21_sscanf_tests.c -o s21_sscanf_tests.o
	gcc $(CFLAGS) --coverage -c s21_sprintf_tests.c -o s21_sprintf_tests.o
	gcc $(CFLAGS) --coverage -c s21_string_tests.c -o s21_string_tests.o
	gcc $(CFLAGS) --coverage -c s21_string_test_new.c -o s21_string_test_new.o
	gcc $(CFLAGS) --coverage main.c s21_string.o s21_string_test_new.o s21_sscanf_tests.o s21_sprintf_tests.o s21_string_tests.o $(CHECK)
	./a.out
	gcov -b -l -p -c s21_string.gcno; gcovr -g -k -r . --html --html-details -o report.html
