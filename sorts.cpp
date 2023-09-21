// Example program
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
// #include <iterator>
// #include <numeric>
// #include <cassert>
using namespace std;

/* \ \ \ \ \ / / / / / */
constexpr int CUI = 2000; //
/* / / / / / \ \ \ \ \ */

/* * * * * * * * DECLARACIONES * * * * * * * */

// Máquina de generación de números aleatorios
mt19937 Rand;

// Variables de conteo estadístico
unsigned long long int cont_comparaciones = 0, cont_escrituras = 0;

// Medición de tiempo (en microsegundos) desde transcurrido(true) hasta transcurrido()
typedef uint_fast64_t t_transcurrido; // Definido en microsegundos
constexpr double __MedidaTiempo = 1000000.0;    // Define microsegundos
clock_t __inicio_transcurrido = clock();
inline t_transcurrido transcurrido(bool reiniciar);

inline t_transcurrido transcurrido(bool reiniciar = false) {
  if ( reiniciar ) __inicio_transcurrido = clock();
  return ((__MedidaTiempo*double(clock()-__inicio_transcurrido))/double(CLOCKS_PER_SEC));
};

template < class RandomIt >
void SelectionSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void SelectionSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void HeapSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void HeapSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void InsertionSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void InsertionSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void MergeSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void MergeSort ( RandomIt b, RandomIt e, Compare comp );

template < class RandomIt >
void QuickSort ( RandomIt b, RandomIt e ) ;
template < class RandomIt, class Compare >
void QuickSort ( RandomIt b, RandomIt e, Compare comp );


typedef void ( *t_ordenamiento ) ( vector<int>::iterator, vector<int>::iterator ); // tipo de función de ordenamiento

template < t_ordenamiento >
void EvaluaOrdenamiento ();


/* * * * * * * * IMPLEMENTACIONES * * * * * * * */

template < class RandomIt >
void SelectionSort ( RandomIt b, RandomIt e ) {
  SelectionSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void SelectionSort ( RandomIt b, RandomIt e, Compare comp ) {
  cont_comparaciones = cont_escrituras = 0;
  for (RandomIt s = b; s < e-1; s++) {
    RandomIt m = s;
    for ( RandomIt i = s+1; i < e; i++ ) {
      cont_comparaciones++;
      if ( comp ( *i, *m ) ) m = i;
    }
    if ( m != s ) {
      cont_escrituras+=3; // swap(a,b) escribe t=a;a=b;b=t;
      swap ( *s, *m );
    }
  }
}

template < class RandomIt >
void HeapSort ( RandomIt b, RandomIt e ) {
  HeapSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void HeapSort ( RandomIt b, RandomIt e, Compare comp ) {
  cont_comparaciones = cont_escrituras = 0;
  // Utilizando la heap de std
  make_heap ( b, e );
  sort_heap ( b, e );
}

template < class RandomIt >
void InsertionSort ( RandomIt b, RandomIt e ) {
  InsertionSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void InsertionSort ( RandomIt b, RandomIt e, Compare comp ) {
  cont_comparaciones = cont_escrituras = 0;
  cont_comparaciones = cont_escrituras = 0;
  for(RandomIt s = b; s < e-1; s++) {
    for(RandomIt i = s+1; i > b && comp ( *i, *(i-1) ); --i ) {
      cont_comparaciones++;
      cont_escrituras += 3; // swap(a,b) escribe t=a;a=b;b=t;
      swap ( *i, *(i-1) );
    }
  }
}

template < class RandomIt >
void MergeSort ( RandomIt b, RandomIt e ) {
  MergeSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void MergeSort ( RandomIt b, RandomIt e, Compare comp ) {
  cont_comparaciones = cont_escrituras = 0;
  cont_comparaciones = cont_escrituras = 0;
  if( e-b > 1 ) {
    RandomIt m = b + (e-b)/2;
    MergeSort ( b, m, comp );
    MergeSort ( m, e, comp );
    vector<int> aux ( e-b );
    RandomIt i = b, j = m, k = aux.begin();
    while ( i < m && j < e ) {
      cont_comparaciones++;
      cont_escrituras++;
      if ( comp ( *i, *j ) ) *k++ = *i++;
      else *k++ = *j++;
    }
    while ( i < m ) {
      cont_escrituras++;
      *k++ = *i++;
    }
    while ( j < e ) {
      cont_escrituras++;
      *k++ = *j++;
    }
    copy ( aux.begin(), aux.end(), b );
  }
}

template < class RandomIt >
void QuickSort ( RandomIt b, RandomIt e ) {
  QuickSort ( b, e, less<decltype(*(b))>() );
}

template < class RandomIt, class Compare >
void QuickSort ( RandomIt b, RandomIt e, Compare comp ) {
  cont_comparaciones = cont_escrituras = 0;
  // IMPLEMENTE AQUÍ
}



template < t_ordenamiento _ordenamiento >
void EvaluaOrdenamiento ( string s_ordenamiento ) {
  vector<int> V;

  // Unit Test: verifica si ordena bien
  V.resize(32);
  iota ( V.begin(), V.end(), 0 );
  shuffle ( V.begin(), V.end(), Rand );
  _ordenamiento (V.begin(), V.end());
  for(auto i=V.begin()+1;i<V.end();i++) if (*(i-1)!=*i-1) {
    cout << "NO ORDENA BIEN!!!\n";
    for ( auto &i: V ) cout << i << ", ";
    cout << endl;
    exit(1);
  }

  //Inicia pruebas
  // vector<int> T = {4096,32768,262144,2097152,16777216,134217728,1073741824};
  vector<int> T = {16,64,256,1024,4096,16384};
  Rand.seed(CUI);
  for ( auto t : T ) {
    V.resize(t);
    iota ( V.begin(), V.end(), 0 );
    shuffle ( V.begin(), V.end(), Rand );
    cout << s_ordenamiento << '\t' << t << '\t';
    transcurrido(true);
    _ordenamiento (V.begin(), V.end());
    cout << transcurrido() << '\t';
    cout << cont_comparaciones << '\t';
    cout << cont_escrituras << endl;
  }
}


int main() {
  vector<int> V;

  EvaluaOrdenamiento<&SelectionSort>("Sel");
  EvaluaOrdenamiento<&HeapSort>("Heap");
  EvaluaOrdenamiento<&sort>("sort");

  // EvaluaOrdenamiento<&InsertionSort>("Ins");
  // EvaluaOrdenamiento<&MergeSort>("Merge");
  // EvaluaOrdenamiento<&QuickSort>("Quick");

}




//
