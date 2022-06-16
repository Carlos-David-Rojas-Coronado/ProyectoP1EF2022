

///José Rodrigo Pérez Cojon 9959-21-4557

char logear(char nombreUsuario[], char password[]) {
	FILE *archivo;
	char logeoExitoso;
	Usuario usuario;

	/* Abre el archivo en modo de lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) {
		logeoExitoso = 0;

	} else {
		logeoExitoso = 0;

		/* Lee secuencialmente del archivo de usuarios */
		fread(&usuario, sizeof(usuario), 1, archivo);
		while (!feof(archivo)) {
			if (strcmp(usuario.nombre, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0) {
				/* Encuentra un usuario del archivo con el nombre de usuario y password buscado */
				logeoExitoso = 1;
					hora();
					string filename("bitacora.dat");
				    ofstream file_out;
				    file_out.open("bitacora.dat", std::ios_base::app);
				    file_out <<usuario.nombre<<" se logueo";

				break;
			}

			fread(&usuario, sizeof(usuario), 1, archivo);
		}

		/* Cierra el archivo*/
		fclose(archivo);
	}

	return logeoExitoso;
}
