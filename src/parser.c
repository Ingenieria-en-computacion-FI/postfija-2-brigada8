#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"
#include "../include/pila.h"

void cargarArchivo(
    const char* nombreArchivo,
    Variable variables[],
    int* totalVariables,
    char expression[]
) {

// TODO: Apertura del archivo
FILE* archivo = fopen(nombreArchivo, "r");
if (archivo == NULL) {
    return;
}

char linea[256];

*totalVariables = 0;

// TODO: Usar un while para leer todo el archivo
// TODO: Usar la función strtok
while (fgets(linea, sizeof(linea), archivo)) {
    linea[strcspn(linea, "\n")] = '\0';
    
    char* token = strtok(linea, " =");
    if (token == NULL) continue;
    
    if (isalpha(token[0]) && token[1] == '\0') {
        char* valorToken = strtok(NULL, " =");
        if (valorToken != NULL) {
            variables[*totalVariables].nombre = token[0];
            variables[*totalVariables].valor = atof(valorToken);
            (*totalVariables)++;
        }
    } else {
        strcpy(expression, linea);
    }
}

fclose(archivo);
}

int precedencia(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Cola* infijaAPostfija(char* expresion) {
    Cola* salida = crearCola();
    Pila* operadores = crearPila();
    
    for (int i = 0; expresion[i] != '\0'; i++) {
        char c = expresion[i];
        
        if (c == ' ') continue;
        
        if (isalnum(c)) {
            enqueue(salida, &c, sizeof(char));
        }
        else if (c == '(') {
            push(operadores, &c, sizeof(char));
        }
        else if (c == ')') {
            while (!pilaVacia(operadores)) {
                char top = peek(operadores);
                if (top == '(') {
                    pop(operadores);
                    break;
                } else {
                    char op = pop(operadores);
                    enqueue(salida, &op, sizeof(char));
                }
            }
        }
        else if (esOperador(c)) {
            while (!pilaVacia(operadores)) {
                char top = peek(operadores);
                if (top != '(' && precedencia(top) >= precedencia(c)) {
                    char op = pop(operadores);
                    enqueue(salida, &op, sizeof(char));
                } else {
                    break;
                }
            }
            push(operadores, &c, sizeof(char));
        }
    }
    
    while (!pilaVacia(operadores)) {
        char op = pop(operadores);
        enqueue(salida, &op, sizeof(char));
    }
    
    destruirPila(operadores);
    return salida;
}
