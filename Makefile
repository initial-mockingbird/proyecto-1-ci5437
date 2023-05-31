IDA-Spin: ./src/algorithms/IDA.cpp ./src/top-spin/topspin12-4.c ./src/main.cpp
	 g++ ./src/algorithms/IDA.cpp ./src/main.cpp -include ./src/top-spin/topspin12-4.c -std=c++20 -o main.o

A_star-Spin: ./src/algorithms/A_star/* ./src/solvers/top-spin/A_star/main_a.cpp
	 g++ ./src/algorithms/A_star/A_star.cpp ./src/top-spin/topspin12-4.hpp ./src/solvers/top-spin/A_star/main_a.cpp  -std=c++20 -o main_a.o