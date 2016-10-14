#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_reader.h"
#include "automata.h"

int main(int argc, char const *argv[]){
  char cadena[100];
  //printf("Por favor ingrese la cadena que desea validar.\n");
  scanf("%s", cadena);
  Nodo* nodo;
  nodo = crearNodo(cadena);

  char *alfabeto, *transition;
  int *estados,  estadoInicial, *estadosFinales,  *estadosOrigen, *estadosDestino;
  int estadoLength, estadosFinalesLength, origenLength, destinoLength;
  LeerArchivo(&alfabeto, &transition, &estados, &estadoInicial, &estadosFinales, &estadosOrigen, &estadosDestino, &estadoLength, &estadosFinalesLength, &origenLength, &destinoLength);


  Estado* initialState;
  initialState = crearEstados(alfabeto, estadoInicial, estados, estadoLength, transition, estadosOrigen, estadosDestino, origenLength, destinoLength);


  recorrerEstados(nodo, initialState);

  return 0;
}
