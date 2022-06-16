#include <stdio.h>

#define ARCHIVO_USUARIOS "usuarios.dat"
#define MAX 80


///José Rodrigo Pérez Cojon 9959-21-4557

struct usuario {
     char nombre[MAX];
     char password[MAX];
 };
 typedef struct usuario Usuario;



Usuario *obtenerUsuarios(int *n) {

	FILE *archivo;
	Usuario usuario;
	Usuario *usuarios; /* Vector dinámico de usuarios */
	int i;

	/* Abre el archivo en modo lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n = 0 */
		usuarios = NULL;

	} else {

		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(Usuario); /* # de usuarios almacenados en el archivo. (# de registros) */
		usuarios = (Usuario *)malloc((*n) * sizeof(Usuario)); /* Se asigna memoria para todos los usuarios almacenados en el archivo */

		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&usuario, sizeof(usuario), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			usuarios[i++] = usuario;
			fread(&usuario, sizeof(usuario), 1, archivo);
		}

		/* Cierra el archivo */
		fclose(archivo);
	}

	return usuarios;
}
