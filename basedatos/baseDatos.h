#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"

int dbExiste(char* fichero);
int abrirConexion();
void cerrarConexion(sqlite3* baseDatos);

int gestionarError(sqlite3* baseDatos);
void gestionarFree(char* str);
int eliminarTablas();
void selectRRPP(char codRRPP);
int comprobarExistencia();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void mostrarlistadoeventos();
int inicializacion();

void cargarLocales();

#endif