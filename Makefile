build:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 

full:
	bash ./test1.sh

clean:
	rm a.out