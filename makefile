.PHONY:all
all: 01.out 02.out 03.out 04.out 05.out 06.out 07.out 08.out

.PHONY:run_all
run_all: 01 02 03 04 05 06 07

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

05.out: 05.cpp
	g++ $< -o $@

05: 05.out
	./$< < 05.txt

05s: 05.out
	./$< < 05Short.txt

06.out: 06.cpp
	g++ $< -o $@

06: 06.out
	./$< < 06.txt

06s: 06.out
	./$< < 06Short.txt

07.out: 07.cpp
	g++ $< -o $@

07: 07.out
	./$< < 07.txt

07s: 07.out
	./$< < 07Short.txt

08.out: 08.cpp
	g++ $< -o $@ -std=c++23

08: 08.out
	./$< < 08.txt

08s: 08.out
	./$< < 08Short.txt

09.out: 09.cpp
	g++ $< -o $@ -std=c++23

09: 09.out
	./$< < 09.txt

09s: 09.out
	./$< < 09Short.txt
