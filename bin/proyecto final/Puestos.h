#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>

///Leticia Eugenia sontay chanchavac 9491-21-9664


using namespace std;
const char *nombe_archivo = "archivo.dat";

struct Empleado{
	int codigo_Puesto;
	char nombre_Puesto[50];
	int borrar=0;
};
void ingresarpuestos();

//main(){}

void ingresarpuestos(){
	system("cls");
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab");
	string nombre_Puesto,codigo_Puesto;
		Empleado empleado;
		do{
			fflush(stdin);
		cout<<"INGRESE CODIGO DEL PUESTO: ";
		cin>>empleado.codigo_Puesto;
        cin.ignore();

		cout<<"INGRESE NOMBRE DEL PUESTO:             ";
		cin>>empleado.nombre_Puesto;
		cin.ignore();

		empleado.borrar==0;
		fwrite( &empleado, sizeof(Empleado), 1, archivo );

		cout<<"QUIERE REGISTRAR OTRO EMPLEADO [S/N] : ";
		cin>>continuar;
		} while((continuar=='s') || (continuar=='S') );

	fclose(archivo);
	//main();

}
