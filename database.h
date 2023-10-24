//DECLARACIONES DE LAS FUNCIONES DEL MENU
struct unPaciente{
  char name[25];
  char DNI[10];
  unsigned short age;
  unsigned char fever;
  unsigned char cough;
  char symptom;
};

typedef struct unPaciente datosPacientes; // Hacemos un typedef para simplificar el codigo.

//Declaramos la struct anterior como regPacientes por comodidad

//MENU
int p_register (datosPacientes *tabla, int *numero);
int p_search (datosPacientes *tabla, int numero);
int p_discharge (datosPacientes *tabla, int *numero);
int p_list (datosPacientes *tabla, int numero);
int p_mark (datosPacientes *tabla, int numero);

//FICHEROS:
int r_fich (datosPacientes *tabla, int *numero, char *mensaje);
int w_fich (datosPacientes *tabla, int numero, char *mensaje);
