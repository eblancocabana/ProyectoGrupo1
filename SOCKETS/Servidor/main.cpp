// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <sstream>
#include <limits>
#include "clases/reservalocal.h"

extern "C" {
    #include "basedatos/sqlite/sqlite3.h"
    #include "basedatos/baseDatos.h"
    #include "estructuras/entrada_est.h"
    #include "estructuras/reservarlocal_est.h"
    }

#include "administrador/inicio_servidor.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_LOGIN 15

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

using namespace std;

//Para ejecutar el "servidor.exe"

//gcc -c basedatos/baseDatos.c -o bd.o         CREAR .O DE LOS C
//gcc -c basedatos/sqlite/sqlite3.c -o sqlite.o         CREAR .O DE LOS C
//g++ -c administrador/inicio_servidor.cpp -o inicio.o         CREAR .O DE LOS C++
//g++ -c main.cpp -o main.o         CREAR .O DE LOS C++

//g++ main.o inicio.o sqlite.o bd.o -o servidor.exe -lWs2_32        EJECUTAR EL ARCHIVO

void iniciarSesion() {
    int existe = 1;
    char input[MAX_REGISTRO];

    cout << "Usuario: ";
    cin.getline(input, MAX_NOMBRE_USU);
    char* us = limpiarInput(input);

    cout << "Contrasenya: ";
    cin.getline(input, MAX_CONTRASENYA);
    char* pa = limpiarInput(input);

    existe = comprobarExistencia(us, pa);
    int admin = comprobarAdmin(us);

    if ((existe == 0) && (admin == 0)) {
        cout << "\nADMIN ENCONTRADO, accediendo al menu\n";
        inicioServidor();

    } else if ((existe == 0)) {
        cout << "\nUSUARIO NO ADMIN\n";

        return;
    } else {
        // Hacer algo si no se encuentra el usuario o la contraseña es incorrecta
    }
}

void deserializar_y_llamar_funcion(SOCKET comm_socket, char * recvBuff) {
  // Dividir el buffer recibido en el nombre de la función y los argumentos
  char * nombre_funcion = strtok(recvBuff, ":");
  char * args = strtok(NULL, ":");

  // Buffer para enviar el valor devuelto por la función llamada
  char sendBuff[512];
  int pos = 0;

  // Llamar a la función correspondiente con sus argumentos y enviar el valor devuelto
  if (strcmp(nombre_funcion, "inicializarUsuarios") == 0) {
    int ret = inicializarUsuarios();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "inicializarDiasDeFiesta") == 0) {
    int ret = inicializarDiasDeFiesta();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "inicializarDJ") == 0) {
    int ret = inicializarDJ();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "inicializarRRPP") == 0) {
    int ret = inicializarRRPP();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "inicializarListaEventos") == 0) {
    int ret = inicializarListaEventos();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "inicializacion") == 0) {
    int ret = inicializacion();
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "limpiarInput") == 0) {
    char * ret = limpiarInput(args);
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;
  } else if (strcmp(nombre_funcion, "clearIfNeeded") == 0) {
    // Dividir los argumentos en str y max_line
    char * ret = strtok(args, ",");
    int max_line = atoi(strtok(NULL, ","));
    clearIfNeeded(ret, max_line);
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;
  } else if (strcmp(nombre_funcion, "comprobarCodigoLocal") == 0) {
    int cod = atoi(args);
    int ret = comprobarCodigoLocal(cod);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarCodigoRRPP") == 0) {
    int cod = atoi(args);
    int ret = comprobarCodigoRRPP(cod);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarUsuario") == 0) {
    int ret = comprobarUsuario(args);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarFecha") == 0) {
    //Dividir los argumentos en fecha y evento
    char * fecha = strtok(args, ",");
    int evento = atoi(strtok(NULL, ","));
    int ret = comprobarFecha(fecha, evento);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarAdmin") == 0) {
    int ret = comprobarAdmin(args);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarExistencia") == 0) {
    //Dividir los argumentos en username y password
    char * username = strtok(args, ",");
    char * password = strtok(NULL, ",");
    int ret = comprobarExistencia(username, password);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "comprobarEntrada") == 0) {
    int ret = comprobarEntrada(args);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "insertarDiaFiesta") == 0) {
    //Dividir los argumentos en fecha,nomDiscoteca y eventoEsp
    char * fecha = strtok(args, ",");
    char * nomDiscoteca = strtok(NULL, ",");
    char * eventoEsp = strtok(NULL, ",");
    int ret = insertarDiaFiesta(fecha, nomDiscoteca, eventoEsp);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  } else if (strcmp(nombre_funcion, "insertarRegistro") == 0) {
    //Dividir los argumentos en nombre usuario sexo edad correo contra
    char * nombre = strtok(args, ",");
    char * usuario = strtok(NULL, ",");
    char * sexo = strtok(NULL, ",");
    int edad = atoi(strtok(NULL, ","));
    char * correo = strtok(NULL, ",");
    char * contra = strtok(NULL, ",");
    int ret = insertarRegistro(nombre, usuario, sexo, edad, correo, contra);
  } else if (strcmp(nombre_funcion, "insertarEvento") == 0) {
    //Dividir los argumentos en fecha,nombreDisco y descripcionEvento
    char * fecha = strtok(args, ",");
    char * nombreDisco = strtok(NULL, ",");
    char * descripcionEvento = strtok(NULL, ",");
    int ret = insertarEvento(fecha, nombreDisco, descripcionEvento);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);
  }

  // Enviar el valor devuelto por la función llamada a través del socket
  send(comm_socket, sendBuff, pos, 0);
}


