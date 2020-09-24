#pragma once

struct fecha
{
    int dia,mes,anio;

    fecha(int d = 0,int m = 0,int a = 0);
    bool verificarFecha(int dia,int mes,int anio);
    void mostrarFecha();
    int obtenerEdad(int dia,int mes,int anio);
    bool inferiorActual(int dia, int mes,int anio);
};
