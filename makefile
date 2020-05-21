main:Polynomial.o Polynomial.h Manage.o  Manage.h main.o
	g++ Polynomial.o Polynomial.h Manage.o Manage.h main.cpp -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
Polynomial.o:Polynomial.cpp
	g++ -c Polynomial.cpp -o Polynomial.o
Manage.o:Manage.cpp
	g++ -c Manage.cpp -o Manage.o
clean:
	rm *.o
	rm main

