CFLAGS=-Wall

poker-cli: src/*.c
	gcc $(CFLAGS) src/main.c -o poker-cli

.PHONY: unit-test
unit-test:
	gcc $(CFLAGS) tests/test.c -o test
	./test

.PHONY: sort-test
sort-test:
	make poker-cli 
	bash ./tests/sort-test.sh

.PHONY: clean
clean:
	rm poker-cli test