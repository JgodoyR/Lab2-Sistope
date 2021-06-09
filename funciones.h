#ifndef FUNCIONES_H
#define FUNCIONES_H

void zoomInImagen(float** matriz, int filas, int columnas, int factorReplicacion);

void suavizarImagen(float** matrizConZoom, int filasZ, int columnasZ);

void liberarMemoriaMatriz(float **matriz, int filas);

void rotarImagen(float** matrizConRotacion, int filasZ, int columnasZ, int rotacion);

void liberarMemoria(struct datos *dato, struct datosZoom *dz);

#endif