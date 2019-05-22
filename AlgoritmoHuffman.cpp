#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;



/*  constantes */
#define LONJITUDMAXarchivo 100
#define ALTURAMAXARBOL 100


/* funciones */
void agregarCaracter(char);
void agregarCaracterAlArreglo(char,int);	

/* variables */
char caracteres[LONJITUDMAXarchivo];
int frecuencias[LONJITUDMAXarchivo];
int indiceCaracteres = 0; 

/*  estructuras */


int main(int argc, char** argv) {
      printf("\n\t\tAlgoritmo de huffman \n\n");	
      ifstream archivo("archivo.txt");
      int tamanio = 1;

      
      char caracter;
      while (archivo.get(caracter)){
         agregarCaracter(caracter);
      }                  // lo
      
  /*     if(archivo.fail()){
         
         system("pause");
         exit(0);
      }else{
         do{
           char caracter;
            archivo >> caracter;
            printf("indice %c \n",caracter);
           // 

         }while (!archivo.eof());
         archivo.close(); 
   

         
      archivo.close();
      } */
      printf("\n\n");
      for (int indice = 0; indice < indiceCaracteres; indice++){
               printf("%c - %i \n",caracteres[indice],frecuencias[indice]);
      }
      
         
         
      /* 	 
         ofstream fs("nombre.txt"); 
         fs << "prueba hola mundo" << endl;
         fs.close();
      */

    cout<<"\n\n";
    system("pause");
    return 0;

}


void agregarCaracter(char caracter){
      int bandera = 0;
      for (int indice = 0; indice < indiceCaracteres; indice++){
         if(caracter == caracteres[indice]){
               bandera = 1;
               frecuencias[indice]++;
               printf("%c = %c aumentando la frecuencia %i \n",caracter,caracteres[indice],frecuencias[indice]);
         } else {
               bandera = 0;
               printf("  %c != %c ",caracter,caracteres[indice]);
         }
      }
      
      if(bandera == 0){
         caracteres[indiceCaracteres] = caracter;
         frecuencias[indiceCaracteres] = 1;
         indiceCaracteres++; 
         printf("agregando caracter %c \n",caracter);
      } 
}

