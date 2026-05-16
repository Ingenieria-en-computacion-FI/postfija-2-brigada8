#include "pila.h"
#include <string.h>
#include <stdio.h>

Pila* crearPila() {

    Pila* p = (Pila*) malloc(sizeof(Pila));

    if (p == NULL) {
        printf("Error al crear pila\n");
        exit(1);
    }

    p->tope = NULL;

    return p;
}

void push(Pila* p, void *dato, size_t size) {

    NodoPila* nuevo = (NodoPila*) malloc(sizeof(NodoPila));

    if (nuevo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }

    nuevo->dato = malloc(size);

    if (nuevo->dato == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }

    memcpy(nuevo->dato, dato, size);

    /* Insertar al inicio */
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
}

char pop(Pila* p) {

    if (pilaVacia(p)) {
        printf("La pila esta vacia\n");
        return '\0';
    }

    NodoPila* temp = p->tope;

    char dato = *(char*)temp->dato;

    p->tope = p->tope->siguiente;

    free(temp->dato);
    free(temp);

    return dato;
}

char peek(Pila* p) {

    if (pilaVacia(p)) {
        printf("La pila esta vacia\n");
        return '\0';
    }

    return *(char*)p->tope->dato;
}

int pilaVacia(Pila* p) {
    return (p->tope == NULL);
}

void destruirPila(Pila* p) {

    while (!pilaVacia(p)) {
        pop(p);
    }

    free(p);
}