//Autor: Carlos Fernández Deus
#include <stdio.h>
#include <ctype.h>
#include <string.h> //sirve también para el funcionamiento de strchr
#include <stdlib.h>
#include "database.h"
#include "inout.h"

    // CONSTANTES (CARÁTULA):
#define APLICACION "DIVOC_"
#define CAR_CAJA '-'
#define SIGNO '|'
#define TAM_LINEA 50
#define COMPARED_WORD "TRWAGMYFPDXBNJZSQVHLCKE"

//FUNCIONES (CARÁTULA):
void stripe (){
  int i;
  for (i=0; i<TAM_LINEA; i++)
    printf("%c", CAR_CAJA);
  printf ("\n");
  return;
}

void headline () {    // Función headline
  int division, i, numblancos;
  numblancos = TAM_LINEA - strlen(APLICACION);
  division = numblancos/2;
  printf ("%c", SIGNO);
   for(i=1; i<division; i++)
      printf ("%c", ' ');
   printf ("%s", APLICACION);
   for(i=1; i<division; i++)
     printf ("%c",' ');
   if (numblancos%2 == 1){ //si la division es par entonces haces solo eso.
     printf ("%c", ' ');//si la division no es par entonces sumas un espacio
    }
   printf ("%c", SIGNO); //esto ya es para cuando es par o impar
   printf ("\n");
  return;    // Sale de la función
}

//FUNCIONES (MENU):
void get_string(char *mensaje, char *la_cadena, int min, int max){ //Practica 3 ej3 modificado
  int valores, salir = 0, longitud_cadena; //Se inicializa aquí salir = 0
  char cadena [256];
  char linea [256];
  char extra [256];
  // char cadena [30]; Antes era necesario esot
  // Ahora no es necesaria porque queremos copiar mensaje si tiene una longitud menor de 24 en la_cadena
 do {
   fprintf (stdout, "\n%s (%d-%d char): ", mensaje, min, max);
   fgets(linea, sizeof(linea), stdin);
   valores = sscanf(linea, "%s%s", cadena, extra);
   longitud_cadena = strlen (cadena);
   //No se usa linea[0]='\n' en vez de eso se utiliza valores != 1
   //No se usa valores > max || valores < min, es mejor usar la longitud de la cadena
   if ( (strlen(linea) == 1) || (longitud_cadena < min) || (longitud_cadena > max) || (valores != 1) ) {
     salir = 0;
   } else {
     salir = 1;
   }
 } while (salir == 0);
 cadena[strlen(cadena)] = '\0'; //Para que no sobre espacios, de esta manera la cadena solo ocupa lo que mide y no más.
 strcpy (la_cadena, cadena);
};//No se pone return 0; porque es una void, aunque se podría poner return;

int get_integer (char *mensaje, int min, int max){ //Esta función nos perimte obtener un entero bajo ciertas condiciones
  int entero, salir = 0;
  char linea [256];
  char extra [256];
  int valores;
  do{
    printf ("\n%s [%d-%d]: ", mensaje, min, max);
    fgets (linea,sizeof(linea), stdin);
    if (linea[0] == '\n'){
      salir = 0;
    }else{
      valores = sscanf(linea,"%d%s",&entero,extra);
      if (valores != 1){
	//valores = numero de concordancias al escanear linea, es decir, si entra algo en extra tb valores == 2
	salir = 0;
      }else{
	if((entero < min)||(entero > max)){
	  salir = 0;
	}else{
	  salir = 1;
	}
      }
    }
  }while (salir == 0);
return entero;
}

int verify_DNI(char *DNI){
  int longitud, numero, indice, i;
  char palabra [25];
  char letra;
  longitud = strlen(DNI);
  if (longitud == 9){
    letra = DNI[8];
    for(i=0; i<(longitud-1); i++){
      if(isdigit(DNI[i]) == 0){
	return 0;
	//La función isdigit() comprueba si en el array DNI[i] hay solo numeros o si también hay letras
	//Si en el DNI[] solo hay numeros el isdigit(DNI[i]) retornará 1.
	//Sin embargo, en el caso de que haya un letra, is digit(DNI[i]) retornará 0 en vez de 1
      }
    }
    numero = atoi(DNI);
    //Coge todo el DNI y solo convierte a DNI los numeros que están dentro de la cadena
    indice = numero%23;
    strcpy (palabra, COMPARED_WORD);
    if ((toupper(letra)) == palabra [indice]){
    return 1;
    };
  }
  return 0;
};

//FUNCIÓN YES_OR_NO:
//Comprueba una acción desde el teclado. Retorna un 1 si el usuario escribe 'y' o 'Y'. Retorna 0 si el usuario escribe 'n' o 'N'.
int yes_or_no(char *mensaje){
  char opcion;
  char linea[256];
  char extra[256];
  int salir =  0;
  int valores = 0;
  do{
    printf("\n%s", mensaje );
    fgets(linea,sizeof(linea),stdin);
    if (strlen(linea) == 1){
      salir = 0;
    }else{
      valores = sscanf(linea,"%c%s", &opcion,extra);
      if(valores != 1){
	salir = 0;
      }else{
	opcion = toupper(opcion);
	if ((opcion == 'Y') || (opcion == 'N')){
	  salir = 1;
	}else{
	  salir = 0;
	}
      }
    }
  }while (salir == 0);
  if (opcion == 'Y'){
    return 1;
  }else{
    return 0;
  }
}
  // Si no es ni 'Y' ni 'N' vuelve al "do"

//FUNCIÓN GER_CHARACTER:
//Comprueba si una letra (si escribes una palabra no vale, tiene que ser un solo caracter) escrita desde el teclado es igual a una serie de caracteres probenientes del p_register (en este caso *comprobacion).
char get_character(char *mensaje, char *comprobacion){
  char comprobada;
  char linea[256];
  char extra[256];
  int salir, valores;
  
  do{
    printf("\n%s (%s): ", mensaje, comprobacion);
    fgets(linea, sizeof(linea), stdin);
    valores = sscanf(linea, "%c%s", &comprobada, extra);
    comprobada = toupper(comprobada);
    if( (strlen(linea) == 1) || (valores != 1) || (strchr(comprobacion, comprobada) == NULL) ) {
      salir = 0;
    } else {
      salir = 1;
    };
  }while (salir == 0);
  
  return comprobada; 
}

//FUNCIÓN DISPLAY_PATIENT:
//Sirve para mostrar los datos de la struct tabla[*numPacientes] 
void display_patient (struct unPaciente paciente){
  printf(">");
  printf("%24s;", paciente.name);
  printf("%9s;", paciente.DNI);
  printf("%4d;", paciente.age);
  printf("%1d;", paciente.fever);
  printf("%1d;", paciente.cough);
  printf("%1c; \n", paciente.symptom);
  //Poniendo el 24s o el 9s consigues que todo quede bien colocado
}
