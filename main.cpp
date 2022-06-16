#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<cstdlib>
#include<iomanip>
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

#define MAX 80
#define ARCHIVO_USUARIOS "usuarios.dat"
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3

using std::cout; using std::ofstream;
using std::endl; using std::string;
using std::cin;

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
int mostrarbitacora();

/* Funciones que manipulan el archivo de usuarios */
char insertarUsuario(Usuario usuario);
char existeUsuario(char nombreUsuario[], Usuario *usuario);
Usuario *obtenerUsuarios(int *);
char logear(char nombreUsuario[], char password[]);

int leerLinea(char *cad, int n);
void leerClave(char *password);
char hora();

char usuarioglob;

using namespace std;
class persona
{
	private:
		string id,name,phone,college,address;
	public:
		void menu();
		void insert();
		void sede();
		void carrera();
		void cursos();
		void creararchivo();
		void display();
		void display2();
		void display3();
		void display4();
		void display5();
		void modify();
		void search();
		void delet();
};

char linea[MAX];
int main() {
	menuInicial();
	return 0;
}

void menuInicial() {
	char repite = 1;
	int opcion = -1;

	do {
		system("cls");
		printf("\n\t\t\tMENU INICIAL\n");
		printf("\t\t\t============\n");
		printf("\n\t\t[1]. Ver usuarios registrados\n");
		printf("\t\t[2]. Registrar usuario nuevo\n");
		printf("\t\t[3]. Ingresar al sistema\n");
		printf("\t\t[0]. Salir\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
		leerLinea(linea, MAX);
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

void menuRegistrarUsuario() {
	Usuario usuario;
	char nombreUsuario[MAX];
	char respuesta[MAX];
	char repite = 1;

	do {
		system("cls");
		printf("\n\t\t\tREGISTRAR USUARIO\n");
		printf("\t\t\t=================\n");
		printf("\n\tIngrese nombre de usuario: ");
		leerLinea(linea, MAX);
		sscanf(linea, "%s", nombreUsuario);

		/* Se verifica que el nombre de usuario no exista */
		if (!existeUsuario(nombreUsuario, &usuario)) {
			strcpy(usuario.nombre, nombreUsuario);

			printf("\tIngrese la clave: ");
			leerLinea(usuario.password, MAX);

			/* Se inserta el usuario en el archivo de usuarios */
			if (insertarUsuario(usuario)) {
				printf("\n\tEl usuario fue registrado satisfactoriamente!\n");
				hora();
				string filename("bitacora.txt");
			    ofstream file_out;
			    file_out.open("bitacora.txt", std::ios_base::app);
			    file_out <<"se registro un nuevo usuario:   "<<nombreUsuario;

			} else {
				printf("\n\tOcurrio un error al registrar el usuario\n");
				printf("\nInténtelo mas tarde\n");
			}
		} else {
			printf("\n\tEl usuario \"%s\" ya ha sido registrado previamente\n", usuario.nombre);
			printf("\tNo puede registrar dos usuarios con el mismo nombre de usuario.\n");
		}

		printf("\n\tDesea seguir registrando usuarios? [S/N]: ");
		leerLinea(respuesta, MAX);

		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}

	} while (repite == 1);
}

void menuListarUsuarios() {
	int numeroUsuarios = 0;
	Usuario *usuarios;
	int i;

	system("cls");
	usuarios = obtenerUsuarios(&numeroUsuarios); /* Retorna un vector dinámico de usuarios */

	if (numeroUsuarios == 0) {
		printf("\n\tNo existe ningun usuario registrado!\n");

	} else {
		printf("\n\t\t    ==> LISTADO DE USUARIOS REGISTRADOS <==\n");
		printf(" ------------------------------------------------------------------------------\n");
		printf("%10s%25s%25s\n", "#", "NOMBRE", "PASSWORD");
		printf(" ------------------------------------------------------------------------------\n");

		/* Se recorre el vector dinámico de productos */
		for (i = 0; i < numeroUsuarios; i++) {
			printf("%10d%25s%25s\n", (i + 1), usuarios[i].nombre, usuarios[i].password);
		}
		printf(" ------------------------------------------------------------------------------\n");
	}

	// Se libera la memoria asignada al vector dinámico
	free(usuarios);
	usuarios = NULL;
	getchar();
}

void menuIniciarSesion() {
	char nombreUsuario[MAX];
	char password[MAX];
	int intento = 0;
	int loginExitoso = 0;

	do {
		system("cls");
		printf("\n\t\t\tINGRESAR AL SISTEMA\n");
		printf("\t\t\t===================\n");

		printf("\n\t\tUSUARIO: ");
		leerLinea(linea, MAX);
		sscanf(linea, "%s", nombreUsuario);

		printf("\t\tCLAVE: ");
		leerClave(password);

		if (logear(nombreUsuario, password)) {
			loginExitoso = 1;
		} else {
			printf("\n\n\t\tUsuario y/o password incorrectos");
			intento++;
			getchar();
		}
	} while (intento < MAX_INTENTOS && loginExitoso == 0);

	if (loginExitoso == 1) {
		menuSistema();

	} else {
		printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
		getchar();
	}
}

void menuSistema() {
	system("cls");
	printf("\n     ======================================================================\n");
	printf("\t\t\t     BIENVENIDO AL SISTEMA\n");
	printf("\t\t    Sistema de Coorporacion Educativa\n");
	printf("\t\t    Programacion 2022 | Carlos David Rojas Coronado\n");
	printf("     ======================================================================\n");

	persona estudiante;
	estudiante.menu();

	getchar();
}

/* Retorna 1 si se registró el usuario en el archivo correctamente */
char insertarUsuario(Usuario usuario) {
	FILE *archivo;
	char insercion = 0;

	/* Abre el archivo en modo de añadidura, para agregar datos al final. Si no existe es creado*/
	archivo = fopen(ARCHIVO_USUARIOS, "ab");

	if (archivo == NULL) {
		insercion = 0;

	} else {
		/* Registra el struct usuario en el archivo */
		fwrite(&usuario, sizeof(usuario), 1, archivo);
		insercion = 1;

		/* Cierra el archivo */
		fclose(archivo);
	}

	return insercion;
}

/* Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe */
char existeUsuario(char nombreUsuario[], Usuario* usuario) {
	FILE *archivo;
	char existe;

	/* Abre el archivo en modo de lectura */
	archivo = fopen(ARCHIVO_USUARIOS, "rb");

	if (archivo == NULL) {
		existe = 0;

	} else {
		existe = 0;

		/* Lee secuencialmente del archivo de usuarios */
		fread(&(*usuario), sizeof(*usuario), 1, archivo);
		while (!feof(archivo)) {
			if (strcmp((*usuario).nombre, nombreUsuario) == 0) {
				/* Encuentra un usuario del archivo con el nombre de usuario buscado */
				existe = 1;
				break;
			}

			fread(&(*usuario), sizeof(*usuario), 1, archivo);
		}

		/* Cierra el archivo*/
		fclose(archivo);
	}

	return existe;
}

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

/* Retorna 1 o 0 si el usuario y password son correctos para un usuario en particular */
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
					string filename("bitacora.txt");
				    ofstream file_out;
				    file_out.open("bitacora.txt", std::ios_base::app);
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

void leerClave(char *password) {
	char caracter;
	int i = 0;

	while (caracter = getch()) {
		if (caracter == TECLA_ENTER) {
			password[i] = '\0';
			break;

		} else if (caracter == TECLA_BACKSPACE) {
			if (i > 0) {
				i--;
				printf("\b \b");
			}

		} else {
			if (i < MAX) {
				printf("*");
				password[i] = caracter;
				i++;
			}
		}
	}
}
void persona::menu()
{
    int choice;
	char x;
	do
    {
	system("cls");

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t--Carlos David Rojas Coronado--"<<endl;
	cout<<"\t\t\t---------9959-21-504-----------"<<endl;
	cout<<"\t\t\t |   SISTEMA GESTION De INFORMACION  |"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingreso de Facultades"<<endl;
	cout<<"\t\t\t 2. Despliegue facultades"<<endl;
	cout<<"\t\t\t 3. Modifica Facultades"<<endl;
	cout<<"\t\t\t 4. Busca Facultades"<<endl;
	cout<<"\t\t\t 5. Borra Facultades"<<endl;
	cout<<"\t\t\t 6. Mostrar bitacora"<<endl;
	cout<<"\t\t\t 7. Registrar Aulas "<<endl;
	cout<<"\t\t\t 8. Mostrar Aulas"<<endl;
	cout<<"\t\t\t 9. Ingrese Sede "<<endl;
	cout<<"\t\t\t 10. Motrar Sedes"<<endl;
	cout<<"\t\t\t 11. Ingrese Cursos"<<endl;
	cout<<"\t\t\t 12. Mostrar Cursos"<<endl;
	cout<<"\t\t\t 13. Ingrese Carreras"<<endl;
	cout<<"\t\t\t 14. Mostrar Carreras"<<endl;
	cout<<"\t\t\t 15. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6/7/8/9/10/11/12/13/14]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;

    switch(choice)
    {
    case 1:
    	do
    	{
    		insert();
    		cout<<"\n\t\t\t Agrega otra Facultad(Y,N): ";
    		cin>>x;
		}while(x=='y'||x=='Y');
		break;
	case 2:
		display();
		break;
	case 3:
		modify();
		break;
	case 4:
		search();
		break;
	case 5:
		delet();
		break;
	case 6:
		mostrarbitacora();
		break;
	case 7:
        creararchivo();
        break;
    case 8:
        display2();
		break;
    case 9:
        sede();
        break;
    case 10:
        display3();
        break;
    case 11:
        cursos();
        break;
    case 12:
        display4();
        break;
    case 13:
        carrera();
        break;
    case 14:
        display5();
        break;
	case 15:
		exit(0);
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
	}
	getch();
    }while(choice!= 8);
}
void persona::insert()
{
	system("cls");
	fstream file;
	cout<<"\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n-------------------------------------------------Agregar detalles Persona ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Id Facultad         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Facultad     : ";
	cin>>name;
	cout<<"\t\t\tIngresa codigo Facultad   : ";
	cin>>phone;
	cout<<"\t\t\tIngresa nivel de Facultad: ";
	cin>>college;
	cout<<"\t\t\tIngresa Direccion Facultad  : ";
	cin>>address;
	file.open("ParticipantRecord.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
	file.close();
	hora();
	string filename("bitacora.txt");
	ofstream file_out;
	file_out.open("bitacora.txt", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;


}
void persona::display()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Facultad -------------------------"<<endl;
	file.open("ParticipantRecord.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Id Facultad: "<<id<<endl;
			cout<<"\t\t\t Nombre Facultad: "<<name<<endl;
			cout<<"\t\t\t codigo Facultad: "<<phone<<endl;
			cout<<"\t\t\t Nivel de Facultad: "<<college<<endl;
			cout<<"\t\t\t Ingrese Estatus de Facultad: "<<address<<endl;
			file >> id >> name >> phone >> college >> address;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
	}
	file.close();
}
void persona::modify()
{
	system("cls");
	fstream file,file1;
	string participant_id;
	int found=0;
	cout<<"\n-------------------------Modificacion Detalles sobre Facultad-------------------------"<<endl;
	file.open("ParticipantRecord.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion..,";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese Id de la Facultad que quiere modificar: ";
		cin>>participant_id;
		file1.open("Record.txt",ios::app | ios::out);
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			if(participant_id!=id)
			{
			 file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
			}
			else
			{
				cout<<"\t\t\tIngrese Id Facultad: ";
				cin>>id;
				cout<<"\t\t\tIngrese Nombre Facultad: ";
				cin>>name;
				cout<<"\t\t\tIngrese Codigo Facultad: ";
				cin>>phone;
				cout<<"\t\t\tIngrese Nivel de Facultad: ";
				cin>>college;
				cout<<"\t\t\tIngrese estatus Facultad: ";
				cin>>address;
				file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
				found++;
				hora();
				string filename("bitacora.txt");
	    		ofstream file_out;
    			file_out.open("bitacora.txt", std::ios_base::app);
    			file_out <<"el ultimo usuario logueado modifico el registro con id  "<<id;

			}
			file >> id >> name >> phone >> college >> address;

		}
		file1.close();
		file.close();
		remove("ParticipantRecord.txt");
		rename("Record.txt","ParticipantRecord.txt");
	}
}
void persona::search()
{
	system("cls");
	fstream file;
	int found=0;
	file.open("ParticipantRecord.txt",ios::in);
	if(!file)
	{
		cout<<"\n-------------------------Datos de la Facultad buscada------------------------"<<endl;
		cout<<"\n\t\t\tNo existe tal informacion informacion...";
	}
	else
	{
		string participant_id;
		cout<<"\n-------------------------Datos de Facultad buscada------------------------"<<endl;
		cout<<"\nIngrese Id de la Facultad que quiere buscar: ";
		cin>>participant_id;
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			if(participant_id==id)
			{
				cout<<"\n\n\t\t\t Id Facultad: "<<id<<endl;
				cout<<"\t\t\t Nombre Facultad: "<<name<<endl;
				cout<<"\t\t\t Codigo Facultad: "<<phone<<endl;
				cout<<"\t\t\t Nivel de Facultad: "<<college<<endl;
				cout<<"\t\t\t Estatus Facultad: "<<address<<endl;
				found++;
			}
			file >> id >> name >> phone >> college >> address;
		}
		if(found==0)
		{
			cout<<"\n\t\t\t Persona no encontrada...";
		}
		file.close();
	}
}
void persona::delet()
{
	system("cls");
	fstream file,file1;
	string participant_id;
	int found=0;
	cout<<"\n-------------------------Detalles Persona a Borrar-------------------------"<<endl;
	file.open("ParticipantRecord.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion...";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese el Id de la Persona que quiere borrar: ";
		cin>>participant_id;
		file1.open("Record.txt",ios::app | ios::out);
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			if(participant_id!= id)
			{
				file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
			}
			else
			{
				found++;
				hora();
				string filename("bitacora.txt");
    			ofstream file_out;
    			file_out.open("bitacora.txt", std::ios_base::app);
    			file_out <<"el ultimo usuario logueado elimino el registro con id  "<<id;
				cout << "\n\t\t\tBorrado de informacion exitoso";


			}
			file >> id >> name >> phone >> college >> address;
		}
		if(found==0)
		{
			cout<<"\n\t\t\t Id Persona no encontrado...";
		}

		remove("ParticipantRecord.txt");
		rename("Record.txt","ParticipantRecord.txt");
		file1.close();
		file.close();
	}
}
void persona::creararchivo()
{
    system("cls");
    fstream file;
    cout<<"\n-------------------------------------------------Agregar detalles del aula ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Id Aula         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Aula    : ";
	cin>>name;
	cout<<"\t\t\tIngresa Codigo Aula  : ";
	cin>>phone;
	cout<<"\t\t\tIngresa Estatus Aula: ";
	cin>>college;
	cout<<"\t\t\tIngresa Nivel Aula  : ";
	cin>>address;
    file.open("NivelesdeEstudio.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
	file.close();
	hora();
	string filename("bitacora.txt");
	ofstream file_out;
	file_out.open("bitacora.txt", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;

}
void persona::display2()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles del codigo del aula -------------------------"<<endl;
	file.open("NivelesdeEstudio.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Id Aula: "<<id<<endl;
			cout<<"\t\t\t Nombre Aula: "<<name<<endl;
			cout<<"\t\t\t Codigo Aula: "<<phone<<endl;
			cout<<"\t\t\t Estatus Aula: "<<college<<endl;
			cout<<"\t\t\t Nivel del Aula: "<<address<<endl;
			file >> id >> name >> phone >> college >> address;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion(por culpa de Juan >:V)...";
		}
	}
	file.close();
}
void persona::sede()
{
    system("cls");
    fstream file;
    cout<<"\n-------------------------------------------------Agregar detalles de la Sede ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Codigo Sede         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Sede    : ";
	cin>>name;
	cout<<"\t\t\tIngresa Estatus Sede: ";
	cin>>college;
    file.open("Sedesymas.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< college << "\n";
	file.close();
	hora();
	string filename("bitacora.txt");
	ofstream file_out;
	file_out.open("bitacora.txt", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;

}
void persona::display3()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de la Sede -------------------------"<<endl;
	file.open("Sedesymas.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo existe tal información...";
		file.close();
	}
	else
	{
		file >> id >> name >> college;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Codigo Sede: "<<id<<endl;
			cout<<"\t\t\t Nombre Sede: "<<name<<endl;
			cout<<"\t\t\t Estatus Sede: "<<college<<endl;
			file >> id >> name >> college;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion(por culpa de Juan >:V)...";
		}
	}
	file.close();
}
void persona::carrera()
{
    system("cls");
    fstream file;
    cout<<"\n-------------------------------------------------Agregar detalles de la Carrera ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Codigo Carrera         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Carrera    : ";
	cin>>name;
	cout<<"\t\t\tIngresa Estatus Carrera: ";
	cin>>college;
	cout<<"\t\t\tIngresa codigo Facultad:  ";
	cin>>address;
    file.open("Carreramas.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
	file.close();
	hora();
	string filename("bitacora.txt");
	ofstream file_out;
	file_out.open("bitacora.txt", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;

}
void persona::display4()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de la Carrera -------------------------"<<endl;
	file.open("Carreramas.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo existe tal información...";
		file.close();
	}
	else
	{
		file >> id >> name >> college;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Codigo Carrera: "<<id<<endl;
			cout<<"\t\t\t Nombre Carrera: "<<name<<endl;
			cout<<"\t\t\t Estatus Carrera: "<<college<<endl;
			cout<<"\t\t\t Codigo Facultad: "<<address<<endl;
			file >> id >> name >> college >> address;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion(por culpa de Juan >:V)...";
		}
	}
	file.close();
}
void persona::cursos()
{
    system("cls");
    fstream file;
    cout<<"\n-------------------------------------------------Agregar detalles del Curso ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Codigo Curso        : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Curso    : ";
	cin>>name;
	cout<<"\t\t\tIngresa Estatus Curso: ";
	cin>>college;
    file.open("Cursosya.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< college << "\n";
	file.close();
	hora();
	string filename("bitacora.txt");
	ofstream file_out;
	file_out.open("bitacora.txt", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;

}
void persona::display5()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles del Curso -------------------------"<<endl;
	file.open("Cursosya.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo existe tal información...";
		file.close();
	}
	else
	{
		file >> id >> name >> college;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Codigo Curso: "<<id<<endl;
			cout<<"\t\t\t Nombre Curso: "<<name<<endl;
			cout<<"\t\t\t Estatus Curso: "<<college<<endl;
			file >> id >> name >> college;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion(por culpa de Juan >:V)...";
		}
	}
	file.close();
}
char hora()
{
/* fecha/hora actual basado en el sistema actual */
time_t now = time(0);

/* Objeto de una estructura tm con fecha/hora local */
tm * time = localtime(&now);

vector<string> mes;
mes.push_back("1");
mes.push_back("2");
mes.push_back("3");
mes.push_back("4");
mes.push_back("5");
mes.push_back("6");
mes.push_back("7");
mes.push_back("8");
mes.push_back("9");
mes.push_back("10");
mes.push_back("11");
mes.push_back("12");

int year = 1900 + time->tm_year;

	string filename("bitacora.txt");
    ofstream file_out;

    file_out.open("bitacora.txt", std::ios_base::app);
    file_out << endl<< time->tm_mday << "/" << mes[time->tm_mon] << "/" << year << "  "<< time->tm_hour << ":"
<< time->tm_min << ":" << time->tm_sec<<"  \t";

 return 0;
}
int mostrarbitacora(){

	system("cls");
	string linea;

	ifstream archivo("bitacora.txt");

	while (getline(archivo,linea)){
		cout<<linea<<endl;
	}
}
