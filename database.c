#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "database.h"
#include "inout.h"

//FUNCIONES (MENU):

//FUNCIÓN P_REGISTER:
//Sirve para registrar a los pacientes
int p_register (struct unPaciente *tabla, int *numero) {
  //Usamos struct losPacientes *tabla, para crear así un array de structs con todos los pacientes. Este utiliza los datos del struct losPacientes que pasa la función p_register en el divoc. Esa struct está declarada en el database.h
  
  //numPacientes se lo pasa la función del divoc p_register. Este numPacientes srive para poder incrementar ese numPacientes del divoc y que así el próximo paciente no sea el 0 otra vez sino sea el 1 dentro del array de structs.

  //Llamamamos a la función get_string ("Name", la_cadena) siendo Name el mensaje que le damos como parametro y siendo la_cadena el lugar donde se copiará el mensaje en la función, puesto que la_cadena coge el valor de *la_cadena en la función
  printf("\nRegister \n");
  get_string ("Name", tabla[*numero].name,1,24);
  do{
    get_string ("DNI", tabla[*numero].DNI,9,9);
    if(verify_DNI(tabla[*numero].DNI) == 0){
       printf("\nInvalid DNI\n");
    }else{
      break;
    }
  }while (1);
  tabla[*numero].age = get_integer("Date", 1900, 2020);
  tabla[*numero].fever = yes_or_no("Fever (y/n):");
  tabla[*numero].cough = yes_or_no("Cough (y/n):");
  tabla[*numero].symptom = get_character("Symptom", "FSTMN");
  printf("\nNew patient: \n");
  display_patient (tabla[*numero]);
  (*numero)++;
  
  return 0;    // Sale de la función 
}

//FUNCIÓN P_SEARCH:
//Sirve para buscar pacientes
int p_search (struct unPaciente *tabla, int numero) {
  int i, result;
  char p_DNI[10];
  fprintf (stdout, "\nSearch\n");
   if (numero == 0){
      printf("\nNo patients yet \n");
   }else{
     get_string("DNI",p_DNI,9,9);
     for(i=0; i<numero; i++){
       result = (strcmp(tabla[i].DNI, p_DNI));
       if (result == 0){
	 printf("\nPatient data: \n");
	 display_patient (tabla[i]);
	 break;
       }
       if ((i == (numero - 1)) && (result != 0)){
	 printf("\nUnknown patient");
       }
     }
   }
  return 0;    // Sale de la función

}int p_discharge (struct unPaciente *tabla, int *numero) { 
  int i,j, result = 1;
  char p_DNI[10];

  fprintf (stdout, "\nDischarge\n");
  if(*numero == 0){
    printf("\nNo patients yet\n");
  }else{
    get_string("DNI", p_DNI,9,9);
    for (i=0; i<(*numero); i++){
      result = strcmp(tabla[i].DNI, p_DNI);
      if (result == 0){
	for(j=i; j<(*numero-1); j++){
	  tabla[j] = tabla[j+1];
	}
	printf("\nDischarged patient\n");
	(*numero)--;
	break;
      }
    }
      if (result != 0){
	printf("\nUnknown patient");
      }
    }
    return 0;    // Sale de la función

}int p_list (struct unPaciente *tabla, int numero) {
   int i, p_age;
  // *tabla sería la variable (como registro1)
  // No se hace *numero porque no queremos que el numPacientes del divoc cambie ya que ese es el numero de pacientes registrados.
  fprintf (stdout, "\nList \n");
  if(numero == 0){
    printf("\nNo patients yet\n");
  }else{
    p_age = get_integer("Date",1900,2020);
    printf("\nPatients born before %d:\n", p_age);
    for (i = 0; i < numero; i++){
      if(p_age >= tabla[i].age){
	display_patient(tabla[i]);
      }
    }
  }
    return 0;
    
}int p_mark (struct unPaciente *tabla, int numero){
  int i;
  char comprobacion[4] = "FSTM";
  printf ("\nPositives\n");
  if (numero == 0){
    printf("\nNo patients yet\n");
  }else{
    printf("\nPositive patients:\n");
    for(i=0; i < numero; i++){
      if( (tabla[i].fever == 1) && (tabla[i].cough == 1) ){
	if(strchr(comprobacion, tabla[i].symptom) == NULL){
	}else{
	display_patient(tabla[i]);
	}
      }
    }
  }
  return 0;
}
  
//FUNCIONES DE FICHEROS:

int r_fich(struct unPaciente *tabla, int *numero, char *mensaje){
  FILE *fich_patients;
  int i;
  char linea [256];
  char name[25];
  char DNI[10];
  int age;
  int fever,cough;
  char symptom;
  fich_patients = fopen (mensaje, "r");
  if(fich_patients == NULL){ //si no existe fichero ya no hace el resto porque no es necesario copiar los datos del fichero a la tabla de pacientes
    return -1;
  }  while (fgets(linea, sizeof(linea), fich_patients) != NULL){ //Si el fichero exite pero esta vacio no tiene que copiar nada (si es == NULL entonces esta vacio)
    sscanf(linea, "%s %s %d %d %d %c", name, DNI, &age, &fever, &cough, &symptom);
    strcpy(tabla[*numero].name,name);
    strcpy(tabla[*numero].DNI,DNI);
    tabla[*numero].age = age;
    tabla[*numero].fever = fever;
    tabla[*numero].cough = cough;
    tabla[*numero].symptom = symptom;
    i++;
    (*numero)++;
  }
  fclose (fich_patients);
  return 0;
}

int w_fich(struct unPaciente *tabla, int numero, char *mensaje){
  FILE *fich_patients;
  int i;
  fich_patients = fopen(mensaje, "w");
  for (i=0; i<numero; i++){
    fprintf(fich_patients, "%s %s %d %d %d %c\n", tabla[i].name, tabla[i].DNI, tabla[i].age, tabla[i].fever, tabla[i].cough, tabla[i].symptom);
  }
  fclose(fich_patients);
  return 0;
}
  
  

