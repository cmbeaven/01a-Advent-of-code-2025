.PHONY:all
all: 01a.out

01a.out: main.cpp
	g++ main.cpp -o $@

.PHONY:run
run: 01a.out
	./01a.out < input.txt

.PHONY:run_short
run_short: 01a.out
	./01a.out < shortInput.txt