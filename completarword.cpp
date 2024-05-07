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
        {"Carro", "Ver", "Tierra", "Vía"},
        {"Sol", "Tú", "Uno", "Tino"},
        {"Arte", "Red", "Fiar", "Tarde"},
        {"Lago", "Gallo", "Agil", "Bailón"},
        {"Mano", "Luna", "Humo", "Amén"}
    };

    cout << "Bienvenido al juego de encuentra las palabras" << endl;

    steady_clock::time_point tiempoInicio = steady_clock::now();

    while (vidas > 0 && puntos < 100 && vidas_pc > 0 && puntos_pc < 100)  {
        cout << "Basado en estas letras tienes 10 segundos para adivinar la mayor cantidad de palabras: ";
        for (auto &&i : matrizletras[0]) {
            cout << i << ',';
        }

        while (duration_cast<seconds>(steady_clock::now() - tiempoInicio).count() < tiempolimite && vidas > 0 && puntos < 100) {
            string varaux;
            cout << endl << "Ingresa una palabra. Tienes 5 segundos para ingresarla ==> ";
            cin >> varaux;

            vector<string> palabrasusu = palabras[0];
            auto it = find(palabrasusu.begin(), palabrasusu.end(), varaux);

            // Verificar si se ha excedido el tiempo de respuesta, si es así
            // con el continue vuelve y empieza sabiendo que el usuario tiene una
            // vida menos
            if (duration_cast<seconds>(steady_clock::now() - tiempoInicio).count() >= tiempoRespuesta) {
                cout << "Te has demorado más de " << tiempoRespuesta << " segundos. La respuesta se considera incorrecta." << endl << endl;
                vidas -= 1;
                continue;
            }

            if (it != palabrasusu.end() && duration_cast<seconds>(steady_clock::now() - tiempoInicio).count() <= tiempoRespuesta) {
                cout << "La palabra \"" << varaux << "\" está correcta. Ganaste 50 puntos" << endl << endl;
                puntos += 50;
            } else if (it == palabrasusu.end()){
                cout << "La palabra \"" << varaux << "\" no está correcta. Perdiste 1 vida" << endl << endl;
                vidas -= 1;
            }
            vector<string> palabras = {"Gano","Perdio"};
    
            // Sembrar el generador de números aleatorios
            random_device rd;
            mt19937 rng(rd());
            
            // Generar un índice aleatorio
            uniform_int_distribution<int> dist(0, palabras.size() - 1);
            int indice_aleatorio = dist(rng);
            cout << "Es turno de la computadora" << endl;
            cout << "El PC " << palabras[indice_aleatorio];

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


// Función para inicializar la palabra oculta y mostrar las letras reveladas
void inicializarPalabra(const string& palabra, vector<bool>& letrasReveladas, string& palabraOculta) {
    palabraOculta = "";
    for (int i = 0; i < palabra.size(); ++i) {
        if (letrasReveladas[i]) {
            palabraOculta += palabra[i];
        } else {
            palabraOculta += "_";
        }
    }
}

// Función principal para jugar el juego del ahorcado
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
        cout << "Deseas utiliza una pista? Si la utilizas se te restara una vida y 20 puntos.  Ingresa 0 para omitir y 1 para ver la pista ";
        cin >> pista;
        
        if (pista == 1){
            switch(indice_aleatorio_1){
                case 0:
                                cout << "pista: Es un pais de sudamerica" << endl;
                break;
                case 1:
                                cout << "pista: Es un pais de sudamerica" << endl;
                break;
                case 2:
                                cout << "pista: Es un pais de sudamerica" << endl;
                break;
                case 3:
                                cout << "pista: Es un pais de asia" << endl;
                break;
                case 4:
                                cout << "pista: Es un pais de asia" << endl;

                break;
                case 5:
                                cout << "pista: Es un pais de asia" << endl;

                break;
                case 6:
                                cout << "pista: Es un pais de Africa " << endl;
                break;
                case 7:
                                cout << "pista: Es un pais de Africa " << endl;

                break;
                case 8:
                                cout << "pista: Es un pais de Africa " << endl;
                break;
                default:
                                cout << "No tenemos pistas" << endl;
                break;
            }
            vidas--;
            puntos -= 10;
        }
        
        cout << "Ingresa una letra: ";
        cin >> letra;
        
        // Verificar si la letra ya ha sido revelada
        if (find(letrasReveladas.begin(), letrasReveladas.end(), letra) != letrasReveladas.end()) {
            cout << "Ya has ingresado esta letra antes. Intenta con otra." << endl;
            continue;
        }
        
        // Verificar si la letra está en la palabra y actualizar letras reveladas
        bool letraEncontrada = false;
        for (int i = 0; i < palabra.size(); ++i) {
            if (palabra[i] == letra) {
                letrasReveladas[i] = true;
                letraEncontrada = true;
                puntos += 10;
            }
        }
        
        // Si la letra no está en la palabra, reducir el número de intentos
        if (!letraEncontrada) {
            vidas--;
            cout << "La letra no está en la palabra. Te quedan " << vidas << " intentos." << endl;
        }
        
        // Verificar si el jugador ha adivinado la palabra
        bool adivinado = true;
        for (bool revelada : letrasReveladas) {
            if (!revelada) {
                adivinado = false;
            }
        }
        if (indice_aleatorio == 0){
            puntos_pc += 10;
        } else{
            vidas_pc -= 1;
        }
        cout << "Tus puntos son: "<< puntos << endl;
        cout << "Tus vidas son: " << vidas << endl << endl;
        
        cout << "Turno del pc" << endl;
        cout << "El pc " << options[indice_aleatorio] << endl;
        cout << "Las vidas del pc son: " << vidas_pc << endl;
        cout << "Los puntos del pc son: " << puntos_pc << endl;
        
        
        if (puntos_pc == 100){
            cout << "Lastimosamente el pc ha ganado" << endl;
        }
        if (adivinado) {
            cout << "¡Felicidades! Has adivinado la palabra." << endl;
            puntos += 100;
        }
    }
    
    // Si el jugador no adivina la palabra después de los intentos máximos
    if (vidas == 0) {
        cout << "¡Lo siento! Has agotado tus intentos. La palabra era: " << palabra << endl;
    } else{
        cout << endl << "El pc ha perdido, por lo tanto el ganador eres tu";
    }
}
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Estructura para representar una pregunta y sus opciones de respuesta
struct Question {
    string pregunta;
    string opciones[4];
    int respuestaCorrecta;
};

