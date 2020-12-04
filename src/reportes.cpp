#include <iostream>
#include <iomanip>
#include "funciones.h"
#include "usuario.h"
#include "entrenamientos.h"

using namespace std;

void rangoPeso(int minimo, int maximo)
{
    int i = 0;
    usuario reg;
    cout << left << setfill(' ') << setw(25) << "Nombre(s)";
    cout << left << setfill(' ') << setw(25) << "Apellido(s)";
    cout << left << setfill(' ') << setw(8) << "Peso" << endl;
    cout << setfill('.') << setw(58) << "." << endl;
    for (int i = 0; i < contarRegistros(PATH_USUARIO, sizeof(usuario)); i++)
    {
        reg = leerUsuario(i);
        if (reg.peso < maximo && reg.peso > minimo)
        {
            cout << left << setfill(' ') << setw(25) << reg.nombres;
            cout << left << setfill(' ') << setw(25) << reg.apellidos;
            cout << left << setfill(' ') << setw(6) << reg.peso;
            cout << left << "Kgs." << endl;
            cout << setfill('.') << "." << setw(58) << endl;
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
            if (caloriasMaximas < caloriasActuales)
            {
                caloriasMaximas = caloriasActuales;
                posMaximas = i;
            }
        }
    }
    mamadisimo = leerUsuario(posMaximas);
    std::cout << "Felicitaciones a " << mamadisimo.nombres << " " << mamadisimo.apellidos << " por haber quemado mas calorias";
    std::cout << "Cantidad de calorias quemadas: " << caloriasMaximas << "!!!";
}

float promedioPorPerfil(char perfilUsuario)
{
    usuario aux;
    float promedio = 0;
    char perfilMay = toupper(perfilUsuario), perfilMin = tolower(perfilUsuario);
    int cant = 0;
    for (int i = 0; i < contarRegistros(PATH_USUARIO, sizeof(usuario)); i++)
    {
        aux = leerUsuario(i);
        if (aux.perfilActividad == perfilMay || aux.perfilActividad == perfilMin)
        {
            promedio += aux.altura;
            cant++;
        }
    }
    return promedio / cant;
}

void mayorPromedioTipoB()
{
    usuario aux;
    float promedio = promedioPorPerfil('b');
    for (int i = 0; i < contarRegistros(PATH_USUARIO, sizeof(usuario)); i++)
    {
        aux = leerUsuario(i);
        if (aux.perfilActividad == 'b' || aux.perfilActividad == 'B')
        {
            if (aux.altura > promedio)
            {
                listarUsuario(aux);
                cout << endl;
            }
        }
    }
}

int acuEntrenamientos(int tipoAct, char perfil)
{
    entrenamientos obj;
    usuario aux;
    int posUsuario;
    int cant = 0;
    for (int i = 0; i < contarRegistros(PATH_ENTRENAMIENTOS, sizeof(entrenamientos)); i++)
    {
        obj = leerEntrenamientos(i);
        posUsuario = buscarUsuario(obj.IDusuario);
        aux = leerUsuario(posUsuario);
        if (obj.actividad == tipoAct)
        {
            if (aux.perfilActividad == toupper(perfil) || aux.perfilActividad == tolower(perfil))
            {
                cant += 1;
            }
        }
    }
    return cant;
}

char numToChar(int n)
{
    switch (n)
    {
    case 1:
        return 'a';
        break;
    case 2:
        return 'b';
        break;
    case 3:
        return 'c';
    }
}

void actividadesPorPerfil()
{
    int matEntrenamientos[5][3] = {0};
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matEntrenamientos[i][j] = acuEntrenamientos(i + 1, numToChar(j + 1));
        }
    }
    cout << left << setw(15) << setfill(' ') << "Nombre de act";
    cout << left << setw(3) << setfill(' ') << "A";
    cout << left << setw(3) << setfill(' ') << "B";
    cout << left << setw(3) << setfill(' ') << "C" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                cout << left << setw(15) << setfill('.') << nombreActividad(i + 1);
                cout << left << setw(3) << setfill(' ') << matEntrenamientos[i][j];
            }
            else
            {
                cout << left << setw(3) << setfill(' ') << matEntrenamientos[i][j];
            }
        }
        cout << endl;
    }
}