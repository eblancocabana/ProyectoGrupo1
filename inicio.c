#include <stdio.h>
#include "inicio.h"

#define MAX_SELECCION 5
#define MAX_REGISTRO 20

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

char mostrarLogin() {
    char inputLogin[MAX_SELECCION];
    int numLogin;
    printf("\nInicio Sesion: \n\t1. Registrarse \n\t2. Login \n\t0. Salir \n\n Elige una opcion: ");

    fgets(inputLogin, MAX_SELECCION, stdin);
    sscanf(inputLogin, "%d", &numLogin);

    return *inputLogin;
}

char mostrarRegistrarse() {
    char inputRegistrarse[MAX_SELECCION];
    int numRegistrarse;
    printf("\n\t1. Aceptar \n\t2. Atras \n\n Elige una opcion: ");

    fgets(inputRegistrarse, MAX_SELECCION, stdin);
    sscanf(inputRegistrarse, "%d", &numRegistrarse);

    return *inputRegistrarse;
}

char mostrarMenu() {
    char inputMenu[MAX_SELECCION];
    int numMenu;
    printf("\nMenu Principal: \n\t1. Informacion de eventos \n\t2. Comprar entradas \n\t3. Reservar local \n\t4. Mis reservas / compras \n\t0. Cerrar Sesion \n\n Elige una opcion: ");

    fgets(inputMenu, MAX_SELECCION, stdin);
    sscanf(inputMenu, "%d", &numMenu);

    return *inputMenu;
}

char rellenarCamposRegistro() {
    char inputRegis[MAX_REGISTRO];
    char* nombre;
    char* nombreUsu;
    char* sexo;
    int edad;
    char* correo;
    char* contrasenya;
    char* repertirContrasenya;

    printf("Menu Registro:\n\n");

    printf("Nombre: ");
    fgets(inputRegis, MAX_NOMBRE, stdin);
    sscanf(inputRegis, "%d", &nombre);

    printf("Nombre de Usuario: ");
    fgets(inputRegis, MAX_NOMBRE_USU, stdin);
    sscanf(inputRegis, "%d", &nombreUsu);

    printf("Sexo: ");
    fgets(inputRegis, MAX_SEXO, stdin);
    sscanf(inputRegis, "%d", &sexo);

    printf("Edad: ");
    fgets(inputRegis, MAX_EDAD, stdin);
    sscanf(inputRegis, "%d", &edad);

    printf("Correo Electronico: ");
    fgets(inputRegis, MAX_CORREO, stdin);
    sscanf(inputRegis, "%d", &correo);

    printf("Contrasenya: ");
    fgets(inputRegis, MAX_CONTRASENYA, stdin);
    sscanf(inputRegis, "%d", &contrasenya);

    printf("Repetir Contrasenya: ");
    fgets(inputRegis, MAX_CONTRASENYA, stdin);
    sscanf(inputRegis, "%d", &repertirContrasenya);

    return *inputRegis;
}

int registrarse() {
    char opcionRegistrarse;

    rellenarCamposRegistro();

    do {
        opcionRegistrarse = mostrarRegistrarse();
        switch (opcionRegistrarse) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                login();
            break;
                
            case '2': 
                printf("\n---------------------------------------------------\n");
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
                menu();
            break;
        }

    } while (opcionLogin != '0');

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
            break;
                
            case '2': 
                printf("\n---------------------------------------------------\n");
                printf("Menu de compra de entrada\n\n");
            break;

            case '3': 
                printf("\n---------------------------------------------------\n");
                printf("Reservar el local\n\n");
            break;

            case '4':
                printf("\n---------------------------------------------------\n"); 
                printf("Listado de mis reservas\n\n");
            break;
        }

    } while (opcionMenu != '0');

    return 0;
}