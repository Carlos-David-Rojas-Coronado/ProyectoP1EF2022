///Carlos David Rojas Coronado 9959-21-504
string name;

void insert2()
{

    system("cls");
    fstream file;
    cout<<"\n-------------------------------------------------Agregar detalles del nivel de Estudio ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa el nivel de estudio: ";
	cin>>name;
	/*cout<<"\t\t\tIngresa Nombre Persona     : ";
	cin>>name;
	cout<<"\t\t\tIngresa Nivel Persona   : ";
	cin>>phone;
	cout<<"\t\t\tIngresa Estudio Persona: ";
	cin>>college;
	cout<<"\t\t\tIngresa Departamento Persona  : ";
	cin>>address;*/
	/*id="0";
	phone="0";
	college = "0";
	address = "0";
*/
    //cout << name;

    file.open("NivelesdeEstudio.dat", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< name << "\n";
	file.close();
	hora();
	string filename("bitacora.dat");
	ofstream file_out;
	file_out.open("bitacora.dat", std::ios_base::app);
	file_out <<"el ultimo usuario ingreso un nivel de estudio  "<< name ;

}
void display2()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Niveles de Estudio -------------------------"<<endl;
	file.open("NivelesdeEstudio.dat",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> name ;
		while(!file.eof())
		{
			total++;
			//cout<<"\n\n\t\t\t Id Persona: "<<id<<endl;
			cout<<"\t\t\t Nombre de los niveles de estudio: "<<name<<endl;
			//cout<<"\t\t\t Nivel Persona: "<<phone<<endl;
			//cout<<"\t\t\t Estudio de  Persona: "<<college<<endl;
			//cout<<"\t\t\t Departamento Persona: "<<address<<endl;
			file >> name ;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion(por Juna >:V)...";
		}
	}
	file.close();
}
