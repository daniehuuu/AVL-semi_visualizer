#pragma once 
template<class T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;
    //int altura;

    Nodo() {
        izq = nullptr;
        der = nullptr;
        //altura = 0;
    }
};