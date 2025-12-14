.PHONY:all
all: 01.out 02.out

.PHONY:clean
clean:
	rm *.out

01.out: 01.cpp
	g++ $< -o $@

.PHONY:01
01: 01.out
	./$< < 01.txt

.PHONY:01s
01s: 01.out
	./$< < 01Short.txt

02.out: 02.cpp
	g++ $< -o $@

.PHONY:02
02: 02.out
	./$< < 02.txt

.PHONY:02s
02s: 02.out
	./$< < 02Short.txt

03.out: 03.cpp
	g++ $< -o $@

.PHONY:03
03: 03.out
	./$< < 03.txt

.PHONY:03s
03s: 03.out
	./$< < 03Short.txt

04.out: 04.cpp
	g++ $< -o $@

04: 04.out
	./$< < 04.txt

04s: 04.out
	./$< < 04Short.txt