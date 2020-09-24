#include <regex>
#include "funciones.h"

bool verificarMail (const char* mail){
    const std::regex pattern("(\\w)+((\\.|_)*(\\w*))*@(\\w)+(\\.(\\w+))+");

    return std::regex_match(mail,pattern);
}

bool verificarNombre(const char* nombre) {
    const std::regex pattern("((\\w)+((\\')(\\w))*(\\s)*)+");

    return std::regex_match(nombre, pattern);
}


bool verificarPerfils(char perfil){
    switch (perfil)
    {
    case 'a': case 'A': case 'b': case 'B': case 'c': case 'C':
        return true;
        break;
    default:
        return false;
        break;
    }
}

int procesarApto (char aptoMedico){
    switch (aptoMedico)
    {
    case 's': case 'S':
        return 1;
        break;
    case 'n' : case 'N':
        return 0;
        break;
    default:
        error ("Opcion invalida");
        return -1;
        break;
    }
}
