#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "baseDatos.h"
#include "../inicio.h"

#define MAX_REGISTRO 20
#define MAX_LOGIN 15
#define MAX_NOMBRE_USU 20
#define MAX_CONTRASENYA 20

sqlite3* database;
int apertura;
int aperturaInsert;
int existeBD;
char* mensajeError = NULL;
char* errorMessage = NULL;

int dbExiste(char* fichero) {
  FILE* arch = fopen(fichero, "r");

  if (arch) {
    fclose(arch);
    return 1;
  }
  return 0;
}

int gestionarError(sqlite3* baseDatos) {
  fprintf(stderr, "\nSQL Error: %s\n", sqlite3_errmsg(baseDatos));
  return sqlite3_errcode(baseDatos);
}

void gestionarFree(char* str) {
  sqlite3_free(str);
}

void cerrarConexion(sqlite3* baseDatos) {
  sqlite3_close(baseDatos);
  fprintf(stdout, "\nLa Base De Datos se cerro exitosamente\n");
}

int abrirConexion() {
  existeBD = dbExiste("basedatosSSR.db");
  apertura = sqlite3_open("basedatosSSR.db", &database);
  
  if (apertura != SQLITE_OK) {
    fprintf(stderr, "No se puede abrir la Base De Datos: %s\n", gestionarError(database));
    cerrarConexion(database);
    return 0;

  } else {
    fprintf(stdout, "\nLa Base De Datos se abrio exitosamente\n");
    return 1;
  }
}



