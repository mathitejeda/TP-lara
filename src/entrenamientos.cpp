#include <iostream>
#include "entrenamientos.h"
#include "usuario.h"
#include "funciones.h"
#include "fecha.h"
#include "rlutil.h"
//creacion

bool cargarEntrenamiento(entrenamientos *ref)
{
    ref->ID = contarRegistros(PATH_ENTRENAMIENTOS,sizeof(entrenamientos)) +1 ;
    std::cout << "Ingrese el id de usuario";
    std::cin >> ref->IDusuario;
    while (buscarUsuario(ref->IDusuario) < 0)
    {
        error("No existe el usuario");
        std::cout << "Ingrese el id de usuario";
        std::cin >> ref->IDusuario;
    }
    std::cout << "Fecha de entrenamiento (Formato dd mm aaaa separado por espacios): ";
    std::cin >> ref->fechaEntrenamiento.dia >> ref->fechaEntrenamiento.mes >> ref->fechaEntrenamiento.anio;
    while (!ref->fechaEntrenamiento.verificarFecha(ref->fechaEntrenamiento.dia, ref->fechaEntrenamiento.mes, ref->fechaEntrenamiento.anio) || !ref->fechaEntrenamiento.inferiorActual(ref->fechaEntrenamiento.dia, ref->fechaEntrenamiento.mes, ref->fechaEntrenamiento.anio))
    {
        rlutil::cls();
        error("La fecha ingresada es incorrecta");
        std::cout << "Ingrese la fecha de entrenamiento: ";
        std::cin >> ref->fechaEntrenamiento.dia >> ref->fechaEntrenamiento.mes >> ref->fechaEntrenamiento.anio;
    }

    do{
    std::cout << "Ingrese la actividad a realizar" << std::endl;
    std::cout << "1_Caminata" << std::endl;
    std::cout << "2_Correr" << std::endl;
    std::cout << "3_Bicicleta" << std::endl;
    std::cout << "4_Natación" << std::endl;
    std::cout << "5_Pesas" << std::endl;
    std::cin >> ref->actividad;
    if (ref->actividad == pesas || ref->actividad == natacion)
    {
        if (!getAptoMedico(ref->IDusuario))
        {
            error("No se puede realizar esta actividad sin apto medico");
            return false;
        }
    }
    if(ref->actividad < 1 || ref->actividad >5) error ("Actividad invalida");
    }while(ref->actividad < 1 || ref->actividad >5);

    do
    {
        std::cout << "Calorias quemadas: ";
        std::cin >> ref->calorias;
        if (ref->calorias < 0)
        {
            error("El numero no puede ser negativo");
        }
    } while (ref->calorias < 0);
    do
    {
        std::cout << "Tiempo (En minutos): ";
        std::cin >> ref->tiempo;
        if (ref->tiempo < 0)
        {
            error("El tiempo no puede ser negativo");
        }
    } while (ref->tiempo < 0);
    return true;
}

bool guardarEntrenamiento(entrenamientos save)
{
    bool guardado;
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "ab");
    if (p == NULL)
        return false;
    guardado = fwrite(&save, sizeof(entrenamientos), 1, p);
    fclose(p);
    return guardado;
}

void nuevoEntrenamiento()
{
    entrenamientos nuevo;
    if (cargarEntrenamiento(&nuevo))
    {
        if (guardarEntrenamiento(nuevo))
        {
            exito("Entrenamiento guardado con exito");
        }
        else
            error("No se pudo guardar el entrenamiento");
    }
    else
        error("No se pudo cargar el entrenamiento");
}

//listados

void listarEntrenamiento(entrenamientos mostrar)
{
    std::cout << "#ID: " << mostrar.ID << std::endl;
    std::cout << "#ID usuario: " << mostrar.IDusuario << std::endl;
    std::cout << "+ Fecha de entrenamiento: " << std::endl;
    mostrar.fechaEntrenamiento.mostrarFecha();
    std::cout<<std::endl;
    std::cout << "+ Actividad: " << nombreActividad(mostrar.actividad);
    std::cout << std::endl;
    std::cout << "+ Calorias quemadas: " << mostrar.calorias << std::endl;
    std::cout << "+ Tiempo: " << mostrar.tiempo << " Minutos" << std::endl;
}

void listarEntrenamientoPorID(int id)
{
    entrenamientos listar;
    int pos = buscarEntrenamiento(id);
    if (pos >= 0)
    {
        listar = leerEntrenamientos(pos);
        listarEntrenamiento(listar);
    }
    else
        error("No se encontro el entrenamiento");
}

