
#include <iostream>
using namespace std;
# define MAX 20

int main()

{
  
  int numfilmatriz1,numcolmatriz1,numfilmatriz2,numcolmatriz2;

  double *matriz1,*matriz2,*result;


  

  cout<<"lectura de matriz 1."<<endl;
  cout<<endl;
  cout<<"Ingrese numero de Filas de la matriz 1:"<<endl; cin>>numfilmatriz1;
  cout<<"Ingrese numero de columnas de la matriz 1:"<<endl; cin>>numcolmatriz1;

  matriz1 = new double[numfilmatriz1*numcolmatriz1];
    
    for (int i = 0; i <numfilmatriz1; ++i)    
    {
      for(int j = 0; j <numcolmatriz1; ++j)
      {
        cout<<"Ingrese los valores para la matriz 1 ["<<i<<"] ["<<j<<"]: ";
        cin>>matriz1[j+(i*numcolmatriz1)];
      }
    }

  cout<<endl;
  cout<<"Matriz 1: " <<endl;
  cout<<"";

    for (int i = 0; i < numfilmatriz1; ++i)
    {
        for (int j = 0; j<numcolmatriz1; ++j)
        {
          cout<<matriz1[j+(i*numcolmatriz1)]<<"  ";
        }
          cout<<endl;
    }




  cout<<endl;   
  cout<<"lectura de matriz 2."<<endl;
  cout<<endl;
  cout<<"Ingrese numero de Filas de la matriz 2 "<<endl;
  cout<<"(Es necesario que sea igual al numero de columnas de matriz 1) : " <<endl; cin>>numfilmatriz2;
   
  while (numfilmatriz2 != numcolmatriz1)

  {

  cout<<" El numero de filas de la matriz 2 debe ser igual al numero de columnas de la matriz 1 para poder realizar el producto"<<endl;
  cout<<"Ingrese nuevamente el numero de filas de la matriz 2"<<endl; cin>>numfilmatriz2;
  //retornar el int numfilmatriz1=0 y el int numcolmatriz2=0.
  
  }

  cout<<"Ingrese  el numero de columnas de la matriz 2"<<endl; cin>>numcolmatriz2;
  cout<<endl;

  matriz2 = new double[numfilmatriz2*numcolmatriz2];

    for (int i = 0; i < numfilmatriz2; ++i)
    {
      for (int j = 0; j <numcolmatriz2; ++j)
      { 
         cout<<"Ingrese los valores para la matriz 2 ["<<i<<"] ["<<j<<"]: ";
         cin>>matriz2[j+(i*numcolmatriz2)];
      }
    }

    cout<<"Matriz 2: "<<endl;
  	cout<<"";

    for (int i = 0; i <numfilmatriz2; ++i)
    {
        for (int j = 0; j<numcolmatriz2; ++j)
        {
          cout<<matriz2[j+(i*numcolmatriz2)]<<"  ";
        }
           cout<<endl;
    }

  result = new double[numfilmatriz1*numcolmatriz2];
        
//Inicializamos la matriz resultante = matriz C
  	for (int i = 0; i < numfilmatriz2; ++i)
    {
      for (int j = 0; j <numcolmatriz1; ++j)
      { 
         
         result[j+(i*numcolmatriz1)] = 0;
      }
    }



//Generamos la matriz resultante = matriz C

    for (int i = 0; i < numfilmatriz1; ++i)
    {        
        for (int j = 0; j <numcolmatriz2; ++j)
        {
            for (int z= 0; z<numcolmatriz1; ++z)
            {
              result[j+(i*numcolmatriz2)] =result[j+(i*numcolmatriz2)] + matriz1[z+(i*numcolmatriz1)] * matriz2[j+(z*numcolmatriz2)];
            }
        } 
    }


  cout<<"Matriz resultante: "<<endl;
  	cout<<"";

    for (int i = 0; i < numfilmatriz1; ++i)
    {
        for (int j = 0; j<numcolmatriz2; ++j)
        {
          cout<<result[j+(i*numcolmatriz2)]<<"  ";
        }
         cout<<endl;
    }


    //retornar el double *result, el int numfilmatriz1 y el int numcolmatriz2.


return 0;     
              
    
}