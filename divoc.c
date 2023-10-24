// Autor: Carlos Fdez. Deus
// Fecha: 18-11-2020
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inout.h"
#include "database.h"

    // CONSTANTES (CARÁTULA):
#define APLICACION "DIVOC_"
#define CAR_CAJA '-'
#define SIGNO '|'
#define TAM_LINEA 50

    // CONSTANTES (MENU):
#define P_REGISTER 'R'
#define P_SEARCH 'S'
#define P_DISCHARGE 'D'
#define P_LIST 'L'
#define P_MARK 'P'
#define P_POSITIVE 'P'
#define P_EXIT 'X'

// ******************************* FUNCION PRINCIPAL DEL PROGRAMA ******************************
int main () {
  struct unPaciente losPacientes[256];
  int numPacientes = 0;
  int salir = 0;
  char caracter;
  
  // CARÁTULA DEL PROYECTO:
  stripe ();
  headline ();    // llamada a la función headline
  stripe ();
  r_fich(losPacientes, &numPacientes, "patients.txt");
  // MENU DEL PROYECTO:
  do{
    printf("\nR) Register a patient");
    printf("\nS) Search for a patient");
    printf("\nD) Discharge a patient");
    printf("\nL) List patients by age");
    printf("\nP) Mark positive");
    printf("\n\nX) Exit the program\n");
    
    caracter = get_character("Choose an option","RSDLPX");
    
    switch(caracter){
    case P_REGISTER:
      p_register(losPacientes, &numPacientes);
      break;
    case P_SEARCH:
      p_search(losPacientes, numPacientes);
      break;
    case P_DISCHARGE:
      p_discharge(losPacientes, &numPacientes);
      break;
    case P_LIST:
      p_list(losPacientes, numPacientes);
      break;
    case P_EXIT:
      break;
    case P_MARK:
      p_mark(losPacientes, numPacientes);
      break;
    }
    if(toupper(caracter) == P_EXIT){
      printf("\nExit\n");
      salir = yes_or_no("Are you sure you want to exit the program? (y/n):");
    }
  }while (salir != 1);
  w_fich(losPacientes, numPacientes, "patients.txt");
  //printf("\nHope to see you soon\n");
  return 0;    // sale de main() con valor 0
}

