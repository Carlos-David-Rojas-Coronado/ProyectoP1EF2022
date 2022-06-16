#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

#include "leerLinea.h"
#include "gotoxy.h"
#include "menuListarUsuarios.h"
#include "menuRegistrarUsuario.h"
#include "menuIniciarSesion.h"

using namespace std;

///Arlethe Esthepany Mendoza Guzmán 9959-21–1160

void MenuInicial() {
    setlocale(LC_CTYPE,"Spanish"); /// ASIGNAMOS IDIOMA
	system("color 87");
	char repite = 1, linea[80];
	int opcion = -1;

	do {
		system("cls");
		gotoxy (50,3); printf("MENU INICIAL");
		gotoxy (50,4); printf("============");
		gotoxy (40,5); printf("[1]. Ver usuarios registrados");
		gotoxy (40,6); printf("[2]. Registrar usuario nuevo");
		gotoxy (40,7); printf("[3]. Ingresar al sistema");
		gotoxy (40,8); printf("[0]. Salir");
		gotoxy (45,9); printf("Ingrese su opcion: [ ]\b\b");
		leerLinea(linea, 80);
		sscanf(linea, "%d", &opcion);

		switch (opcion) {
			case 1:
				menuListarUsuarios();
				break;

			case 2:
				menuRegistrarUsuario();
				break;

			case 3:
				menuIniciarSesion();
				break;

			case 0:
				repite = 0;
				break;
		}

	} while (repite == 1);
}
