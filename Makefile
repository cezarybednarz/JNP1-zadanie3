all:
	g++ --std=c++17 -Wall -c fibo.cc -o fibo.o
	g++ --std=c++17 -c main.cc
	g++ fibo.o main.o -o main