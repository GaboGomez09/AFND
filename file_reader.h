#ifndef file_reader
#define file_reader

void LeerArchivo(char **alfabeto, char **transition, int **estados, int *estadoInicial, int **estadosFinales, int **estadosOrigen, int **estadosDestino, int *estadoLength, int *estadosFinalesLength, int *origenLength, int *destinoLength);
void LeerLinea(char **buffer, FILE *filePointer);
void ConvertirNumeros(int **arreglo,char *buffer, int *arregloLength);
void FiltrarCaracteres(char **alfabeto, char *buffer);
void guardarFuncionesDelta(int **estadosOrigen, int *origenLength,char **transition, int **estadosDestino, int *destinoLength, FILE *apuntadorArchivo);

void LeerArchivo(char **alfabeto, char **transition, int **estados, int *estadoInicial, int **estadosFinales, int **estadosOrigen, int **estadosDestino, int *estadoLength, int *estadosFinalesLength, int *origenLength, int *destinoLength){
  FILE* apuntadorArchivo = fopen("automata.txt", "r");
  char *buffer;
  if (apuntadorArchivo == NULL) {
    printf("No se pudo abrir el archivo.\n");
  } else {
      LeerLinea(&buffer, apuntadorArchivo);
      ConvertirNumeros(estados,buffer, estadoLength);

      LeerLinea(&buffer, apuntadorArchivo);
      FiltrarCaracteres(alfabeto, buffer);

      LeerLinea(&buffer, apuntadorArchivo);
      (*estadoInicial) = atoi(buffer);

      LeerLinea(&buffer, apuntadorArchivo);
      ConvertirNumeros(estadosFinales, buffer, estadosFinalesLength);

      guardarFuncionesDelta(estadosOrigen, origenLength, transition, estadosDestino, destinoLength, apuntadorArchivo);

      fclose(apuntadorArchivo);
  }

}

void guardarFuncionesDelta(int **estadosOrigen, int *origenLength,char **transition, int **estadosDestino, int *destinoLength, FILE *apuntadorArchivo){
  int o, d;
  char t;
  int sizeOrigen = sizeof(int), sizeDestino = sizeof(int), sizeTransition = sizeof(char) + 1;
  *estadosOrigen = (int*)malloc(sizeOrigen*200);
  *transition = (char*)malloc(sizeTransition*200);
  *estadosDestino = (int*)malloc(sizeDestino*200);
  int i = 0;
  while (fscanf(apuntadorArchivo, "%d %c %d", &o, &t, &d) != EOF) {
    (*estadosOrigen)[i] = o;
    (*transition)[i] = t;
    (*estadosDestino)[i] = d;
    i++;
    (*transition)[i] = '\0';
    *origenLength = i;
    *destinoLength = i;
  }
  //(*transition)[i-1] = '\0';
  //printf("%s\n", *transition);
}

void LeerLinea(char **buffer, FILE *filePointer){
  char buf;
  int bufferSize = 1;
  *buffer = (char*)malloc(bufferSize);
  while ((buf = fgetc((filePointer))) != '\n') {
    *buffer = (char*)realloc(*buffer, bufferSize++);
    (*buffer)[bufferSize - 2] = buf;
    (*buffer)[bufferSize - 1] = '\0';
  }
}

void ConvertirNumeros(int **arreglo,char *buffer, int *arregloLength){
  char numero[100];
  for (size_t l = 0; l < 100; l++) {
    numero[l] = 0;
  }
  int k = 0, arregloSize = sizeof(int);
  *arreglo = (int*)malloc(arregloSize);
  for (size_t i = 0; i < strlen(buffer); i++) {
    int j = 0;
    while (buffer[i] != ',') {
      if (buffer[i] == '\000') {
        break;
      }else{
        numero[j] = buffer[i];
        i++;
        j++;
      }
    }
    (*arreglo)[k] = atoi(numero);
    *arreglo = (int*)realloc(*arreglo, arregloSize + 4);
    k++;
    *arregloLength = k;

  }
}

void FiltrarCaracteres(char **alfabeto, char *buffer){
  int alfabetSize = 1;
  *alfabeto = (char*)malloc(alfabetSize);
  for (size_t i = 0; i < strlen(buffer); i++) {
    if (isspace(buffer[i]) || ispunct(buffer[i])) {

    } else {
      *alfabeto = (char*)realloc(*alfabeto, alfabetSize++);
      (*alfabeto)[alfabetSize - 2] = buffer[i];
      (*alfabeto)[alfabetSize - 1] = '\0';

    }
  }
}
#endif
