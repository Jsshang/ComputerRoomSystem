#include "manager.h"
#include "globalFile.h"
#include <fstream>
#include <algorithm>

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	// construct with parameter and initialize vectors for future use
	this->initVector();

	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;

	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	cout << "The current number of computer rooms is: " << vCom.size() << endl;
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

	string errorTip;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "Please input student id: ";
		errorTip = "Student id already exists, please try again";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "Please input teacher id: ";
		errorTip = "Employee id already exists, please try again";
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (true)
	{
		cin >> id;

		bool ret = this->checkRepeat(id, select);

		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "please input the name: " << endl;
	cin >> name;

	cout << "please input the passcode: " << endl;
	cin >> pwd;

	ofs << "\n" << id << " " << name << " " << pwd << " " << endl;
	cout << "account added successfully" << endl;

	system("pause");
	system("cls");

	ofs.close();

	this->initVector();
}

void printStudent(Student& s)
{
	cout << "student id: " << s.m_Id << "student name: " << s.m_Name << "password: "
		<< s.m_Pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "Employee id: " << t.m_EmpId << "Employee name: " << t.m_Name << "password: "
		<< t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "Please select the content. " << endl;
	cout << "1. show all students" << endl;
	cout << "2. show all teachers" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		cout << "Information of all studentS: " << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "Information of all teachers: " << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "current computerRoom info is: " << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "Roomnumber: " << it->m_ComId << " the maximum capacity: " << it->m_MaxNum << endl;
	}

	system("pause");
	system("cls");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "Appointment records have been cleared!" << endl;
	system("pause");
	system("cls");
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

	ifs.open(TEACHER_FILE, ios::in);
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "The current number of teacher is: " << vTea.size() << endl;
	ifs.close();

}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}

	return false;
}