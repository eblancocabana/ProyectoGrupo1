#ifndef _RESERVAR_LOCAL_H_
#define _RESERVAR_LOCAL_H_

void reservarLocal();

char mostrarListado();
void cargarLocales();

char* elegirFecha();
char* elegirDiscoteca();

void pagarReserva();
char mostrarPagarReserva();

char* introducirNumeroTarjeta();
char* introducirCVVTarjeta();
char* introducirCaducidadTarjeta();

#endif