#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <iostream>

using namespace std;

vector<int> generarVector(int longitud);
vector<int> generarEjemplo(int longitud);
int secuencial(vector<int>, int, int );
void imprimir(vector<int>, int);
int binaria(vector<int>, int, int );
int ternaria(vector<int>, int, int );

int contador_secuencial = 0;
int contador_binaria = 0;
int contador_ternaria = 0;


int main(void)
{
    vector <int> ejemploNoOrdenado;
	vector <int> ejemploOrdenado;
    int numeroBuscar, resultado;
    
    ejemploNoOrdenado = generarVector(100);
    imprimir(ejemploNoOrdenado,100);
    cout<<"************************************** "<<endl;
    cout<<"*** EJEMPLO DE BUSQUEDA SECUENCIAL *** "<<endl;
    cout<<"************************************** "<<endl;
    numeroBuscar = rand() % 99 + 1;
    cout<<"Numero a Buscar:  "<<numeroBuscar<<endl;
    resultado = secuencial(ejemploNoOrdenado,100,numeroBuscar);
    if (resultado ==-1)
    	cout<<"ELEMENTO NO ENCONTRADO "<<endl;
    else
    	cout<<"ELEMENTO ENCONTRADO.  EN LA POSICION:  "<<resultado <<endl;
        cout << "Tardo " << contador_secuencial << " iteración" << endl; 

  
  	ejemploOrdenado = generarEjemplo(100);
    imprimir(ejemploOrdenado,100);
    cout<<"************************************** "<<endl;
    cout<<"***** EJEMPLO DE BUSQUEDA BINARIA **** "<<endl;
    cout<<"************************************** "<<endl;
    numeroBuscar = rand() % 99 + 1;
    cout<<"Numero a Buscar:  "<<numeroBuscar<<endl;
    resultado = binaria(ejemploOrdenado,100,numeroBuscar);
    if (resultado ==-1)
    	cout<<"ELEMENTO NO ENCONTRADO "<<endl;
    else
    	cout<<"ELEMENTO ENCONTRADO.  EN LA POSICION:  "<<resultado <<endl;
        cout << "Tardo " << contador_binaria << " iteraciónes " << endl; 


    cout<<"************************************** "<<endl;
    cout<<"***** EJEMPLO DE BUSQUEDA TERNARIA**** "<<endl;
    cout<<"************************************** "<<endl;
    numeroBuscar = rand() % 99 + 1;
    cout<<"Numero a Buscar:  "<<numeroBuscar<<endl;
    resultado = ternaria(ejemploOrdenado,100,numeroBuscar);
    if (resultado ==-1)
    	cout<<"ELEMENTO NO ENCONTRADO "<<endl;
    else
    	cout<<"ELEMENTO ENCONTRADO.  EN LA POSICION:  "<<resultado <<endl;
        cout << "Tardo " << contador_ternaria << " iteraciónes " << endl; 

 	
    return 0;
}


vector<int> generarVector(int longitud){
	vector<int> vec;
	/* initialize random seed: */
	srand (time(NULL));
	
	for (int i=0; i<longitud;i++)
	{
		vec.push_back(rand() % 99 + 1);
	}
	return vec;
}

vector<int> generarEjemplo(int longitud){
	vector<int> vec;
	for (int i=0; i<longitud;i++)
		vec.push_back(i + 1);
	return vec;
}

void imprimir(vector<int> v1, int lon)
{
	for ( int v1_i=0; v1_i<lon; v1_i++ )
	  cout << v1[v1_i]<< "\t";
	cout<<endl;
}


int secuencial(vector<int> vectorDatos, int longitud, int clave) {
	int encontrado = -1, indice=0;
	
	while (indice <longitud and encontrado ==-1){
		if (vectorDatos[indice] == clave) {
            encontrado = indice; 
        }
        else 
        	indice ++;
            contador_secuencial += 1;
	}
    return encontrado; 
}

int binaria(vector<int> vectorDatos, int longitud, int clave){
    int pos = -1,  inf = 0, sup;
	sup = longitud;
	int centro;
 	while ((inf <= sup) and (pos < 0)) {
		centro = (inf + sup) / 2;
		if (vectorDatos[centro] == clave)
			pos = centro;
		else
            
			if (clave > vectorDatos[centro] )
				inf = centro + 1;
			else
				sup = centro - 1;
            contador_binaria += 1;
	}
	return pos;
}

int ternaria(vector<int> vectorDatos, int longitud, int clave)
{
    int inf = 0, sup = longitud - 1;
 	int pos = -1;
    while (inf <= sup and pos==-1)
    {
        int izq_centro = inf + (sup - inf) / 3;
        int der_centro = sup - (sup - inf) / 3;

        if (vectorDatos[izq_centro] == clave) {
            pos = izq_centro;
        }
        else if (vectorDatos[der_centro] == clave) {
            pos = der_centro;
        }
        else if (vectorDatos[izq_centro] > clave) {
            sup = izq_centro - 1;
        }
        else if (vectorDatos[der_centro] < clave) {
            inf = der_centro + 1;
        }
        else {
            inf = izq_centro + 1;
			sup = der_centro - 1;
        }
        contador_ternaria += 1;
    }
 
    return pos;
}

/* *******DOCUMENTACION**********
El código proporcionado implementa tres algoritmos de búsqueda en vectores:
    búsqueda secuencial,
    búsqueda binaria y 
    búsqueda ternaria. 
    
    Además, incluye funciones auxiliares para generar vectores aleatorios y vectores ordenados para su uso en los ejemplos de búsqueda.

Aquí está una descripción de las funciones y procedimientos en el código:
generarVector(int longitud): Esta función genera un vector de enteros aleatorios de longitud especificada.
generarEjemplo(int longitud): 
        Esta función genera un vector ordenado de enteros en orden ascendente desde 1 hasta la longitud especificada.
imprimir(vector<int> v1, int lon): Esta función imprime los elementos de un vector de enteros junto con un salto de línea.
secuencial(vector<int> vectorDatos, int longitud, int clave): Este procedimiento realiza una búsqueda secuencial en el vector de datos para encontrar la clave especificada. Devuelve la posición de la clave si se encuentra o -1 si no se encuentra.
binaria(vector<int> vectorDatos, int longitud, int clave): Este procedimiento realiza una búsqueda binaria en el vector de datos para encontrar la clave especificada. Devuelve la posición de la clave si se encuentra o -1 si no se encuentra.
ternaria(vector<int> vectorDatos, int longitud, int clave): Este procedimiento realiza una búsqueda ternaria en el vector de datos para encontrar la clave especificada. Devuelve la posición de la clave si se encuentra o -1 si no se encuentra.
Además, hay tres variables globales contador_secuencial, contador_binaria y contador_ternaria que registran el número de iteraciones realizadas en cada algoritmo de búsqueda para buscar un elemento. Esto se utiliza para medir el rendimiento de cada algoritmo.
El programa principal (main()) utiliza estas funciones y procedimientos para generar ejemplos de vectores, realizar búsquedas con diferentes algoritmos y mostrar los resultados junto con el número de iteraciones realizadas en cada búsqueda.
*/