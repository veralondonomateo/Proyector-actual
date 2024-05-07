#include <iostream>
using namespace std;

struct Notas{
    string nombre;
    float parcial1;
    float parcial2;
    float parcial3;
};

Notas persona;


void añadir_datos(){
    cout << "Cual es tu nombre? ";
    cin >> persona.nombre;
    cout << "Cual es la nota de tu primer parcial? ";
    cin >> persona.parcial1;
    cout << "Cual es la nota de tu segundo parcial? ";
    cin >> persona.parcial2;
    cout << "Cual es la nota de tu tercer parcial? ";
    cin >> persona.parcial3;
}

void calcular_promedio(){
    float promedio;
    
    float nota1 = (persona.parcial1) * 0.3;
    float nota2 = (persona.parcial2) * 0.35;
    float nota3 = (persona.parcial3) * 0.35;
    
    promedio = nota1 + nota2 + nota3;
    cout << promedio << endl;
    if (promedio >= 3){
        cout << "Aprobo";
    } else  {
        cout << "No aprobo";
    }
}
;

int main()
{
    añadir_datos();
    calcular_promedio();
    return 0;
}