#include "cola.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Cola* crearCola() {
    Cola* c = (Cola*) malloc(sizeof(Cola));

    if (c == NULL) {
        printf("Error al crear la cola\n");
        exit(1);
    }

    c->frente = NULL;
    c->final = NULL;

    return c;
}

void enqueue(Cola* c, void* dato, size_t size) {

    if (c == NULL) {
        return;
    }

    NodoCola* nuevo = (NodoCola*) malloc(sizeof(NodoCola));

    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return;
    }

    nuevo->dato = malloc(size);

    if (nuevo->dato == NULL) {
        printf("Error de memoria\n");
        free(nuevo);
        return;
    }

    memcpy(nuevo->dato, dato, size);

    nuevo->siguiente = NULL;

    if (c->final == NULL) {

        c->frente = nuevo;
        c->final = nuevo;

    } else {

        c->final->siguiente = nuevo;
        c->final = nuevo;
    }
}

char dequeue(Cola* c) {

    if (colaVacia(c)) {
        printf("Cola vacia\n");
        return -1;
    }

    NodoCola* temp = c->frente;

    char dato = *(char*)temp->dato;

    c->frente = c->frente->siguiente;

    if (c->frente == NULL) {
        c->final = NULL;
    }

    free(temp->dato);
    free(temp);

    return dato;
}

int colaVacia(Cola* c) {
    return (c->frente == NULL);
}

void imprimirCola(Cola* c) {

    NodoCola* aux = c->frente;

    while (aux != NULL) {

        printf("%c ", *(char*)aux->dato);

        aux = aux->siguiente;
    }

    printf("\n");
}

void destruirCola(Cola* c) {

    while (!colaVacia(c)) {
        dequeue(c);
    }

    free(c);
}