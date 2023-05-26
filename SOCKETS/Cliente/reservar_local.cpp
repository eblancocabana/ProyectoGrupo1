#include <iostream>
#include "reservar_local.h"
//#include "basedatos/baseDatos.h"
#include "inicio.h"
#include <istream>
#include "enviar_datos.h"
#include <cstring>
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

char mostrarListado() {
    cout << "\nListado de dias disponible: (codigo - fecha - nombre discoteca - aforo - evento?)\n\n";
    //BD
    enviar_datos_char("mostrarLocales", 0);
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
    int codLocal;
    int existe = 0;

    do {
        opcionReserva = mostrarListado();
        switch (opcionReserva) {
        case '1':
            cout << "\n---------------------------------------------------\n";
            cout << "Introducir fecha y nombre de discoteca";

            codLocal = elegirCodigo();
            //BD
            existe = enviar_datos_int("comprobarCodigoLocal", 1, codLocal);
            

            pagarReserva();
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
    char numeroTarjeta[MAX_NUMERO_TARJETA];
    char cvvTarjeta[MAX_CVV];
    char caducidadTarjeta[MAX_CADUCIDAD];

    do {
        opcionPagoReserva = mostrarPagarReserva();
        switch (opcionPagoReserva) {
        case '1':
            cout << "\n---------------------------------------------------\n";
            cout << "Introducir datos de la tarjeta";

            strcpy(numeroTarjeta,introducirNumeroTarjeta());
            strcpy(cvvTarjeta,introducirCVVTarjeta());
            strcpy(caducidadTarjeta,introducirCaduTarjeta());

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
            cout << "\nEL PAGO HA SIDO CONFIRMADO"; //bd
            fecha_loc = enviar_datos_char("buscarFechaConCodidoFecha", 1, codLocal);
            nombreDiscoteca = enviar_datos_char("buscarDiscotecaConCodigoFecha", 1, codLocal);
            struct ReservaLocal {
                    int codigo;
                    char* fecha;
                    char* nomDiscoteca;
                    int numPersonas;
                    char* numTarjeta;
                    char* cvvTar;
                    char* caducidadTar;
    
                    ReservaLocal(int codigo, char* fecha, char* nomDiscoteca, int numPersonas,
                        char* numTarjeta, char* cvvTar, char* caducidadTar);

                    ReservaLocal* rl = new ReservaLocal(codLocal, fecha_loc, nombreDiscoteca, aforo, numeroTarjeta, cvvTarjeta, caducidadTarjeta);
                };
            

            menu();
            opcionConfirmarReserva = '0';
            opcionPagoReserva = '0';
            opcionReserva = '0';
            break;
        }
    } while (opcionConfirmarReserva != '0');
}