// Función para mostrar una pregunta y sus opciones
void mostrarPregunta(Question pregunta) {
    cout << endl << pregunta.pregunta << endl;
    for (int i = 0; i < 4; ++i) {
        cout << i + 1 << ". " << pregunta.opciones[i] << endl;
    }
}

// Función para obtener las opciones incorrectas a eliminar como pista
vector<int> obtenerOpcionesIncorrectas(Question pregunta) {
    vector<int> opcionesIncorrectas;
    for (int i = 0; i < 4; ++i) {
        if ( i != pregunta.respuestaCorrecta) {
            opcionesIncorrectas.push_back(i);
        }
    }

    return opcionesIncorrectas;
}

// Función para realizar el juego
void jugarpreguntas() {
    // Definir preguntas y respuestas
    Question preguntas[] = {
    {"¿Cuál es la capital de Francia?", {"Madrid", "Berlín", "París", "Roma"}, 3},
    {"¿Dónde se encuentra la Gran Muralla China?", {"India", "China", "Japón", "Corea del Sur"}, 2},
    {"¿Cuál es el río más largo del mundo?", {"Amazonas", "Nilo", "Yangtsé", "Misisipi"}, 1},
    {"¿Cuál es la capital de Australia?", {"Sydney", "Melbourne", "Canberra", "Brisbane"}, 3},
    {"¿En qué continente se encuentra Sudáfrica?", {"Europa", "Asia", "África", "América"}, 3},
    {"¿Cuál es el país más grande del mundo en términos de área terrestre?", {"Estados Unidos", "China", "Rusia", "Canadá"}, 3},
    {"¿Dónde se encuentra la Ciudad del Vaticano?", {"Italia", "España", "Francia", "Ciudad del Vaticano"}, 4},
    {"¿Cuál es el país conocido como 'La Tierra del Sol Naciente'?", {"China", "Japón", "Corea del Sur", "Vietnam"}, 2},
    {"¿En qué océano se encuentra la Isla de Pascua?", {"Atlántico", "Índico", "Pacífico", "Ártico"}, 3},
    {"¿Cuál es la capital de Canadá?", {"Toronto", "Ottawa", "Vancouver", "Montreal"}, 3},
    {"¿En qué país se encuentra la Gran Barrera de Coral?", {"Australia", "Filipinas", "México", "Brasil"}, 1},
    {"¿Cuál es el punto más alto de la Tierra?", {"Everest", "K2", "Kilimanjaro", "Mont Blanc"}, 1},
    {"¿Cuál es el río más largo de América del Sur?", {"Amazonas", "Paraná", "Orinoco", "Magdalena"}, 1},
    {"¿Cuál es la capital de Nueva Zelanda?", {"Auckland", "Wellington", "Christchurch", "Queenstown"}, 2},
    {"¿En qué continente se encuentra Egipto?", {"África", "Asia", "Europa", "Oceanía"}, 1},
    {"¿Cuál es la capital de Noruega?", {"Copenhague", "Estocolmo", "Helsinki", "Oslo"}, 4},
    {"¿En qué país se encuentra la Acrópolis de Atenas?", {"Italia", "Grecia", "Turquía", "Egipto"}, 2},
    {"¿Cuál es la montaña más alta de África?", {"Mont Blanc", "Kilimanjaro", "Atlas", "Ruinsori"}, 2},
    {"¿En qué país se encuentra el Taj Mahal?", {"India", "Pakistán", "Bangladesh", "Nepal"}, 1},
    {"¿Cuál es la capital de Argentina?", {"Buenos Aires", "Río de Janeiro", "Santiago", "Montevideo"}, 1},
    {"¿En qué océano se encuentra Madagascar?", {"Atlántico", "Índico", "Pacífico", "Antártico"}, 2},
    {"¿Cuál es la capital de Irlanda?", {"Edimburgo", "Dublín", "Belfast", "Cardiff"}, 2},
    {"¿En qué país se encuentra el Canal de Panamá?", {"Colombia", "Panamá", "Costa Rica", "Honduras"}, 2}
};



    // Obtener la cantidad de preguntas
    int totalPreguntas = sizeof(preguntas) / sizeof(preguntas[0]);

    // Inicializar el generador de números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Iniciar el juego
    int puntaje = 0;
    int vidas = 3;
    int puntajepc=0;
    int vidaspc=3;
    int i=0;


    while(puntaje<100 && vidas>=1 && puntajepc<100 && vidaspc>=1){
        
        
            
        // Crear una versión temporal de la pregunta para mostrar la pista
        Question preguntaTemporal = preguntas[i];

        // Mostrar la pregunta al inicio del bucle
        mostrarPregunta(preguntaTemporal);

        // Obtener la respuesta del jugador
        int respuestaJugador;
        cout << "Ingresa el número de la respuesta correcta o 0 para recibir ayuda: ";
        cin >> respuestaJugador;

        // Verificar si el jugador pide ayuda
        if (respuestaJugador == 0) {
            puntaje-=15;
            // Mostrar las opciones incorrectas eliminadas como pista
            vector<int> opcionesIncorrectas = obtenerOpcionesIncorrectas(preguntaTemporal);
            random_shuffle(opcionesIncorrectas.begin(), opcionesIncorrectas.end());

            // Eliminar dos opciones incorrectas temporalmente
            int opcionEliminar1 = opcionesIncorrectas[0];
            int opcionEliminar2 = opcionesIncorrectas[1];
            preguntaTemporal.opciones[opcionEliminar1] = " ";
            preguntaTemporal.opciones[opcionEliminar2] = " ";

            // Mostrar la pregunta con las opciones eliminadas
            mostrarPregunta(preguntaTemporal);

            // Dar otra oportunidad al jugador para responder
            cout << "Ingresa el número de la respuesta correcta: ";
            cin >> respuestaJugador;

            // Restaurar la pregunta original
            preguntaTemporal.opciones[opcionEliminar1] = preguntas[i].opciones[opcionEliminar1];
            preguntaTemporal.opciones[opcionEliminar2] = preguntas[i].opciones[opcionEliminar2];
        }

        // Verificar la respuesta
        if (respuestaJugador == preguntas[i].respuestaCorrecta ) {
            cout << "¡Correcto!" << endl;
            puntaje += 25;
            cout << "Puntos => " << puntaje << endl;
        } else {
            cout << "Incorrecto. La respuesta correcta es: " << preguntas[i].respuestaCorrecta << endl;
            vidas -= 1;
            cout << "Te quedan " << vidas << " vidas" << endl;
        }
        
        cout<<endl<< "Ahora es turno de la computadora : "<< endl;
        vector<string> opcionpc={"respuesta Correcta","respuesta Incorrecta","respuesta Correcta, utilizó pista.","respuesta Incorrecta, Utilizó pista."};
        srand(time(0));
        

    // Obtener un índice aleatorio dentro del rango del vector
         size_t indiceAleatorio = rand() % opcionpc.size();

    // Obtener el elemento aleatorio del vector
        string elementoAleatorio = opcionpc[indiceAleatorio];

        switch(indiceAleatorio){
            case 0:
            cout<<elementoAleatorio<<endl;
            puntajepc+=25;
            cout<<"la computadora tiene "<<puntajepc<<" puntos ."<<endl;
            break;
            case 1:
            cout<<elementoAleatorio<<endl;
            vidaspc-=1;
            cout<<"la computadora tiene "<< vidaspc<< " vidas ."<<endl;
            break;
            case 2:
            cout<<elementoAleatorio<<endl;
            puntajepc+=10;
            cout<<"la computadora tiene "<<puntajepc<<" puntos ."<<endl;
            break;
            case 3:
            cout<<elementoAleatorio<<endl;
            puntajepc-=15;
            vidaspc-=1;
            cout<<"la computadora tiene "<<vidaspc<<" vidas ."<<endl;
            break;
        }
        
        
        


        cout << endl;
        i=rand()% totalPreguntas;

       
    
    }

    // Mostrar el resultado final
    if (puntaje >= 100 || vidaspc<1) {
        cout << "¡Muy bien hecho! Acabas de vencer a la computadora  :) ." << endl;
    }else{
        cout<<"la computadora te acaba de vencer :( . suerte para la proxima !!"<<endl;
    }
}

