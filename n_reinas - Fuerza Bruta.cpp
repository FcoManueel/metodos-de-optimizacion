#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void imprimir_arreglo(int *a, int size);
void imprimir_tablero(int *reinas, int num_reinas);

void n_reinas(int *reinas, int num_reinas);
bool nueva_reina(int *reinas, int i, int num_reinas);
bool reina_valida(int *reinas, int i, int candidata);

int main(){
    int *reinas;
    int num_reinas = 8;
    reinas = new int[num_reinas];
    //int num_resultados = 1;
    //for(int rep = 1; rep <= num_resultados; ++rep ){
        n_reinas(reinas, num_reinas);

        //cout << "El resultado "<< rep <<" es ";
        cout << "El resultado es ";
        imprimir_arreglo(reinas, num_reinas);
        imprimir_tablero(reinas, num_reinas);
    //}
}

void n_reinas(int *reinas, int num_reinas){
    srand(time(NULL));
    int intentos = 1;

    for(int i = 0; i < num_reinas; ++i){
        if( nueva_reina(reinas, i, num_reinas) == false){
            //cout << "\nFallo el intento << ++intentos <<: ";
            //imprimir_arreglo(reinas, i+1); // i+1 para imprimir con que elemento se produjo el fallo
            i = 0;
            ++intentos;
        }
    }
    //cout << "Se realizaron "<< intentos <<" intentos para resolver el problema de las "<< num_reinas <<" reinas.\n";

    cout << "\tProblema de las "<< num_reinas <<" reinas.\n";
}

void imprimir_arreglo(int *a, int size){
    cout << "( ";
    for(int i = 0; i<size; ++i){
        cout << *(a+i) << "  ";
    }
    cout << "\b)\n";
}

void imprimir_tablero(int *reinas, int num_reinas){
    cout << "\n----------------- Tablero "<< num_reinas << "x" << num_reinas <<" -----------------\n\t";
    for(int j = 0; j<num_reinas; ++j){ // Un ciclo por renglon
        for(int i = 0; i<num_reinas; ++i){ // Un ciclo por elemento
            cout << (*(reinas+i) == (j+1) ? 'x' : '-');
            cout << "  ";
        }
        cout << "\n\t";
    }
    cout << "\n";
}

bool nueva_reina(int *reinas, int i, int num_reinas){
    int candidata;
    candidata = rand() % num_reinas + 1;

    for(int intentos = 0; intentos < num_reinas; ++intentos){
        if(reina_valida(reinas, i, candidata)){
            *(reinas+i) = candidata;
            return true;
        }

        candidata = candidata%num_reinas + 1;
    }

    *(reinas+i) = candidata;
    return false;
}

bool reina_valida(int *reinas, int i, int candidata){
    for(int j=0; j<i; ++j){
        if((*(reinas+j) == candidata) ||
           (j- *(reinas+j) == i-candidata) ||
           (j+ *(reinas+j) == i+candidata) ){
               return false;
           }
    }
    return true;
}
