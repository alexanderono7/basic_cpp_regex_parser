.SILENT:
build:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc regex.cc -o a.out 

all:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 
	bash ./test1.sh

one:
	# Testing just one directory of test cases (you need to change test2.sh manually, by the way).
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 
	bash ./test2.sh
	
foo = ./inputs.txt
def:
	# default, literally 1 test case (defined in inputs.txt)
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 
	cat ./inputs.txt
	printf "\n\n"
	./a.out < $(foo)

reg:
	# testing regex files
	g++ -std=c++11 -g -ggdb -Wall regex.cc -o a.out 

clean:
	rm a.out