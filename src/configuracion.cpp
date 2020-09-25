#include <iostream>
#include "rlutil.h"
#include "entrenamientos.h"
#include "usuario.h"
#include "funciones.h"

using namespace std;
using namespace rlutil;

const char *BACKUP_USUARIOS = "../datos/usuarios.bkp", *BACKUP_ENTRENAMIENTOS = "../datos/entrenamientos.bkp";

bool backup(const char *archivoOrigen, const char *archivoDestino, long tamanio)
{
    bool estado;
    int cantidadRegistros = contarRegistros(archivoOrigen, tamanio);
    FILE *p;
    p = fopen(archivoOrigen, "rb");
    if (p == NULL)
    {
        error("1");
        return false;
    }
    void *datos;
    datos = malloc(cantidadRegistros * tamanio);
    if (datos == NULL)
    {
        error("2");
        return false;
    }
    estado = fread(datos, tamanio, cantidadRegistros, p);
    fclose(p);
    if (!estado)
    {
        error("3");
        return false;
    }
    p = fopen(archivoDestino, "wb");
    estado = fwrite(datos, tamanio, cantidadRegistros, p);
    fclose(p);
    if (!estado)
    {
        error("4");
        return false;
    }
    free(datos);
    return true;
}

void crearBackup()
{
    bool estado = backup(PATH_USUARIO, BACKUP_USUARIOS, sizeof(usuario)) &&
                  backup(PATH_ENTRENAMIENTOS, BACKUP_ENTRENAMIENTOS, sizeof(entrenamientos));

    if (estado)
    {
        exito("Backup creado con exito");
    }
    else
    {
        error("No se pudo crear el backup");
    }
}

void restaurarBackup()
{
    char sel;
    bool estado;
    cout << "Esta accion eliminara todo lo que haya cargado luedo de crear el ultimo backup!" << endl;
    cout << "Desea continuar? [s/n]: ";
    cin >> sel;
    switch (sel)
    {
    case 's':
    case 'S':
        cls();
        estado = backup(BACKUP_USUARIOS, PATH_USUARIO, sizeof(usuario)) &&
                 backup(BACKUP_ENTRENAMIENTOS, PATH_ENTRENAMIENTOS, sizeof(entrenamientos));
        if (estado){
            exito ("Backup restaurado exitosamente");
        }
        else error("No se pudo restaurar el backup");
        break;
    case 'n':
    case 'N':
        cls();
        cout << "No se recuperara el backup.";
        break;
    default:
        cls();
        cout << "Opcion invalida.";
        break;
    }
}