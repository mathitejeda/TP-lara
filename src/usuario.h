#pragma once
#include "fecha.h"

struct usuario
{
    int ID, aptoMedico;
    char nombres[50], apellidos[50], apto;
    fecha fechaNacimiento;
    float altura, peso;
    char perfilActividad;
    bool estado = true;
};

usuario leerUsuario(int pos);
int buscarUsuario(int id);
void listarUsuario(usuario mostrar);

bool cargarUsuario(usuario *ref);
bool guardarUsuario(usuario ref);
void nuevoUsuario();

bool modificarUsuario(usuario *ref);
bool sobreescribirUsuario(usuario *ref, int pos);
void modificacionUsuario(int id);

void listarUsuarioPorID(int id);
void listarUsuarios ();
void eliminarUsuario (int id);
int cantidadUsuarios();
bool getAptoMedico(int id);