string generarParrafo() {
    string parrafos[] = {
        "Estados Unidos es conocido por su diversidad cultural y económica, albergando ciudades icónicas como Nueva York y San Francisco.",
        "China, la nación más poblada del mundo, es famosa por su rica historia, su Gran Muralla y su rápido desarrollo económico.",
        "India, con su colorida cultura y patrimonio, es la cuna de religiones como el hinduismo y el budismo.",
        "Rusia es el país más extenso del mundo, con una historia fascinante que abarca desde los zares hasta la era soviética.",
        "Australia, la isla-continente, destaca por su diversa fauna única, que incluye canguros, koalas y el ornitorrinco.",
        "Brasil, hogar del Carnaval de Río de Janeiro, es conocido por su biodiversidad amazónica y su pasión por el fútbol.",
        "Japón, una nación insular, combina la tradición milenaria con la tecnología moderna, siendo famosa por el monte Fuji y el sushi.",
        "Sudáfrica, con su historia de lucha contra el apartheid, cuenta con paisajes impresionantes, como el Parque Nacional Kruger.",
        "Canadá, el segundo país más grande del mundo, es conocido por su belleza natural, incluyendo las Cataratas del Niágara.",
        "México, cuna de civilizaciones antiguas como los aztecas y los mayas, ofrece una rica cultura, gastronomía y playas hermosas.",
        // Puedes seguir agregando más datos sobre otros países...
    };

    int numParrafos = sizeof(parrafos) / sizeof(parrafos[0]);
    int indice = rand() % numParrafos;
    return parrafos[indice];
}

