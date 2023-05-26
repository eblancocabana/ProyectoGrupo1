#include <iostream>
#include <string.h>
#include "comprar_entradas.h"
//#include "basedatos/sqlite/sqlite3.h"
//#include "basedatos/baseDatos.h"
#include "inicio.h"
#include "enviar_datos.h"
#include "clases/entrada.h"


#define MAX_SELECCION 5
#define MAX_ENTRADAS 10
#define MAX_NOMBRE 40
#define MAX_GMAIL 30
#define MAX_NUM_TARJETA 20
#define MAX_CVV 5
#define MAX_CADUCIDAD 10
#define MAX_COD_RRPP 5

using namespace std;

char opcionDatosCompra;
char opcionPagoEntrada;
char opcionConfirmarPago;
char opcionConfirmarCompra;

int codigoFecha_ent;
char* fecha_ent;
char* nomDiscoteca;
int numEntradas;
char* nombreCompleto;
char* gmail;
char* numTarjeta;
char* cvvTar;
char* caducidadTar;
int tipoEntradas;
const char* entradaCat;
int longitud;
double precios;
char* entradaCatFin;

char mostrarDatosCompra(){
    cout << "\nDatos necesarios:\n\t1. Comprar \n\t0. Atras\n\nElige una opcion: ";

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    cin.getline(inputDatosCompra, MAX_SELECCION);
    sscanf(inputDatosCompra, "%d", &numDatosCompra);

    return *inputDatosCompra;
}

int introducirNumEntradas(){
    cout << "\n\tIntroduce el numero de entradas: ";

    char inputNumEntradas[MAX_ENTRADAS];
    int numEntradas;

    cin.getline(inputNumEntradas, MAX_ENTRADAS);
    sscanf(inputNumEntradas, "%d", &numEntradas);
    return numEntradas;
}

char* introducirNombreCompleto(){
    cout << "\tIntroduce tu nombre de usuario: ";

    char* inputNombreCompleto = new char[MAX_NOMBRE];
    cin.getline(inputNombreCompleto, MAX_NOMBRE);
    return inputNombreCompleto;
}

char* introducirGmail(){
    cout << "\tIntroduce tu cuenta de gmail: ";

    char* inputGmail = new char[MAX_GMAIL];
    cin.getline(inputGmail, MAX_GMAIL);
    return inputGmail;
}

void datosCompra(int codFecha, int tipoEntrada, double precio){
    //int numEntradas;
    //char* nombreCompleto;
    //char* gmail;

    codigoFecha_ent = codFecha;
    tipoEntradas = tipoEntrada;
    precios = precio;

    do{
        opcionDatosCompra = mostrarDatosCompra();
        switch(opcionDatosCompra){
            case '1':
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir datos de la compra";
                numEntradas = introducirNumEntradas(); //ENTRADAS
                nombreCompleto = introducirNombreCompleto();
                gmail = introducirGmail();

                int len = strcspn(nombreCompleto, "\n");
                nombreCompleto[len] = '\0';

                len = strcspn(gmail, "\n");
                gmail[len] = '\0';

                pagarEntrada();
            break;
        }
    } while(opcionDatosCompra != '0');
}

char mostrarPagarEntrada(){
    cout << "\nPagar entrada:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    char inputPagarEntrada[MAX_SELECCION];
    int numPagarEntrada;

    cin.getline(inputPagarEntrada, MAX_SELECCION);
    sscanf(inputPagarEntrada, "%d", &numPagarEntrada);

    return *inputPagarEntrada;
}

char* introducirNumTarjeta() {
    cout << "\n\tIntroduce el numero de tarjeta (sin espacios - 9 caracteres): ";

    char* inputNumTarjeta = new char[MAX_NUM_TARJETA];
    cin.getline(inputNumTarjeta, MAX_NUM_TARJETA);
    return inputNumTarjeta;
}

char* introducirCaducidadTarjeta() {
    cout << "\tIntroduce la caducidad de tarjeta (mm/aa): ";

    char* inputCaducidad = new char[MAX_CADUCIDAD];
    cin.getline(inputCaducidad, MAX_CADUCIDAD);
    return inputCaducidad;
}

char* introducirCVVTar() {
    cout << "\tIntroduce el CVV de tarjeta: ";

    char* inputCVV = new char[MAX_CVV];
    cin.getline(inputCVV, MAX_CVV);
    return inputCVV;
}

