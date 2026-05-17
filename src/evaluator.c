#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "../include/evaluator.h"
#include "../include/pila.h"

float obtenerValorVariable(
    Variable variables[],
    int total,
    char nombre) 
{
    for (int i = 0; i < total; i++) {
        if (variables[i].nombre == nombre) {
            return variables[i].valor;
        }
    }
    printf("Variable no encontrada: %c\n", nombre);
    return 0;
}

float aplicarOperacion
    (float op1,
    float op2,
    char operador) 
{
    switch (operador) {
        case '+':
            return op1 + op2;

        case '-':
            return op1 - op2;

        case '*':
            return op1 * op2;

        case '/':
            if (op2 == 0) {
                printf("Error: division entre cero\n");
                return 0;
            }
            return op1 / op2;

        case '^':
            return pow(op1, op2);

        default:
            printf("Operador invalido: %c\n", operador);
            return 0;
    }
}

float evaluarPostfija
    (Cola* postfija,
    Variable variables[],
    int totalVariables) 
{

    Pila* pila = crearPila();
    NodoCola* aux = postfija->frente;
    while (aux != NULL) {

        char token = *(char*)aux->dato;
        if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) 
        {
            float valor =
                obtenerValorVariable(
                    variables,
                    totalVariables,
                    token
                );

            char dato = (char) valor;

            push
                (pila,
                &dato,
                sizeof(char));
        }

        else if 
            (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') 
        {
            float op2 = (float) pop(pila);
            float op1 = (float) pop(pila);
            float resultado =
                aplicarOperacion(
                    op1,
                    op2,
                    token
                );

            char dato = (char) resultado;

            push(
                pila,
                &dato,
                sizeof(char)
            );
        }
        aux = aux->siguiente;
    }
    float resultadoFinal = (float) pop(pila);
    destruirPila(pila);
    return resultadoFinal;
}