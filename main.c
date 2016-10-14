#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_reader.h"
#include "automata.h"

int main(int argc, char const *argv[]){
  char cadena[100];
  //printf("Por favor ingrese la cadena que desea validar.\n");
  //scanf("%s", cadena);

  char *alfabeto, *transition;
  int *estados,  estadoInicial, *estadosFinales,  *estadosOrigen, *estadosDestino;
  int estadoLength, estadosFinalesLength, origenLength, destinoLength;
  LeerArchivo(&alfabeto, &transition, &estados, &estadoInicial, &estadosFinales, &estadosOrigen, &estadosDestino, &estadoLength, &estadosFinalesLength, &origenLength, &destinoLength);
  crearEstados(alfabeto, estadoInicial, estados, estadoLength, transition, estadosOrigen, estadosDestino, origenLength, destinoLength);
  /*
  printf("Conjunto de estados ");
  for (size_t i = 0; i < estadoLength; i++) {
    printf("%d ", estados[i]);
  }
  printf("\n");

  printf("Alfabeto: %s\n", alfabeto);

  printf("Estado inicial: %d\n", estadoInicial);

  printf("Estados finales ");
  for (size_t i = 0; i < estadosFinalesLength; i++) {
    printf("%d ", estadosFinales[i]);
  }
  printf("\n");

  printf("Transition: %s\n", transition);
  */
  //crearEstados();
  //crearNodo(cadena);
  //recorrerEstados();

  return 0;
}
