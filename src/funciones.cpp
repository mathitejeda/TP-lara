#include "funciones.h"
#include <iostream>
#include "rlutil.h"
using namespace std;
using namespace rlutil;

void error (const char*mensaje){
    setColor(RED);
    cout << ">"<<mensaje<<endl;
    setColor(WHITE);
}
void exito (const char*mensaje){
    setColor(GREEN);
    cout << ">"<<mensaje<<endl;
    setColor(WHITE);
}

int contarRegistros(const char *archivo, long tamanio){
    FILE *p;
    p = fopen(archivo, "rb");
    if (p==NULL){
        return 0;
    }
    long bytes;
    fseek(p, 0, 2);
    bytes = ftell(p);
    fclose(p);
    return bytes/tamanio;
}