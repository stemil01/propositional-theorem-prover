prover: run main.o tree.o well_formed.o tableaux.o latex.o
	g++ -Wall run/main.o run/tree.o run/well_formed.o run/tableaux.o run/latex.o

run:
	mkdir -p run

main.o: main.cpp
	g++ -c -Wall main.cpp -o run/main.o

tree.o: tree.hpp tree.cpp
	g++ -c -Wall tree.cpp -o run/tree.o

well_formed.o: well_formed.hpp well_formed.cpp
	g++ -c -Wall well_formed.cpp -o run/well_formed.o

tableaux.o: tableaux.hpp tableaux.cpp
	g++ -c -Wall tableaux.cpp -o run/tableaux.o

latex.o: latex.hpp latex.cpp
	g++ -c -Wall latex.cpp -o run/latex.o