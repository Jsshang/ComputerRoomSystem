#include<iostream>
using namespace std;

#include "globalFile.h"
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include <fstream>
#include <string>

void managerMenu(Identity*& manager);

void LoginIn(string fileName, int type)
{
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "file not found!" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "Please input your student id: " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "Please input your employee id: " << endl;
		cin >> id;
	}

	cout << "Please input your name: " << endl;
	cin >> name;
	cout << "Please input your password: " << endl;
	cin >> pwd;

	if (type == 1)
	{
		int fId;
		string fName;
		string fPwd;

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "student loginIn succeed!" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);

				return;
			}
		}
	}
	else if (type == 2)
	{
		int fid;
		string fname;
		string fpwd;

		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (id == fid && name == fname && pwd == fpwd)
			{
				cout << "teacher loginin succeed!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				return;
			}
		}
	}
	else if (type == 3)
	{
		string fname;
		string fpwd;

		while (ifs >> fname && ifs >> fpwd)
		{
			if (name == fname && pwd == fpwd)
			{
				cout << "admin loginin succeed!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}

	cout << "Login verification failed!" << endl;

	system("pause");
	system("cls");
	return;
}

void managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();

		Manager* man = (Manager*)manager;
		int select = 0;

		cin >> select;

		if (select == 1)
		{
			cout << "add account" << endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			cout << "lookup account" << endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			cout << "lookup computerRoom" << endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			cout << "clear appointments" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;
			cout << "Logout succeed!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

int main() {

	int select = 0;

	while (true)
	{

		cout << "======================  welcome to the system  =====================" << endl;
		cout << endl << "please select your role " << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.student            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.teacher            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.admin              |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.exit               |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "Please select: ";

		cin >> select; //接受用户选择

		switch (select)
		{
		case 1:  //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:  //退出系统
			cout << "see you soon!" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "Incorrect choice, please select again!" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}