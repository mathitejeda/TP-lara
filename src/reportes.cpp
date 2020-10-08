#include <iostream>
#include "funciones.h"
#include "usuario.h"
#include "entrenamientos.h"

void rangoPeso(int minimo, int maximo)
{
    int i = 0;
    usuario reg;
    for (int i = 0; i < contarRegistros(PATH_USUARIO, sizeof(usuario)); i++)
    {
        reg = leerUsuario(i);
        if (reg.peso < maximo && reg.peso > minimo)
        {
            std::cout << "+" << reg.nombres << " " << reg.apellidos << std::endl;
        }
    }
}

int acumularCalorias(int id)
{
    entrenamientos acu;
    int calorias = 0;
    for (int i = 0; i < contarRegistros(PATH_ENTRENAMIENTOS, sizeof(entrenamientos)); i++)
    {
        acu = leerEntrenamientos(i);
        if (id == acu.IDusuario)
        {
            calorias += acu.calorias;
        }
    }
    return calorias;
}

void masCaloriasQuemadas()
{
    usuario mamadisimo;
    int caloriasMaximas, caloriasActuales, posMaximas;
    bool primero = false;
    for (int i = 0; i < contarRegistros(PATH_USUARIO, sizeof(usuario)); i++)
    {
        mamadisimo = leerUsuario(i);
        caloriasActuales = acumularCalorias(mamadisimo.ID);
        if (!primero)
        {
            caloriasMaximas = caloriasActuales;
            posMaximas = i;
            primero = true;
        }
        else
        {
            if (caloriasMaximas < caloriasActuales){
            caloriasMaximas = caloriasActuales;
            posMaximas = i;
            }
        }
    }
    mamadisimo = leerUsuario (posMaximas);
    std::cout << "Felicitaciones a " << mamadisimo.nombres << " " << mamadisimo.apellidos << " por haber quemado mas calorias";
    std::cout << "Cantidad de calorias quemadas: "<<caloriasMaximas<< "!!!";
}
