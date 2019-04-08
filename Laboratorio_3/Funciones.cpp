#include "Funciones.h"

double Provector(int servicio, int tam, double vec[]){

	if(servicio==1){
		double resultado=0;
		int var =0;
		float valor=0;
		for(var=0;var<=tam;var++){
			valor+=vec[var];
		}
		resultado=valor/(tam+1);
		return resultado;
	}	
}


double Desviacionvector(int servicio, int tam, double vec[]){

	if(servicio==2){
		float media=0;
		double resultado;
		int var =0;
		float valor=0;
		for(var=0;var<=tam;var++){
			valor+=vec[var];
		}
		media=valor/(tam+1);
		double rango=0, desviacion=0;
		float varianza=0;
		int i=0;

		for(i = 0 ; i <= tam; i++){
   			rango=0;
   			rango = pow(vec[i] - media,2);
   			varianza = varianza + rango;
  		}
  		varianza = varianza / (tam+1);
  		desviacion = sqrt(varianza);
  		return desviacion;

	}	
	
}

double Matrizordenada(int servicio, int numfilas, int numcolumnas, int columna, double matriz[][]){

	printf("%d\n", numfilas);
	printf("%d\n", numcolumnas);

	for(int i=0;i<numfilas;i++){
		for(int h=0;h<numcolumnas;h++){
			std::cout<<"  "<<matriz[i][h];
		}
		std::cout<<std::endl;
	}

}