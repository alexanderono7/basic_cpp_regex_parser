build:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 

all:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 
	bash ./test1.sh

one:
	g++ -std=c++11 -g -ggdb -Wall inputbuf.cc lexer.cc parser.cc -o a.out 
	bash ./test2.sh

clean:
	rm a.out