char generarLetraAleatoria() {
    char letra = 'a' + rand() % 26;
    return letra;
}

int contarLetraEnParrafo(const string& parrafo, char letra) {
    int contador = 0;
    for (char caracter : parrafo) {
        if (tolower(caracter) == tolower(letra)) {
            contador++;
        }
    }
    return contador;
}

void cuenta_datos() {
    srand(time(0));

    int puntaje = 0;
    int vidas = 3;
    int puntajepc=0;
    int vidaspc=3;

    while (puntaje < 100 && puntajepc<100 && vidas >= 1 && vidaspc>=1) {
        string parrafo = generarParrafo();
        this_thread::sleep_for(chrono::seconds(3));
        cout <<endl<< "Párrafo: " << parrafo << endl;

        char letraAleatoria = generarLetraAleatoria();
        this_thread::sleep_for(chrono::seconds(5));
        cout << "¿Cuántas veces aparece la letra '" << letraAleatoria << "' en el párrafo? ";

        // Iniciar temporizador
        auto start = chrono::steady_clock::now();

        int respuestaJugador;
        cin >> respuestaJugador;

        // Detener temporizador y calcular el tiempo transcurrido
        auto end = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();

        // Verificar la respuesta y actualizar el puntaje y las vidas
        int respuestaCorrecta = contarLetraEnParrafo(parrafo, letraAleatoria);
        if(elapsed<=10){
            if (respuestaJugador == respuestaCorrecta ) {
                
                cout << "¡Respuesta correcta! Ganaste 25 puntos." << endl;
                puntaje += 25;
                cout<<"puntaje :"<<puntaje;
                 

                
                
            
            } else {
                
                cout << "Respuesta incorrecta . La cantidad correcta de la letra '" << letraAleatoria << "' es: " << respuestaCorrecta << endl;
                vidas--;
                cout<<"vidas :"<<vidas;// Decrementar vidas si la respuesta es incorrecta o el tiempo se agota
        }

        }else{cout<< "TIEMPO AGOTADO !!"<<endl;
            vidas-=1;
            cout<<"tienes "<< vidas<<" vidas.";
        }
        this_thread::sleep_for(chrono::seconds(2));

        cout<<endl<<endl<<"turno de la computadora.."<<endl;
        this_thread::sleep_for(chrono::seconds(5));

        
        int i=rand()%2;
        if(i==1){
            cout<<endl<<"la respuesta de la computadora es : CORRECTA "<<endl;
            puntajepc+=25;
            cout<<"puntos: "<< puntajepc<< endl;
            
        }else{
            cout<<"la respuesta de la computadora es : INCORRECTA "<<endl;
            vidaspc-=1;
            cout<<" vidas : "<<vidaspc<<endl;
            
        }
        this_thread::sleep_for(chrono::seconds(3));
        cout <<endl<< "Prepárate para la siguiente pregunta..." << endl;
        
        this_thread::sleep_for(chrono::seconds(6));
    }
    
    
    if(puntaje==puntajepc || vidaspc==vidas){
        cout<<"Esto es un EMPATEE ";
    }else{
        
    }

        // Verificar si el jugador ha ganado
    if (puntaje >= 100 || vidaspc<=0) {
        cout << "¡FELICIDADES! Has derrotado a la computadora ¡Ganaste el juego!" << endl;
        
        }else{
            cout<<"ACABAS DE PERDER , suerte para la proxima :( ";
        }
}


int main() {
    // Llamar a la función para jugar el juego del ahorcado
    int eleccion;
    cout << "BIENVENIDOS AL JUEGO DE GEOGRAFIA" << endl;
    cout << "Elige una opción de juego en la que quieras participar" << endl;
    cout << "1- Completar palabra" << endl;
    cout << "2- Te damos letras y nos das palabras" << endl;
    cout << "3- Preguntas y respuestas" << endl;
    cout << "4- Responder información de un texto" << endl;
    cin >> eleccion;
    
    switch(eleccion){
        case 1:
            completarwords();
            break;
        case 2:
            letrastopalabras();
            break;
        case 3:
            jugarpreguntas();
            break;
            
    }

    
    return 0;
}