#include <iostream>
#include <cmath>    // sqrt()
#include <cstdlib>  // rand()
#include <ctime>    // time()
#include <vector>
using namespace std;
#define SIZE 12

struct Punto;
void ingresar_puntos(vector<Punto> &vmap);
void llenar_vector_distancias(vector<Punto> &vmap, vector<double> &vdist);
void actualizar_vector_distancias(vector<Punto> &vmap, vector<double> &vdist);
float vdistancia(Punto a, Punto b);
double sum(const vector<double> v);
void swap(vector<Punto> &vmap, int j, int k);
void swap(int &i, int &j);
void region_swap(vector<Punto> &vmap, int j, int k);
void imprimir_dist(const vector<double> vdist);
void imprimir_puntos(const vector<Punto> &vmap);

struct Punto
{
    double x;
    double y;
    Punto(double x_, double y_) : x(x_), y(y_){}
    void imprimir(){ cout << "(" << x << ", " << y << ")" ;}
};

int main(){
    srand(time(NULL));

    vector<Punto> vmap;
    vmap.reserve(SIZE);
    ingresar_puntos(vmap);
    int n = vmap.size();

    vector<double> vdist;
    vdist.reserve(SIZE);
    llenar_vector_distancias(vmap, vdist);

    double temp = 500.0;   // temperatura incial del sistema
    double rate = 0.995;   // ritmo al que disminuye temp (temp = rate*temp)
    double delta_s;        // diferencia entre sol. actual y sol. siguiente
    double dist_actual = sum(vdist);
    double vdist_candidata;
    double mejor_dist = dist_actual;
    vector<Punto> mejor_map;
    bool continuar = true; // condicion de paro

    cout << "****Datos iniciales \n";
    imprimir_puntos(vmap);
    imprimir_dist(vdist);
    cout << "------------------\n";
    region_swap(vmap, 0, 11);

    while(continuar){
        int j, k;
        j = rand() % n;
        do{
            k = rand() % n;
        }while(j == k);

        region_swap(vmap, j, k);
        actualizar_vector_distancias(vmap, vdist); // deberia de ser "actualizar_dist" en lugar de "llenar_vector_distancias", mejorar luego
        vdist_candidata = sum(vdist);

        delta_s = vdist_candidata - dist_actual;
        if(delta_s <= 0 || ((double)rand() / RAND_MAX) <= exp(-1.0*delta_s / temp)){
            dist_actual = vdist_candidata;
            //mejor_dist = (dist_actual < mejor_dist ? dist_actual : mejor_dist);
            if(dist_actual < mejor_dist){
                mejor_dist = dist_actual;
                mejor_map = vmap;
            }
        }else{
            region_swap(vmap, j, k); //deshacer cambios hechos al generar vecino
        }

        temp = rate*temp;
        continuar = (temp > 0.000001);

    }

    cout << "****Datos finales \n";
    imprimir_puntos(vmap);
    imprimir_dist(vdist);
    cout << "------------------\n";
    imprimir_puntos(mejor_map);
    cout << "Mejor vdistancia " << mejor_dist << "\n";

}

float vdistancia(Punto a, Punto b){
    return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void llenar_vector_distancias(vector<Punto> &vmap, vector<double> &vdist){
    int n = vmap.size(); // tamanio del vector
    vdist.begin();

    for(int i = 0; i < n-1; ++i){
        vdist.push_back( vdistancia(vmap[i], vmap[i+1]) );
    }
    vdist.push_back( vdistancia(vmap[n-1], vmap[0]) );
}

void actualizar_vector_distancias(vector<Punto> &vmap, vector<double> &vdist){
    int n = vmap.size(); // tamanio del vector
    for(int i = 0; i < n-1; ++i){
        vdist[i] = vdistancia(vmap[i], vmap[i+1]);
    }
    vdist[n-1] = vdistancia(vmap[n-1], vmap[0]);
}

void ingresar_puntos(vector<Punto> &vmap){
    vmap.push_back( Punto(0, 0) );
    vmap.push_back( Punto(0, 1) );
    vmap.push_back( Punto(0, 2) );
    vmap.push_back( Punto(0, 3) );
    vmap.push_back( Punto(1, 0) );
    vmap.push_back( Punto(1, 3) );
    vmap.push_back( Punto(2, 0) );
    vmap.push_back( Punto(2, 3) );
    vmap.push_back( Punto(3, 0) );
    vmap.push_back( Punto(3, 1) );
    vmap.push_back( Punto(3, 2) );
    vmap.push_back( Punto(3, 3) );
}

void imprimir_puntos(const vector<Punto> &vmap){
    int i = 0;
    cout << "Puntos: \n";
    for(Punto p : vmap){
        cout << "  " << i++ << ":";
        p.imprimir();
        cout << " \n";
    }
    cout << "\n";
}
void imprimir_dist(const vector<double> vdist){
    int i = 0;
    cout << "Distancias: \n";
    for(double d : vdist){
        //cout << "  d"<<i++<<"-"<<i << ":   "<<d;
        cout << "  d"<<i<<"-"<<i++ << ":   "<<d;
        cout << "\n";
    }
    cout << "    Distancia total: " << sum(vdist);
    cout << "\n";
}

double sum(const vector<double> v){
    double sum = 0;
    for(double num : v) sum += num;
    return sum;
}

void swap(vector<Punto> &vmap, int j, int k){
    Punto aux = vmap[j];
    vmap[j] = vmap[k];
    vmap[k] = aux;
}

void region_swap(vector<Punto> &vmap, int j, int k){
    if(k < j) swap(j,k);
    int n = (k-j+1) / 2;

    for(int i = 0; i < n; ++i) swap(vmap, j+i, k-i);
}

void swap(int &i, int &j){
    int aux = i;
    i = j;
    j = aux;
}


/*
0 1 2 3 4 5 6 7 8 9

3 5

5-3+1 = 3
3/2 = 1

swap (3+0, 5-0) = swap (3, 5)
    0 1 2 5 4 3 6 7 8 9
//swap (3+1, 5-1) = swap (4, 4)
//    0 1 2 5 4 3 6 7 8 9



0 1 2 3 4 5 6 7 8 9
3 6

6-3+1 = 4
4/2 = 2

swap (3+0, 6-0) = swap (3, 6)
    0 1 2 6 4 5 3 7 8 9
swap (3+1, 6-1) = swap (4, 5)
    0 1 2 6 5 4 3 7 8 9
//swap (3+2, 6-2) = swap (5, 4)
//    0 1 2 6 4 5 3 7 8 9



0 1 2 3 4 5 6 7 8 9
1 7

7-1+1 = 7
7/2 = 3

swap (1+0, 7-0) = swap (1, 7)
    0 7 2 3 4 5 6 1 8 9
swap (1+1, 7-1) = swap (2, 6)
    0 7 6 3 4 5 2 1 8 9
swap (1+2, 7-2) = swap (3, 5)
    0 7 6 5 4 3 2 1 8 9

//swap (3+2, 6-2) = swap (5, 4)
//    0 1 2 6 4 5 3 7 8 9

*/
