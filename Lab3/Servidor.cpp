#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h> //shm_open, mmap
#include <unistd.h> //ftruncate
#include <fcntl.h> //defines the shm_open, mmap
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define max 30

using namespace std;

void *hilo_cliente(void *param);
void *otro(void *data);
double cofactor(double det[][max], int orden, int fila, int columna);
double determinante(double matr[][max], int orden);

#define size 80

const int SIZE = 128;
const char *name = "SHMEM_MATH_SERVER_SUBSCRIPTION";
const unsigned char bandera = 0;

int num_tuberia=0;
int numThreads=0;
char myfifo[81];

typedef struct{//creamos una estructura la cual tendra los items de la memoria compartida
	unsigned char bandera;
	char path[81];
	unsigned char salida;
}item;

void scatch(int sig){//funcion que recibe la interrupcion CTRL+C y cierra la memoria compartida

	printf("[P] Servidor cerrado\n");
    shm_unlink(name);//cerramos la memoria compartida
    exit(-1);//salimos del programa
}

int main(int argc, char *argv[])
{
	system("clear");
	signal(SIGINT,&scatch);//activa la funcion de la interrupcion CTRL+C
	int shm_fd=0, espera=0;
	void *ptr;
	item *registro;
	char lista_tuberias[80][80],aja[50];
	int fd, conf=0;

	printf("[P] Iniciando servidor matemático...\n");
	shm_fd = shm_open(name,O_RDONLY, 0666);//preguntamos si existe una memoria compartida con el nombre name
	if(shm_fd==-1){//no existe memoria compartida con el nombre name
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);//creamos la memoria compartida
		ftruncate(shm_fd, SIZE);//reservamos un tamaño SIZE para la memoria
		ptr = mmap(0, SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm_fd, 0);//puntero a la primer posicion de la memoria
		registro = (item*)ptr;//creamos una estructura con el tamaño de la estructura "item" y la llevamos al puntero ptr
		registro->bandera=0;//asignamos un valor de 0 a la bandera de la estructura
		
		while(true){
			espera=0;
			int conf1=0;
			printf("\n[P] Esperando suscripciones.\n");

			while(espera==0){//esperamos a que un cliente se suscriba
				int a=registro->bandera;
				if(a==1){//esperamos a que se suscriba un cliente1;
					break;
				}
			}			conf=0;
			strcpy(myfifo,registro->path);
			for(int i=0;i<81;i++){
				if(registro->path[i]=='\0'){//verificamos que el path introducido por el cliente sea valido
					conf=1;
					break;
				}
			}
			if(conf==0){//si el path es invalido, le informamos al cliente
				printf("[P] Nombre de tubería inválido.\n");
				registro->salida=2;
				conf1=1;
			}else{//path valido;
				
				for(int i=0;i<num_tuberia;i++){
					if(strcmp(lista_tuberias[i],myfifo)==0){
						printf("[P] La tubería ya está suscrita\n");
						conf1=1;
						registro->salida=2;
						break;
					}
				}
				fd=open(myfifo,O_RDONLY);
				if(fd<0){
					close(fd);
					printf("[P] La tuberia %s no existe.\n", myfifo);
					conf1=1;
					registro->salida=2;
				}else{
					close(fd);
					
				}

				if(conf1==0){
					
					registro->salida=1;
					registro->bandera=0;
					printf("[P] Usuario suscrito a la ruta: %s\n",myfifo);
			
					strcpy(lista_tuberias[num_tuberia],myfifo);
					num_tuberia++;
					//printf("# %d",num_tuberia);
					pthread_t tid[30]; //id del hilo
					pthread_attr_t attr[30]; //atributos del hilo
					//inicializar atributos de scheduling del hilo por defecto
					pthread_attr_init(&attr[numThreads]);//pthread_create(id hilo, atributos hilo, void* rutina hilo, void* argumentos rutina)
					pthread_create(&tid[numThreads], &attr[numThreads], &hilo_cliente, myfifo);
					numThreads++;

					//}
				}
				
			}
			registro->bandera=0;
		}
	}
	else{//ya existe una memoria compartida con el nombre "name"
		printf("[P] ERROR: Ya se encuentra un servidor ejecutandose\n");
	}
	shm_unlink(name);//liberamos la memoria con el nombre "name"
	return 0;
}

