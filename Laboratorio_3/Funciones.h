#ifndef FUNC_H
#define FUNC_H

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<sstream>
#include<stdio.h>
#include <math.h>

double **data;

double Provector(int servicio, int tam, double vec[7]);

double Desviacionvector(int servicio, int tam, double vec[]);

double Matrizordenada(int servicio, int numfilas, int numcolumnas, int columna, double matriz[][]);
#endif