void pagarEntrada(){
    //char* numTarjeta;
    //char* cvvTarjeta;
    //char* caducidadTarjeta;

    do{
        opcionPagoEntrada = mostrarPagarEntrada();
        switch(opcionPagoEntrada){
            case '1':
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir datos de la tarjeta";
                numTarjeta = introducirNumTarjeta(); //TARJETA
                cvvTar = introducirCVVTar();
                caducidadTar = introducirCaducidadTarjeta();

                int len = strcspn(numTarjeta, "\n");
                numTarjeta[len] = '\0';

                len = strcspn(cvvTar, "\n");
                cvvTar[len] = '\0';

                len = strcspn(caducidadTar, "\n");
                caducidadTar[len] = '\0';

                confirmarPago();
            break;
        }
    } while(opcionPagoEntrada != '0');
}

char mostrarConfirmarPago(){
    cout << "\nConfirmar pago:\n\t1. Confirmar pago (RRPP)\n\t0. Atras\n\nElige una opcion: ";

    char inputConfirmarPago[MAX_SELECCION];
    int numConfirmarPago;

    cin.getline(inputConfirmarPago, MAX_SELECCION);
    sscanf(inputConfirmarPago, "%d", &numConfirmarPago);

    return *inputConfirmarPago;
}

char confirmarPagoCompra(){
    cout << "\nConfirmar pago:\n\t1. Confirmar\n\t0. Atras\n\nElige una opcion: ";

    char inputConfirmarCompra[MAX_SELECCION];
    int numConfirmarCompra;

    cin.getline(inputConfirmarCompra, MAX_SELECCION);
    sscanf(inputConfirmarCompra, "%d", &numConfirmarCompra);

    return *inputConfirmarCompra;
}

int introducirCodigoRRPP() {
    cout << "\n\tIntroduce el codigo del RRPP: ";

    int inputCodRRPP;
    cin >> inputCodRRPP;
    return inputCodRRPP;
}


void confirmarPago(){
    int codigoRRPP;

    do{
        opcionConfirmarPago = mostrarConfirmarPago();
        switch(opcionConfirmarPago){
            case '1':
                cout << "\n---------------------------------------------------\n";
                enviar_datos_char("mostrarRRPP", 0);
                //mostrarRRPP(); BD
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir Codigo de RRPP";
                codigoRRPP = introducirCodigoRRPP();
                //BD
                enviar_datos_int("comprobarCodigoRRPP", 1, &codigoRRPP, sizeof(codigoRRPP));

                confirmarCompra();
            break;
        }
    } while(opcionConfirmarPago != '0');
}

void confirmarCompra(){
    do {
        opcionConfirmarCompra = confirmarPagoCompra();
        switch (opcionConfirmarCompra) {
            case '1':
                cout << "\nEL PAGO HA SIDO CONFIRMADO\n"; // bd
                fecha_ent = enviar_datos_char("buscarFechaConCodidoFecha", 1, codigoFecha_ent);
                nomDiscoteca = enviar_datos_char("buscarDiscotecaConCodigoFecha", 1, codigoFecha_ent);
                if (tipoEntradas == 1) {
                    entradaCat = "Una consumicion";
                } else if (tipoEntradas == 2) {
                    entradaCat = "Dos consumicion";
                } else if (tipoEntradas == 3) {
                    entradaCat = "Tres consumicion";
                } else {
                    entradaCat = "Reservado";
                }
                longitud = strlen(entradaCat)+1;
                entradaCatFin = new char[longitud];
                strcpy(entradaCatFin, entradaCat);

                struct Entrada {
                    int codigoFecha;
                    char* fechaEntrada;
                    char* nombreDiscoteca;
                    int numeroEntradas;
                    char* cuentaGmail;
                    char* numeroTarjetaCredito;
                    char* cvvTarjeta;
                    char* caducidadTarjeta;
                    char* tipoEntrada;
                    double precio;
                    char* usuario;
    
                    Entrada(int codigoFecha, char* fechaEntrada, char* nombreDiscoteca, int numeroEntradas, char* cuentaGmail,
                        char* numeroTarjetaCredito, char* cvvTarjeta, char* caducidadTarjeta, char* tipoEntrada, double precio,
                        char* usuario);

                    Entrada* e = new Entrada(codigoFecha_ent, fecha_ent, nomDiscoteca, numEntradas, gmail, numTarjeta, cvvTar, caducidadTar, entradaCatFin, precios, nombreCompleto);
                };

                opcionDatosCompra = '0';
                opcionPagoEntrada = '0';
                opcionConfirmarPago = '0';
                opcionConfirmarCompra = '0';
                menu();
            break;
        }
    } while (opcionConfirmarCompra != '0');
}
