#!/usr/bin/perl
#
# Recibe un argumento: el nombre del programa que queremos evaluar, y que
# contiene la versión de enero del proyecto Divoc
#
# Asume la existencia de un Makefile con reglas para generar un objetivo
# con nombre = divoc
#
# De no ser así, es decir, si no se genera dicho programa, sale dando el
# correspondiente mensaje de error.
#
#
# Autor: Pedro Rodríguez
#

use v5.22;
use File::Copy;
use experimental qw(smartmatch);

# use utf8;


# Funcion muestra_entorno()
# Recibe un parámetro: el número de la prueba
#
sub muestra_entorno {
  if (@_ != 1) {
    say <<'end_of_ca_help_message'; 
Mal uso de la funcion muestra_entorno()
uso: muestra_entorno (num_prueba);
          num_prueba    número de la prueba
end_of_ca_help_message
    exit 1;
  }

  my ${num_prueba} = shift @_;

  say "Condiciones de contorno:";
  given (${num_prueba}) {
    when ([0]) {
      say "A la entrada no existe el fichero de pacientes";
      say "El usuario se limita a salir";
      say "A la salida debe existir un fichero de pacientes vacío";
    }
    when ([1]) {
      say "A la entrada existe un fichero de pacientes vacío";
      say "El usuario se limita a salir";
      say "A la salida debe existir un fichero de pacientes vacío";
    }
    when ([2]) {
      say "A la entrada no existe el fichero de pacientes";
      say "El usuario intenta todas las operaciones imposibles sin pacientes";
      say "A la salida debe existir un fichero de pacientes vacío";
    }
    when ([3]) {
      say "A la entrada existe un fichero de pacientes vacío";
      say "El usuario teclea opciones incorrectas en el menú y en yes_or_no()";
      say "A la salida debe existir un fichero de pacientes vacío";
    }
    when ([4]) {
      say "A la entrada existe un fichero con 6 pacientes, copia de patientsA.base";
      say "El usuario intenta operaciones sobre pacientes inexistentes";
      say "A la salida debe existir el mismo fichero de pacientes";
    }
    when ([5]) {
      say "A la entrada existe un fichero con 6 pacientes, copia de patientsB.base";
      say "El usuario introduce datos erróneos antes de dar datos correctos";
      say "A la salida debe existir un fichero de pacientes con 2 cambios";
    }
    when ([6]) {
      say "A la entrada existe un fichero de pacientes vacío";
      say "El usuario registra 80 pacientes correctos";
      say "A la salida debe existir un fichero de pacientes idéntico a patientsC.base";
    }
    when ([7]) {
      say "A la entrada existe un fichero con 80 pacientes, copia de patientsC.base";
      say "El usuario realiza una serie de cambios";
      say "A la salida debe existir un fichero de pacientes con varios cambios";
    }
    when ([8]) {
      say "A la entrada existe un fichero con 6 pacientes, copia de patientsB.base";
      say "El usuario da de baja a todos los pacientes";
      say "A la salida debe existir un fichero de pacientes vacío";
    }
    when ([9]) {
      say "A la entrada existe un fichero con 3 pacientes, copia de patientsD.base";
      say "El usuario da de baja a todos los pacientes, intenta operaciones imposibles, y da de alta a 3 nuevos";
      say "A la salida debe existir un fichero con 3 nuevos pacientes";
    }
  }
  return ;
}

