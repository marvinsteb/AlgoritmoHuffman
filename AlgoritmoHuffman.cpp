#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;

/*  constantes */
#define LONJITUDMAXARCHIVO 100
#define ALTURAARBOL 100


/*  prototipos de funciones */
void agregarCaracter(char);
void agregarCaracterAlArreglo(char,int);
void arbolDIntercambio(struct Nodo **, struct Nodo **);
void codigicarArreglo(char[], int[], int);	

/* variables */
char caracteres[LONJITUDMAXARCHIVO];
int frecuencias[LONJITUDMAXARCHIVO];
int resultado[1000];
int indiceCaracteres = 0; 
int indiceResultado = 0;

/* estructuras para el arbol huffman */
struct Nodo{
    char caracter;
    unsigned frecuencia;
    struct Nodo *izquierda, *derecha;
};
struct NodoRaiz{
    unsigned altura;
    unsigned capacidad;
    struct Nodo **array;
};

struct Nodo *nuevoNodo(char caracter, unsigned frecuencia){
    struct Nodo *temporal = (struct Nodo *)malloc(sizeof(struct Nodo));
    temporal->izquierda = temporal->derecha = NULL;
    temporal->caracter = caracter;
    temporal->frecuencia = frecuencia;
    return temporal;
}

struct NodoRaiz *crearNodoRaiz(unsigned capacidad){

    struct NodoRaiz *ndRaiz = (struct NodoRaiz *)malloc(sizeof(struct NodoRaiz));
    ndRaiz->altura = 0;
    ndRaiz->capacidad = capacidad;
    ndRaiz->array = (struct Nodo **)malloc(ndRaiz->capacidad * sizeof(struct Nodo *));
    return ndRaiz;
}

int main(int argc, char** argv) {
      printf("\n\t\tAlgoritmo de huffman \n\n");	
      ifstream archivo("archivo.txt");    
      char caracter;
      while (archivo.get(caracter)){
         agregarCaracter(caracter);
      }
      printf("\n\n Frecuencias de cada caracter \n");
      for (int indice = 0; indice < indiceCaracteres; indice++){
               printf("%c : %i \n",caracteres[indice],frecuencias[indice]);
      }
      remove("archivo2.txt");
      printf("\n\n Codificando caracteres, utilizando el algoritmo de huffman \n");    
      codigicarArreglo(caracteres,frecuencias,indiceCaracteres);
      printf("\n\n");
      system("pause");
      return 0;

}
/*  cuenta las frecuencias de cada caracter del archivo */

void agregarCaracter(char caracter){
      int bandera = 0;
      for (int indice = 0; indice < indiceCaracteres; indice++){
         if(caracter == caracteres[indice]){
               bandera = 1;
               frecuencias[indice]++;
               printf(" %c = %c frecuencia %i \n",caracter,caracteres[indice],frecuencias[indice]);
         } else {
               printf(" %c != %c \n",caracter,caracteres[indice]);
         }
      }
      
      if(bandera == 0){
         caracteres[indiceCaracteres] = caracter;
         frecuencias[indiceCaracteres] = 1;
         indiceCaracteres++; 
         printf("agregando caracter %c \n",caracter);
      } 
}


void arbolDIntercambio(struct Nodo **a, struct Nodo **b){
    struct Nodo *t = *a;
    *a = *b;
    *b = t;
}

void crearArbolInicial(struct NodoRaiz *ndRaiz, int indice){
    int alturaInicial = indice;
    int izquierda = 2 * indice + 1;
    int derecha = 2 * indice + 2;

    if (izquierda < ndRaiz->altura && ndRaiz->array[izquierda]->frecuencia < ndRaiz->array[alturaInicial]->frecuencia)
        alturaInicial = izquierda;

    if (derecha < ndRaiz->altura && ndRaiz->array[derecha]->frecuencia < ndRaiz->array[alturaInicial]->frecuencia)
        alturaInicial = derecha;

    if (alturaInicial != indice){
        arbolDIntercambio(&ndRaiz->array[alturaInicial], &ndRaiz->array[indice]);
        crearArbolInicial(ndRaiz, alturaInicial);
    }
}

int AlturaInicial(struct NodoRaiz *ndRaiz){
    return (ndRaiz->altura == 1);
}

struct Nodo *extrarValorMinimo(struct NodoRaiz *ndRaiz){
    struct Nodo *temporal = ndRaiz->array[0];
    ndRaiz->array[0] = ndRaiz->array[ndRaiz->altura - 1];

    --ndRaiz->altura;
    crearArbolInicial(ndRaiz, 0);

    return temporal;
}

void incertarNodoRaiz(struct NodoRaiz *ndRaiz, struct Nodo *nodoInicio){
    ++ndRaiz->altura;
    int indice = ndRaiz->altura - 1;

    while (indice && nodoInicio->frecuencia < ndRaiz->array[(indice - 1) / 2]->frecuencia){
        ndRaiz->array[indice] = ndRaiz->array[(indice - 1) / 2];
        indice = (indice - 1) / 2;
    }

    ndRaiz->array[indice] = nodoInicio;
}

