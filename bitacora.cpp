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

using namespace std;

using std::cout; using std::ofstream;
using std::endl; using std::string;
char hora();
int mostrarbitacora();

main(){
	hora();

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
