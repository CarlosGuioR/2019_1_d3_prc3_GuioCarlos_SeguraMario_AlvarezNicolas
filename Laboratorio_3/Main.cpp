#include "Funciones.h"

int main(int argc, char const *argv[])
{
	
	int servicio1 = 1;
	int tam = 6;
	double vector[] = {1,5,1,2,3,4,5};	

	//std::cout<<Provector(servicio1, tam, vector);
	//std::cout<<""<<std::endl;

	int servicio2 = 2;

	
	//std::cout<<Desviacionvector(servicio2, tam, vector);
	//std::cout<<""<<std::endl;

	int servicio3=3;

	int numfilas = 2; 
	int numcolumnas = 2; 
	int columna = 1;
	double matriz[][] = {{1,2},{3,4}};;

	Matrizordenada(servicio3, numfilas, numcolumnas, columna, matriz[][]);

	return 0;
}