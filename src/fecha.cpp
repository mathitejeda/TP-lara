#include <iostream>
#include <ctime>
#include "fecha.h"

fecha::fecha(int d,int m,int a){
    if (d != 0 || m != 0 || a != 0)
    {
        dia = d;
        mes = m;
        anio = a;
    }
    else
    {
        time_t tiempo;
        struct tm *tmPtr;
        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);
        anio = tmPtr->tm_year + 1900;
        mes = tmPtr->tm_mon + 1;
        dia = tmPtr->tm_mday;
    }
}

bool fecha::verificarFecha (int dia, int mes, int anio){
    if (mes>=1 && mes <= 12){
    switch (mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (dia >= 1 && dia <= 31) return true;
            else return false;
            break;
        case 2:
            if (anio%4==0 && anio%100!=0){
                if (dia>=1 && dia <=27) return true;
                else return false;
            }
            else if (dia >=1 && dia <=29) return true;
            else return false;
            break;
        case 4: case 6: case 9: case 11:
        if (dia >=1 && dia <=30) return true;
        else return false;
        break;
    }
    }
    else return false;
}

void fecha::mostrarFecha(){
    std::cout<< dia<< "/"<<mes<<"/"<<anio;
}

int fecha::obtenerEdad (int dia,int mes,int anio){
    fecha fechaActual;
    int edad = fechaActual.anio - anio;
    if (fechaActual.mes >= mes){
        if(fechaActual.dia >= dia){
            return edad;
        }
    }
    return edad-1;
}  

bool fecha::inferiorActual(int dia, int mes, int anio){
    fecha fechaActual;
    if (dia > fechaActual.dia && mes > fechaActual.mes && anio > fechaActual.anio){
        return false;
    }
    else return true;
}