void *hilo_cliente(void *param){

	int opcion=0, cantidad=0, numhilo=numThreads;	
	char arr1[100], arr2[100];
	int numero[10];
	int fd, fc;
	char mypath[80];
	double datos[100], *mat1, *mat2, *matriz, *result, **matdet;
	double resultado[1];
	strcpy(mypath,(char *)param);
	printf("path: %s\n",mypath);
	mkfifo(myfifo, 0666);
	
	while(1){
		//abrir FIFO en modo escritura
		while(true){

			while(true){
						  
				fd = open(myfifo, O_RDONLY);//leer opcion
				read(fd, numero, sizeof(int));
				opcion=numero[0];
				printf("%d\n",opcion);
				if(opcion==1||opcion==2||opcion==3||opcion==4||opcion==5){
					break;
				}else{
					printf("[P]Opcion incorrecta, intentelo de nuevo.\n");
				}

			}
			if(opcion==1){
				printf("\n[P]Promedio de un vector.\n");
				read(fd, numero, sizeof(int));
				printf("[Cliente %d] Tamaño del vector: %d\n",numhilo,numero[0]);
				cantidad=numero[0];

				
				float valor=0, valor1=0;
				printf("[Cliente %d]Vector:\n",numhilo);
				for(int var=0;var<cantidad;var++){
					read(fd, matriz,sizeof(double));
					datos[var]=matriz[0];
					printf("%f\n",datos[var]);
					valor+=datos[var];
				}
				close(fd);
				resultado[0]=valor/double(cantidad);

				printf("[Cliente %d]Promedio: %f\n",numhilo,resultado);

				fd = open(myfifo, O_WRONLY);//leer opcion
				write(fd, resultado, sizeof(double));
				close(fd);

			}else if(opcion==2){
				printf("\n[P]Desviacion estandar de un vector.\n");
				read(fd, numero, sizeof(int));
				printf("[Cliente %d]Tamaño del vector: %d\n",numhilo,numero[0]);
				cantidad=numero[0];

				double resultado=0,matriz[1];
				float valor=0, valor1=0;
				printf("[Cliente %d]Vector:\n",numhilo);
				for(int var=0;var<cantidad;var++){
					read(fd, matriz,sizeof(double));
					datos[var]=matriz[0];
					printf("%f\n",datos[var]);
					valor+=datos[var];
				}
				close(fd);
				resultado=valor/double(cantidad);

				double rango=0, desviacion[1], varianza=0; 
				for(int i = 0 ; i < cantidad; i++){
		   			rango=0;
		   			rango = pow(datos[i] - resultado,2);
		   			varianza += rango;
		  		}
		  		varianza = varianza / double(cantidad);
		  		desviacion[0] = sqrt(varianza);
				
				printf("[Cliente %d]Desviacion estandar: %f \n",numhilo,desviacion[0]);

				fd = open(myfifo, O_WRONLY);//leer opcion
				write(fd, desviacion, sizeof(double));
				close(fd);


			}else if(opcion==3){

				int filas1=0, columnas1=0, base=0, *orden;
				printf("\n[P] Ordenamiento de una matriz respecto a una columna.\n");
				read(fd, numero, sizeof(int));
				filas1=numero[0];
				read(fd, numero, sizeof(int));
				columnas1=numero[0];
				read(fd, numero, sizeof(int));
				base=numero[0];
				double mat1[filas1][columnas1], copia[filas1][columnas1];
				matriz=new double[1];
				double result[filas1][columnas1],comp;
				orden = new int[filas1];
				printf("[Cliente %d]Columna respecto a la que se organizara: %d\n",numhilo,base);
				printf("[Cliente %d] Matriz:\n",numhilo);
				for(int i=0;i<filas1;i++){
					for(int j=0;j<columnas1;j++){
						read(fd,matriz,sizeof(double));
						mat1[i][j]=matriz[0];
						copia[i][j]=matriz[0];
						printf("%f ",mat1[i][j]);
					}
					printf("\n");
				}
				printf("\n");
				close(fd);
				
				int conta=0,c=0;
				comp=100000;
				orden[0]=0;
				while(true){
					for(int i=0;i<filas1;i++){
						if(copia[i][base]<comp){
							orden[conta]=i;
							comp=copia[i][base];
						}
					}
					copia[orden[conta]][base]=100000;
					comp=10000;
					conta++;
					if(conta==filas1){
						break;
					}
				}

				for(int i=0;i<filas1;i++){
					printf("%d\n",orden[i] );
				}

				printf("[Cliente %d]Matriz ordenada: \n",numhilo);
				for(int i=0;i<filas1;i++){
					for(int j=0;j<columnas1;j++){
						result[i][j]=mat1[orden[i]][j];
						printf("%f ",result[i][j]);
					}
					printf("\n");
				}

				fd = open(myfifo, O_WRONLY);//leer opcion
				for(int i=0;i<filas1;i++){
					for(int j=0;j<columnas1;j++){
						matriz[0]=result[i][j];
						write(fd, matriz,sizeof(double));
					}
				}
				close(fd);


			
			}else if(opcion==4){	

				int filas1=0, columnas1=0, filas2=0, columnas2=0;
				printf("\n[P] Multiplicacion de dos matrices.\n");
				read(fd, numero, sizeof(int));
				filas1=numero[0];
				printf("[Cliente %d]Numero de filas matriz 1: %d\n",numhilo,filas1);
				read(fd, numero, sizeof(int));
				columnas1=numero[0];
				printf("[Cliente %d]Numero de columnas matriz 1: %d\n",numhilo,columnas1);
				read(fd, numero, sizeof(int));
				filas2=numero[0];
				printf("[Cliente %d]Numero de filas matriz 2: %d\n",numhilo,filas2);
				read(fd, numero, sizeof(int));
				columnas2=numero[0];
				printf("[Cliente %d]Numero de columnas matriz 2: %d\n",numhilo,columnas2);
				mat1= new double[filas1*columnas1];
				mat2= new double[filas2*columnas2];
				matriz=new double[1];
				result = new double[filas1*columnas2];
				printf("[Cliente %d]Matriz 1: \n",numhilo);
				for(int i=0;i<filas1;i++){
					for(int j=0;j<columnas1;j++){
						read(fd,matriz,sizeof(double));
						mat1[j+i*columnas1]=matriz[0];
						printf("%f ",mat1[j+i*columnas1]);
					}
					printf("\n");
				}
				printf("\n");
				printf("[Cliente %d]Matriz 2: \n",numhilo);
				for(int i=0;i<filas2;i++){
					for(int j=0;j<columnas2;j++){
						read(fd,matriz,sizeof(double));
						mat2[j+i*columnas2]=matriz[0];
						printf("%f ",mat2[j+i*columnas2]);
					}
				printf("\n");
				}
				close(fd);
				

				if(columnas1==filas2){
				    for(int i = 0; i < filas1; ++i){        
				        for(int j = 0; j <columnas2; ++j) {
				            for(int z= 0; z<columnas1; ++z){
				              result[j+(i*columnas2)] =result[j+(i*columnas2)] + mat1[z+(i*columnas1)] * mat2[j+(z*columnas2)];
				            }
				        } 
				    }
				    printf("[Cliente %d]Matriz resultante: \n",numhilo);
				    printf("\n");
					for(int i=0;i<filas1;i++){
						for(int j=0;j<columnas2;j++){
							printf("%f ",result[j+i*columnas2]);
						}
					printf("\n");
					}

					fd = open(myfifo, O_WRONLY);//leer opcion
					int res[1];
					res[0]=filas1;
					write(fd, res, sizeof(int));
					res[0]=columnas2;
					write(fd, res, sizeof(int));
					for(int i=0;i<filas1;i++){
						for(int j=0;j<columnas2;j++){
							matriz[0]=result[j+i*columnas2];
							write(fd, matriz,sizeof(double));
						}
					}
					
					close(fd);
			  
				}else{
					printf("[P] Matrices no se pueden multiplicar, dimensiones incorrectas.\n");
					fd = open(myfifo, O_WRONLY);//leer opcion
					int res[1];
					res[0]=0;
					write(fd, res, sizeof(int));
					write(fd, res, sizeof(int));
					close(fd);
				}


			}else if(opcion==5){


				int filas1=0, columnas1=0;
				printf("\n[P] Determinante de una matriz.\n");
				read(fd, numero, sizeof(int));
				filas1=numero[0];
				printf("%d \n",filas1);
				read(fd, numero, sizeof(int));
				columnas1=numero[0];
				printf("%d \n",columnas1);
				matriz=new double[1];
				double matdet[filas1][max];

				printf("[Cliente %d]Matriz: \n",numhilo);
				for(int i=0;i<filas1;i++){
					for(int j=0;j<columnas1;j++){
						read(fd,matriz,sizeof(double));
						matdet[i][j]=matriz[0];
						printf("%f ",matdet[i][j]);
					}
					printf("\n");
				}
				close(fd);

				if(filas1==columnas1){
					
					if(filas1==1){
						fd = open(myfifo, O_WRONLY);//leer opcion
						int res[1];
						res[0]=1;
						write(fd, res, sizeof(int));
						close(fd);
					}else{
					double rrr=determinante(matdet,filas1);
					printf("[cliente %d]Determinante: %f\n",numThreads,rrr );

					fd = open(myfifo, O_WRONLY);//leer opcion
					double res[1];
					res[0]=rrr;
					write(fd, res, sizeof(double));
					close(fd);

					}
				}else{
					printf("[P]No se puede calcular el determinante, dimensiones incorrectas.\n");
					fd = open(myfifo, O_WRONLY);//leer opcion
					double res[1];
					res[0]=sqrt(-1);
					write(fd, res, sizeof(double));
					close(fd);
				}				
			} 
			close(fd);
			printf("\n...\n\n");
		}
		printf("[P] Hilo terminado\n");
	}
	pthread_exit(0);
}

double cofactor(double det[][max], int orden, int fila, int columna){
	double submatriz[max][max];
	int n=orden-1;

	int x=0;
	int y=0;

	for(int i=0;i<orden;i++){
		for(int j=0;j<orden;j++){
			if(i!=fila && j!=columna){
				submatriz[x][y]=det[i][j];
				y++;
				if(y>=n){
					x++;
					y=0;
				}
			}
		}
	}
	return pow(-1,fila+columna)*determinante(submatriz, n);
}

double determinante(double matr[][max], int orden){
	int det=0;
	for(int i=0;i<orden;i++){
		det=det+matr[0][i]*cofactor(matr,orden,0,i);
	}
}