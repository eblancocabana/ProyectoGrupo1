#include <iostream>
#include <istream>
#include <string>
#include <windows.h>
#include <cstring>
#include <time.h>

#include "reservar_local.h"
#include "inicio.h"
#include "enviar_datos.h"
#include "clases/reservalocal.h"

#define MAX_SELECCION 5
#define MAX_NOMBRE_DISCOTECA 20
#define MAX_FECHA 15
#define MAX_CODIGO 10

#define MAX_NUMERO_TARJETA 25
#define MAX_CVV 5
#define MAX_CADUCIDAD 10

using namespace std;

char opcionReserva;
char opcionPagoReserva;
char opcionConfirmarReserva;

int codLocal;
char* fecha_loc;
char* nombreDiscoteca;
int aforo = 400;
char numeroTarjeta[MAX_NUMERO_TARJETA];
char cvvTarjeta[MAX_CVV];
char caducidadTarjeta[MAX_CADUCIDAD];
char* r;

char mostrarListado() {
    cout << "\nListado de dias disponible: (codigo - fecha - nombre discoteca - aforo - evento?)\n\n";

    //BD
    r = enviar_datos_char("mostrarLocales", 0);
    printf(r);
    cout << "\nOpcion reserva:\n\t1. Realizar reserva \n\t0. Atras\n\nElige una opcion: ";

    char inputReservaLocal[MAX_SELECCION];
    cin.getline(inputReservaLocal, sizeof(inputReservaLocal));

    return inputReservaLocal[0];
}

int elegirCodigo() {
    cout << "\n\tIntroduce el codigo del local: ";
    char inputCodigo[MAX_CODIGO];
    int numCodigo;

    cin.getline(inputCodigo, sizeof(inputCodigo));
    sscanf(inputCodigo, "%d", &numCodigo);
    return numCodigo;
}

void reservarLocal() {
    int existe = 0;
    int codigo;
    char inputCod[MAX_CODIGO+5];
    char* cod;
    char* type;
    char auxCodigo[16];
    char* resultado;

    do {
        opcionReserva = mostrarListado();

        switch (opcionReserva) {
        case '1':
            cout << "\n---------------------------------------------------\n";
            do {
                cout << "Introducir codigo del local: ";
                cin.getline(inputCod, MAX_CODIGO);
                sscanf(inputCod, "%d", &codigo);
                        
                //BD
                cod = enviar_datos_char("limpiarInput", 1, &inputCod, sizeof(inputCod));
                printf("%s\n", cod);

                errno = 0;
                long int num = strtol(cod, &type, 10); //CodigoFecha
                codLocal = num;
                if (errno != 0 || *type != '\0') {
                    cout << "'" << cod << "' no es una entrada valida\n";
                }

            } while (errno != 0 || *type != '\0');

            sprintf(auxCodigo, "%d", codigo);

            //BD
            existe = enviar_datos_int("comprobarCodigoLocal", 1, auxCodigo, strlen(auxCodigo));
            
            if (existe == 1) {
                cout << "Local con codigo: '" << auxCodigo << "' seleccionada correctamente\n";
                pagarReserva();
            } else if ( existe == -1) {
                cout << "El codigo del local seleccionado no existe\nOperacion cancelada\n";

            } else {
                cout << "Codigo seleccionado incorrectamente\nOperacion cancelada\n";
            }

            break;
        }

    } while (opcionReserva != '0');
}


char mostrarPagarReserva() {
    cout << "\nPagar reserva:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    char inputPagarReserva[MAX_SELECCION];
    int numPagarReserva;

    cin.getline(inputPagarReserva, sizeof(inputPagarReserva));
    sscanf(inputPagarReserva, "%d", &numPagarReserva);

    return inputPagarReserva[0];
}

char confirmarPagoReserva() {
    cout << "\nConfirmar pago:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    char inputConfirmarReserva[MAX_SELECCION];
    int numConfirmarReserva;

    cin.getline(inputConfirmarReserva, sizeof(inputConfirmarReserva));
    sscanf(inputConfirmarReserva, "%d", &numConfirmarReserva);

    return inputConfirmarReserva[0];
}


char* introducirNumeroTarjeta() {
    cout << "\n\tIntroduce el numero de tarjeta (sin espacios): ";
    char* inputNumeroTarjeta = new char[MAX_NUMERO_TARJETA];
    cin.getline(inputNumeroTarjeta, MAX_NUMERO_TARJETA);
    return inputNumeroTarjeta;
}

char* introducirCVVTarjeta() {
    cout << "\tIntroduce el CVV de tarjeta: ";
    char* cvvTarjeta = new char[MAX_CVV];
    cin.getline(cvvTarjeta, MAX_CVV);
    return cvvTarjeta;
}

char* introducirCaduTarjeta() {
    cout << "\tIntroduce la caducidad de tarjeta (mm/aa): ";
    char* caducidadTarjeta = new char[MAX_CADUCIDAD];
    cin.getline(caducidadTarjeta, MAX_CADUCIDAD);
    return caducidadTarjeta;
}


void pagarReserva() {
    do {
        opcionPagoReserva = mostrarPagarReserva();

        switch (opcionPagoReserva) {
        case '1':
            cout << "\n---------------------------------------------------\n";
            cout << "Introducir datos de la tarjeta";

            strcpy(numeroTarjeta, introducirNumeroTarjeta());
            strcpy(cvvTarjeta, introducirCVVTarjeta());
            strcpy(caducidadTarjeta, introducirCaduTarjeta());

            confirmarReserva();
            break;
        }

    } while (opcionPagoReserva != '0');
}


void confirmarReserva() {
    do {
        opcionConfirmarReserva = confirmarPagoReserva();
        
        switch (opcionConfirmarReserva) {
        case '1':
            cout << "\nEL PAGO HA SIDO CONFIRMADO\n"; //bd
            const char* codigo_aux = (std::to_string(codLocal)).c_str();
            fecha_loc = enviar_datos_char("buscarFechaConCodidoFecha", 1, codigo_aux, strlen(codigo_aux)+1);
            nombreDiscoteca = enviar_datos_char("buscarDiscotecaConCodigoFecha", 1, codigo_aux, strlen(codigo_aux)+1);
            const char* aforo_aux = (std::to_string(aforo)).c_str();

            int resultado = enviar_datos_int("insertarReservaLocal", 7, codigo_aux, strlen(codigo_aux)+1, fecha_loc, strlen(fecha_loc)+1, nombreDiscoteca, strlen(nombreDiscoteca)+1, aforo_aux, strlen(aforo_aux)+1, numeroTarjeta, strlen(numeroTarjeta)+1, cvvTarjeta, strlen(cvvTarjeta)+1, caducidadTarjeta, strlen(caducidadTarjeta)+1);

            menu();
            opcionConfirmarReserva = '0';
            opcionPagoReserva = '0';
            opcionReserva = '0';
            break;

        }
    } while (opcionConfirmarReserva != '0');
}