void costruirNodoArbol(struct NodoRaiz *ndRaiz){
    int n = ndRaiz->altura - 1;
    int indice;
    for (indice = (n - 1) / 2; indice >= 0; --indice)
        crearArbolInicial(ndRaiz, indice);
}

void imprimeAregloCodificado(int arregloCaracteres[], int n){
    int indice;
    for (indice = 0; indice < n; ++indice)
        printf("%i", arregloCaracteres[indice]);

    printf( "\n");
}


void creaArregloBitsFinal(int arregloCaracteres[], int altura){
    char caracter;    
     ifstream archivo("archivo2.txt");  
      while (archivo.get(caracter)){
         resultado[indiceResultado] = caracter;
         indiceResultado++;
      }        
     archivo.close();
           for (int indice = 0; indice < altura; ++indice){
            printf("%i", arregloCaracteres[indice]);
            resultado[indiceResultado] = arregloCaracteres[indice];
            indiceResultado++;
      } 
      printf( "\n");

}

int esHoja(struct Nodo *raiz){
    return !(raiz->izquierda) && !(raiz->derecha);
}

struct NodoRaiz *createAndBuildMinHeap(char caracter[], int frecuencia[], int altura){
    struct NodoRaiz *ndRaiz = crearNodoRaiz(altura);

    for (int indice = 0; indice < altura; ++indice)
        ndRaiz->array[indice] = nuevoNodo(caracter[indice], frecuencia[indice]);

    ndRaiz->altura = altura;
    costruirNodoArbol(ndRaiz);

    return ndRaiz;
}

struct Nodo *costruirArbolHufman(char caracter[], int frecuencia[], int altura){
    struct Nodo *izquierda, *derecha, *inicio;

    struct NodoRaiz *ndRaiz = createAndBuildMinHeap(caracter, frecuencia, altura);

    while (!AlturaInicial(ndRaiz)) {

        izquierda = extrarValorMinimo(ndRaiz);
        derecha = extrarValorMinimo(ndRaiz);

        inicio = nuevoNodo('$', izquierda->frecuencia + derecha->frecuencia);

        inicio->izquierda = izquierda;
        inicio->derecha = derecha;

        incertarNodoRaiz(ndRaiz, inicio);
    }

    return extrarValorMinimo(ndRaiz);
}

void imprimeCaracteres(struct Nodo *raiz, int arregloCaracteres[], int inicio){

    if (raiz->izquierda){
        arregloCaracteres[inicio] = 0;
        imprimeCaracteres(raiz->izquierda, arregloCaracteres, inicio + 1);
    }

    if (raiz->derecha){
        arregloCaracteres[inicio] = 1;
        imprimeCaracteres(raiz->derecha, arregloCaracteres, inicio + 1);
    }

    if (esHoja(raiz)){
        printf("%c : ",raiz->caracter);
        imprimeAregloCodificado(arregloCaracteres, inicio);
    }
}


void creaCadenaDeBitsFinal(struct Nodo *raiz, int arregloCaracteres[], int inicio, char caracter ){

    if (raiz->izquierda){
        arregloCaracteres[inicio] = 0;
        creaCadenaDeBitsFinal(raiz->izquierda, arregloCaracteres, inicio + 1,caracter);
    }

    if (raiz->derecha){
        arregloCaracteres[inicio] = 1;
        creaCadenaDeBitsFinal(raiz->derecha, arregloCaracteres, inicio + 1,caracter);
    }

    if (esHoja(raiz)){
        if(raiz->caracter == caracter){
             printf("%c : ",raiz->caracter);
            creaArregloBitsFinal(arregloCaracteres, inicio);
        }
        
    }
}


void encriptarArchivo(){
    printf("\n resultado del archivo ");

     ofstream archivo2("archivo2.txt");
      
    if(archivo2.fail()){
    	printf("error al crear el archivo \n");
    } else {

       for (int indice = 0; indice < indiceResultado; ++indice){
        printf("%i",resultado[indice]);   
        archivo2 << resultado[indice];
      }
	archivo2.close();
    }
}

void codigicarArreglo(char caracter[], int frecuencia[], int altura){
    struct Nodo *raiz = costruirArbolHufman(caracter, frecuencia, altura);

    int arregloCaracteres[ALTURAARBOL], inicio = 0;

    imprimeCaracteres(raiz, arregloCaracteres, inicio);
      printf("\n encriptando...\n");
      ifstream archivo("archivo.txt");    
      char caracterArchivo;
      while (archivo.get(caracterArchivo)){
         creaCadenaDeBitsFinal(raiz,arregloCaracteres,inicio,caracterArchivo);
      }
      encriptarArchivo();
    
}

