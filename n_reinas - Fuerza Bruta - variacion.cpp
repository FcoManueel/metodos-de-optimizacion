#include <iostream>
#include <cstdlib>
#include <ctime>
#define NUM_REINAS 8
using namespace std;

void imprimir_arreglo(int *a, int size);
void imprimir_tablero(int *reinas);

int nuevas_reinas(int *reinas);
int num_ataques(int *reinas);


int main(){
    int *reinas;
    int min_ataques_local;
    int min_ataques_total = 999; // 999 es un numero arbitrario, para asegurar que min_ataques_total se modifique en el futuro
    reinas = new int[NUM_REINAS];

    for(int rep = 0; rep < 100000; ++rep ){
        srand(time(NULL)+rep*5);
        min_ataques_local = nuevas_reinas(reinas);
        if(min_ataques_local < min_ataques_total) min_ataques_total = min_ataques_local;
        if(min_ataques_total == 0) cout << "Se pudo resolver el problema en la iteracion "<<rep<<"\n";
    }
    cout << "La menor cantidad de ataques fue "<<min_ataques_total<<"\n";
}

int nuevas_reinas(int *reinas){

    for(int i = 0; i < NUM_REINAS; ++i){
        *(reinas+i) = rand() % NUM_REINAS + 1;
    }
    //imprimir_arreglo(reinas, NUM_REINAS);
    return num_ataques(reinas);
}

int num_ataques(int *reinas){
    int num_ataques = 0;

    for(int i=0; i<NUM_REINAS; ++i){
        for(int j=i; j<NUM_REINAS; ++j){
            if((*(reinas+i) == *(reinas+j)) ||
               (*(reinas+j) == *(reinas+i)) ||
               (j- *(reinas+j) == i-(*(reinas+i))) ||
               (j+ *(reinas+j) == i+(*(reinas+i)))){
                   ++num_ataques;
               }
        }
    }
    //cout << "Se produjeron "<<num_ataques<<" ataques.\n";
    return num_ataques;
}

void imprimir_arreglo(int *a, int size){
    cout << "( ";
    for(int i = 0; i<size; ++i){
        cout << *(a+i) << "  ";
    }
    cout << "\b)\n";
}

void imprimir_tablero(int *reinas){
    cout << "\n----------------- Tablero "<< NUM_REINAS << "x" << NUM_REINAS <<" -----------------\n\t";
    for(int j = 0; j<NUM_REINAS; ++j){ // Un ciclo por renglon
        for(int i = 0; i<NUM_REINAS; ++i){ // Un ciclo por elemento
            cout << (*(reinas+i) == (j+1) ? 'x' : '-');
            cout << "  ";
        }
        cout << "\n\t";
    }
    cout << "\n";
}