# Funcion compara_archivos()
# Recibe dos parámetros: los nombres de los dos archivos que se quiere comparar
#
sub compara_archivos {
  if (@_ != 2) {
    say <<'end_of_ca_help_message'; 
Mal uso de la funcion compara_archivos()
uso: compara_archivos (modelo archivo);
          modelo    nombre del modelo con el que se quiere comparar el archivo
          archivo   nombre del archivo que se quiere comparar con el modelo
end_of_ca_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;

  say "Comparamos:";
  say "el fichero ${archivo} generado por el programa que hemos evaluado";
  say "con el ${modelo} que debería haberse generado,";
  say "y mostramos las diferencias (si las hay)\n";

  my ${estado} = 0;
  system ("diff -Bw ${modelo} ${archivo}");
  if ($? == 0) {
    say "El fichero [01;32m${archivo}[00m es correcto";
  }
  else {
    say "El fichero [01;32m${archivo}[00m [01;31mNO[00m es correcto";
    ${estado} = 1;
  }

  say "\nPulsa enter para continuar...";
  my ${continuar} = <STDIN>;
  return ${estado};
}

# Funcion mueve_y_compara()
# Recibe dos parámetros: los nombres de los dos archivos que se quiere comparar
# tras asegurarse de que el que se quiere evaluar existe
#
sub mueve_y_compara {
  if (@_ != 2) {
    say <<'end_of_mc_help_message'; 
Mal uso de la funcion mueve_y_compara()
uso: mueve_y_compara (modelo archivo);
         modelo    nombre del modelo con el que se quiere comparar el archivo
         archivo   nombre del archivo que se quiere comparar con el modelo
end_of_mc_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;
  my ${estado} = 0;

  if ( -e "${archivo}") {
    rename "${archivo}", "my_${modelo}";
    ${archivo}="my_${modelo}";
    ${estado} = compara_archivos ("${modelo}", "${archivo}");
  }
  else {
    say "El fichero [01;31m${archivo}[00m no existe";
    say "Pulsa enter para continuar...";
    my ${continuar} = <STDIN>;
    ${estado} = 1;
  }
  return ${estado};
}

# Funcion prueba_existe()
# Recibe dos parámetros: el nombre del archivo que se quiere comprobar si
# existe y el del modelo de archivo que sería si existiese
#
sub prueba_existe {
  if (@_ != 2) {
    say <<'end_of_pe_help_message'; 
Mal uso de la funcion prueba_existe()
uso: prueba_existe (modelo archivo);
          modelo    nombre del modelo de archivo que sería si existiese
          archivo   nombre del archivo que se quiere comprobar si existe
end_of_pe_help_message
    exit 1;
  }

  my ${modelo} = shift @_;
  my ${archivo} = shift @_;

  say "\nComprobamos que el programa no ha generado un fichero [01;32mmy_${modelo}[00m\n";

  my ${estado} = 0;

  if ( -e "${archivo}") {
    rename "${archivo}", "my_${modelo}";
    ${archivo}="my_${modelo}";
    say "El fichero [01;32m${archivo}[00m [01;31mNO debería existir[00m\n";
    say "Pulsa enter para continuar...";
    my ${continuar} = <STDIN>;
    ${estado} = 1;
  }
  return ${estado};
}


if (@ARGV != 1) {
say <<'end_of_help_message'; 
   uso: $0 programa
          programa    nombre del programa que queremos evaluar

end_of_help_message
exit 1;
}


# El protocolo, propiamente dicho
#
my ${programa} = shift @ARGV;
my ${pruebas_falladas}=0;
my ${total_pruebas}=10;

say "\nProtocolo para evaluar un programa que contiene la versión de enero";
say "del proyecto Divoc\n";

say "El programa se llama: \"${programa}\"\n";

if ( ! -e "Makefile") {
  say "No existe un 'Makefile' capaz de generar el objetivo \"${programa}\"\n";
  exit 2;
}

say "Limpiamos el escenario";
system ("make clean");
unlink ("patients.txt", glob("my_patients[0-2][0-9].txt"), glob("my_output[0-2][0-9].txt"));

say "\nConstruimos la aplicación";
system ("make ${programa}");
say "\n";

if ( ! -e "${programa}") {
  say "El programa ${programa} no existe\n";
  exit 3;
}
elsif ( ! -x "${programa}") {
  say "El programa ${programa} no se puede ejecutar\n";
  exit 4;
}
else {
  say "Ejecutamos la batería de pruebas\n";

  for my ${num} (0..9) {
    say "[01;36mPrueba número ${num}[00m: ./${programa} < proto0${num}.txt > my_output0${num}.txt";
    muestra_entorno (${num});
    given (${num}) {
      when ([1, 3]) {
	copy ("patients0${num}.txt", "patients.txt");
      }
      when ([4]) {
	copy ("patientsA.base", "patients.txt");
      }
      when ([5]) {
	copy ("patientsB.base", "patients.txt");
      }
      when ([7]) {
	copy ("patientsC.base", "patients.txt");
      }
      when ([8]) {
	copy ("patientsB.base", "patients.txt");
      }
      when ([9]) {
	copy ("patientsD.base", "patients.txt");
      }
    }
    system ("ulimit -f 120 ; ./${programa} < proto0${num}.txt > my_output0${num}.txt");
    say "\nComprobaciones:";
    my ${cuenta_fallos} = 0;
    ${cuenta_fallos} += mueve_y_compara ("patients0${num}.txt", "patients.txt");
    ${cuenta_fallos} += compara_archivos ("output0${num}.txt", "my_output0${num}.txt");
    if (${cuenta_fallos} > 0) { ${pruebas_falladas}++; }
  }


  if (${pruebas_falladas} > 0) {
    say "\n[01;31m${pruebas_falladas} pruebas falladas de ${total_pruebas}[00m\n"
  }
  else {
    say "\n[01;32mTodas las pruebas se han superado correctamente[00m\n"
  }
}
