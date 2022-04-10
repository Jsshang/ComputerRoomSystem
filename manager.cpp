#include "manager.h"
#include "globalFile.h"
#include <fstream>

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Manager::operMenu()
{
	cout << "welcome admin:" << this->m_Name << "login!" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.add_account         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.lookup_account      |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.lookup_computerRoom |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.clear_files         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.logout              |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "Please select your operation: " << endl;
}

void Manager::addPerson()
{
	cout << "Please input the type of account you want to add" << endl;
	cout << "1. add student" << endl;
	cout << "2. add teacher" << endl;

	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "Please input student id: ";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "Please input teacher id: ";
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	cin >> id;

	cout << "please input the name: " << endl;
	cin >> name;

	cout << "please input the passcode: " << endl;
	cin >> pwd;

	ofs << "\n" << id << " " << name << " " << pwd << " " << endl;
	cout << "account added successfully" << endl;

	system("pause");
	system("cls");

	ofs.close();
}

void Manager::showPerson()
{

}

void Manager::showComputer()
{

}

void Manager::cleanFile()
{

}

void Manager::initVector()
{

	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "file open failed" << endl;
		return;
	}

	vStu.clear();
	vTea.clear();

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "The current number of students is: " << vStu.size() << endl;
	ifs.close();

	Teacher t;


}