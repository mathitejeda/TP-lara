#pragma once
#include "fecha.h"
struct entrenamientos
{
    int ID, IDusuario, actividad, tiempo;
    fecha fechaEntrenamiento;
    float calorias;
};
enum actividad
{
    caminata = 1,
    correr = 2,
    bicicleta = 3,
    natacion = 4,
    pesas = 5
};
bool cargarEntrenamiento(entrenamientos *ref);
bool guardarEntrenamiento(entrenamientos save);
void nuevoEntrenamiento();
bool modificarEntrenamiento(entrenamientos *ref);
bool sobreescribirEntrenamiento(entrenamientos *ref, int pos);
void modificacionEntrenamiento(int id);
void listarEntrenamiento(entrenamientos mostrar);
void listarEntrenamientoPorID(int id);
void listarEntrenamientoPorIDUsuario (int id);
void listarEntrenamientos();
const char* nombreActividad(int actividad);
//operaciones con archivos

entrenamientos leerEntrenamientos(int pos);
int buscarEntrenamiento(int id);
int cantidadEntrenamientos();