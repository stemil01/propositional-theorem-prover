prover: run main.o tree.o well_formed.o
	g++ -Wall run/main.o run/tree.o run/well_formed.o

run:
	mkdir -p run

main.o: main.cpp
	g++ -c main.cpp -o run/main.o

tree.o: tree.hpp tree.cpp
	g++ -c tree.cpp -o run/tree.o

well_formed.o: well_formed.hpp well_formed.cpp
	g++ -c well_formed.cpp -o run/well_formed.o
