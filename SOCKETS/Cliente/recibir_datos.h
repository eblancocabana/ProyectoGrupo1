// inicio.h
#ifndef RECIBIR_DATOS_H
#define RECIBIR_DATOS_H

#include <iostream>
#include <cstring>
#include <type_traits>
#include <winsock2.h>

extern SOCKET s;

template <typename T>
T recibir_datos() {
    char buffer[sizeof(T)];
    int bytes_recibidos = recv(s, buffer, sizeof(buffer), 0);
    if (bytes_recibidos == sizeof(T)) {
        T resultado;
        memcpy(&resultado, buffer, sizeof(T));
        return resultado;
    } else {
        std::cerr << "Error al recibir datos del servidor" << std::endl;
        return T();
    }
}

#endif
