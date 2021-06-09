/*
Autor: Jordan Godoy
*/

#include "struct.h"
#include "funciones.h"
#include "io.h"

//Funcion principal
int main(int argc, char** argv){

    //Variable para el switch-case
    int c;

    char* extension;

    //Se le asigna memoria a las estructuras
    struct datos *dato = (struct datos*)calloc(1, sizeof(struct datos));
    struct datosZoom *dz = (struct datosZoom*)calloc(1, sizeof(struct datosZoom));

    if(argc > 14){
        printf("\nLa cantidad de parametros de entrada ingresados excede la cantidad solicitada.\n");
        return 0;
    }
    else if(argc < 12){
        printf("\nLa cantidad de parametros de entrada ingresados es menor a la cantidad solicitada.\n");
        return 0;
    }

    //getopt
    else{
        while((c = getopt(argc, argv, "I:O:M:N:r:g:b")) != -1){
            switch(c){
                case 'I':
                    dato->imagenEntrada = optarg;
                    //Se valida que la extension del archivo de entrada posea la extension .raw
                    extension = strrchr(dato->imagenEntrada , '.');
                    if(strcmp(extension, ".raw") != 0){
                        printf("\nEl archivo no posee la extension '.raw'.\n");
                        exit(0);
                    }
                    break;
                case 'O':
                    dato->imagenSalida = optarg;
                    //Se valida que la opcion ingresada como nombre de la imagen de salida posea la extension .raw
                    extension = strrchr(dato->imagenSalida , '.');
                    if(strcmp(extension, ".raw") != 0){
                        printf("\nEl nombre de la imagen de salida debe poseer la extension '.raw' .\n");
                        exit(0);
                    }
                    break;
                case 'M':
                    dato->filasImagen = atoi(optarg);
                    //Se comprueba que las filas sean un numero mayor a 0
                    if(dato->filasImagen <= 0){
                        printf("\nLa cantidad de filas de la imagen debe ser mayor a 0.\n");
                        exit(0);
                    }
                    break;
                case 'N':
                    //Se comprueba que las columnas sean un numero mayor a 0
                    dato->columnasImagen = atoi(optarg);
                    if(dato->columnasImagen <= 0){
                        printf("\nLa cantidad de columnas de la imagen debe ser mayor a 0.\n");
                        exit(0);
                    }
                    break;
                case 'r':
                    //Se comprueba que el factor de replicacion sea un numero mayor a 0
                    dato->factor = atoi(optarg);
                    if(dato->factor <= 0){
                        printf("\nEl factor debe ser mayor a 0.\n");
                        exit(0);
                    }
                    break;
                case 'g':
                    //Se comprueba que los grados ingresados sea un numero valido
                    dato->grados = atoi(optarg);
                    if(dato->grados != 0 && dato->grados != 90 && dato->grados != 180 && dato->grados != 270){
                        printf("\nLos grados en que se puede rotar la imagen son: 0, 90, 180 o 270\n");
                        exit(0);
                    }
                    break;
                case 'b':
                    dato->bandera = 1;
                    break;
                case '?':
                    if(optopt == 'b'){
                        fprintf(stderr, "La opcion -%c requiere un argumento.\n", optopt);
                    }
                    else if(isprint (optopt)){
                        fprintf(stderr, "La opcion '-%c' requiere un argumento.\n", optopt);
                    }
                    else{
                        fprintf(stderr, "Opcion con caracter desconocido '\\x%x'.\n", optopt);
                    }   
                    return 1;
                default:
                    abort();
            }
        }
    }

    printf("\nI = %s\nO = %s \nM = %i\nN = %i\nr = %i\ng = %i\nb = %i\n", dato->imagenEntrada, dato->imagenSalida, dato->filasImagen, dato->columnasImagen, dato->factor, dato->grados, dato->bandera);

    /*USO DE FUNCIONES*/

    //Se calcula las nuevas dimensiones de la imagen con zoom
    dz->filasZoom = dato->filasImagen * dato->factor;

    dz->columnasZoom = dato->columnasImagen * dato->factor;

    //Se lee la imagen de entrada
    leerImagen(dato->imagenEntrada, dato->filasImagen, dato->columnasImagen);

    //Se verifica si se muestran datos en pantalla
    flag(dato->bandera, dz->filasZoom, dz->columnasZoom);

    //Se hace el zoom a la imagen
    zoomInImagen(matrizImagen, dato->filasImagen, dato->columnasImagen, dato->factor);


    //Se escriben la imagen con zoom
    //escribirResultados(dato->imagenZoom, matrizZoomIn, dz->filasZoom, dz->columnasZoom);


    //Se realiza el suavizado de la imagen
    suavizarImagen(matrizZoomIn, dz->filasZoom, dz->columnasZoom);

/**/

    rotarImagen(matrizRotada, dz->filasZoom, dz->columnasZoom, dato->grados);

    //Se escriben la imagen suavizada
    escribirResultados(dato->imagenSalida, matrizRotada, dz->filasZoom, dz->columnasZoom);

/**/

    //Se escriben la imagen suavizada
    //escribirResultados(dato->imagenSuavizada, matrizSuavizada, dz->filasZoom, dz->columnasZoom);


    //Se libera la memoria de la matriz con zoom
    liberarMemoriaMatriz(matrizZoomIn, dz->filasZoom);

    //Se libera la memoria de la matriz suavizada
    liberarMemoriaMatriz(matrizSuavizada, dz->filasZoom);

    //Se libera la memoria las estructuras
    liberarMemoria(dato, dz);

    return 0;

}