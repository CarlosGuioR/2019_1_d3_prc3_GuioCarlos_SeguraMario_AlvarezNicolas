

servidor: Servidor.o 
#   g++ std=c++11 -o main lab2.cpp Bank.cpp Cliente.cpp Cuenta.cpp
	g++ -o servidor Servidor.o -lrt -pthread -w

Servidor.o: Servidor.cpp 
	g++ -c -o Servidor.o Servidor.cpp -lrt -pthread -w

run: servidor
	./servidor

.PHONY: clear
clean:
	rm *.o servidor