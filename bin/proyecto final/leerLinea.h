#include <iostream>
#include <conio.h>
///Edwin Adony Montejo Martínez 9491-21-3898
int leerLinea(char *cad, int n)
{
	int i, c;

	/* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}

	if (c == '\n') {
		i = 0;
	} else {
		cad[0] = c;
		i = 1;
	}

	/* 2. LECTURA DE LA CADENA */
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';

	/*3. LIMPIEZA DEL BUFFER */
	if (c != '\n' && c != EOF) /* es un caracter */
		while ((c = getchar()) != '\n' && c != EOF);

	return 1;
}