void listarEntrenamientoPorIDUsuario (int id){
    if(buscarUsuario(id) > 0){
    entrenamientos busqueda;
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "rb");
    if (p == NULL)
        return;
    int i = 0;
    while (fread(&busqueda, sizeof(entrenamientos), 1, p))
    {
        if (busqueda.IDusuario == id)
        {
            listarEntrenamiento(busqueda);
            std::cout << ".........................."<<std::endl;
        }
        i++;
    }
    fclose(p);
    }
    else error ("No se encontro al usuario");
    return;
}

void listarEntrenamientos(){
    int cant = contarRegistros(PATH_ENTRENAMIENTOS,sizeof(entrenamientos));
    if (cant == 0)
    {
        error("No hay entrenamientos cargados");
        return;
    }
    entrenamientos *listar;
    listar = (entrenamientos *)malloc(cant * sizeof(entrenamientos));
    if (listar == NULL)
    {
        error("No hay memoria para continuar");
        return;
    }
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "rb");
    if (p == NULL)
    {
        free(listar);
        error("No existe el archivo");
        return;
    }
    fread(&listar[0], sizeof(entrenamientos), cant, p);
    fclose(p);
    for (int i = 0; i < cant; i++)
    {
        std::cout << ".............................." << std::endl;
        listarEntrenamiento(listar[i]);
        std::cout << std::endl;
    }
    free(listar);
}

const char* nombreActividad(int actividad){
    bool valido = true;
    while (valido){
    switch (actividad)
    {
    case 1:
        return "Caminata";
        break;
    case 2:
        return "Correr";
        break;
    case 3:
        return "Bicicleta";
        break;
    case 4:
        return "Natación";
        break;
    case 5:
        return "Pesas";
        break;
    default:
        return "error";
        break;
    }
    }
}

//modificacion

bool modificarEntrenamiento(entrenamientos *ref)
{
    int opc;
    std::cout << "Que desea modificar?" << std::endl;
    std::cout << "-1 Tiempo" << std::endl;
    std::cout << "-2 Calorias" << std::endl;
    std::cout << "-0 Cancelar" << std::endl
              << std::endl;
    std::cout << "Seleccione una opcion: ";
    switch (opc)
    {
    case 1:
        rlutil::cls();
        do
        {
            std::cout << "Tiempo (En minutos): ";
            std::cin >> ref->tiempo;
            if (ref->tiempo < 0)
            {
                error("El tiempo no puede ser negativo");
            }
        } while (ref->tiempo < 0);
        break;
    case 2:
        rlutil::cls();
        do
        {
            std::cout << "Calorias quemadas: ";
            std::cin >> ref->calorias;
            if (ref->calorias < 0)
            {
                error("El numero no puede ser negativo");
            }
        } while (ref->calorias < 0);
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

bool sobreescribirEntrenamiento(entrenamientos *ref, int pos)
{
    bool sobreescrito;
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "rb+");
    if (p == NULL)
        return false;
    fseek(p, pos * sizeof(entrenamientos), SEEK_SET);
    sobreescrito = fwrite(&ref, sizeof(entrenamientos), 1, p);
    fclose(p);
    return sobreescrito;
}

void modificacionEntrenamiento(int id)
{
    entrenamientos mod;
    int pos = buscarEntrenamiento(id);
    if (pos >= 0)
    {
        mod = leerEntrenamientos(pos);
        listarEntrenamiento(mod);
        std::cout << std::endl;
        if (modificarEntrenamiento(&mod))
        {
            if (sobreescribirEntrenamiento(&mod, pos))
            {
                exito("Entrenamiento modificado!");
            }
            else
                error("No se pudieron guardar los cambios.");
        }
        else
            error("No se pudo modificar el eltrenamiento");
    }
    else
        error("No se encontró el entrenamiento.");
    return;
}

//busqueda y lectura

entrenamientos leerEntrenamientos(int pos)
{
    entrenamientos read;
    bool exito;
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "rb");
    if (p == NULL)
    {
        error("Error en lectura");
        return read;
    }
    fseek(p, pos * sizeof(entrenamientos), SEEK_SET);
    fread(&read, sizeof(entrenamientos), 1, p);
    fclose(p);
    return read;
}

int buscarEntrenamiento(int id)
{
    entrenamientos busqueda;
    FILE *p;
    p = fopen(PATH_ENTRENAMIENTOS, "rb");
    if (p == NULL)
        return -1;
    int i = 0;
    while (fread(&busqueda, sizeof(entrenamientos), 1, p))
    {
        if (busqueda.ID == id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    return -1;
}