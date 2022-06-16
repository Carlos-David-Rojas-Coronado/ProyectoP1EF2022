#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX 80
#define ARCHIVO_USUARIOS "usuarios.dat"
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3

/* Estructura de cuentas de usuario */
struct usuario {
	char nombre[MAX];
	char password[MAX];
};

typedef struct usuario Usuario;

/* Funciones de menú */
void menuInicial();
void menuListarUsuarios();
void menuRegistrarUsuario();
void menuIniciarSesion();
void menuSistema();

/* Funciones que manipulan el archivo de usuarios */
char insertarUsuario(Usuario usuario);
char existeUsuario(char nombreUsuario[], Usuario *usuario);
Usuario *obtenerUsuarios(int *);
char logear(char nombreUsuario[], char password[]);

int leerLinea(char *cad, int n);
void leerClave(char *password);

char linea[MAX];
int main() {
	menuInicial();
	return 0;
}
