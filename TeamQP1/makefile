FLAGS = -std=c++11

P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ $(FLAGS) -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ $(FLAGS) -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ $(FLAGS) -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ $(FLAGS) -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ $(FLAGS) -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch *.p1 *.dbg *.lst

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp Dfa.hpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile SetLimits.cpp SetLimits.h README.txt
	rm -rf TeamQP1
	mkdir TeamQP1
	cp Project1.cpp TeamQP1
	cp LexicalAnalyzer.h TeamQP1
	cp LexicalAnalyzer.cpp TeamQP1
	cp Dfa.hpp TeamQP1
	cp SetLimits.cpp TeamQP1
	cp SetLimits.h TeamQP1
	cp SyntacticalAnalyzer.h TeamQP1
	cp SyntacticalAnalyzer.cpp TeamQP1
	cp makefile TeamQP1
	cp README.txt TeamQP1
	tar cfvz TeamQP1.tgz TeamQP1
	cp TeamQP1.tgz ~tiawatts/cs460drop
