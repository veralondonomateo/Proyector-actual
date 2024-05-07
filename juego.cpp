#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void letrastopalabras() {
    int vidas = 3;
    int puntos = 0;
    int vidas_pc = 3;
    int puntos_pc = 0;
    const int tiempolimite = 40;
    const int tiempoRespuesta = 6; // Tiempo máximo de respuesta permitido en segundos
    vector<vector<char>> matrizletras = {
        {'L', 'E', 'A', 'R', 'T', 'H', 'D'},
        {'O', 'M', 'P', 'S', 'I', 'N', 'E'},
        {'R', 'A', 'C', 'T', 'E', 'I', 'V'},
        {'S', 'U', 'N', 'I', 'O', 'T', 'A'},
        {'D', 'E', 'R', 'F', 'A', 'T', 'I'},
        {'G', 'O', 'L', 'N', 'A', 'I', 'B'},
        {'H', 'U', 'M', 'A', 'N', 'E', 'D'}
    };
    vector<vector<string>> palabras = {
        {"REAL", "HORA", "ARTE", "DAR"},
        {"MES", "PINO", "SOL", "PISO"},
        {"CARRO", "VER", "TIERRA", "VIA"},
        {"SOL", "TU", "UNO", "TINO"},
        {"ARTE", "RED", "FIAR", "TARDE"},
        {"LAGO", "GALLO", "AGIL", "BAILON"},
        {"MANO", "LUNA", "HUMO", "AMEN"}
    };

    cout << "Bienvenido al juego de encuentra las palabras" << endl;

    while (vidas > 0 && puntos < 100 && vidas_pc > 0 && puntos_pc < 100)  {
        cout << "Basado en estas letras tienes 10 segundos para adivinar la mayor cantidad de palabras: ";
        for (auto && i : matrizletras[0]) {
            cout << i << ',';
        }

        steady_clock::time_point tiempoInicio = steady_clock::now();

        while (duration_cast<seconds>(steady_clock::now() - tiempoInicio).count() < tiempolimite && vidas > 0 && puntos < 100) {
            string varaux;
            cout << endl << "Ingresa una palabra. Tienes 5 segundos para ingresarla ==> ";
            cin >> varaux;

            bool palabraEncontrada = false;
            for (auto& palabrasusu : palabras) {
                auto it = find(palabrasusu.begin(), palabrasusu.end(), varaux);
                if (it != palabrasusu.end()) {
                    palabraEncontrada = true;
                    cout << "La palabra \"" << varaux << "\" está correcta. Ganaste 50 puntos" << endl << endl;
                    puntos += 50;
                    break;
                }
            }

            if (!palabraEncontrada) {
                cout << "La palabra \"" << varaux << "\" no está correcta. Perdiste 1 vida" << endl << endl;
                vidas -= 1;
            }

            // Verificar si se ha excedido el tiempo de respuesta
            if (duration_cast<seconds>(steady_clock::now() - tiempoInicio).count() >= tiempoRespuesta) {
                cout << "Te has demorado más de " << tiempoRespuesta << " segundos. La respuesta se considera incorrecta." << endl << endl;
                vidas -= 1;
                break; // Salir del bucle interno si el tiempo se agota
            }
        }

        // Turno de la computadora
        if (vidas > 0 && puntos < 100) {
            vector<string> palabras_pc = {"Gano","Perdio"};

            // Sembrar el generador de números aleatorios
            random_device rd;
            mt19937 rng(rd());

            // Generar un índice aleatorio
            uniform_int_distribution<int> dist(0, palabras.size() - 1);
            int indice_aleatorio = dist(rng);
            cout << "Es turno de la computadora" << endl;
            cout << "El PC " << palabras_pc[indice_aleatorio] << endl;

            // Esperar un segundo antes de la siguiente iteración
            this_thread::sleep_for(seconds(1));
        }
    }

    if (vidas == 0) {
        cout << "Te quedaron 0 vidas. Perdiste, Gano el pc" << endl;
        cout << "Tuviste " << puntos << " puntos";
    } else {
        cout << "Ganaste, el pc perdio";
        cout << "Tuviste " << puntos << " puntos"; 
    }
}

