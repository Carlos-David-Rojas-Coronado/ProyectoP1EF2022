#include<iomanip>

#include "sueldos.h"
#include "Puestos.h"
#include "niveldeestudio.h"

//#include "hora.h"

///Carlos David Rojas Coronado 9959-21-504


	class persona
    {
        private:
            string id,name,phone,college,address;
        public:
            void menu();
            void insert();
            void display();
            void modify();
            void search();
            void delet();
    };


    void persona::menu()
{
    int choice;
	char x;
	do
    {
	system("cls");

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t |   SISTEMA GESTION PERSONAS  |"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingreso Personas"<<endl;
	cout<<"\t\t\t 2. Despliegue Personas"<<endl;
	cout<<"\t\t\t 3. Modifica Personas"<<endl;
	cout<<"\t\t\t 4. Busca Personas"<<endl;
	cout<<"\t\t\t 5. Borra Personas"<<endl;
	cout<<"\t\t\t 6. conteo de sueldos"<<endl;
	cout<<"\t\t\t 7. ingresar nivel de estudio"<<endl;
	cout<<"\t\t\t 8. mostrar niveles de estudio"<<endl;
	cout<<"\t\t\t 9. puestos"<<endl;
	cout<<"\t\t\t 10. Mostrar bitacora"<<endl;
	cout<<"\t\t\t 11. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;

    switch(choice)
    {
    case 1:
    	do
    	{
    		insert();
    		cout<<"\n\t\t\t Agrega otra persona(Y,N): ";
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
		conteosueldos();
		break;
    case 7:
        insert2();
		break;
    case 8:
        display2();
		break;
	case 9:
	    ingresarpuestos();
		break;
    case 10:
		mostrarbitacora();
		break;
	case 11:
		exit(0);
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
	}
	getch();
    }while(choice!= 6);
}
void persona::insert()
{
	system("cls");
	fstream file;
	cout<<"\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n-------------------------------------------------Agregar detalles Persona ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Id Persona         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Persona     : ";
	cin>>name;
	cout<<"\t\t\tIngresa Telefono Persona   : ";
	cin>>phone;
	cout<<"\t\t\tIngresa Universidad Persona: ";
	cin>>college;
	cout<<"\t\t\tIngresa Direccion Persona  : ";
	cin>>address;
	file.open("ParticipantRecord.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
	file.close();





                    ///Edwin Adony Montejo Martínez 9491-21-3898



	hora();
	string filename("bitacora.dat");
	ofstream file_out;
	file_out.open("bitacora.dat", std::ios_base::app);
	file_out <<"el ultimo usuario logueado ingreso un nuevo registro con id:  "<< id;


}
void persona::display()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Personas -------------------------"<<endl;
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
			cout<<"\n\n\t\t\t Id Persona: "<<id<<endl;
			cout<<"\t\t\t Nombre Persona: "<<name<<endl;
			cout<<"\t\t\t Telefono Persona: "<<phone<<endl;
			cout<<"\t\t\t Universidad Persona: "<<college<<endl;
			cout<<"\t\t\t Direccion Persona: "<<address<<endl;
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
	cout<<"\n-------------------------Modificacion Detalles Persona-------------------------"<<endl;
	file.open("ParticipantRecord.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion..,";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese Id de la personas que quiere modificar: ";
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
				cout<<"\t\t\tIngrese Id Persona: ";
				cin>>id;
				cout<<"\t\t\tIngrese Nombre Persona: ";
				cin>>name;
				cout<<"\t\t\tIngrese Telefono Persona: ";
				cin>>phone;
				cout<<"\t\t\tIngrese Universidad Persona: ";
				cin>>college;
				cout<<"\t\t\tIngrese Direccion Persona: ";
				cin>>address;
				file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< name <<std::left<<std::setw(15)<< phone <<std::left<<std::setw(15)<< college <<std::left<<std::setw(15)<< address << "\n";
				found++;



                            ///Edwin Adony Montejo Martínez 9491-21-3898

				hora();
				string filename("bitacora.dat");
	    		ofstream file_out;
    			file_out.open("bitacora.dat", std::ios_base::app);
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
		cout<<"\n-------------------------Datos de la Persona buscada------------------------"<<endl;
		cout<<"\n\t\t\tNo hay informacion...";
	}
	else
	{
		string participant_id;
		cout<<"\n-------------------------Datos de Persona buscada------------------------"<<endl;
		cout<<"\nIngrese Id de la Persona que quiere buscar: ";
		cin>>participant_id;
		file >> id >> name >> phone >> college >> address;
		while(!file.eof())
		{
			if(participant_id==id)
			{
				cout<<"\n\n\t\t\t Id Persona: "<<id<<endl;
				cout<<"\t\t\t Nombre Persona: "<<name<<endl;
				cout<<"\t\t\t Telefono Persona: "<<phone<<endl;
				cout<<"\t\t\t Universidad Persona: "<<college<<endl;
				cout<<"\t\t\t Direccion Persona: "<<address<<endl;
				found++;




                                    ///Edwin Adony Montejo Martínez 9491-21-3898



				hora();
				string filename("bitacora.dat");
	    		ofstream file_out;
    			file_out.open("bitacora.dat", std::ios_base::app);
    			file_out <<"se consulto la persona "<<name << "con el id: " << id ;





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



                                ///Edwin Adony Montejo Martínez 9491-21-3898

				hora();
				string filename("bitacora.dat");
    			ofstream file_out;
    			file_out.open("bitacora.dat", std::ios_base::app);
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
