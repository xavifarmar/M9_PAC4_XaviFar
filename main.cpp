#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

bool ganador = false;  // Variable para determinar si hay un ganador
const int meta = 50;   // Distancia de la meta
mutex mtx;            // Mutex para proteger la variable ganador

// FunciÃ³n para simular el movimiento de un animal
void correr(const string& nombre, const string& simbolo) {
    int distancia = 0; 
    srand(static_cast<unsigned>(time(0) + distancia)); // Semilla para nÃºmeros aleatorios

    while (distancia < meta && !ganador) {
        // Genera un nÃºmero aleatorio para el avance
        int avance = rand() % 5 + 1;  // NÃºmero aleatorio entre 1 y 5
        this_thread::sleep_for(chrono::milliseconds(100 * avance)); // Pausa para simular movimiento
        distancia += avance; // Incrementa la distancia

        // Bloquea el acceso a la variable ganador para actualizar la consola
        mtx.lock();
        cout << nombre << ": " << string(distancia, '.') << simbolo << endl;  // VisualizaciÃ³n
        mtx.unlock();
        
        // Comprobar si ganÃ³
        if (distancia >= meta) {
            mtx.lock();
            if (!ganador) {
                ganador = true; 
                cout << nombre << " ha ganado la carrera!" << endl; // Anuncio de victoria
            }
            mtx.unlock();
        }
    }
}

int main() {
    // Crear hilos para cada animal
    thread t1(correr, "Conejo", "ðŸ‡");
    thread t2(correr, "Tortuga", "ðŸ¢");
    thread t3(correr, "Perro", "ðŸ•");

    // Esperar a que todos los hilos terminen
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
