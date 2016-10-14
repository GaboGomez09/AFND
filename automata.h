#ifndef automata
#define automata

#include <string.h>

typedef struct estado Estado;
typedef struct nodo Nodo;

struct estado{
    int estadoID;
    Estado* transiciones[100][100]; //arreglo bidimensional de direcciones de estados
    Estado* apuntadorTemp; //arreglo de caracteres, sirve como metadatos para la matriz de direcciones
};

struct nodo{
    char cadena[100];
    int* recorrido;
    Estado* siguiente;
};

typedef struct lista{
  Estado* cabeza;
}Lista;

Estado* crearEstado(int ID);
void insertarFinal(Lista* lista, int ID);
Estado* crearEstados(char*alfabeto, int estadoInicial, int *estados, int estadoLength, char* transition, int *estadosOrigen, int* estadosDestino, int origenLength, int destinoLength);
void inicializarTransiciones(Lista* lista);
int posicionDeCaracter(char letra, char* alfabeto);
Estado* direccionDeEstadoDestino(Lista* lista, int destinoID);
Nodo* crearNodo(char palabra[100]);
void recorrerEstados(Nodo* nodo, Estado* initialState, char* alfabeto);
Nodo* clonarNodo(Nodo* nodo);

void recorrerEstados(Nodo* nodo, Estado* initialState, char* alfabeto){
  nodo->siguiente = initialState;
  int numeroDeDirecciones, posicion, j;
  for (size_t i = 0; i < strlen(nodo->cadena); i++) {

    posicion = posicionDeCaracter(cadena[i], alfabeto);
    numeroDeDirecciones = 0;
    j = 0;
    while (nodo->siguiente->transiciones[k][posicion] != NULL) {
      numeroDeDirecciones++;
    }

    if (numeroDeDirecciones == 1) {

    }else{
      recorrerEstados(clonarNodo, nodo->siguiente, alfabeto);
    }
    
  }
}

Nodo* clonarNodo(Nodo* nodo){
  Nodo* clon = crearNodo(nodo->cadena);
  for (size_t i = 0; i < strlen(nodo->cadena); i++) {
    clon->recorrido[i] = nodo->recorrido[i];
  }
}

Nodo* crearNodo(char palabra[100]){
  Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
  strcpy(nodo->cadena, palabra);
  nodo->recorrido = (int*)malloc(sizeof(int)*strlen(palabra));
  nodo->siguiente = NULL;
  return nodo;
}

void insertarFinal(Lista* lista, int ID){
  Estado* estado = crearEstado(ID);
  if (lista->cabeza == NULL) {
    lista->cabeza = estado;
  } else {
    Estado* puntero = lista->cabeza;
    while (puntero->apuntadorTemp) {
      puntero = puntero->apuntadorTemp;
    }
    puntero->apuntadorTemp = estado;
  }
}

Estado* crearEstados(char* alfabeto, int estadoInicial, int *estados, int estadoLength, char* transition, int *estadosOrigen, int* estadosDestino, int origenLength, int destinoLength){
  Lista* lista = (Lista*)malloc(sizeof(Lista));
  Estado* initialState;
  Estado* punteroAux;
  Estado* zombie;
  lista->cabeza = NULL;

  for (size_t i = 0; i < estadoLength; i++) {
    insertarFinal(lista, estados[i]);
  }
  zombie = crearEstado(101);

  initialState = lista->cabeza;
  while ((initialState->estadoID) != estadoInicial) {
    initialState = initialState->apuntadorTemp;
  }

  inicializarTransiciones(lista); //iniciliza matriz de puntores(ambiguedades) en NULL
  punteroAux = lista->cabeza;
  int posicion;
  while (punteroAux->apuntadorTemp) {
    for (size_t j = 0; j < origenLength; j++) {
      if ((punteroAux->estadoID) == estadosOrigen[j]) {
        posicion = posicionDeCaracter(transition[j], alfabeto);
        int k = 0;
        while (punteroAux->transiciones[k][posicion] != NULL) {
          k++;
        }
        punteroAux->transiciones[k][posicion] = direccionDeEstadoDestino(lista, estadosDestino[j]);
      }
    }
    punteroAux = punteroAux->apuntadorTemp;
  }


  punteroAux = lista->cabeza;

  while (punteroAux->apuntadorTemp) {
    for (size_t l = 0; l < strlen(alfabeto); l++) {
      if (punteroAux->transiciones[0][l] == NULL) {
        punteroAux->transiciones[0][l] = zombie;
      }
    }
    punteroAux = punteroAux->apuntadorTemp;
  }

  for (size_t z = 0; z < 100; z++) {
    zombie->transiciones[0][z] = zombie;
  }


  return initialState;
}

Estado* direccionDeEstadoDestino(Lista* lista, int destinoID){
  Estado* direccionDestino;
  Estado* puntero = lista->cabeza;

  while (puntero->apuntadorTemp) {
    if (puntero->estadoID == destinoID) {
      direccionDestino = puntero;
    }
    puntero = puntero->apuntadorTemp;
  }

  return direccionDestino;
}

int posicionDeCaracter(char letra, char* alfabeto){
  int posicion = 0;
  while (alfabeto[posicion] != letra) {
    posicion++;
  }
  return posicion;
}

void inicializarTransiciones(Lista* lista){
  Estado* puntero = lista->cabeza;
  while (puntero->apuntadorTemp) {
    for (size_t i = 0; i < 100; i++) {
      for (size_t j = 0; j < 100; j++) {
        puntero->transiciones[j][i] = NULL;
      }
    }
    puntero = puntero->apuntadorTemp;
  }
}

Estado* crearEstado(int ID){
  Estado* estado = (Estado*)malloc(sizeof(estado));
  estado->estadoID = ID;
  estado->apuntadorTemp = NULL;
  return estado;
}

#endif
