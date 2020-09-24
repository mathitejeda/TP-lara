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