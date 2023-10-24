//FUNCIONES CARÁTULA:
void stripe ();
void headline();

typedef struct unPaciente datosPacientes; // Hacemos un typedef para simplificar el codigo.

//FUNCIONES MENU:
void get_string(char *mensaje, char *la_cadena, int min, int max);
int get_integer (char *mensaje, int min, int max);
int yes_or_no(char *mensaje);
int verify_DNI(char *DNI);
char get_character(char *mensaje, char *comprobacion);
void display_patient (datosPacientes paciente);
