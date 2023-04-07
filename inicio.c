#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include "inicio.h"
#include "reservar_local.h"
#include "comprar_entradas.h"
#include "basedatos/sqlite/sqlite3.h"
#include "basedatos/baseDatos.h"
#include "servidor/inicio_servidor.h"
 
#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_LOGIN 15

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

char* name;
char* username;
char* sex;
int edad;
char* correoElec;
char* password;

char mostrarLogin() {
  char inputLogin[MAX_SELECCION];
  int numLogin;
  printf("\nInicio Sesion: \n\t1. Registrarse \n\t2. Login \n\t0. Salir \n\n Elige una opcion: ");

  fgets(inputLogin, MAX_SELECCION, stdin);
  sscanf(inputLogin, "%d", & numLogin);

  return * inputLogin;
}

char mostrarRegistrarse() {
  char inputRegistrarse[MAX_SELECCION];
  int numRegistrarse;
  printf("\n\t1. Aceptar \n\t0. Atras \n\n Elige una opcion: ");

  fgets(inputRegistrarse, MAX_SELECCION, stdin);
  sscanf(inputRegistrarse, "%d", & numRegistrarse);

  return * inputRegistrarse;
}

char mostrarMenu() {
  char inputMenu[MAX_SELECCION];
  int numMenu;
  printf("\nMenu Principal: \n\t1. Informacion de eventos \n\t2. Comprar entradas \n\t3. Reservar local \n\t4. Mis reservas / compras \n\t0. Cerrar Sesion \n\n Elige una opcion: ");

  fgets(inputMenu, MAX_SELECCION, stdin);
  sscanf(inputMenu, "%d", & numMenu);

  return * inputMenu;
}

void rellenarCamposRegistro() {
  char inputRegis[MAX_REGISTRO];
  char* nombre;
  char* nombreUsu;
  char* sexo;
  char* age;
  char* correo;
  char* contrasenya;
  char* repertirContrasenya;
  int existe = 1;
  char* type;

  printf("Menu Registro:\n\n");

  printf("Nombre: ");
  fgets(inputRegis, MAX_NOMBRE, stdin);
  sscanf(inputRegis, "%s", &nombre);

  name = limpiarInput(inputRegis);

  printf("Nombre de Usuario: ");
  fgets(inputRegis, MAX_NOMBRE_USU, stdin);
  sscanf(inputRegis, "%s", &nombreUsu);

  username = limpiarInput(inputRegis);

  printf("Sexo: ");
  fgets(inputRegis, MAX_SEXO, stdin);
  sscanf(inputRegis, "%s", &sexo);

  sex = limpiarInput(inputRegis);
   
  do {
    printf("Edad: ");
    fgets(inputRegis, MAX_EDAD, stdin);
    sscanf(inputRegis, "%i", &edad);
    age = limpiarInput(inputRegis);

    errno = 0;
    long int num = strtol(age, &type, 10);

    if (errno != 0 || *type != '\0') {
      printf("'%s' no es una edad valida\n", age);
    }

  } while (errno != 0 || *type != '\0');

  printf("Correo Electronico: ");
  fgets(inputRegis, MAX_CORREO, stdin);
  sscanf(inputRegis, "%s", &correo);

  correoElec = limpiarInput(inputRegis);

  printf("Contrasenya: ");
  fgets(inputRegis, MAX_CONTRASENYA, stdin);
  sscanf(inputRegis, "%s", &contrasenya);

  password = limpiarInput(inputRegis);

  printf("Repetir Contrasenya: ");
  fgets(inputRegis, MAX_CONTRASENYA, stdin);
  sscanf(inputRegis, "%s", &repertirContrasenya);

  char* repPass = limpiarInput(inputRegis);

  printf("\nDatos introducidos: %s - %s - %s - %s - %s - %s - %s\n", name, username, sex, age, correoElec, password, repPass);
  existe = comprobarUsuario(username);

  if ((existe == -1) && (strcmp(password, repPass) != 0)) {
    printf("Pero las contrasenyas NO coinciden\n");
    login();

  } else if ((existe == -1) && (strcmp(password, repPass) == 0)) {
    printf("Valores aceptados para ser introducidos a la BD\n\nQuiere registrarse?\n");  

  } else if (existe == 0) {
    printf("\nEl usuario ya existe, registro cancelado\n");
    login();
  }
}

void iniciarSesion() {
  int existe = 1;

  char input[MAX_REGISTRO];

  printf("Usuario: ");
  fgets(input, MAX_NOMBRE_USU, stdin);

  char* us = limpiarInput(input);

  printf("Contrasenya: ");
  fgets(input, MAX_CONTRASENYA, stdin);

  char* pa = limpiarInput(input);

  existe = comprobarExistencia(us, pa);

  if ((existe == 0) && (comprobarAdmin(us) == 0)) {
    printf("\nADMIN ENCONTRADO, accediendo al menu\n");
    inicioServidor();

  } else if ((existe == 0)) {
    printf("\nUSUARIO ENCONTRADO, accediendo al menu\n");
    menu();

  } else {

  }
}

int registrarse() {
  char opcionRegistrarse;

  rellenarCamposRegistro();

  do {
    opcionRegistrarse = mostrarRegistrarse();
    switch (opcionRegistrarse) {
    case '1':
      printf("\n---------------------------------------------------\n");
      insertarRegistro(name, username, sex, edad, correoElec, password);
      login();
      break;
    }
  } while (opcionRegistrarse != '0');

  return 0;
}

int login() {
  char opcionLogin;

  do {
    opcionLogin = mostrarLogin();
    switch (opcionLogin) {
    case '1':
      printf("\n---------------------------------------------------\n");
      registrarse();
      break;

    case '2':
      printf("\n---------------------------------------------------\n");
      iniciarSesion();
      break;
    }

  } while (opcionLogin != '0');

  if (opcionLogin == 0) {
    exit(0);
  }

  return 0;
}

int menu() {
  char opcionMenu;

  do {
    opcionMenu = mostrarMenu();
    switch (opcionMenu) {
    case '1':
      printf("\n---------------------------------------------------\n");
      printf("Listado de eventos\n\n");
      mostrarlistadoeventos();
      break;

    case '2':
      printf("\n---------------------------------------------------\n");
      printf("Menu de compra de entrada\n\n");
      break;

    case '3':
      printf("\n---------------------------------------------------\n");
      printf("Reservar el local\n\n");
      reservarLocal();
      break;

    case '4':
      printf("\n---------------------------------------------------\n");
      printf("Listado de mis reservas\n\n");
      break;
    }

  } while (opcionMenu != '0');

  return 0;
}