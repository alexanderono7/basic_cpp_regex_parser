# Alexander Ono
# amono1@asu.edu
# SID: 1214959876
# CSE340 - Dr. Bazzi
# Project #1 - Regex Parser
# 9/24/2022

.SILENT:
build:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc regex.cc -o a.out 

all:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc regex.cc -o a.out 
	bash ./test1.sh

one:
	# Testing just one directory of test cases (you need to change test2.sh manually, by the way).
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc regex.cc -o a.out 
	bash ./test2.sh
	
foo = ./inputs.txt
def:
	# default, literally 1 test case (defined in inputs.txt)
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc regex.cc -o a.out 
	cat ./inputs.txt
	printf "\n\n"
	./a.out < $(foo)

reg:
	# testing regex files
	g++ -std=c++11 -g -ggdb -Wall regex.cc -o a.out 

clean:
	rm a.out