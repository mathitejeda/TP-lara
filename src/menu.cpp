#include "iostream"
#include "rlutil.h"
#include "menu.h"
#include "usuario.h"
#include "entrenamientos.h"
#include "funciones.h"
using namespace std;
using namespace rlutil;

void menuPrincipal()
{
    int opcion;
    while (true)
    {
        cls();
        cout << "MENÚ PRINCIPAL" << endl;
        cout << "...................." << endl;
        cout << "1)Usuarios" << endl;
        cout << "2)Entrenamientos" << endl;
        cout << "3)Reportes" << endl;
        cout << "4)Configuración" << endl;
        cout << "...................." << endl;
        cout << "0)SALIR DEL PROGRAMA" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            cls();
            submenuUsuario();
            break;
        case 2:
            cls();
            submenuEntrenamientos();
            break;
        case 0:
            cls();
            cout << "Programa finalizado.";
            msleep(1000);
            return;
            break;
        default:
            cls();
            error("Opción invalida.");
            anykey();
            break;
        }
    }
}
void submenuUsuario()
{
    int opcion, id;
    while (true)
    {
        cls();
        cout << "MENÚ USUARIOS" << endl;
        cout << "...................." << endl;
        cout << "1)Nuevo usuario" << endl;
        cout << "2)Modificar usuario" << endl;
        cout << "3)Listar por ID" << endl;
        cout << "4)Listar todos los usuarios" << endl;
        cout << "5)Eliminar usuario" << endl;
        cout << "...................." << endl;
        cout << "0)Volver al menú principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            cls();
            nuevoUsuario();
            anykey();
            break;
        case 2:
            cls();
            cout << "Ingrese el id del usuario a modificar: ";
            cin >> id;
            cin.ignore();
            modificacionUsuario(id);
            anykey();
            break;
        case 3:
            cls();
            cout << "Ingrese el id del usuario: ";
            cin >> id;
            cin.ignore();
            listarUsuarioPorID(id);
            anykey();
            break;
        case 4:
            cls();
            listarUsuarios();
            anykey();
            break;
        case 5:
            cls();
            cout << "Ingrese el id del usuario: ";
            cin >> id;
            cin.ignore();
            eliminarUsuario(id);
            break;
        case 0:
            cls();
            cout << "Volviendo al menú principal";
            msleep(1000);
            return;
            break;
        default:
            cls();
            error("Opción invalida.");
            anykey();
            break;
        }
    }
}

void submenuEntrenamientos()
{
    int opcion, id;
    while (true)
    {
        cls();
        cout << "MENÚ ENTRENAMIENTOS" << endl;
        cout << "...................." << endl;
        cout << "1)Nuevo entrenamiento" << endl;
        cout << "2)Modificar entrenamiento" << endl;
        cout << "3)Listar entrenamiento por ID" << endl;
        cout << "4)Listar entrenamiento por ID de usuario" << endl;
        cout << "5)Listar todos los entrenamientos" << endl;
        cout << "...................." << endl;
        cout << "0)Volver al menú principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            cls();
            nuevoEntrenamiento();
            anykey();
            break;
        case 2:
            cls();
            cout << "Inserte el id del entrenamiento a modificar: ";
            cin >> id;
            cin.ignore();
            modificacionEntrenamiento(id);
            anykey();
            break;
        case 3:
            cls();
            cout << "Inserte el id del entrenamiento: ";
            cin >> id;
            cin.ignore();
            listarEntrenamientoPorID(id);
            anykey();
            break;
        case 4:
            cls();
            cout << "Inserte el id del usuario: ";
            cin >> id;
            cin.ignore();
            listarEntrenamientoPorIDUsuario(id);
            anykey();
            break;
        case 5:
            cls();
            listarEntrenamientos();
            anykey();
            break;
        case 0:
            cls();
            cout << "Volviendo al menú principal";
            msleep(1000);
            return;
            break;
        default:
            cls();
            error("Opción invalida.");
            anykey();
            break;
        }
    }
}