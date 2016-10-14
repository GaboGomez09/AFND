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
Estado* crearEstados(char*alfabeto, int estadoInicial, int *estados, int estadoLength, char* transition, int *estadosOrigen, int* estadosDestino, int origenLength, int destinoLength);
void inicializarTransiciones(Lista* lista);
int posicionDeCaracter(char letra, char* alfabeto);
Estado* direccionDeEstadoDestino(Lista* lista, int destinoID);


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

  lista->cabeza = NULL;

  for (size_t i = 0; i < estadoLength; i++) {
    insertarFinal(lista, estados[i]);
  }

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

  //falta crear el estado zombie y vincular las transiciones correspondientes a él

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
