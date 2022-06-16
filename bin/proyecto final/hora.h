#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
///Edwin Adony Montejo Martínez 9491-21-3898
//#include "menuSistema.h"

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

	string filename("bitacora.dat");
    ofstream file_out;

    file_out.open("bitacora.dat", std::ios_base::app);
    file_out << endl<< time->tm_mday << "/" << mes[time->tm_mon] << "/" << year << "  "<< time->tm_hour << ":"
<< time->tm_min << ":" << time->tm_sec<<"  \t";

 return 0;
}
int mostrarbitacora(){

	system("cls");
	string linea;

	ifstream archivo("bitacora.dat");

	while (getline(archivo,linea)){
		cout<<linea<<endl;
	}
	//menuSistema();
}
