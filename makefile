.PHONY:all
all: 01.out 02.out

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

.PHONY:01
02: 02.out
	./$< < 02.txt

.PHONY:01s
02s: 02.out
	./$< < 02Short.txt