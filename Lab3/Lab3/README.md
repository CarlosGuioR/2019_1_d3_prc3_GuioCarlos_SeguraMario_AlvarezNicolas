# Laboratorio 2 
# Sistemas Digitales III

### Presentado por:

- Carlos Fernando Guio Rodriguez
- Mario Alberto Segura Albarracin
- Nicolas Alzarez Casadiego

# Introduccion:
	
En este laboratorio se crea un servidor capaz de atender varios clientes a la vez, cada cliente se comunica con el servidor por medio de una tuberia propia. El servidor ofrece los servicios de: promedio de un vector, desviacion estandar de un vector, ordenamiento de una matriz segun una columna, multiplicacion de matrices y determinante de una matriz.

# Desarrollo del programa:

El programa consta de dos grandes funciones, la primera en donde se verifica si el cliente accede a la memoria compartida, despues verifica la suscripcion de los usuarios y finalmente verifica el nombre de la tuberia para poder crear el hilo de cada cliente y finalmente crear la tuberia. La segunda parte es donde se atienden los servicios que ofrece el cliente, cada uno por aparte.

El servidor crea una memoria compartida con el nombre: "SHMEM_MATH_SERVER_SUBSCRIPTION" para que los usuarios que quieran suscribirse envien sus solicitudes, en esta memoria hay una estructura que se conforma por una bandera (uchar) que es 1 si existe algun cliente que quiera conectarse o un 0 en caso contrario, un path (char[81]) en donde se escribira el path de la tuberia donde se quiere hacer la comunicacion Cliente-Servidor y finalmente una salida en donde el servidor confirmara o no la suscripcion del cliente.

Despues de realizar la suscripcion, el servidor verifica que el path sea valido(que exista, que contenga un caracter nulo '\0' y que no este en uso), en caso de no ser valido se le informa al usuario colocando la salida en 2. Despues de verificar el path se procede a crear un hilo para ese cliente y una tuberia con la direccion path.

## Servicios:

Cuando ya esta creada la tuberia y se establece la comunicacion, el cliente envia una trama de datos dependiendo de la opcion, la primer trama del dato es el servicio que se quiere: 1 para el promedio de un vector, 1 para la desviacion estandar de un vector, 3 para el ordenamiento de una matriz segun una columna, 4 para multiplicacion de matrices y 5 para el determinante de una matriz.

### Promedio de un vector:
En este caso se recibe el tamaño del vector como un int, con esto se leen los datos dependiendo del dato anterior, estos datos son de tipo double, finalmente se realiza el promedio y se devuelve el resultado por la tuberia en formado double. 
 
### Desviacion estandar de un vector:
En este caso se recibe el tamaño del vector como un int, con esto se leen los datos dependiendo del dato anterior, estos datos son de tipo double, finalmente se realiza el calculo de la varianza y se devuelve el resultado por la tuberia en formado double. 

### Ordenamiento de una matriz segun una columna: 

En este caso se recibe la cantidad de filas de la matriz en formato int, la cantidad de columnas en formato int ,la columna sobre la que se quiere ordenar y los datos de izquierda a derecha y de arriba hacia abajo en formato doble de la matriz, en este caso se guarda en un vector el indice de menor a mallor de los datos correspondientes a la columna elegida y finalmente se reorganiza la matriz, al final se envian estos valores por medio de la tuberia en formato double de izquierda a derecha y de arriba hacia abajo.

### Multiplicacion de matrices:

En este caso se recibe la cantidad de filas de la primer matriz en formato int, la cantidad de columnas en formato int ,la cantidad de filas y columnas de la matriz 2 y los datos, primero los de la matriz 1 y despues de la matriz 2. Cuando ya se tienen todos los datos se verifica que la multiplicacion sea posible (Columnas de la matriz 1 sea igual al numero de filas de la matriz 2), en caso de no ser valido se le informa al cliente retornando 0 en filas y columnas. En caso de ser valido se realiza lamultiplicacion entre matrices y se devuelve primero un int con el numero de filas, un int con el numero de columnas y los datos de la moltuplicacion de izquierda a derecha y de arriba a abajo en formato double. 

### Determinante de una matriz:

En este caso se recibe la cantidad de filas de la matriz en formato int, la cantidad de columnas en formato int y los datos de izquierda a derecha y de arriba hacia abajo en formato doble de la matriz, en este caso se verifica que las filas y las columnas sean iguales para poder calcular el determinante, si no lo son se devuelve "nan" en el resultado, en caso de ser valido se calcula el determinante y se devuelven un double con el valor del determinante.
	


# Conclusiones:
	
- Se pueden crear tantos clientes se deseen, cada uno es un proceso diferente y es atendido por el servidor por medio de su propio hilo.

- El control de la lectura y escritura por medio de latuberia es fundamental, esto puede desordenar todo.

- La comunicacion por medio de tuberias es estricta en cuanto a el numero de bytes que se leen, esto fue un reto.


	




