int main(int argc, char *argv[]) {
    cout << "\n\n\n\n";
    cout << "\e[34m\e[1m";
    cout << "********************************\n";
    cout << "*                              *\n";
    cout << "*   SOUND STRATEGY PARTNERS    *\n";
    cout << "*                              *\n";
    cout << "********************************\n";
    cout << "\e[0m";
    cout << "\n";

    WSADATA wsaData;
    SOCKET conn_socket;
    SOCKET comm_socket;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char sendBuff[512], recvBuff[512];

    int opcion = 0;
    std::string entrada;

    while (opcion != 1 && opcion != 2) {
        cout << "Ingrese una opcion\n";
        cout << "\t1. Acceder como admin modo local\n";
        cout << "\t2. Ejecutar el servidor\n";

        getline(cin, entrada);

        try {
            opcion = std::stoi(entrada);

            if (opcion == 1) {
                cout << "Accediendo como admin modo local...\n";
                inicializacion();
                iniciarSesion();

                return 0;
            } else if (opcion == 2) {
                cout << "Ejecutando el servidor para ponerse en escucha...\n";
            } else {
                cout << "Opcion no válida. Por favor, intente nuevamente.\n";
            }
        } catch (std::exception const& e) {
            cout << "Entrada no válida. Por favor, ingrese un número entero.\n";
        }
    }

    cout << "\nInitialising Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed. Error Code : " << WSAGetLastError();

        return -1;
    }

    cout << "Initialised.\n";

    //SOCKET creation
    if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket : " << WSAGetLastError();
        WSACleanup();

        return -1;
    }

    cout << "Socket created.\n";

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    //BIND (the IP/port with socket)
    if (bind(conn_socket, (struct sockaddr*) &server,
            sizeof(server)) == SOCKET_ERROR) {
        cout << "Bind failed with error code: " << WSAGetLastError();
        closesocket(conn_socket);
        WSACleanup();

        return -1;
    }

    cout << "Bind done.\n";

    //LISTEN to incoming connections (socket server moves to listening mode)
    if (listen(conn_socket, 1) == SOCKET_ERROR) {
        cout << "Listen failed with error code: " << WSAGetLastError();
        closesocket(conn_socket);
        WSACleanup();

        return -1;
    }

    //ACCEPT incoming connections (server keeps waiting for them)
    cout << "Waiting for incoming connections...\n";
    int stsize = sizeof(struct sockaddr);
    comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
    // Using comm_socket is able to send/receive data to/from connected client
    if (comm_socket == INVALID_SOCKET) {
        cout << "accept failed with error code : " << WSAGetLastError();
        closesocket(conn_socket);
        WSACleanup();

        return -1;
    }
    cout << "Incomming connection from: " << inet_ntoa(client.sin_addr) <<
            "(" << ntohs(client.sin_port) << ")"<<std::endl;

     // Closing the listening sockets (is not going to be used anymore)
     closesocket(conn_socket);

     //SEND and RECEIVE data
     cout<<"Waiting for incoming messages from client... \n";
     do {
         int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
         if (bytes > 0) {
             cout<<"Receiving message... \n";
             cout<<"Data received: "<<recvBuff<<std::endl;

             // Deserializar los datos recibidos y llamar a la función correspondiente con sus argumentos
            deserializar_y_llamar_funcion(comm_socket, recvBuff);

             if (strcmp(recvBuff, "Bye") == 0)
                 break;
         }
         
     } while (1);

     // CLOSING the sockets and cleaning Winsock...
     closesocket(comm_socket);
     WSACleanup();

     return 0;
}
