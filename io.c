#include "struct.h"
#include "funciones.h"
#include "io.h"

/*
Entradas: Nombre de la imagen
Funcionamiento: Funcion que valida que exista la imagen en el directorio dado
Salida: Entero (0 o 1)
*/
int validarArchivoEntrada(char* entrada){  

    //Se abre el archivo de entrada
    int nombreImagen = open(entrada, O_RDONLY);

    //Se comprueba la existencia del archivo de entrada
    if(nombreImagen == -1){
        printf("\nNo existe el archivo o se encuenta en otra ubicacion.\n");
        exit(-1);
    }
    else{
        return 1;
    }
    
}

/*
Entradas: Bandera x Filas de la imagen con zoom x Columnas de la imagen con zoom
Funcionamiento: Funcion que comprueba el valor de la bandera, y en caso de ser 1, muestra las dimensiones de la imagen con zoom
                por pantalla
Salida: No tiene
*/
void flag(int band, int filasZ, int columnasZ){

    //Se comprueba que exista la bandera
    if(band){
        //Si existe la bandera, se imprime por pantalla el valor de las filas y columnas de la imagen con zoom
        printf("\nLas filas de la imagen con zoom son: %d", filasZ);
        printf("\nLas columnas de la imagen con zoom son: %d\n", columnasZ);
    }

}

/*
Entradas: Nombre del archivo de entrada x Filas de la imagen x Columnas de la imagen
Funcionamiento: Funcion que lee una imagen en formato ".raw", le asigna memoria a una matriz  y
                almacena los datos de la imagen en dicha matriz.
Salida: No tiene
*/
void leerImagen(char* entrada, int filas, int columnas){

    if(validarArchivoEntrada(entrada) == 1){

        //Se asigna memoria a la matriz que contendra los elementos de la imagen
        matrizImagen = (float **)malloc(filas * sizeof(float*));
        for(int i = 0; i < filas; i++){
            matrizImagen[i] = (float *)malloc(columnas * sizeof(float));
        }

        //Se abre el archivo en modo lectura "rb", el cual abre archivos binarios
        FILE* archivo = fopen(entrada, "rb");

        //Se almacena todo el contenido de la imagen en una matriz
        for(int i = 0; i < filas; i++){
            fread(matrizImagen[i], sizeof(float), columnas, archivo);
        }

        fclose(archivo);
    }

}
    
/*
Entradas: Nombre del archivo de salida x Matriz a escribir x Filas de la imagen con zoom x Columnas de la imagen con zoom
Funcionamiento: Funcion que escribe un archivo en formato ".raw" con el contenido de una matriz
Salida: No tiene
*/
void escribirResultados(char* nombre, float** matrizConZoom, int filasZ, int columnasZ){

    FILE* archivo = fopen(nombre, "wb");

    //Se recorre la matriz y se escribe en un archivo binario el contenido de esta
    for(int z = 0; z < filasZ; z++){
        fwrite(matrizConZoom[z], sizeof(float), columnasZ, archivo);
    }

    fclose(archivo);

}