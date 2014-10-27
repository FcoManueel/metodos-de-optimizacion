/*
    n-queens problem using gradient descendent method.
    Francisco Manuel Valle Ruiz
    September 2013
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void n_queens_grad_desc(int *queens, const int num_queens); // 8 queens using gradient descendent. Recieves an array of num_queens*2 integers
void fill_board(int *queens, const int num_queens);
void copy_board(const int* original, int* copy, const int num_queens);
bool repeated_queens(const int *queens, const int num_queens);
bool is_valid_board(const int *queens, const int num_queens);
void check_move(const int *aux_queens, int *best_queens, const int num_queens, int &best_cost);
int cost(const int *queens, const int num_queens);
bool set_next_pos(int *queens, const int num_queens);

void print_array(const int *a, const int size);
void print_queen_array(const int *a, const int num_queens);
void print_board(const int *queens, const int num_queens);
//void new_print_board(const int *queens, const int num_queens);
void print_board_status(const int *queens, const int num_queens);

int main(){
    int *queens;
    int num_queens = 8;
    queens = new int[num_queens*2];
    n_queens_grad_desc(queens, num_queens);
    //fill_board(queens, num_queens);

    cout << "El resultado es ";
    print_queen_array(queens, num_queens);
    print_board(queens, num_queens);
    //print_board(queens);

    //cin.ignore();
    //cin.get();
}

//////////////////////////
//
//   Gradient Descendent
//
//////////////////////////

void n_queens_grad_desc(int *queens, const int num_queens){
    srand(time(NULL));
    fill_board(queens, num_queens);

    cout << "\tProblema de las "<< num_queens <<" reinas.\n";
    cout << "...calculando resultado usando el m"<<char(130)<<"todo del gradiente descendiente...\n";

     while(cost(queens, num_queens))
        if(set_next_pos(queens, num_queens) == false) fill_board(queens, num_queens); //If it fails, restart (randomly re-fill board)
    cout << "...solucion encontrada!\n\n";
}

void fill_board(int *queens, const int num_queens){
    int size = num_queens*2;
    for(int i = 0; i < size; i+=2){
        queens[i] = rand()%num_queens + 1;
        queens[i+1] = rand()%num_queens + 1;
        for(int j = 0; j < i; j+=2)
            if((queens[i] == queens[j]) && (queens[i+1] == queens[j+1])) i -= 2;
    }
}

int cost(const int *queens, const int num_queens){
    int cost = 0;
    int size = num_queens*2;

    for(int i=0; i<size; i+=2){
        for(int j=0; j<i; j+=2){
            if( (queens[j]==queens[i]) ||                           // Comparten columna
                (queens[j+1]==queens[i+1]) ||                       // Comparten fila
                (queens[j+1]-queens[j] == queens[i+1]-queens[i]) || // Comparten diagonal descendente
                (queens[j]+queens[j+1] == queens[i]+queens[i+1]) ){ // Comparten diagonal ascendente
                   ++cost;
                   // cout << "La reina ("<<queens[i]<<","<<queens[i+1]<<") entra en conflicto con la reina ("<<queens[j]<<","<<queens[j+1]<<").\n";
            }
        }
    }
    return cost;
}
void copy_board(const int* original, int* copy, const int num_queens){ // Copies the content of'original' in 'copy'
    int size = num_queens*2;
    for(int i = 0; i < size; ++i)
        *(copy + i) = *(original + i);
}

bool repeated_queens(const int *queens, const int num_queens){
    int size = num_queens*2;
    for(int i = 0; i < size; i+=2){
        for(int j = 0; j < i; j+=2)
            if((queens[i] == queens[j]) && (queens[i+1] == queens[j+1])) return true;
    }
    return false;
}

bool is_valid_board(const int *queens, const int num_queens){
    int size = num_queens*2;
    for(int i = 0; i < size; ++i) if(queens[i]<1 || queens[i]>num_queens) return false;
    return !repeated_queens(queens, num_queens);
}

void check_move(const int *aux_queens, int *best_queens, const int num_queens, int &best_cost){
    int aux_cost;

    if(is_valid_board(aux_queens, num_queens)){
        aux_cost = cost(aux_queens, num_queens);
        if(aux_cost < best_cost){
            best_cost = 0;
            copy_board(aux_queens, best_queens, num_queens);
        }
    }
}

bool set_next_pos(int *queens, const int num_queens){
    int *aux_queens, *best_queens;
    aux_queens = new int[num_queens*2];
    best_queens = new int[num_queens*2];
    if(!aux_queens || !best_queens) return false; // In case there's no memory available return false :(

    int original_cost, best_cost;
    original_cost = cost(queens, num_queens);
    best_cost = original_cost;
    copy_board(queens, aux_queens, num_queens);

    for(int i = 0; i < num_queens; ++i){
        // Move queen to up-left square
        --aux_queens[i];
        --aux_queens[i+1];
        check_move(aux_queens, best_queens, num_queens, best_cost);

        ++aux_queens[i]; // Move queen to up square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        ++aux_queens[i]; // Move queen to up-rigth square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        ++aux_queens[i+1]; // Move queen to right square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        ++aux_queens[i+1]; // Move queen to down-right square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        --aux_queens[i]; // Move queen to down square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        --aux_queens[i]; // Move queen to down-left square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        --aux_queens[i+1]; // Move queen to left square
        check_move(aux_queens, best_queens, num_queens, best_cost);

        ++aux_queens[i]; // Return to original position
    }
    if(best_cost < original_cost){
        copy_board(best_queens, queens, num_queens);
        return true;
    }else{
        return false; // Means there's no better position than the actual
    }
}



/////////////////////
//
//   Formatting
//
/////////////////////

void print_array(const int *a, const int size){
    cout << "( ";
    for(int i = 0; i<size; ++i){
        cout << *(a+i) << "  ";
    }
    cout << "\b)\n";
}

void print_queen_array(const int *a, const int num_queens){
    int size = num_queens*2;
    cout << "(";
    for(int i = 0; i<size; ++i){
        cout << "[" << *(a+i);
        ++i;
        cout << ","<< *(a+i) << "], ";
    }
    cout << "\b\b)\n";
}

void print_board(const int *queens, const int num_queens){
    int *aux;
    aux = new int[num_queens];
    for(int i = 0; i < num_queens; ++i) aux[queens[i*2]-1] = queens[i*2+1];

    cout << "\n----------------- Tablero "<< num_queens << "x" << num_queens <<" -----------------\n\t";
    for(int j = 0; j<num_queens; ++j){ // One iteration per row
        for(int i = 0; i<num_queens; ++i){ // One iteration per element
            cout << (*(aux+i) == (j+1) ? 'x' : '-');
            cout << "  ";
        }
        cout << "\n\t";
    }
    cout << "\n";
}

void print_board_status(const int *queens, const int num_queens){
    int size = num_queens*2;
    int costo = cost(queens,num_queens);
    cout << (costo ? "Fail-" : "Exito!-");
    cout << "costo:" << costo << " tablero:";
    print_queen_array(queens, num_queens);
    cout << "\n";
}