void completarwords() {
    // Palabras para el juego
    vector<string> palabras = {"COLOMBIA", "VENEZUELA", "BRASIL", "KOREA DEL SUR", "JAPON","MONGOLIA", "SUDAFRICA", "MARRUECOS","EGIPTO"};
    
    // Elegir una palabra aleatoria del vector
    srand(time(nullptr));
    int indice_aleatorio_1 = rand() % palabras.size();
    string palabra = palabras[indice_aleatorio_1];
    
    // Inicializar letras reveladas para mostrar solo las primeras dos letras
    vector<bool> letrasReveladas(palabra.size(), false);
    letrasReveladas[0] = true;
    letrasReveladas[1] = true;
    
    // Número máximo de intentos
    int vidas = 3;
    int puntos = 0;
    int vidas_pc = 3;
    int puntos_pc = 0;
    
    cout << "BIENVENIDO A COMPLETAR PALABRA" << endl;
    cout << "Te daremos una palabra para completar, por cada letra que adivines ganaras 20 puntos. Puedes utilizar una pista y perderas 5" << endl;
    // Bucle principal del juego
    while (vidas > 0 && puntos < 100 && vidas_pc > 0 && puntos_pc < 100) {
        // Inicializar la palabra oculta para esta iteración
        vector<string> options = {"Gano", "Perdio"};
        int indice_aleatorio = rand() % 2;
        
        string palabraOculta;
        inicializarPalabra(palabra, letrasReveladas, palabraOculta);
        
        // Mostrar la palabra oculta
        cout << "Palabra: " << palabraOculta << endl;
        
        // Pedir al jugador que ingrese una letra
        char letra;
        int pista;
        cout << "Deseas utiliza una pista? (Ingresa 1 si deseas pista) ==> ";
        cin >> pista;
        if(pista == 1){
            if(palabra == "COLOMBIA"){
                cout << "Es un pais de sudamerica";
            }
            if(palabra == "VENEZUELA"){
                cout << "Es un pais de sudamerica";
            }
            if(palabra == "BRASIL"){
                cout << "Es un pais de sudamerica";
            }
            if(palabra == "KOREA DEL SUR"){
                cout << "Es un pais de asia";
            }
            if(palabra == "JAPON"){
                cout << "Es un pais de asia";
            }
            if(palabra == "MONGOLIA"){
                cout << "Es un pais de asia";
            }
            if(palabra == "SUDAFRICA"){
                cout << "Es un pais de africa";
            }
            if(palabra == "MARRUECOS"){
                cout << "Es un pais de africa";
            }
            if(palabra == "EGIPTO"){
                cout << "Es un pais de africa";
            }
            puntos -= 5;
            cout << endl;
        }
        
        cout << "Ingresa una letra ==> ";
        cin >> letra;
        
        // Verificar si la letra está en la palabra
        bool letraAdivinada = false;
        for (int i = 0; i < palabra.size(); ++i) {
            if (tolower(palabra[i]) == tolower(letra) && !letrasReveladas[i]) {
                letraAdivinada = true;
                letrasReveladas[i] = true;
                puntos += 20;
            }
        }
        
        if (letraAdivinada) {
            cout << "¡Bien hecho! La letra está en la palabra." << endl;
        } else {
            cout << "La letra no está en la palabra. Pierdes 1 vida." << endl;
            --vidas;
        }
        
        // Verificar si el jugador ha completado la palabra
        if (find(letrasReveladas.begin(), letrasReveladas.end(), false) == letrasReveladas.end()) {
            cout << "¡Felicidades! Has completado la palabra." << endl;
            break;
        }
        
        // Turno de la computadora
        if (vidas > 0 && puntos < 100) {
            cout << "Es turno de la computadora" << endl;
            cout << "El PC " << options[indice_aleatorio] << endl;
        }
    }
    
    if (vidas == 0) {
        cout << "Te quedaron 0 vidas. Perdiste, Gano el pc" << endl;
        cout << "Tuviste " << puntos << " puntos";
    } else {
        cout << "Ganaste, el pc perdio";
        cout << "Tuviste " << puntos << " puntos"; 
    }
}

int main() {
    int opcion;
    cout << "Bienvenido a la plataforma de juegos" << endl;
    cout << "1. Encuentra palabras" << endl;
    cout << "2. Completar palabras" << endl;
    cout << "Elije una opcion ==> ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            letrastopalabras();
            break;
        case 2:
            completarwords();
            break;
        default:
            cout << "Opción no válida";
            break;
    }
    return 0;
}
