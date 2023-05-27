#include <iostream>
#include <string.h>
#include "comprar_entradas.h"
//#include "basedatos/sqlite/sqlite3.h"
//#include "basedatos/baseDatos.h"
#include "inicio.h"
#include "enviar_datos.h"
#include "clases/entrada.h"
#include <windows.h>
#include <string>
#include <stdio.h>
#include <cstring>
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
char numTarjeta[MAX_NUM_TARJETA];
char cvvTar[MAX_CVV];
char caducidadTar[MAX_CADUCIDAD];
int tipoEntradas;
const char* entradaCat;
int longitud;
double precios;


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
    char* pr;
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
    cout << "\n\tIntroduce el número de tarjeta (sin espacios - 9 caracteres): ";

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
    char* pr;
    do{

        opcionPagoEntrada = mostrarPagarEntrada();
        switch(opcionPagoEntrada){
            case '1':
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir datos de la tarjeta";

                std::strcpy(numTarjeta, introducirNumTarjeta());
                std::strcpy(cvvTar, introducirCVVTar());
                std::strcpy(caducidadTar, introducirCaducidadTarjeta());

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
    char* pr;
    int existe = 0;
    int codigo;
    char inputCod[MAX_ENTRADAS+5];
    char* cod;
    char* type;
    char auxCodigo[16];
    char* resultado;
    do{
        opcionConfirmarPago = mostrarConfirmarPago();
        resultado= enviar_datos_char("mostrarRRPP",0);
        std::printf("%s",resultado);
        switch(opcionConfirmarPago){
            case '1':
                cout << "\n---------------------------------------------------\n";
            do {
                
                std::printf("%s\n", cod);

                errno = 0;
                long int num = strtol(cod, &type, 10); //CodigoFecha
                codigoFecha_ent = num;
                if (errno != 0 || *type != '\0') {
                    cout << "'" << cod << "' no es una entrada valida\n";
                }

            } while (errno != 0 || *type != '\0');

            bool isNumber = true;
            do {
                isNumber = true;
                cout << "Introducir Codigo de RRPP: ";
                cin.getline(inputCod, MAX_ENTRADAS);
                sscanf(inputCod, "%d", &codigo);
                        
                //BD
                cod = enviar_datos_char("limpiarInput", 1, &inputCod, sizeof(inputCod));
                for (int i = 0; cod[i] != '\0'; i++) {
                    if (!isdigit(cod[i])) {
                        isNumber = false;
                        break;
                    }
                }
                // do something here
            } while (!isNumber);

            std::printf(cod);
            //BD
            existe = enviar_datos_int("comprobarCodigoRRPP", 1, cod, strlen(cod));
            
            if (existe == 1) {
                cout << "RRPP con codigo: '" << auxCodigo << "' seleccionada correctamente\n";
                confirmarCompra();
            } else if ( existe == -1) {
                cout << "El codigo del RRPP seleccionado no existe\nOperacion cancelada\n";

            } else {
                cout << "Codigo seleccionado incorrectamente\nOperacion cancelada\n";
            }

            break;
        }
    } while(opcionConfirmarPago != '0');
}

void confirmarCompra(){
    char* pr;
    do {
        opcionConfirmarCompra = confirmarPagoCompra();
        switch (opcionConfirmarCompra) {
            case '1':
                cout << "\nEL PAGO HA SIDO CONFIRMADO\n"; // bd

                const char* codigo_aux = (std::to_string(codigoFecha_ent)).c_str();
                fecha_ent = enviar_datos_char("buscarFechaConCodidoFecha", 1, codigo_aux, strlen(codigo_aux)+1);
                std::printf("%s\n", fecha_ent);
                nomDiscoteca = enviar_datos_char("buscarDiscotecaConCodigoFecha", 1, codigo_aux, strlen(codigo_aux)+1);
                
                char* entradaCatFin;
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
                std::strcpy(entradaCatFin, entradaCat);

                const char* codFechaAux = (std::to_string(codigoFecha_ent)).c_str();
                const char* numEntradasAux = (std::to_string(numEntradas)).c_str();
                const char* preciosAux = (std::to_string(precios)).c_str();

                std::printf("%s\n", codFechaAux);
                std::printf("%s\n", fecha_ent);
                std::printf("%s\n", nomDiscoteca);
                std::printf("%s\n", numEntradasAux);
                std::printf("%s\n", gmail);
                std::printf("%s\n", numTarjeta);
                std::printf("%s\n", cvvTar);
                std::printf("%s\n", caducidadTar);
                std::printf("%s\n", entradaCatFin);
                std::printf("%s\n", preciosAux);
                std::printf("%s\n", nombreCompleto);

                int resultado = enviar_datos_int("insertarEntrada", 11, codFechaAux, strlen(codFechaAux)+1, fecha_ent, strlen(fecha_ent)+1, nomDiscoteca, strlen(nomDiscoteca)+1, numEntradasAux, strlen(numEntradasAux)+1, gmail, strlen(gmail)+1, numTarjeta, strlen(numTarjeta)+1, cvvTar, strlen(cvvTar)+1, caducidadTar, strlen(caducidadTar)+1, entradaCatFin, strlen(entradaCatFin)+1, preciosAux, strlen(preciosAux)+1, nombreCompleto, strlen(nombreCompleto)+1);

                opcionDatosCompra = '0';
                opcionPagoEntrada = '0';
                opcionConfirmarPago = '0';
                opcionConfirmarCompra = '0';
                menu();
            break;
        }
    } while (opcionConfirmarCompra != '0');
}
