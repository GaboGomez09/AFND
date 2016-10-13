#ifndef automata
#define automata

typedef struct estado Estado;
typedef struct nodo Nodo;

struct estado{
    int estadoID;
    Estado* transiciones[100][100]; //arreglo bidimensional de direcciones de estados
    Estado* apuntadorTemp; //arreglo de caracteres, sirve como metadatos para la matriz de direcciones
};

struct nodo{
    char* cadena;
    int* recorrido;
};

typedef struct lista{
  Estado* cabeza;
}Lista;

Estado* crearEstado(int ID);
void insertarFinal(Lista* lista, int ID);
Estado* crearEstados(int estadoInicial, int *estados, int estadoLength, char* transition, int *estadosOrigen, int* estadosDestino, int origenLength, int destinoLength);
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

Estado* crearEstados(int estadoInicial, int *estados, int estadoLength, char* transition, int *estadosOrigen, int* estadosDestino, int origenLength, int destinoLength){
  Lista* lista;
  Estado* estadoCabeza;
  Estado* puntero;

  for (size_t i = 0; i < estadoLength; i++) {
    insertarFinal(lista, estados[i]);
  }
  estadoCabeza = lista->cabeza;
  while ((estadoCabeza->estadoID) != estadoInicial) {
    estadoCabeza = estadoCabeza->apuntadorTemp;
  }

  puntero = estadoCabeza;
  


  return estadoCabeza;
}

Estado* crearEstado(int ID){
  Estado* estado = (Estado*)malloc(sizeof(estado));
  estado->estadoID = ID;
  estado->apuntadorTemp = NULL;
  return estado;
}

#endif
