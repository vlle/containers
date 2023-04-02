CC := g++

.PHONY: all 
all: test

hello_test:
	cmake -S . -B build/
	make -C build/

.PHONY: test
test: hello_test
	./build/hello_test

.PHONY: leak
leak: hello_test
	leaks -atExit -- ./build/hello_test

.PHONY: clean
clean:
	@-rm -rf *.o *.a *.gcno *.gcda *.info test report

.PHONY: gcov_report
gcov_report:
	@$(CC) $(COVERAGE) $(CFLAGS) tests/main_test.cc -o test $(TFLAGS)
	@./test
	@lcov -t "test" -c -d ./ --no-external -o ./coverage.info
	@genhtml -o ./report/ ./coverage.info
	@open ./report/index.html

.PHONY: style
style:
	@clang-format -style=Google -n tests/*.cc *.h
	@clang-format -style=Google -i tests/*.cc *.h