int comprobarExistencia() {
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  abrirConexion();

  char input[MAX_REGISTRO];

  printf("Usuario: ");
  fgets(input, MAX_NOMBRE_USU, stdin);

  char * username = malloc((MAX_NOMBRE_USU) * sizeof(char));
  sscanf(input, "%s", username); //le quita el 'n' (si lo hay)

  clearIfNeeded(input, MAX_NOMBRE_USU); //le quita el 'n' (si lo hay)
  fflush(stdout);
  fflush(stdin);

  printf("Contrasenya: ");
  fgets(input, MAX_CONTRASENYA, stdin);

  char * password = malloc((MAX_CONTRASENYA) * sizeof(char));
  sscanf(input, "%s", password); //le quita el 'n' (si lo hay)

  clearIfNeeded(input, MAX_CONTRASENYA); //le quita el 'n' (si lo hay)
  fflush(stdout);
  fflush(stdin);

  printf("%s, %s", username, password);

  char * sentencia = "SELECT usuario, contrasenya FROM usuarios WHERE usuario = ? AND contrasenya = ?;";
  if (sqlite3_errcode(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos.:::%s\n",sqlite3_errmsg(database));
    // Aquí puedes agregar el código para manejar el error.
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);
  printf("\n%i\n", busqueda);

  sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
  sqlite3_bind_text(statement, 2, password, strlen(password), SQLITE_STATIC);

  if (busqueda != SQLITE_OK) {
    printf("AQUI");
    printf("Error preparing SQL statement: %s\n", sqlite3_errmsg(database));
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  printf("BIEN");

  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);

    cerrarConexion(database);
    return 0;
  }

  if (busqueda == SQLITE_ROW) {
    printf("\nUSUARIO ENCONTRADO, accediendo al menu\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;

  } else if (busqueda != SQLITE_OK) {
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else {
    printf("No se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
  }

  cerrarConexion(database);
  return 0;
}





int eliminarTablas() {
  char* sentenciaDDF = "DROP TABLE IF EXISTS dias_de_fiesta;";

  int resultadoDDF = sqlite3_exec(database, sentenciaDDF, NULL, NULL, &mensajeError);

  if (resultadoDDF != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  char* sentenciaDJ = "DROP TABLE IF EXISTS dj;";

  int resultadoDJ = sqlite3_exec(database, sentenciaDJ, NULL, NULL, &mensajeError);

  if (resultadoDJ != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  char* sentenciaLE = "DROP TABLE IF EXISTS listaEventos;";

  int resultadoLE = sqlite3_exec(database, sentenciaLE, NULL, NULL, &mensajeError);

  if (resultadoLE != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  char* sentenciaRRPP = "DROP TABLE IF EXISTS rrpp;";

  int resultadoRRPP = sqlite3_exec(database, sentenciaRRPP, NULL, NULL, &mensajeError);

  if (resultadoRRPP != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  char* sentenciaUsu = "DROP TABLE IF EXISTS usuarios;";

  int resultadoUsu = sqlite3_exec(database, sentenciaUsu, NULL, NULL, &mensajeError);

  if (resultadoUsu != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);
      
      cerrarConexion(database);
      return 1;
  }

  return 0;
}

int inicializacion() {
  
  abrirConexion();

  if (!existeBD) {
    //Se eliminan las tablas para evitar errores
    eliminarTablas();

    // Implementacion de importacion de datos CSV
    char * sql = "CREATE TABLE dias_de_fiesta(codigo TEXT PRIMARY KEY NOT NULL, fecha DATE NOT NULL, nombre TEXT NOT NULL, entradas INT NOT NULL, especial TEXT NOT NULL)";
    apertura = sqlite3_exec(database, sql, 0, 0, &mensajeError);

    if (apertura != SQLITE_OK) {
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
    }

    FILE* fp = fopen("ficheros/dias_de_fiesta.csv", "r");
    if (!fp) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line[1024];

    fgets(line, sizeof(line), fp); // Saltar la primera línea (encabezados)

    while (fgets(line, sizeof(line), fp)) {

      char codigo[50], fecha[50], nombre[50], entradas[50], especial[50];

      sscanf(line, "%[^','],%[^','],%[^','],%[^','],%s", codigo,
        fecha, 
        nombre,
        entradas,
        especial);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO dias_de_fiesta VALUES('%s','%s','%s',%s,'%s');",
        codigo,
        fecha,
        nombre,
        entradas,
        especial);

      aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarFree(mensajeError);
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }

    fclose(fp);

    char * sql2 = "CREATE TABLE dj(identificador INT PRIMARY KEY NOT NULL, nombre_comercial TEXT NOT NULL, genero_musical TEXT NOT NULL, fecha_nacimiento TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql2, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
    }

    FILE * fp2 = fopen("ficheros/dj.csv", "r");
    if (!fp2) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line2[1024];

    fgets(line2, sizeof(line2), fp2); // Saltar la primera línea (encabezados)

    while (fgets(line2, sizeof(line2), fp2)) {

      char identificador[50], nombre_comercial[50], genero_musical[50], fecha_nacimiento[50], numero_contacto[50];

      sscanf(line2, "%[^','],%[^','],%[^','],%[^','],%s", identificador,
        nombre_comercial,
        genero_musical,
        fecha_nacimiento,
        numero_contacto);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO dj VALUES(%s,'%s','%s','%s','%s');",
        identificador,
        nombre_comercial,
        genero_musical,
        fecha_nacimiento,
        numero_contacto);

      aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
      
      if (apertura != SQLITE_OK) {
        gestionarFree(mensajeError);
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }

    fclose(fp2);

    char * sql3 = "CREATE TABLE listaEventos(dia TEXT NOT NULL, descripcion TEXT NOT NULL, nombre_discoteca TEXT NOT NULL, aforo INT NOT NULL);";
    apertura = sqlite3_exec(database, sql3, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
    }

    FILE * fp3 = fopen("ficheros/listaeventos.csv", "r");
    if (!fp3) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line3[1024];

    fgets(line3, sizeof(line3), fp3); // Saltar la primera línea (encabezados)

    while (fgets(line3, sizeof(line3), fp3)) {

      char Dia[50], Descripcion[50], nombre_discoteca[50], Aforo[50];

      sscanf(line3, "%[^','],%[^','],%[^','],%s", Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO listaEventos VALUES('%s','%s','%s',%s);",
        Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

      aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
      
      if (apertura != SQLITE_OK) {
        gestionarFree(mensajeError);
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }

    fclose(fp3);

    char * sql4 = "CREATE TABLE rrpp(codigo INT PRIMARY KEY NOT NULL, nombre TEXT NOT NULL, zona_recogida TEXT NOT NULL, hora_recogida TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql4, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
    }

    FILE * fp4 = fopen("ficheros/rrpp.csv", "r");
    if (!fp4) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line4[1024];

    fgets(line4, sizeof(line4), fp4); // Saltar la primera línea (encabezados)

    while (fgets(line4, sizeof(line4), fp4)) {

      char Codigo[50], nombre[50], zona_recogida[50], hora_recogida[50], numero_contacto[50];

      sscanf(line4, "%[^','],%[^','],%[^','],%[^','],%s", Codigo,
        nombre,
        zona_recogida,
        hora_recogida,
        numero_contacto);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO rrpp VALUES(%s,'%s','%s','%s','%s');",
        Codigo,
        nombre,
        zona_recogida,
        hora_recogida,
        numero_contacto);

      aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
      
      if (apertura != SQLITE_OK) {
        gestionarFree(mensajeError);
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }

    fclose(fp4);

    char * sql5 = "CREATE TABLE usuarios(nombre TEXT NOT NULL, usuario TEXT NOT NULL, sexo TEXT NOT NULL, edad INT NOT NULL, email TEXT NOT NULL, contrasenya TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql5, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
    }

    FILE * fp5 = fopen("ficheros/usuarios.csv", "r");
    if (!fp5) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line5[1024];

    fgets(line5, sizeof(line5), fp5); // Saltar la primera línea (encabezados)

    while (fgets(line5, sizeof(line5), fp5)) {

      char Nombre[50], nombre_usuario[50], Sexo[50], Edad[50], email[50], password[50];

      sscanf(line5, "%[^','],%[^','],%[^','],%[^','],%[^','],%s", Nombre,
        nombre_usuario,
        Sexo,
        Edad,
        email,
        password);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO usuarios VALUES('%s','%s','%s',%s,'%s','%s');",
        Nombre,
        nombre_usuario,
        Sexo,
        Edad,
        email,
        password);

      aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarFree(mensajeError);
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }
    fclose(fp5);
  }
  
  cerrarConexion(database);
  printf("Se mantendra cerrada hasta cualquier cambio\n");

  return 0;
}

void selectRRPP(char codRRPP){
    
}


void cargarLocales() {
  /*
  char* st = "SELECT * FROM dias_de_fiesta WHERE fecha > ?";

  time_t current_time;
  time(&current_time);

  struct tm* local_time = localtime(&current_time);

  char date_str[8];
  strftime(date_str, sizeof(date_str, "%Y-%m-%d", local_time));
  */

  char* st = "SELECT * FROM dias_de_fiesta";
  sqlite3_stmt* sql_st;
  apertura = sqlite3_prepare_v2(database, st, -1, &sql_st, 0);


  if (apertura != SQLITE_OK) {
    fprintf(stderr, "Error en la consulta: %s\n", sqlite3_errmsg(database));
    sqlite3_finalize(sql_st);
    cerrarConexion(database);
    return 0;
  }

  apertura = sqlite3_step(sql_st);

  while (apertura != SQLITE_DONE) {
    if (apertura == SQLITE_ROW) {
      char* codigo = sqlite3_column_int(sql_st, 0);
      char* fecha = sqlite3_column_int(sql_st, 1);
      char* nombre = sqlite3_column_int(sql_st, 2);
      char* entradas = sqlite3_column_int(sql_st, 3);
      char* especial = sqlite3_column_int(sql_st, 4);

      // crear un listado de los datos
      printf("%s - %s - %s\n", codigo, fecha, nombre);
    }

    apertura = sqlite3_step(sql_st);
  }

  sqlite3_finalize(sql_st);

}