#include <iostream>
#include <fstream>
using namespace std;

#define LONJITUDMAXarchivo 100


int main(int argc, char** argv) {
   char caracteres[LONJITUDMAXarchivo];
   char frecuencia[LONJITUDMAXarchivo];
   int indice = 0;

   
   cout<<"\n\t\tAlgoritmo de huffman \n\n";
  

   ifstream archivo;
   archivo.open("archivo.txt"); 

    if(archivo.fail()){
   	printf("Error en el archivo \n");
    system("pause");
    exit(0);
   }else{
   	do{
         char caracter;
         archivo >> caracter;
         cout<<caracter<<endl;

    	}while (!archivo.eof());
      archivo.close();
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

