.PHONY: all clean test $(SOURCENAME).a

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TFLAGS = -lgtest -pthread
COVERAGE = --coverage
SOURCENAME = s21_vector

all: $(SOURCENAME).a test

$(SOURCENAME).a: $(SOURCENAME).h
	@$(CC) $(CFLAGS) -c $(SOURCENAME).cc
	@ar rc $(SOURCENAME).a $(SOURCENAME).o
	@ranlib $(SOURCENAME).a
	@rm $(SOURCENAME).o

test:
	@$(CC) $(CFLAGS) tests/main_test.cc -o test $(TFLAGS)
	@./test

clean:
	@-rm -rf *.o *.a *.txt *.gcno *.gcda *.info test report

gcov_report:
	@$(CC) $(COVERAGE) $(CFLAGS) tests/main_test.cc -o test $(TFLAGS)
	@./test
	@lcov -t "test" -c -d ./ --no-external -o ./coverage.info
	@genhtml -o ./report/ ./coverage.info
	@open ./report/index.html

style:
	@clang-format -style=google -n tests/*.cc *.h
	@clang-format -style=google -i tests/*.cc *.h
