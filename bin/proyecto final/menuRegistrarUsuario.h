#include "existeUsuario.h"
#include "insertarUsuario.h"
#include "hora.h"

#define MAX 80


///José Rodrigo Pérez Cojon 9959-21-4557


void menuRegistrarUsuario() {
    char linea[MAX];
	Usuario usuario;
	char nombreUsuario[MAX];
	char respuesta[MAX];
	char repite = 1;

	do {
		system("cls");
		gotoxy(50,3); printf("REGISTRAR USUARIO");
		gotoxy(50,4); printf("=================");
		gotoxy(40,5); printf("Ingrese nombre de usuario: ");
		leerLinea(linea, MAX);
		sscanf(linea, "%s", nombreUsuario);

		/* Se verifica que el nombre de usuario no exista */
		if (!existeUsuario(nombreUsuario, &usuario)) {
			strcpy(usuario.nombre, nombreUsuario);

			gotoxy(40,6); printf("Ingrese la clave: ");
			leerLinea(usuario.password, MAX);

			/* Se inserta el usuario en el archivo de usuarios */
			if (insertarUsuario(usuario)) {
				gotoxy(40,7); printf("El usuario fue registrado satisfactoriamente!");
//				hora();
				string filename("bitacora.dat");
                ofstream file_out;
			    file_out.open("bitacora.dat", std::ios_base::app);
			    file_out <<"se registro un nuevo usuario:   "<<nombreUsuario;

			} else {
				gotoxy(40,7); printf("Ocurrio un error al registrar el usuario");
				gotoxy(40,8); printf("Inténtelo mas tarde");
			}
		} else {
			gotoxy(30,7); printf("El usuario \"%s\" ya ha sido registrado previamente", usuario.nombre);
			gotoxy(30,8);printf("No puede registrar dos usuarios con el mismo nombre de usuario.\n");
		}

		gotoxy(30,10); printf("Desea seguir registrando usuarios? [S/N]: ");
		leerLinea(respuesta, MAX);

		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}

	} while (repite == 1);
}

