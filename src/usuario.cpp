#include <iostream>
#include "rlutil.h"
#include "fecha.h"
#include "usuario.h"
#include "verifier.h"
#include "funciones.h"

const char *PATH_USUARIO = "../datos/usuario.dat";

usuario leerUsuario(int pos)
{
    usuario read;
    bool exito;
    FILE *p;
    p = fopen(PATH_USUARIO, "rb");
    if (p == NULL)
    {
        error("Error en lectura");
        return read;
    }
    fseek(p, pos * sizeof(usuario), SEEK_SET);
    fread(&read, sizeof(usuario), 1, p);
    fclose(p);
    return read;
}

int buscarUsuario(int id)
{
    usuario busqueda;
    FILE *p;
    p = fopen(PATH_USUARIO, "rb");
    if (p == NULL)
        return -1;
    int i = 0;
    while (fread(&busqueda, sizeof(usuario), 1, p))
    {
        if (busqueda.ID == id && busqueda.estado == true)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    return -1;
}

void listarUsuario(usuario mostrar)
{
    std::cout << "#ID: " << mostrar.ID << std::endl;
    std::cout << "+ Nombre(s): " << mostrar.nombres << std::endl;
    std::cout << "+ Apellido(s)" << mostrar.apellidos << std::endl;
    std::cout << "+ Fecha de nacimiento: ";
    mostrar.fechaNacimiento.mostrarFecha();
    std::cout << std::endl;
    std::cout << "+ Altura:" << mostrar.altura << "mts" << std::endl;
    std::cout << "+ Peso:" << mostrar.peso << "kgs" << std::endl;
    std::cout << "+ Perfil de actividad: " << mostrar.perfilActividad << std::endl;
}

bool cargarUsuario(usuario *ref)
{
    ref->ID = cantidadUsuarios() + 1;
    std::cout << "Ingrese el nombre: ";
    std::cin.getline(ref->nombres, 50);
    while (!verificarNombre(ref->nombres))
    {
        rlutil::cls();
        error("El nombre ingresado no es valido");
        std::cout << "Ingrese el nombre: ";
        std::cin.getline(ref->nombres, 50);
    }
    std::cout << "Ingrese el apellido: ";
    std::cin.getline(ref->apellidos, 50);
    while (!verificarNombre(ref->apellidos))
    {
        rlutil::cls();
        error("El apellido ingresado no es valido");
        std::cout << "Ingrese el apellido: ";
        std::cin.getline(ref->apellidos, 50);
    }

    std::cout << "Ingrese la fecha de nacimiento (formato dd mm aaaa, separado con espacios): ";
    std::cin >> ref->fechaNacimiento.dia >> ref->fechaNacimiento.mes >> ref->fechaNacimiento.anio;
    while (!ref->fechaNacimiento.verificarFecha(ref->fechaNacimiento.dia, ref->fechaNacimiento.mes, ref->fechaNacimiento.anio))
    {
        rlutil::cls();
        error("La fecha ingresada es incorrecta");
        std::cout << "Ingrese la fecha de nacimiento: ";
        std::cin >> ref->fechaNacimiento.dia, ref->fechaNacimiento.mes, ref->fechaNacimiento.anio;
    }
    if (ref->fechaNacimiento.obtenerEdad(ref->fechaNacimiento.dia, ref->fechaNacimiento.mes, ref->fechaNacimiento.anio) < 13)
    {
        error("La edad del usuario debe ser mayor a 13");
        return false;
    }

    do
    {
        std::cout << "Ingresar altura: ";
        std::cin >> ref->altura;
        if (ref->altura < 0)
            error("La altura ingresada es invalida");
    } while (ref->altura < 0);

    do
    {
        std::cout << "Ingresar peso: ";
        std::cin >> ref->peso;
        if (ref->peso < 0)
            error("El peso ingresado es invalido");
    } while (ref->peso < 0);

    std::cout << "Ingrese el perfil de actividad: ";
    std::cin >> ref->perfilActividad;
    while (!verificarPerfils(ref->perfilActividad))
    {
        rlutil::cls();
        error("El perfil de actividad no es valido");
        std::cout << "Ingrese el perfil de actividad: ";
        std::cin >> ref->perfilActividad;
    }
    std::cout << "Apto medico? s/n: ";
    std::cin >> ref->apto;
    while (procesarApto(ref->apto) < 0 || procesarApto(ref->apto) > 1)
    {
        rlutil::cls();
        std::cout << "Apto medico? s/n: ";
        std::cin >> ref->apto;
    }
    ref->aptoMedico = procesarApto(ref->apto);
    return true;
}

bool guardarUsuario(struct usuario ref)
{
    bool guardado;
    FILE *p;
    p = fopen(PATH_USUARIO, "ab");
    if (p == NULL)
        return false;
    guardado = fwrite(&ref, sizeof(usuario), 1, p);
    fclose(p);
    return guardado;
}

void nuevoUsuario()
{
    usuario ref;
    if (cargarUsuario(&ref))
    {
        exito("usuario cargado con exito!");
        if (guardarUsuario(ref))
        {
            exito("Usuario guardado con exito!");
        }
        else
            error("No se pudo guardar el usuario");
    }
    else
        error("No se pudo cargar el usuario;");
}

bool modificarUsuario(usuario *ref)
{
    int opc;
    std::cout << "Que desea modificar?" << std::endl;
    std::cout << "-1 Peso" << std::endl;
    std::cout << "-2 Perfil de actividad" << std::endl;
    std::cout << "-3 Apto medico" << std::endl;
    std::cout << "-0 Cancelar" << std::endl
              << std::endl;
    std::cout << "Seleccione una opcion: ";
    switch (opc)
    {
    case 1:
        rlutil::cls();
        do
        {
            std::cout << "Ingresar peso: ";
            std::cin >> ref->peso;
            if (ref->peso < 0)
                error("El peso ingresado es invalido");
        } while (ref->peso < 0);
        break;
    case 2:
        rlutil::cls();
        std::cout << "Ingrese el perfil de actividad: ";
        std::cin >> ref->perfilActividad;
        while (verificarPerfils(ref->perfilActividad))
        {
            rlutil::cls();
            error("El perfil de actividad no es valido");
            std::cout << "Ingrese el perfil de actividad: ";
            std::cin >> ref->perfilActividad;
        }
        break;

    case 3:
        rlutil::cls();
        std::cout << "Apto medico? s/n: ";
        std::cin >> ref->apto;
        while (procesarApto(ref->apto) < 0 || procesarApto(ref->apto) > 1)
        {
            rlutil::cls();
            std::cout << "Apto medico? s/n: ";
            std::cin >> ref->apto;
        }
        ref->aptoMedico = procesarApto(ref->apto);
        break;
    case 0:
        return false;
        break;
    default:
        rlutil::cls();
        error("La opcion ingresada es incorrecta");
        break;
    }
    return true;
}

bool sobreescribirUsuario(usuario *ref, int pos)
{
    bool sobreescrito;
    FILE *p;
    p = fopen(PATH_USUARIO, "rb+");
    if (p == NULL)
        return false;
    fseek(p, pos * sizeof(usuario), SEEK_SET);
    sobreescrito = fwrite(&ref, sizeof(usuario), 1, p);
    fclose(p);
    return sobreescrito;
}

void modificacionUsuario(int id)
{
    usuario mod;
    int pos = buscarUsuario(id);
    if (pos >= 0)
    {
        mod = leerUsuario(pos);
        listarUsuario(mod);
        std::cout << std::endl;
        if (modificarUsuario(&mod))
        {
            if (sobreescribirUsuario(&mod, pos))
            {
                exito("Usuario modificado!");
            }
            else
                error("No se pudieron guardar los cambios.");
        }
        else
            error("No se pudo modificar el usuario");
    }
    else
        error("No se encontró al usuario.");
    return;
}

void listarUsuarioPorID(int id)
{
    usuario listar;
    int pos = buscarUsuario(id);
    if (pos >= 0)
    {
        listar = leerUsuario(pos);
        listarUsuario(listar);
    }
    else
        error("No se encontro el usuario");
}

void listarUsuarios()
{
    int cant = cantidadUsuarios();
    if (cant == 0)
    {
        error("No hay usuarios");
        return;
    }
    usuario *listar;
    listar = (usuario *)malloc(cant * sizeof(usuario));
    if (listar == NULL)
    {
        error("No hay memoria para continuar");
        return;
    }
    FILE *p;
    p = fopen(PATH_USUARIO, "rb");
    if (p == NULL)
    {
        free(listar);
        error("No existe el archivo");
        return;
    }
    fread(&listar[0], sizeof(usuario), cant, p);
    fclose(p);
    for (int i = 0; i < cant; i++)
    {
        std::cout << ".............................." << std::endl;
        listarUsuario(listar[i]);
        std::cout << std::endl;
    }
    free(listar);
}

void eliminarUsuario(int id)
{
    char sel;
    int pos = buscarUsuario(id);
    if (pos >= 0)
    {
        usuario reg = leerUsuario(pos);
        std::cout << std::endl;
        listarUsuario(reg);
        std::cout << std::endl;
        std::cout << "Seguro quiere eliminar al usuario? [s/n]: ";
        std::cin >> sel;
        std::cin.ignore();
        rlutil::cls();
        switch (sel)
        {
        case 's':
        case 'S':
            reg.estado = false;
            if (sobreescribirUsuario(&reg, pos))
            {
                exito("Usuario eliminado");
            }
            else
                error("No se pudo eliminar al usuario");
            break;
        case 'n':
        case 'N':
            error("No se eliminara al usuario");
            return;
            break;
        default:
            error("opcion invalida");
            break;
        }
    }
}

int cantidadUsuarios()
{
    int cant, bytes;
    FILE *p;
    p = fopen(PATH_USUARIO, "rb");
    if (p == NULL)
        return 0;
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cant = bytes / sizeof(usuario);
    fclose(p);
    return cant;
}

bool getAptoMedico(int id)
{
    int pos = buscarUsuario(id);
    usuario apto = leerUsuario(pos);
    if (apto.aptoMedico)
        return true;
    else
        return false;
}